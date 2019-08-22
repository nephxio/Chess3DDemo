// Fill out your copyright notice in the Description page of Project Settings.

#include "Piece.h"
#include "Chess3DDemo.h"
#include "Tile.h"
#include "Chessboard.h"


// Sets default values
APiece::APiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	RootComponent = ObjectMesh;

}


// Called when the game starts or when spawned
void APiece::BeginPlay()
{
	Super::BeginPlay();

	

}

// Called every frame
void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Initialize Piece because UE4 is dumb
void APiece::InitializePiece(int Player)
{
	FLinearColor PieceColor;
	TArray<UStaticMeshComponent*> Components;

	if (Player == PLAYER_BLACK)
	{
		PieceColor = FLinearColor(FColor(70.f, 70.f, 70.f));
		PlayerColor = PLAYER_BLACK;
	}
	else if (Player == PLAYER_WHITE)
	{
		PieceColor = FLinearColor::White;
		PlayerColor = PLAYER_WHITE;
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

void APiece::SetOccupyingTile(ATile * pTile)
{
	pTileCurrentlyOccupying = pTile;
}

ATile * APiece::GetOccupyingTile()
{
	return pTileCurrentlyOccupying;
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

void APiece::SetBoardReference(AChessBoard * const pBoard)
{
	pGameBoard = pBoard;
}

TArray<ATile*> APiece::GetValidMovesInDirection(int PrimaryDirection, int SecondaryDirection)
{
	TArray<ATile*> pValidMoves;
	ATile* pCurrentTile;

	pCurrentTile = GetOccupyingTile();

	while (pCurrentTile->GetTileInDirection(PrimaryDirection, SecondaryDirection) &&
		(!pCurrentTile->GetTileInDirection(PrimaryDirection,SecondaryDirection)->GetTileIsOccupied() || 
		(pCurrentTile->GetTileInDirection(PrimaryDirection,SecondaryDirection) && 
			pCurrentTile->GetTileInDirection(PrimaryDirection,SecondaryDirection)->GetOccupyingPiece()->GetPlayerColor() != GetOccupyingTile()->GetOccupyingPiece()->GetPlayerColor())))
	{
		pValidMoves.Add(pCurrentTile->GetTileInDirection(PrimaryDirection,SecondaryDirection));
		pCurrentTile = pCurrentTile->GetTileInDirection(PrimaryDirection, SecondaryDirection);
	}

	return pValidMoves;
}

TArray<ATile*> APiece::GetValidMoves()
{
	return TArray<ATile*>();
}

void APiece::HighlightedPieceGrab()
{
	FVector PieceLoc = FVector(GetActorLocation());

	if (!IsPieceHighlighted)
	{
		PieceLoc.Z += 50.f;
//		SetActorLocation(PieceLoc);
	}
	else if (IsPieceHighlighted)
	{
		PieceLoc.Z -= 50.f;
//		SetActorLocation(PieceLoc);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HighlightedPieceGrab: IsHighlighted check failure."));
	}

	ChangeHighlight();
	SetIsHighlighted();
}

bool APiece::ChangeHighlight()
{
	TArray<UStaticMeshComponent*> Components;

	GetComponents<UStaticMeshComponent>(Components);

	pDynamicMaterial = Cast<UMaterialInstanceDynamic>(Components[0]->GetMaterial(0));

	//If piece is not highlighted, highlight it, else remove highlight
	if (!IsPieceHighlighted)
	{
		pDynamicMaterial->SetScalarParameterValue("Intensity", 1.0f);
	}
	else
	{
		pDynamicMaterial->SetScalarParameterValue("Intensity", 0.0f);
	}

	return IsPieceHighlighted;
}

//return if the piece is highlighted (exposed for Blueprint use)
bool APiece::IsHighlighted()
{
	return IsPieceHighlighted;
}

void APiece::SetIsHighlighted()
{
	if (IsPieceHighlighted)
	{
		IsPieceHighlighted = false;
	}
	else
	{
		IsPieceHighlighted = true;
	}
}

int APiece::GetPlayerColor()
{
	return PlayerColor;
}

TArray<ATile*> APieceBishop::GetValidMoves()
{
	TArray<ATile*> pValidMoves;

	pValidMoves += GetValidMovesInDirection(TILE_NORTH, TILE_EAST);
	pValidMoves += GetValidMovesInDirection(TILE_NORTH, TILE_WEST);
	pValidMoves += GetValidMovesInDirection(TILE_SOUTH, TILE_EAST);
	pValidMoves += GetValidMovesInDirection(TILE_SOUTH, TILE_WEST);

	return pValidMoves;
}

TArray<ATile*> APieceKing::GetValidMoves()
{
	ATile* pTileToCheck = GetOccupyingTile();

	TArray<int> TilesToRemove;
	TArray<ATile*> pValidMoves;
	TArray<FVector2D> TileOffsets = {
		FVector2D(0,1), FVector2D(1,1),
		FVector2D(1,0), FVector2D(1,-1),
		FVector2D(0,-1), FVector2D(-1,-1),
		FVector2D(-1,0), FVector2D(-1,1) };

	for (int x = 0; x < 8; x++)
	{
		int XCoord = TileOffsets[x].X + pTileToCheck->GetBoardCoordinate().X;
		int YCoord = TileOffsets[x].Y + pTileToCheck->GetBoardCoordinate().Y;

		if (((XCoord <= 8) && (XCoord > 0))
			&& ((YCoord <= 8) && (YCoord > 0)))
		{
			pValidMoves.Add(pGameBoard->GetTile(XCoord, YCoord));
		}
	}

	for (int x = 0; x < pValidMoves.Num(); x++)
	{
		if (pValidMoves[x]->GetTileIsOccupied())
		{
			if (GetPlayerColor() == pValidMoves[x]->GetOccupyingPiece()->GetPlayerColor())
			{
				TilesToRemove.Add(x);
			}
		}
	}

	while (TilesToRemove.Num() != 0)
	{
		int x = TilesToRemove.Pop();
		pValidMoves.RemoveAt(x);
	}

	return pValidMoves;

}
