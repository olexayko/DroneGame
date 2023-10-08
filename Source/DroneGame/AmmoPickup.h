#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "AmmoPickup.generated.h"

UCLASS()
class DRONEGAME_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()
	
protected:
	
public:
	AAmmoPickup();

	int AmmoCount = 3;
	virtual void GivePickupTo(ADrone* Actor) override;
};
