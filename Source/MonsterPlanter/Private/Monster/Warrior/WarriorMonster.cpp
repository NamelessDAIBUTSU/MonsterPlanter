// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Warrior/WarriorMonster.h"
#include "Components/StaticMeshComponent.h"
#include <Player/Body/PlayerBody.h>
#include <Components/BoxComponent.h>

AWarriorMonster::AWarriorMonster()
{
	SpearMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpearMesh"));

	AttackCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision"));
	AttackCollision->SetupAttachment(SpearMesh);
}

void AWarriorMonster::OnConstruction(const FTransform& Transform)
{
	// スケルタルメッシュの手にアタッチ
	SpearMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("weapon"));

	
}

void AWarriorMonster::BeginPlay()
{
	Super::BeginPlay();

	if (AttackCollision)
	{
		// 生成初期はコリジョンの当たり判定を無効にする
		AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// オーバーラップイベント
		AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &AWarriorMonster::OnAttackCollisionOverlapBegin);
	}
}

void AWarriorMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWarriorMonster::SetAttackCollisionEnabled(bool bEnabled)
{
	if (AttackCollision)
	{
		ECollisionEnabled::Type CollisionType = bEnabled ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision;
		AttackCollision->SetCollisionEnabled(CollisionType);
	}
}

void AWarriorMonster::OnAttackCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// プレイヤーにダメージを与える
	APlayerBody* Player = Cast<APlayerBody>(OtherActor);
	if (Player == nullptr)
		return;

	// 無敵時間中であれば無視する
	if (Player->GetInvincibleEndTime() >= GetWorld()->GetTimeSeconds())
	{
		UE_LOG(LogTemp, Warning, TEXT("WarriorMonster: Just Dodge!!"));

		return;
	}

	// Log出力
	UE_LOG(LogTemp, Warning, TEXT("WarriorMonster: Player hit!"));
	//Player->TakeDamage(AttackDamage, FDamageEvent(), nullptr, this);
}
