// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "TBPlayerController.h"
#include "Commands/Command.h"
#include "Commands/MoveCommand.h"



// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	if (auto PlayerController = GWorld->GetFirstPlayerController<ATBPLayerController>())
	{
		PlayerController->GameManager = this;
	}

	if (Levels.IsValidIndex(CurrentLevel))
	{
		CreateLevelActors(Levels[CurrentLevel]);
	}
}

void AGameManager::CreateLevelActors(FSLevelInfo& Info)
{
	ThePlayer = nullptr;

	for (auto UnitInfo : Info.Units)
	{
		if (AGameSlot* Slot = GameGrid->GetSlot(UnitInfo.StartPosition))
		{
			Slot->SpawnUnitHere(UnitInfo.UnitClass);
			if (Slot->Unit && Slot->Unit->IsControlledByThePlayer())
			{
				ThePlayer = Slot->Unit;
			}
		}
	}
}

void AGameManager::OnActorClicked(AActor* Actor, FKey button)
{
	if (CurrentCommand.IsValid() && CurrentCommand->IsExecuting()) return;

	AGameSlot* Slot = Cast<AGameSlot>(Actor);

	// Clicked on a non slot actor?
	if (!Slot) return;

	// Does the player clicked?
	if (!ThePlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("No player unit detected!"))
			return;
	}

	// Empty slot?
	if (Slot->Unit == nullptr)
	{
		// Move player
		TSharedRef<MoveCommand> Cmd =
			MakeShared<MoveCommand>(ThePlayer->Slot->GridPosition, Slot->GridPosition);
		CommandPool.Add(Cmd);
		Cmd->Execute();
		CurrentCommand = Cmd;
	}
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentCommand.IsValid())
	{
		CurrentCommand->Update(DeltaTime);
	}

}

bool AGameManager::UndoLastMove()
{
	if (CommandPool.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-3, 4.f, FColor::Red, TEXT("Undo Couldn't completed!!!!"));
		return false;
	}

	TSharedRef <MoveCommand> PreviousMove = StaticCastSharedRef<MoveCommand>(CommandPool.Pop());
	PreviousMove->Revert();

	GEngine->AddOnScreenDebugMessage(-3, 4.f, FColor::White, TEXT("Undo Completed"));
	return true;
}

