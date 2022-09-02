// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Resource.h"
#include "CitizenBody.generated.h"

class ABuilding; // forward declaration Building.h
class AHouse;
class ATownHall;
class ATree;
class AFarm;
class AStone;
class AStoreHouse;

UCLASS(Blueprintable)
class AICIVPROJECTV1_API ACitizenBody : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACitizenBody();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	int Health = 100;
	int Stress = 0;
	int StressTimer = 0; // Timer for intervals taking on stress
	int Hunger = 0; 
	int HungerTimer = 0; // Timer for intervals for becoming hungry

	UPROPERTY(EditAnywhere)
		int StressThreshold = 70;

	UPROPERTY(EditAnywhere)
		int StressResetThreshold = 0;

	UPROPERTY(EditAnywhere)
		int HungerThreshold = 70;

	UPROPERTY(EditAnywhere)
		int HungerResetThreshold = 0;

	// future work
	int Age;
	bool Gender;
	
	int TownNum; // used to check associated town, if many are present.

	int NumResources = 0;
	int CarryWeight = 100;
	int ResourceType = 0; // 0 = none, 1 = food, 2 = wood, 3 = stone

	UPROPERTY()
		ACitizenBody* Partner = nullptr;

	UPROPERTY()
		AHouse* Home = nullptr;

	UPROPERTY()
		ABuilding* TargetBuilding = nullptr;

	UPROPERTY()
		AResource* TargetResource = nullptr; // Dropped Resource

	UPROPERTY()
		AFarm* AssignedFarm = nullptr;

	UPROPERTY()
		ATree* TargetTree = nullptr;

	UPROPERTY()
		AStone* TargetStone = nullptr;

	UPROPERTY()
		ATownHall* MyTownHall = nullptr;

	UPROPERTY()
		AStoreHouse* TargetStoreHouse = nullptr;

	int Wellbeing;

	UPROPERTY(EditAnywhere, Category = "C++")
		int CurrentRole; // Dont directly change, only change with RoleChange as it is used to override 
	int RoleChange; // if changed it will reset current work task then change role to this number

	//////////////////////////////////////////////////////////////
	bool AtHome = false;
	bool AtTaskLocation = false;
	bool Resting = false;
	bool RestingPenalty = false;
	bool Working = false;
	//////////////////////////////////////////////////////////////

	UFUNCTION()
		void DoTask(int ToDo, bool AtStoreHouse = false);

	UFUNCTION()
		void Eating();

	UFUNCTION()
		void StressDamage();

	UFUNCTION()
		void HungerDamage();

	UFUNCTION()
		void CalculateWellbeing();

	UFUNCTION()
		void EnterHome();

	UFUNCTION()
		void LeaveHome();

	UFUNCTION()
		void DropResources();

	UFUNCTION()
		void Sleeping();
	int restTick = 0;

	UFUNCTION()
		void EmergencyStop(); // if triggered rest until Stress and are Hunger < 10 (Probably called when it looks like the Citizen might kill themselves)
		bool EmergencyStopActive = false;

	UFUNCTION()
		void CheckEStopStatus();

	UFUNCTION()
		void ConfirmPartner();

	////////////////////////////////////////////////////////////////

	UPROPERTY(EditAnywhere, Category = "Resource")
		TSubclassOf<AResource> DropStuff;
};
