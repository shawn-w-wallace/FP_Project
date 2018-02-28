// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActorReplicator.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMyActorReplicator::AMyActorReplicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActorReplicator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActorReplicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//synchronizes replicated instances of this actor
AMyActorReplicator::AActor(const class FPostConstructInitalizeProperties & PCIP) : Super(PCIP)
{
	bReplicates = true;
}
//registers properties for replication
void AActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION(AActor, ReplicatedMovement, COND_SimulatedOnly);
}