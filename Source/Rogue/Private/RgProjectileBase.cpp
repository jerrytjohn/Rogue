// Fill out your copyright notice in the Description page of Project Settings.


#include "RgProjectileBase.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ARgProjectileBase::ARgProjectileBase()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionProfileName("Projectile");
	SphereComponent->OnComponentHit.AddDynamic(this, &ARgProjectileBase::OnActorHit);
	RootComponent = SphereComponent;

	EffectComponent = CreateDefaultSubobject<UParticleSystemComponent>("EffectComponent");
	EffectComponent->SetupAttachment(RootComponent);

	MoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MoveComponent->bRotationFollowsVelocity = true;
	MoveComponent->bInitialVelocityInLocalSpace = true;
	MoveComponent->ProjectileGravityScale = 0.0f;
	MoveComponent->InitialSpeed = 7777;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ARgProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}


void ARgProjectileBase::Explode_Implementation()
{
	if(ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

		Destroy();
	}
}

void ARgProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}




