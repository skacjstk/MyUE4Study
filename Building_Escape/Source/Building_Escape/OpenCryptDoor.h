// Copyright nam seok won

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/AudioComponent.h"
#include "OpenCryptDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenCryptDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenCryptDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void InitializeYaw();
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	void FindAudioComponent();
	void DoorSoundPlayOnce(bool state);

private:
	float currentYaw = 0.f;
	float initialYaw = 0.f;
	bool binarySwitch = false;

	UPROPERTY(EditAnywhere)
		float openAngle = -90.0f;
	UPROPERTY(EditAnywhere)
		float doorOpenSpeed = 3.f;
	UPROPERTY(EditAnywhere)
		float doorCloseSpeed = 3.f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* playerPlate = nullptr;
	UPROPERTY(EditAnywhere)
		AActor* actorThatOpens;

	UPROPERTY()
		UAudioComponent* audioComponent = nullptr;
};
