// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireBall.generated.h"

UCLASS()
class THISISMYDUNGEON_API AFireBall : public AActor
{
	GENERATED_BODY()

	float CurrentTime;

	
public:	
	// Sets default values for this actor's properties
	AFireBall();

	class AEnemy* EnemyToFollow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Collider")
		class USphereComponent* SphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeUntilDelete = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float BaseDamage = 5.f;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	bool foundComponent = false;
	

};
