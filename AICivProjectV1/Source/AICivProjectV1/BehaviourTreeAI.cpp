// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "BehaviourTreeAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

ABehaviourTreeAI::ABehaviourTreeAI()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	BehaviourComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourComp"));
}

void ABehaviourTreeAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	RefreshInfo();
	SetBlackboardTown();
}

void ABehaviourTreeAI::BeginPlay()
{
	Super::BeginPlay();
	RefreshInfo();
}

void ABehaviourTreeAI::RefreshInfo()
{
	if (this->GetPawn())
	{
		AssignedTown = Cast<ATownHall>(this->GetPawn());
		if (AssignedTown)
		{
			AssignedTown->BTAIClass = this;
			initialised = true;
		}
		else
		{
			initialised = false;
		}
	}
}

void ABehaviourTreeAI::CallBuild(int BuildingType, int Radius)
{
	if (AssignedTown)
	{
		if (Radius == 0)
		{
			AssignedTown->BuildBuilding(BuildingType);
		}
		else
		{
			AssignedTown->BuildBuilding(BuildingType, Radius);
		}
	}
}

void ABehaviourTreeAI::SortCitizens(int WoodPriority, int RoleSort)
{
	if (WoodPriority < 0)
	{
		WoodPriority = 0;
	}

	int TotalStone = 0;

	if (initialised) {
		if (AssignedTown->AllStoreHouses.Num() > 0) {
			for (int x = 0; x < AssignedTown->AllStoreHouses.Num(); x++) {
				if (AssignedTown->AllStoreHouses[x]) {
					TotalStone += AssignedTown->AllStoreHouses[x]->MaxStone;
				}
			}
		}

		// Already assigned citizens
		TArray<class ACitizenBody*> UnassignedCits;
		TArray<class ACitizenBody*> Farmers;
		TArray<class ACitizenBody*> Lumberjacks;
		TArray<class ACitizenBody*> Miners;
		for (const auto& Itr : AssignedTown->AllCitizens)
		{
			if (RoleSort == -1)
			{
				Itr->CurrentRole = 0;
				UnassignedCits.Add(Itr);
			}
			else
			{
				switch (Itr->Role)
				{
				case 1:
					Farmers.Add(Itr);
					break;
				case 2:
					Lumberjacks.Add(Itr);
					break;
				case 3:
					Miners.Add(Itr);
					break;
				default:
					UnassignedCits.Add(Itr);
					break;
				}
			}

		}

		if (RoleSort == -1)
		{
			int ReassignedCitz = 0;
			bool Skip = false;
			AssignedTown->AssignedFarmers.Empty();
			AssignedTown->AssignedLumberJacks.Empty();
			AssignedTown->AssignedMiners.Empty();

			for (const auto& Itr : UnassignedCits)
			{
				if (AssignedTown->AssignedFarmers.Num() < AssignedTown->OwnedFarms.Num())
				{
					Itr->CurrentRole = 0; // Farmers
					AssignedTown->AssignedFarmers.Add(Itr);
					ReassignedCitz++;
				}
				else if (!Skip || (AssignedTown->AssignedLumberJacks.Num() < WoodPriority || AssignedTown->AssignedMiners.Num() >= AssignedTown->AllStoreHouses.Num()))
				{
					Itr->CurrentRole = 1; // Lumberjack
					AssignedTown->AssignedLumberJacks.Add(Itr);
					ReassignedCitz++;
					if (AssignedTown->AssignedLumberJacks.Num() >= WoodPriority && TotalStone > 0 && AssignedTown->AssignedMiners.Num() < AssignedTown->AllStoreHouses.Num())
					{
						Skip = true;
					}
				}
				else
				{
					Itr->CurrentRole = 2; // Miners
					AssignedTown->AssignedMiners.Add(Itr);
					ReassignedCitz++;
					if (AssignedTown->AssignedLumberJacks.Num() >= WoodPriority && TotalStone > 0 && AssignedTown->AssignedMiners.Num() < AssignedTown->AllStoreHouses.Num())
					{
						Skip = true;
					}
					else 
					{
						Skip = false;
					}
				}
			}
		}
		else
		{
			switch (RoleSort)
			{
			case 0: // Farmers
				if (UnassignedCits.Num() > 0)
				{
					for (const auto& Itr : UnassignedCits)
					{
						if (AssignedTown->AssignedFarmers.Num() < AssignedTown->OwnedFarms.Num())
						{
							Itr->CurrentRole = 1;
							AssignedTown->AssignedFarmers.Add(Itr);
						}
					}
				}
				if (AssignedTown->OwnedFarms.Num() > AssignedTown->AssignedFarmers.Num())
				{
					if (Miners.Num() > 0)
					{
						for (const auto& Itr : Miners)
						{
							Itr->CurrentRole = 1;
							AssignedTown->AssignedFarmers.Add(Itr);
						}
					}
					for (const auto& Itr : Lumberjacks)
					{
						Itr->CurrentRole = 1;
						if (AssignedTown->OwnedFarms.Num() <= AssignedTown->AssignedFarmers.Num())
						{
							break;
						}
					}
				}
				break;
			case 1: // Lumberjacks
				for (const auto& Itr : UnassignedCits)
				{
					if (AssignedTown->AssignedLumberJacks.Num() < WoodPriority)
					{
						Itr->CurrentRole = 2;
						AssignedTown->AssignedLumberJacks.Add(Itr);
					}
				}
				if (AssignedTown->AssignedLumberJacks.Num() < WoodPriority)
				{
					if (Miners.Num() > 0)
					{
						for (const auto& Itr : Miners)
						{
							Itr->CurrentRole = 2;
							AssignedTown->AssignedLumberJacks.Add(Itr);
							return;
						}
					}
				}
				break;
			case 2: // Miners
				if (AssignedTown->AssignedMiners.Num() < AssignedTown->AllStoreHouses.Num())
				{
					if (UnassignedCits.Num() > 0)
					{
						for (const auto& Itr : UnassignedCits) // currently throws the rest of them into miners
						{
							Itr->CurrentRole = 3;
							AssignedTown->AssignedMiners.Add(Itr);
						}
					}
				}
				break;
			}
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 0.3, FColor::Red, TEXT("Pass"));
}

void ABehaviourTreeAI::UpgradeTier(ABuilding* BuildingToUpgrade)
{
	if (BuildingToUpgrade)
	{
		BuildingToUpgrade->UpgradeTier();
	}
}

void ABehaviourTreeAI::SetBlackboardTown()
{
	if (BlackboardComp)
	{
		//BlackboardComp->SetValueAsObject(TEXT("TownHall"), AssignedTown);
	}
}

void ABehaviourTreeAI::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AssignedTown = Cast<ATownHall>(InPawn);

	if (AssignedTown && AssignedTown->BehaviorTree)
	{
		BlackboardComp->InitializeBlackboard(*AssignedTown->BehaviorTree->BlackboardAsset);

		BehaviourComp->StartTree(*AssignedTown->BehaviorTree);
	}
}