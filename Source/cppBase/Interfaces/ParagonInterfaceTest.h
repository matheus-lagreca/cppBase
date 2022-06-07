// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ParagonInterfaceTest.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UParagonInterfaceTest : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CPPBASE_API IParagonInterfaceTest
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void DiePure() = 0;

	UFUNCTION()
	virtual void InteractPure() = 0;

	UFUNCTION()
	virtual void LineAttackPure() = 0;

	UFUNCTION()
	virtual void MoveForward(float Value) = 0;

	UFUNCTION()
	virtual void MoveRight(float Value) = 0;
};
