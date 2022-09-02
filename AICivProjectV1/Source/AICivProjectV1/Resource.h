// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Resource.generated.h"

UCLASS()
class AICIVPROJECTV1_API AResource : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResource();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	int Health;
	bool Dead = false;

	int TotalResource = 1000;
	int ResourceType; // 0 = Food, 1 = Wood, 2 = Stone

	virtual void Regenerate();

	virtual void SetAppearence();

	// Set model to a box, child classes will have their own anyway
};
