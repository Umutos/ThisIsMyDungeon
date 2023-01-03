// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../DebugString.hpp"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AActor* AEnemyController::treasure = nullptr;

AEnemyController::AEnemyController(const FObjectInitializer& ObjectInitializer)
{
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard Component"));
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AEnemy* Chr = Cast<AEnemy>(InPawn);
	if (Chr != nullptr && Chr->TreeAsset != nullptr)
	{
		BBC->InitializeBlackboard(*Chr->TreeAsset->BlackboardAsset);
		GoToLocationId = BBC->GetKeyID("GoToLocation");
		BTC->StartTree(*Chr->TreeAsset);
	}

	if (!treasure)
	{
		TArray<AActor*> treasures;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Treasure"), treasures);
		if (treasures.Num() > 0)
		{
			treasure = treasures[0];
			BBC->SetValueAsVector("GoToLocation", treasures[0]->GetActorLocation());
		}
	}
	else
	{
		BBC->SetValueAsVector("GoToLocation", treasure->GetActorLocation());
	}
	
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	treasure = nullptr;

}