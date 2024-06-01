// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RgInteractableInterface.h"
#include "GameFramework/Actor.h"
#include "RgItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ROGUE_API ARgItemChest : public AActor, public IRgInteractableInterface
{
	GENERATED_BODY()

	
	
public:	
	// Sets default values for this actor's properties
	ARgItemChest();

	UPROPERTY(EditAnywhere)
	float TargetPitch;

	void Interact_Implementation(APawn* InstigatorPawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
