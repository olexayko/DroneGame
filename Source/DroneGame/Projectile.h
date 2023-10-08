#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class DRONEGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* MovementComp = nullptr;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* MeshComp = nullptr;
	
	const FString MeshAssetPath = TEXT("/Script/Engine.SkeletalMesh'/Game/VigilanteContent/Projectiles/West_Missile_M26/SK_West_Missile_M26.SK_West_Missile_M26'");
	const FString ExplosionAssetPath = TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'");

protected:
	
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComp = nullptr;
	
	virtual void BeginPlay() override;

	

public:
	UPROPERTY(EditAnywhere)
	float SpeedMultiplier = 20000;

	UPROPERTY(EditAnywhere)
	float DamageAmount = 20;
	
	virtual void Tick(float DeltaTime) override;

	void SpawnExplosion();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);
};
