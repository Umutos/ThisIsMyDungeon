// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericTrap.generated.h"

UCLASS()
class THISISMYDUNGEON_API AGenericTrap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGenericTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetBoxColliderSize();

	class APlayerCharacter* Player;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Material")
		UMaterialInterface* ValidPreviewMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Material")
		UMaterialInterface* InvalidPreviewMaterial;

	UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider")
		class UBoxComponent* Collider;

	UPROPERTY(EditAnywhere, Category = "Trap")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Description")
		FString DescriptionText;

	UFUNCTION(BlueprintImplementableEvent)
		bool IsOverlappingSomeone();

	void CanBePlacedCheck();

	void SetUp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Index")
		int Index = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cost")
		int Cost = 100;

	bool Placed = false;
	bool CanBePlaced = false;
	bool CanBePlacedOnWalls = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Size")
		FVector size;
};
