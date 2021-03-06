// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Piece.generated.h"

UENUM()
enum class EPlayerColor {
	PLAYER_NONE = 0,
	PLAYER_WHITE = 1,
	PLAYER_BLACK = -1
};

UENUM()
enum class ETileDirection {
	TILE_NONE = -1,
	TILE_NORTH = 0,
	TILE_WEST = 1,
	TILE_SOUTH = 2,
	TILE_EAST = 3
};

UCLASS()
class CHESS3DDEMO_API APiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APiece();

	UFUNCTION(BlueprintCallable, Category = "Moving")
	virtual TArray<ATile*> GetValidMoves();

	UFUNCTION(BlueprintCallable, Category = "Highlighting")
	void HighlightedPieceGrab();

	UFUNCTION(BlueprintCallable, Category = "Highlighting")
	bool ChangeHighlight();

	UFUNCTION(BlueprintCallable, Category = "Highlighting")
	bool IsHighlighted() const;

	UFUNCTION(BlueprintCallable, Category = "Player Data")
	EPlayerColor GetPlayerColor() const;
	
	void InitializePiece(EPlayerColor Player);

	UFUNCTION(BlueprintCallable, Category = "Object Initialization")
	void SetOccupyingTile(ATile* pTile);

	UFUNCTION(BlueprintCallable, Category = "Object Initialization")
	ATile* GetOccupyingTile() const;

	UFUNCTION(BlueprintCallable, Category = "Object Initialization")
	UMaterialInstanceDynamic* GetDynamicMaterial() const;

	UFUNCTION(BlueprintCallable, Category = "Position")
	FVector2D GetBoardLocation() const;

//	UFUNCTION(BlueprintCallable, Category = "Piece")
	FORCEINLINE bool GetIsDead() const { return IsDead; }

//	UFUNCTION(BlueprintCallable, Category = "Piece")
	void SetIsDead(bool value);

	TArray<ATile*> GetValidMovesInDirection(ETileDirection PrimaryDirection, ETileDirection SecondaryDirection = ETileDirection::TILE_NONE) const;

	ATile* GetTileFromBoard(int x, int y);

	void HighlightValidMoves();


protected:

	//Static Mesh Component
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* pObjectMesh;

	//Material for setting Piece color
	UPROPERTY(EditDefaultsOnly, Category = "Material")
	UMaterialInstanceDynamic* pDynamicMaterial;

private:

	//Represents player color
	EPlayerColor PlayerColor;

	//If the piece is highlighted
	bool IsPieceHighlighted;

	//Link to tile currently on
	TWeakObjectPtr<ATile> pTileCurrentlyOccupying;

	//Stores if piece is dead
	bool IsDead = false;
};

/**
 *
 */
UCLASS()
class CHESS3DDEMO_API APieceBishop : public APiece
{
	GENERATED_BODY()

public:
	//	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual TArray<ATile*> GetValidMoves() override;
};

/**
 *
 */
UCLASS()
class CHESS3DDEMO_API APieceKing : public APiece
{
	GENERATED_BODY()

public:
	//	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual TArray<class ATile*> GetValidMoves() override;
};

/**
 *
 */
UCLASS()
class CHESS3DDEMO_API APieceKnight : public APiece
{
	GENERATED_BODY()

public:
	//	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual TArray<class ATile*> GetValidMoves() override;
};

/**
 *
 */
UCLASS()
class CHESS3DDEMO_API APiecePawn : public APiece
{
	GENERATED_BODY()

public:
	//	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual TArray<class ATile*> GetValidMoves() override;

	FORCEINLINE bool GetIsFirstMove() const { return IsFirstMove; }

	FORCEINLINE void SetIsFirstMove(bool FirstMove) { IsFirstMove = FirstMove; }

private:
	bool IsFirstMove = true;
};

/**
 *
 */
UCLASS()
class CHESS3DDEMO_API APieceQueen : public APiece
{
	GENERATED_BODY()

public:
	//	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual TArray<class ATile*> GetValidMoves() override;
};

/**
 *
 */
UCLASS()
class CHESS3DDEMO_API APieceRook : public APiece
{
	GENERATED_BODY()

public:
	//	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual TArray<class ATile*> GetValidMoves() override;
};