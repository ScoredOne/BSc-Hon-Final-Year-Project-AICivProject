// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building.h"
#include "StoreHouse.generated.h"

/**
 * 
 */
UCLASS()
class AICIVPROJECTV1_API AStoreHouse : public ABuilding
{
	GENERATED_BODY()
public:

	virtual void Tick(float DeltaSeconds) override;
	

};
