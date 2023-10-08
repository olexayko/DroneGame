#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UHealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHpChanged, float, NewHp);


UCLASS()
class DRONEGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere)
	float CurrentHealth;

	UPROPERTY(EditAnywhere)
	FOnDeath OnDeath;

	UPROPERTY(EditAnywhere)
	FOnHpChanged OnHpChanged;
	void Heal(float Amount);
	void TakeDamage(float Amount);
	bool IsAlive() const;

protected:
	virtual void BeginPlay() override;
};
