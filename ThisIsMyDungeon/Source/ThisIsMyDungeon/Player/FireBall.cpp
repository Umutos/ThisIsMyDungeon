// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBall.h"
#include "../DebugString.hpp"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "../Enemy/Enemy.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFireBall::AFireBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 600;
	ProjectileMovementComponent->MaxSpeed = 600;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bIsHomingProjectile = true;
	ProjectileMovementComponent->HomingAccelerationMagnitude = 1200;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();
	CurrentTime = TimeUntilDelete;
	//Getting Mesh.
	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	if (Components[0])
		Mesh = Components[0];
	else
		return;

	if (auto sphere = Mesh->GetChildComponent(0))
		SphereCollider = Cast<USphereComponent>(sphere);
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AFireBall::OnCollision);
}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyToFollow && !foundComponent)
	{
		foundComponent = true;
		ProjectileMovementComponent->HomingTargetComponent = EnemyToFollow->GetRootComponent();
	}

	if (CurrentTime > 0)
	{
		CurrentTime -= DeltaTime;
	}
	else
	{
		Destroy();
	}

}

void AFireBall::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->GetClass() != this->GetClass())
		Destroy();
	if (auto Enemy = Cast<AEnemy>(OtherActor))
	{
		int damage = BaseDamage;
		if (Enemy->GetClosestSocket(GetActorLocation()) == "head")
			damage *= 3;
		Enemy->NewWidgetAnim(GetActorLocation(), damage);
		Enemy->ApplyDamage(damage);
	}
}
