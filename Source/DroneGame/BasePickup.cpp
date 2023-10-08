#include "BasePickup.h"
#include "Drone.h"

// Sets default values
ABasePickup::ABasePickup()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComp->InitSphereRadius(500.0f);

	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	MeshComp->SetupAttachment(CollisionComp);

}

void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	BaseZ = GetActorLocation().Z;
	MeshComp->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *MeshAssetPath));
	CollisionComp->SetCollisionProfileName("Pickup");
	MeshComp->SetCollisionProfileName("Pickup");
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	ADrone* Drone = Cast<ADrone>(OtherActor);
	if(!Drone)
	{
		return;
	}
	GivePickupTo(Drone);
	Destroy();
}

void ABasePickup::GivePickupTo(ADrone* Pawn)
{
	
}

void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime;
	
	FVector NewLocation = GetActorLocation();
	NewLocation.Z = BaseZ + Amplitude * FMath::Sin(Frequency * Time);
	
	SetActorLocation(NewLocation);
	AddActorLocalRotation(FRotator(0,1,0));
}

