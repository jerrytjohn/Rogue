// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RgProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystemComponent;

UCLASS(Abstract)		// Useful to mark Base classes as abstract. They're intentionally incomplete. Keeps this type out of dropdowns like SpawnActor
class ROGUE_API ARgProjectileBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	UParticleSystem* ImpactVFX;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UProjectileMovementComponent* MoveComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UParticleSystemComponent* EffectComponent;

	UFUNCTION()	
	virtual  void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	virtual  void PostInitializeComponents() override; 
public:	
	// Sets default values for this actor's properties
	ARgProjectileBase();
	

};
