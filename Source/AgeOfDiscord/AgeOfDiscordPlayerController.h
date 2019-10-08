// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AgeOfDiscordPlayerController.generated.h"

UCLASS()
class AAgeOfDiscordPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAgeOfDiscordPlayerController();

	/*
		This var is filled on AI character spawn in GameMode
	*/
	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "AI")
	class AAgeOfDiscordCharacter* ControlledCharacter = NULL;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps)const;

	UPROPERTY()
	class ACPP_Map_PlayerPawn* MapPawn = NULL;

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	UFUNCTION(Unreliable, Server, WithValidation)
	void Server_SetNewMoveDestination(APawn* ActingPawn, const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
};


