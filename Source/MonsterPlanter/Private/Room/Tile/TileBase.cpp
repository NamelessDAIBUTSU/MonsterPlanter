#include "Room/Tile/TileBase.h"

ATileBase::ATileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// メッシュコンポーネントを作成してルートコンポーネントに設定
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComp;
}

void ATileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// マテリアルの設定
void ATileBase::SetTileMaterial(UMaterialInterface* Material)
{
	if (MeshComp && Material)
	{
		MeshComp->SetMaterial(0, Material);
	}
}

