// Fill out your copyright notice in the Description page of Project Settings.


#include "LineTraceWorld.h"
#include "DrawDebugHelpers.h"
#include "cppBase/Interfaces/InteractInterface.h"

// Sets default values for this component's properties
ULineTraceWorld::ULineTraceWorld()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULineTraceWorld::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULineTraceWorld::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector Start = GetOwner()->GetActorLocation();
	FVector End = ((GetForwardVector() * TraceDistance)+ Start);
	
	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);
	DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 0.1f);

	if(bHit)
	{
		/*
		 //og log, changed because im using the interface now
		GEngine->AddOnScreenDebugMessage(-1,1,FColor::Orange,
		FString::Printf(TEXT("Trace hit: %s"), *Hit.GetActor()->GetName()));
		*/

		// check hit actor, check the class of that actor,
		// check if it implements the interface, checks if it is interactInterface
		
		// syntax 2 (use this version)
		IInteractInterface* Interface = Cast<IInteractInterface>(Hit.GetActor());
		if(Interface)
		{
			Interface->InteractPure(); // c++
			Interface->Execute_Interact(Hit.GetActor()); // bp
		}
	}
}



// syntax 1 -> interface
/*
if(Hit.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
{
	Cast<IInteractInterface>(Hit.GetActor())->InteractPure(); // c++
	IInteractInterface::Execute_Interact(Hit.GetActor()); // bp
}
*/