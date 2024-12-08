// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameSlot.h"
#include "GameManager.h"
#include "TBPLayerController.generated.h"

/**
 *
 */
UCLASS()
class LABWORK2_API ATBPLayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATBPLayerController();

	void BeginPlay() override;

	void OnActorClicked(AActor* Slot, FKey key);

	UPROPERTY(BlueprintReadWrite)
	AGameManager* GameManager;
};