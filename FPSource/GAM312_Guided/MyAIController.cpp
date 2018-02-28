// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIController.h"
#include "AICharacter.h"
#include "BotTargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"


AMyAIController::AMyAIController()
{
	//Initialize BehaviorTreeComponent, BlackboardComponent and corresponding keys
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	LocationToGoKey = "LocationToGo";
	PlayerSpottedKey = "Target";
}

void AMyAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	//Get the possessed Character and check if it's my own AI Character
	AAICharacter* AIChar = Cast<AAICharacter>(Pawn);

	if (AIChar)
	{
		//If the blackboard is valid initialize the blackboard for the corresponding behavior tree
		if (AIChar->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AIChar->BehaviorTree->BlackboardAsset));
		}
		
		//***NOT MY NOTE*** Helps me understand what is going on and why in terms of AI 
		//location retrieval and array access
		/*Populate the array of available bot target points
		The following function needs a TArray of AActors, that's why I declared the
		BotTargetPoints as such. When I will need to get an exact point and compare it,
		I will cast it to the corresponding class (ABotTargetPoint)*/
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABotTargetPoint::StaticClass(), BotTargetPoints);

		//Start the behavior tree which corresponds to the specific character
		BehaviorComp->StartTree(*AIChar->BehaviorTree);
	}
}

void AMyAIController::SetSeenTarget(APawn* Pawn)
{
	//Pawn sees player
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerSpottedKey, Pawn);
	}
}