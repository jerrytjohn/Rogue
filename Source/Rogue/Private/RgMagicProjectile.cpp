// Fill out your copyright notice in the Description page of Project Settings.


#include "RgMagicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ARgMagicProjectile::ARgMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionProfileName("Projectile");
	RootComponent = SphereComponent;

	ParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>("ParticleEffect");
	ParticleEffect->SetupAttachment(SphereComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMover");
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;

}
 
// Called when the game starts or when spawned
void ARgMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARgMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

