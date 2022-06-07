// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InterpComponentExample.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPBASE_API UInterpComponentExample : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInterpComponentExample();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* Parent = nullptr;

	UPROPERTY(EditAnywhere, Category="Interp")
	AActor* TargetActor;
	
	UPROPERTY(EditAnywhere, Category="Interp")
	float InterpSpeed = 3;

	// wait time is for demo only
	UPROPERTY(EditAnywhere, Category="Interp")
	float WaitTime = 3;
	
};
