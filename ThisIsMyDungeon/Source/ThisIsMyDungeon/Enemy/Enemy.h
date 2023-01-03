// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"


UCLASS()
class THISISMYDUNGEON_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Destroyed() override;
	
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "AI")
		class UBehaviorTree* TreeAsset;

	class UWidgetComponent* widgetComp = nullptr;

	class APlayerCharacter* Player;

	UPROPERTY(EditAnywhere)
		FVector TreasureLoc;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Life")
		int MaxHealth = 100;

	UPROPERTY(BlueprintReadonly);
		int Health = 0;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Damage")
		int damageToTreasure = 5;

	UFUNCTION(BlueprintImplementableEvent)
		void ShowLifeBar(bool value);

	float MaxSpeed;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(int Damage);

	FName GetClosestSocket(FVector pos);

	UFUNCTION(BlueprintImplementableEvent)
	void NewWidgetAnim(FVector pos, int Damage);

	UPROPERTY(BlueprintReadonly);
	float HideLifeBarCooldown = 0;
};
