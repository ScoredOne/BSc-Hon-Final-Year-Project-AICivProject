// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BehaviourTreeAI.h"
#include "TownHall.h"
#include "BTDecorator_CheckBuildReq.generated.h"

/**
 * 
 */
UCLASS()
class AICIVPROJECTV1_API UBTDecorator_CheckBuildReq : public UBTDecorator
{
	GENERATED_UCLASS_BODY()
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	UPROPERTY(EditAnywhere)
		int BuildNum = -1;
};
