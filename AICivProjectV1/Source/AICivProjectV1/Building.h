// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class AICIVPROJECTV1_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	int Health;
	int Tier = 0;

	TArray<class ACitizenBody*> HousedCitizens;
	int32 CountedHousedCitizens; // Counting current housed citizens

	TArray<class ACitizenBody*> AssignedCitizens;
	int32 CountedAssignedCitizens = 0;

	int32 MaxHousedCitizens; // used to compare assigned and current housed
	bool CanHouseCitizens;
		
	int HousedFood = 0;
	int MaxFood;
	int HousedWood = 0;
	int MaxWood;
	int HousedStone = 0;
	int MaxStone;

	UFUNCTION()
		void UpgradeTier();
};
