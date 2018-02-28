// Fill out your copyright notice in the Description page of Project Settings.

/*
Parent class is the Pawn Movement Component Class, which has built
in functionality and features related to movement and physics.  So,
This class inclundes expanded functionality building off of the 
parent class.

included functions utilized:

ConsumeInputVector reports and clears the value of a built-in 
variable that we will use to store our movement inputs.

SafeMoveUpdatedComponent uses Unreal Engine physics to move 
our Pawn Movement Component while respecting solid barriers.

SlideAlongSurface handles the calculations and physics 
involved with sliding smoothly along collision surfaces like 
walls and ramps when a move results in a collision, rather 
than simply stopping in place and sticking to the wall or ramp.
*/
#include "ComponentPawnMovementComponent.h"

void UComponentPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure that everything is still valid, and that we are allowed to move.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Get (and then clear) the movement vector that we set in ACollidingPawn::Tick
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// If we bumped into something, try to slide along it
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
};

