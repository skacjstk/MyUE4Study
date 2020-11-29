// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
 

APawnTank::APawnTank() {
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(TurretMesh); //���ǿ����� RootComponent

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}
void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();
	//Hide player TODO Create new function to handle this 
	bIsPlayerAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
} 

bool APawnTank::GetIsPlayerAlive()
{
	return bIsPlayerAlive;
}


// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	TankRotate = TurretMesh->GetComponentRotation();

	PlayerConrollerRef = Cast<APlayerController>(GetController());
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();

	/*
	if (PlayerConrollerRef) {
		FHitResult TraceHitResult;
		PlayerConrollerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;
		RotateTurret(HitLocation);
	}
	*/
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotaterInput);
	//axis �� �� ������ ���� ����. action �� action �� �� ����	https://docs.unrealengine.com/ko/Programming/Tutorials/PlayerInput/3/index.html
	PlayerInputComponent->BindAction("Fire",IE_Pressed, this, &APawnTank::Fire);
	PlayerInputComponent->BindAxis("PlayerTurretTurn",  this, &APawnTank::RotateTurretKeyBoard);
}
void APawnTank::CalculateMoveInput(float Value)
{	
	MoveVector = Value;	//���� �����ΰ��°� �ڷΰ��°�. ( rotate ���� )	
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotaterInput(float Value)
{
	if (MoveVector == 0.f){	
		MoveVector = 1.0f;
	}
	float RotaterAmount = MoveVector * Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotaterAmount, 0);
	RotationDirection = FQuat(Rotation);
}
void APawnTank::RotateTurretKeyBoard(float Value)
{
	if (PlayerConrollerRef) { //nullptr ��ȣ
		Value *= TurretRotateSpeed;
		TankRotate += FRotator(0, Value, 0);
		TurretMesh->SetWorldRotation(TankRotate);
	}
}
void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);	//���� ������ ���� 
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection,true);
}

