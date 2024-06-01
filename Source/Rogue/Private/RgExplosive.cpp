// Fill out your copyright notice in the Description page of Project Settings.


#include "RgExplosive.h"

#include "DrawDebugHelpers.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ARgExplosive::ARgExplosive()
{
	bExploded = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetSimulatePhysics(true);
	//RootComponent = Mesh;

	DestroyedMesh = CreateDefaultSubobject<UStaticMesh>("DestroyedMesh");
	
	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	// Leaving this on applies small constant force via component 'tick' (Optional)
	RadialForce->SetAutoActivate(false);
	//RadialForce->SetupAttachment(Mesh);
	RadialForce->Radius = 750.0f;
	RadialForce->ImpulseStrength = 2500.0f;
	RadialForce->bImpulseVelChange = true;	// Optional. Ignores mass. If false, the impulse strength will need to be very high (~20k) to even be noticed.
	RadialForce->AddCollisionChannelToAffect(ECC_WorldDynamic); // Optional, default constructor of component already adds 4 object types to affect, excluding WorldDynamic

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

	// Debug stuff
	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Barrel"));

	// %s = string
	// %f = float
	// logs: "OtherActor: MyActor_1, at gametime: 124.4" 
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
}

void ARgExplosive::Explode()
{
	if(!bExploded)
	{
		RadialForce->FireImpulse();
		Mesh->SetStaticMesh(DestroyedMesh);
		bExploded = true;
	}
	
}
