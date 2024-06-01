// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RgInteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URgInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ROGUE_API IRgInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)			// Blueprint Native allows us to use C++ functions in BP
	void Interact(APawn* InstigatorPawn);
};
