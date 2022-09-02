// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Resource.h"
#include "Tree.generated.h"

/**
 * 
 */
UCLASS()
class AICIVPROJECTV1_API ATree : public AResource
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	int ResourceType = 1;

	virtual void Regenerate() override;
	int RegenTimer = 20;
	int counter = 0;

	virtual void SetAppearence() override;
};
