// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TPGameModeBase.h"

void ATPGameModeBase::SetMaxRemainTime(float InRemainTime)
{
	MaxRemainTime = InRemainTime;
	CurrentRemainTime = MaxRemainTime;
}