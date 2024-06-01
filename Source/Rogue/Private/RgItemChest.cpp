// Fill out your copyright notice in the Description page of Project Settings.


#include "RgItemChest.h"

// Sets default values
ARgItemChest::ARgItemChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 120;
}

// Called when the game starts or when spawned
void ARgItemChest::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARgItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARgItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}