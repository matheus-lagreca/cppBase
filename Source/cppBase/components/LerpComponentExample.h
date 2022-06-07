// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LerpComponentExample.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPBASE_API ULerpComponentExample : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULerpComponentExample();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// for demonstration purposes
	UMaterialInterface* Material;
	UMaterialInstanceDynamic* DynamicMaterial;

	float TimeElapsed = 0;
	AActor* Parent = nullptr;
	FVector StartLocation;

	UPROPERTY(VisibleDefaultsOnly, Category="Lerp")
	UStaticMeshComponent* Mesh;

	// make edit widget on editor
	// to changed target location instead of having to set another actor...
	UPROPERTY(EditAnywhere, Category="Lerp", Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, Category="Lerp")
	float LerpDuration = 3;

	// demo
	UPROPERTY(EditAnywhere, Category="Lerp")
	float WaitTime = 3;
};
