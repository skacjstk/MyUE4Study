// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;
	InitialLifeSpan= 3.0f;

	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	ParticleTrail->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	Super::BeginPlay();

	//3D 사운드 시스템, 2D 는 오디오가 어디있던 동일한 볼륨을 원할때 씀.
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());

}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
//	UE_LOG(LogTemp, Warning, TEXT("OnHit exe!"));
	AActor* MyOwner = GetOwner();
	if (!MyOwner)
		return;

	if (OtherActor && OtherActor != this && OtherActor != MyOwner) {
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation()); 
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);

		Destroy();
	}
//	UE_LOG(LogTemp, Warning, TEXT("Destroy Complete!"));
	
}


