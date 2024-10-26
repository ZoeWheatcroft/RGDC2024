// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHeaalthChangedSignature, UHealthComponent*, HealthComponent, float, HealthBefore, float, HealthDelta, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RGDC2024_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(VisibleAnywhere, Category="Stats")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category="Stats")
	float InitialHealth;

	UPROPERTY(BlueprintReadOnly, Category="Stats")
	float Health;

	UPROPERTY()

	// Sets default values for this component's properties
	UHealthComponent();

	// subtract abs(amount) from health value
	UFUNCTION(BlueprintCallable)
	void Damage(float amount);

	// add abs(amount) to health value
	UFUNCTION(BlueprintCallable)
	void Heal(float amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void TakeDamageHandler(
		AActor* DamagedActor,
		float Damage,
		const UDamageType* DamageType,
		AController* InstigatedBy,
		AActor* DamageCauser);
};
