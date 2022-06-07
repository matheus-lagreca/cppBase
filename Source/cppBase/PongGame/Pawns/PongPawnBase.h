// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "PongPawnBase.generated.h"

UCLASS()
class CPPBASE_API APongPawnBase : public APawn
{
	GENERATED_BODY()
	APongPawnBase* PawnReference;

public:
	// Sets default values for this pawn's properties
	APongPawnBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
// -- FUNCTIONS --
	// INPUT 
	UFUNCTION(BlueprintImplementableEvent, Category="Movement")
	void MoveRight(float MovementSpeed);


	

	// basic Movement
	/** Use floating pawn movement to smooth out motion. */
	UPROPERTY(EditAnywhere)
	class UFloatingPawnMovement* Movement;
	
	// Components
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Collision;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

};

