// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Chess3DDemo.h"


// Sets default values
ATile::ATile() : pNeighbors{ nullptr,nullptr,nullptr,nullptr }, pOccupiedBy{ nullptr }, IsOccupied{ EPlayerColor::PLAYER_NONE }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	RootComponent = pObjectMesh;
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

void ATile::InitializePiece(EPlayerColor Player)
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
	return pOccupiedBy.Get();
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