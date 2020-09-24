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

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component on it, but no pressurePlate set!*"), *GetOwner()->GetName());
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
	}	
}
void UOpenDoor::OpenDoor(float DeltaTime)
{
	//	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	//	UE_LOG(LogTemp, Warning, TEXT("Yaw is %f"), GetOwner()->GetActorRotation().Yaw);
	FRotator openDoor = GetOwner()->GetActorRotation();
	//Change Yaw of OpenDoor
//	openDoor.Yaw = FMath::FInterpConstantTo(currentYaw, targetYaw, DeltaTime, 45); //이게 선형보간,
//	currentYaw = FMath::Lerp(currentYaw, targetYaw, 0.03f);
	currentYaw = FMath::Lerp(currentYaw, targetYaw, DeltaTime * 1.f);
//	currentYaw = FMath::FInterpTo(currentYaw, targetYaw, DeltaTime, 3);  //얘랑 Lerp 가 지수 보간
//	UE_LOG(LogTemp, Warning, TEXT("DeltaTime is %f"), DeltaTime);

	openDoor.Yaw = currentYaw;
	GetOwner()->SetActorRotation(openDoor);
}


