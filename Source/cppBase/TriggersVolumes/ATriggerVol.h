// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "ATriggerVol.generated.h"


UCLASS()
class CPPBASE_API AATriggerVol : public ATriggerVolume
{
	GENERATED_BODY()

public:
	AATriggerVol();

protected:
	virtual void BeginPlay() override;

private:
	// overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	// overlap end function
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};
