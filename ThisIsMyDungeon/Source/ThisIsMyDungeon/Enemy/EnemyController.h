// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class THISISMYDUNGEON_API AEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyController(const FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

	UPROPERTY(transient)
		class UBehaviorTreeComponent* BTC;

	UPROPERTY(transient)
		class UBlackboardComponent* BBC;
	//Blackbard Ids
	uint8 GoToLocationId;
	

	static AActor* treasure;
};

