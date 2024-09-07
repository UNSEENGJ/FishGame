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
	
	virtual void BeginPlay() override;

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
		void TryToStartMatch();

	UFUNCTION()
		void TryToEndMatch(bool bInEndMatch);

	UFUNCTION(BlueprintCallable)
		float GetRemainTimeRate();

	virtual void Tick(float DeltaSeconds) override;

private:
	/** �ִ� �ð� */
	UPROPERTY()
		float MaxRemainTime;

	/** ���� �ð� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Time")
		float RemainTime;

	/** �ְ� ���� */
	UPROPERTY()
		float MaxScore;

	/** ���� ����: �ð� ������ ������ �� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Score")
		float Score;

	/** �ְ� ����: �ð� ������ ������ �� */
	UPROPERTY()
		float HighScore;

	/** ���� ���� ���� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "GameState")
		bool bStartMatch;

	/** ���� ���� ���� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category="GameState")
		bool bMatchEnded;
};
