#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "HealthPickup.generated.h"

UCLASS()
class DRONEGAME_API AHealthPickup : public ABasePickup
{
	GENERATED_BODY()
public:
	AHealthPickup();
	virtual void GivePickupTo(ADrone* Drone) override;
	float HealAmount = 40.f;
};
