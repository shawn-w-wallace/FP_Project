// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h" 

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
	//on start up, sets viewport to current camera FollowCamera
	OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	FollowCamera = OurPlayerController->GetViewTarget();

}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//function for transition from camera 'x' to cameraOne using blending for smooth transition based on the position of the two cameras
void ACameraDirector::SetCameraOne()
{
	if (OurPlayerController)
	{
		if (OurPlayerController->GetViewTarget() != CameraOne)
		{
			OurPlayerController->SetViewTargetWithBlend(CameraOne, SmoothBlendTime);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Set to CameraOne"));
		}
	}
}
//function for transition from camera 'x' to cameraTwo using blending for smooth transition based on the position of the two cameras
void ACameraDirector::SetCameraTwo()
{
	if (OurPlayerController)
	{
		if (OurPlayerController->GetViewTarget() != CameraTwo)
		{
			OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Set to CameraTwo"));
		}
	}
}
//function for transition from camera 'x' to player camera using blending for smooth transition based on the position of the two cameras
void ACameraDirector::SetFollowCamera()
{
	if (OurPlayerController)
	{
		if (OurPlayerController->GetViewTarget() != FollowCamera)
		{
			OurPlayerController->SetViewTargetWithBlend(FollowCamera, SmoothBlendTime);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Set to FollowCamera"));
		}
	}
}
//function for transition from camera 'x' to first person camera using blending for smooth transition based on the position of the two cameras
void ACameraDirector::SetFPCamera()
{
	if (OurPlayerController)
	{
		if (OurPlayerController->GetViewTarget() != FPCamera)
		{
			OurPlayerController->SetViewTargetWithBlend(FPCamera, SmoothBlendTime);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Set to FPCamera"));
		}
	}
}
