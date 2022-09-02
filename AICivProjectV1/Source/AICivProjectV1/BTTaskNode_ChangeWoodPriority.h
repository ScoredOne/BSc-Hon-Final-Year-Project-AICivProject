// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_ChangeWoodPriority.generated.h"

/**
 * 
 */
UCLASS()
class AICIVPROJECTV1_API UBTTaskNode_ChangeWoodPriority : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()
	
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector BlackboardKey;

	UPROPERTY(EditAnywhere)
		bool Add = true;

	UPROPERTY()
		uint32 bUseSelf : 1;
	
	
};
