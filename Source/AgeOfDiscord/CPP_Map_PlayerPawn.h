// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPP_Map_PlayerPawn.generated.h"

UCLASS()
class AGEOFDISCORD_API ACPP_Map_PlayerPawn : public APawn
{
	GENERATED_BODY()

	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;

	UPROPERTY()
	class AAgeOfDiscordPlayerController* PlayerController = NULL;

public:
	// Sets default values for this pawn's properties
	ACPP_Map_PlayerPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool bShouldMoveWithControlledCharacter = true;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "AI")
	class AAgeOfDiscordCharacter* ControlledCharacter = NULL;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "AI")
		float MapPawnInterpSpeed = 15.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
