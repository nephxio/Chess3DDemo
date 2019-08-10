// Fill out your copyright notice in the Description page of Project Settings.

#include "PieceKing.h"
#include "Chess3DDemo.h"
#include "ChessBoard.h"



TArray<ATile*> APieceKing::GetValidMoves()
{
	ATile* pTileToCheck = GetOccupyingTile();

	TArray<int> TilesToRemove;
	TArray<ATile*> pValidMoves;
	TArray<FVector2D> TileOffsets = { 
		FVector2D(0,1), FVector2D(1,1),
		FVector2D(1,0), FVector2D(1,-1),
		FVector2D(0,-1), FVector2D(-1,-1),
		FVector2D(-1,0), FVector2D(-1,1) };

	for (int x = 0; x < 8; x++)
	{
		int XCoord = TileOffsets[x].X + pTileToCheck->GetBoardCoordinate().X;
		int YCoord = TileOffsets[x].Y + pTileToCheck->GetBoardCoordinate().Y;

		if (((XCoord <= 8) && (XCoord > 0))
			&& ((YCoord <= 8) && (YCoord > 0)))
		{
			pValidMoves.Add(pGameBoard->GetTile(XCoord, YCoord));
		}
	}

	for (int x = 0; x < pValidMoves.Num(); x++)
	{
		if (pValidMoves[x]->GetTileIsOccupied())
		{
			if (GetPlayerColor() == pValidMoves[x]->GetOccupyingPiece()->GetPlayerColor())
			{
				TilesToRemove.Add(x);
			}
		}
	}

	while (TilesToRemove.Num() != 0)
	{
		int x = TilesToRemove.Pop();
		pValidMoves.RemoveAt(x);
	}

	return pValidMoves;

}



