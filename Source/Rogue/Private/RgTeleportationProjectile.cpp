// Fill out your copyright notice in the Description page of Project Settings.


#include "RgTeleportationProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ARgTeleportationProjectile::ARgTeleportationProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MoveComponent->InitialSpeed = 9999.0f;
}

void ARgTeleportationProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ARgTeleportationProjectile::Explode, DetonateDelay);
}



void ARgTeleportationProjectile::Explode_Implementation()
{
	// Clear timer if the Explode() was already called through another source like OnActorHit
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComponent->DeactivateSystem();
	MoveComponent->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ARgTeleportationProjectile::TeleportInstigator, TeleportDelay);
	
}

void ARgTeleportationProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();

	if(ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
}