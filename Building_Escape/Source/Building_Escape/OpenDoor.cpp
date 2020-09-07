// Copyright nam seok won


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	float rotate = 90.f; //90.0 의 표현 

	FRotator currentRotation = GetOwner()->GetActorRotation();
	currentRotation.Yaw += 90.0f;
	GetOwner()->SetActorRotation(currentRotation);

//	FRotator openDoor = { 0.f, 90.f, 0.f };
	//강의에서는 하드코딩된 값을 입력해주며, 이미 90도로 돌아가있는 문이 열리지 않음을 문제로 지목했음

}
//https://docs.unrealengine.com/en-US/API/Runtime/Core/Math/FRotator/__ctor/5/index.html
//YZX  (피치 요 롤 순서)

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

