// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PickUp.generated.h"

UCLASS()
class GAM312_GUIDED_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Root component for pick up item
	UPROPERTY(EditAnywhere)
		USceneComponent* PickUpItemRoot;
	//collision volume
	UPROPERTY(EditAnywhere)
		UBoxComponent* PickUpItemBox;
	//pick up item mesh
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PickUpItem;
	//function for collision
	UFUNCTION()
		void OnPlayerEnterPickUpItemBox(UPrimitiveComponent* OverlappedCom, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
