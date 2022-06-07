// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialDynamicChange.h"

// Sets default values
AMaterialDynamicChange::AMaterialDynamicChange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AMaterialDynamicChange::BeginPlay()
{
	Super::BeginPlay();

	// Get the material in the first slot
	// ** NOTE ** needs to be a material instance. Base Materials will not work.
	Material = Mesh->GetMaterial(0);

	// Make a new Dynamic Material Instance from Material store above. This is why we need a material instance
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);

	// Set the Material slot 0 to be our Dynamic version. This allows runtime changes.
	Mesh->SetMaterial(0, DynamicMaterial);

	// Set the parameters for the Dynamic Material Instance, these will be the names inside of the material/material instance
	DynamicMaterial->SetScalarParameterValue(TEXT("EmissiveStrength"), 50);
	DynamicMaterial-> SetVectorParameterValue(TEXT("Colour"), FLinearColor::Yellow);
}

