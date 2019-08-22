// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Piece.h"
#include "PiecePawn.generated.h"

/**
 * 
 */
UCLASS()
class CHESS3DDEMO_API APiecePawn : public APiece
{
	GENERATED_BODY()

public:
	TArray<ATile*> GetValidMoves() override;

	UPROPERTY(BlueprintReadWrite, Category = "Pawn Moves")
	bool bIsFirstMove = true;
	
	
private:

};
