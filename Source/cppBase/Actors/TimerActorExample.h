// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerActorExample.generated.h"

UCLASS()
class CPPBASE_API ATimerActorExample : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimerActorExample();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
		
	int32 CallTracker = 3;

public:	
	void TimerFunction();
	
	FTimerHandle TimerHandle;
};
