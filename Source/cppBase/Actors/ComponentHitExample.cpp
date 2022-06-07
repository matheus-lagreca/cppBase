// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentHitExample.h"

#include "Components/BoxComponent.h"
#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White,String)

// Sets default values
AComponentHitExample::AComponentHitExample()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set up the overlapbox
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	HitBox->OnComponentHit.AddDynamic(this, &AComponentHitExample::OnHit);
}

// Called when the game starts or when spawned
void AComponentHitExample::BeginPlay()
{
	Super::BeginPlay();
}

void AComponentHitExample::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	PrintString(FString::Printf(TEXT("Hit: %s"), *OtherActor->GetName()));
}

