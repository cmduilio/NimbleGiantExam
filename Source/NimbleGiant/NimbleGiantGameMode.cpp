// Copyright Epic Games, Inc. All Rights Reserved.

#include "NimbleGiantGameMode.h"
#include "NimbleGiantHUD.h"
#include "NimbleGiantCharacter.h"
#include "PS_NimbleGiant.h"
#include "UObject/ConstructorHelpers.h"
#include "GS_Nimble.h"

ANimbleGiantGameMode::ANimbleGiantGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ANimbleGiantHUD::StaticClass();

	CubesLeft = 28;
	Winner = "";
	ScoreWinner = 0;
}

void ANimbleGiantGameMode::CubeHit(ABlock* block, ANimbleGiantCharacter* Player)
{
	if (AGS_Nimble* GS = GetGameState<AGS_Nimble>()) {

		TSet<FString> Cubes;

		int32 Count = DoWhenHit(&Cubes, block);
		int32 Score = CalculateScoreWithFibonacci(Count);

		if (APS_NimbleGiant* PS = Player->GetPlayerState<APS_NimbleGiant>())
		{
			PS->AddScore(Score);

			if (PS->GetScore() > ScoreWinner) {
				ScoreWinner = PS->GetScore();
				Winner = Player->GetName();
			}
		}

		CubesLeft -= Count;

		if (CubesLeft == 0) {

			for (APlayerState* PS : GS->PlayerArray)
			{
				if (APlayerController* Controller = PS->GetOwner<APlayerController>())
				{
					if (ANimbleGiantCharacter* Character = Controller->GetPawn<ANimbleGiantCharacter>())
					{
						bool IsWinner = Winner == Character->GetName();
						Character->AddWidgetEndEvent(IsWinner);
					}

					Controller->SetPause(true);
				}
			}
		}
	}
}

int32 ANimbleGiantGameMode::DoWhenHit(TSet<FString>* Cubes, ABlock* Block) {

	int32 Count = 1;
	TSet<AActor*> Hits;
	(*Cubes).Add(Block->GetName());

	Block->GetNeighbors(&Hits);

	Block->Destroy();

	for (AActor* Hit : Hits) {
		if (ABlock* NextBlock = Cast<ABlock>(Hit))
		{
			if (!(*Cubes).Contains(NextBlock->GetName()) && NextBlock->GetColorIndex() == Block->GetColorIndex())
			{
				(*Cubes).Add(NextBlock->GetName());
				Count += DoWhenHit(Cubes, NextBlock);
			}

		}
	}
	return Count;
}

int32 ANimbleGiantGameMode::CalculateScoreWithFibonacci(int32 Number) {
	int32 Previous = 0;
	int32 Now = 1;
	int32 Sum = 1;

	for (int index = 2; index <= Number; index++)
	{
		Sum += Previous + Now;
		Now = Previous + Now;
		Previous = Now - Previous;
	}
	return Sum;
}