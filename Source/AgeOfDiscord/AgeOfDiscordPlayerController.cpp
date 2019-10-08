// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AgeOfDiscordPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AgeOfDiscordCharacter.h"
#include "UnrealNetwork.h"
#include "CPP_Map_PlayerPawn.h"
#include "Engine.h"

AAgeOfDiscordPlayerController::AAgeOfDiscordPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	
}

void AAgeOfDiscordPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAgeOfDiscordPlayerController, ControlledCharacter);
}

void AAgeOfDiscordPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (ControlledCharacter)
	{
		// keep updating the destination every tick while desired
		if (bMoveToMouseCursor)
			MoveToMouseCursor();
	}
}

void AAgeOfDiscordPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MapPawn = Cast<ACPP_Map_PlayerPawn>(GetPawn());
}

void AAgeOfDiscordPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AAgeOfDiscordPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AAgeOfDiscordPlayerController::OnSetDestinationReleased);
}

void AAgeOfDiscordPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.Location);
	}
}

void AAgeOfDiscordPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	if (ControlledCharacter)
	{
		float const Distance = FVector::Dist(DestLocation, ControlledCharacter->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
			Server_SetNewMoveDestination(ControlledCharacter, DestLocation);

		if (MapPawn)
			MapPawn->bShouldMoveWithControlledCharacter = true;
	}
}


bool AAgeOfDiscordPlayerController::Server_SetNewMoveDestination_Validate(APawn* ActingPawn, const FVector DestLocation)
{
	return true;
}

void AAgeOfDiscordPlayerController::Server_SetNewMoveDestination_Implementation(APawn* ActingPawn, const FVector DestLocation)
{
	AAIController* AI_Controller = Cast<AAIController>(ActingPawn->GetController());
	if (AI_Controller)
		AI_Controller->MoveToLocation(DestLocation);
}

void AAgeOfDiscordPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AAgeOfDiscordPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
