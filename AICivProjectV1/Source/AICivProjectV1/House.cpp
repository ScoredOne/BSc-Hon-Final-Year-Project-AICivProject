// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "House.h"


void AHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CanHouseCitizens = true;

	switch (Tier)
	{
	case 0:
		MaxHousedCitizens = 4;
		break;
	case 1:
		MaxHousedCitizens = 6;
		break;
	case 2:
		MaxHousedCitizens = 8;
		break;
	}
}
