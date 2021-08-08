// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PS_NimbleGiant.generated.h"

/**
 * 
 */
UCLASS()
class NIMBLEGIANT_API APS_NimbleGiant : public APlayerState
{
	GENERATED_BODY()
	
public: 

	APS_NimbleGiant();

	void AddScore(int32 Points);
};
