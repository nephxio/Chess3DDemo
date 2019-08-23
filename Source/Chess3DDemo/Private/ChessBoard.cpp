// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessBoard.h"
#include "Chess3DDemo.h"
#include "Piece.h"


// Sets default values
AChessBoard::AChessBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AChessBoard::BeginPlay()
{

	Super::BeginPlay();

	SpawnBoard();

	LinkTiles();

	SpawnInitialPlayerPieces();
}

// Called every frame
void AChessBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChessBoard::LinkTiles()
{
	//quick and dirty linking of adjacent tiles
	for (int i = 0; i < Board.Num(); i++)
	{
		if (Board[i]->GetBoardCoordinate().X - 1 >= 1)
		{
			Board[i]->SetAdjacentTile(TILE_WEST, GetTile(Board[i]->GetBoardCoordinate().X - 1, Board[i]->GetBoardCoordinate().Y));
		}
		if (Board[i]->GetBoardCoordinate().X + 1 <= 8)
		{
			Board[i]->SetAdjacentTile(TILE_EAST, GetTile(Board[i]->GetBoardCoordinate().X + 1, Board[i]->GetBoardCoordinate().Y));
		}
		if (Board[i]->GetBoardCoordinate().Y - 1 >= 1)
		{
			Board[i]->SetAdjacentTile(TILE_SOUTH, GetTile(Board[i]->GetBoardCoordinate().X, Board[i]->GetBoardCoordinate().Y - 1));
		}
		if (Board[i]->GetBoardCoordinate().Y + 1 <= 8)
		{
			Board[i]->SetAdjacentTile(TILE_NORTH, GetTile(Board[i]->GetBoardCoordinate().X, Board[i]->GetBoardCoordinate().Y + 1));
		}
	}
}

APiece* AChessBoard::SpawnPiece(ATile* pTile, TSubclassOf<APiece> PieceToSpawn, EPlayerColor Player)
{
	APiece* pPiece;
	TArray<UStaticMeshComponent*> Components;
	pTile->GetComponents<UStaticMeshComponent>(Components);
	
	pPiece = GetWorld()->SpawnActor<APiece>(PieceToSpawn, Components[0]->GetSocketLocation("Piece"), Components[0]->GetSocketRotation("Piece"));

	pPiece->InitializePiece(Player);

	if (Player == EPlayerColor::PLAYER_BLACK)
	{
		PlayerBlack.Add(pPiece);
	}
	else if (Player == EPlayerColor::PLAYER_WHITE)
	{
		PlayerWhite.Add(pPiece);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Probably forgot to set a Player Color"));
		return nullptr;
	}

	pPiece->SetOccupyingTile(pTile);
//	pPiece->SetBoardReference(this);

	return pPiece;
}

ATile* AChessBoard::GetTile(int x, int y)
{
	return Board[8*(y-1) + (x-1)];
}

