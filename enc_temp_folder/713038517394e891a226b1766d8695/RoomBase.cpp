// Fill out your copyright notice in the Description page of Project Settings.

#include "Room/RoomBase.h"
#include <Room/RoomDef.h>
#include "Components/PointLightComponent.h"
#include "Components/SpotLightComponent.h"
#include <Camera/RoomCamera.h>
#include <Kismet/GameplayStatics.h>
#include <PlayerController/GodPlayerController.h>
#include <Camera/CameraManager.h>

ARoomBase::ARoomBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// 部屋の原点を設定
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RoomRoot"));

	// 床配置用の親コンポーネントを作成
	FloorRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("FloorRootComp"));
	FloorRootComp->SetupAttachment(RootComponent);

	// 壁配置用の親コンポーネントを作成
	WallRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("WallRootComp"));
	WallRootComp->SetupAttachment(RootComponent);

	// 天井配置用の親コンポーネントを作成
	RoofRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RoofRootComp"));
	RoofRootComp->SetupAttachment(RootComponent);
}

void ARoomBase::BeginPlay()
{
	Super::BeginPlay();
	
	// 部屋のレイアウトに基づいてモジュールを配置
	SetupRoomLayout();
}

void ARoomBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 部屋のレイアウトに基づいてモジュールを配置
void ARoomBase::SetupRoomLayout()
{
	// タイルの数を初期化
	InitializeTileCounts();

	// 床の配置
	SetupFloor();
	// 壁の配置
	SetupWalls();
	// 天井の配置
	SetupRoof();

	// 天井から下向きにライトを配置（天井中央に1つ）
	SetupLights();

	// カメラの配置
	SetupCamera();
}

// 床の配置
void ARoomBase::SetupFloor()
{
	if (LayoutData == nullptr || LayoutData->FloorClass == nullptr)
		return;

	// 床の生成
	for (int i = 0; i < FloorTileHeight; ++i)
	{
		for (int j = 0; j < FloorTileWidth;++j)
		{
			AActor* FloorTile = GetWorld()->SpawnActor<AActor>(LayoutData->FloorClass);
			if (FloorTile == nullptr)
				return;

			if (AFloorTile* FloorTileActor = Cast<AFloorTile>(FloorTile))
			{
				FloorTiles.Add(FloorTileActor);

				// 床タイルを床配置用の親コンポーネントにアタッチ
				FloorTileActor->AttachToComponent(FloorRootComp, FAttachmentTransformRules::KeepRelativeTransform);

				// 床タイルの位置を設定
				FVector TileLocation;
				TileLocation.X = j * ROOM_TILE_SIZE;
				TileLocation.Y = i * ROOM_TILE_SIZE;
				// Z = 0 に配置
				TileLocation.Z = 0.0f;
				FloorTileActor->SetActorRelativeLocation(TileLocation);
			}
		}
	}
}

