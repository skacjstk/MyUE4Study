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
void UGrabber::FindPhysicsHandle() {
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle) {
		//pyhcics is found
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on %s!"), *GetOwner()->GetName());
	}
}
void UGrabber::SetupInputComponent() {
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>(); //���� ó�� �߰ߵ� �͸� ������
	if (inputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("input Component found on %s!"), *GetOwner()->GetName());
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Released);
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed!"));	
	FVector lineTraceEnd = GetLineTraceEnd();

	FHitResult hitResult = GetFirstPhysicsBodyReach();
	AActor* hitActor = hitResult.GetActor();
	UPrimitiveComponent* componentToGrab = hitResult.GetComponent();
	if (hitActor) {
//		physicsHandle->GrabComponentAtLocation(
//			componentToGrab,
//			NAME_None,
//			lineTraceEnd
//		);
		physicsHandle->GrabComponentAtLocationWithRotation(
			componentToGrab,
			NAME_None,
			lineTraceEnd,
			hitActor->GetActorRotation()
		);
	} 
}
void UGrabber::Released() {
	UE_LOG(LogTemp, Warning, TEXT("Grabber Released %s!"), "!");
	physicsHandle->ReleaseComponent();
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
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector()* reach;
	return lineTraceEnd;
}
//playerViewPointLocation �� ��� ���� �Լ� �����ε���.
FVector UGrabber::GetLineTraceEnd(FVector &playerViewPointLocation) const{

	FRotator playerViewPointRotation;
	//out parameter: ��ȯ���� �ִ°� �ƴ϶�, ������ �ּҰ��� ������� ���� ���� �Ǿ� ���ڷ� �����ϴ� ����
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector()* reach;
	return lineTraceEnd;
}

FHitResult UGrabber::GetFirstPhysicsBodyReach() const{
	// �÷��̾� ����Ʈ ���
	FVector playerViewPointLocation;
	FVector lineTraceEnd = GetLineTraceEnd(OUT playerViewPointLocation);	
	//define OUT, �ڵ��� �������� ���� out parameter ���� �����.
	FHitResult hit;
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner()); //false �� �ڱ��ڽ� ����

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
		FColor(0, 255, 0),	//�ʷ� ��
		false,
		0.f,
		0,
		5.f			//5�ȼ�?
	);

	// Rotation �� ���� ���� ������ x y z �� 0~1 ������ ������ ǥ�����ְ� ....
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