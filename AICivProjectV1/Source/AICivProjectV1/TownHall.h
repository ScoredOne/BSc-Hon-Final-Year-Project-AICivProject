// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"

#include "House.h"
#include "StoreHouse.h"

#include "Resource.h"
#include "Farm.h"
#include "Tree.h"
#include "Stone.h"

#include "TownHall.generated.h"  // all includes go before the .generated

class ACitizenBody;
class ABehaviourTreeAI;

UCLASS()
class AICIVPROJECTV1_API ATownHall : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATownHall();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//int Health;
	int CitSpawnTimer = 0;

	int TotalFood, TotalWood, TotalStone;

	int FoodInterval1, FoodInterval2, FoodIntervalTimer = 0;
	bool IntervalSwitch = false;

	int FoodRate = 0;

	int TownTier = 0;

	int TownNum;

	int HousableCitizens;
	int TotalCitizens = 0;

	UPROPERTY()
		TArray<ACitizenBody*> AllCitizens;

	UPROPERTY()
		TArray<ACitizenBody*> AssignedFarmers;

	UPROPERTY()
		TArray<ACitizenBody*> AssignedLumberJacks;

	UPROPERTY()
		TArray<ACitizenBody*> AssignedMiners;

	UPROPERTY()
		TArray<AStoreHouse*> AllStoreHouses;

	UPROPERTY()
		TArray<AHouse*> AllHouses;

	UPROPERTY()
		TArray<ATree*> FoundWood;

	UPROPERTY()
		TArray<AStone*> FoundStone;

	UPROPERTY()
		TArray<AFarm*> OwnedFarms;

	UPROPERTY()
		TArray<AResource*> DroppedResources;


		ABehaviourTreeAI* BTAIClass;

	////////////////////////////////////////////
	
	UFUNCTION()
		void ScanForResources(); // Find all Resources within range

	UFUNCTION()
		ATree* GetClosestTree();

	UFUNCTION()
		AStone* GetClosestStone();

	UFUNCTION()
		AFarm* GetUnassignedFarm();

	UFUNCTION()
		AStoreHouse* GetAvailableStoreHouse(int ResourceType);

	UFUNCTION()
		AResource* GetDroppedResource();

	UFUNCTION()
		void UpdateResourceCount();

	UFUNCTION()
		void InitialSpawning(); // Spawn the Storehouse, Citizens and resources (or just spawn the storehouse with the resources)

	UFUNCTION()
		void BuildBuilding(int Choice, int Radius = 2500, bool InitialSpawn = false); // 0 = storehouse, 1 = house, 2 = Farm

	UFUNCTION()
		void CheckIdentityUnique();

	UFUNCTION()
		void AssignHousing(ACitizenBody* Cit);

	//UFUNCTION()
	//	void AssignHousingADV();

	UFUNCTION()
		void FindDroppedResources();


	////////////////////////////////////////////

	UPROPERTY(EditAnywhere, Category = "ActorSpawning")
		TSubclassOf<AStoreHouse> StoreHouse;

	UPROPERTY(EditAnywhere, Category = "ActorSpawning")
		TSubclassOf<AHouse> House;

	UPROPERTY(EditAnywhere, Category = "ActorSpawning")
		TSubclassOf<AFarm> Farm;

	UPROPERTY(EditAnywhere, Category = "ActorSpawning")
		TSubclassOf<ACitizenBody> Citizen;
	
	////////////////////////////////////////////

	UFUNCTION()
		FVector GetRandomMeshPoint(float Radius); // need a check for if building would intersect other objects

	////////////////////////////////////////////

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;
};
