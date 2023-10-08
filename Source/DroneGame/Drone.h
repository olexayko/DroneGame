// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UHealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/MovementComponent.h"
#include "Drone.generated.h"

UCLASS()
class DRONEGAME_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnHpChanged(float NewHp);
	ADrone();

protected:
	void UpdateHUD(float NewHp);
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* MeshComp = nullptr;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp = nullptr;

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* MovementComp = nullptr;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComp = nullptr;

	UPROPERTY(EditAnywhere)
	UArrowComponent* ArrowComp = nullptr;
	
	FVector VelocityForward;
	FVector VelocityRight;
	FVector VelocityUp;
	float RotationPitch;
	float RotationYaw;

	UPROPERTY(EditAnywhere)
	int AmmoAmount = 5;
	
	UPROPERTY(EditAnywhere)
	float VelocityMultiplier = 10000;

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComp;
	
	const FString SkMeshAssetPath = TEXT("/Script/Engine.SkeletalMesh'/Game/VigilanteContent/Vehicles/West_Fighter_F18C/SK_West_Fighter_F18C.SK_West_Fighter_F18C'");
	const FString PhysAssetPath = TEXT("/Script/Engine.PhysicsAsset'/Game/VigilanteContent/Vehicles/West_Fighter_F18C/PHYS_West_Fighter_F18C.PHYS_West_Fighter_F18C'");
	bool bDead = false;
	UWorld* World;

private:
	void MoveUp(float Amount);
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void LookAround(float Amount);
	void LookUp(float Amount);
	void TryFire();
	void Fire();
	
	UFUNCTION()
	void OnDeath();
};
