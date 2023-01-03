// Fill out your copyright notice in the Description page of Project Settings.


#include "PileThrowerTrap.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../DebugString.hpp"
#include "Components/BoxComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "../Enemy/Enemy.h"



APileThrowerTrap::APileThrowerTrap()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	BoxCollider->SetupAttachment(Collider);
	BoxCollider->SetWorldLocation(GetActorLocation());
	
	Cost = 200;
}

void APileThrowerTrap::BeginPlay()
{
	Super::BeginPlay();
	Index = 4;
	this->DescriptionText = "Throw pile at your enemies for a large area of damage";

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &APileThrowerTrap::BeginOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &APileThrowerTrap::EndOverlap);

	NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(ArrowTrailEffect, Collider, NAME_None, FVector(0.f), GetActorRotation() - FRotator(90), EAttachLocation::Type::KeepRelativeOffset, true);
	
	NiagaraComp->SetVisibility(false);
	
	//if (NiagaraComp)
	//{
	
		//NiagaraComp->;
	//}	
}

void APileThrowerTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Placed)
	{

		if (!isFiring && !isReloading && enemiesToHurt.Num() != 0)
		{
			isFiring = true;
			FTimerHandle Handle;
			GetWorld()->GetTimerManager().SetTimer(Handle, this, &APileThrowerTrap::Reload, 4.2f);
			// This spawns the chosen effect on the owning WeaponMuzzle SceneComponent
			if (NiagaraComp)
			{
				NiagaraComp->SetVisibility(true);
				UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
				
			}
	
			//NiagaraComp->DestroyComponent()
		}
		if (isFiring && !isReloading)
		{
			if (enemiesToHurt.Num() != 0 && !isApplyingDMG)
			{
				AEnemy* toHurt = enemiesToHurt[0];
				ApplyDMG(toHurt);
				enemiesToHurt.Remove(toHurt);
				
			}
		}
	}
		
	/*if (isFiring)
	{
		Debug("Tir");
	}
	if (isReloading)
	{
		Debug("Recharge");
	}
	if (!isFiring && !isReloading)
	{
		//Debug("Nothing");
	}*/

}

void APileThrowerTrap::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (Placed)
	{
		if (AEnemy* enemy = Cast<AEnemy>(OtherActor))
		{
			enemies.Add(enemy);
			enemiesToHurt.Add(enemy);
			
		}

	}
	
}

void APileThrowerTrap::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Placed)
	{
		if (AEnemy* enemy = Cast<AEnemy>(OtherActor))
		{
			enemies.Remove(enemy);
		}

	}
}

void APileThrowerTrap::Reload()
{
	enemiesToHurt = enemies;
	isReloading = true;
	isFiring = false;
	if (NiagaraComp)
	{
		NiagaraComp->SetVisibility(false);
	}
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			isReloading = false;
		}, 4, false);

}

void APileThrowerTrap::ApplyDMG(AEnemy* enemyToInflictPain)
{
	if (enemies.Contains(enemyToInflictPain) && isFiring)
	{
		enemyToInflictPain->ApplyDamage(Damage);
		FTimerHandle Handle;
		FTimerDelegate DMGDelegate = FTimerDelegate::CreateUObject(this, &APileThrowerTrap::ApplyDMG, enemyToInflictPain);
		GetWorld()->GetTimerManager().SetTimer(Handle, DMGDelegate, 0.2f,false);
		
	}


}



