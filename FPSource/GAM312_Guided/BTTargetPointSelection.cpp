// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTargetPointSelection.h"
#include "BotTargetPoint.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"



EBTNodeResult::Type UBTTargetPointSelection::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());

	if (AICon)
	{
		//from blackboard component look from next location relative from current location
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		ABotTargetPoint* CurrentPoint = Cast<ABotTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailableTargetPoints = AICon->GetAvailableTargetPoints();

		//random point from array of move to locations
		int32 RandomIndex;

		//retrieved point
		ABotTargetPoint* NextTargetPoint = nullptr;

		//ensures random point is not current point
		do
		{
			RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num() - 1);
			//Remember that the Array provided by the Controller function contains AActor* objects so we need to cast.
			NextTargetPoint = Cast<ABotTargetPoint>(AvailableTargetPoints[RandomIndex]);
		} while (CurrentPoint == NextTargetPoint);

		//update blackboard
		BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);

		//behavior and blackboard update completed, return to sequence/loop
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}