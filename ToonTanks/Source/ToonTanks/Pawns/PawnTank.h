// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Pawns/PawnBase.h"	//기본 설정이 이리되어있어서 오류가 생김.
#include "PawnBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;
UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm = nullptr;
	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera = nullptr;
	
	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "PlayerDirection", meta = (AllowPrivateAccess = "true"))
	FVector MoveDirection;
	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "PlayerDirection", meta = (AllowPrivateAccess = "true"))
	FQuat RotationDirection;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 500.0f;
	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 100.0f;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float TurretRotateSpeed = 0.50f;
	//내가 임의로 만듬.
	float MoveVector = 0.f;

	FRotator TankRotate;
	APlayerController* PlayerConrollerRef;
	bool bIsPlayerAlive = true;
	

	void CalculateMoveInput(float Value);
	void CalculateRotaterInput(float Value);
	void Move();
	void Rotate();
	//내가 임의로 만듬.
	void RotateTurretKeyBoard(float Value);
	void UpDownCameraKeyBoard(float Value);

public:
	APawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void HandleDestruction() override;

	bool GetIsPlayerAlive();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
