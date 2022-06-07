// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ViewTargetWithBlendExample.generated.h"
class UBoxComponent;

UCLASS()
class CPPBASE_API AViewTargetWithBlendExample : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AViewTargetWithBlendExample();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// -- COMPONENTS --
	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* OverlapBox;
	
	// -- VARIABLES --
	UPROPERTY(EditAnywhere, Category="ViewTarget")
	AActor* ViewTarget = nullptr;
	UPROPERTY(EditAnywhere, Category="ViewTarget")
	float BlendTime = 1.0f;
	APlayerController* PC;

	// -- FUNCTIONS --
	// overlap with begin function
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	// overlap with end function
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
