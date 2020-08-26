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

	//FString log = TEXT("Hello");
	//FString* ptrLog = &log;

	//log.Len();

	//(*ptrLog).Len();
	//ptrLog->Len();
	////precedence �켱����
	//UE_LOG(LogTemp, Warning, TEXT("%s"), **ptrLog);


	FString objectName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *objectName);


	//LogTemp ī�װ��� 3���� Verbosity, �׸��� �޽���
//	UE_LOG(LogTemp, Display, TEXT("Just log, Hello !")); //ȸ��
//	UE_LOG(LogTemp, Warning, TEXT("This is a Warning")); //�����
//	UE_LOG(LogTemp, Error, TEXT("This is a Error"));	//������ 
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

