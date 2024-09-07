// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "TPPlayerController.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class FISHGAME_API ATPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ATPPlayerController();

protected:
	/*Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> CutAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;

protected:
	
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

protected:

	UPROPERTY()
	TObjectPtr<class AActor> Knife;
	UPROPERTY()
	TObjectPtr<class USplineComponent> SplineBone;

	UPROPERTY()
	TObjectPtr<class ATPGameMode> CachedTPGameMode;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	UNiagaraSystem* FXSystem;

private:

	FVector PrePos;
	uint8 bIsStart : 1;
	float PassedDist;
	float MaxDist;

private:

	void EndCut();
	void StartCut();
	/*Mouse Input*/
	void Cut();
	void Move();
	void CalculateScore();
	void Search();
	void SettingIMC();
};
