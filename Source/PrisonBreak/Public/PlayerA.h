// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerA.generated.h"

UCLASS()
class PRISONBREAK_API APlayerA : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerA();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// �̵� �Լ�
	void MoveForward(float value);
	void MoveRight(float value);

	// ��ȣ�ۿ� �Է� �Լ�
	void OnInteraction(float value);

	void OnInteractionTwo(float value);

	// �޸���
	void Sprint();
	void StopSprinting();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class APlayerA* me;

	// ��������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* BoomArm;

	// ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = State)
		bool isInTrigger;

	UPROPERTY(EditDefaultsOnly, Category = State)
		float cuttingTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = State)
		float cuttingComplete = 0;

	UPROPERTY()
		float interact;

	UPROPERTY()
		float interactTwo;

	UPROPERTY()
		class ADoor* door;

	UPROPERTY()
		class ACCTV* cctv;

	UPROPERTY(VisibleAnywhere, Category = "Target")
		class AActor* target;

	// �޸���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedMultiplier;
};
