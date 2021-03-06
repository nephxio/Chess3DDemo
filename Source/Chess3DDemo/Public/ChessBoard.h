// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <future>
#include "ChessGameMode.h"
#include "Tile.h"
#include "Piece.h"
#include "ChessPlayerPawn.h"
#include "GameFramework/Actor.h"
#include "ChessBoard.generated.h"

UENUM()
enum class EPieceType {
	PIECE_NONE		UMETA(DisplayName = "None"),
	PIECE_BISHOP	UMETA(DisplayName = "Bishop"),
	PIECE_KING		UMETA(DisplayName = "King"),
	PIECE_KNIGHT	UMETA(DisplayName = "Knight"),
	PIECE_PAWN		UMETA(DisplayName = "Pawn"),
	PIECE_QUEEN		UMETA(DisplayName = "Queen"),
	PIECE_ROOK		UMETA(DisplayName = "Rook"),
};

UCLASS()
class CHESS3DDEMO_API AChessBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChessBoard();

	//Spawns a piece
	APiece* SpawnPiece(ATile* pTile, TSubclassOf<APiece> PieceToSpawn, EPlayerColor Player);
	
	//Gets pointer from Board to tile at coord (x,y)
	UFUNCTION(BlueprintCallable, Category = "Chess Tiles")
	ATile* GetTile(int x, int y);

	UFUNCTION(BlueprintCallable, Category = "Board")
	FORCEINLINE TArray<ATile*> GetBoard() { return Board; }

	bool KingIsInCheck(APiece* King, TArray<APiece*> EnemyList);

	void MovePiece(ATile* pDestinationTile, APiece* pPieceToMove);

	TArray<ATile*> GetAllPlayerMoves(TArray<APiece*> EnemyList);

	TArray<APiece*> GetPlayerPieces(EPlayerColor PlayerColor) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Blueprints for the Tiles to Spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Blueprint")
	TSubclassOf<ATile> TileBlueprint;

	//Blueprints for spawning Pieces
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece Blueprints")
	TMap<EPieceType, TSubclassOf<APiece>> Pieces;


private:	
	//Holds all the tiles of the board for reference later
	TArray<ATile*> Board;

	//Links adjacent tiles together
	void LinkTiles();

	//Creates the board
	void SpawnBoard();

	//Sets up Black and White players
	void SpawnInitialPlayerPieces();

	TArray<std::future<TArray<ATile*>>> asyncFutures;
		
};
