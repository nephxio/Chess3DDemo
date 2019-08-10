// Fill out your copyright notice in the Description page of Project Settings.

#include "PieceQueen.h"
#include "Chess3DDemo.h"
#include "ChessBoard.h"

TArray<ATile*> APieceQueen::GetValidMoves()
{
	TArray<ATile*> pValidMoves;
	
	pValidMoves += GetValidMovesInDirection(TILE_NORTH, TILE_EAST);
	pValidMoves += GetValidMovesInDirection(TILE_NORTH, TILE_WEST);
	pValidMoves += GetValidMovesInDirection(TILE_SOUTH, TILE_EAST);
	pValidMoves += GetValidMovesInDirection(TILE_SOUTH, TILE_WEST);
	pValidMoves += GetValidMovesInDirection(TILE_NORTH);
	pValidMoves += GetValidMovesInDirection(TILE_SOUTH);
	pValidMoves += GetValidMovesInDirection(TILE_EAST);
	pValidMoves += GetValidMovesInDirection(TILE_WEST);

	return pValidMoves;
}





