// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "EngineUtils.h"
#include "TownHall.h"
#include "BehaviourTreeAI.h"

// Sets default values
ATownHall::ATownHall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//AIControllerClass = ABehaviourTreeAI::StaticClass();


}

// Called when the game starts or when spawned
void ATownHall::BeginPlay()
{
	Super::BeginPlay();

	CheckIdentityUnique();

	InitialSpawning();

	ScanForResources();
}

// Called every frame
void ATownHall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateResourceCount();
	FindDroppedResources();

	if (CitSpawnTimer < 100000)
	{
		CitSpawnTimer++;
	}
	else
	{
		BuildBuilding(3, true);
		CitSpawnTimer = 0;
	}
	if (FoodIntervalTimer < 1000)
	{
		FoodIntervalTimer++;
	}
	else
	{
		if (IntervalSwitch)
		{
			FoodInterval2 = TotalFood;
			FoodRate = FoodInterval1 - FoodInterval2;
			IntervalSwitch = false;
		}
		else
		{
			FoodInterval1 = TotalFood;
			FoodRate = FoodInterval2 - FoodInterval1;
			IntervalSwitch = true;
		}
		FoodIntervalTimer = 0;
	}
}

void ATownHall::ScanForResources()
{
	FoundWood.Empty();
	FoundStone.Empty();
	for (TActorIterator<ATree> Itr(GetWorld()); Itr; ++Itr) // Get all trees in the game
	{
		ATree* Tree = *Itr;
		if (!Tree->Dead)
		{
			FoundWood.Add(*Itr);
		}
	}

	for (TActorIterator<AStone> Itr(GetWorld()); Itr; ++Itr) // Get all stones in the game
	{
		AStone* Stone = *Itr;
		if (!Stone->Dead)
		{
			FoundStone.Add(*Itr);
		}
	}
}

ATree* ATownHall::GetClosestTree()
{
	ATree* ClosestTree = nullptr;
	float DistanceToTree = 0;
	if (FoundWood.Num() > 0)
	{
		for (const auto& Trees : FoundWood)
		{
			if (!Trees->Dead)
			{
				float Distance = FVector::Dist(this->GetActorLocation(), Trees->GetActorLocation());
				if (DistanceToTree == 0 || DistanceToTree > Distance)
				{
					DistanceToTree = Distance;
					ClosestTree = Trees;
				}
			}
		}
	}
	else
	{
		ScanForResources();
	}

	return ClosestTree;
}

AStone* ATownHall::GetClosestStone()
{
	AStone* ClosestStone = nullptr;
	float DistanceToStone = 0;
	if (FoundStone.Num() > 0)
	{
		for (const auto& Stones : FoundStone)
		{
			if (!Stones->Dead)
			{
				float Distance = (this->GetActorLocation() - Stones->GetActorLocation()).Size();
				if (DistanceToStone == 0 || DistanceToStone > Distance)
				{
					DistanceToStone = Distance;
					ClosestStone = Stones;
				}
			}
		}
	}
	else
	{
		ScanForResources();
	}

	return ClosestStone;
}

AFarm* ATownHall::GetUnassignedFarm()
{
	AFarm* UnassignedFarm = nullptr;
	if (OwnedFarms.Num() > 0)
	{
		for (const auto& Farms : OwnedFarms)
		{
			if (!Farms->WorkingCitizen)
			{
				UnassignedFarm = Farms;
				break;
			}
		}
	}

	return UnassignedFarm;
}

AStoreHouse* ATownHall::GetAvailableStoreHouse(int ResourceType)
{
	AStoreHouse* Storehouse = nullptr;
	for (const auto& Stores : AllStoreHouses)
	{
		if (ResourceType == 1) // Resource type is currently the same as the cits "Role"
		{
			if (Stores->HousedFood < Stores->MaxFood)
			{
				Storehouse = Stores;
				break;
			}
		}
		else if (ResourceType == 2)
		{
			if (Stores->HousedWood < Stores->MaxWood)
			{
				Storehouse = Stores;
				break;
			}
		}
		else if (ResourceType == 3)
		{
			if (Stores->HousedStone < Stores->MaxStone)
			{
				Storehouse = Stores;
				break;
			}
		}
	}
	return Storehouse;
}

AResource* ATownHall::GetDroppedResource()
{
	AResource* Box = nullptr;
	if (DroppedResources.Num() > 0)
	{
		for (const auto& Res : DroppedResources)
		{
			if (Res->TotalResource > 0)
			{
				return Res;
			}
			else
			{
				Res->Dead = true;
				DroppedResources.Remove(Res);
			}
		}
	}
	return Box;
}

