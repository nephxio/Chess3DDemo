// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayerPawn.h"

// Sets default values
AChessPlayerPawn::AChessPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChessPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChessPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChessPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int AChessPlayerPawn::FindPiece(APiece* Piece) const
{
	return ChessPieces.Find(Piece);
}