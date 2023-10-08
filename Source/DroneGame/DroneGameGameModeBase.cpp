// Copyright Epic Games, Inc. All Rights Reserved.


#include "DroneGameGameModeBase.h"
#include "Drone.h" 
#include "DroneHUD.h"

ADroneGameGameModeBase::ADroneGameGameModeBase()
{
	DefaultPawnClass = ADrone::StaticClass();
	HUDClass = ADroneHUD::StaticClass();
}
