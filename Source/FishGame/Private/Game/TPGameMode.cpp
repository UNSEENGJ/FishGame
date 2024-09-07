// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TPGameMode.h"
#include <Kismet/GameplayStatics.h>

ATPGameMode::ATPGameMode()
{
	MaxRemainTime = 0.f;
	RemainTime = 0.f;
}

void ATPGameMode::StartMatch()
{
	Super::StartMatch();

	// 시간 초기화
	SetMaxRemainTime(150.f);

	// 점수 초기화
	UpdateScore(0.f);

	// @TODO_Caspian 게임 시작 - 3초 딜레이 후 Input 입력 시작
}

void ATPGameMode::EndMatch()
{
	FName OutroLevelName = FName(TEXT("Level"));

	Super::EndMatch();

	UGameplayStatics::OpenLevel(this, OutroLevelName, true);


	// @TODO_Capian Open Level To show score
}

void ATPGameMode::SetMaxRemainTime(float InMaxRemainTime)
{
	MaxRemainTime = InMaxRemainTime;
	RemainTime = MaxRemainTime;
}

void ATPGameMode::UpdateRemainTime(float InNewRemainTime)
{
	RemainTime = (InNewRemainTime > 0) ? InNewRemainTime : 0;

	if (RemainTime <= 0)
	{
		TryToEndMatch(true);
	}
}

void ATPGameMode::UpdateScore(float InNewScore)
{
	Score = InNewScore;
}

void ATPGameMode::SetHighScore(float InNewHighScore)
{
	// @TODO_Caspian 최고 점수와 이름은 시간되면 구현
}

void ATPGameMode::TryToEndMatch(bool bInEndMatch)
{
	if(bMatchEnded != bInEndMatch)
	{
		bMatchEnded = bInEndMatch;
	}
}
