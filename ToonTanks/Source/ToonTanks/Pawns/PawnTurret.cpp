// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
	//	GetWorldTimerManager()	같음.
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction() 
{
	Super::HandleDestruction();
	Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange) {
		return;
		
	}
	if (!PlayerPawn->GetIsPlayerAlive()) {
		UE_LOG(LogTemp, Warning, TEXT("ACtor died"));
		SetActorTickEnabled(false);
	}
	RotateTurret(PlayerPawn->GetActorLocation());	
}
void APawnTurret::CheckFireCondition() 
{
	// if player == null || is dead then bail
	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive()) {
		return;
	}
	// If player 가 사거리 내로 왔을 때 FIRE
	if (ReturnDistanceToPlayer() <= FireRange) {		
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn) {
		return 0.0f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());	
}

