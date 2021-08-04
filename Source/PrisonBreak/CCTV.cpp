// Fill out your copyright notice in the Description page of Project Settings.


#include "CCTV.h"

// Sets default values
ACCTV::ACCTV()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ACCTV::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACCTV::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACCTV::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
}

void ACCTV::ChangePerson()
{
	GetWorld()->GetFirstPlayerController()->Possess(this);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

