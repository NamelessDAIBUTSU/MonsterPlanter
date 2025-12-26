// Fill out your copyright notice in the Description page of Project Settings.

#include "FarmSlot/FarmSlotBase.h"

AFarmSlotBase::AFarmSlotBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// メッシュの生成
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);

	// Cubeメッシュを割り当て
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(
		TEXT("/Engine/BasicShapes/Cube.Cube")
	);
	if (CubeMesh.Succeeded())
	{
		MeshComp->SetStaticMesh(CubeMesh.Object);
		MeshComp->SetCastShadow(false);
	}

	//
	//// コリジョンの生成
	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	//if (BoxCollision)
	//{
	//	BoxCollision->SetupAttachment(RootComponent);
	//}
}

void AFarmSlotBase::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AFarmSlotBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//if (BoxCollision)
	//{
	//	// コリジョンの当たり判定設定
	//	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//	BoxCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	//	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	//	// コリジョンサイズ設定
	//	BoxCollision->SetBoxExtent(FVector(100.f, 50.f, 100.f));
	//	// コリジョンの位置をX軸方向に移動
	//	BoxCollision->SetRelativeLocation(FVector(250.f, 0.f, 100.f));
	//}
}

void AFarmSlotBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

