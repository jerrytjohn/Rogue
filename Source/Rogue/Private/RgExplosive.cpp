// Fill out your copyright notice in the Description page of Project Settings.


#include "RgExplosive.h"

#include "DrawDebugHelpers.h"
#include "Particles/ParticleEmitter.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ARgExplosive::ARgExplosive()
{
	bExploded = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetSimulatePhysics(true);
	RootComponent = Mesh;

	DestroyedMesh = CreateDefaultSubobject<UStaticMesh>("DestroyedMesh");
	
	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	// Leaving this on applies small constant force via component 'tick' (Optional)
	RadialForce->SetAutoActivate(false);
	RadialForce->SetupAttachment(RootComponent);
	RadialForce->Radius = 750.0f;
	RadialForce->ImpulseStrength = 2500.0f;
	RadialForce->bImpulseVelChange = true;	// Optional. Ignores mass. If false, the impulse strength will need to be very high (~20k) to even be noticed.
	RadialForce->AddCollisionChannelToAffect(ECC_WorldDynamic); // Optional, default constructor of component already adds 4 object types to affect, excluding WorldDynamic

	ExplosionVFX = CreateDefaultSubobject<UParticleSystemComponent>("ExplosionVFX");
	ExplosionVFX->SetupAttachment(RootComponent);
	ExplosionVFX->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void ARgExplosive::BeginPlay()
{
	Super::BeginPlay();
	
}


void ARgExplosive::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Mesh->OnComponentHit.AddDynamic(this, &ARgExplosive::OnActorHit);
}

void ARgExplosive::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void ARgExplosive::Explode()
{
	if(!bExploded)
	{
		RadialForce->FireImpulse();
		Mesh->SetStaticMesh(DestroyedMesh);
		Mesh->AddImpulse(FVector(0,0,1)*500,NAME_None ,true);
		Mesh->AddTorqueInRadians(FVector(1,1,0)*500,NAME_None ,true);
		ExplosionVFX->Activate();
		bExploded = true;
	}
	
}
