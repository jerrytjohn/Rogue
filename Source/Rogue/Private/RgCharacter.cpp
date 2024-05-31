// Fill out your copyright notice in the Description page of Project Settings.


#include "RgCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARgCharacter::ARgCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;		// Turn direction is camera on spring arm direction
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;		// The character physically turns toward their direction of movement

	bUseControllerRotationYaw = false;			// Character can face in one direction, but that direction will not (necessarily) be controller forward
}

// Called when the game starts or when spawned
void ARgCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARgCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(), Value);
}

void ARgCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	// X = Forward
	// Y = Left
	// Z = Up
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, Value);
}

void ARgCharacter::PrimaryAttack()
{
	FVector RightHandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTransform = FTransform(GetControlRotation(), RightHandLocation);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	// Spawn even if you spawn inside something
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
}

// Called every frame
void ARgCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARgCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Inputs that handle player movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ARgCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARgCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Inputs that handle attacks
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ARgCharacter::PrimaryAttack);
}

