// Fill out your copyright notice in the Description page of Project Settings.


#include "TilemapPawn.h"

// Sets default values
ATilemapPawn::ATilemapPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATilemapPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATilemapPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATilemapPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

