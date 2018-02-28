// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "CameraDirector.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class GAM312_GUIDED_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()


		//First Person camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent*FPCamera;

		//Uproperty camera and boom components for player follow camera, protected from garbage collection.  sort of a "save" function for static settings 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;


public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	void Lateral(float Value); //Forward and Backward
	void SidetoSide(float Value); //Right and Left
	void BeginSprint(); //function sets IsSprinting to true
	void EndSprint(); //function sets IsSprinting to False
	float InitCameraZoom = 200.0f;// boom setting for follow camera

	UFUNCTION()
	void SrvInteract();//interact function

	void HandleHighlight();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	//highlights object for player
	AActor* FindActorInLOS();//gets object in viewport

	//player input controls variables *note: would it be wiser to move the variables 
	//(broken into sub groups if necessary) to the top of the public encapsulation?*
	bool bIsSprinting = false;
	float WalkSpeed = 300.f;
	float SprintSpeed = WalkSpeed * 1.5f;

	//sets jump flag when key is pressed
	UFUNCTION()
	void OnStartJump();
	//clears jump flag when key is released
	UFUNCTION()
	void OnStopJump();

	//index storing current camera for function call and blending transitions
	template <int Index>
	void ChangeView() { SetView(Index); }
	void SetView(int CamNumber);

private:
	AActor* FocusedActor;
	float InteractionDistance = 200.0f;
	FCollisionQueryParams TraceParams; //line trace for distance of player from object

};