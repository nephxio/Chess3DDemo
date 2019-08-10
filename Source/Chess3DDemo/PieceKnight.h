// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Piece.h"
#include "PieceKnight.generated.h"

/**
 * 
 */
UCLASS()
class CHESS3DDEMO_API APieceKnight : public APiece
{
	GENERATED_BODY()
	
//	UFUNCTION(BlueprintCallable, Category = "Movement")
	TArray<class ATile*> GetValidMoves() override;
	
	
};
