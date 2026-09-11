#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	void HandleDestruction();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Speed = 5.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float SmoothRotationRate = 12.f;

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "True"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "True"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "True"))
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")	
	class UParticleSystem* DeathParticle;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

public:	


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
