// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TownHall.h"
#include "Building.h"
#include "Resource.h"
#include "BehaviourTreeAI.generated.h"

/**
 *
 */
UCLASS()
class AICIVPROJECTV1_API ABehaviourTreeAI : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(transient)
		class UBehaviorTreeComponent* BehaviourComp; // Behaviour Tree Reference

	UPROPERTY(transient)
		class UBlackboardComponent* BlackboardComp; // Blackboard Reference

public:

	ABehaviourTreeAI();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void RefreshInfo();

	UFUNCTION()
		void CallBuild(int BuildingType, int Radius = 0);

	UFUNCTION()
		void SortCitizens(int WoodPriority, int RoleSort = -1); // RoleSort = -1 sort will check all areas are filled
																// 0 = farmers, 1 = lumberjacks, 2 = miners
	UFUNCTION()
		void UpgradeTier(ABuilding* BuildingToUpgrade);

	/* example from site
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGoKey;

	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() { return BotTargetPoints; }
	*/

	UFUNCTION()
		void SetBlackboardTown();

	virtual void Possess(APawn* InPawn) override;

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

protected:

	ATownHall* AssignedTown;

private:
	UPROPERTY()
	bool initialised = false;
};
