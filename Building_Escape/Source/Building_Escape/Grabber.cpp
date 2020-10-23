// Copyright nam seok won

#include "Grabber.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetupInputComponent();

} 

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector lineTraceEnd = GetLineTraceEnd();
	if (physicsHandle->GrabbedComponent) {
		physicsHandle->SetTargetLocation(lineTraceEnd);
	}
}
FVector UGrabber::GetLineTraceEnd() const {
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);
	return playerViewPointLocation + playerViewPointRotation.Vector()* reach;
}
void UGrabber::SetupInputComponent() {
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>(); //가장 처음 발견된 것만 가져옴
	if (inputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("input Component found on %s!"), *GetOwner()->GetName());
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Released);
	}
}
void UGrabber::FindPhysicsHandle() {
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on %s!"), *GetOwner()->GetName());
	}
}
void UGrabber::Grab() {
//	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed!"));	
	FVector lineTraceEnd = GetLineTraceEnd();

	FHitResult hitResult = GetFirstPhysicsBodyReach();
	AActor* hitActor = hitResult.GetActor();
	UPrimitiveComponent* componentToGrab = hitResult.GetComponent();
	if (hitActor) {
		physicsHandle->GrabComponentAtLocationWithRotation(
			componentToGrab,
			NAME_None,
			lineTraceEnd,
			hitActor->GetActorRotation()	// 000 으로 해도 잡을때를 기준으로 고정된다. 		
		);
	} 
}
void UGrabber::Released() {
//	UE_LOG(LogTemp, Warning, TEXT("Grabber Released %s!"), "!");
	physicsHandle->ReleaseComponent();
}
//playerViewPointLocation 을 얻기 위해 함수 오버로딩함.
FVector UGrabber::GetLineTraceEnd(FVector &playerViewPointLocation) const{

	FRotator playerViewPointRotation;
	//out parameter: 반환값이 있는게 아니라, 변수의 주소값이 결과값을 받을 값이 되어 인자로 전달하는 형태
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector()* reach;
	return lineTraceEnd;
}

FHitResult UGrabber::GetFirstPhysicsBodyReach() const{
	// 플레이어 뷰포트 얻기
	FVector playerViewPointLocation;
	FVector lineTraceEnd = GetLineTraceEnd(OUT playerViewPointLocation);	
	//define OUT, 코드의 가독성을 위해 out parameter 임을 명시함.
	FHitResult hit;
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner()); //false 가 자기자신 제외

	//ray-cast out to a certain distance (reach) 
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		playerViewPointLocation,
		lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParams
	);
	AActor* actorHit = hit.GetActor();
	if (actorHit)
		UE_LOG(LogTemp, Display, TEXT("Hit Object is: %s"), *(actorHit->GetName()));

	return hit;
}


/*
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
*/