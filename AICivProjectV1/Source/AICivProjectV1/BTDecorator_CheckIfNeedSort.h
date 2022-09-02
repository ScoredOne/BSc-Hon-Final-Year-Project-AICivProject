// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BehaviourTreeAI.h"
#include "TownHall.h"
#include "BTDecorator_CheckIfNeedSort.generated.h"

/**
 * 
 */
UCLASS()
class AICIVPROJECTV1_API UBTDecorator_CheckIfNeedSort : public UBTDecorator
{
	GENERATED_UCLASS_BODY()
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	UPROPERTY(EditAnywhere)
		int Role = -1; // -1 = nothing // 0 = Farmers, 1 = Lumberjacks, 2 = Miners

	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector BlackboardKey;
};
