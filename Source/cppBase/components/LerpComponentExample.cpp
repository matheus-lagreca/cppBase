// Fill out your copyright notice in the Description page of Project Settings.


#include "LerpComponentExample.h"

// Sets default values for this component's properties
ULerpComponentExample::ULerpComponentExample()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Parent = GetOwner();
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}


// Called when the game starts
void ULerpComponentExample::BeginPlay()
{
	Super::BeginPlay();

	// set start location to component location
	StartLocation = GetComponentLocation();

	// Material setup
	// get material in the first slot
	Material = Mesh->GetMaterial(0);
	// ** NOTE ** Needs to be material instance
	// make a new dynamic material instance from the material stored above.
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	// set the material slot 0 toi be the dynamic version
	Mesh->SetMaterial(0, DynamicMaterial);
	// set material colour before the tick
	DynamicMaterial->SetVectorParameterValue(TEXT("Colour"), FLinearColor::Blue);
	
	
}


// Called every frame
void ULerpComponentExample::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Small Delay just to stop it looking choppy due to lag on load.
	if(WaitTime > 0)
	{
		WaitTime -= DeltaTime;
		return;
	}

	// chase in specific time duration
	if(TimeElapsed < LerpDuration)
	{
		// Move Parent Actor to target location
		Parent->SetActorLocation(FMath::Lerp(StartLocation, TargetLocation, TimeElapsed / LerpDuration ));
		// the other mesh
		DynamicMaterial->SetVectorParameterValue(TEXT("Colour"),FMath::Lerp(FLinearColor::Blue,FLinearColor::Red,TimeElapsed / LerpDuration));
		// Keep track of elapsed time;
		TimeElapsed += DeltaTime;
	}
	
}

