// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RgAiController.generated.h"

class UBehaviorTree;

UCLASS()
class ROGUE_API ARgAiController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviourTree;
	virtual void BeginPlay() override;
	
};
