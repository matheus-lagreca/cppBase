// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MaterialSwapExample.generated.h"

UCLASS()
class CPPBASE_API AMaterialSwapExample : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaterialSwapExample();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	// Materials to swap between. Interface variant is the same as used on the MeshComponent (parent of the UstaticMeshComponent)
	UPROPERTY(EditAnywhere, Category="Materials")
	UMaterialInterface* MaterialOne;
	UPROPERTY(EditAnywhere, Category="Materials")
	UMaterialInterface* MaterialTwo;


	// Examples of other material types that can be added;
	UPROPERTY(EditAnywhere, Category="Materials")
	UMaterial* Material;
	UPROPERTY(EditAnywhere, Category="Materials")
	UMaterialInstance* MaterialInstance;

	UPROPERTY(EditAnywhere, Category="Materials")
	bool bChooseOne = true;
};
