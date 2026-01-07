#include "Room/RoomManager.h"
#include "Room/RoomBase.h"
#include "Room/RoomClassInfoList.h"

URoomManager::URoomManager()
{
	// 生成する部屋クラス情報をを取得
	static ConstructorHelpers::FObjectFinder<URoomClassInfoList> RoomClassListObject(
		TEXT("/Game/MonsterPlanter/Room/DA_RoomClassInfoList.DA_RoomClassInfoList")
	);

	// 生成可能な部屋クラス情報をマップに保存
	if (RoomClassListObject.Succeeded())
	{
		URoomClassInfoList* RoomClassInfoList = RoomClassListObject.Object;
		if (RoomClassInfoList)
		{
			for (const FRoomClassInfo& ClassInfo : RoomClassInfoList->RoomClassInfoList)
			{
				RoomClassMap.Add(ClassInfo.RoomType, ClassInfo.RoomClass);
			}
		}
	}
}

void URoomManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void URoomManager::CreateDefaultRooms()
{
	// 魔王部屋を作成
	CreateRoom(ERoomType::Devil);

	// 農場部屋を作成
	CreateRoom(ERoomType::Farm);

	// 初期部屋を作成
	CreateRoom(ERoomType::Standard);
}

// 部屋の生成
void URoomManager::CreateRoom(ERoomType RoomType)
{
	if (TSubclassOf<ARoomBase>* Found = RoomClassMap.Find(RoomType))
	{
		// 現在の部屋数から、次の配置開始位置を計算
		int32 NextRoomNum = Rooms.Num() + 1;
		FVector StartLocation = FVector::ZeroVector;
		StartLocation.X = (MAX_ROOM_SIZE + ROOM_TILE_THICKNESS * 0.5f) * NextRoomNum;

		// 生成
		ARoomBase* NewRoom = GetWorld()->SpawnActor<ARoomBase>(*Found, StartLocation, FRotator::ZeroRotator);

		// 管理コンテナに追加
		AddRoom(NewRoom);
	}
}

// 部屋の追加
void URoomManager::AddRoom(ARoomBase* NewRoom)
{
	if (NewRoom == nullptr)
		return;

	Rooms.Add(NewRoom);
}

// グリッド線の表示切替
void URoomManager::ToggleVisibleGrid()
{
	for (ARoomBase* Room : Rooms)
	{
		if (IsValid(Room))
		{
			Room->ToggleVisibleGrid();
		}
	}
}