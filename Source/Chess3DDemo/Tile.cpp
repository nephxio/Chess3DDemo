// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Chess3DDemo.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pOccupiedBy = nullptr;

	pNeighbors[0] = nullptr;
	pNeighbors[1] = nullptr;
	pNeighbors[2] = nullptr;
	pNeighbors[3] = nullptr;

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	RootComponent = ObjectMesh;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::InitializePiece(int Player)
{
	FLinearColor PieceColor;
	TArray<UStaticMeshComponent*> Components;

	if (Player == PLAYER_BLACK)
	{
		PieceColor = COLOR_BLACK;
		PlayerColor = COLOR_BLACK;
	}
	else if (Player == PLAYER_WHITE)
	{
		PieceColor = COLOR_WHITE;
		PlayerColor = COLOR_WHITE;
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

	IsHighlighted = false;
}

bool ATile::GetTileIsOccupied()
{
	if (IsOccupied == 0)
		return false;
	return true;
}

void ATile::SetTileIsOccupied(int Status, APiece* pOccupyingPiece)
{
	IsOccupied = Status;
	pOccupiedBy = pOccupyingPiece;
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
	return pOccupiedBy;
}

UMaterialInstanceDynamic* ATile::GetDynamicMaterial()
{
	return pDynamicMaterial;
}

ATile* ATile::GetTileInDirection(int PrimaryDirection, int SecondaryDirection)
{
	if(SecondaryDirection < 0)
	{ 
		return pNeighbors[PrimaryDirection];
	}
	else
	{
		if (pNeighbors[PrimaryDirection])
		{
			return pNeighbors[PrimaryDirection]->GetTileInDirection(SecondaryDirection);
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

	if ((CurrentColor != COLOR_BLACK) && (CurrentColor != COLOR_WHITE))
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
	TArray<UStaticMeshComponent*> Components;

	GetComponents<UStaticMeshComponent>(Components);

	pDynamicMaterial = Cast<UMaterialInstanceDynamic>(Components[0]->GetMaterial(0));

	//If piece is not highlighted, highlight it, else remove highlight
	if (IsHighlighted)
	{
		pDynamicMaterial->SetScalarParameterValue("Intensity", 1.0f);
	}
	else
	{
		pDynamicMaterial->SetScalarParameterValue("Intensity", 0.0f);
	}

	return IsHighlighted;
}