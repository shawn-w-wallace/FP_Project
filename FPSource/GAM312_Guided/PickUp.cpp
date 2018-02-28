// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUp.h"


// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//component constructors
	PickUpItemRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickUpItemRoot"));
	RootComponent = PickUpItemRoot;
	PickUpItem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpItem"));
	PickUpItem->AttachToComponent(PickUpItemRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	PickUpItemBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickUpItemBox"));
	PickUpItemBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	PickUpItemBox->bGenerateOverlapEvents = true;
	PickUpItemBox->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnPlayerEnterPickUpItemBox);
	PickUpItemBox->AttachToComponent(PickUpItemRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//When player overlaps volume destroy the mesh
//logic can be replaced to increment weapon ammo, player health etc
void APickUp::OnPlayerEnterPickUpItemBox(UPrimitiveComponent * OverlappedCom, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Destroy();
}

