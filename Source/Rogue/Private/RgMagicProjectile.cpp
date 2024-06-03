// Fill out your copyright notice in the Description page of Project Settings.


#include "RgMagicProjectile.h"

#include "RgAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ARgMagicProjectile::ARgMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionProfileName("Projectile");
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARgMagicProjectile::OnActorOverlap);
	//SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
	RootComponent = SphereComponent;

	ParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>("ParticleEffect");
	ParticleEffect->SetupAttachment(SphereComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMover");
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->Radius = 300.0f;
	RadialForceComponent->ImpulseStrength = 400.0f;
	RadialForceComponent->SetAutoActivate(false);		// Disabling the slight constant radial force on surrounding objects
	RadialForceComponent->AddCollisionChannelToAffect(ECC_WorldDynamic); 
	RadialForceComponent->SetupAttachment(SphereComponent);
	RadialForceComponent->bImpulseVelChange = true;		// You need ridiculously high force values if this is false

}
 
// Called when the game starts or when spawned
void ARgMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARgMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)	// Don't call functions on null pointers
	{
		URgAttributeComponent* AttributeComponent = Cast<URgAttributeComponent>(OtherActor->GetComponentByClass(URgAttributeComponent::StaticClass()));
		if(AttributeComponent)		// We could have hit a wall or something that doesn't have attributes like health. Make sure this s not null
		{
			AttributeComponent->ApplyHealthChange(-20.0f);		// Clean up and assign to a variable later
			Destroy();
		}
	}
}

// Called every frame
void ARgMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

