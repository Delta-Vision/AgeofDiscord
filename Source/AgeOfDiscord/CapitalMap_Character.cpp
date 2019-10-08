// Fill out your copyright notice in the Description page of Project Settings.


#include "CapitalMap_Character.h"

// Sets default values
ACapitalMap_Character::ACapitalMap_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACapitalMap_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACapitalMap_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACapitalMap_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

