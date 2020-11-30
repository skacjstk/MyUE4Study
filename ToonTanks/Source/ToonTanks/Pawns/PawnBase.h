// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

private:
	//Components
	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComp = nullptr;
	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;	//투사체 스폰 포인트
	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	UPROPERTY(EditANywhere, Category="Effects")
	UParticleSystem* DeathParticle;
	//Variables
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;


protected:
	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Components", meta = (AllowProtectedAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	void RotateTurret(FVector LookAtTarget);
	void Fire();






//현재로썬 visible은 보이기, 그 뒤 인자는 변수 수정 인거같은데 
//	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
//		int EditA_BPReadOnly = 1;
//	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
//		int VisibleA_BPReadOnly = 1;
public:
	// Sets default values for this pawn's properties
	APawnBase();

	virtual void HandleDestruction();
};
