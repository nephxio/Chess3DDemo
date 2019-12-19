// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Chess3DDemo.h"


// Sets default values
ATile::ATile() : pNeighbors{ nullptr,nullptr,nullptr,nullptr }, IsHighlighted{ false }, pOccupiedBy{ nullptr }, IsOccupied{ EPlayerColor::PLAYER_NONE }, pBoard{ nullptr }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	RootComponent = pObjectMesh;
}

void ATile::InitializePiece(EPlayerColor Player, AChessBoard* Board)
{
	FLinearColor PieceColor;
	TArray<UStaticMeshComponent*> Components;

	if (Player == EPlayerColor::PLAYER_BLACK)
	{
		PieceColor = FLinearColor::Black;
		PlayerColor = FLinearColor::Black;
	}
	else if (Player == EPlayerColor::PLAYER_WHITE)
	{
		PieceColor = FLinearColor::White;
		PlayerColor = FLinearColor::White;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Wrong Piece Color Integer"));
	}

	GetComponents<UStaticMeshComponent>(Components);

	//Get the Static Mesh Component
	pDynamicMaterial = UMaterialInstanceDynamic::Create(pObjectMesh->GetMaterial(0), this);

	//Set the tint parameter to Black or White
	pDynamicMaterial->SetVectorParameterValue("Tint", PieceColor);
	pObjectMesh->SetMaterial(0, pDynamicMaterial);

	IsHighlighted = false;

	pBoard = Board;
}

bool ATile::GetTileIsOccupied()
{
	if (IsOccupied == EPlayerColor::PLAYER_NONE)
		return false;
	return true;
}

void ATile::SetTileIsOccupied(EPlayerColor Status, APiece* pOccupyingPiece)
{
	IsOccupied = Status;
	pOccupiedBy = TWeakObjectPtr<APiece>(pOccupyingPiece);
}

void ATile::SetBoardCoordinate(int XCoord, int YCoord)
{
	BoardCoordinate.X = XCoord;
	BoardCoordinate.Y = YCoord;
}

FVector2D ATile::GetBoardCoordinate()
{
	return BoardCoordinate;
}

APiece* ATile::GetOccupyingPiece()
{
	if (!pOccupiedBy.Get())
	{
		APiece* error = GetWorld()->SpawnActor<APiece>(TSubclassOf<APiecePawn>(), pObjectMesh->GetSocketLocation(FName("Piece")), pObjectMesh->GetSocketRotation(FName("Piece")));
		UE_LOG(LogTemp, Error, TEXT("Tile %s piece is nullptr!"), *this->GetName());
		return error;
	}
	return pOccupiedBy.Get();
}

UMaterialInstanceDynamic* ATile::GetDynamicMaterial()
{
	return pDynamicMaterial;
}

ATile* ATile::GetTileInDirection(ETileDirection PrimaryDirection, ETileDirection SecondaryDirection)
{
	if((int)SecondaryDirection < 0)
	{ 
		return pNeighbors[(int)PrimaryDirection];
	}
	else
	{
		if (pNeighbors[(int)PrimaryDirection])
		{
			return pNeighbors[(int)PrimaryDirection]->GetTileInDirection(SecondaryDirection);
		}
		else
		{
			return nullptr;
		}
	}
	return nullptr;
}

void ATile::ChangeTint(FColor Color)
{
	FLinearColor CurrentColor;

	pDynamicMaterial->GetVectorParameterValue(FName("Tint"), CurrentColor);

	if ((CurrentColor != FLinearColor::Black) && (CurrentColor != FLinearColor::White))
	{
		pDynamicMaterial->SetVectorParameterValue("Tint", PlayerColor);
	}
	else
	{
		pDynamicMaterial->SetVectorParameterValue("Tint", Color);
	}
}

bool ATile::ChangeHighlight()
{
	pDynamicMaterial = Cast<UMaterialInstanceDynamic>(pObjectMesh->GetMaterial(0));

	//If piece is not highlighted, highlight it, else remove highlight
	if (!IsHighlighted)
	{
		pDynamicMaterial->SetVectorParameterValue("Tint", FLinearColor::Red);
		IsHighlighted = true;
	}
	else
	{
		pDynamicMaterial->SetVectorParameterValue("Tint", PlayerColor);
		IsHighlighted = false;
	}

	return IsHighlighted;
}