// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileMapActor.h"
#include "CatfishingTilemapActor.generated.h"

// Structure to hold tile data
USTRUCT(BlueprintType)
struct FTileData
{
	GENERATED_USTRUCT_BODY()

	// Whether the tile has a fishnet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tilemap")
	bool HasFishnet = false;
};

UCLASS()
class CATFISHING_API ACatfishingTilemapActor : public APaperTileMapActor
{
	GENERATED_BODY()

	// Height class member
	UPROPERTY(VisibleAnywhere, Category = "Tilemap")
	int32 MapHeight;

	// Width class member
	UPROPERTY(VisibleAnywhere, Category = "Tilemap")
	int32 MapWidth;

	// Number of layers
	UPROPERTY(VisibleAnywhere, Category = "Tilemap")
	int32 NumLayers;

	// Tile width (Accessible from blueprint)
	UPROPERTY(VisibleAnywhere, Category = "Tilemap")
	float TileWidth;

	// Tiledata
	UPROPERTY(VisibleAnywhere, Category = "Tilemap")
	TArray<FTileData> MapTileData;

public:
	// Invoked When the game is first started
	virtual void BeginPlay() override;

	// Checks if the tile at the given position is blocked
	UFUNCTION(BlueprintPure, Category = "Tilemap")
	bool IsTileBlocked(FIntPoint TilePosition);

	// Converts a world position to a tile position
	UFUNCTION(BlueprintCallable, Category = "Tilemap")
	FIntPoint WorldToTilePosition(FVector WorldPosition);

	// Checks if start and end tiles are in a straight line
	UFUNCTION(BlueprintPure, Category = "Tilemap")
	bool IsStraightLine(FIntPoint StartTile, FIntPoint EndTile);

	// Checks if there are any blocked tiles between the start and end tiles
	// If there are no blocked tiles, returns false
	// If there are, returns true and the first blocked tile
	// If the line is not straight, returns true, but FirstBlockedTile will be (-1, -1)
	UFUNCTION(BlueprintCallable, Category = "Tilemap")
	bool CheckIfAnyBlockedTiles(FIntPoint StartTile, FIntPoint EndTile, FIntPoint& FirstBlockedTile);

	// Checks if the given direction is valid
	// The function will check if the direction is valid for the given start tile
	UFUNCTION(BlueprintCallable, Category = "Tilemap")
	bool CheckIfValidDirection(FIntPoint StartTile, FVector Direction);

	// Checks if the current tile has a fishnet
	// If the supplied tile position is invalid, the function will return false.
	UFUNCTION(BlueprintPure, Category = "Tilemap")
	bool HasFishnet(FIntPoint TilePosition);

	// Adds a fishnet to the given tile.
	// If the tile already has a fishnet or the supplie position is invalid, the function will return false.
	// If the tile does not have a fishnet, the function will return true and the tile will be updated.
	UFUNCTION(BlueprintCallable, Category = "Tilemap")
	bool AddFishnet(FIntPoint TilePosition);

	// Removes the fishnet from the given tile.
	// If the tile does not have a fishnet or the supplied position is invalid, the function will return false.
	// If the tile has a fishnet, the function will return true and the tile will be updated.
	UFUNCTION(BlueprintCallable, Category = "Tilemap")
	bool RemoveFishnet(FIntPoint TilePosition);

	// Gets a copy of the 1D tile data array.
	UFUNCTION(BlueprintPure, Category = "Tilemap")
	TArray<FTileData> GetMapTileData();

	// Sets the tile data array.
	UFUNCTION(BlueprintCallable, Category = "Tilemap")
	void SetMapTileData(TArray<FTileData> TileData);

private:
	// Helper function to get the tile data at the given position
	FTileData *GetTileData(FIntPoint TilePosition);
};
