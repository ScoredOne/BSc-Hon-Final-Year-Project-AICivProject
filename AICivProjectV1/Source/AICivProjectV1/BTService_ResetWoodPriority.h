// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_ResetWoodPriority.generated.h"

/**
 * 
 */
UCLASS()
class AICIVPROJECTV1_API UBTService_ResetWoodPriority : public UBTService
{
	GENERATED_UCLASS_BODY()

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	
	UPROPERTY(EditAnywhere)
	struct FBlackboardKeySelector BlackboardKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltalSeconds) override;
};
