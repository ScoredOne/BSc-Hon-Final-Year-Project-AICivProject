// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "FiniteStateMachineAI.h"


void AFiniteStateMachineAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	RefreshInfo();
	CheckHealth();
	Run();

	if (Cit->RestingPenalty && !Cit->Resting)
	{
		Cit->RestingPenalty = false;
	}

	if (Cit->Resting)
	{
		if (Cit->Stress <= 0)
		{
			Cit->Resting = false;
			Cit->Stress = 0;
		}
		else
		{
			Cit->Sleeping();
		}
	}

}

void AFiniteStateMachineAI::Work()
{
	// 1 - move to work location, 2 - working, 3 - go to storehouse, 4 - put resources in storehouse, reset
	Cit->Resting = false;

	if (Role != Cit->CurrentRole) // if citizens role is changed
	{
		ResetWork();
		Role = Cit->CurrentRole;
		return;
	}

	if (!Stage1) // FIRST CHECK START
	{
		Stage1Work();
	}
	else 
	{
		if (!Stage2) { // resets stage1 back to false if fails (double chack), once task is done then stop
			Stage1Work(); 
		}

		if (Stage1) // END FIRST CHECK
		{
			if (!Stage2) // START SECOND CHECK
			{
				Stage2Work();
			}
			else // END SECOND CHECK
			{
				if (!Stage3) // START THIRD CHECK
				{
					Stage3Work();
				}
				else
				{
					if (!Stage4) // resets stage3 back to false if fails (double chack)
					{
						Stage3Work();
					}
					if (Stage3) // END THIRD CHECK
					{
						Stage4Work();
						if (Stage4)
						{
							ResetWork();
						}
					}
				}
			}
		}
	}
}

void AFiniteStateMachineAI::Stage1Work() // Checks citizen is at the work location
{
	if (Role == 1) // Farmers and gatheres
	{
		if (!Cit->AssignedFarm)
		{
			Cit->AssignedFarm = Cit->MyTownHall->GetUnassignedFarm();
			if (Cit->AssignedFarm)
			{
				Cit->AssignedFarm->WorkingCitizen = Cit;
			}
		}
		else if (Cit != Cit->AssignedFarm->WorkingCitizen)
		{
			Cit->AssignedFarm = Cit->MyTownHall->GetUnassignedFarm();
			if (Cit->AssignedFarm)
			{
				Cit->AssignedFarm->WorkingCitizen = Cit;
			}
		}
		else
		{
			Stage1 = GoToLocation(Cit->AssignedFarm->GetActorLocation());
		}
	}
	else if (Role == 2)
	{
		if (!Cit->TargetTree)
		{
			Cit->TargetTree = Cit->MyTownHall->GetClosestTree();
		}
		else if (Cit->TargetTree->Dead)
		{
			Cit->TargetTree = Cit->MyTownHall->GetClosestTree();
		}
		else
		{
			Stage1 = GoToLocation(Cit->TargetTree->GetActorLocation());
		}
	}
	else if (Role == 3)
	{
		if (!Cit->TargetStone)
		{
			Cit->TargetStone = Cit->MyTownHall->GetClosestStone();
		}
		else if (Cit->TargetStone->Dead)
		{
			Cit->TargetStone = Cit->MyTownHall->GetClosestStone();
		}
		else 
		{
			Stage1 = GoToLocation(Cit->TargetStone->GetActorLocation());
		}
	}
	else
	{
		//Stage1 = GoToLocation(Cit->TargetBuilding->GetActorLocation()); // currently pointless...
	}
}

void AFiniteStateMachineAI::Stage2Work()
{

	switch (Role)
	{
	case 1: // Farm //////////////////////////////////////
		if (Cit->ResourceType != 1)
		{
			if (Cit->NumResources > 0)
			{
				Cit->DropResources();
			}
			Cit->ResourceType = 1;
		}

		Cit->AssignedFarm->Worker = true;

		if (Cit->NumResources >= Cit->CarryWeight)
		{
			Stage2 = true;
			Cit->AssignedFarm->Worker = false;
		}
		else
		{
			if (Stage1)
			{
				// work farm
				Cit->DoTask(1);
			}
		}

		break;
	case 2: // Lumberjack ///////////////////////////////
		if (Cit->ResourceType != 2)
		{
			if (Cit->NumResources > 0)
			{
				Cit->DropResources();
			}
			Cit->ResourceType = 2;
		}
		if (Cit->NumResources >= Cit->CarryWeight)
		{
			Stage2 = true;
		}
		else
		{
			if (Stage1)
			{
				// take wood
				Cit->DoTask(2);
			}
		}
		break;
	case 3: // Miner ////////////////////////////////////
		if (Cit->ResourceType != 3)
		{
			if (Cit->NumResources > 0)
			{
				Cit->DropResources();
			}
			Cit->ResourceType = 3;
		}
		if (Cit->NumResources >= Cit->CarryWeight)
		{
			Stage2 = true;
		}
		else
		{
			if (Stage1)
			{
				// take stone
				Cit->DoTask(3);
			}
		}

		break;
	case 4: // currently dropped resource gatherer ////
		// if carried resources = 0
		// get resource of anytype else get one of the same type #done before this is called#
		// pick up resources #DoTask based on resource type#
		break;
	}
}