void ATownHall::UpdateResourceCount()
{
	TotalFood = 0;
	TotalWood = 0;
	TotalStone = 0;
	for (const auto& Store : AllStoreHouses)
	{
		TotalFood += Store->HousedFood;
		TotalWood += Store->HousedWood;
		TotalStone += Store->HousedStone;
	}
}

void ATownHall::InitialSpawning()
{

	BuildBuilding(0, true);

	BuildBuilding(1);
	BuildBuilding(1);

	BuildBuilding(2);
	BuildBuilding(2);
	BuildBuilding(2);

	for (int x = 0; x < 4; x++)
	{
		BuildBuilding(3, NULL, true);
	}

}

void ATownHall::BuildBuilding(int Choice, int Radius, bool InitialSpawn)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bNoCollisionFail = false;
	FTransform SpawnTransform = GetTransform();
	if (Radius < 2500)
	{
		Radius = 2500;
	}
	SpawnTransform.SetLocation(GetRandomMeshPoint(Radius));

	if (GetWorld())
	{
		if (Choice == 0) // StoreHouse
		{
			AStoreHouse* SpawnStoreHouse = GetWorld()->SpawnActor<AStoreHouse>(StoreHouse, SpawnTransform, SpawnParameters);
			if (InitialSpawn)
			{
				SpawnStoreHouse->HousedFood = 1000;
				SpawnStoreHouse->HousedWood = 1000;
			}
			else
			{
				int ResourcesNeeded = 1000;
				for (const auto& Itr : AllStoreHouses)
				{
					if (Itr->HousedWood < ResourcesNeeded)
					{
						ResourcesNeeded -= Itr->HousedWood;
						Itr->HousedWood = 0;
					}
					else
					{
						Itr->HousedWood -= ResourcesNeeded;
					}
					if (ResourcesNeeded <= 0)
					{
						break;
					}
				}
			}
			AllStoreHouses.Add(SpawnStoreHouse);
		}
		else if (Choice == 1) // House
		{
			AHouse* SpawnHouse = GetWorld()->SpawnActor<AHouse>(House, SpawnTransform, SpawnParameters);
			AllHouses.Add(SpawnHouse);
			if (InitialSpawn)
			{
				SpawnHouse->HousedFood = 1000;
			}
			else
			{
				int ResourcesNeeded = 500;
				for (const auto& Itr : AllStoreHouses)
				{
					if (Itr->HousedWood < ResourcesNeeded)
					{
						ResourcesNeeded -= Itr->HousedWood;
						Itr->HousedWood = 0;
					}
					else
					{
						Itr->HousedWood -= ResourcesNeeded;
					}
					if (ResourcesNeeded <= 0)
					{
						break;
					}
				}
			}
		}
		else if (Choice == 2) // Farm
		{
			AFarm* SpawnFarm = GetWorld()->SpawnActor<AFarm>(Farm, SpawnTransform, SpawnParameters);
			if (!InitialSpawn)
			{
				int ResourcesNeeded = 500;
				for (const auto& Itr : AllStoreHouses)
				{
					if (Itr->HousedWood < ResourcesNeeded)
					{
						ResourcesNeeded -= Itr->HousedWood;
						Itr->HousedWood = 0;
					}
					else
					{
						Itr->HousedWood -= ResourcesNeeded;
					}
					if (ResourcesNeeded <= 0)
					{
						break;
					}
				}
			}
			OwnedFarms.Add(SpawnFarm);
		}
		else if (Choice == 3) // Citizen
		{
			ACitizenBody* SpawnCitizen = GetWorld()->SpawnActor<ACitizenBody>(Citizen, SpawnTransform, SpawnParameters);
			SpawnCitizen->MyTownHall = this;
			SpawnCitizen->TownNum = TownNum;
			if (InitialSpawn)
			{
				SpawnCitizen->CurrentRole = FMath::FRandRange(1, 3); // Temp for testing
			}
			else
			{
				int ResourcesNeeded = 1000;
				for (const auto& Itr : AllStoreHouses)
				{
					if (Itr->HousedFood < ResourcesNeeded)
					{
						ResourcesNeeded -= Itr->HousedFood;
						Itr->HousedFood = 0;
					}
					else
					{
						Itr->HousedFood -= ResourcesNeeded;
					}
					if (ResourcesNeeded <= 0)
					{
						break;
					}
				}
				SpawnCitizen->CurrentRole = 0;
				if (BTAIClass != nullptr) {
					BTAIClass->SortCitizens(-1);
				}
			}
			AllCitizens.Add(SpawnCitizen);
			TotalCitizens++;
		}
	}
}

