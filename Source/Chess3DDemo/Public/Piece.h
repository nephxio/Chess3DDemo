// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Piece.generated.h"

#define PIECE_BISHOP	Pieces[0]
#define PIECE_KING		Pieces[1]
#define PIECE_KNIGHT	Pieces[2]
#define PIECE_PAWN		Pieces[3]
#define PIECE_QUEEN		Pieces[4]
#define PIECE_ROOK		Pieces[5]

#define PLAYER_WHITE		1
#define PLAYER_BLACK		2

enum class ETile_Direction : uint8 {
	TILE_NORTH,
	TILE_WEST,
	TILE_SOUTH,
	TILE_EAST,
};

//enum class Player_Color : int {
//	PLAYER_WHITE,
//	PLAYER_BLACK,
//};



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
	int GetPlayerColor();
	
	UFUNCTION(BlueprintCallable, Category = "Object Initialization")
	void InitializePiece(int Player);

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

	void SetBoardReference(class AChessBoard* const pBoard);

	TArray<ATile*> GetValidMovesInDirection(int PrimaryDirection, int SecondaryDirection = -1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//reference to the Chess Board
	AChessBoard* pGameBoard;

	//Static Mesh Component
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* ObjectMesh;

	//Material for setting Piece color
	UMaterialInstanceDynamic* pDynamicMaterial;

	//Player Color: 1 is White, 2 is Black
	UPROPERTY(EditAnywhere, Category = "Player Color")
	int PlayerColor;

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