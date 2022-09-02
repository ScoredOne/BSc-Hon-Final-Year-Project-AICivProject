// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BehaviourTreeAI.h"
#include "BTTaskNode_CheckIfNeedBuilding.generated.h"

/**
 * 
 */
UCLASS()
class AICIVPROJECTV1_API UBTTaskNode_CheckIfNeedBuilding : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere)
		int CheckNum = -1; // -1 = nothing // 0 = Storehouse, 1 = house, 2 = Farm, 3 = Citizen
};