void ATownHall::CheckIdentityUnique() // done once on spawn
{
	bool check = false;
	while (check == false)
	{
		TownNum = FMath::RandRange(0, 10000);
		TArray<ATownHall*> CheckArray;
		bool towncheck = false;

		// Check all other townhalls to see if townnumber is unique
		for (TActorIterator<ATownHall> Itr(GetWorld()); Itr; ++Itr) // Get all towns in the game
		{
			CheckArray.Add(*Itr);
		}
		for (const auto& Towns : CheckArray) // cycle through array
		{
			if (Towns->GetFName() != this->GetFName()) // if not self
			{
				if (Towns->TownNum == TownNum) {
					towncheck = true;
				}
			}
		}
		if (towncheck == false)
		{
			check = true;
		}
	}
}

void ATownHall::AssignHousing(ACitizenBody* Cit) // basic house assign
{
	if (!Cit->Home)
	{
		for (const auto& itr : AllHouses)
		{
			if (itr->AssignedCitizens.Contains(Cit))
			{
				itr->AssignedCitizens.Remove(Cit);
			}
		}
		if (!Cit->Partner) // #Future Work#
		{
			for (const auto& House : AllHouses)
			{
				if (House->CountedAssignedCitizens < House->MaxHousedCitizens)
				{
					Cit->Home = House;
					House->AssignedCitizens.Add(Cit);
				}
			}
		}
		else // #Future Work#
		{
			if (Cit->Partner->Home->CountedAssignedCitizens < Cit->Partner->Home->MaxHousedCitizens)
			{
				Cit->Home = Cit->Partner->Home;
			}
		}
	}
	else if (!Cit->Home->AssignedCitizens.Contains(Cit))
	{
		for (const auto& itr : AllHouses)
		{
			if (itr->AssignedCitizens.Contains(Cit))
			{
				itr->AssignedCitizens.Remove(Cit);
			}
		}
		for (const auto& House : AllHouses)
		{
			if (House->CountedAssignedCitizens < House->MaxHousedCitizens)
			{
				Cit->Home = House;
				House->AssignedCitizens.Add(Cit);
			}
		}
	}
}
/*
void ATownHall::AssignHousingADV() // EVERYONE gets reassigned + couples #future work#
{
	for (const auto& House : AllHouses)
	{
		House->AssignedCitizens.Empty();
		House->CountedAssignedCitizens = 0;
	}
	for (const auto& Cit : AllCitizens)
	{
		Cit->Home = NULL;
	}

	for (const auto& Cit : AllCitizens)
	{
		Cit->ConfirmPartner();

		if (Cit->Partner != NULL)
		{
			for (const auto& House : AllHouses)
			{
				if (House->CountedAssignedCitizens < House->MaxHousedCitizens)
				{
					Cit->Home = House;
					House->AssignedCitizens.Add(Cit);
				}
			}
		}
		else if (Cit->Partner->Home != NULL)
		{
			if (Cit->Partner->Home->CountedAssignedCitizens < Cit->Partner->Home->CountedAssignedCitizens)
			{
				Cit->Home = Cit->Partner->Home;
			}
		}
		else
		{
			bool PairedHousingFailed = false;
			if (Cit->Partner->Home == NULL)
			{
				for (const auto& House : AllHouses)
				{
					if (House->MaxHousedCitizens - House->CountedAssignedCitizens >= 2)
					{
						Cit->Home = House;
						Cit->Partner->Home = House;
						House->AssignedCitizens.Add(Cit);
						House->AssignedCitizens.Add(Cit->Partner);
					}
				}
			}
			else if (Cit->Partner->Home->CountedAssignedCitizens < Cit->Partner->Home->MaxHousedCitizens)
			{
				Cit->Home = Cit->Partner->Home;
			}
		}
	}
}
*/
void ATownHall::FindDroppedResources()
{
	DroppedResources.Empty();
	for (TActorIterator<AResource> Itr(GetWorld()); Itr; ++Itr)
	{
		DroppedResources.Add(*Itr);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////

FVector ATownHall::GetRandomMeshPoint(float Radius)
{
	FNavLocation RandomPointResult;
	UNavigationSystem* NavSystem = UNavigationSystem::GetCurrent(GetWorld());

	bool GenerateNode = NavSystem->GetRandomPointInNavigableRadius(this->GetActorLocation(), Radius, RandomPointResult);

	return RandomPointResult.Location;
}