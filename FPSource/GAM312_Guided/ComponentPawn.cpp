// Fill out your copyright notice in the Description page of Project Settings.

#include "ComponentPawn.h"
#include "ComponentPawnMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
AComponentPawn::AComponentPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

		//sphere constructor, this is the root component and contains the collision mask and physics properties 
		USphereComponent* Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
		RootComponent = Sphere;
		Sphere->InitSphereRadius(50.0f);
		Sphere->SetCollisionProfileName(TEXT("Pawn"));
		Sphere->SetSimulatePhysics(true);

		//mesh constructor, this is the visual component and is attatched to the root component so that the visual asset "has" physics and collision properties
		UStaticMeshComponent* SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
		SphereMesh->AttachTo(RootComponent);
		static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
		if (SphereVisualAsset.Succeeded())
		{
			SphereMesh->SetStaticMesh(SphereVisualAsset.Object);
			SphereMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
			SphereMesh->SetWorldScale3D(FVector(0.8f));
			SphereMesh->SetSimulatePhysics(true);
		}
		// Use a spring arm to give the camera smooth, natural-feeling motion.
		USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
		SpringArm->SetupAttachment(RootComponent);
		SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
		SpringArm->TargetArmLength = 400.0f;
		SpringArm->bEnableCameraLag = true;
		SpringArm->CameraLagSpeed = 3.0f;

		// Create a camera and attach to our spring arm
		UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
		Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

		//player controls component commented out for steppingstone
		//AutoPossessPlayer = EAutoReceiveInput::Player0;

		// Create an instance of our movement component, and tell it to update the root.
		OurMovementComponent = CreateDefaultSubobject<UComponentPawnMovementComponent>(TEXT("CustomMovementComponent"));
		OurMovementComponent->UpdatedComponent = RootComponent;


}

// Called when the game starts or when spawned
void AComponentPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AComponentPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AComponentPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("Lateral", this, &AComponentPawn::MoveForward);
	InputComponent->BindAxis("SideToSide", this, &AComponentPawn::MoveRight);
	InputComponent->BindAxis("Turn", this, &AComponentPawn::Turn);

}
//function returns custom movement component
UPawnMovementComponent* AComponentPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}
//movement lateral
void AComponentPawn::MoveForward(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}
// movement side to side
void AComponentPawn::MoveRight(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}
//rotation
void AComponentPawn::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}