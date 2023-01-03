// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Enemy/Enemy.h"
#include "Spawner.generated.h"

UCLASS()
class THISISMYDUNGEON_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();
	
	virtual void Tick(float DeltaTime) override;
	
	void SpawnEnemy();
	void SpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere) 
		int spawnNumberEnemy;

	UPROPERTY(EditAnywhere) 
		int WavesNumber;

	UPROPERTY(EditAnywhere) 
		int numberOfSpawn;

	UPROPERTY(EditAnywhere) 
		int Actor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) 
		TArray<int> ArrayOfWaves;

	UPROPERTY(EditAnywhere, BlueprintReadOnly) 
		TArray<int> ArrayOfTimeWaves;


	UPROPERTY(EditAnywhere, Category = "Indicator")
		class UNiagaraComponent* NiagaraComp;

};
