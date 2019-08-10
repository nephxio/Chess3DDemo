// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Piece.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

#define TILE_NORTH	0
#define TILE_WEST	1
#define TILE_SOUTH	2
#define TILE_EAST	3

UCLASS()
class CHESS3DDEMO_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Color Changing")
	void ChangeTint(FColor Color);

	UFUNCTION(BlueprintCallable, Category = "Color Changing")
	void ResetTile() { pDynamicMaterial->SetVectorParameterValue("Tint", PlayerColor); }

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	bool ChangeHighlight();

	UFUNCTION(BlueprintCallable, Category = "Tiles")
	bool GetTileIsOccupied();

	UFUNCTION(BlueprintCallable, Category = "Tiles")
	APiece* GetOccupyingPiece();

	//Sets tile occupation status.
	UFUNCTION(BlueprintCallable, Category = "Tiles")
	void SetTileIsOccupied(int Status, APiece* pOccupyingPiece);

	UFUNCTION(BlueprintCallable, Category = "Position")
	void SetBoardCoordinate(int XCoord, int YCoord);

	UFUNCTION(BlueprintCallable, Category = "Position")
	FVector2D GetBoardCoordinate();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void InitializePiece(int Player);

	UFUNCTION(BlueprintCallable, Category = "Object Initialization")
	UMaterialInstanceDynamic* GetDynamicMaterial();

	UPROPERTY(EditAnywhere, Category = "Board")
	ATile* pNeighbors[4];

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Static Mesh Component
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* ObjectMesh;

	//Material for setting Piece color
	UMaterialInstanceDynamic* pDynamicMaterial;

	//Player Color: 1 is White, 2 is Black
	FLinearColor PlayerColor;

	//If the piece is highlighted
	bool IsHighlighted;

	UPROPERTY(EditAnywhere, Category = "Coords")
	//represents the coordinate on the board
	FVector2D BoardCoordinate;

private:
	//Reference to occupying piece
	APiece* pOccupiedBy;

	//if Tile is Occupied.  0 for unoccupied, 1 for White, 2 for Black
	int IsOccupied;
};
