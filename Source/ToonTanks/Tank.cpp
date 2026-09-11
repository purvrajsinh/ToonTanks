// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h" 
#include "Kismet/GameplayStatics.h"

ATank::ATank(){
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm -> SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera -> SetupAttachment(SpringArm);

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent -> BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATank::Move);
        EnhancedInputComponent -> BindAction(IA_Fire, ETriggerEvent::Started, this, &ATank::Fire);
    }
} 

void ATank::BeginPlay()
{
    Super::BeginPlay();
    
	TankPlayerController = CastChecked<APlayerController>(GetController());

    if(TankPlayerController)
    {
       if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(TankPlayerController->GetLocalPlayer()))
       {
            Subsystem -> AddMappingContext(TankMappingContext,0);
       }
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive =false;
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController -> GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
        false,
        HitResult);

        RotateTurret(HitResult.ImpactPoint);
    }
}

void ATank::Move(const FInputActionValue& Value)
{ 
    const FVector2D CurrentValue = Value.Get<FVector2D>();
    double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    if(CurrentValue.Y != 0){
        FVector Movement = FVector::ZeroVector;
        Movement.X = CurrentValue.Y * MoveSpeed * DeltaTime;
        AddActorLocalOffset(Movement ,true);
    }

    if(CurrentValue.X != 0){
        FRotator Rotation = FRotator::ZeroRotator;
        Rotation.Yaw = CurrentValue.X * TurnRate * DeltaTime;
        AddActorLocalRotation(Rotation ,true);
    }
}


