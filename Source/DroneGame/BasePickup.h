// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drone.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

UCLASS()
class DRONEGAME_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

protected:

	UPROPERTY(EditAnywhere)
	USphereComponent* CollisionComp = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;
	float Amplitude = 200.f;
	float Frequency = 3.f;
	float Time = 0.f;
	float BaseZ;

	virtual void BeginPlay() override;
	virtual void GivePickupTo(ADrone* Pawn);
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	FString MeshAssetPath;
	

public:	
	virtual void Tick(float DeltaTime) override;

};
