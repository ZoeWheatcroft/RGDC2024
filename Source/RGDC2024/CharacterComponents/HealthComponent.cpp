// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	MaxHealth = 10.f;
	InitialHealth = MaxHealth;
	Health = InitialHealth;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamageHandler);
}

float UHealthComponent::GetHealth() const
{
	return Health;
}

void UHealthComponent::Kill()
{
	OnDied.Broadcast();
	Health = 0.f;
}

void UHealthComponent::Damage(float amount)
{
	if (amount == 0.f)
		return;
	amount = FMath::Abs(amount);
	OnHit.Broadcast(FMath::Clamp(amount, 0, Health));
	Health -= amount;
	if (Health <= 0)
		Kill();
}

void UHealthComponent::Heal(float amount)
{
	if (amount == 0.f)
		return;
	amount = FMath::Abs(amount);
	Health += amount;
}

void UHealthComponent::TakeDamageHandler(
	AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser)
{
	this->Damage(Damage);
}