void AChessBoard::SpawnBoard()
{
	ATile* SpawnedTile = nullptr;

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (!((x + y) % 2))
			{
				SpawnedTile = GetWorld()->SpawnActor<ATile>(TileBlueprint, FVector(y*200.0f, x*200.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
				SpawnedTile->InitializePiece(EPlayerColor::PLAYER_BLACK);
			}
			else
			{
				SpawnedTile = GetWorld()->SpawnActor<ATile>(TileBlueprint, FVector(y*200.0f, x*200.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
				SpawnedTile->InitializePiece(EPlayerColor::PLAYER_WHITE);
			}
			Board.Add(SpawnedTile);
			SpawnedTile->SetBoardCoordinate(x+1, y+1);
			UE_LOG(LogTemp, Warning, TEXT("Setting coordinate X=%d, Y=%d"), x, y);
		}
	}
}

void AChessBoard::SpawnInitialPlayerPieces()
{

	//spawn Black Pieces
	GetTile(1, 8)->SetTileIsOccupied(EPlayerColor::PLAYER_BLACK, SpawnPiece(GetTile(1, 8), Pieces[EPieceType::PIECE_ROOK], EPlayerColor::PLAYER_BLACK));
	GetTile(2, 8)->SetTileIsOccupied(EPlayerColor::PLAYER_BLACK, SpawnPiece(GetTile(2, 8), Pieces[EPieceType::PIECE_KNIGHT], EPlayerColor::PLAYER_BLACK));
	GetTile(3, 8)->SetTileIsOccupied(EPlayerColor::PLAYER_BLACK, SpawnPiece(GetTile(3, 8), Pieces[EPieceType::PIECE_BISHOP], EPlayerColor::PLAYER_BLACK));
	GetTile(4, 8)->SetTileIsOccupied(EPlayerColor::PLAYER_BLACK, SpawnPiece(GetTile(4, 8), Pieces[EPieceType::PIECE_QUEEN], EPlayerColor::PLAYER_BLACK));
	GetTile(5, 8)->SetTileIsOccupied(EPlayerColor::PLAYER_BLACK, SpawnPiece(GetTile(5, 8), Pieces[EPieceType::PIECE_KING], EPlayerColor::PLAYER_BLACK));
	GetTile(6, 8)->SetTileIsOccupied(EPlayerColor::PLAYER_BLACK, SpawnPiece(GetTile(6, 8), Pieces[EPieceType::PIECE_BISHOP], EPlayerColor::PLAYER_BLACK));
	GetTile(7, 8)->SetTileIsOccupied(EPlayerColor::PLAYER_BLACK, SpawnPiece(GetTile(7, 8), Pieces[EPieceType::PIECE_KNIGHT], EPlayerColor::PLAYER_BLACK));
	GetTile(8, 8)->SetTileIsOccupied(EPlayerColor::PLAYER_BLACK, SpawnPiece(GetTile(8, 8), Pieces[EPieceType::PIECE_ROOK], EPlayerColor::PLAYER_BLACK));


	//spawn White Pieces
	GetTile(1, 1)->SetTileIsOccupied(EPlayerColor::PLAYER_WHITE, SpawnPiece(GetTile(1, 1), Pieces[EPieceType::PIECE_ROOK], EPlayerColor::PLAYER_WHITE));
	GetTile(2, 1)->SetTileIsOccupied(EPlayerColor::PLAYER_WHITE, SpawnPiece(GetTile(2, 1), Pieces[EPieceType::PIECE_KNIGHT], EPlayerColor::PLAYER_WHITE));
	GetTile(2, 1)->GetOccupyingPiece()->SetActorRelativeRotation(FRotator(0.f, 180.f, 0.f));
	GetTile(3, 1)->SetTileIsOccupied(EPlayerColor::PLAYER_WHITE, SpawnPiece(GetTile(3, 1), Pieces[EPieceType::PIECE_BISHOP], EPlayerColor::PLAYER_WHITE));
	GetTile(4, 1)->SetTileIsOccupied(EPlayerColor::PLAYER_WHITE, SpawnPiece(GetTile(4, 1), Pieces[EPieceType::PIECE_QUEEN], EPlayerColor::PLAYER_WHITE));
	GetTile(5, 1)->SetTileIsOccupied(EPlayerColor::PLAYER_WHITE, SpawnPiece(GetTile(5, 1), Pieces[EPieceType::PIECE_KING], EPlayerColor::PLAYER_WHITE));
	GetTile(6, 1)->SetTileIsOccupied(EPlayerColor::PLAYER_WHITE, SpawnPiece(GetTile(6, 1), Pieces[EPieceType::PIECE_BISHOP], EPlayerColor::PLAYER_WHITE));
	GetTile(7, 1)->SetTileIsOccupied(EPlayerColor::PLAYER_WHITE, SpawnPiece(GetTile(7, 1), Pieces[EPieceType::PIECE_KNIGHT], EPlayerColor::PLAYER_WHITE));
	GetTile(7, 1)->GetOccupyingPiece()->SetActorRelativeRotation(FRotator(0.f, 180.f, 0.f));
	GetTile(8, 1)->SetTileIsOccupied(EPlayerColor::PLAYER_WHITE, SpawnPiece(GetTile(8, 1), Pieces[EPieceType::PIECE_ROOK], EPlayerColor::PLAYER_WHITE));

	//spawn Pawns
	for (int x = 0; x < 8; x++)
	{		
		GetTile(x+1, 2)->SetTileIsOccupied(EPlayerColor::PLAYER_WHITE, SpawnPiece(GetTile(x + 1, 2), Pieces[EPieceType::PIECE_PAWN], EPlayerColor::PLAYER_WHITE));
		GetTile(x+1, 7)->SetTileIsOccupied(EPlayerColor::PLAYER_BLACK, SpawnPiece(GetTile(x + 1, 7), Pieces[EPieceType::PIECE_PAWN], EPlayerColor::PLAYER_BLACK));
	}
	
}

void AChessBoard::MovePiece(ATile* pDestinationTile, APiece* pPieceToMove)
{
	FTransform SocketLocation,MoveLocation;
	TArray<UStaticMeshComponent*> Components;
	pDestinationTile->GetComponents<UStaticMeshComponent>(Components);

	if (pPieceToMove->GetOccupyingTile())
	{
		pPieceToMove->GetOccupyingTile()->SetTileIsOccupied(EPlayerColor::PLAYER_NONE, nullptr);
	}
		
	//SocketLocation.SetComponents(Components[0]->GetSocketRotation("Piece").Quaternion(), Components[0]->GetSocketLocation("Piece"), pPieceToMove->GetActorScale());

	////Ensure Knights don't turn around
	//MoveLocation.SetLocation(SocketLocation.GetLocation());
	//MoveLocation.SetRotation(pPieceToMove->GetActorRotation().Quaternion());
	//MoveLocation.SetScale3D(pPieceToMove->GetActorScale()); //ensure the piece doesn't resize if we set custom sizes in the blueprint
	//

	//pPieceToMove->SetActorTransform(MoveLocation);

	pPieceToMove->SetActorLocation(Components[0]->GetSocketLocation("Piece"));

	if (pDestinationTile)
	{
		pPieceToMove->SetOccupyingTile(pDestinationTile);
	}

	pPieceToMove->SetIsHighlighted();
}