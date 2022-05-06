// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
//here use includes because you will use methods 
#include "Components/CapsuleComponent.h"


// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(RootComponent);

}

void APawnBase::PublicTestFunction()
{
}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	// it will be shown in the events tab
	ImplementableEventVoid();
	// for the bool, it will be shown in the functions tab
	// but you need to right click the tab,
	// then click override function and find the function below.
	ImplementableEventBool();
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int32 APawnBase::SumPure(int32 aValue, int32 bValue)
{
	return aValue + bValue;
}

int32 APawnBase::SumCallable(int32 aValue, int32 bValue)
{
	return aValue + bValue;
}

/* Logs
 types [
 Warning = Yellow
 Error = Red
 Fatal = Makes game crash
 there are more types...
]
TEXT => message
 UE_LOG(LogTemp, type, TEXT("log message"));


 
*/


// Public example
/*
PawnReference->PublicTestFunction();
PawnReference->PublicTestFloat = 140.0f;
*/
// Private Example -> will cause build to fail
/*
PawnReference->PrivateTestFunction();
PawnReference->PrivateTestFloat() = 140.0f;
*/
/*
if(MyInt != 0)
{
	// Do a thing based on MyInt
}
if(MyBool == true)
{
	// Do a thing if a boolean is true.
}
*/
//DemoFunction();
/*
void APawnBase::DemoFunction()
{
}

void APawnBase::PrivateTestFunction()
{
}
*/