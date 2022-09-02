// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "StoneSpawner.h"


// Sets default values
AStoneSpawner::AStoneSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStoneSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnStuff();
}

// Called every frame
void AStoneSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AStoneSpawner::SpawnStuff()
{
	FActorSpawnParameters SpawnParameters;
	FTransform SpawnTransform = GetTransform();

	for (int x = 0; x < 100; x++)
	{
		SpawnTransform.SetLocation(GetRandomMeshPoint(1000));
		AStone* SpawnStone = GetWorld()->SpawnActor<AStone>(StoneBase, SpawnTransform, SpawnParameters);
	}
}

FVector AStoneSpawner::GetRandomMeshPoint(float Radius)
{
	FNavLocation RandomPointResult;
	UNavigationSystem* NavSystem = UNavigationSystem::GetCurrent(GetWorld());

	bool GenerateNode = NavSystem->GetRandomReachablePointInRadius(this->GetActorLocation(), Radius, RandomPointResult);

	return RandomPointResult.Location;
}