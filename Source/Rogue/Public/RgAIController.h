// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RgAIController.generated.h"

class UBehaviorTree;

UCLASS()
class ROGUE_API ARgAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UBehaviorTree* BehaviorTree;
	virtual void BeginPlay() override;
};
