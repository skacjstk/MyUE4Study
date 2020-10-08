// Copyright nam seok won

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Grabber.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	// ...
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// �÷��̾� ����Ʈ ���
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	//out parameter: ��ȯ���� �ִ°� �ƴ϶�, ������ �ּҰ��� ������� ���� ���� �Ǿ� ���ڷ� �����ϴ� ����
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);
	//define OUT, �ڵ��� �������� ���� out parameter ���� �����.
	//�÷��̾ ���� �Ÿ� �� �׸���
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector()* reach;
	FVector question = playerViewPointLocation + playerViewPointRotation.Vector();
	DrawDebugLine(
		GetWorld(),
		playerViewPointLocation,
		lineTraceEnd,
		FColor(0,255,0),	//�ʷ� ��
		false,
		0.f,
		0,
		5.f			//5�ȼ�?
	);
	UE_LOG(LogTemp, Warning, TEXT("player Location: %s , Rotation: %s , lineTraceEnd: %s, else: %s"),
		*playerViewPointLocation.ToString(),
		*playerViewPointRotation.ToString(),
		*lineTraceEnd.ToString(),
		*question.ToString()
	);

	// ray-cast out  �Ÿ�����
	//
}

