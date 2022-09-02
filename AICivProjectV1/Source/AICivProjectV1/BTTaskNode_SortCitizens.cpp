// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTTaskNode_SortCitizens.h"

UBTTaskNode_SortCitizens::UBTTaskNode_SortCitizens(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Sort Citizens";

	BlackboardKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UBTTaskNode_SortCitizens, BlackboardKey));
	BlackboardKey.SelectedKeyName = FBlackboard::KeySelf;
}

EBTNodeResult::Type UBTTaskNode_SortCitizens::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	FName Name = FName("WoodPriority");
	uint8 keyid = BlackboardComp->GetKeyID(Name);

	uint32 WoodPri = BlackboardComp->GetValueAsInt(Name);

	ABehaviourTreeAI* MyController = Cast<ABehaviourTreeAI>(OwnerComp.GetAIOwner());
	if (MyController)
	{
		MyController->SortCitizens(WoodPri, SortType);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

