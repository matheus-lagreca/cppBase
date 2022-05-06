// Fill out your copyright notice in the Description page of Project Settings.


#include "SweepTrace.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USweepTrace::USweepTrace()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USweepTrace::BeginPlay()
{
	Super::BeginPlay();

	TArray<FHitResult> HitResults;

	const FVector Start = GetOwner()->GetActorLocation();
	const FVector End = GetOwner()->GetActorLocation();

	const FCollisionShape ColShape = FCollisionShape::MakeSphere(TraceRadius);
	const bool Hit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_Camera, ColShape);
	
	DrawDebugSphere(GetWorld(), Start, TraceRadius,50, FColor::Orange, true);

	if(Hit)
	{
		// for each HitResult in the array
		for(FHitResult const HitResult : HitResults)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange,
				FString::Printf(TEXT("Hit: %s"), *HitResult.GetActor()->GetName()));
		}
	}
}


// Called every frame
void USweepTrace::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

