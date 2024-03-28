// Fill out your copyright notice in the Description page of Project Settings.

#include "TilemapPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATilemapPawn::ATilemapPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a BoxComponent to represent the pawn's collision
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	Pivot->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATilemapPawn::BeginPlay()
{
	Super::BeginPlay();

	// Get the catfishing tilemap
	Tilemap = Cast<ACatfishingTilemapActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACatfishingTilemapActor::StaticClass()));

	// Set the current tile position based on the tilemap
	if (Tilemap)
	{
		TilePosition = Tilemap->WorldToTilePosition(GetActorLocation());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Tilemap not found!"));
	}
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

FIntPoint ATilemapPawn::AssignTilePosition()
{
	TilePosition = Tilemap->WorldToTilePosition(GetActorLocation());
	return TilePosition;
}