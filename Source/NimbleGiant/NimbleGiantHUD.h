// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NimbleGiantHUD.generated.h"

UCLASS()
class ANimbleGiantHUD : public AHUD
{
	GENERATED_BODY()

public:
	ANimbleGiantHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

