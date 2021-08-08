// Fill out your copyright notice in the Description page of Project Settings.


#include "Net/UnrealNetwork.h"
#include "NimbleGiantCharacter.h"
#include "PS_NimbleGiant.h"

APS_NimbleGiant::APS_NimbleGiant()
{
	SetScore(0);
}


void APS_NimbleGiant::AddScore(int32 Points)
{
	if (HasAuthority()) {
		SetScore(GetScore() + Points);
		ForceNetUpdate();
	}
}
