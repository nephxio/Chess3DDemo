// Fill out your copyright notice in the Description page of Project Settings.

#include "Mouse_PlayerController.h"
#include "Chess3DDemo.h"
#include "Blueprint/UserWidget.h"

AMouse_PlayerController::AMouse_PlayerController()
{

}

void AMouse_PlayerController::BeginPlay()
{
	bEnableClickEvents = true;
	bShowMouseCursor = true;

	InputComponent->BindAction("MouseLeftClicked", IE_Pressed, this, &AMouse_PlayerController::ClickOnObject);

	pClickedPiece = nullptr;
	pClickedTile = nullptr;

	if (wGameUI)
	{
		GameUI = CreateWidget<UUserWidget>(this, wGameUI);

		if(GameUI)
		{
			GameUI->AddToViewport();
		}
	}
}

void AMouse_PlayerController::ClickOnObject()
{
	FHitResult ClickResult;
	APiece* pPreviouslyClickedPiece = pClickedPiece;
	AChessGameMode* pGameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());
	TArray<ATile*> pValidMoves;

	if (!pGameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to cast pGameMode in AMousePlayerController::ClickOnObject"));
		return;
	}


	if (GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ClickResult))
	{
		if (ClickResult.GetActor()->IsA(ATile::StaticClass()))
		{
			if (Cast<ATile>(ClickResult.GetActor()))
			{
				pClickedTile = Cast<ATile>(ClickResult.GetActor());
			}
		}
		else if (ClickResult.GetActor()->IsA(APiece::StaticClass()))
		{

			if (Cast<APiece>(ClickResult.GetActor()))
			{
				if (!pClickedPiece)
				{
					pClickedPiece = Cast<APiece>(ClickResult.GetActor());

					pClickedPiece->HighlightedPieceGrab();
					pClickedPiece->HighlightValidMoves();
				}
				else if (pClickedPiece == Cast<APiece>(ClickResult.GetActor()))
				{
					pClickedPiece->HighlightedPieceGrab();
					pClickedPiece->HighlightValidMoves();
					pClickedPiece = nullptr;
				}
				else
				{
					if (pClickedPiece->GetPlayerColor() != Cast<APiece>(ClickResult.GetActor())->GetPlayerColor())
					{
						pClickedTile = Cast<APiece>(ClickResult.GetActor())->GetOccupyingTile();
					}
					else
					{
						pClickedPiece->HighlightedPieceGrab();
						pClickedPiece->HighlightValidMoves();
						pClickedPiece = Cast<APiece>(ClickResult.GetActor());
						pClickedPiece->HighlightedPieceGrab();
						pClickedPiece->HighlightValidMoves();
					}
				}

			}
		}
	}
	
	if (pClickedTile && !pPreviouslyClickedPiece)
	{
		pPreviouslyClickedPiece = nullptr;
		pClickedTile = nullptr;
	}

	else if (pClickedPiece && (pPreviouslyClickedPiece == pClickedPiece) && pClickedTile)
	{
		pValidMoves = pClickedPiece->GetValidMoves();

		if (pValidMoves.Contains(pClickedTile))
		{
			pClickedPiece->HighlightValidMoves();

			if (pClickedTile->GetTileIsOccupied())
			{
				pClickedTile->GetOccupyingPiece()->SetIsDead(true);
			}

			pGameMode->GetBoard()->MovePiece(pClickedTile, pClickedPiece);

			pClickedPiece = nullptr;
			pClickedTile = nullptr;
		}
	}

	pGameMode->IsBlackKingInCheck();
	pGameMode->IsWhiteKingInCheck();
}