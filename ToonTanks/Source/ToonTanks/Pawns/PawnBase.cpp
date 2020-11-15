// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values 
APawnBase::APawnBase() 
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; //이거 false하면 하위들도 동작안함

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh ->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	FVector LookAtTargetCleaned = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();
	FRotator TurretRotation = FVector(LookAtTargetCleaned - StartLocation).Rotation();

	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire()
{		
	// ProjectileSpawnPoint Location 과 Rotation 가져와서 -> Projectile 크래스 소환 at Location  후 Rotation을 향해 발사
	if (ProjectileClass) {
		FVector	SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	} 
//	UE_LOG(LogTemp, Warning, TEXT("Fire Complete!"));
}
 
void APawnBase::HandleDestruction()
{
	//공통 함수기능 
	// death 이펙트 파티클 재생, 소리와 카메라 쉐이크

	//자식클래스 기능
	//PawnTurret  죽으면 ->Destroy() 스스로 호출

	//PawnTank 죽으면 -> 모든 컴포넌트 Hide() && movement input 비활성화 
	//약 11분: 파괴해버리면 카메라를 잃고 월드 기본 카메라로 하드 점프해버려서
}
