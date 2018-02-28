// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class GAM312_GUIDED_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UFUNCTION()
		void OnSeePlayer(APawn* Pawn);

public:
	// Sets default values for this character's properties
	AAICharacter();

	//Behavior Tree of this character
	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;
	//Senses  of this character
	UPROPERTY(VisibleAnywhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
