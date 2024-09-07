// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPlayerPawn.h"
#include "Camera/CameraComponent.h"
// Sets default values
ATPPlayerPawn::ATPPlayerPawn()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(-90.f,0.f,0.f));

}

void ATPPlayerPawn::BeginPlay()
{
	Super::BeginPlay();


	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
}




