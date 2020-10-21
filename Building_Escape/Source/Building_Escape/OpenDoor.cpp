// Copyright nam seok won


#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
	//만약 잘못건드려서 언리얼 프로젝트 안켜지면, 코드 되돌리고 vs프로젝트명 빌드(U) 눌러보자
	//그리고 PATick 은 아니야...

}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	currentYaw = GetOwner()->GetActorRotation().Yaw;
	initialYaw = currentYaw;
	openAngle += currentYaw;
	//openAngle 는 90.0f로 초기화되어 있다. 
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component on it, but no pressurePlate set!*"), *GetOwner()->GetName());
	//	GetOwner()->SetActorTickEnabled(false);
	}
	else {
	//	GetOwner()->SetActorTickEnabled(true);
		ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	}

}
//https://docs.unrealengine.com/en-US/API/Runtime/Core/Math/FRotator/__ctor/5/index.html
//YZX  (피치 요 롤 순서)

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor(DeltaTime);
		doorLastOpened = GetWorld()->GetTimeSeconds();
		// 문이 마지막에 열린 시간. = 문이 열린 시간
	}
	else {
		if(doorLastOpened + doorCloseDelay < GetWorld()->GetTimeSeconds())
		//문이 x 초 보다 길게 연결되었다면;
		CloseDoor(DeltaTime);
	}
}
void UOpenDoor::CloseDoor(float DeltaTime)
{
//	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
//	UE_LOG(LogTemp, Warning, TEXT("Yaw is %f"), GetOwner()->GetActorRotation().Yaw);
	FRotator closeDoor = GetOwner()->GetActorRotation();
	currentYaw = FMath::FInterpTo(currentYaw, initialYaw, DeltaTime, doorCloseSpeed);
	
	closeDoor.Yaw = currentYaw;
	GetOwner()->SetActorRotation(closeDoor);
}
void UOpenDoor::OpenDoor(float DeltaTime)
{
//	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
//	UE_LOG(LogTemp, Warning, TEXT("Yaw is %f"), GetOwner()->GetActorRotation().Yaw);
	FRotator openDoor = GetOwner()->GetActorRotation();
	//Change Yaw of OpenDoor
//	openDoor.Yaw = FMath::FInterpConstantTo(currentYaw, openAngle, DeltaTime, 45); //이게 선형보간,
//	currentYaw = FMath::Lerp(currentYaw, openAngle, 0.03f);
//	currentYaw = FMath::Lerp(currentYaw, openAngle, DeltaTime * doorMoveSpeed);
	currentYaw = FMath::FInterpTo(currentYaw, openAngle, DeltaTime, doorOpenSpeed);  //얘랑 Lerp 가 지수 보간
//	UE_LOG(LogTemp, Warning, TEXT("DeltaTime is %f"), DeltaTime);

	openDoor.Yaw = currentYaw;
	GetOwner()->SetActorRotation(openDoor);
}


