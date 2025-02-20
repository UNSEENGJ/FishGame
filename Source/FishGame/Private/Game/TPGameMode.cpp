﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TPGameMode.h"
#include <Kismet/GameplayStatics.h>

ATPGameMode::ATPGameMode()
{
	MaxRemainTime = 0.f;
	RemainTime = 0.f;


	bDelayedStart = true;
}

void ATPGameMode::StartMatch()
{
	// 시간 초기화
	SetMaxRemainTime(45.f);

	// 점수 초기화
	MaxScore = 500.f;
	Score = MaxScore;

	Super::StartMatch();

	// @TODO_Caspian 게임 시작 - 3초 딜레이 후 Input 입력 시작
}

void ATPGameMode::EndMatch()
{
	FName OutroLevelName = FName(TEXT("Level"));

	Super::EndMatch();

	//UGameplayStatics::OpenLevel(this, OutroLevelName, true);

	ShowResultWindow();
	// @TODO_Capian Open Level To show score
}

void ATPGameMode::BeginPlay()
{
	FTimerHandle MyTimerHandle;

	Super::BeginPlay();

	TryToStartMatch();
	// GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ATPGameMode::TryToStartMatch, 3, false);
}

void ATPGameMode::SetMaxRemainTime(float InMaxRemainTime)
{
	MaxRemainTime = InMaxRemainTime;
	RemainTime = MaxRemainTime;
}

void ATPGameMode::UpdateRemainTime(float InNewRemainTime)
{
	RemainTime -= InNewRemainTime;

	if (RemainTime <= 0)
	{	
		TryToEndMatch(true);
		SetGameResult(ETPGameResult::ETPGameResult_Trash);
	}
}

void ATPGameMode::UpdateScore(float InValue)
{
	Score -= InValue;

	// UE_LOG(LOG_TEMP, LOG, TEXT("Score is %f"), Score);

	if (Score <= 0)
	{
		TryToEndMatch(true);
		SetGameResult(ETPGameResult::ETPGameResult_Trash);
	}
}

void ATPGameMode::SetHighScore(float InNewHighScore)
{
	// @TODO_Caspian �ְ� ������ �̸��� �ð��Ǹ� ����
	// @TODO_Caspian 최고 점수와 이름은 시간되면 구현
}

void ATPGameMode::TryToStartMatch()
{
	if (IsMatchInProgress() == false)
	{
		bDelayedStart = false;
		bStartMatch = true;
	}
}

void ATPGameMode::TryToEndMatch(bool bInEndMatch)
{
	if(IsMatchInProgress() && bMatchEnded != bInEndMatch)
	{
		ETPGameResult DesiredGameResult;

		DesiredGameResult = ETPGameResult::ETPGameResult_Trash;
		if (Score > 350.f)
		{
			DesiredGameResult = ETPGameResult::ETPGameResult_Perfect;
		}
		else if (Score > 150.f)
		{
			DesiredGameResult = ETPGameResult::ETPGameResult_Hmm;
		}
		else
		{
			DesiredGameResult = ETPGameResult::ETPGameResult_Trash;
		}

		SetGameResult(DesiredGameResult);
		bMatchEnded = bInEndMatch;
	}
}

float ATPGameMode::GetRemainTimeRate()
{
	if(MaxRemainTime != 0.f)
	{
		return 1 - (RemainTime / MaxRemainTime);
	}

	return 0.f;
}

void ATPGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsMatchInProgress())
	{
		UpdateRemainTime(DeltaSeconds);
	}
}

ETPGameResult ATPGameMode::GetGameResult()
{
	return GameResult;
}

void ATPGameMode::SetGameResult(ETPGameResult InGameResult)
{
	GameResult = InGameResult;
}
