// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

// on header just forward the class because you wont use methods
class UCapsuleComponent;

UCLASS()
class CPPBASE_API APawnBase : public APawn
{
	GENERATED_BODY()
	APawnBase* PawnReference;
	// if a variable is defined here, it will be private
	
public:
	// Sets default values for this pawn's properties
	// constructor
	APawnBase();

	// Public example
	void PublicTestFunction();
	float PublicTestFloat;

	// Uproperties
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	// Uproperties, visibility and read/write, categories

	// Read only
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	// UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)

	// Write
	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	// UPROPERTY(EditInstanceOnly, BlueprintReadOnly)

	// Categories
	UPROPERTY(EditAnywhere, Category= "Public", BlueprintReadOnly)
	float PublicVisibleFloat = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category= "Public", BlueprintReadWrite)
	float PublicDefaultFloat = 5.0f;
	
	UPROPERTY(EditInstanceOnly, Category= "Public", BlueprintReadOnly)
	float PublicInstanceFloat = 5.0f;

	// Meant to be implemented in BP
	UFUNCTION(BlueprintImplementableEvent)
	void ImplementableEventVoid();
	UFUNCTION(BlueprintImplementableEvent)
	bool ImplementableEventBool();

protected:
	// private but extended classes can modify
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UCapsuleComponent* Capsule;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	int32 MyInt;
	float MyFloat;
	bool MyBool;
	void DemoFunction();
	
	// meta = (AllowPrivateAccess ="true")
	// metadata specifiers, expose variables that you want to see in the editor
	// but also keep it private
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Private", meta = (AllowPrivateAccess ="true"))
	float PrivateVisibleFloat = 15.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Private", meta = (AllowPrivateAccess ="true"))
	float PrivateDefaultFloat = 15.0f;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Private", meta = (AllowPrivateAccess ="true"))
	float PrivateInstanceFloat = 15.0f;
	
	// Private Example 
	void PrivateTestFunction();
	float PrivateTestFloat;

	// UFunction (similar to UProperty)
	// only returns the value
	UFUNCTION(BlueprintPure)
	int32 SumPure(int32 aValue, int32 bValue);

	// has execution pins and target
	UFUNCTION(BlueprintCallable)
	int32 SumCallable(int32 aValue, int32 bValue);


	// basic Movement
	FVector MovementDirection;
	UPROPERTY(EditAnywhere, Category="Movement")
	float MovementSpeed = 500.0f;

	void MoveForward(float Value);
	void MoveRight(float Value);
};
