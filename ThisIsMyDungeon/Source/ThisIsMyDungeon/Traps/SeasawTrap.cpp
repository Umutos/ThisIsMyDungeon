// Fill out your copyright notice in the Description page of Project Settings.


#include "SeasawTrap.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "../Enemy/Enemy.h"
#include "../DebugString.hpp"

ASeasawTrap::ASeasawTrap()
{
	seasawMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Seasaw Mesh"));
	seasawMeshComp->SetupAttachment(Mesh);

	seasawColComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Seasaw Collider"));
	seasawColComp->SetupAttachment(seasawMeshComp);
	seasawColComp->SetHiddenInGame(false);
	seasawColComp->OnComponentBeginOverlap.AddDynamic(this, &ASeasawTrap::OnSeasawColliderBeginOverlap);
	Cost = 500;
}

void ASeasawTrap::BeginPlay()
{
	Super::BeginPlay();
	Index = 3;
	this->DescriptionText = "Deal a lot of damage to heroes who walk on them";
}

void ASeasawTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Placed) {
		CanBePlacedCheck();
		if (CanBePlaced)
		{
			seasawMeshComp->SetMaterial(0, ValidPreviewMaterial);
		}
		else
		{
			seasawMeshComp->SetMaterial(0, InvalidPreviewMaterial);
		}
	}

	seasawMeshComp->AddRelativeRotation(FQuat::MakeFromEuler(FVector(0, 720.f * DeltaTime, 0)));
	seasawMeshComp->SetRelativeLocation(FVector(sinf(GetWorld()->GetTimeSeconds() * 2.f) * 125.f, 0, 0));
}

//void ASeasawTrap::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
//{
//	Debug("begin overlap");
//	if (Placed)
//	{
//		if (AEnemy* enemy = Cast<AEnemy>(OtherActor))
//		{
//			enemy->ApplyDamage(500);
//		}
//	}
//}

void ASeasawTrap::OnSeasawColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (Placed)
	{
		if (AEnemy* enemy = Cast<AEnemy>(OtherActor))
		{
			enemy->ApplyDamage(50);
		}
	}
}

