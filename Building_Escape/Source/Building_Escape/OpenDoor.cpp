// Copyright nam seok won


#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT
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
	}
	else {
		ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (TotalMassOfActors() > MassToOpenDoor) {
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
	FRotator closeDoor = GetOwner()->GetActorRotation();
	currentYaw = FMath::FInterpTo(currentYaw, initialYaw, DeltaTime, doorCloseSpeed);
	
	closeDoor.Yaw = currentYaw;
	GetOwner()->SetActorRotation(closeDoor);
}
void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator openDoor = GetOwner()->GetActorRotation();
	currentYaw = FMath::FInterpTo(currentYaw, openAngle, DeltaTime, doorOpenSpeed);  //얘랑 Lerp 가 지수 보간
	openDoor.Yaw = currentYaw;
	GetOwner()->SetActorRotation(openDoor);
}

float UOpenDoor::TotalMassOfActors() const {
	float totalMass = 0.f;
	//overlapping actor 모두 찾기
	TArray<AActor*> overLappingActors;
	PressurePlate->GetOverlappingActors(OUT overLappingActors);
	for (AActor* Actor : overLappingActors) {
		totalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
//		UE_LOG(LogTemp, Warning, TEXT("%s is on the pressurePlate!"), *Actor->GetName());
	}
	//그들의 질량들 더하기
	return totalMass;
}


//https://docs.unrealengine.com/en-US/API/Runtime/Core/Math/FRotator/AActor/5/index.html
//YZX  (피치 요 롤 순서)

	//Change Yaw of OpenDoor
//	openDoor.Yaw = FMath::FInterpConstantTo(currentYaw, openAngle, DeltaTime, 45); //이게 선형보간,
//	currentYaw = FMath::Lerp(currentYaw, openAngle, 0.03f);
//	currentYaw = FMath::Lerp(currentYaw, openAngle, DeltaTime * doorMoveSpeed);