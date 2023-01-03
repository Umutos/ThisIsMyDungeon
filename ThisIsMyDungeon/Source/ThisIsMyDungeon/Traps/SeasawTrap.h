// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GenericTrap.h"
#include "SeasawTrap.generated.h"

/**
 * 
 */
UCLASS()
class THISISMYDUNGEON_API ASeasawTrap : public AGenericTrap
{
	GENERATED_BODY()
public:
	ASeasawTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Trap")
		class UStaticMeshComponent* seasawMeshComp;

	/*UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);*/

	UFUNCTION()
	void OnSeasawColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider")
		class UBoxComponent* seasawColComp;

};
