// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "ThisIsMyDungeon/DungeonGameMode.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "../DebugString.hpp"
#include "../Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<APlayerCharacter>(GEngine->GetFirstLocalPlayerController(GetWorld())->GetPawn());
	Player->ShowPressButton(false);
	Player->InterRound = false;
	MaxSpeed = this->GetCharacterMovement()->MaxWalkSpeed;
	ADungeonGameMode* GM = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(this));
	if (GM)
		MaxHealth = 25 * GM->currentWave + 100;
	Health = MaxHealth;
}

void AEnemy::Destroyed()
{
	ADungeonGameMode* GM = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->counterEnemy--;
		if (GM->counterEnemy <= 0)
		{
			if (Player) {
				Player->InterRound = true;
				Player->ShowPressButton(true);
			}
		}
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UNavigationSystemV1::TestPathSync()
	if (HideLifeBarCooldown > 0)
	{
		HideLifeBarCooldown -= DeltaTime;
	}
	else if (HideLifeBarCooldown > -1 && HideLifeBarCooldown <= 0)
	{
		HideLifeBarCooldown = -1;
		this->ShowLifeBar(false);
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::ApplyDamage(int Damage)
{
	Health -= Damage;
	this->ShowLifeBar(true);
	HideLifeBarCooldown = 2.f;
	if (Health <= 0)
	{
		Player->AddPower(100);
		Destroy();
	}
}

FName AEnemy::GetClosestSocket(FVector pos)
{
	float distance = FLT_MAX;
	FName currentSkel;
	for (auto skelName : GetMesh()->GetAllSocketNames())
	{
		auto skel = GetMesh()->GetSocketLocation(skelName);
		float currentDistance = FVector::Distance(pos, skel);
		if (distance > currentDistance)
		{
			distance = currentDistance;
			currentSkel = skelName;
		}
	}
	return currentSkel;
}

