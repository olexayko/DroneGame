// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UHealthComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class DRONEGAME_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurret();

	UFUNCTION()
	void OnDeath();

protected:

	virtual void BeginPlay() override;

public:
	void Fire();
	bool IsPlayerNear();
	void TryFire();

	virtual void Tick(float DeltaTime) override;

	const FString MeshAssetPath = TEXT("/Script/Engine.SkeletalMesh'/Game/VigilanteContent/Vehicles/East_Arty_D30122mm/SK_East_Arty_D30122mm.SK_East_Arty_D30122mm'");

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* MeshComp = nullptr;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComp = nullptr;

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComp = nullptr;
	
	UPROPERTY(EditAnywhere)
	float InterpSpeed = 2.0f;

	UPROPERTY(EditAnywhere)
    bool bWorking = true;

	UPROPERTY(EditAnywhere)
	APawn* PlayerPawn;

	UPROPERTY(EditAnywhere)
	double LastFireTime;

	UPROPERTY(EditAnywhere)
	UArrowComponent* ArrowComp;
	
	double FireRadius = 20000;
	UWorld* World;
};
