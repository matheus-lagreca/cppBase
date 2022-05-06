// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnActorExample.generated.h"

UCLASS()
class CPPBASE_API ASpawnActorExample : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnActorExample();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// variable -> allow to choose any type of actor to spawn in the world
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ActorToSpawn;
};