// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category ="Components" , meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComp = nullptr;
	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
protected:
	UPROPERTY(VisibleAnyWhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurretMesh;
private:
	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;	//투사체 스폰 포인트


	//현재로썬 visible은 보이기, 그 뒤 인자는 변수 수정 인거같은데 
//	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
//		int EditA_BPReadOnly = 1;
//	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
//		int VisibleA_BPReadOnly = 1;
public:
	// Sets default values for this pawn's properties
	APawnBase();

};