void AFiniteStateMachineAI::Stage3Work() // go to storehouse
{
	Cit->TargetStoreHouse = Cit->MyTownHall->GetAvailableStoreHouse(Role);
	if (Cit->TargetStoreHouse == nullptr)
	{
		Cit->DropResources();
		ResetWork();
	}
	else
	{
		Stage3 = GoToLocation(Cit->TargetStoreHouse->GetActorLocation());
	}
}

void AFiniteStateMachineAI::Stage4Work() // drop off resources
{
	if (Stage3)
	{
		Cit->DoTask(4);
	}
	if (Cit->NumResources <= 0)
	{
		Cit->NumResources = 0;
		Stage4 = true;
	}
}

void AFiniteStateMachineAI::ResetWork()
{
	Stage1 = false;
	Stage2 = false;
	Stage3 = false;
	Stage4 = false;

	if (Cit->AssignedFarm)
	{
		if (Cit->AssignedFarm->WorkingCitizen == Cit)
		{
			Cit->AssignedFarm->Worker = false;
		}
		else
		{
			Cit->AssignedFarm = nullptr;
		}
	}

	if (Cit->NumResources > 0)
	{
		Cit->DropResources();
	}
}

//////

void AFiniteStateMachineAI::Idle()
{

}

void AFiniteStateMachineAI::Run()
{
	switch (State)
	{
	case 0:
		Cit->Working = true;
		Cit->Resting = false;
		Work();
		break;
	case 1:
		Cit->Working = false;
		GoRest();
		break;
	case 2:
		Cit->Working = false;
		Cit->Resting = false;
		GoEat();
		break;
	}
}

void AFiniteStateMachineAI::GoEat()
{
	if (Cit->Home)
	{
		if (Cit->Home->HousedFood > 0)
		{
			if (GoToLocation(Cit->Home->GetActorLocation()))
			{
				Cit->AtHome = true;
			}
			Cit->DoTask(5);
			// eat
		}
	}
	else
	{
		for (const auto& Itr : Cit->MyTownHall->AllStoreHouses)
		{
			if (Itr->HousedFood > 0)
			{
				Cit->TargetBuilding = Itr;
				break;
			}
		}
		if (GoToLocation(Cit->TargetBuilding->GetActorLocation()))
		{
			Cit->DoTask(5, true);
			// Eat from storehouse
		}
	}
	if (Cit->Hunger < 10)
	{
		State = 0;
	}
}

void AFiniteStateMachineAI::GoRest()
{
	if (Cit->Home)
	{
		if (Cit->AtHome)
		{
			Cit->Resting = true;
			Cit->EnterHome();
		}
		else
		{
			if (GoToLocation(Cit->Home->GetActorLocation()))
			{
				Cit->AtHome = true;
			}
		}
	}
	else
	{
		Cit->MyTownHall->AssignHousing(Cit);
		if (!Cit->Home)
		{
			Cit->RestingPenalty = true;
			Cit->Resting = true;
		}
	}

	if (Cit->Stress < 10)
	{
		Cit->LeaveHome();
		State = 0;
	}
}

void AFiniteStateMachineAI::CheckHealth()
{
	if (Cit->Hunger > Cit->HungerThreshold)
	{
		State = 2;
		//GEngine->AddOnScreenDebugMessage(-1, 0.3, FColor::Red, FString::FromInt(Cit->Hunger));
		GEngine->AddOnScreenDebugMessage(-1, 0.3, FColor::Red, TEXT("HUNGRY!"));
	}
	else if (Cit->Stress > Cit->StressThreshold)
	{
		State = 1;
	}
}

void AFiniteStateMachineAI::RefreshInfo()
{
	if (this->GetPawn()) 
	{
		Cit = Cast<ACitizenBody>(this->GetPawn());
	}
}

bool AFiniteStateMachineAI::GoToLocation(FVector Destination)
{
	bool AtLocation;

	if (FVector::Dist(Destination, Cit->GetActorLocation()) < 450) // Checks if within a reasonable area
	{
		AtLocation = true;
		Super::StopMovement();
	}
	else
	{
		// Because the NavMesh is dynamic it needs a valid move point on the mesh itself
		
		FNavLocation RandomPointResult;
		UNavigationSystem* NavSystem = UNavigationSystem::GetCurrent(GetWorld());
		NavSystem->GetRandomReachablePointInRadius(Destination, 400, RandomPointResult);

		MoveToLocation(Destination, 10);
		AtLocation = false;

	}
	return AtLocation;
}