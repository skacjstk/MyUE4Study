// Copyright nam seok won

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float reach = 250.f;
	UPhysicsHandleComponent* physicsHandle = nullptr;
	UInputComponent* inputComponent = nullptr;

	void Grab();
	void Released();
	void FindPhysicsHandle();
	void SetupInputComponent();
	bool CheckPhysicsHandle();
	FVector GetLineTraceEnd(FVector &playerViewPointLocation) const;
	FVector GetLineTraceEnd() const;
	//반환 첫번째 엑터 피직스 바디에 닿은 거
	FHitResult GetFirstPhysicsBodyReach() const;
};
