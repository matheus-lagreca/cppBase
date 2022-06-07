// Fill out your copyright notice in the Description page of Project Settings.


#include "SweepTraceKismet.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
USweepTraceKismet::USweepTraceKismet()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USweepTraceKismet::BeginPlay()
{
	Super::BeginPlay();

	// Store the start and end locations of the trace, as we`re using the radius of the sphere these can be the same.
	const FVector Start = GetOwner()->GetActorLocation();
	const FVector End = GetOwner()->GetActorLocation();
	// Array of actors to ignore
	TArray<AActor*> ActorsToIgnore;
	// Ignore Self
	ActorsToIgnore.Add(GetOwner());
	// Variable to store the hit information returned from the trace
	TArray<FHitResult> HitArray;

	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), Start, End, TraceRadius,
		UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorsToIgnore,
		EDrawDebugTrace::ForDuration, HitArray, true, FLinearColor::Gray,
		FLinearColor::Blue, 60.0f);

	// If we get a valid hit result, do something

	if(Hit)
	{
		for(const FHitResult HitResult : HitArray)
		{
			// Print information ot the screen about the items we`ve hit
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange,
				FString::Printf(TEXT("Hit: %s"), *HitResult.GetActor()->GetName()));
		}
	}
}


// Called every frame
void USweepTraceKismet::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

