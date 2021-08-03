// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerA.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PrisonBreak.h"
#include "Door.h"
#include "CCTV.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
APlayerA::APlayerA()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ε巯�� ������
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	// ��������
	BoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	BoomArm->SetupAttachment(RootComponent);
	BoomArm->TargetArmLength = 300.0f;
	BoomArm->bUsePawnControlRotation = true;

	// ī�޶�
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(BoomArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->SetRelativeLocationAndRotation(FVector(-12, 0, 146), FRotator(0, -20, 0));

	// �ٵ� �޽� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SK_BODY.Succeeded())
	{
		// ĳ���Ϳ��� ��ӵ� �޽ÿ� ���̷�Ż �޽� ����
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);
	}

	// �ִϸ��̼� ��� ����
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// �ִϸ��̼� �������Ʈ Ŭ���� ��������
	static ConstructorHelpers::FClassFinder<UAnimInstance> PlayerAnim(TEXT("AnimBlueprint'/Game/Blueprint/PlayerAnimation.PlayerAnimation_C'"));
	if (PlayerAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PlayerAnim.Class);
	}

	// �ȴ� �ӵ�
	UCharacterMovementComponent* MovementPtr = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	MovementPtr->MaxWalkSpeed = 300;


}

// Called when the game starts or when spawned
void APlayerA::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (interact == 1 && isInTrigger == true)
	{
		cuttingComplete += DeltaTime + cuttingTime;
	}

	if (cuttingComplete> 3)
	{
		door = Cast<ADoor>(GetOwner());
		door->Destroy();
	}

	if (interactTwo == 1)
	{
		GetWorld()->GetFirstPlayerController()->UnPossess();
		if (GetWorld()->GetFirstPlayerController() == nullptr)
		{
			CALLINFO();
			cctv = Cast<ACCTV>(GetOwner());
			cctv->GetWorld()->GetFirstPlayerController()->Possess(cctv);
		}
	}
}

// Called to bind functionality to input
void APlayerA::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerA::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerA::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// �÷��̾� ��ȣ�ۿ� Ű ���ε�
	PlayerInputComponent->BindAxis(TEXT("Interaction"), this, &APlayerA::OnInteraction);
	PlayerInputComponent->BindAxis(TEXT("InteractionTwo"), this, &APlayerA::OnInteractionTwo);
}

void APlayerA::OnInteraction(float value)
{
	if (Controller != NULL && value != 0.0)
	{
		interact = value;
	}
}

void APlayerA::OnInteractionTwo(float value)
{
	if (Controller != NULL && value != 0.0)
	{
		interactTwo = value;
	}
}

void APlayerA::MoveForward(float value)
{
	if (Controller != NULL && value != 0.0) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);
		// ��� ���� �������� �˾Ƴ���, �÷��̾ �� �������� �̵��ϰ��� �Ѵٰ� ���
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, value);
	}
}

void APlayerA::MoveRight(float value)
{
	if (Controller != NULL && value != 0.0) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, value);
	}
}
