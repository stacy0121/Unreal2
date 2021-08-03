// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	// pawn ��ü�� ��ȿ�ϸ�
	if (::IsValid(Pawn)) {
		// �ӷ� ���ؼ� ������ ����
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}

	auto Character = Cast<ACharacter>(Pawn);
	if (Character) {
		// ���� �̵� �ӵ� ����
		CurrentWalkSpeed = Character->GetMovementComponent()->GetMaxSpeed();
	}
}
