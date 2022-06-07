// Fill out your copyright notice in the Description page of Project Settings.


#include "ParagonCharacterTest.h"
#include "DrawDebugHelpers.h"
#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White,String)

// Sets default values
AParagonCharacterTest::AParagonCharacterTest()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Default stats
	Health = MaxHealth;
	Mana = MaxMana;
}

// Called when the game starts or when spawned
void AParagonCharacterTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParagonCharacterTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AParagonCharacterTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up the player controller
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AParagonCharacterTest::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AParagonCharacterTest::MoveRight);

	// bind jumping to regular UE Jump
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AParagonCharacterTest::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AParagonCharacterTest::StopJumping);

	// Bind OtherButtons
	PlayerInputComponent->BindAction(TEXT("InteractButtonTest"), IE_Pressed, this, &AParagonCharacterTest::InteractPure);
	PlayerInputComponent->BindAction(TEXT("LineTraceAttackTest"), IE_Pressed, this, &AParagonCharacterTest::LineAttackPure);
}


void AParagonCharacterTest::DiePure()
{
	// do something when character health reaches 0
}

void AParagonCharacterTest::InteractPure()
{
	// do something when character interacts with something
	// does the same as LineAttack but without animation, projectile or vfx,
	// cost no mana

	//InteractButtonTest
	
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = ((GetActorForwardVector() * TraceDistance)+ Start);

	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 3.0f);

	if(bHit)
	{
		// Print, call another method in cpp, or use an interface for cpp or bp
		// for now only printing
		PrintString(TEXT("Interact with something"));
	}
}

void AParagonCharacterTest::LineAttackPure()
{
	// create a line in front of the character that hits and prints
	// uses mana on use, cannot attack if out of mana
	// add animation, projectile and vfx

	// LineTraceAttackTest
	if(Mana <= 0)
	{
		PrintString(TEXT("No Mana"));
		return;
	}
	Mana = Mana-25;
	
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = ((GetActorForwardVector() * TraceDistance)+ Start);

	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);
	DrawDebugLine(GetWorld(), Start, End, FColor::Purple, false, 3.0f);

	if(bHit)
	{
		// Print, call another method in cpp, or use an interface for cpp or bp
		// for now only printing
		PrintString(TEXT("Hit something"));
	}

	// add later things below
	// anim on bp
	// vfx on bp
}

void AParagonCharacterTest::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AParagonCharacterTest::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

bool AParagonCharacterTest::IsAlive() const
{
	// if health less or equals 0 then return is dead else return is alive
	return Health <= 0 ? false : true;
}

float AParagonCharacterTest::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	// if its dead then do nothing
	if(!this->IsAlive()){ return Health; }

	// reduce health
	Health -= DamageAmount;
	PrintString(FString::Printf(TEXT("Health: %f"), Health));

	if(!this->IsAlive()){ PrintString(TEXT("YOU DIED")); }

	return DamageAmount;
}

