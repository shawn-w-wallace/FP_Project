// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAM312_GUIDED_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
	//Behavior tree component reference
	UBehaviorTreeComponent* BehaviorComp;
	//Blackboard component reference
	UBlackboardComponent* BlackboardComp;

	//Blackboard keys
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName LocationToGoKey; //patrol movemnt, ie (AI) go from your current location to array location
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName PlayerSpottedKey; //target is player, used in AI "Senses" ie AI "sees" player, will break current 
	                  //logic and start new logic to follow target (Player)

	
	//Blueprint instances of BotTargetPoints stored in array for refrence of AI "Random" movements
	TArray<AActor*> BotTargetPoints;

public:

	//Game starts, pawn blackboard and logic behavior starts
	virtual void Possess(APawn* Pawn) override;
	
	//Player spotted by AI, set blackboard
	void SetSeenTarget(APawn* Pawn);

public:

	AMyAIController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() { return BotTargetPoints; }
	
};
