// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialSwapExample.h"

// Sets default values
AMaterialSwapExample::AMaterialSwapExample()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	MaterialOne = CreateDefaultSubobject<UMaterialInterface>("MaterialOne");
	MaterialTwo = CreateDefaultSubobject<UMaterialInterface>("MaterialTwo");
}

// Called when the game starts or when spawned
void AMaterialSwapExample::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetMaterial(0, bChooseOne ? MaterialOne : MaterialTwo);
	
}


