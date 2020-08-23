// Fill out your copyright notice in the Description page of Project Settings.

 
#include "WorldPosition.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
   

// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	//LogTemp 카테고리에 3가지 Verbosity, 그리고 메시지
	UE_LOG(LogTemp, Display, TEXT("Just log, Hello !")); //회색
	UE_LOG(LogTemp, Warning, TEXT("This is a Warning")); //노란색
	UE_LOG(LogTemp, Error, TEXT("This is a Error"));	//빨간색 
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

