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

	//200829  udemy �𸮾� 94 
	FString objectName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *objectName);
	FString objectPosition = GetOwner()->GetActorLocation().ToString();
	FString objectPositionTransform = GetOwner()->GetActorTransform().GetScale3D().ToString();
	//xyz ��ġ
	UE_LOG(LogTemp, Warning, TEXT("%s"), *objectPosition);
	//xyz ��ġ ȸ�� ������  (GetLoaction �߰��� ���� ����)
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
	////precedence �켱����

	//udemy �𸮾� 91 start
	//LogTemp ī�װ��� 3���� Verbosity, �׸��� �޽���
//	UE_LOG(LogTemp, Display, TEXT("Just log, Hello !")); //ȸ��
//	UE_LOG(LogTemp, Warning, TEXT("This is a Warning")); //�����
//	UE_LOG(LogTemp, Error, TEXT("This is a Error"));	//������
	//udemy �𸮾� 91 end

	//200829  udemy �𸮾� 94 start
	FString objectName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *objectName);
	FString objectPosition = GetOwner()->GetActorLocation().ToString();
	FString objectPositionTransform = GetOwner()->GetActorTransform().GetLocation().ToString();
	//xyz ��ġ
	UE_LOG(LogTemp, Warning, TEXT("%s"), *objectPosition);
	//xyz ��ġ ȸ�� ������  (GetLoaction �߰��� ���� ����)
	UE_LOG(LogTemp, Warning, TEXT("trans %s"), *objectPositionTransform);
	//200829  udemy �𸮾� 94 end
*/