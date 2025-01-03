// Fill out your copyright notice in the Description page of Project Settings.


#include "NetPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "NetBaseCharacter.h"

void ANetPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetPlayerState, Data);
	DOREPLIFETIME(ANetPlayerState, PlayerIndex);
}

void ANetPlayerState::OnRep_PlayerInfo()
{
	ANetBaseCharacter* Character = Cast<ANetBaseCharacter>(GetPawn());
	if (Character) Character->bPlayerInfoReceived = true;
	else
	{
		FTimerHandle PlayerInfoUpdateTimer;
		GWorld->GetTimerManager().SetTimer(PlayerInfoUpdateTimer,this,
			&ANetPlayerState::OnRep_PlayerInfo, .25f, false);
	}
};