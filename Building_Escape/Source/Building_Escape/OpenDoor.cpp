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

	currentYaw = GetOwner()->GetActorRotation().Yaw;
//	targetYaw = currentYaw + targetYaw;
	targetYaw += currentYaw;
	//targetYaw 는 90.0f로 초기화되어 있다. 
}
//https://docs.unrealengine.com/en-US/API/Runtime/Core/Math/FRotator/__ctor/5/index.html
//YZX  (피치 요 롤 순서)

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is %f"), GetOwner()->GetActorRotation().Yaw);

	 
	FRotator openDoor = GetOwner()->GetActorRotation();
	openDoor.Yaw = currentYaw; 
	//Change Yaw of OpenDoor
//	openDoor.Yaw = FMath::FInterpConstantTo(currentYaw, targetYaw, DeltaTime, 45); //이게 선형보간,
//	openDoor.Yaw = FMath::Lerp(currentYaw, targetYaw, 0.02f);
	currentYaw = FMath::FInterpTo(currentYaw, targetYaw, DeltaTime, 2);  //얘랑 Lerp 가 지수 보간
	
	GetOwner()->SetActorRotation(openDoor);

	//FRotator currentRotation = GetOwner()->GetActorRotation();
	//currentRotation.Yaw += 90.0f;
	//	FRotator openDoor = { 0.f, 90.f, 0.f };
	//강의에서는 하드코딩된 값을 입력해주며, 이미 90도로 돌아가있는 문이 열리지 않음을 문제로 지목했음
}

