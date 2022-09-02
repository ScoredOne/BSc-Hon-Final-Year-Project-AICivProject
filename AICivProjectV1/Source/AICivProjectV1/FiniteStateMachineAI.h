// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TownHall.h"
#include "CitizenBody.h"

#include "Building.h"
#include "House.h"
#include "StoreHouse.h"

#include "Resource.h"
#include "Farm.h"
#include "Tree.h"
#include "Stone.h"
#include "FiniteStateMachineAI.generated.h"


/**
 * 
 */
UCLASS()
class AICIVPROJECTV1_API AFiniteStateMachineAI : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaSeconds) override;

	int State = 0; // place in the state machine | 0 - Normal working state, 1 - resting state, 2 - hungry...
	int Role = 0; // work task | 0 = unassigned

/////////// WORK FUNCTIONS////////////////////////////////////////////////////////////////////////////
	// Work stages | 1 for movement, 2 for working ext
	bool Stage1 = false;
	bool Stage2 = false; 
	bool Stage3 = false; // Take resources back to the storehouse
	bool Stage4 = false; 

	UFUNCTION()
		virtual void Work();

	UFUNCTION()
		virtual void Stage1Work();

	UFUNCTION()
		virtual void Stage2Work();

	UFUNCTION()
		virtual void Stage3Work();

	UFUNCTION()
		virtual void Stage4Work();

	UFUNCTION()
		virtual void ResetWork();

//////////////////////////////////////////////////////////////////////////////////////////////////////

	UFUNCTION()
		virtual void Idle();

	UFUNCTION()
		virtual void Run();

	UFUNCTION()
		virtual void GoEat();
	bool RestockHouse;

	UFUNCTION()
		virtual void GoRest();

	UFUNCTION()
		virtual void CheckHealth();

	UFUNCTION()
		virtual void RefreshInfo();

	UFUNCTION()
		bool GoToLocation(FVector Destination);
	bool MovementComplete = true; /////////////////////////////////// instead of true of false, check distance and if its not close enough move else work.

	UPROPERTY()
		ACitizenBody* Cit = nullptr;

};

