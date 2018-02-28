// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ComponentPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAM312_GUIDED_API UComponentPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()


public:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

};
