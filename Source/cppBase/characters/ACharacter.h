// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "cppBase/Interfaces/InteractInterface.h"
#include "GameFramework/Character.h"
#include "ACharacter.generated.h"

// added public IInteractInterface (first I is for interface (unreal stuff));
UCLASS()
class CPPBASE_API AACharacter : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AACharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Interface functions (must add all of them)
	void Interact_Implementation() override; // Also Include bp function

	virtual void InteractPure() override; // c++ only func
private:
	// INPUT FUNCTIONS
	UFUNCTION()
	void MoveForward(float Value);
	UFUNCTION()
	void MoveRight(float Value);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;
	
	// Properties
	float Health = 0;
	float DefaultHealth = 100;
};

