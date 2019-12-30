// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Piece.h"
#include "ChessPlayerPawn.generated.h"

UCLASS()
class CHESS3DDEMO_API AChessPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AChessPlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetPieceList(TArray<class APiece*> InArray) { ChessPieces = InArray; }

	FORCEINLINE TArray<APiece*> GetPieceList() const { return ChessPieces; }

	FORCEINLINE void AddPieceToList(APiece* Piece) { ChessPieces.Add(Piece); }
	
	int FindPiece(APiece* Piece) const;

	FORCEINLINE void SetPlayerColor(EPlayerColor Color) { PlayerColor = Color; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	



protected:
	TArray<APiece*> ChessPieces;

	EPlayerColor PlayerColor;
};
