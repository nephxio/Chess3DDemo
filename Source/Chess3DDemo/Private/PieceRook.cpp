// Fill out your copyright notice in the Description page of Project Settings.

#include "PieceRook.h"
#include "Chess3DDemo.h"
#include "ChessBoard.h"

TArray<ATile*> APieceRook::GetValidMoves()
{
	TArray<ATile*> pValidMoves;
	
	pValidMoves += GetValidMovesInDirection(TILE_NORTH);
	pValidMoves += GetValidMovesInDirection(TILE_SOUTH);
	pValidMoves += GetValidMovesInDirection(TILE_EAST);
	pValidMoves += GetValidMovesInDirection(TILE_WEST);
	
	return pValidMoves;
}


