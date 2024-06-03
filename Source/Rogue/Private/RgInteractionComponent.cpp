// Fill out your copyright notice in the Description page of Project Settings.


#include "RgInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "RgCharacter.h"
#include "RgInteractableInterface.h"

// Sets default values for this component's properties
URgInteractionComponent::URgInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void URgInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URgInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URgInteractionComponent::PrimaryInteract()
{
	ARgCharacter* MyOwnerCharacter = Cast<ARgCharacter>(GetOwner());
	
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwnerCharacter->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FCollisionShape Shape;
	Shape.SetSphere(50.0f);

	//Ignore the player
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(MyOwnerCharacter);

	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectParams.AddObjectTypesToQuery(ECC_Pawn);

	float RayCastRange = 250.0f;			// Query Distance in front of eyes in centimeters
	FVector TraceEnd = EyeLocation+ (EyeRotation.Vector()*RayCastRange);		

	FHitResult HitData;
	bool bHitSomething = GetWorld()->SweepSingleByObjectType(HitData, EyeLocation, TraceEnd, FQuat::Identity, ObjectParams, Shape, CollisionParams);
	AActor* HitActor = HitData.GetActor();


	if(HitActor)	// Avoiding a null pointer
	{
		if (HitActor->Implements<URgInteractableInterface>())		// The only place where the syntax expects UInterface instead of Interface 
		{
			APawn* MyPawn = Cast<APawn>(GetOwner());
			IRgInteractableInterface::Execute_Interact(HitActor, MyPawn);
			
			MyOwnerCharacter->PlayAnimMontage(InteractAnim);

			// Debug visualizers
			TraceEnd = HitData.ImpactPoint;
			DrawDebugSphere(GetWorld(),TraceEnd, 50.0f, 12, FColor::Yellow, false, 2.0f);
			FColor SightLineColor = bHitSomething? FColor::Green : FColor::Red;
			DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, SightLineColor,false, 2.0f, 2.0f);
		}
	}

}

