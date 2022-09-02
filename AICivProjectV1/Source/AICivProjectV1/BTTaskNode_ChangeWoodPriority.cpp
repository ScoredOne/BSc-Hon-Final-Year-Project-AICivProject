// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTTaskNode_ChangeWoodPriority.h"


UBTTaskNode_ChangeWoodPriority::UBTTaskNode_ChangeWoodPriority(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Change Wood Priority";

	BlackboardKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UBTTaskNode_ChangeWoodPriority, BlackboardKey));
	BlackboardKey.SelectedKeyName = FBlackboard::KeySelf;

}

void UBTTaskNode_ChangeWoodPriority::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (bUseSelf)
	{
		BlackboardKey.SelectedKeyName = FBlackboard::KeySelf;
		bUseSelf = false;
	}

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (ensure(BBAsset))
	{
		BlackboardKey.ResolveSelectedKey(*BBAsset);
	}
}

EBTNodeResult::Type UBTTaskNode_ChangeWoodPriority::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	FName Name = FName("WoodPriority");
	uint8 keyid = BlackboardComp->GetKeyID(Name);

	uint32 WoodPri = BlackboardComp->GetValueAsInt(Name);

	if (WoodPri)
	{
		if (WoodPri <= 0)
		{
			WoodPri = 0;
		}
		if (Add)
		{
			WoodPri++;
			BlackboardComp->SetValueAsInt(Name, WoodPri);
			return EBTNodeResult::Succeeded;
		}
		else
		{
			if (WoodPri != 0)
			{
				WoodPri--;
			}
			BlackboardComp->SetValueAsInt(Name, WoodPri);
			return EBTNodeResult::Succeeded;
		}
	}

	//return EBTNodeResult::Failed;
	return EBTNodeResult::Succeeded; // testing without wood priority
}


