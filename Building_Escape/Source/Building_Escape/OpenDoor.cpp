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
	//���� �߸��ǵ���� �𸮾� ������Ʈ ��������, �ڵ� �ǵ����� vs������Ʈ�� ����(U) ��������
	//�׸��� PATick �� �ƴϾ�...

}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	currentYaw = GetOwner()->GetActorRotation().Yaw;
	initialYaw = currentYaw;
	openAngle += currentYaw;
	//openAngle �� 90.0f�� �ʱ�ȭ�Ǿ� �ִ�. 
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component on it, but no pressurePlate set!*"), *GetOwner()->GetName());
	}
	else {
	
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (TotalMassOfActors() > MassToOpenDoor) {
		OpenDoor(DeltaTime);
		doorLastOpened = GetWorld()->GetTimeSeconds();
		// ���� �������� ���� �ð�. = ���� ���� �ð�
	}
	else {
		if(doorLastOpened + doorCloseDelay < GetWorld()->GetTimeSeconds())
		//���� x �� ���� ��� ����Ǿ��ٸ�;
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
	currentYaw = FMath::FInterpTo(currentYaw, openAngle, DeltaTime, doorOpenSpeed);  //��� Lerp �� ���� ����
	openDoor.Yaw = currentYaw;
	GetOwner()->SetActorRotation(openDoor);
}

float UOpenDoor::TotalMassOfActors() const {
	float totalMass = 0.f;
	//overlapping actor ��� ã��
	TArray<AActor*> overLappingActors;
	if(PressurePlate){
		PressurePlate->GetOverlappingActors(OUT overLappingActors);
	}
	else return totalMass;
	for (AActor* Actor : overLappingActors) {
		totalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
//		UE_LOG(LogTemp, Warning, TEXT("%s is on the pressurePlate!"), *Actor->GetName());
	}
	//�׵��� ������ ���ϱ�
	return totalMass;
}


//https://docs.unrealengine.com/en-US/API/Runtime/Core/Math/FRotator/AActor/5/index.html
//YZX  (��ġ �� �� ����)

	//Change Yaw of OpenDoor
//	openDoor.Yaw = FMath::FInterpConstantTo(currentYaw, openAngle, DeltaTime, 45); //�̰� ��������,
//	currentYaw = FMath::Lerp(currentYaw, openAngle, 0.03f);
//	currentYaw = FMath::Lerp(currentYaw, openAngle, DeltaTime * doorMoveSpeed);