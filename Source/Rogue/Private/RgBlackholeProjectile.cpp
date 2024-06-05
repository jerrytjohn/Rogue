// Fill out your copyright notice in the Description page of Project Settings.


#include "RgBlackholeProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ARgBlackholeProjectile::ARgBlackholeProjectile()
{
	CollapseDelay = 3.0f;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	// Leaving this on applies small constant force via component 'tick' (Optional)
	RadialForceComponent->SetAutoActivate(true);
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->Radius = 1250.0f;
	RadialForceComponent->ForceStrength = -1500000.0f;

	//SphereComponent->OnComponentBeginOverlap
}

void ARgBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();
	//GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ARgTeleportationProjectile::Co, DetonateDelay);
	GetWorldTimerManager().SetTimer(TimerHandle_CollapseDelay, this, &ARgBlackholeProjectile::Explode, CollapseDelay);
}

void ARgBlackholeProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ARgBlackholeProjectile::Explode_Implementation()
{
	EffectComponent->DeactivateSystem();
	MoveComponent->StopMovementImmediately();
	Super::Explode_Implementation();
}

