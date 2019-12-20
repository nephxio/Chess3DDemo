 // Fill out your copyright notice in the Description page of Project Settings.


#include "ChessBoard.h"
#include "Piece.h"
#include "ChessGameMode.h"

AChessGameMode::AChessGameMode() : pBoard{ nullptr }, pWhiteKing { nullptr }, pBlackKing { nullptr }
{

}

void AChessGameMode::BeginPlay()
{
	Super::BeginPlay();

	pBoard = GetWorld()->SpawnActor<AChessBoard>(boardBlueprint, FVector(0,0,0), FRotator(0,0,0));

	GetWorld()->Exec(GetWorld(), TEXT("r.setRes 1200x900w"));

	GetKingPointers();

}


void AChessGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AChessGameMode::GetKingPointers()
{
	TArray<APiece*> pieces = pBoard->GetPlayerPieces(EPlayerColor::PLAYER_BLACK);
	for (APiece* p : pieces)
	{
		if (p->IsA(APieceKing::StaticClass()))
		{
			pBlackKing = (APieceKing*)p;
		}
	}

	pieces = pBoard->GetPlayerPieces(EPlayerColor::PLAYER_WHITE);
	for (APiece* p : pieces)
	{
		if (p->IsA(APieceKing::StaticClass()))
		{
			pWhiteKing = (APieceKing*)p;
		}
	}
}

bool AChessGameMode::IsBlackKingInCheck()
{
	return pBoard->KingIsInCheck(pBlackKing, pBoard->GetPlayerPieces(EPlayerColor::PLAYER_WHITE));
}

bool AChessGameMode::IsWhiteKingInCheck()
{
	return pBoard->KingIsInCheck(pWhiteKing, pBoard->GetPlayerPieces(EPlayerColor::PLAYER_BLACK));
}
