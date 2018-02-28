// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

UCLASS()
class GAM312_GUIDED_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:

	virtual void BeginPlay() override;

	//blends transition from one camera to another, as opposed to snapping to it
	const float SmoothBlendTime = 0.5f;

public:

	virtual void Tick(float DeltaTime) override;

	APlayerController* OurPlayerController;

	//static camera 1, key binding 1 (not numpad)
	UPROPERTY(EditAnywhere)
		AActor* CameraOne;
	void SetCameraOne();
	//static camera 2, key binding 2 (not numpad)
	UPROPERTY(EditAnywhere)
		AActor* CameraTwo;
	void SetCameraTwo();
	//player camera, keybinding 0 (not numpad)
	UPROPERTY(EditAnywhere)
		AActor* FollowCamera;
	void SetFollowCamera();
	//First Person Camera, keybinding 3 (not numpad)
	UPROPERTY(EditAnywhere)
		AActor* FPCamera;
	void SetFPCamera();
};

