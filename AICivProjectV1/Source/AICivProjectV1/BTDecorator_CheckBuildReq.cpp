// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "BTDecorator_CheckBuildReq.h"

UBTDecorator_CheckBuildReq::UBTDecorator_CheckBuildReq(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Check Building Requirements";
}

bool UBTDecorator_CheckBuildReq::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ABehaviourTreeAI* MyController = Cast<ABehaviourTreeAI>(OwnerComp.GetAIOwner());
	ATownHall* MyTownHall = Cast<ATownHall>(MyController->GetControlledPawn());
	if (MyController)
	{
		if (BuildNum >= 0)
		{
			switch (BuildNum)
			{
			case 0:
				if (MyTownHall->TotalWood >= 1000)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;
			case 1:
				if (MyTownHall->TotalWood >= 500)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;
			case 2:
				if (MyTownHall->TotalWood >= 500)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;
			case 3:
				if (MyTownHall->TotalFood >= 1000)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;
			}
		}
	}

	return false;
}

