// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CitizenBody.h"
#include "Resource.h"
#include "Farm.generated.h"

/**
 * 
 */
UCLASS()
class AICIVPROJECTV1_API AFarm : public AResource
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	int ResourceType = 1;
	int MaxResources = 1000;

	virtual void Regenerate() override;

	int RegenTimer = 10;
	int counter = 0;
	
	bool Worker;
	bool HarvestReady = false;

	int OwnedTown;

	virtual void SetAppearence() override;

	ACitizenBody* WorkingCitizen;
};
