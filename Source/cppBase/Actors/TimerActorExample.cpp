// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerActorExample.h"



#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White,String)

// Sets default values
ATimerActorExample::ATimerActorExample()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimerActorExample::BeginPlay()
{
	Super::BeginPlay();

	// Call the TimerFunction every 3 seconds, ensure the timer loops and delay first call for half a second
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATimerActorExample::TimerFunction, 3.0f, true, 0.5f);
}
void ATimerActorExample::TimerFunction()
{
	// Track the number of times we're calling the function
	CallTracker--;
	// if calltracker is zero the print A and clear the timer to stop it from looping, otherwise print B
	CallTracker == 0 ? PrintString("Finished Looping"), GetWorldTimerManager().ClearTimer(TimerHandle) : PrintString("Timer Called");
	// Print the number of loops the tracker has remaining
	PrintString(FString::Printf(TEXT("Calls Remaining: %d"), CallTracker));
}

