// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "SpectatorCamController.generated.h"

/**
 * 
 */
UCLASS()
class AICIVPROJECTV1_API ASpectatorCamController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASpectatorCamController();

	virtual void PlayerTick(float DeltaTime) override;
	
	
};