// 壁の配置
void ARoomBase::SetupWalls()
{
	if (LayoutData == nullptr || LayoutData->WallClass == nullptr)
		return;

	// タイル幅のオフセット
	float SizeOffset = ROOM_TILE_THICKNESS * 0.5f + ROOM_TILE_SIZE * 0.5f;

	// 上壁から時計回りに生成
	for (int dir = 0; dir < 4; ++dir)
	{
		FVector TileLocation = FVector::ZeroVector;
		FRotator TileRotation = FRotator::ZeroRotator;
		float TileOffset = 0.f;

		// ループ回数
		bool bIsUDWall = (dir % 2 == 0);
		int WallTileWidth = bIsUDWall ? UDWallTileWidth : LRWallTileWidth;
		int WallTileHeight = bIsUDWall ? UDWallTileHeight : LRWallTileHeight;

		for (int i = 0; i < WallTileHeight; ++i)
		{
			for (int j = 0; j < WallTileWidth; ++j)
			{
				// 高さの位置を設定
				TileLocation.Z = i * ROOM_TILE_SIZE + SizeOffset;

				// 生成
				AActor* WallTile = GetWorld()->SpawnActor<AActor>(LayoutData->WallClass);
				if (AWallTile* WallTileActor = Cast<AWallTile>(WallTile))
				{
					// 管理配列に追加
					WallTiles.Add(WallTileActor);

					// 壁タイルを壁配置用の親コンポーネントにアタッチ
					WallTileActor->AttachToComponent(WallRootComp, FAttachmentTransformRules::KeepRelativeTransform);

					switch (dir)
					{
					// 上壁
					case 0:
						// 壁タイルの位置を設定
						TileLocation.X = j * ROOM_TILE_SIZE;
						TileLocation.Y = SizeOffset * -1.f;
						break;

					// 右壁
					case 1:
						TileOffset = (FloorTileWidth - 1) * ROOM_TILE_SIZE;

						// 壁タイルの位置を設定
						TileLocation.X = TileOffset + SizeOffset;
						TileLocation.Y = j * ROOM_TILE_SIZE;

						// 90度回転
						TileRotation = FRotator(0.f, 90.f, 0.f);
						break;

					// 下壁
					case 2:
						TileOffset = (FloorTileHeight - 1) * ROOM_TILE_SIZE;

						// 壁タイルの位置を設定
						TileLocation.X = j * ROOM_TILE_SIZE;
						TileLocation.Y = TileOffset + SizeOffset;

						// 180度回転
						TileRotation = FRotator(0.f, 180.f, 0.f);
						break;

					// 左壁
					case 3:
						// 壁タイルの位置を設定
						TileLocation.X = SizeOffset * -1.f;
						TileLocation.Y = j * ROOM_TILE_SIZE;

						// -90度回転
						TileRotation = FRotator(0.f, -90.f, 0.f);
						break;
					default:
						break;
					}
					
					// 配置・回転を反映
					WallTileActor->SetActorRelativeRotation(TileRotation);
					WallTileActor->SetActorRelativeLocation(TileLocation);
				}
			}
		}
	}
}

// 天井の配置
void ARoomBase::SetupRoof()
{
	if (LayoutData == nullptr || LayoutData->RoofClass == nullptr)
		return;

	// 天井の生成
	for (int i = 0; i < FloorTileHeight; ++i)
	{
		for (int j = 0; j < FloorTileWidth;++j)
		{
			AActor* RoofTile = GetWorld()->SpawnActor<AActor>(LayoutData->RoofClass);
			if (RoofTile == nullptr)
				return;

			if (ARoofTile* RoofTileActor = Cast<ARoofTile>(RoofTile))
			{
				RoofTiles.Add(RoofTileActor);

				// 天井タイルを天井配置用の親コンポーネントにアタッチ
				RoofTileActor->AttachToComponent(RoofRootComp, FAttachmentTransformRules::KeepRelativeTransform);

				// 天井タイルの位置を設定
				FVector TileLocation;
				TileLocation.X = j * ROOM_TILE_SIZE;
				TileLocation.Y = i * ROOM_TILE_SIZE;
				// RoomSize.Z + タイルの厚さの半分 に配置
				TileLocation.Z = LayoutData->RoomSize.Z + ROOM_TILE_THICKNESS * 0.5f;
				RoofTileActor->SetActorRelativeLocation(TileLocation);
			}
		}
	}
}

// 天井の真ん中から一つだけ下向きにライトを配置
void ARoomBase::SetupLights()
{
	// メインライトを配置
	SetupMainLight();

	// 補助ライトを配置
	SetupSubLights();

	// 演出ライトを配置
	SetupDecorationLight();
}

// メインライトを配置
void ARoomBase::SetupMainLight()
{
	if (LayoutData == nullptr || RoofRootComp == nullptr)
		return;

	// 中央位置を計算（タイルの中心）
	const float CenterX = (RoofTileWidth > 0) ? ((RoofTileWidth - 1) * 0.5f * ROOM_TILE_SIZE) : 0.f;
	const float CenterY = (RoofTileHeight > 0) ? ((RoofTileHeight - 1) * 0.5f * ROOM_TILE_SIZE) : 0.f;
	const float LightZ = LayoutData->RoomSize.Z + LayoutData->LightZOffset;

	FVector LightLocation(CenterX, CenterY, LightZ);

	// SpotLight を作成して天井から下向きに照らす
	UPointLightComponent* Spot = NewObject<UPointLightComponent>(this, UPointLightComponent::StaticClass());
	if (Spot == nullptr)
		return;

	// ルートコンポーネントにアタッチして登録
	Spot->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Spot->RegisterComponent();

	// 配置と回転を設定
	Spot->SetRelativeLocation(LightLocation);
	Spot->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

	// ライト設定
	Spot->SetIntensity(LayoutData->MainLightIntensity);
	Spot->SetLightColor(LayoutData->MainLightColor);
	Spot->SetAttenuationRadius(3000.f);
	//Spot->SetInnerConeAngle(20.0f);
	//Spot->SetOuterConeAngle(45.0f);

	Spot->bUseInverseSquaredFalloff = true;
	Spot->SetCastShadows(true);
}

