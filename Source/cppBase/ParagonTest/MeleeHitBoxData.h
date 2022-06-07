// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MeleeHitBoxData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FMEleeHitSphereDefinition
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName Nickname;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FVector Offset;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Radius;
	
};

UCLASS(BlueprintType)
class CPPBASE_API UMeleeHitBoxData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FMEleeHitSphereDefinition> MeleeHitSpheres;

	UFUNCTION(BlueprintPure)
	TArray<FMEleeHitSphereDefinition> GetMeleeHitSpheres(TArray<int> indexes);
	
};
