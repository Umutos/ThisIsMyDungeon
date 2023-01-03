// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGameMode.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#define Debug(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugError(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugWarning(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(x), __VA_ARGS__));}


ADungeonGameMode::ADungeonGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ADungeonGameMode::BeginPlay()
{
	Super::BeginPlay();
	TSubclassOf<ASpawner> ClassToFind;
	ClassToFind = ASpawner::StaticClass();
	TArray<AActor*> TempSpawner;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TempSpawner);

	for (int i = 0; i <= TempSpawner.Num() - 1; i++)
	{
		Spawners.Add(Cast<ASpawner>(TempSpawner[i]));
	}

	int max = 0;

	for (ASpawner* spawner : Spawners)
	{
		for (auto wave : spawner->ArrayOfWaves)
		{
			max = wave > max ? wave : max;
		}
	}
	maxWaveCount = max;
}

void ADungeonGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//Debug("%d", counterEnemy);
	if (!endWave && counterEnemy <= 0)
	{
		endWave = true;
		for (int i = 0; i <= Spawners.Num() - 1; i++)
		{
			for (int j = 0; j <= Spawners[i]->ArrayOfWaves.Num() - 1; j++)
			{
				if (Spawners[i]->ArrayOfWaves[j] == currentWave+1)
				{
					Spawners[i]->NiagaraComp->SetVisibility(true);
				}
			}
		}
	}
}

void ADungeonGameMode::StartWaveGM()
{
	if(counterEnemy <= 0)
	{
		currentWave++;
		FTimerHandle MemberTimerHandle2;
		for (int i = 0; i <= Spawners.Num() - 1; i++)
		{
			for (int j = 0; j <= Spawners[i]->ArrayOfWaves.Num() - 1; j++)
			{
				//Debug("%d", Spawners[i]->ArrayOfWaves[j]);
				if(Spawners[i]->ArrayOfWaves[j] == currentWave)
				{
					Spawners[i]->NiagaraComp->SetVisibility(false);
					Spawners[i]->SpawnEnemy();
					endWave = false;
				}
			}
		}

		GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle2, [&]()
		{
			TimeWaveGM();
		}, 5, false);
	}
}

void ADungeonGameMode::TimeWaveGM()
{
	for (int i = 0; i <= Spawners.Num() - 1; i++)
	{
		for (int j = 0; j <= Spawners[i]->ArrayOfTimeWaves.Num() - 1; j++)
		{
			Debug("%d", Spawners[i]->ArrayOfWaves[j]);
			if(Spawners[i]->ArrayOfTimeWaves[j] == currentWave)
			{
				Spawners[i]->SpawnEnemy();
			}
		}
	}
}



