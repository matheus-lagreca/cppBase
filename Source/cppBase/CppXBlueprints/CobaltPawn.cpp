// Fill out your copyright notice in the Description page of Project Settings.


#include "CobaltPawn.h"
#include "UObject/ConstructorHelpers.h"


ACobaltPawn::ACobaltPawn(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// try just the Weapon point
	WeaponClass = AWeapon::StaticClass();
}

// Called when the game starts or when spawned
void ACobaltPawn::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponClass != nullptr)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		SpawnInfo.Instigator = this;

		const FTransform SpawnOffset(FQuat::Identity, FVector(0.0f, 15.0f, -15.0f));
		const FTransform SpawnTransform = GetActorTransform() * SpawnOffset;

		Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, SpawnTransform, SpawnInfo);
	}
}


// Called to bind functionality to input
void ACobaltPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("cppxbpFire"), IE_Pressed, this, &ACobaltPawn::OnFirePressed);

}

void ACobaltPawn::OnFirePressed()
{
	if(Weapon)
	{
		Weapon->Fire();
	}
}