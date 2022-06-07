// Fill out your copyright notice in the Description page of Project Settings.


#include "PreProcessor.h"

// just for show, dont define numbers like this add to header
#define PI 3.14159
#define GRAVITY 9.81
// macro to use blueprint like prints
#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White,String)

#if PLATFORM_PS4
// do Playstation stuff
#endif

#if PLATFORM_XBOXONE
// do XBONE stuff
#endif

// Sets default values
APreProcessor::APreProcessor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APreProcessor::BeginPlay()
{
	Super::BeginPlay();
	PrintString("Simple print to thes screen using preprocessor");
	PrintString(FString::Printf(TEXT("Pi = %f"), PI));
	PrintString(FString::Printf(TEXT("Gravity = %f"), GRAVITY));
	
}

// Called every frame
void APreProcessor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

