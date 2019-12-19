 // Fill out your copyright notice in the Description page of Project Settings.


#include "ChessBoard.h"
#include "ChessGameMode.h"

AChessGameMode::AChessGameMode() : pBoard{ nullptr }
{

}

void AChessGameMode::BeginPlay()
{
	Super::BeginPlay();

	pBoard = GetWorld()->SpawnActor<AChessBoard>(boardBlueprint, FVector(0,0,0), FRotator(0,0,0));

	GetWorld()->Exec(GetWorld(), TEXT("r.setRes 1200x900w"));

}

void AChessGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}