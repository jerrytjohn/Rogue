// Fill out your copyright notice in the Description page of Project Settings.


#include "RgInteractionComponent.h"

#include "DrawDebugHelpers.h"
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
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);	// list of all the object types that you want to query

	AActor* MyOwner = GetOwner();
	
	FVector End;
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	float RayCastRange = 250.0f;			// Query Distance in front of eyes in centimeters
	End = EyeLocation+ (EyeRotation.Vector()*RayCastRange);					

	FHitResult HitResult;
	bool bHitSomething = GetWorld()->LineTraceSingleByObjectType(HitResult, EyeLocation, End, ObjectQueryParams);

	AActor* HitActor = HitResult.GetActor();

	if(HitActor)	// Avoiding a null pointer
	{
		if (HitActor->Implements<URgInteractableInterface>())		// The only place where the syntax expects UInterface instead of Interface 
		{
			APawn* MyPawn = Cast<APawn>(MyOwner); 
			IRgInteractableInterface::Execute_Interact(HitActor, MyPawn);
		}
	}
	/*
	// Debug to see the cast
	FColor SightLineColor = bHitSomething? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), EyeLocation, End, SightLineColor,false, 2.0f, 2.0f);
	*/

}

