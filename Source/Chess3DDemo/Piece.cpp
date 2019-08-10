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
		IsPieceHighlighted = true;
	}
	else if (IsPieceHighlighted)
	{
		PieceLoc.Z -= 50.f;
//		SetActorLocation(PieceLoc);
		IsPieceHighlighted = false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HighlightedPieceGrab: bIsHighlighted check failure."));
	}

	ChangeHighlight();
}

bool APiece::ChangeHighlight()
{
	TArray<UStaticMeshComponent*> Components;

	GetComponents<UStaticMeshComponent>(Components);

	pDynamicMaterial = Cast<UMaterialInstanceDynamic>(Components[0]->GetMaterial(0));

	//If piece is not highlighted, highlight it, else remove highlight
	if (IsPieceHighlighted)
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

void APiece::SetIsHighlighted(bool Highlight)
{
	IsPieceHighlighted = Highlight;
}

int APiece::GetPlayerColor()
{
	return PlayerColor;
}
