// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Piece.h"
#include "PieceKing.generated.h"

/**
 * 
 */
UCLASS()
class CHESS3DDEMO_API APieceKing : public APiece
{
	GENERATED_BODY()
	
//	UFUNCTION(BlueprintCallable, Category = "Movement")
	TArray<class ATile*> GetValidMoves() override;
	
	
};
