// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"


static const ECollisionChannel ECC_WeaponFire = ECC_GameTraceChannel1;

AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) // search about this
{
	// try to initialize using the DevEnabled code style...
	RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));

	MuzzleComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("MuzzleComponent"));
	MuzzleComponent->SetupAttachment(RootComponent);
	MuzzleComponent->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));
}

void AWeapon::Fire()
{
	const FTransform MuzzleTransform = MuzzleComponent->GetComponentTransform();
	// trace code
	RunWeaponTrace(MuzzleTransform, 5000.0f);

	// blueprints
	PlayFireEffects();
}

void AWeapon::RunWeaponTrace(const FTransform& MuzzleTransform, float TraceDistance)
{
	const FVector TraceStart = MuzzleTransform.GetLocation();
	const FVector TraceEnd = TraceStart + (MuzzleTransform.GetUnitAxis(EAxis::X) * TraceDistance);
	const FCollisionQueryParams QueryParams(TEXT("WeaponTrace"), false, this);

	FHitResult Hit;
	if(GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_WeaponFire, QueryParams))
	{
		if(IsValid(Hit.GetActor()))
		{
			// 
			const float DamageAmount = 1.0f;
			const FVector ShotFromDirection = (TraceEnd - TraceStart).GetSafeNormal();
			const TSubclassOf<UDamageType> DamageTypeClass = UDamageType::StaticClass();
			const FPointDamageEvent DamageEvent(DamageAmount, Hit, ShotFromDirection, DamageTypeClass);
			Hit.GetActor()->TakeDamage(DamageAmount, DamageEvent, GetInstigatorController(), this);
		}
	}
}
