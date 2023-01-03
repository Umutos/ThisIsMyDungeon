// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class THISISMYDUNGEON_API APlayerCharacter : public ACharacter
{
private:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
		FVector TreasureLoc;

	UPROPERTY(EditAnywhere)
		TArray<FVector> SpawnLoc;

	UPROPERTY(EditAnywhere)
		FVector PlayerSpawn;

	UPROPERTY(EditAnywhere)
		class AGenericTrap* lastTrap;

	class AEnemy* PreviousEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	class UStaticMeshComponent* ProjectileStart;

	FTransform SpawnTransform;
	
	FTransform MeshRelativeTransform;

	bool RaycastFromCamera(FHitResult* RV_Hit, float MaxDistance = 1000.f, ECollisionChannel collisionType = ECollisionChannel::ECC_WorldStatic);

	bool TrapHidden = false;

	bool isFiring = false;

	bool isPressed = false;

	bool IsInAnimation = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool isDead = false;

	void OnShootButtonPressed() { if (!isAttacking) { isFiring = true; } }
	void OnShootButtonReleased() { isFiring = false; }

	void OnSwingButtonPressed() { if (inputsEnable) { isAttacking = true; isPressed = true;} }
	void OnSwingButtonReleased();

	FHitResult hit;

	float _currentTime = 0;

	float _currentFireBallCooldown;

	bool inputsEnable = false;
protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void OnJump();

	void OnStopJump();

	void OnShoot();


	void ResetRotation();

	void OnTrapSetUp();

	void OnCancelTrap();

	UFUNCTION(BlueprintCallable)
	void ApplyPlayerDamage(int Damage);

	void DisableTrap(bool);

	void Respawn();

	void OnTrap1();
	void OnTrap2();
	void OnTrap3();
	void OnTrap4();

	void SelectTrap(int index);

	void CheckPath();

	void StartWave();

	void EnablePlayerInputs();

	void RotatePlus();
	void RotateMinus();

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver();

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	APlayerCharacter();


	virtual void Tick(float DeltaTime) override;

	void AddPower(int add);



	UFUNCTION(BlueprintImplementableEvent)
		void ShowPressButton(bool value);

	UFUNCTION(BlueprintImplementableEvent)
		void ShowVictory(bool value);

	UFUNCTION(BlueprintCallable)
		int GetCurrentTrapIndex();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	// Life
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Life)
		int MaxLife = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Life)
		int CurrentLife = 0;

	// Power
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Power)
		int CurrentPower = 0;

	UPROPERTY(EditAnywhere, Category = Power)
		int StartingPower = 800;

	bool InterRound = true;

	UPROPERTY(EditAnywhere)
		float FireBallCooldown = 0.3f;

	FRotator TrapRotation = FRotator::ZeroRotator;

	// Projectiles
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class AFireBall> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
		class AGenericTrap* CurrentTrap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trap")
		TArray<TSubclassOf<class AGenericTrap>> TrapsBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
		UAnimMontage* ShootAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
		UAnimMontage* DeathAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
		UAnimMontage* VictoryAnimation;

	// Projectiles

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider")
		class UBoxComponent* HammerBoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isAttacking = false;
};
