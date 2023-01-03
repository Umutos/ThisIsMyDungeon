// Fill out your copyright notice in the Description page of Project Settings.


#include "TarPuddle.h"
#include "../DebugString.hpp"
#include "Components/BoxComponent.h"
#include "../Enemy/Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"

ATarPuddle::ATarPuddle()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	BoxCollider->SetupAttachment(Collider);
	BoxCollider->SetWorldLocation(GetActorLocation());
	Cost = 100;
}

void ATarPuddle::BeginPlay()
{
	Super::BeginPlay();
	Index = 2;
	this->DescriptionText = "Slow down heros and useful for traps to make more damage.";
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ATarPuddle::BeginOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ATarPuddle::EndOverlap);

	CanBePlacedOnWalls = false;
}

void ATarPuddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

 void ATarPuddle::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (Placed)
	{
		if (AEnemy* enemy = Cast<AEnemy>(OtherActor) )
		{
			UCharacterMovementComponent* MovementPtr = Cast<UCharacterMovementComponent>(enemy->GetMovementComponent());
			MovementPtr->MaxWalkSpeed = enemy->MaxSpeed /4;
		}
		
	}

}

void ATarPuddle::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Placed)
	{
		if (AEnemy* enemy = Cast<AEnemy>(OtherActor))
		{	
			UCharacterMovementComponent* MovementPtr = Cast<UCharacterMovementComponent>(enemy->GetMovementComponent());
			MovementPtr->MaxWalkSpeed = enemy->MaxSpeed;
		}
	}
}