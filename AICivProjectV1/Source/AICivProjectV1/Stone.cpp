// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "Stone.h"


void AStone::SetAppearence()
{

}


void AStone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TotalResource <= 0)
	{
		this->Destroy();
		Dead = true;
	}
}