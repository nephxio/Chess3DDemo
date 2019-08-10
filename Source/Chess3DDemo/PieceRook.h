// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Piece.h"
#include "PieceRook.generated.h"

/**
 * 
 */
UCLASS()
class CHESS3DDEMO_API APieceRook : public APiece
{
	GENERATED_BODY()

//	UFUNCTION(BlueprintCallable, Category = "Movement")
	TArray<ATile*> GetValidMoves() override;
	
};
