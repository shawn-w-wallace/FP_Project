// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "InteractionInterface.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//constructors build boom and camera. boom attatched to character and camera, camera attatched to boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = InitCameraZoom;
	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	//First Person camera constructors, creates camera and attatches it to collision capsule, then moves it above mesh head
	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment(GetCapsuleComponent());
	FPCamera->RelativeLocation = FVector(-39.56f, 1.75f, 64.f);
	FPCamera->bUsePawnControlRotation = true;
	//trace collision query parameters
	TraceParams = FCollisionQueryParams(FName(TEXT("Trace")), true, this);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleHighlight();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(InputComponent);
	//gets control bindings (W & S) for movement along the x axis
	InputComponent->BindAxis("Lateral", this, &AMyCharacter::Lateral);
	//gets control bindings (A & D) for movement along the y axis
	InputComponent->BindAxis("SidetoSide", this, &AMyCharacter::SidetoSide);
	//left shift binding and functionality for sprinting
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::BeginSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::EndSprint);
	//mouse look control
	InputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);
	//jumping
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::OnStopJump);
	//camera bindings
	InputComponent->BindAction("CameraOne", IE_Pressed, this, &AMyCharacter::ChangeView<1>);
	InputComponent->BindAction("CameraTwo", IE_Pressed, this, &AMyCharacter::ChangeView<2>);
	InputComponent->BindAction("FPCamera", IE_Pressed, this, &AMyCharacter::ChangeView<3>);
	InputComponent->BindAction("FollowCamera", IE_Pressed, this, &AMyCharacter::ChangeView<0>);
	//interaction
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMyCharacter::SrvInteract);
}

//float value used for greater precision
void AMyCharacter::Lateral(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::SidetoSide(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::BeginSprint()//player is holding down Left shift
{
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AMyCharacter::EndSprint()//player is no longer holding down Left shift
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AMyCharacter::OnStartJump() //start jump, player in air
{
	bPressedJump = true;
}

void AMyCharacter::OnStopJump() //end jump, player lands, can jump again.
{
	bPressedJump = false;
}

//sets current camera to viewport based on user input via function call
void  AMyCharacter::SetView(int CamNumber)
{

	for (TActorIterator<ACameraDirector> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (CamNumber == 0)
		{
			ActorItr->SetFollowCamera();
			break;
		}
		else if (CamNumber == 1)
		{
			ActorItr->SetCameraOne();
			break;
		}
		else if (CamNumber == 2)
		{
			ActorItr->SetCameraTwo();
			break;
		}
		else if (CamNumber == 3)
		{
			ActorItr->SetFPCamera();
			break;
		}
	}
}

//if object can be interacted with returns interaction function
void  AMyCharacter::SrvInteract()
{
	if (FocusedActor)
	{
		IInteractionInterface* interface = Cast<IInteractionInterface>(FocusedActor);
		if (interface)
		{
			interface->Execute_OnInteract(FocusedActor, this);
		}
	}
}
//
//
//
AActor*  AMyCharacter::FindActorInLOS()
{
	FVector Loc;
	FRotator Rot;
	FHitResult Hit(ForceInit);
	GetController()->GetPlayerViewPoint( Loc, Rot );

	FVector Start = Loc;
	FVector End = Start + (Rot.Vector() * InteractionDistance);

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	return Hit.GetActor();
}

//handles whether or not an object the player is looking at is interactable and should be highlighted or not
void  AMyCharacter::HandleHighlight()
{
	AActor* interactable = FindActorInLOS();
	
	if (interactable)
	{
		if (interactable != FocusedActor)
		{
			if (FocusedActor)
			{
				IInteractionInterface* interface = Cast<IInteractionInterface>(FocusedActor);
				if (interface)
				{
					interface->Execute_EndFocus(FocusedActor);
				}
			}
			IInteractionInterface* interface = Cast<IInteractionInterface>(interactable);
			if (interface)
			{
				interface->Execute_StartFocus(interactable);
			}
			FocusedActor = interactable;
		}
	}
	else
	{
		if (FocusedActor)
		{
			IInteractionInterface* interface = Cast<IInteractionInterface>(FocusedActor);
			if (interface)
			{
				interface->Execute_EndFocus(FocusedActor);
			}
		}
		FocusedActor = nullptr;
	}
}
