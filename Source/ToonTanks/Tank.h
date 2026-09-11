// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	bool bAlive = true;
	
	void HandleDestruction();
	
	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* TankMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float MoveSpeed = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float TurnRate = 50.f;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Move(const FInputActionValue& Value);

	

private:

	APlayerController* TankPlayerController;

	UPROPERTY(VisibleAnyWhere, Category = "Components")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly , Category = "Components", Meta = (AllowPrivateAccess = "True"))
	class UCameraComponent* Camera;

};
