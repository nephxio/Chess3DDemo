// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Piece.h"
#include "PieceBishop.generated.h"

/**
 * 
 */
UCLASS()
class CHESS3DDEMO_API APieceBishop : public APiece
{
	GENERATED_BODY()
	
//	UFUNCTION(BlueprintCallable, Category = "Movement")
	TArray<ATile*> GetValidMoves() override;
	
};
