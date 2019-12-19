// Fill out your copyright notice in the Description page of Project Settings.

#include "Piece.h"
#include "Chess3DDemo.h"
#include "Tile.h"
#include "Chessboard.h"


// Sets default values
APiece::APiece() : IsPieceHighlighted { false }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	RootComponent = pObjectMesh;

}

//Initialize Piece because UE4 is dumb
void APiece::InitializePiece(EPlayerColor Player)
{
	FLinearColor PieceColor;
	TArray<UStaticMeshComponent*> Components;

	if (Player == EPlayerColor::PLAYER_BLACK)
	{
		PieceColor = FLinearColor(FColor(70.f, 70.f, 70.f));
		PlayerColor = EPlayerColor::PLAYER_BLACK;
	}
	else if (Player == EPlayerColor::PLAYER_WHITE)
	{
		PieceColor = FLinearColor::White;
		PlayerColor = EPlayerColor::PLAYER_WHITE;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Wrong Piece Color Integer"));
	}

	GetComponents<UStaticMeshComponent>(Components);

	//Get the Static Mesh Component
	pDynamicMaterial = UMaterialInstanceDynamic::Create(Components[0]->GetMaterial(0), this);

	//Set the tint parameter to Black or White
	pDynamicMaterial->SetVectorParameterValue("Tint", PieceColor);
	Components[0]->SetMaterial(0, pDynamicMaterial);

	IsPieceHighlighted = false;
}

void APiece::SetOccupyingTile(ATile* pTile)
{
	pTileCurrentlyOccupying = TWeakObjectPtr<ATile>(pTile);
}

ATile* APiece::GetOccupyingTile()
{
	return pTileCurrentlyOccupying.Get();
}

UMaterialInstanceDynamic* APiece::GetDynamicMaterial()
{
	return pDynamicMaterial;
}

FVector2D APiece::GetBoardLocation()
{
	FVector2D Vect = pTileCurrentlyOccupying->GetBoardCoordinate();
	return Vect;
}

TArray<ATile*> APiece::GetValidMovesInDirection(ETileDirection PrimaryDirection, ETileDirection SecondaryDirection)
{
	TArray<ATile*> pValidMoves;
	ATile* pCurrentTile;

	pCurrentTile = GetOccupyingTile();

	while (pCurrentTile->GetTileInDirection(PrimaryDirection, SecondaryDirection))
	{
		if (pCurrentTile->GetTileInDirection(PrimaryDirection, SecondaryDirection)->GetTileIsOccupied() &&
			pCurrentTile->GetTileInDirection(PrimaryDirection, SecondaryDirection)->GetOccupyingPiece()->GetPlayerColor() != this->GetPlayerColor())
		{
			pValidMoves.Add(pCurrentTile->GetTileInDirection(PrimaryDirection, SecondaryDirection));
			break;
		}

		else if (pCurrentTile->GetTileInDirection(PrimaryDirection, SecondaryDirection)->GetTileIsOccupied() &&
			pCurrentTile->GetTileInDirection(PrimaryDirection, SecondaryDirection)->GetOccupyingPiece()->GetPlayerColor() == this->GetPlayerColor())
		{
			break;
		}

		else if (!pCurrentTile->GetTileInDirection(PrimaryDirection, SecondaryDirection)->GetTileIsOccupied())
		{
			pValidMoves.Add(pCurrentTile->GetTileInDirection(PrimaryDirection, SecondaryDirection));			
		}

		pCurrentTile = pCurrentTile->GetTileInDirection(PrimaryDirection, SecondaryDirection);

	}

	return pValidMoves;
}

TArray<ATile*> APiece::GetValidMoves()
{
	return TArray<ATile*>();
}

ATile* APiece::GetTileFromBoard(int x, int y)
{
	AChessGameMode* gameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());

	return gameMode->GetBoard()->GetTile(x, y);
}

void APiece::HighlightValidMoves()
{
	TArray<ATile*> validMoves = GetValidMoves();
	for (ATile* tile : validMoves)
	{
		tile->ChangeHighlight();
	}
}

void APiece::HighlightedPieceGrab()
{
	FVector PieceLoc = FVector(GetActorLocation());

	if (!IsPieceHighlighted)
	{
		PieceLoc.Z += 50.f;
	}
	else if (IsPieceHighlighted)
	{
		PieceLoc.Z -= 50.f;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HighlightedPieceGrab: IsHighlighted check failure."));
	}

	ChangeHighlight();
}

bool APiece::ChangeHighlight()
{
	pDynamicMaterial = Cast<UMaterialInstanceDynamic>(pObjectMesh->GetMaterial(0));

	//If piece is not highlighted, highlight it, else remove highlight
	if (!IsPieceHighlighted)
	{
		pDynamicMaterial->SetScalarParameterValue("Intensity", 1.0f);
		IsPieceHighlighted = true;
	}
	else
	{
		pDynamicMaterial->SetScalarParameterValue("Intensity", 0.0f);
		IsPieceHighlighted = false;
	}

	return IsPieceHighlighted;
}

//return if the piece is highlighted (exposed for Blueprint use)
bool APiece::IsHighlighted()
{
	return IsPieceHighlighted;
}

EPlayerColor APiece::GetPlayerColor()
{
	return PlayerColor;
}

TArray<ATile*> APieceBishop::GetValidMoves()
{
	TArray<ATile*> pValidMoves;

	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_NORTH, ETileDirection::TILE_EAST);
	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_NORTH, ETileDirection::TILE_WEST);
	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_SOUTH, ETileDirection::TILE_EAST);
	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_SOUTH, ETileDirection::TILE_WEST);

	return pValidMoves;
}

