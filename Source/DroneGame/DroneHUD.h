// CustomHUD.h
#pragma once

#include "GameFramework/HUD.h"
#include "DroneHUD.generated.h"

UCLASS()
class DRONEGAME_API ADroneHUD : public AHUD
{
    GENERATED_BODY()

public:
    // Constructor
    ADroneHUD();

    // Override the DrawHUD function to render the health bar
    virtual void DrawHUD() override;

    // Function to set the player's health (called from your game logic)
    void SetPlayerHealth(float Health);
    void SetMaxPlayerHealth(float MaxHealth);

private:
    // Store the player's health value
    float CurrentHealth;
    float MaxHealth;
};
