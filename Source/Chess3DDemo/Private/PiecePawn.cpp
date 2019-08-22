// Fill out your copyright notice in the Description page of Project Settings.

#include "PiecePawn.h"
#include "Chess3DDemo.h"
#include "ChessBoard.h"

TArray<ATile*> APiecePawn::GetValidMoves()
{
	TArray<ATile*> pValidMoves;
	ATile* pTileToCheck = GetOccupyingTile();
	int ColorMod = 1;

	if (GetPlayerColor() == 2)
	{
		ColorMod = -1;
	}

	if (bIsFirstMove)
	{
		if (!pGameBoard->GetTile(GetOccupyingTile()->GetBoardCoordinate().X, GetOccupyingTile()->GetBoardCoordinate().Y + (2 * ColorMod))->GetTileIsOccupied())
		{
			if (!pGameBoard->GetTile(pTileToCheck->GetBoardCoordinate().X, pTileToCheck->GetBoardCoordinate().Y + ColorMod)->GetTileIsOccupied())
			{
				pValidMoves.Add(pGameBoard->GetTile(GetOccupyingTile()->GetBoardCoordinate().X, GetOccupyingTile()->GetBoardCoordinate().Y + (2 * ColorMod)));
			}
		}
	}

	//Check to see if diagonal squares are occupied by enemy pieces
	if ((pTileToCheck->GetBoardCoordinate().X + 1 <= 8) && (pTileToCheck->GetBoardCoordinate().Y + 1 <= 8) && (pTileToCheck->GetBoardCoordinate().Y - 1 > 0))
	{
		if (pGameBoard->GetTile(pTileToCheck->GetBoardCoordinate().X + 1, pTileToCheck->GetBoardCoordinate().Y + ColorMod)->GetTileIsOccupied())
		{
			if (GetPlayerColor() != pGameBoard->GetTile(pTileToCheck->GetBoardCoordinate().X + 1,
				pTileToCheck->GetBoardCoordinate().Y + ColorMod)->GetOccupyingPiece()->GetPlayerColor())
			{
				pValidMoves.Add(pGameBoard->GetTile(pTileToCheck->GetBoardCoordinate().X + 1, pTileToCheck->GetBoardCoordinate().Y + ColorMod));
			}
		}
		
	}

	if ((pTileToCheck->GetBoardCoordinate().X - 1 > 0) && (pTileToCheck->GetBoardCoordinate().Y + 1 <= 8) && (pTileToCheck->GetBoardCoordinate().Y - 1 > 0))
	{
		if (pGameBoard->GetTile(pTileToCheck->GetBoardCoordinate().X - 1, pTileToCheck->GetBoardCoordinate().Y + ColorMod)->GetTileIsOccupied())
		{
			if (GetPlayerColor() != pGameBoard->GetTile(pTileToCheck->GetBoardCoordinate().X - 1,
				pTileToCheck->GetBoardCoordinate().Y + ColorMod)->GetOccupyingPiece()->GetPlayerColor())
			{
				pValidMoves.Add(pGameBoard->GetTile(pTileToCheck->GetBoardCoordinate().X - 1, pTileToCheck->GetBoardCoordinate().Y + ColorMod));
			}
		}
	}

	if ((pTileToCheck->GetBoardCoordinate().Y + 1 <= 8) && (pTileToCheck->GetBoardCoordinate().Y - 1 > 0))
	{
		if (!pGameBoard->GetTile(pTileToCheck->GetBoardCoordinate().X, pTileToCheck->GetBoardCoordinate().Y + ColorMod)->GetTileIsOccupied())
		{
			pValidMoves.Add(pGameBoard->GetTile(pTileToCheck->GetBoardCoordinate().X, pTileToCheck->GetBoardCoordinate().Y + ColorMod));
		}
	}



	return pValidMoves;
}
