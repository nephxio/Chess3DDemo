// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Piece.generated.h"

UENUM()
enum class EPlayerColor {
	PLAYER_NONE,
	PLAYER_WHITE,
	PLAYER_BLACK,
};

UENUM()
enum class ETileDirection : uint8 {
	TILE_NORTH,
	TILE_WEST,
	TILE_SOUTH,
	TILE_EAST,
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
	bool IsHighlighted();

	UFUNCTION(BlueprintCallable, Category = "Highlighting")
	void SetIsHighlighted();

	UFUNCTION(BlueprintCallable, Category = "Player Data")
	EPlayerColor GetPlayerColor();
	
	void InitializePiece(EPlayerColor Player);

	UFUNCTION(BlueprintCallable, Category = "Object Initialization")
	void SetOccupyingTile(ATile* pTile);

	UFUNCTION(BlueprintCallable, Category = "Object Initialization")
	ATile* GetOccupyingTile();

	UFUNCTION(BlueprintCallable, Category = "Object Initialization")
	UMaterialInstanceDynamic* GetDynamicMaterial();

	UFUNCTION(BlueprintCallable, Category = "Position")
	FVector2D GetBoardLocation();

	UFUNCTION(BlueprintCallable, Category = "Piece")
	bool GetIsDead() {	return IsDead;	}

	UFUNCTION(BlueprintCallable, Category = "Piece")
	void SetIsDead() { IsDead = true; }

	TArray<ATile*> GetValidMovesInDirection(int PrimaryDirection, int SecondaryDirection = -1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//reference to the Chess Board
//	AChessBoard* pGameBoard;

	//Static Mesh Component
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* ObjectMesh;

	//Material for setting Piece color
	UMaterialInstanceDynamic* pDynamicMaterial;

	//Represents player color
	EPlayerColor PlayerColor;

	//If the piece is highlighted
	bool IsPieceHighlighted = false;

	//Link to tile currently on
	class ATile* pTileCurrentlyOccupying;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

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

		//	UFUNCTION(BlueprintCallable, Category = "Movement")
		TArray<ATile*> GetValidMoves() override;
};

/**
 *
 */
UCLASS()
class CHESS3DDEMO_API APieceKing : public APiece
{
	GENERATED_BODY()

		//	UFUNCTION(BlueprintCallable, Category = "Movement")
		TArray<class ATile*> GetValidMoves() override;
};

/**
 *
 */
UCLASS()
class CHESS3DDEMO_API APieceKnight : public APiece
{
	GENERATED_BODY()

		//	UFUNCTION(BlueprintCallable, Category = "Movement")
		TArray<class ATile*> GetValidMoves() override;
};

/**
 *
 */
UCLASS()
class CHESS3DDEMO_API APiecePawn : public APiece
{
	GENERATED_BODY()

		//	UFUNCTION(BlueprintCallable, Category = "Movement")
		TArray<class ATile*> GetValidMoves() override;
};

/**
 *
 */
UCLASS()
class CHESS3DDEMO_API APieceQueen : public APiece
{
	GENERATED_BODY()

		//	UFUNCTION(BlueprintCallable, Category = "Movement")
		TArray<class ATile*> GetValidMoves() override;
};

/**
 *
 */
UCLASS()
class CHESS3DDEMO_API APieceRook : public APiece
{
	GENERATED_BODY()

		//	UFUNCTION(BlueprintCallable, Category = "Movement")
		TArray<class ATile*> GetValidMoves() override;
};