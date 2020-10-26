// Copyright nam seok won

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
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
	float TotalMassOfActors() const; //ø¢≈Õ¿« √—¡˙∑Æ
	void FindAudioComponent();
	void DoorSoundPlayOnce(bool state);

private:

	float currentYaw = 0.f;
	float initialYaw = 0.f;
	bool binarySwitch = false;
	

	UPROPERTY(EditAnywhere)
		float openAngle = 90.0f;
	UPROPERTY(EditAnywhere)
		float doorOpenSpeed = 3.f;
	UPROPERTY(EditAnywhere)
		float doorCloseSpeed = 3.f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;	
	UPROPERTY(EditAnywhere)
		float MassToOpenDoor = 50.f;

	UPROPERTY()
		UAudioComponent* audioComponent = nullptr;

	float doorLastOpened = 0.f;
	float doorCloseDelay = 2.f;
};
