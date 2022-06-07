// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GASDemoAttributeSet.h"
#include "Abilities/GameplayAbility.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GASAbilityDemoCharacter.generated.h"

UCLASS()
class CPPBASE_API AGASAbilityDemoCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess= "true"))
	USpringArmComponent* CameraBoom;

	/** Follow Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess= "true"))
	UCameraComponent* FollowCamera;

public:
	// Sets default values for this character's properties
	AGASAbilityDemoCharacter();

	//** Base turn rate */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	float BaseTurnRate;

	//** base look up rate */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	float BaseLookUpRate;
	
	virtual void BeginPlay() override;

	//Function to bind to Attribute Changed delegate. Calls On Health Changed.
	void OnHealthChangedInternal(const FOnAttributeChangeData & Data);

	//Blueprint-implementable On Health Changed event. Used to send information to the UI about current health.
	UFUNCTION(BlueprintImplementableEvent, Category="Abilities|Attributes")
	void OnHealthChanged(float oldValue, float newValue);
	
	/** return the current health value */
	UFUNCTION(BlueprintPure, Category="Abilities|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintPure, Category="Abilities|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintPure, Category="Abilities|Attributes")
	float GetStrength() const;

	UFUNCTION(BlueprintPure, Category="Abilities|Attributes")
	float GetEndurance() const;

	UFUNCTION(BlueprintPure, Category="Abilities|Attributes")
	float GetBaseDamage() const;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	/** Ability System Interface getter */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}

	/** Grants Ability at given level */
	UFUNCTION(BlueprintCallable, Category="Abilities")
	void GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level, int32 InputCode);

	/** Activates an ability with a matching input code */
	UFUNCTION(BlueprintCallable, Category="Abilities")
	void ActivateAbility(int32 InputCode);

	UFUNCTION(BlueprintCallable, Category="Abilities")
	void CancelAbility(const FGameplayTagContainer CancelWithTags);
protected:

	/** Character Attribute set */
	UPROPERTY()
	const UGASDemoAttributeSet* AttributeSet;

	/** Movement */
	void MoveForward(float Value);
	void MoveRight(float Value);

	/**
	 *Called via input to turn at given rate.
	 * @param Rate This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	 void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
public:
	/** Returns Camera subObject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom;}
	/** Returns followCamera subjobject **/
	FORCEINLINE UCameraComponent* GetFollwoCamera() const { return FollowCamera;}



};
