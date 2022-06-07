// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeDamageExecution.h"

#include <execution>

#include "GASDemoAttributeSet.h"
#include "AbilitySystemComponent.h"

// Helper struct for fetching the stats necessary for the melee calculation
struct FMeleeDamageStatics
{
	// Capture declarations for attributes;
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Endurance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(WeaponDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);

	// Default constructor
	FMeleeDamageStatics()
	{
		// Capturedef Definitions for the attributes.

		// Strength and weapon damage form the source of the gameplay Effect running this calculation
		// Snapshoted at the moment the calculation is made
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASDemoAttributeSet, Strength, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASDemoAttributeSet, WeaponDamage, Source, true);

		// Endurance and health from the target of the gameplay effect using this calculation
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASDemoAttributeSet, Endurance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASDemoAttributeSet, Health, Source, false);
	}
};

// Static helper function to quickly fetch the melee damage attributes
static const FMeleeDamageStatics& MeleeDamageStatics()
{
	static FMeleeDamageStatics DmgStatics;
	return DmgStatics;
}

// Constructor for the melee damage execution. we capture only the attributes used to make the calculation,
// not the healtha ttribute itself. we apply that at the end of the execution

UMeleeDamageExecution::UMeleeDamageExecution()
{
	RelevantAttributesToCapture.Add(MeleeDamageStatics().EnduranceDef);
	RelevantAttributesToCapture.Add(MeleeDamageStatics().StrengthDef);
	RelevantAttributesToCapture.Add(MeleeDamageStatics().WeaponDamageDef);
}

// Main implementation for this execution
void UMeleeDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// Step 1:
	// obtain references to the target and source ability system component
	// each copy of a gameplay effect will have one of each

	UAbilitySystemComponent* TargetABSC = ExecutionParams.GetTargetAbilitySystemComponent();
	AActor* TargetActor = TargetABSC ? TargetABSC->GetAvatarActor() : nullptr;

	UAbilitySystemComponent* SourceABSC = ExecutionParams.GetSourceAbilitySystemComponent();
	AActor* SourceActor = SourceABSC ? SourceABSC->GetAvatarActor() : nullptr;

	// Get the owning gameplay effect spec so that you can use its variables and tags
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Aggregator Eavluate Parameters used during the attribute capture
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	//------------------------------------------------------------------------------------
	// Capturing the weapon damage
	float BaseDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		MeleeDamageStatics().WeaponDamageDef, EvaluationParameters, BaseDamage);

	// Capturing Endurance
	float Endurance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		MeleeDamageStatics().EnduranceDef, EvaluationParameters, Endurance);

	// defense will at minimum be 1.
	if (Endurance <= 1.0f)
	{
		Endurance = 1.0f;
	}

	// Capturing Strength
	float Strength = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		MeleeDamageStatics().StrengthDef, EvaluationParameters, Strength);

	// performing the actual damage calculation. final damage done = damage * attack power /endurance
	float DamageDone = BaseDamage + (Strength / Endurance);

	// we floor damage at 1
	if (DamageDone <= 0.f)
	{
		DamageDone = 1.0f;
	}

	// Final execution output. we can add more than one AddOutputModifier to  change multiple parameters at
	// a time based on more complicated calculations. Here we apply damage -DamageDone
	// to health. Health itself is clamped in the attributeSet
	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(MeleeDamageStatics()
			.HealthProperty, EGameplayModOp::Additive, -DamageDone));
	

}