TArray<ATile*> APieceKing::GetValidMoves()
{
	TArray<ATile*> pValidMoves;
	TArray<FVector2D> offsets = { FVector2D(-1, 1), FVector2D(0, 1),
							  FVector2D(1, 1),  FVector2D(1, 0),
							  FVector2D(1, -1), FVector2D(0, -1),
							  FVector2D(-1, -1), FVector2D(-1, 0) };

	int xCoord = GetOccupyingTile()->GetBoardCoordinate().X;
	int yCoord = GetOccupyingTile()->GetBoardCoordinate().Y;

	for (FVector2D vec : offsets)
	{
		if (((xCoord + vec.X > 0) && (xCoord + vec.X <= 8)) && ((yCoord + vec.Y > 0) && (yCoord + vec.Y <= 8)))
		{
			if (GetTileFromBoard(xCoord + vec.X, yCoord + vec.Y) && (!GetTileFromBoard(xCoord + vec.X, yCoord + vec.Y)->GetTileIsOccupied()) ||
				(GetTileFromBoard(xCoord + vec.X, yCoord + vec.Y)->GetTileIsOccupied() && GetTileFromBoard(xCoord + vec.X, yCoord + vec.Y)->GetOccupyingPiece()->GetPlayerColor() != this->GetPlayerColor()))
			{
				pValidMoves.Add(GetTileFromBoard(xCoord + vec.X, yCoord + vec.Y));
			}
		}
	}


	return pValidMoves;

}

TArray<ATile*> APieceKnight::GetValidMoves()
{
	TArray<ATile*> pValidMoves;
	TArray<FVector2D> offsets = { FVector2D(-1, 2), FVector2D(1, 2),
								  FVector2D(2, 1),  FVector2D(2, -1),
								  FVector2D(1, -2), FVector2D(-1, -2),
								  FVector2D(-2, 1), FVector2D(-2, -1) };

	int xCoord = GetOccupyingTile()->GetBoardCoordinate().X;
	int yCoord = GetOccupyingTile()->GetBoardCoordinate().Y;

	for (FVector2D vec : offsets)
	{
		if (((xCoord + vec.X > 0) && (xCoord + vec.X <= 8)) && ((yCoord + vec.Y > 0) && (yCoord + vec.Y <= 8)))
		{
			if (GetTileFromBoard(xCoord + vec.X, yCoord + vec.Y) && (!GetTileFromBoard(xCoord + vec.X, yCoord + vec.Y)->GetTileIsOccupied()) || 
				(GetTileFromBoard(xCoord + vec.X, yCoord + vec.Y)->GetTileIsOccupied() && GetTileFromBoard(xCoord + vec.X, yCoord + vec.Y)->GetOccupyingPiece()->GetPlayerColor() != this->GetPlayerColor()))
			{
				pValidMoves.Add(GetTileFromBoard(xCoord + vec.X, yCoord + vec.Y));
			}
		}
	}


	return pValidMoves;

}

TArray<ATile*> APiecePawn::GetValidMoves()
{
	TArray<ATile*> pValidMoves;
	ATile* pMainTile = GetTileFromBoard(GetOccupyingTile()->GetBoardCoordinate().X, GetOccupyingTile()->GetBoardCoordinate().Y + (int)GetPlayerColor());

	if (GetIsFirstMove() &&
		!GetTileFromBoard(GetOccupyingTile()->GetBoardCoordinate().X, GetOccupyingTile()->GetBoardCoordinate().Y + (2 * (int)GetPlayerColor()))->GetTileIsOccupied())
		
	{
		pValidMoves.Add(GetTileFromBoard(GetOccupyingTile()->GetBoardCoordinate().X, GetOccupyingTile()->GetBoardCoordinate().Y + (2 * (int)GetPlayerColor())));
	}

	if (pMainTile->GetTileInDirection(ETileDirection::TILE_WEST) && 
		pMainTile->GetTileInDirection(ETileDirection::TILE_WEST)->GetTileIsOccupied() &&
		pMainTile->GetTileInDirection(ETileDirection::TILE_WEST)->GetOccupyingPiece()->GetPlayerColor() != this->GetPlayerColor())
	{
		pValidMoves.Add(pMainTile->GetTileInDirection(ETileDirection::TILE_WEST));
	}

	if (pMainTile->GetTileInDirection(ETileDirection::TILE_EAST) &&
		pMainTile->GetTileInDirection(ETileDirection::TILE_EAST)->GetTileIsOccupied() &&
		pMainTile->GetTileInDirection(ETileDirection::TILE_EAST)->GetOccupyingPiece()->GetPlayerColor() != this->GetPlayerColor())
	{
		pValidMoves.Add(pMainTile->GetTileInDirection(ETileDirection::TILE_EAST));
	}

	if (pMainTile && !pMainTile->GetTileIsOccupied())
	{
		pValidMoves.Add(pMainTile);
	}

	return pValidMoves;

}

TArray<ATile*> APieceQueen::GetValidMoves()
{
	TArray<ATile*> pValidMoves;

	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_NORTH, ETileDirection::TILE_EAST);
	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_NORTH, ETileDirection::TILE_WEST);
	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_SOUTH, ETileDirection::TILE_EAST);
	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_SOUTH, ETileDirection::TILE_WEST);
	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_NORTH);
	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_SOUTH);
	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_EAST);
	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_WEST);

	return pValidMoves;

}

TArray<ATile*> APieceRook::GetValidMoves()
{
	TArray<ATile*> pValidMoves;

	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_NORTH);
	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_SOUTH);
	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_EAST);
	pValidMoves += GetValidMovesInDirection(ETileDirection::TILE_WEST);

	return pValidMoves;

}