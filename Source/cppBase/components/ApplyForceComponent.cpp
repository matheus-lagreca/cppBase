// Fill out your copyright notice in the Description page of Project Settings.


#include "ApplyForceComponent.h"

// Sets default values for this component's properties
UApplyForceComponent::UApplyForceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UApplyForceComponent::BeginPlay()
{
	Super::BeginPlay();
	MeshComp = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	
}


// Called every frame
void UApplyForceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// its making bp crash, so i disabled it for now
	//const FVector Up = this->GetUpVector();
	//MeshComp-> AddForce(Up * Force * MeshComp->GetMass());
	
}

