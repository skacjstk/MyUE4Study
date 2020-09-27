// Copyright nam seok won

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
private:

	UPROPERTY(EditAnywhere)
	float targetYaw = 90.0f;
	float currentYaw = 0.f;
	float initialYaw = 0.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;
	
	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens;
};
