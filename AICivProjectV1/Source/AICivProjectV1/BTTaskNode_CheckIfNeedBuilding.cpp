// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "BTTaskNode_CheckIfNeedBuilding.h"

UBTTaskNode_CheckIfNeedBuilding::UBTTaskNode_CheckIfNeedBuilding(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Check If Needs Building";
}

EBTNodeResult::Type UBTTaskNode_CheckIfNeedBuilding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABehaviourTreeAI* MyController = Cast<ABehaviourTreeAI>(OwnerComp.GetAIOwner());
	ATownHall* MyTownHall = Cast<ATownHall>(MyController->GetControlledPawn());

	if (MyController)
	{
		switch (CheckNum) // 0 = Storehouse, 1 = house, 2 = Farm, 3 = Citizen
		{
		case 0:
			if (MyTownHall->TotalWood > 1000)
			{
				return EBTNodeResult::Succeeded;
			}
			break;
		case 1:
			if (MyTownHall->TotalWood > 500 && MyTownHall->AllCitizens.Num() > MyTownHall->AllHouses.Num() / 4) // *4 accounting pre tier system
			{
				return EBTNodeResult::Succeeded;
			}
			break;
		case 2:
			if (MyTownHall->TotalWood > 500 && MyTownHall->FoodRate < 0)
			{
				return EBTNodeResult::Succeeded;
			}
			break;
		case 3:
			if (MyTownHall->TotalFood > 1000 && MyTownHall->FoodRate > 0)
			{
				return EBTNodeResult::Succeeded;
			}
			break;
		}
	}

	return EBTNodeResult::Failed;
}
