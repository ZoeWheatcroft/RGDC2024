// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "FPSController.generated.h"

UCLASS()
class RGDC2024_API AFPSController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFPSController();

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> m_inputMapping;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> m_mouseInputVector2;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> m_horizontalAxisInput;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> m_verticalAxisInput;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> m_jumpInput;

	UPROPERTY(EditAnywhere, Category="Physics")
	float m_gravityMagnitude;

private:
	bool m_jumped;
	FVector m_currentVelocity;
	TObjectPtr<USceneComponent> m_cameraBoom;
	TObjectPtr<UCameraComponent> m_camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MouseLook(const FInputActionInstance&);
	void HorizontalAxisMove(const FInputActionInstance&);
	void VerticalAxisMove(const FInputActionInstance&);
	void Jump(const FInputActionInstance&);
};
