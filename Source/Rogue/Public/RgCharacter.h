// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RgCharacter.generated.h"

class URgAttributeComponent;
class URgInteractionComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ROGUE_API ARgCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Projectiles")
	TSubclassOf<AActor> PrimaryProjectileClass;

	UPROPERTY(EditAnywhere, Category="Projectiles")
	TSubclassOf<AActor> TeleportationProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category="Attack")
	float AttackAnimDelay;
	
	FTimerHandle TimerHandle_PrimaryAttack;
public:
	// Sets default values for this character's properties
	ARgCharacter();

	

protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	URgInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URgAttributeComponent* AttributeComponent;
	
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void PrimaryAttack();
	void PrimaryAttack_Fire();
	void TeleportViaProjectile();
	void TeleportViaProjectile_TimeElapsed();
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void PrimaryInteract();
};
