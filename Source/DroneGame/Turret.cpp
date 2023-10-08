#include "Turret.h"
#include "Projectile.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;
	HealthComp = CreateDefaultSubobject<UHealthComponent>("HealthComp");
	HealthComp->OnDeath.AddDynamic(this, &ATurret::OnDeath);
	
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	MeshComp->SetCollisionProfileName("Turret");
	USkeletalMesh* MeshCompAsset = LoadObject<USkeletalMesh>(nullptr, *MeshAssetPath);
	if (MeshCompAsset)
	{
		MeshComp->SetSkeletalMesh(MeshCompAsset);
	}
	
	RootComponent = MeshComp;
	
	ArrowComp = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ArrowComp->SetRelativeLocation(FVector(1000.f, 0,0));

	SetActorRelativeScale3D(FVector(6,6,6));
	SetPivotOffset(FVector(-150,0,50));
}

void ATurret::OnDeath()
{
	Destroy();
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
	World = GetWorld();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}

void ATurret::Fire()
{
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		TSubclassOf<AProjectile> ProjectileClass = AProjectile::StaticClass();
		
		FVector SpawnLocation = ArrowComp->GetComponentLocation();
		FRotator SpawnRotation = ArrowComp->GetComponentRotation(); 
		
		AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
		Projectile->MeshComp->SetCollisionProfileName("TurretProjectile");
		if (Projectile)
		{
			Projectile->MovementComp->Velocity = GetActorForwardVector() * Projectile->SpeedMultiplier;
		}
	}
}

bool ATurret::IsPlayerNear()
{
	return (GetActorLocation() - PlayerPawn->GetActorLocation()).Length() <= FireRadius;
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(World, GetActorLocation(), FireRadius, 30, FColor::Red);
	
	if (bWorking && PlayerPawn && IsPlayerNear())
	{
		FVector TargetLocation = PlayerPawn->GetActorLocation();
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation() - GetPivotOffset(), TargetLocation);
		FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, InterpSpeed);
		
		SetActorRotation(NewRotation);

		if (World->GetTimeSeconds() - LastFireTime >= 4.0f)
		{
			Fire();
			LastFireTime = World->GetTimeSeconds(); 
		}
		
	}
	
}

