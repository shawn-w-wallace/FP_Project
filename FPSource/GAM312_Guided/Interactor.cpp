// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactor.h"
#include "Components/MeshComponent.h"

// Sets default values
AInteractor::AInteractor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractor::BeginPlay()
{
	Super::BeginPlay();
	
	//gets components on this acter that ae of the mesh class, cast them to mesh component and stores them in an array
	for (UActorComponent* Comp : GetComponentsByClass(UMeshComponent::StaticClass()))
	{
		UMeshComponent* Mesh = Cast<UMeshComponent>(Comp);
		Meshes.Push(Mesh);
	}
}

// Called every frame
void AInteractor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//
void AInteractor::OnInteract_Implementation(AActor* Caller)
{
	Destroy();
}

//goes through array of meshes and when player is looking at the object, adds outline
void AInteractor::StartFocus_Implementation()
{
	for (UMeshComponent* Mesh : Meshes)
	{
		Mesh-> SetRenderCustomDepth(true);
	}
}

//goes through array of meshes and when player is not looking at the object, gets rid of outline
void AInteractor::EndFocus_Implementation()
{
	for (UMeshComponent* Mesh : Meshes)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}
