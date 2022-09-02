// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "SpectatorCamController.h"

ASpectatorCamController::ASpectatorCamController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ASpectatorCamController::PlayerTick(float DeltaTime) 
{
	Super::PlayerTick(DeltaTime);

}
