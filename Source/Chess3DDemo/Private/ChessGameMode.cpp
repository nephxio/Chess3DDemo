 // Fill out your copyright notice in the Description page of Project Settings.

#include "ChessGameMode.h"
#include "ChessBoard.h"

AChessGameMode::AChessGameMode() : pBoard{ nullptr }, pWhiteKing { nullptr }, pBlackKing { nullptr }
{

}

void AChessGameMode::BeginPlay()
{
	Super::BeginPlay();

	pBoard = GetWorld()->SpawnActor<AChessBoard>(boardBlueprint, FVector(0,0,0), FRotator(0,0,0));

	GetWorld()->Exec(GetWorld(), TEXT("r.setRes 1200x900w"));

	GetKingPointers();

	PlayerTurn = EPlayerColor::PLAYER_WHITE;
}


void AChessGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AChessGameMode::AdvanceTurn()
{
	if (PlayerTurn == EPlayerColor::PLAYER_WHITE)
	{
		PlayerTurn = EPlayerColor::PLAYER_BLACK;
	}
	else if (PlayerTurn == EPlayerColor::PLAYER_BLACK)
	{
		PlayerTurn = EPlayerColor::PLAYER_WHITE;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerTurn is set to no color in AChessGameMode::AdvanceTurn"));
	}
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
