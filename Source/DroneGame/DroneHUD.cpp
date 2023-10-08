#pragma once

#include "DroneHUD.h"
#include "Engine/Canvas.h"

ADroneHUD::ADroneHUD()
{
	
}

void ADroneHUD::DrawHUD()
{
	Super::DrawHUD();

	// Get the screen dimensions
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);

	// Calculate the position of the health bar in the top left corner
	FVector2D HealthBarPosition = FVector2D(80.0f, 50.0f);

	// Calculate the size of the health bar (adjust as needed)
	FVector2D HealthBarSize = FVector2D(200.0f, 20.0f);

	// Calculate the fill percentage of the health bar
	float HealthPercentage = FMath::Clamp(CurrentHealth / 100.0f, 0.0f, 1.0f);

	// Draw the health bar background
	FCanvasTileItem BackgroundTile(HealthBarPosition, HealthBarSize, FLinearColor(0.2f, 0.2f, 0.2f, 0.7f));
	Canvas->DrawItem(BackgroundTile);

	// Draw the filled health bar
	FCanvasTileItem HealthTile(HealthBarPosition, FVector2D(HealthBarSize.X * HealthPercentage, HealthBarSize.Y), FLinearColor(0.0f, 1.0f, 0.0f, 0.7f));
	Canvas->DrawItem(HealthTile);

	FString HpLabelText = FString::Printf(TEXT("HP:"));
	FCanvasTextItem HpLabelTextItem(FVector2d(HealthBarPosition.X - 30, HealthBarPosition.Y), FText::FromString(HpLabelText), GEngine->GetSmallFont(), FLinearColor::Black);
	Canvas->DrawItem(HpLabelTextItem);

	FString HealthText;
	if (CurrentHealth > 0)
	{
		HealthText = FString::Printf(TEXT("%0.f / %0.f"), CurrentHealth, MaxHealth);
	}
	else
	{
		HealthText = FString::Printf(TEXT("DEAD"));
	}
	FCanvasTextItem HealthTextItem(HealthBarPosition, FText::FromString(HealthText), GEngine->GetSmallFont(), FLinearColor::Black);
	Canvas->DrawItem(HealthTextItem);
	
}

void ADroneHUD::SetPlayerHealth(float Health)
{
	CurrentHealth = Health;
}

void ADroneHUD::SetMaxPlayerHealth(float Health)
{
	MaxHealth = Health;
}
