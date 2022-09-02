// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "Tree.h"

void ATree::Regenerate()
{
	if (counter >= RegenTimer) {
		counter = 0;
		TotalResource++;
	}
	else
	{
		counter++;
	}
}

void ATree::SetAppearence()
{

}

void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Regenerate();

	if (TotalResource <= 0)
	{
		this->Destroy();
		Dead = true;
	}
}
