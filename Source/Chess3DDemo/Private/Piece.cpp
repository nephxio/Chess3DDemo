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

	TArray<ATile*> Moves = GetValidMoves();

	for (ATile* Tile : Moves)
	{
		Tile->ChangeHighlight();
	}
}

bool APiece::ChangeHighlight()
{
	pDynamicMaterial = Cast<UMaterialInstanceDynamic>(ObjectMesh->GetMaterial(0));

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

	pValidMoves += GetValidMovesInDirection(TILE_NORTH, TILE_EAST);
	pValidMoves += GetValidMovesInDirection(TILE_NORTH, TILE_WEST);
	pValidMoves += GetValidMovesInDirection(TILE_SOUTH, TILE_EAST);
	pValidMoves += GetValidMovesInDirection(TILE_SOUTH, TILE_WEST);

	return pValidMoves;
}

TArray<ATile*> APieceKing::GetValidMoves()
{
	TArray<ATile*> pValidMoves;



	return pValidMoves;

}

TArray<ATile*> APieceKnight::GetValidMoves()
{
	TArray<ATile*> pValidMoves;



	return pValidMoves;

}

TArray<ATile*> APiecePawn::GetValidMoves()
{
	TArray<ATile*> pValidMoves;



	return pValidMoves;

}

TArray<ATile*> APieceQueen::GetValidMoves()
{
	TArray<ATile*> pValidMoves;

	pValidMoves += GetValidMovesInDirection(TILE_NORTH, TILE_EAST);
	pValidMoves += GetValidMovesInDirection(TILE_NORTH, TILE_WEST);
	pValidMoves += GetValidMovesInDirection(TILE_SOUTH, TILE_EAST);
	pValidMoves += GetValidMovesInDirection(TILE_SOUTH, TILE_WEST);
	pValidMoves += GetValidMovesInDirection(TILE_NORTH);
	pValidMoves += GetValidMovesInDirection(TILE_SOUTH);
	pValidMoves += GetValidMovesInDirection(TILE_EAST);
	pValidMoves += GetValidMovesInDirection(TILE_WEST);

	return pValidMoves;

}

TArray<ATile*> APieceRook::GetValidMoves()
{
	TArray<ATile*> pValidMoves;

	pValidMoves += GetValidMovesInDirection(TILE_NORTH);
	pValidMoves += GetValidMovesInDirection(TILE_SOUTH);
	pValidMoves += GetValidMovesInDirection(TILE_EAST);
	pValidMoves += GetValidMovesInDirection(TILE_WEST);

	return pValidMoves;

}