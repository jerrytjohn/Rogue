// Fill out your copyright notice in the Description page of Project Settings.


#include "RgAiCharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "RgAttributeComponent.h"

// Sets default values
ARgAiCharacter::ARgAiCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttributeComponent = CreateDefaultSubobject<URgAttributeComponent>("AttributeComponent");

}

void ARgAiCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComponent->OnHealthChanged.AddDynamic(this, &ARgAiCharacter::OnHealthChanged);
}

// Called when the game starts or when spawned
void ARgAiCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ARgAiCharacter::OnHealthChanged(URgAttributeComponent* OwningComponent, AActor* InstigatorActor, float NewHealth,
	float Delta, float HealthFraction)
{
	// Check if dead
	if(NewHealth <= 0.0f)
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		if(AIController)
		{
			// Disable controller
			AIController->GetBrainComponent()->StopLogic("Killed");
			
		}

		// Ragdoll
		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName("Ragdoll");
		// Set life spam
		SetLifeSpan(6.0f);
	}

	
}

// Called every frame
void ARgAiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


