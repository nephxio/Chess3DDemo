// Fill out your copyright notice in the Description page of Project Settings.

#include "PieceQueen.h"
#include "Chess3DDemo.h"
#include "ChessBoard.h"

TArray<ATile*> APieceQueen::GetValidMoves()
{
	TArray<ATile*> pValidMoves = GenerateRookMoves();
	pValidMoves.Append(GenerateBishopMoves());

	return pValidMoves;
}

TArray<ATile*> APieceQueen::GenerateRookMoves()
{
	TArray<ATile*> pValidMoves;
	FVector2D CurrentPos = GetOccupyingTile()->GetBoardCoordinate();
	int XCounter = CurrentPos.X + 1;
	int YCounter = CurrentPos.Y + 1;

	//check all tiles to the right of the piece
	while (XCounter <= 8)
	{
		ATile* pTileToCheck = pGameBoard->GetTile(XCounter, CurrentPos.Y);

		//Check to see if the tile is occupied.  If not, add to Array of Valid moves
		if (!pTileToCheck->GetTileIsOccupied())
		{
			pValidMoves.Add(pTileToCheck);
			XCounter++;
		}
		else
		{
			//Check to see if occupying piece is of the same color
			//if not, add to valid moves and set XCounter to immediately break loop
			if (pTileToCheck->GetOccupyingPiece()->GetPlayerColor() != GetPlayerColor())
			{
				pValidMoves.Add(pTileToCheck);
			}
			XCounter = 9;
		}
	}

	//reset X Counter
	XCounter = CurrentPos.X - 1;

	//check all tiles to left of the piece
	while (XCounter > 0)
	{
		ATile* pTileToCheck = pGameBoard->GetTile(XCounter, CurrentPos.Y);

		//Check to see if the tile is occupied.  If not, add to Array of Valid moves
		if (!pTileToCheck->GetTileIsOccupied())
		{
			pValidMoves.Add(pTileToCheck);
			XCounter--;
		}
		else
		{
			//Check to see if occupying piece is of the same color
			//if not, add to valid moves and set XCounter to immediately break loop
			if (pTileToCheck->GetOccupyingPiece()->GetPlayerColor() != GetPlayerColor())
			{
				pValidMoves.Add(pTileToCheck);
			}
			XCounter = -1;
		}
	}

	//now check above the piece
	while (YCounter <= 8)
	{
		ATile* pTileToCheck = pGameBoard->GetTile(CurrentPos.X, YCounter);

		//Check to see if the tile is occupied.  If not, add to Array of Valid moves
		if (!pTileToCheck->GetTileIsOccupied())
		{
			pValidMoves.Add(pTileToCheck);
			YCounter++;
		}
		else
		{
			//Check to see if occupying piece is of the same color
			//if not, add to valid moves and set XCounter to immediately break loop
			if (pTileToCheck->GetOccupyingPiece()->GetPlayerColor() != GetPlayerColor())
			{
				pValidMoves.Add(pTileToCheck);
			}
			YCounter = 9;
		}
	}

	//reset Y Counter
	YCounter = CurrentPos.Y - 1;

	//check all tiles below the piece
	while (YCounter > 0)
	{
		ATile* pTileToCheck = pGameBoard->GetTile(CurrentPos.X, YCounter);

		//Check to see if the tile is occupied.  If not, add to Array of Valid moves
		if (!pTileToCheck->GetTileIsOccupied())
		{
			pValidMoves.Add(pTileToCheck);
			YCounter--;
		}
		else
		{
			//Check to see if occupying piece is of the same color
			//if not, add to valid moves and set XCounter to immediately break loop
			if (pTileToCheck->GetOccupyingPiece()->GetPlayerColor() != GetPlayerColor())
			{
				pValidMoves.Add(pTileToCheck);
			}
			YCounter = -1;
		}
	}

	return pValidMoves;;
}

TArray<ATile*> APieceQueen::GenerateBishopMoves()
{
	TArray<ATile*> pValidMoves;
	FVector2D CurrentPos = GetOccupyingTile()->GetBoardCoordinate();
	int XCounter = CurrentPos.X + 1;
	int YCounter = CurrentPos.Y + 1;

	//check all tiles to the right of the piece
	while ((XCounter <= 8) && (YCounter <= 8))
	{

		ATile* pTileToCheck = pGameBoard->GetTile(XCounter, YCounter);

		//Check to see if the tile is occupied.  If not, add to Array of Valid moves
		if (!pTileToCheck->GetTileIsOccupied())
		{
			pValidMoves.Add(pTileToCheck);
			XCounter++;
			YCounter++;
		}
		else
		{
			//Check to see if occupying piece is of the same color
			//if not, add to valid moves and set XCounter to immediately break loop
			if (pTileToCheck->GetOccupyingPiece()->GetPlayerColor() != GetPlayerColor())
			{
				pValidMoves.Add(pTileToCheck);
			}
			XCounter = 9;
			YCounter = 9;
		}
	}

	//reset X Counter
	XCounter = CurrentPos.X - 1;
	YCounter = CurrentPos.Y - 1;

	//check all tiles to left of the piece
	while ((XCounter > 0) && (YCounter > 0))
	{
		ATile* pTileToCheck = pGameBoard->GetTile(XCounter, YCounter);

		//Check to see if the tile is occupied.  If not, add to Array of Valid moves
		if (!pTileToCheck->GetTileIsOccupied())
		{
			pValidMoves.Add(pTileToCheck);
			XCounter--;
			YCounter--;
		}
		else
		{
			//Check to see if occupying piece is of the same color
			//if not, add to valid moves and set XCounter to immediately break loop
			if (pTileToCheck->GetOccupyingPiece()->GetPlayerColor() != GetPlayerColor())
			{
				pValidMoves.Add(pTileToCheck);
			}
			XCounter = -1;
			YCounter = -1;
		}
	}

	XCounter = CurrentPos.X - 1;
	YCounter = CurrentPos.Y + 1;

	//now check above the piece
	while ((XCounter > 0) && (YCounter <= 8))
	{
		ATile* pTileToCheck = pGameBoard->GetTile(XCounter, YCounter);

		//Check to see if the tile is occupied.  If not, add to Array of Valid moves
		if (!pTileToCheck->GetTileIsOccupied())
		{
			pValidMoves.Add(pTileToCheck);
			YCounter++;
			XCounter--;
		}
		else
		{
			//Check to see if occupying piece is of the same color
			//if not, add to valid moves and set XCounter to immediately break loop
			if (pTileToCheck->GetOccupyingPiece()->GetPlayerColor() != GetPlayerColor())
			{
				pValidMoves.Add(pTileToCheck);
			}
			YCounter = 9;
			XCounter = -1;
		}
	}

	XCounter = CurrentPos.X + 1;
	YCounter = CurrentPos.Y - 1;

	//check all tiles below the piece
	while ((XCounter <= 8) && (YCounter > 0))
	{
		ATile* pTileToCheck = pGameBoard->GetTile(XCounter, YCounter);

		//Check to see if the tile is occupied.  If not, add to Array of Valid moves
		if (!pTileToCheck->GetTileIsOccupied())
		{
			pValidMoves.Add(pTileToCheck);
			YCounter--;
			XCounter++;
		}
		else
		{
			//Check to see if occupying piece is of the same color
			//if not, add to valid moves and set XCounter to immediately break loop
			if (pTileToCheck->GetOccupyingPiece()->GetPlayerColor() != GetPlayerColor())
			{
				pValidMoves.Add(pTileToCheck);
			}
			YCounter = -1;
			XCounter = 9;
		}
	}

	return pValidMoves;
}



