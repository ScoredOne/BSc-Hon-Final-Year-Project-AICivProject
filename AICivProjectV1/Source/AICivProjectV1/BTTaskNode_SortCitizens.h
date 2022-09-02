// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BehaviourTreeAI.h"
#include "BTTaskNode_SortCitizens.generated.h"

/**
 * 
 */
UCLASS()
class AICIVPROJECTV1_API UBTTaskNode_SortCitizens : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector BlackboardKey;

	UPROPERTY(EditAnywhere)
		int SortType = -1; // -1 = Sort all, 0 = Farmers, 1 = Lumberjacks, 2 = Miners
};
