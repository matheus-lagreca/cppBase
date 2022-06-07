// Fill out your copyright notice in the Description page of Project Settings.


#include "ATriggerVol.h"
#include "DrawDebugHelpers.h"
#include "Engine/BrushShape.h"

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White,String)

AATriggerVol::AATriggerVol()
{
	//register events
	OnActorBeginOverlap.AddDynamic(this, &AATriggerVol::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AATriggerVol::OnOverlapEnd);
}

void AATriggerVol::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), Brush->Bounds.BoxExtent,
		FColor::Orange, true, -1, 0, 5);
}

// ifs -> there is another actor and its not itself;
void AATriggerVol::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor && (OtherActor != this))
	{
		PrintString("Overlap Begin");
	}
}

void AATriggerVol::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor && (OtherActor != this))
	{
		PrintString("Overlap End");
	}
}

