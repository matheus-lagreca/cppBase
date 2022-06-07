// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRadialForceComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UMyRadialForceComponent::UMyRadialForceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyRadialForceComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<FHitResult> HitArray;
	const FVector Start = this->GetComponentLocation();
	const FVector End = Start;

	const FCollisionShape SphereShape = FCollisionShape::MakeSphere(Radius);

	const bool bSweepHit = GetWorld()->SweepMultiByChannel(HitArray, Start, End,
		FQuat::Identity, ECC_WorldStatic, SphereShape);
	//debug lines
	DrawDebugSphere(GetWorld(), Start, Radius, 50, FColor::Orange, true);

	if(bSweepHit)
	{
		for(const FHitResult HitResult : HitArray)
		{
			UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>((HitResult.GetActor())->GetRootComponent());
			if(MeshComp)
			{
				MeshComp->AddRadialImpulse(Start, Radius, Strength, ERadialImpulseFalloff::RIF_Constant, true);
			}
		}
	}
	
	
}

