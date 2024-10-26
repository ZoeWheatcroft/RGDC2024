// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"

// Sets default values
AFPSController::AFPSController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	m_currentVelocity = {};
	m_jumped = false;
	m_verticalAxisInput = {};
	m_horizontalAxisInput = {};
	m_jumpInput = {};
	m_gravityMagnitude = 9.8f;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	m_cameraBoom = CreateDefaultSubobject<USceneComponent>(TEXT("CameraBoom"));
	m_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//auto* box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	m_camera->bUsePawnControlRotation = true;
	m_cameraBoom->SetupAttachment(RootComponent);
	m_camera->SetupAttachment(m_cameraBoom);
	//box->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFPSController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_currentVelocity.Y -= m_gravityMagnitude * DeltaTime;

	if (!m_currentVelocity.IsZero())
	{
		FHitResult hitres;
		SetActorLocation(m_currentVelocity * DeltaTime, false, &hitres);
		// if there was jump velocity, we just applied it
		m_jumped = false;
	}
}

void AFPSController::HorizontalAxisMove(const FInputActionInstance& instance)
{
	m_currentVelocity.X += FMath::Clamp(instance.GetValue().Get<float>(), -1.0f, 1.0f);
}

void AFPSController:: VerticalAxisMove(const FInputActionInstance& instance)
{
	m_currentVelocity.Y += FMath::Clamp(instance.GetValue().Get<float>(), -1.0f, 1.0f);
}

void AFPSController::Jump(const FInputActionInstance&)
{
	if (m_jumped) // reset every time we tick / move velocity
		return;

	m_currentVelocity.Y = 10;
	// we need to jump so we haven't yet
	m_jumped = false;
}

void AFPSController::MouseLook(const FInputActionInstance& inst)
{
	auto delta = inst.GetValue().Get<FVector2D>();

	m_cameraBoom->AddLocalRotation(FQuat::MakeFromEuler({ 0.f, delta.X, 0.f }));
	m_camera->AddLocalRotation(FQuat::MakeFromEuler({ delta.Y, 0.f, 0.f }));
}

// Called to bind functionality to input
void AFPSController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (auto* localPlayer = Cast<ULocalPlayer>(GetLocalViewingPlayerController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!m_inputMapping.IsNull())
			{
				// NOTE: priority 0
				InputSystem->AddMappingContext(m_inputMapping.LoadSynchronous(), 0);
			}
		}
	}

	input->BindAction(m_mouseInputVector2, ETriggerEvent::Triggered, this, &AFPSController::MouseLook);
	input->BindAction(m_verticalAxisInput, ETriggerEvent::Triggered, this, &AFPSController::VerticalAxisMove);
	input->BindAction(m_horizontalAxisInput, ETriggerEvent::Triggered, this, &AFPSController::HorizontalAxisMove);
	input->BindAction(m_jumpInput, ETriggerEvent::Triggered, this, &AFPSController::Jump);
}

