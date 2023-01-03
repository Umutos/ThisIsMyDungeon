// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxTrap.h"
#include "Components/StaticMeshComponent.h"
#include "../DebugString.hpp"

ABoxTrap::ABoxTrap()
{
	Cost = 200;
	CanBePlacedOnWalls = false;
}

void ABoxTrap::BeginPlay()
{
	Super::BeginPlay();
	Index = 1;
	this->DescriptionText = "Blocks and redirects heros paths and useful for forcing heros into traps.";
}

void ABoxTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
