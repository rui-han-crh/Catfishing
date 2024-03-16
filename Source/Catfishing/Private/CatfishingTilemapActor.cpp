// Fill out your copyright notice in the Description page of Project Settings.


#include "CatfishingTilemapActor.h"
#include "PaperTileMap.h"
#include "PaperTileMapComponent.h"
#include "PaperTileSet.h"

// Invoked when the game is first started
void ACatfishingTilemapActor::BeginPlay()
{
	// Get the tilemap component
	UPaperTileMapComponent* TileMapComponent = GetRenderComponent();

	// Get the tilemap
	UPaperTileMap* TileMap = TileMapComponent->TileMap;

	// Set the map width and height
	MapWidth = TileMap->MapWidth;
	MapHeight = TileMap->MapHeight;

	// Set the number of layers
	NumLayers = TileMap->TileLayers.Num();

	// Set the tile width
	TileWidth = TileMap->TileWidth;

	// Set the tile data
	MapTileData.SetNum(MapWidth * MapHeight);
}


bool ACatfishingTilemapActor::IsTileBlocked(FIntPoint TilePosition)
{
	// Get the tilemap component
	UPaperTileMapComponent* TileMapComponent = GetRenderComponent();

	// Get the tile index (The last layer is the base layer)
	FPaperTileInfo TileInfo = TileMapComponent->GetTile(TilePosition.X, TilePosition.Y, NumLayers - 1);

	if (!TileInfo.IsValid()) // DO NOT REMOVE THIS, will cause crash on null pointer dereference
	{
		// No tile at the given position
		return true;
	}

	// Check if within bounds of the tilemap

	if (TilePosition.X < 0 || TilePosition.X >= MapWidth || TilePosition.Y < 0 || TilePosition.Y >= MapHeight)
	{
		return true;
	}

	return TileInfo.TileSet->GetTileUserData(TileInfo.GetTileIndex()) == FName("Blocked");
}

FIntPoint ACatfishingTilemapActor::WorldToTilePosition(FVector WorldPosition)
{
	// Get Actor location
	FVector ActorLocation = GetActorLocation();

	// Get the tilemap component
	UPaperTileMapComponent* TileMapComponent = GetRenderComponent();

	FVector WorldOrigin = ActorLocation - FVector();

	// Convert the world position to a tile position
	FVector TilePosition = WorldPosition - (ActorLocation - FVector(TileWidth / 2, TileWidth / 2, 0));

	TilePosition.X = FMath::FloorToInt(TilePosition.X / TileWidth);
	TilePosition.Y = FMath::FloorToInt(TilePosition.Y / TileWidth);

	return FIntPoint(TilePosition.X, TilePosition.Y);
}

bool ACatfishingTilemapActor::IsStraightLine(FIntPoint StartTile, FIntPoint EndTile)
{
	// Check if the tiles are in a straight line
	return StartTile.X == EndTile.X || StartTile.Y == EndTile.Y;
}

bool ACatfishingTilemapActor::CheckIfAnyBlockedTiles(FIntPoint StartTile, FIntPoint EndTile, FIntPoint& FirstBlockedTile)
{
	// Check if the tiles are in a straight line
	if (IsStraightLine(StartTile, EndTile))
	{
		// Check if the tiles are in a straight line
		if (StartTile.X == EndTile.X)
		{
			// Check if the tiles are in a straight line
			for (int32 Y = FMath::Min(StartTile.Y, EndTile.Y); Y <= FMath::Max(StartTile.Y, EndTile.Y); Y++)
			{
				// Check if the tile is blocked
				if (IsTileBlocked(FIntPoint(StartTile.X, Y)))
				{
					FirstBlockedTile = FIntPoint(StartTile.X, Y);
					return true;
				}
			}

			return false;
		}
		else
		{
			// Check if the tiles are in a straight line
			for (int32 X = FMath::Min(StartTile.X, EndTile.X); X <= FMath::Max(StartTile.X, EndTile.X); X++)
			{
				// Check if the tile is blocked
				if (IsTileBlocked(FIntPoint(X, StartTile.Y)))
				{
					FIntPoint(StartTile.X, X);
					return true;
				}
			}

			return false;
		}
	}

	FirstBlockedTile = FIntPoint(-1, -1);
	return true;
}

bool ACatfishingTilemapActor::CheckIfValidDirection(FIntPoint StartTile, FVector Direction)
{
	// Round X and Y to the nearest integer
	int32 X = FMath::RoundToInt(Direction.X);
	int32 Y = FMath::RoundToInt(Direction.Y);

	// Check if only one of X and Y is non-zero
	if (X != 0 && Y != 0)
	{
		return false;
	}

	return !IsTileBlocked(FIntPoint(StartTile.X + X, StartTile.Y + Y));
}

bool ACatfishingTilemapActor::HasFishnet(FIntPoint TilePosition)
{
	// Get the tile data
	FTileData* TileData = GetTileData(TilePosition);

	if (TileData == nullptr)
	{
		return false;
	}

	// Check if the tile has a fishnet
	return TileData->HasFishnet;
}

bool ACatfishingTilemapActor::AddFishnet(FIntPoint TilePosition)
{
	// Check if the tile already has a fishnet
	if (HasFishnet(TilePosition))
	{
		return false;
	}

	// Add a fishnet to the tile
	FTileData* TileData = GetTileData(TilePosition);

	if (TileData == nullptr)
	{
		return false;
	}

	TileData->HasFishnet = true;

	return true;
}

bool ACatfishingTilemapActor::RemoveFishnet(FIntPoint TilePosition)
{
	// Check if the tile has a fishnet
	if (!HasFishnet(TilePosition))
	{
		return false;
	}

	// Remove the fishnet from the tile
	FTileData* TileData = GetTileData(TilePosition);

	if (TileData == nullptr)
	{
		return false;
	}

	TileData->HasFishnet = false;

	return true;
}

FTileData *ACatfishingTilemapActor::GetTileData(FIntPoint TilePosition)
{
	// Check if the tile is within bounds
	if (TilePosition.X < 0 || TilePosition.X >= MapWidth || TilePosition.Y < 0 || TilePosition.Y >= MapHeight)
	{
		return nullptr;
	}

	return &MapTileData[TilePosition.X + TilePosition.Y * MapWidth];
}