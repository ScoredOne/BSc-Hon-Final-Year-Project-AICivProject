// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "TreeSpawner.h"


// Sets default values
ATreeSpawner::ATreeSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATreeSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnStuff();
}

// Called every frame
void ATreeSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATreeSpawner::SpawnStuff()
{
	FActorSpawnParameters SpawnParameters;
	FTransform SpawnTransform = GetTransform();

	for (int x = 0; x < 500; x++)
	{
		SpawnTransform.SetLocation(GetRandomMeshPoint(2500));
		ATree* SpawnTree = GetWorld()->SpawnActor<ATree>(TreeBase, SpawnTransform, SpawnParameters);
	}
}

FVector ATreeSpawner::GetRandomMeshPoint(float Radius)
{
	FNavLocation RandomPointResult;
	UNavigationSystem* NavSystem = UNavigationSystem::GetCurrent(GetWorld());

	bool GenerateNode = NavSystem->GetRandomPointInNavigableRadius(this->GetActorLocation(), Radius, RandomPointResult);
	
	return RandomPointResult.Location;
}