// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GenericTrap.h"
#include "BoxTrap.generated.h"

UCLASS()
class THISISMYDUNGEON_API ABoxTrap : public AGenericTrap
{
	GENERATED_BODY()
public:
	ABoxTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
