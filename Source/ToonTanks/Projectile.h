// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "True"))
	class UProjectileMovementComponent* ProjectileMovementComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called Every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "True"))
	class UStaticMeshComponent* ProjectileMesh;
	
	UPROPERTY(EditAnywhere)
	float Damage = 50.f;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticle;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystemComponent* TrailParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpuls, const FHitResult& Hit);
};
