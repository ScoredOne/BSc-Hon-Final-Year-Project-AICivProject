// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "AICivProjectV1GameMode.h"
#include "SpectatorCamController.h"
#include "SpectatorCamera.h"

AAICivProjectV1GameMode::AAICivProjectV1GameMode()
{
	DefaultPawnClass = ASpectatorCamera::StaticClass();
	PlayerControllerClass = ASpectatorCamController::StaticClass();
}


