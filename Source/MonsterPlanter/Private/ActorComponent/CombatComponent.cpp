// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/CombatComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// 攻撃処理
void UCombatComponent::Attack(AActor* DamagedActor, float Damage)
{
	if (DamagedActor == nullptr)
		return;

	if (AActor* Owner = GetOwner())
	{
		// 攻撃通知
		UGameplayStatics::ApplyDamage(DamagedActor, Damage, Owner->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());

		// ログ出力
		UE_LOG(LogTemp, Log, TEXT("%s attacked %s for %f damage."), *Owner->GetName(), *DamagedActor->GetName(), Damage);
	}
}

