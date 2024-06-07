// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RgAiCharacter.generated.h"

class URgAttributeComponent;
class ARgAIController;

UCLASS()
class ROGUE_API ARgAiCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARgAiCharacter();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URgAttributeComponent* AttributeComponent;

	UFUNCTION()
	void OnHealthChanged(URgAttributeComponent* OwningComponent, AActor* InstigatorActor, float NewHealth, float Delta, float HealthFraction);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
