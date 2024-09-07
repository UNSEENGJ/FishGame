// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "Components/SplineMeshComponent.h"
#include "Components/SplineComponent.h"
#include "FishGame/Character/TPPlayerPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineUtils.h"
#include <Game/TPGameMode.h>
#include <Kismet/GameplayStatics.h>
#include <Game/TPGameMode.h>


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
		EnhancedInputComponent->BindAction(CutAction, ETriggerEvent::Triggered, this, &ATPPlayerController::Cut);
	}

}

void ATPPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	bShowMouseCursor = true;

	Search();
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

void ATPPlayerController::Cut()
{
	//반복문 검사 Spline
	Move();
	CalculateScore();
}

void ATPPlayerController::Move()
{
	if (Knife)
	{
		FHitResult HitResult;

		bool bHitSuccessful = GetHitResultUnderCursor(ECC_Visibility, true, HitResult);

		if (bHitSuccessful)
		{
			FVector Loc = HitResult.Location;

			Loc.Z = Knife->GetActorLocation().Z;

			Knife->SetActorLocation(Loc);
		}
	}
}

void ATPPlayerController::CalculateScore()
{
	float MinDist = 987654321.f;

	if (SplineBone && Knife)
	{
		//TArray SplineMesh 가져오기
		//for문 돌면서
		int32 SplineLen = SplineBone->GetNumberOfSplinePoints();

		for (int Idx = 0; Idx < SplineLen-1; Idx++)
		{
			FVector PointPos = SplineBone->GetLocationAtSplinePoint(Idx, ESplineCoordinateSpace::World);
			FVector Loc = Knife->GetActorLocation();
			Loc.Z = 0;
			PointPos.Z = 0;

			float Dist = FVector::Dist(PointPos, Loc);

			MinDist = FMath::Min(MinDist, Dist);
		}

	}
	
	ATPGameMode* TPGameMode = Cast<ATPGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	float DesiredScoreDifference;
	float ScoreAdjustmentFactor = 0.1f;

	if (TPGameMode)
	{
		DesiredScoreDifference = MinDist * ScoreAdjustmentFactor;
		TPGameMode->UpdateScore(DesiredScoreDifference);
	}
}

void ATPPlayerController::Search()
{
	UWorld* CurrentWorld = GetWorld();

	for (TActorIterator<AActor> It(CurrentWorld); It; ++It)
	{
		FString Name = It->GetName();

		if (Name.Contains("Knife"))
		{
			Knife = *It;
		}

		if (Name.Contains("BoneLine"))
		{
			SplineBone = It->GetComponentByClass<USplineComponent>();
		}
	}
}


