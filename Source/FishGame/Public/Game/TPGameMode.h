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

	UFUNCTION(BlueprintCallable)
		float GetRemainTimeRate();

	virtual void Tick(float DeltaSeconds) override;

private:
	/** 최대 시간 */
	UPROPERTY()
		float MaxRemainTime;

	/** 남은 시간 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Time")
		float RemainTime;

	/** 최고 점수 */
	UPROPERTY()
		float MaxScore;

	/** 현재 점수: 시간 남으면 구현할 것 */
	UPROPERTY()
		float Score;

	/** 최고 점수: 시간 남으면 구현할 것 */
	UPROPERTY()
		float HighScore;

	/** 게임 종료 여부 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category="GameState")
		bool bMatchEnded;
};
