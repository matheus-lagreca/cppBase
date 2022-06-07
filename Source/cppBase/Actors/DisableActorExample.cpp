// Fill out your copyright notice in the Description page of Project Settings.


#include "DisableActorExample.h"
#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White,String)

// Sets default values
ADisableActorExample::ADisableActorExample()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//set to false
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADisableActorExample::BeginPlay()
{
	Super::BeginPlay();
	// set whether we should override the tick being toggled in the SetActive.
	// for cases where tick maybe fuill disabled and toggling setactive would re-enable tick unintentionally
	bOverrideTick = !PrimaryActorTick.bCanEverTick;
	// debugging test. if autodisable then demonstrate fucnction on begin play
	if(bAutoDisable)
	{
		SetActive(false);
	}
}

// Called every frame
void ADisableActorExample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PrintString("Tick");

}

void ADisableActorExample::SetActive(bool Active)
{
	// control tick
	// if were overriding it based on bCanEverTick being set to the false ( we never want thid class to tick)
	// then override the SetActorTickEnable to not use Active and always default to == false
	if(bOverrideTick)
	{
		SetActorTickEnabled(false);
	}
	else
	{
		SetActorTickEnabled(Active);
	}
	// Control visibility. remember to invert as this is a default false value.
	SetActorHiddenInGame(!Active);
	// control collision
	SetActorEnableCollision(Active);
}

