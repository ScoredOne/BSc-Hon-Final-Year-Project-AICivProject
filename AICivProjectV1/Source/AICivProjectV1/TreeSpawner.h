// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tree.h"
#include "TreeSpawner.generated.h"

UCLASS()
class AICIVPROJECTV1_API ATreeSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreeSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
		FVector GetRandomMeshPoint(float Radius);

	UFUNCTION()
		void SpawnStuff();
	
	UPROPERTY(EditAnywhere, Category = "TreeSpawning")
		TSubclassOf<ATree> TreeBase;
};
