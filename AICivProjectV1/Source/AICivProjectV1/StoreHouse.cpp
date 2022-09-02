// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "StoreHouse.h"


void AStoreHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MaxHousedCitizens = 0;
	CanHouseCitizens = false;

	switch (Tier)
	{
	case 0:
		MaxFood = 10000;
		MaxWood = 10000;
		MaxStone = 10000;

		//MaxFood = 2000; 
		//MaxWood = 2000;
		//MaxStone = 0;
		break;
	case 1:
		MaxFood = 4000;
		MaxWood = 4000;
		MaxStone = 1000;
		break;
	case 2:
		MaxFood = 8000;
		MaxWood = 8000;
		MaxStone = 2500;
		break;
	}
}
