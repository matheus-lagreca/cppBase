// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ComponentHitExample.generated.h"

class UBoxComponent;

UCLASS()
class CPPBASE_API AComponentHitExample : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComponentHitExample();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// -- COMPONENTS --
	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* HitBox;
	// -- FUNCTIONS --
	// custom hit functions using the component specifc signatures
	// hit begin function
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
