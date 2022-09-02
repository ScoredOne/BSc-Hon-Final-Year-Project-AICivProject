// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "BTTaskNode_BuildBuilding.h"

UBTTaskNode_BuildBuilding::UBTTaskNode_BuildBuilding(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Building Builder";
}

EBTNodeResult::Type UBTTaskNode_BuildBuilding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABehaviourTreeAI* MyController = Cast<ABehaviourTreeAI>(OwnerComp.GetAIOwner());

	if (MyController)
	{
		if (BuildNum > 0)
		{
			MyController->CallBuild(BuildNum);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

// Decorators, also known as conditionals in other Behavior Tree systems, are attached to either a Composite or a Task node and define whether or not a branch in the tree, or a single node, can be executed.

//Services attach to Composite nodes, and will execute at their defined frequency as long as their branch is being executed. These are often used to make checks and to update the Blackboard.
//These take the place of traditional Parallel nodes in other Behavior Tree systems


