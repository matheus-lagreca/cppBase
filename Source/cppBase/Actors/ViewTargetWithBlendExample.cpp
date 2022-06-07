// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewTargetWithBlendExample.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White,String)


// Sets default values
AViewTargetWithBlendExample::AViewTargetWithBlendExample()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up the overlap box
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	OverlapBox->SetGenerateOverlapEvents(true);
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AViewTargetWithBlendExample::OnOverlapBegin);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &AViewTargetWithBlendExample::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AViewTargetWithBlendExample::BeginPlay()
{
	Super::BeginPlay();
	// store playerController for use later
	PC = UGameplayStatics::GetPlayerController(this, 0);
}

// Called every frame
void AViewTargetWithBlendExample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AViewTargetWithBlendExample::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	// If we have another actor to view through, swap a view target on overlap
	if(ViewTarget)
	{
		// with blend
		PC->SetViewTargetWithBlend(ViewTarget, BlendTime);
		// without blend (immediate transition) or can add blendtime as 0 to have no lerp.
		// PC->SetViewTarget(ViewTarget);
	}
}

void AViewTargetWithBlendExample::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// return view target to the controlled player when leavin the overlap.

	// with leave
	PC->SetViewTargetWithBlend(PC->GetPawn(), BlendTime);
	// without blend
	// PC->SetViewTarget(PC->GetPawn());
}

