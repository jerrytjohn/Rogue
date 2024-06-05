// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RgProjectileBase.h"
#include "RgBlackholeProjectile.generated.h"

class URadialForceComponent;
/**
 * 
 */
UCLASS()
class ROGUE_API ARgBlackholeProjectile : public ARgProjectileBase
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, Category= "Teleport")
	float CollapseDelay;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComponent;

	FTimerHandle TimerHandle_CollapseDelay;

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void Explode_Implementation() override;

public:
	ARgBlackholeProjectile();
	

};
