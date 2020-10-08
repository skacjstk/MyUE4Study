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
	
	// 플레이어 뷰포트 얻기
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	//out parameter: 반환값이 있는게 아니라, 변수의 주소값이 결과값을 받을 값이 되어 인자로 전달하는 형태
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);
	//define OUT, 코드의 가독성을 위해 out parameter 임을 명시함.
	//플레이어가 보는 거리 줄 그리기
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector()* reach;
	FVector question = playerViewPointLocation + playerViewPointRotation.Vector();
	DrawDebugLine(
		GetWorld(),
		playerViewPointLocation,
		lineTraceEnd,
		FColor(0,255,0),	//초록 선
		false,
		0.f,
		0,
		5.f			//5픽셀?
	);
	UE_LOG(LogTemp, Warning, TEXT("player Location: %s , Rotation: %s , lineTraceEnd: %s, else: %s"),
		*playerViewPointLocation.ToString(),
		*playerViewPointRotation.ToString(),
		*lineTraceEnd.ToString(),
		*question.ToString()
	);

	// ray-cast out  거리측정
	//
}

