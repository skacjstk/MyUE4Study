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
	//targetYaw �� 90.0f�� �ʱ�ȭ�Ǿ� �ִ�. 
}
//https://docs.unrealengine.com/en-US/API/Runtime/Core/Math/FRotator/__ctor/5/index.html
//YZX  (��ġ �� �� ����)

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is %f"), GetOwner()->GetActorRotation().Yaw);

	 
	FRotator openDoor = GetOwner()->GetActorRotation();
	openDoor.Yaw = currentYaw; 
	//Change Yaw of OpenDoor
//	openDoor.Yaw = FMath::FInterpConstantTo(currentYaw, targetYaw, DeltaTime, 45); //�̰� ��������,
//	openDoor.Yaw = FMath::Lerp(currentYaw, targetYaw, 0.02f);
	currentYaw = FMath::FInterpTo(currentYaw, targetYaw, DeltaTime, 2);  //��� Lerp �� ���� ����
	
	GetOwner()->SetActorRotation(openDoor);

	//FRotator currentRotation = GetOwner()->GetActorRotation();
	//currentRotation.Yaw += 90.0f;
	//	FRotator openDoor = { 0.f, 90.f, 0.f };
	//���ǿ����� �ϵ��ڵ��� ���� �Է����ָ�, �̹� 90���� ���ư��ִ� ���� ������ ������ ������ ��������
}

