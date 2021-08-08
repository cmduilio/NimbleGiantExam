// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NimbleGiant/Block.h"
#include "NimbleGiant/NimbleGiantCharacter.h"
#include "NimbleGiantGameMode.generated.h"

UCLASS(minimalapi)
class ANimbleGiantGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:

	int32 CubesLeft;

	FString Winner;
	int32 ScoreWinner;


public:
	ANimbleGiantGameMode();

	void CubeHit(ABlock* Block, ANimbleGiantCharacter* Player);

	int32 DoWhenHit(TSet<FString>* Cubes, ABlock* Block);

	int32 CalculateScoreWithFibonacci(int32 Number);

};



