// Fill out your copyright notice in the Description page of Project Settings.

 
#include "WorldPosition.h"
#include "GameFramework/Actor.h"

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

	//200829  udemy 언리얼 94 
	FString objectName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *objectName);
	FString objectPosition = GetOwner()->GetActorLocation().ToString();
	FString objectPositionTransform = GetOwner()->GetActorTransform().GetScale3D().ToString();
	//xyz 위치
	UE_LOG(LogTemp, Warning, TEXT("%s"), *objectPosition);
	//xyz 위치 회전 스케일  (GetLoaction 추가시 위와 같음)
	UE_LOG(LogTemp, Warning, TEXT("trans %s"), *objectPositionTransform);
	//Scale3D, Rotation, Location
} 


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


/*
	//(*ptrLog).Len();
	//ptrLog->Len();
	////precedence 우선순위

	//udemy 언리얼 91 start
	//LogTemp 카테고리에 3가지 Verbosity, 그리고 메시지
//	UE_LOG(LogTemp, Display, TEXT("Just log, Hello !")); //회색
//	UE_LOG(LogTemp, Warning, TEXT("This is a Warning")); //노란색
//	UE_LOG(LogTemp, Error, TEXT("This is a Error"));	//빨간색
	//udemy 언리얼 91 end

	//200829  udemy 언리얼 94 start
	FString objectName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *objectName);
	FString objectPosition = GetOwner()->GetActorLocation().ToString();
	FString objectPositionTransform = GetOwner()->GetActorTransform().GetLocation().ToString();
	//xyz 위치
	UE_LOG(LogTemp, Warning, TEXT("%s"), *objectPosition);
	//xyz 위치 회전 스케일  (GetLoaction 추가시 위와 같음)
	UE_LOG(LogTemp, Warning, TEXT("trans %s"), *objectPositionTransform);
	//200829  udemy 언리얼 94 end
*/