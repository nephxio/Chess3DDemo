// Fill out your copyright notice in the Description page of Project Settings.

#include "Mouse_PlayerController.h"
#include "Chess3DDemo.h"

AMouse_PlayerController::AMouse_PlayerController()
{

}

void AMouse_PlayerController::BeginPlay()
{
	bEnableClickEvents = true;
	bShowMouseCursor = true;

	InputComponent->BindAction("MouseLeftClicked", IE_Pressed, this, &AMouse_PlayerController::ClickOnObject);
}

void AMouse_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMouse_PlayerController::ClickOnObject()
{
	FHitResult ClickResult;
	if (GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ClickResult))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s was clicked."), *ClickResult.Actor->GetName());
	}
}

