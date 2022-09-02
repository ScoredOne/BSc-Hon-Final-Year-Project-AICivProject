// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BTService_ResetWoodPriority.h"

UBTService_ResetWoodPriority::UBTService_ResetWoodPriority(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Reset Wood Priority";

	BlackboardKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_ResetWoodPriority, BlackboardKey));
	BlackboardKey.SelectedKeyName = FBlackboard::KeySelf;

	bCreateNodeInstance = true;
}

void UBTService_ResetWoodPriority::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (ensure(BBAsset))
	{
		BlackboardKey.ResolveSelectedKey(*BBAsset);
	}
}

void UBTService_ResetWoodPriority::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltalSeconds)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Service Working");
	// do stuff
}