// Copyright nam seok won

#include "CollisionQueryParams.h"
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
//	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle) {
		//pyhcics is found 

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on %s!"), *GetOwner()->GetName());
	}

	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>(); //가장 처음 발견된 것만 가져옴
	if (inputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("input Component found on %s!"), *GetOwner()->GetName());
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("input Component Missing %s!"), *GetOwner()->GetName());

	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grabber Press %s!"),"!");

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
	DrawDebugLine(
		GetWorld(),
		playerViewPointLocation,
		lineTraceEnd,
		FColor(0, 255, 0),	//초록 선
		false,
		0.f,
		0,
		5.f			//5픽셀?
	);
	// Rotation 이 내가 보는 방향의 x y z 를 0~1 사이의 값으로 표현해주고 ....
	//	FVector question = playerViewPointLocation + playerViewPointRotation.Vector();
	//	FVector question2 = playerViewPointRotation.Vector();
	//	FVector question3 = playerViewPointRotation.Vector()*reach;
	//	UE_LOG(LogTemp, Warning, TEXT("End: %s, Loc+Rot: %s, Loc:%s, Rot: %s, %Rot*reach: %s"),
	//		*lineTraceEnd.ToString(),
	//		*question.ToString(),
	//		*playerViewPointLocation.ToString(),
	//		*question2.ToString(),
	//		*question3.ToString()
	//	);
	 
	//	UE_LOG(LogTemp, Warning, TEXT("player Location: %s , Rotation: %s , lineTraceEnd: %s"),
	//		*playerViewPointLocation.ToString(),
	//		*playerViewPointRotation.ToString(),
	//		*lineTraceEnd.ToString(),
	//	);

	FHitResult hit;
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());
	 
	//ray-cast out to a certain distance (reach) 
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		playerViewPointLocation,
		lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParams
	);
	AActor* actorHit = hit.GetActor();
	if(actorHit)
		UE_LOG(LogTemp, Display, TEXT("Hit Object is: %s"), *(actorHit->GetName()));

}

