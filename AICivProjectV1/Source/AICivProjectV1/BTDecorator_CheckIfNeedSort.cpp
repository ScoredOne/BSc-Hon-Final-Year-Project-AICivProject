// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTDecorator_CheckIfNeedSort.h"

UBTDecorator_CheckIfNeedSort::UBTDecorator_CheckIfNeedSort(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Check If Role Needs Sorting";

	BlackboardKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_CheckIfNeedSort, BlackboardKey));
	BlackboardKey.SelectedKeyName = FBlackboard::KeySelf;
}

bool UBTDecorator_CheckIfNeedSort::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ABehaviourTreeAI* MyController = Cast<ABehaviourTreeAI>(OwnerComp.GetAIOwner());
	ATownHall* MyTownHall = Cast<ATownHall>(MyController->GetControlledPawn());

	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	FName Name = FName("WoodPriority");
	uint8 keyid = BlackboardComp->GetKeyID(Name);

	int WoodPri = BlackboardComp->GetValueAsInt(Name);

	if (MyController)
	{
		if (Role >= 0)
		{
			switch (Role)
			{
			case 0:
				if (MyTownHall->AssignedFarmers.Num() < MyTownHall->OwnedFarms.Num() || MyTownHall->FoodRate < 0)
				{
					return true;
				}
				break;
			case 1:
				//if (MyTownHall->AssignedLumberJacks.Num() < WoodPri)
				if (MyTownHall->AssignedLumberJacks.Num() < 1 || MyTownHall->AssignedFarmers.Num() >= MyTownHall->OwnedFarms.Num()) // temp before wood priority
				{
					return true;
				}
				break;
			case 2:
				if (MyTownHall->AssignedMiners.Num() < MyTownHall->AllStoreHouses.Num())
				{
					return true;
				}
				break;
			}
		}
	}

	return false;
}