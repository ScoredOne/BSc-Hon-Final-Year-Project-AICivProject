// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "CitizenBody.h"
#include "FiniteStateMachineAI.h"


// Sets default values
ACitizenBody::ACitizenBody()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AFiniteStateMachineAI::StaticClass();

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CheckEStopStatus();

	StressDamage();
	HungerDamage();


	if (NumResources <= 0 && CurrentRole != 1 && CurrentRole != 2 && CurrentRole != 3)
	{
		NumResources = 0;
		ResourceType = 0;
	}
}

// Called when the game starts or when spawned
void ACitizenBody::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACitizenBody::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	StressDamage();
	HungerDamage();

	if (EmergencyStopActive)
	{
		CheckEStopStatus();
	}


}

// Called to bind functionality to input
void ACitizenBody::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	
}

/////////////////////////////////////////////////////////////////////////////////////

void ACitizenBody::DoTask(int ToDo, bool AtStoreHouse)
{
	switch (ToDo)
	{
	case 0: // unassigned
		break;
	case 1: // Farmer
		if (AssignedFarm->HarvestReady)
		{
			if (AssignedFarm->TotalResource > 0 && NumResources < CarryWeight)
			{
				AssignedFarm->TotalResource--;
				NumResources++;
			}
		}
		break;
	case 2: // Lumberjack
		if (TargetTree->TotalResource > 0 && NumResources < CarryWeight)
		{
			TargetTree->TotalResource--;
			NumResources++;
		}
		break;
	case 3: // Miner
		if (TargetStone->TotalResource > 0 && NumResources < CarryWeight)
		{
			TargetStone->TotalResource--;
			NumResources++;
		}
		break;
	case 4: // put stuff in storehouse
		if (ResourceType == 1)
		{
			if (TargetStoreHouse->HousedFood < TargetStoreHouse->MaxFood)
			{
				NumResources--;
				TargetStoreHouse->HousedFood++;
			}
		}
		else if (ResourceType == 2)
		{
			if (TargetStoreHouse->HousedWood < TargetStoreHouse->MaxWood)
			{
				NumResources--;
				TargetStoreHouse->HousedWood++;
			}
		}
		else if (ResourceType == 3)
		{
			if (TargetStoreHouse->HousedStone < TargetStoreHouse->MaxStone)
			{
				NumResources--;
				TargetStoreHouse->HousedStone++;
			}
		}
		break;
	case 5: // eat from storehouse
		if (AtHome && Home->HousedFood > 0)
		{
			Home->HousedFood--;
			Hunger--;
		}
		else if (TargetStoreHouse->HousedFood > 0 && AtStoreHouse)
		{
			TargetStoreHouse->HousedFood--;
			Hunger--;
		}
		break;
	case 6: // Refill house with food

		break;
	}
}

void ACitizenBody::Sleeping()
{
	if (!RestingPenalty) { // No House
		if (restTick < 4)
		{
			restTick++;
		}
		else
		{
			Stress--;
			restTick = 0;
		}
	}
	else
	{
		Stress--;
		if (restTick < 10)
		{
			restTick++;
		}
		else
		{
			Health++;
			restTick = 0;
		}
	}
}

void ACitizenBody::Eating()
{
	Hunger--;
	// then take away from source of food
}

void ACitizenBody::StressDamage()
{
	if (Stress >= 70) 
	{
		if (Stress >= 80)
		{
			if (Stress >= 90)
			{
				if (Stress >= 100) {
					EmergencyStop();
					Stress = 100;
					Health--;
				}
				Health--;
			}
			Health--;
		}
		Health--;
	}
	// 70% -> 80% -> 90% -> 100%
	if (Working)
	{
		if (StressTimer < 45)
		{
			StressTimer++;
		}
		else
		{
			Stress++;
			StressTimer = 0;
		}
	}

}

void ACitizenBody::HungerDamage()
{
	if (Hunger >= 70)
	{
		if (Hunger >= 80)
		{
			if (Hunger >= 90)
			{
				if (Hunger >= 100) {
					EmergencyStop();
					Hunger = 100;
					Health--;
				}
				Health--;
			}
			Health--;
		}
		Health--;
	}
	// 70% -> 80% -> 90% -> 100%

	if (HungerTimer < 75)
	{
		HungerTimer++;
	}
	else
	{
		Hunger++;
		HungerTimer = 0;
	}
}

void ACitizenBody::CalculateWellbeing() // do later
{

}

void ACitizenBody::EnterHome()
{
	AtHome = true;
	RestingPenalty = false;
	this->SetActorHiddenInGame(true);
}

void ACitizenBody::LeaveHome()
{
	AtHome = false;
	this->SetActorHiddenInGame(false);
}

void ACitizenBody::DropResources() // possibly broken
{
	// Current Resource amount + type, create Resource of stats 
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = this;
	FTransform SpawnTransform = GetTransform();
	SpawnTransform.SetLocation(GetActorForwardVector());
	AResource* DropResources = GetWorld()->SpawnActor<AResource>(DropStuff, SpawnTransform, SpawnParameters);
	DropResources->TotalResource = NumResources;
	DropResources->ResourceType = ResourceType;
	NumResources = 0;
	ResourceType = 0;
}

void ACitizenBody::EmergencyStop()
{
	EmergencyStopActive = true;
}

void ACitizenBody::CheckEStopStatus()
{
	if (Stress <= 10 && Hunger <= 10)
	{
		EmergencyStopActive = false;
	}
}

void ACitizenBody::ConfirmPartner()
{
	if (this->Partner == NULL){} // no need to do anything
	else if (this->Partner != this->Partner->Partner) // if first if fails do check
	{
		this->Partner = NULL;
	}
}