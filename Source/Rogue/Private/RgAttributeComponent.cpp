// Fill out your copyright notice in the Description page of Project Settings.


#include "RgAttributeComponent.h"

// Sets default values for this component's properties
URgAttributeComponent::URgAttributeComponent()
{
	Health = 100;
}

bool URgAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	return true;
}


