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
#include "NiagaraFunctionLibrary.h"


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
	
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NE(TEXT("/Script/Niagara.NiagaraSystem'/Game/Vefects/Blood_VFX/VFX/Performance_Versions/Bullet_Hits/One_Shot/OS_NS_Bullet_Hit_Tiny_ZeroGravity.OS_NS_Bullet_Hit_Tiny_ZeroGravity'"));
	if (NE.Succeeded())
	{
		FXSystem = NE.Object;
	}
	
	bIsStart = false;
}

void ATPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(CutAction, ETriggerEvent::Started, this, &ATPPlayerController::StartCut);
		EnhancedInputComponent->BindAction(CutAction, ETriggerEvent::Triggered, this, &ATPPlayerController::Cut);
		EnhancedInputComponent->BindAction(CutAction, ETriggerEvent::Completed, this, &ATPPlayerController::EndCut);
	}

}

void ATPPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	bShowMouseCursor = true;

	Search();
	SettingIMC();

	CachedTPGameMode = Cast<ATPGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
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

void ATPPlayerController::StartCut()
{

	FHitResult HitResult;
	bool bHitSuccessful = GetHitResultUnderCursor(ECC_GameTraceChannel1, true, HitResult);
	if (bHitSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Start"));

		if (bIsStart)
		{
			UE_LOG(LogTemp, Log, TEXT("도착 %lf %lf"),PassedDist, MaxDist);
			bIsStart = false;
			if (CachedTPGameMode)
			{
				CachedTPGameMode->TryToEndMatch(true);
				if (PassedDist < MaxDist)
				{
					CachedTPGameMode->SetGameResult(ETPGameResult::ETPGameResult_Trash);
				}
			}
			return;
		}
		bIsStart = true;
		PassedDist = 0;
		PrePos = HitResult.Location;
		PrePos.Z = 0;
	}
}

void ATPPlayerController::Cut()
{
	Move();
	if (bIsStart == false) return;
	//반복문 검사 Spline
	CalculateScore();
}

void ATPPlayerController::EndCut()
{
	StartCut();

	if (CachedTPGameMode)
	{
		CachedTPGameMode->UpdateRemainTime(3.f);
	}
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
			UNiagaraComponent* ActiveEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FXSystem, Loc,FRotator::ZeroRotator, FVector(0.1f));

			// if (ActiveEffect)
			// {
			// 	ActiveEffect->Activate();
			// }
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
		int MinIdx = 0;
		PrePos.Z = 0;
		for (int Idx = 0; Idx < SplineLen-1; Idx++)
		{
			FVector PointPos = SplineBone->GetLocationAtSplinePoint(Idx, ESplineCoordinateSpace::World);
			FVector Loc = Knife->GetActorLocation();
			Loc.Z = 0;
			PointPos.Z = 0;

			float Dist = FVector::Dist(PointPos, Loc);

			if (MinDist > Dist)
			{
				MinDist = Dist;
				MinIdx = Idx;
			}
		}

		FVector CurrentPos = SplineBone->GetLocationAtSplinePoint(MinIdx, ESplineCoordinateSpace::World);
		CurrentPos.Z = 0;
		float Dist = FVector::Dist(PrePos, CurrentPos);
		PassedDist += Dist;

		PrePos = CurrentPos;
	}
	
	
	float DesiredScoreDifference;
	float ScoreAdjustmentFactor = 0.1f;

	if (CachedTPGameMode)
	{
		DesiredScoreDifference = MinDist * ScoreAdjustmentFactor;
		CachedTPGameMode->UpdateScore(DesiredScoreDifference);
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
			MaxDist = SplineBone->GetSplineLength();
		}
	}
}


