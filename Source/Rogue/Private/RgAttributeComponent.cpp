// Fill out your copyright notice in the Description page of Project Settings.


#include "RgAttributeComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
URgAttributeComponent::URgAttributeComponent()
{
	MaxHealth = 100;
	Health = MaxHealth;
	
}

float URgAttributeComponent::GetHealthFraction() const
{
	return (Health/MaxHealth);
}


bool URgAttributeComponent::IsDead() const
{
	return (Health<=0);
}

bool URgAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(this, nullptr, Health, Delta, GetHealthFraction());
	return true;
}


