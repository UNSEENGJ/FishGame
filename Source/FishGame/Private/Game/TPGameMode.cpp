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

	// �ð� �ʱ�ȭ
	SetMaxRemainTime(45.f);

	// ���� �ʱ�ȭ
	UpdateScore(0.f);

	// @TODO_Caspian ���� ���� - 3�� ����� �� Input �Է� ����
}

void ATPGameMode::EndMatch()
{
	FName OutroLevelName = FName(TEXT("Level"));

	Super::EndMatch();

	//UGameplayStatics::OpenLevel(this, OutroLevelName, true);


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

	if (Score <= 0)
	{
		TryToEndMatch(true);
	}
}

void ATPGameMode::SetHighScore(float InNewHighScore)
{
	// @TODO_Caspian �ְ� ������ �̸��� �ð��Ǹ� ����
}

void ATPGameMode::TryToEndMatch(bool bInEndMatch)
{
	if(bMatchEnded != bInEndMatch)
	{
		bMatchEnded = bInEndMatch;
	}
}

float ATPGameMode::GetRemainTimeRate()
{
	if(MaxRemainTime != 0.f)
	{
		return RemainTime / MaxRemainTime;
	}

	return 0.f;
}

void ATPGameMode::Tick(float DeltaSeconds)
{
	float DesiredRemainTime;

	Super::Tick(DeltaSeconds);

	if (IsMatchInProgress())
	{
		DesiredRemainTime = RemainTime - DeltaSeconds;
		UpdateRemainTime(DesiredRemainTime);
	}
}
