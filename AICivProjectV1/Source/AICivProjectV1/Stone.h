// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Resource.h"
#include "Stone.generated.h"

/**
 * 
 */
UCLASS()
class AICIVPROJECTV1_API AStone : public AResource
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaSeconds) override;

	int ResourceType = 2;

	virtual void SetAppearence() override;
};
