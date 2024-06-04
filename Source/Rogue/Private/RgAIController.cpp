// Fill out your copyright notice in the Description page of Project Settings.


#include "RgAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


void ARgAIController::BeginPlay()
{
	Super::BeginPlay();

	if(ensure(BehaviorTree))
	{
		RunBehaviorTree(BehaviorTree);
	}

	APawn* MyPlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if(MyPlayerPawn)
	{
		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPlayerPawn);
	}
	
}
