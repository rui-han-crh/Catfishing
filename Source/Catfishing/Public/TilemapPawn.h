// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TilemapPawn.generated.h"



UCLASS()
class CATFISHING_API ATilemapPawn : public APawn
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FStartMove, ATilemapPawn*, Pawn, const FIntPoint&, TilePosition, const FVector&, Direction);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEndMove, ATilemapPawn*, Pawn, const FIntPoint&, TilePosition, const FVector&, Direction);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActionInitialize, ATilemapPawn*, Pawn);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActionFinalize, ATilemapPawn*, Pawn);

public:
	// Sets default values for this pawn's properties
	ATilemapPawn();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "TilemapPawn")
	FStartMove OnStartMove;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "TilemapPawn")
	FEndMove OnEndMove;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "TilemapPawn")
	FActionInitialize OnActionInitialize;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "TilemapPawn")
	FActionFinalize OnActionFinalize;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
