#include "Drone.h"
#include "DroneHUD.h"
#include "Projectile.h"
#include "Turret.h"
#include "UHealthComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

ADrone::ADrone()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	MeshComp->SetCollisionProfileName("Drone");
	MeshComp->SetGenerateOverlapEvents(true);
	RootComponent = MeshComp;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->bUsePawnControlRotation = false;
	
	MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

	ArrowComp = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComp->ArrowSize = 5.0f;
	ArrowComp->SetupAttachment(GetDefaultAttachComponent());
	ArrowComp->SetRelativeLocation(FVector(1500.f, 0, 0));

	HealthComp = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HealthComp->OnDeath.AddDynamic(this, &ADrone::OnDeath);
	HealthComp->OnHpChanged.AddDynamic(this, &ADrone::OnHpChanged);

}

void ADrone::UpdateHUD(float NewHp)
{
	auto PlayerController = Cast<APlayerController>(GetController());
	auto HUD = Cast<ADroneHUD>(PlayerController->GetHUD());
	HUD->SetPlayerHealth(NewHp);
	HUD->SetMaxPlayerHealth(HealthComp->MaxHealth);
}

void ADrone::BeginPlay()
{
	Super::BeginPlay(); 

	World = GetWorld();
	
	MeshComp->SetRelativeLocation(FVector(0, 0, -200));
	
	CameraComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CameraComp->SetRelativeLocation(FVector(-350.0f, 0.0f, 400.f));
	CameraComp->SetActive(true);
	
	UpdateHUD(HealthComp->CurrentHealth);
	
	USkeletalMesh* SkMeshAsset = LoadObject<USkeletalMesh>(nullptr, *SkMeshAssetPath);
	if (SkMeshAsset)
	{
		MeshComp->SetSkeletalMesh(SkMeshAsset);
	}

	UPhysicsAsset* PhysicsAsset = LoadObject<UPhysicsAsset>(nullptr, *PhysAssetPath); 
	if (PhysicsAsset)
	{
		MeshComp->SetPhysicsAsset(PhysicsAsset);
	}
}

void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bDead) MovementComp->Velocity = ((VelocityForward + VelocityRight + VelocityUp).GetSafeNormal() * VelocityMultiplier);
}

void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveRight", this, &ADrone::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &ADrone::MoveForward);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADrone::MoveUp);
	PlayerInputComponent->BindAxis("LookAround", this, &ADrone::LookAround);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ADrone::TryFire);
}


void ADrone::OnHpChanged(float NewHp)
{
	UpdateHUD(NewHp);
}

void ADrone::MoveForward(float Amount) 
{
	VelocityForward = (GetActorForwardVector() * Amount);
}

void ADrone::MoveRight(float Amount)
{
	VelocityRight = (GetActorRightVector() * Amount);
}

void ADrone::MoveUp(float Amount)
{
	VelocityUp = (GetActorUpVector() * Amount);
}

void ADrone::LookAround(float Amount)
{
	float RotationRate = 5.0f;
	AddActorLocalRotation(FRotator(0,Amount * RotationRate,0));
	RotationPitch = Amount * RotationRate;
}

void ADrone::LookUp(float Amount)
{
	float RotationRate = 5.0f;
	RotationYaw = Amount * RotationRate;
}

void ADrone::TryFire()
{
	if(AmmoAmount > 0)
	{
		Fire();
	}
}

void ADrone::Fire()
{
	if (World)
	{

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		
		TSubclassOf<AProjectile> ActorClassToSpawn = AProjectile::StaticClass();
		
		FVector SpawnLocation = ArrowComp->GetComponentLocation();
		FRotator SpawnRotation = ArrowComp->GetComponentRotation(); 
		
		AProjectile* Projectile = World->SpawnActor<AProjectile>(ActorClassToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
		Projectile->MeshComp->SetCollisionProfileName("DroneProjectile");	
		if (Projectile)
		{
			Projectile->MovementComp->Velocity = GetActorForwardVector() * Projectile->SpeedMultiplier;
			AmmoAmount--;
		}
	}
}

void ADrone::OnDeath()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurret::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		if (auto Turret = Cast<ATurret>(Actor))
		{
			Turret->bWorking = false;
		}
	}
	bDead = true;
	APlayerController* MyPlayerController = GetWorld()->GetFirstPlayerController();
	if (MyPlayerController)
	{
		DisableInput(MyPlayerController);
	}
	MovementComp->Velocity = GetActorUpVector() * VelocityMultiplier * -1;
	MovementComp->Deceleration = 0;
}






