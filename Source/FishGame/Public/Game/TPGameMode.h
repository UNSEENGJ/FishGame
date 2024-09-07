// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TPGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FISHGAME_API ATPGameMode : public AGameMode
{
	GENERATED_BODY()

	virtual void StartMatch() override;

	virtual void EndMatch() override;
	
public:
	ATPGameMode();

	UFUNCTION()
		void SetMaxRemainTime(float InMaxRemainTime);

	UFUNCTION()
		void UpdateRemainTime(float InNewRemainTime);

	UFUNCTION()
		void UpdateScore(float InNewScore);

	UFUNCTION()
		void SetHighScore(float InNewHighScore);

	UFUNCTION()
		void TryToEndMatch(bool bInEndMatch);

private:
	/** �ִ� �ð� */
	UPROPERTY()
		float MaxRemainTime;

	/** ���� �ð� */
	UPROPERTY()
		float RemainTime;

	/** �ְ� ���� */
	UPROPERTY()
		float MaxScore;

	/** ���� ����: �ð� ������ ������ �� */
	UPROPERTY()
		float Score;

	/** �ְ� ����: �ð� ������ ������ �� */
	UPROPERTY()
		float HighScore;

	/** ���� ���� ���� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category="GameState")
		bool bMatchEnded;
};
