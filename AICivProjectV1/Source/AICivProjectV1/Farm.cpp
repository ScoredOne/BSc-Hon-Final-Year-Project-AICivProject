// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "Farm.h"

void AFarm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TotalResource <= 0)
	{
		HarvestReady = false;
	}
	if (TotalResource >= MaxResources)
	{
		HarvestReady = true;
	}
	Regenerate();
}

void AFarm::Regenerate()
{
	if (Worker && !HarvestReady) {
		TotalResource++;
	}
	else
	{
		if (counter >= RegenTimer) {
			counter = 0;
			TotalResource++;
		}
		else
		{
			counter++;
		}
	}

}

void AFarm::SetAppearence()
{

}
