// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Mouse_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CHESS3DDEMO_API AMouse_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	//Default Constructor
	AMouse_PlayerController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ClickOnObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
};
