// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
 

APawnTank::APawnTank() {
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(TurretMesh); //강의에서는 RootComponent

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
	//axis 는 매 프레임 마다 반응. action 은 action 할 때 반응	https://docs.unrealengine.com/ko/Programming/Tutorials/PlayerInput/3/index.html
	PlayerInputComponent->BindAction("Fire",IE_Pressed, this, &APawnTank::Fire);
	PlayerInputComponent->BindAxis("PlayerTurretTurn",  this, &APawnTank::RotateTurretKeyBoard);
}
void APawnTank::CalculateMoveInput(float Value)
{	
	MoveVector = Value;	//현재 앞으로가는가 뒤로가는가. ( rotate 계산용 )	
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
	if (PlayerConrollerRef) { //nullptr 보호
		Value *= TurretRotateSpeed;
		TankRotate += FRotator(0, Value, 0);
		TurretMesh->SetWorldRotation(TankRotate);
	}
}
void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);	//전부 쓰지는 않음 
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection,true);
}

