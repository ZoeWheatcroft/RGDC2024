// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h"

void ABaseAIController::BeginPlay()
{

	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);


	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (MyPawn)
	{
		GetBlackboardComponent()->SetValueAsVector("PlayerLocation", MyPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject("Player", MyPawn);

	}
}
