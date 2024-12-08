// Fill out your copyright notice in the Description page of Project Settings.


#include "TBPLayerController.h"

ATBPLayerController::ATBPLayerController()
{

}


void ATBPLayerController::BeginPlay()
{
	bEnableClickEvents = true;
	bShowMouseCursor = true;
	ClickEventKeys.AddUnique(EKeys::RightMouseButton);
}

void ATBPLayerController::OnActorClicked(AActor* Actor, FKey key)
{
	UE_LOG(LogTemp, Warning, TEXT("OnClicked: %s - %s"), *Actor->GetActorLabel(), *key.ToString());
	if (GameManager) GameManager->OnActorClicked(Actor, key);
}

