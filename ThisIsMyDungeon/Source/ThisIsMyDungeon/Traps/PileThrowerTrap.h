// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GenericTrap.h"
#include "PileThrowerTrap.generated.h"

/**
 * 
 */
UCLASS()
class THISISMYDUNGEON_API APileThrowerTrap : public AGenericTrap
{
	GENERATED_BODY()
public:
	APileThrowerTrap();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "State")
		bool isReloading;

	UPROPERTY(EditAnywhere, Category = "State")
		bool isFiring;

	UPROPERTY(EditAnywhere, Category = "State")
		bool isApplyingDMG;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void Reload();

	UFUNCTION()
		void ApplyDMG(class AEnemy* enemyToInflictPain);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyList")
		TArray<class AEnemy*> enemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyList")
		TArray<class AEnemy*> enemiesToHurt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider")
		class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, Category = "Firing")
		class UNiagaraSystem* ArrowTrailEffect;
	
	UPROPERTY(EditAnywhere, Category = "Firing")
		class UNiagaraComponent* NiagaraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		class USoundBase* Sound;

	UPROPERTY(EditAnywhere, Category = "Damage")
		float Damage = 2;

};
