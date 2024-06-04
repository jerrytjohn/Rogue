// Fill out your copyright notice in the Description page of Project Settings.


#include "RgAiCharacter.h"

// Sets default values
ARgAiCharacter::ARgAiCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARgAiCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARgAiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

