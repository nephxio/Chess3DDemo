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
	APiece* pPreviousClickedPiece  = pClickedPiece;
	TArray<ATile*> pValidMoves;

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
				pClickedPiece = Cast<APiece>(ClickResult.GetActor());
			}

			pClickedPiece->HighlightedPieceGrab();

			pClickedPiece->HighlightValidMoves();

		}
	}


	if (pClickedPiece && pClickedTile)
	{
		pValidMoves = pClickedPiece->GetValidMoves();

		if (pValidMoves.Contains(pClickedTile))
		{
			pClickedPiece->HighlightValidMoves();

			if (pClickedTile->GetTileIsOccupied())
			{
				pClickedTile->GetOccupyingPiece()->SetIsDead(true);
			}

			MovePiece(pClickedTile, pClickedPiece);

			pClickedPiece = nullptr;
			pClickedTile = nullptr;
		}
	}
	else if (pClickedTile && !pClickedPiece)
	{
		pClickedPiece = nullptr;
		pClickedTile = nullptr;
	}
	else if (pClickedPiece && pPreviousClickedPiece && !pClickedTile)
	{
		pPreviousClickedPiece->HighlightedPieceGrab();
		pPreviousClickedPiece->HighlightValidMoves();
		pPreviousClickedPiece = pClickedPiece;
	}

	AChessGameMode* pGameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());
	pGameMode->IsBlackKingInCheck();
	pGameMode->IsWhiteKingInCheck();
}

void AMouse_PlayerController::MovePiece(ATile* pDestinationTile, APiece* pPieceToMove)
{
	FTransform SocketLocation, MoveLocation;
	FVector Components = pDestinationTile->GetMesh()->GetSocketLocation(FName("Piece"));

	if (pPieceToMove->GetOccupyingTile())
	{
		pPieceToMove->GetOccupyingTile()->SetTileIsOccupied(EPlayerColor::PLAYER_NONE, nullptr);
	}

	pPieceToMove->SetActorLocation(Components);

	if (pDestinationTile)
	{
		pPieceToMove->SetOccupyingTile(pDestinationTile);
		pDestinationTile->SetTileIsOccupied(pPieceToMove->GetPlayerColor(), pPieceToMove);
	}

	pPieceToMove->HighlightedPieceGrab();

	APiecePawn* pCast = Cast<APiecePawn>(pPieceToMove);

	if (pCast)
	{
		pCast->SetIsFirstMove(false);
	}
}