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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = knife, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AActor> Knife;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = knife, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AActor> SplineBone;

private:

	/*Mouse Input*/
	void Cut();
	void Move();
	void CalculateScore();
	void Search();
	void SettingIMC();

};
