// Fill out your copyright notice in the Description page of Project Settings.


#include "RgAiController.h"

#include "ChaosInterfaceWrapperCore.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ARgAiController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviourTree);

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if(MyPawn)
	{
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());
	}
	
}
