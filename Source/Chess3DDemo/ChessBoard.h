// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tile.h"
#include "Piece.h"
#include "GameFramework/Actor.h"
#include "ChessBoard.generated.h"



UCLASS()
class CHESS3DDEMO_API AChessBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChessBoard();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Blueprints for the Tiles to Spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Blueprint")
	TSubclassOf<ATile> TileBlueprint;

	//Blueprints for spawning Pieces
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece Blueprints")
	TArray<TSubclassOf<APiece>> Pieces;

	//Spawns a Bishop
	UFUNCTION(BlueprintCallable, Category = "Pieces")
	APiece* SpawnPiece(ATile* pTile, TSubclassOf<APiece> PieceToSpawn, int Player);

	UFUNCTION(BlueprintCallable, Category = "Pieces")
	void MovePiece(ATile* pDestinationTile, APiece* pPieceToMove);

	UFUNCTION(BlueprintCallable, Category = "Pieces")
	TArray<APiece*> GetBlackPieces() { return PlayerBlack; }

	UFUNCTION(BlueprintCallable, Category = "Pieces")
	TArray<APiece*> GetWhitePieces() { return PlayerWhite; }
	
	//Gets pointer from Board to tile at coord (x,y)
	UFUNCTION(BlueprintCallable, Category = "Chess Tiles")
	ATile* GetTile(int x, int y);

	UFUNCTION(BlueprintCallable, Category = "Board")
	TArray<ATile*> GetBoard() { return Board; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	//Holds all the tiles of the board for reference later
	TArray<ATile*> Board;

	//Holds all the Black pieces in play
	TArray<APiece*> PlayerBlack;

	//Holds all the White Pieces in play
	TArray<APiece*> PlayerWhite;

	//Links adjacent tiles together
	void LinkTiles();

	//Creates the board
	void SpawnBoard();

	//Sets up Black and White players
	void SpawnInitialPlayerPieces();

	//Piece clicked on by user
	APiece* ClickedPiece;

	//Tile Clicked on by user
	ATile* ClickedTile;



		
};
