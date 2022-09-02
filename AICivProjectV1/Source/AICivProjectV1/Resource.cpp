// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "Resource.h"


// Sets default values
AResource::AResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetAppearence();
}

// Called when the game starts or when spawned
void AResource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResource::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (TotalResource <= 0)
	{
		Dead = true;
		TotalResource = 0;
	}

	Regenerate();
}

void AResource::Regenerate() // Child Overidable
{
}

void AResource::SetAppearence()
{
}