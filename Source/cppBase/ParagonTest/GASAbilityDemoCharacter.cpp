// Fill out your copyright notice in the Description page of Project Settings.


#include "GASAbilityDemoCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"
#include "GASDemoAttributeSet.h"

// Sets default values
AGASAbilityDemoCharacter::AGASAbilityDemoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// dont rotate when the controller rotates. let that just affect the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Config char movement
	GetCharacterMovement()->bOrientRotationToMovement = true;// char moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// create a camera that boom (pulls in towards the player if the is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true; // rotate the arm based on the controller

	// create follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// AKA add the mesh and animbp vfx and shit all on bluepritns 

	// Add the Ability System Component to the character.
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));


}


void AGASAbilityDemoCharacter::CancelAbility(const FGameplayTagContainer CancelWithTags)
{
	// The Ability System Component has multiple ways of cancelling and activating abilities.
	// Using tags provides a generic means of categorizing different types of abilities
	// without knowing what specific ability is active.

	AbilitySystemComponent->CancelAbilities(&CancelWithTags);

}

// Called when the game starts or when spawned
void AGASAbilityDemoCharacter::BeginPlay()
{
	Super::BeginPlay();

	// initializes the attribute set using a data table.
	if (IsValid(AbilitySystemComponent))
	{
		AttributeSet = AbilitySystemComponent->GetSet<UGASDemoAttributeSet>();
		
		//GetGameplayAttributeValueChangedDelegate will enable you to bind delegates without programming them manually.
		// it will not autocomplete the GetHealthAttribute func bc its auto generated
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			AttributeSet->GetHealthAttribute())
		.AddUObject(this, &AGASAbilityDemoCharacter::OnHealthChangedInternal);
	}
}

void AGASAbilityDemoCharacter::OnHealthChangedInternal(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.OldValue, Data.NewValue);
}


float AGASAbilityDemoCharacter::GetHealth() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetHealth();
	}
	return -1.0f;
}

float AGASAbilityDemoCharacter::GetMaxHealth() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetMaxHealth();
	}
	return 0.0f;
}

float AGASAbilityDemoCharacter::GetStrength() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetStrength();
	}

	return 0.0f;
}

float AGASAbilityDemoCharacter::GetEndurance() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetEndurance();
	}

	return 0.0f;
}

float AGASAbilityDemoCharacter::GetBaseDamage() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetWeaponDamage();
	}

	return 0.0f;
}

// create an instance of an Ability and add it to the Ability System Comp
void AGASAbilityDemoCharacter::GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level, int32 InputCode)
{
	if (GetLocalRole() == ROLE_Authority && IsValid(AbilitySystemComponent) && IsValid(AbilityClass))
	{
		UGameplayAbility* Ability = AbilityClass->GetDefaultObject<UGameplayAbility>();
		if(IsValid(Ability))
		{
			// create the new ability spec struct.
			// Ability specs contain metadata about the ability
			// level and reference to the ability
			FGameplayAbilitySpec AbilitySpec(
				Ability,
				Level,
				InputCode
				);
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
}

void AGASAbilityDemoCharacter::ActivateAbility(int32 InputCode)
{
	if(IsValid(AbilitySystemComponent))
	{
		// alter this to work with Enhanced input
		AbilitySystemComponent->AbilityLocalInputPressed(InputCode);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/// inputs
// Called to bind functionality to input
void AGASAbilityDemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	// alter this to enhanced input
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("GASMoveForward", this, &AGASAbilityDemoCharacter::MoveForward);
	PlayerInputComponent->BindAxis("GASMoveRight", this, &AGASAbilityDemoCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("GASTurn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("GASTurnRate", this, &AGASAbilityDemoCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("GASLookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("GASLookUpRate", this, &AGASAbilityDemoCharacter::LookUpAtRate);
}



void AGASAbilityDemoCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGASAbilityDemoCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AGASAbilityDemoCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGASAbilityDemoCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

