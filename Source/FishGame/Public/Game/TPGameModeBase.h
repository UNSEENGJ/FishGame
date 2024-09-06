// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FISHGAME_API ATPGameModeBase : public AGameMode
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
		void SetMaxRemainTime(float InRemainTime);

private:
	UPROPERTY()
		float MaxRemainTime;

	UPROPERTY()
		float CurrentRemainTime;

	UPROPERTY()

};
