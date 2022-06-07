// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "cppBase/Interfaces/ParagonInterfaceTest.h"
#include "GameFramework/Character.h"
#include "ParagonCharacterTest.generated.h"

UCLASS()
class CPPBASE_API AParagonCharacterTest : public ACharacter, public IParagonInterfaceTest
{
private:
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AParagonCharacterTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Interface Functions
	virtual void DiePure() override;
	virtual void InteractPure() override;
	virtual void LineAttackPure() override;
	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;

	// -- FUNCTIONS --
	
	// Check if character is alive
	UFUNCTION(BlueprintCallable, Category="Health")
	virtual bool IsAlive() const;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser) override;
	
	
	// -- PROPERTIES --
	// Health
	UPROPERTY(EditAnywhere, Category="Health")
	float Health = 0;

	UPROPERTY(EditAnywhere, Category="Health")
	float MaxHealth = 100;

	UPROPERTY(EditAnywhere, Category="Health")
	float HealthRegen = 2;
	
	// Mana (or Stamina) 
	UPROPERTY(EditAnywhere, Category="Mana")
	float Mana = 0;

	UPROPERTY(EditAnywhere, Category="Mana")
	float MaxMana = 100;

	UPROPERTY(EditAnywhere, Category="Mana")
	float ManaRegen = 20;

	// TRACE SKILL PROPERTIES
	UPROPERTY(EditAnywhere, Category="Trace")
	float TraceDistance =100.f;

	
// add protected and private later, for testing purposes	
};
