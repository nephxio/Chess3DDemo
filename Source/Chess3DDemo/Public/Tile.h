// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Piece.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


UCLASS()
class CHESS3DDEMO_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Color Changing")
	void ChangeTint(FColor Color);

	UFUNCTION(BlueprintCallable, Category = "Color Changing")
	void ResetTile() { pDynamicMaterial->SetVectorParameterValue(FName("Tint"), PlayerColor); }

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	bool ChangeHighlight();

	UFUNCTION(BlueprintCallable, Category = "Tiles")
	bool GetTileIsOccupied() const;

	UFUNCTION(BlueprintCallable, Category = "Tiles")
	APiece* GetOccupyingPiece();

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	UStaticMeshComponent* GetMesh() const { return pObjectMesh; }

	//Sets tile occupation status.
	void SetTileIsOccupied(EPlayerColor Status, APiece* pOccupyingPiece);

	UFUNCTION(BlueprintCallable, Category = "Position")
	void SetBoardCoordinate(int XCoord, int YCoord);

	UFUNCTION(BlueprintCallable, Category = "Position")
	FVector2D GetBoardCoordinate() const;

	void InitializePiece(EPlayerColor Player, class AChessBoard* Board);

	UFUNCTION(BlueprintCallable, Category = "Object Initialization")
	UMaterialInstanceDynamic* GetDynamicMaterial() const;

	FORCEINLINE void SetAdjacentTile(ETileDirection Direction, ATile* pTile) { pNeighbors[(int)Direction] = pTile; }

	ATile* GetTileInDirection(ETileDirection PrimaryDirection, ETileDirection SecondaryDirection = ETileDirection::TILE_NONE) const;

protected:

	//Static Mesh Component
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* pObjectMesh;

	//Material for setting Piece color
	UMaterialInstanceDynamic* pDynamicMaterial;

	UPROPERTY(EditAnywhere, Category = "Coords")
	//represents the coordinate on the board
	FVector2D BoardCoordinate;

private:

	//stores adjacent tiles in N/W/S/E directions, respectively
	ATile* pNeighbors[4];

	//Player Color: 1 is White, 2 is Black
	FLinearColor PlayerColor;

	//If the piece is highlighted
	bool IsHighlighted;

	//Reference to occupying piece
	TWeakObjectPtr<APiece> pOccupiedBy;

	//if Tile is Occupied.  0 for unoccupied, 1 for White, 2 for Black
	EPlayerColor IsOccupied;
};
