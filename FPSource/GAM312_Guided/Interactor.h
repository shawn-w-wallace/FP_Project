// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Interactor.generated.h"

UCLASS()
class GAM312_GUIDED_API AInteractor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractor();

	//function called when player presses interact button, 'F'
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller) override;
	//player looks at interactable object and object gets outline
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void StartFocus();
	virtual void StartFocus_Implementation() override;
	//player looks away from interactable object and outline goes away
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void EndFocus();
	virtual void EndFocus_Implementation() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//
	TArray<UMeshComponent*> Meshes;
};
