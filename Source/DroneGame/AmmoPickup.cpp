// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickup.h"

AAmmoPickup::AAmmoPickup()
{
	MeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Game/Pickups/SM_RocketPickup.SM_RocketPickup'");
}

void AAmmoPickup::GivePickupTo(ADrone* Drone)
{
	Super::GivePickupTo(Drone);
	Drone->AmmoAmount = Drone->AmmoAmount + AmmoCount;
}
