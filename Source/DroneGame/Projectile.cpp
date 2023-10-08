#include "Projectile.h"
#include "Drone.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	
	USkeletalMesh* MeshCompAsset = LoadObject<USkeletalMesh>(nullptr, *MeshAssetPath);
	if (MeshCompAsset)
	{
		MeshComp->SetSkeletalMesh(MeshCompAsset);
	}
	MovementComp->ProjectileGravityScale = 0;
	
	RootComponent = MeshComp;
	
	SetActorScale3D(FVector(8,8,8));
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::SpawnExplosion()
{
	UParticleSystem* ExplosionParticleSystem = LoadObject<UParticleSystem>(nullptr, *ExplosionAssetPath);

	if (ExplosionParticleSystem)
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = FRotator::ZeroRotator;
		
		UParticleSystemComponent* ParticleSystemComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem, SpawnLocation, SpawnRotation);
		
		if (ParticleSystemComponent)
		{
			ParticleSystemComponent->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
			ParticleSystemComponent->bAutoDestroy = true;
		}
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ADrone* Player = Cast<ADrone>(OtherActor);
	if (Player)
	{
		Player->HealthComp->TakeDamage(DamageAmount);
	}

	ATurret* Turret = Cast<ATurret>(OtherActor);
	if (Turret)
	{
		Turret->HealthComp->TakeDamage(DamageAmount);
	}
	SpawnExplosion();
	Destroy();
}





