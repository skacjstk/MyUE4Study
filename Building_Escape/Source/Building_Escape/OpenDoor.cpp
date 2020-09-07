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

	float rotate = 90.f; //90.0 �� ǥ�� 

	FRotator currentRotation = GetOwner()->GetActorRotation();
	currentRotation.Yaw += 90.0f;
	GetOwner()->SetActorRotation(currentRotation);

//	FRotator openDoor = { 0.f, 90.f, 0.f };
	//���ǿ����� �ϵ��ڵ��� ���� �Է����ָ�, �̹� 90���� ���ư��ִ� ���� ������ ������ ������ ��������

}
//https://docs.unrealengine.com/en-US/API/Runtime/Core/Math/FRotator/__ctor/5/index.html
//YZX  (��ġ �� �� ����)

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

