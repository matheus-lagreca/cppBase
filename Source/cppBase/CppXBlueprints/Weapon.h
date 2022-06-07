// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class CPPBASE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	// Placed at the end of the weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Component")
	USceneComponent* MuzzleComponent;
	
	// Sets default values for this actor's properties
	AWeapon(const FObjectInitializer& ObjectInitializer);
	void Fire();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Weapon")
	void PlayFireEffects();

private:
	void RunWeaponTrace(const FTransform& MuzzleTransform, float TraceDistance);
};