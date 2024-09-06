// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

ATPPlayerController::ATPPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> CutActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/InputAction/IA_Cut.IA_Cut'"));

	if (CutActionRef.Object)
	{
		CutAction = CutActionRef.Object;
	}

	//InputContext Mapping
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputContextMappingRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Input.IMC_Input'"));

	if (InputContextMappingRef.Object)
	{
		InputMappingContext = InputContextMappingRef.Object;
	}

}

void ATPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(CutAction, ETriggerEvent::Started, this, &ATPPlayerController::OnSetCutInputStarted);
		EnhancedInputComponent->BindAction(CutAction, ETriggerEvent::Triggered, this, &ATPPlayerController::OnSetCutTriggered);
		EnhancedInputComponent->BindAction(CutAction, ETriggerEvent::Completed, this, &ATPPlayerController::OnSetCutReleased);
		EnhancedInputComponent->BindAction(CutAction, ETriggerEvent::Canceled, this, &ATPPlayerController::OnSetCutReleased);
	}

}

void ATPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
	
	SettingIMC();
}

void ATPPlayerController::SettingIMC()
{
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->ClearAllMappings(); //모든 매핑 취소
		UInputMappingContext* NewMappingContext = InputMappingContext;

		if (NewMappingContext)
		{
			SubSystem->AddMappingContext(NewMappingContext, 0);
		}
	}
}

//필요없음. 움직임
void ATPPlayerController::OnSetCutInputStarted()
{
}

void ATPPlayerController::OnSetCutTriggered()
{
}

void ATPPlayerController::OnSetCutReleased()
{
}