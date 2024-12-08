// Fill out your copyright notice in the Description page of Project Settings.


#include "Commands/MoveCommand.h"
#include "GameGrid.h"

MoveCommand::MoveCommand(FSGridPosition Src, FSGridPosition Dst) :
	Source(Src),
	Destination(Dst)
{

}

MoveCommand::~MoveCommand()
{
}

void MoveCommand::Execute()
{
	UE_LOG(LogTemp, Warning, TEXT("Executing MoveCommand... "));

	AGameSlot* SlotA = AGameGrid::FindSlot(Source);
	AGameSlot* SlotB = AGameGrid::FindSlot(Destination);

	AUnitBase* UnitA = SlotA->Unit;
	check(UnitA);
	UnitA->AssignToSlot(SlotB);
	SlotB->SetState(GS_Highlighted);
}

void MoveCommand::Revert()
{
	AGameSlot* SlotB = AGameGrid::FindSlot(Source);
	AGameSlot* SlotA = AGameGrid::FindSlot(Destination);
	check(SlotA && SlotB);

	AUnitBase* UnitA = SlotA->Unit;
	check(UnitA);
	UnitA->AssignToSlot(SlotB);
	SlotA->SetState(GS_Highlighted);
	SlotB->SetState(GS_Default);

	UE_LOG(LogTemp, Warning, TEXT("MoveCommand Reverted "));
}
