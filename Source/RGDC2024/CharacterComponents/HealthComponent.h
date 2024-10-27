// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHit, float, DamageTaken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeal, float, DamageHealed);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RGDC2024_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, Category="Stats")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category="Stats")
	float InitialHealth;

	UPROPERTY(BlueprintReadOnly, Category="Stats")
	float Health;

	UPROPERTY(BlueprintAssignable)
	FOnDied OnDied;

	UPROPERTY(BlueprintAssignable)
	FOnHit OnHit;

	UPROPERTY(BlueprintAssignable)
	FOnHit OnHeal;

	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	void Kill();

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
	UFUNCTION()
	void TakeDamageHandler(
		AActor* DamagedActor,
		float Damage,
		const UDamageType* DamageType,
		AController* InstigatedBy,
		AActor* DamageCauser);
};
