// Fill out your copyright notice in the Description page of Project Settings.

#include "PieceBishop.h"
#include "Chess3DDemo.h"
#include "ChessBoard.h"

TArray<ATile*> APieceBishop::GetValidMoves()
{
	TArray<ATile*> pValidMoves;
	
	pValidMoves += GetValidMovesInDirection(TILE_NORTH, TILE_EAST);
	pValidMoves += GetValidMovesInDirection(TILE_NORTH, TILE_WEST);
	pValidMoves += GetValidMovesInDirection(TILE_SOUTH, TILE_EAST);
	pValidMoves += GetValidMovesInDirection(TILE_SOUTH, TILE_WEST);

	return pValidMoves;
}
