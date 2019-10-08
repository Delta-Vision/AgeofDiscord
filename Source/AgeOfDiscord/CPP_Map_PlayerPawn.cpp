// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Map_PlayerPawn.h"
#include "Components/DecalComponent.h"
#include "AgeOfDiscordPlayerController.h"
#include "UnrealNetwork.h"
#include "AgeOfDiscordCharacter.h"
#include "Engine.h"

// Sets default values
ACPP_Map_PlayerPawn::ACPP_Map_PlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
}

void ACPP_Map_PlayerPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPP_Map_PlayerPawn, ControlledCharacter);
}

// Called when the game starts or when spawned
void ACPP_Map_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled())
		PlayerController = Cast<AAgeOfDiscordPlayerController>(GetController());
}

// Called every frame
void ACPP_Map_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController)
	{
		if (CursorToWorld != nullptr)
		{
			FHitResult TraceHitResult;
			PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}

		if (bShouldMoveWithControlledCharacter)
			if (ControlledCharacter)
				if (!GetActorLocation().Equals(ControlledCharacter->GetActorLocation(), 50.f))
					SetActorLocation(FMath::VInterpTo(GetActorLocation(), ControlledCharacter->GetActorLocation(), DeltaTime, MapPawnInterpSpeed));
	}
}

// Called to bind functionality to input
void ACPP_Map_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

