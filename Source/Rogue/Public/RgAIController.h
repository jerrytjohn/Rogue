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

	UPROPERTY(EditAnywhere, Category="Animations")
	UAnimMontage* AttackAnim;

public:
	UAnimMontage* GetAttackAnim() const
	{
		return AttackAnim;
	}

protected:
	virtual void BeginPlay() override;
	
};
