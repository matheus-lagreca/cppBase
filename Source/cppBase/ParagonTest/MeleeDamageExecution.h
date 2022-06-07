// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "MeleeDamageExecution.generated.h"

/**
 * Melee damage execution calculation
 * used for calculating melee damage based on
 * Strength, endurance and weapon damage
 * then applying it to current health
 */
UCLASS()
class CPPBASE_API UMeleeDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	// constructor. sets up the attribute captures need to run the calculation
	UMeleeDamageExecution();

	// Execution implementation. The bulk of this operation is in this function.
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
