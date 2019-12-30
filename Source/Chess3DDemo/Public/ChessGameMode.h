// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Piece.h"
#include "CoreMinimal.h"
#include "ChessPlayerPawn.h"
#include "GameFramework/GameModeBase.h"
#include "ChessGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FPieceIsCapturedDelegate, APiece*, DeadPiece, int, Index, int, PlayerColor);

UCLASS()
class CHESS3DDEMO_API AChessGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AChessGameMode();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	void SetKingPointers();

	FORCEINLINE void SetBoard(class AChessBoard* Board) { pBoard = Board; }

	FORCEINLINE AChessBoard* GetBoard() const { return pBoard; }

	bool IsWhiteKingInCheck();

	bool IsBlackKingInCheck();

	FORCEINLINE EPlayerColor GetPlayerTurn() const { return PlayerTurn; }

	FORCEINLINE AChessPlayerPawn* GetPlayer(EPlayerColor Color) const { return Color == EPlayerColor::PLAYER_WHITE ? PlayerWhite : PlayerBlack;  }

	void AdvanceTurn();

public:
	UPROPERTY(BlueprintAssignable)
	FPieceIsCapturedDelegate OnPieceIsCaptured;

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChessBoard>  boardBlueprint;

	AChessBoard* pBoard;

	AChessPlayerPawn* PlayerBlack;

	AChessPlayerPawn* PlayerWhite;

	APieceKing* pWhiteKing;

	APieceKing* pBlackKing;

	EPlayerColor PlayerTurn;
};
