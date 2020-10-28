// Copyright nam seok won


#include "OpenCryptDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT
// Sets default values for this component's properties
UOpenCryptDoor::UOpenCryptDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenCryptDoor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Test"));
	InitializeYaw();
	
}
void UOpenCryptDoor::InitializeYaw() {
	currentYaw = GetOwner()->GetActorRotation().Yaw;
	initialYaw = currentYaw;
	openAngle += currentYaw;

	if (!playerPlate) {
		UE_LOG(LogTemp, Error, TEXT("%s has the opencryptdoor on it, but no playerPlate set!*"), *GetOwner()->GetName());
	}
	else{
		FindAudioComponent();
	}
	//udemy 111�� �ڱ��ڽ� ã��
	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenCryptDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (playerPlate->IsOverlappingActor(actorThatOpens))
	{
//		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetName());		
		OpenDoor(DeltaTime);
	}
	// ...
}
void UOpenCryptDoor::FindAudioComponent() {
	audioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	//�Լ�ȭ �ϱ� ������.
	if (!audioComponent) {
		UE_LOG(LogTemp, Error, TEXT("%s missing AudioComponent"), *GetOwner()->GetName());
	}
}
void UOpenCryptDoor::OpenDoor(float DeltaTime) {
	FRotator openDoor = GetOwner()->GetActorRotation();
	
	currentYaw = FMath::FInterpTo(currentYaw, openAngle, DeltaTime, doorOpenSpeed);  //��� Lerp �� ���� ����
	openDoor.Yaw = currentYaw;
	GetOwner()->SetActorRotation(openDoor);
	DoorSoundPlayOnce(true);

}
void UOpenCryptDoor::CloseDoor(float DeltaTime) {
	FRotator openDoor = GetOwner()->GetActorRotation();

	currentYaw = FMath::FInterpTo(currentYaw, initialYaw, DeltaTime, doorOpenSpeed);  //��� Lerp �� ���� ����
	openDoor.Yaw = currentYaw;
	GetOwner()->SetActorRotation(openDoor);
	DoorSoundPlayOnce(false);
}

void UOpenCryptDoor::DoorSoundPlayOnce(bool state) {
	//	UE_LOG(LogTemp, Warning, TEXT("�ѱ�"));  openDoor.cpp �� UTF-8 �� �����ϴ� TEXT�� �ѱ���µ�.
	if (binarySwitch != state) {
		if (audioComponent)
			audioComponent->Play();
		binarySwitch = state;
	}
}