// 補助ライトを配置
void ARoomBase::SetupSubLights()
{

}

// 演出ライトを配置
void ARoomBase::SetupDecorationLight()
{

}

// タイルの数を初期化
void ARoomBase::InitializeTileCounts()
{
	if (LayoutData == nullptr)
		return;

	FloorTileWidth = LayoutData->RoomSize.X / ROOM_TILE_SIZE;
	FloorTileHeight = LayoutData->RoomSize.Y / ROOM_TILE_SIZE;

	UDWallTileWidth = LayoutData->RoomSize.X / ROOM_TILE_SIZE;
	UDWallTileHeight = LayoutData->RoomSize.Z / ROOM_TILE_SIZE;
	LRWallTileWidth = LayoutData->RoomSize.Y / ROOM_TILE_SIZE;
	LRWallTileHeight = LayoutData->RoomSize.Z / ROOM_TILE_SIZE;

	RoofTileWidth = LayoutData->RoomSize.X / ROOM_TILE_SIZE;
	RoofTileHeight = LayoutData->RoomSize.Y / ROOM_TILE_SIZE;
}

// カメラを天井の左下（X=0, Y=Height-1）のすぐ下に配置する
inline void ARoomBase::SetupCamera()
{
	// プレイヤーコントローラーからカメラマネージャーを取得
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
		return;

	// プレイヤーコントローラーをキャスト
	AGodPlayerController* GodPC = Cast<AGodPlayerController>(PlayerController);
	if (GodPC == nullptr)
		return;

	// カメラマネージャーを取得
	UCameraManager* CameraManager = GodPC->GetCameraManager();
	if (CameraManager == nullptr)
		return;

	// カメラの生成
	RoomCamera = GetWorld()->SpawnActor<ARoomCamera>();
	if (RoomCamera == nullptr)
		return;

	if (LayoutData == nullptr)
		return;


	// カメラマネージャーに登録
	CameraManager->RegisterCamera(RoomCamera);

	// 指定するタイルの座標（部屋の左下）
	const int32 TargetX = 0;
	const int32 TargetY = FMath::Max(0, RoofTileHeight - 1);

	// RoofTiles 配列が行優先で格納されていると仮定：Index = X + Y * Width
	int32 Index = -1;
	if (RoofTileWidth > 0 && RoofTiles.Num() > 0)
	{
		Index = TargetX + TargetY * RoofTileWidth;
	}

	// カメラのワールド位置と回転を計算
	FVector CameraWorldLocation = FVector::ZeroVector;
	FRotator CameraWorldRotation = FRotator::ZeroRotator;

	// まずは指定の屋根タイルの下に配置を試みる
	if (RoofTiles.IsValidIndex(Index) && RoofTiles[Index] != nullptr)
	{
		// 屋根タイルのワールド位置を取得し、Z 方向に CameraDistanceBelowRoof 分下げる
		CameraWorldLocation = RoofTiles[Index]->GetActorLocation() - FVector(0.f, 0.f, ROOM_TILE_THICKNESS);
		RoomCamera->SetActorLocation(CameraWorldLocation);

		// 部屋の中心座標を計算
		float CenterX = (RoofTiles[RoofTiles.Num() - 1]->GetActorLocation().X - RoofTiles[0]->GetActorLocation().X) * 0.5f;
		float CenterY = (RoofTiles[RoofTiles.Num() - 1]->GetActorLocation().Y - RoofTiles[0]->GetActorLocation().Y) * 0.5f;
		float CenterZ = ROOM_TILE_THICKNESS * 0.5f + LayoutData->RoomSize.Z * 0.4f;
		FVector CenterLocation = FVector(CenterX, CenterY, CenterZ);

		// 視線は部屋中心に向ける
		CameraWorldRotation = (CenterLocation - RoomCamera->GetActorLocation()).Rotation();
		RoomCamera->SetActorRotation(CameraWorldRotation);
	}

	// FOV を設定
	if (auto* CameraComp = RoomCamera->GetCameraComponent())
	{
		CameraComp->SetFieldOfView(LayoutData->CameraFOV);
	}
}

