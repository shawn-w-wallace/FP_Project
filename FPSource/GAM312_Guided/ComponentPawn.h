// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ComponentPawn.generated.h"

UCLASS()
class GAM312_GUIDED_API AComponentPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AComponentPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//custom movement component variable
	class UComponentPawnMovementComponent* OurMovementComponent;

	//function returns the custom movement component
	virtual UPawnMovementComponent* GetMovementComponent() const override;
	
	//movement functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
};
