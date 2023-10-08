#include "UHealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentHealth = MaxHealth / 2;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::Heal(float Amount)
{
	if (Amount <= 0.0f || !IsAlive())
	{
		return;
	}

	CurrentHealth = FMath::Min(CurrentHealth + Amount, MaxHealth);
	OnHpChanged.Broadcast(CurrentHealth);
}

void UHealthComponent::TakeDamage(float Amount)
{
	if (Amount <= 0.0f || !IsAlive())
	{
		return;
	}

	CurrentHealth = FMath::Max(CurrentHealth - Amount, 0.0f);
	OnHpChanged.Broadcast(CurrentHealth);
	if (!IsAlive())
	{
		OnDeath.Broadcast();
	}
}

bool UHealthComponent::IsAlive() const
{
	return CurrentHealth > 0.0f;
}
