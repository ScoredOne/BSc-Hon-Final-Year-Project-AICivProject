// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "BTTaskNode_UpgradeTier.h"

UBTTaskNode_UpgradeTier::UBTTaskNode_UpgradeTier(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Upgrade Building Tier";
}

EBTNodeResult::Type UBTTaskNode_UpgradeTier::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{


	return EBTNodeResult::Failed;
}


