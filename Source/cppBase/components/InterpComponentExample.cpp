// Fill out your copyright notice in the Description page of Project Settings.


#include "InterpComponentExample.h"

// Sets default values for this component's properties
UInterpComponentExample::UInterpComponentExample()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set the parent to be the owner of the component
	Parent = GetOwner();
}


// Called when the game starts
void UInterpComponentExample::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInterpComponentExample::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Small time delay just to stop it from looking choppy due to lag on load (demo)
	if(WaitTime > 0)
	{
		WaitTime -= DeltaTime;
		return;
	}

	// targetActor should be picked in the editor. Return if that hasn't been set
	if(!TargetActor){return;}

	// interp => speed never changes
	// can chase indefinitely
	Parent->SetActorLocation( 
		FMath::VInterpTo( // vector interpolation to a specific point
			Parent->GetActorLocation(), // current location of the actor, could use get scene component location
			TargetActor->GetTargetLocation(), // destination
			DeltaTime, // 
			InterpSpeed // how fast ?
		));
}

