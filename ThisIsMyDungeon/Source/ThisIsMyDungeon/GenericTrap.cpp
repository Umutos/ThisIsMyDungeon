// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericTrap.h"
#include "Components/BoxComponent.h"
#include "DebugString.hpp"
#include "Player/PlayerCharacter.h"

// Sets default values
AGenericTrap::AGenericTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(GetRootComponent());

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);
}

// Called when the game starts or when spawned
void AGenericTrap::BeginPlay()
{
	Super::BeginPlay();

	

	DefaultMaterial = Mesh->GetMaterial(0);
	Mesh->SetMaterial(0, InvalidPreviewMaterial);
	Player = Cast<APlayerCharacter>(GEngine->GetFirstLocalPlayerController(GetWorld())->GetPawn());
	DescriptionText = "TODO: Add Description here";
}

// Called every frame
void AGenericTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Placed) {
		CanBePlacedCheck();
		if (CanBePlaced)
		{
			for (int i = 0; i < Mesh->GetMaterials().Num(); i++)
			{
				Mesh->SetMaterial(i, ValidPreviewMaterial);
			}
			
		}
		else
		{
			for (int i = 0; i < Mesh->GetMaterials().Num(); i++)
			{
				Mesh->SetMaterial(i, InvalidPreviewMaterial);
			}
		}
	}
}

FVector AGenericTrap::GetBoxColliderSize()
{
	return Collider->GetScaledBoxExtent();
}

void AGenericTrap::CanBePlacedCheck()
{
	CanBePlaced = !IsOverlappingSomeone() && Player->CurrentPower >= Cost;
	if (CanBePlaced && !CanBePlacedOnWalls)
	{
		CanBePlaced = GetActorUpVector().Z <= 1 && GetActorUpVector().Z >= 0.9f;
	}
}

void AGenericTrap::SetUp()
{
	Placed = true;
	//Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	Mesh->SetMaterial(0, DefaultMaterial);
}
