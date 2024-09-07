// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "TPPlayerController.generated.h"

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

private:

	/*Mouse Input*/
	void OnSetCutInputStarted();
	void OnSetCutTriggered();
	void OnSetCutReleased();

	void SettingIMC();
};
