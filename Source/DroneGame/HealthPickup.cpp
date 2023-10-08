#include "HealthPickup.h"

AHealthPickup::AHealthPickup()
{
	MeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Game/Pickups/SM_HealthPickup.SM_HealthPickup'");
}

void AHealthPickup::GivePickupTo(ADrone* Drone)
{
	Super::GivePickupTo(Drone);
	Drone->HealthComp->Heal(HealAmount);
}