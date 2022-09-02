// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BehaviourTreeAI.h"
#include "BTTaskNode_UpgradeTier.generated.h"

/**
 * 
 */
UCLASS()
class AICIVPROJECTV1_API UBTTaskNode_UpgradeTier : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};
