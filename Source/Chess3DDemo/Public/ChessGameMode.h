// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChessGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CHESS3DDEMO_API AChessGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AChessGameMode();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	void SetBoard(class AChessBoard* Board) { pBoard = Board; }

	AChessBoard* GetBoard() { return pBoard; }

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChessBoard> boardBlueprint;

	AChessBoard* pBoard;

};
