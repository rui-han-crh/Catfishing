// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileMapActor.h"
#include "CatfishingTilemapActor.generated.h"
#include 

/**
 * 
 */
UCLASS()
class CATFISHING_API ACatfishingTilemapActor : public APaperTileMapActor
{
	GENERATED_BODY()
	

public:
	// Make a blueprint node that checks if a tile is blocked
	UFUNCTION(BlueprintCallable, Category = "Tilemap")
	bool IsTileBlocked(FIntPoint TilePosition);

	// Make a blueprint node that gets the tile type
	UFUNCTION(BlueprintCallable, Category = "Tilemap")
	int32 GetTileType(FIntPoint TilePosition);

	// Make a blueprint node that checks if a trap exists on a tile position
	UFUNCTION(BlueprintCallable, Category = "Tilemap")
	bool IsTrapOnTile(FIntPoint TilePosition);
};
