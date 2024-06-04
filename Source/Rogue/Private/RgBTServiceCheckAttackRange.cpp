// Fill out your copyright notice in the Description page of Project Settings.


#include "RgBTServiceCheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void URgBTServiceCheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent=  OwnerComp.GetBlackboardComponent();

	if(ensure(BlackboardComponent))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));

		if(TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if(ensure(MyController))
			{
				APawn* AIPawn = MyController->GetPawn();
				if(ensure(AIPawn))
				{
					float SqrDistance = FVector::DistSquared(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					bool bWithinRange = SqrDistance < (1000*1000);
					
					bool bInSight = false;
					if(bWithinRange)
					{
						bInSight = MyController->LineOfSightTo(TargetActor);
					}
					BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinRange&&bInSight));
					
				}
			}
		}
	}
}
