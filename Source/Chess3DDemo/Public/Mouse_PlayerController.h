// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Tile.h"
#include "Piece.h"
#include "ChessGameMode.h"
#include "ChessBoard.h"
#include "Mouse_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CHESS3DDEMO_API AMouse_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	//Default Constructor
	AMouse_PlayerController();

	void ClickOnObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> wGameUI;
	
private:
	//Piece clicked on by user
	APiece* pClickedPiece;

	//Tile Clicked on by user
	ATile* pClickedTile;

	UUserWidget* GameUI;


};
