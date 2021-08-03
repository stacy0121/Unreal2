// Fill out your copyright notice in the Description page of Project Settings.



#include "AIController.h"
#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include <EngineUtils.h>
#include "Enemy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"




void AEnemyAIController::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{

	//Super::TickActor();

	//����(����)�� �ۼ�
	switch (m_state)
	{
	case EEnemyState::Idle:
		Idlestate();
		break;
	case EEnemyState::Move:
		Movestate();
		break;
	case EEnemyState::Check:
		Checkstate();
		break;
		//case EEnemyState::Attack:
			//Attackstate();
			//break;
	case EEnemyState::End:
		Endstate();
		break;
	}
}
//�����ð� ��ٸ��ٰ� ���¸� move�� �ٲ�����
//�ʿ�Ӽ� : ��ٸ� �ð�, ��� �ð�
//���� �Ÿ� �� �ִ� �÷��̾ �ִٸ� Checkstate�� �ٲ�
void AEnemyAIController::Idlestate()
{

	FString str = TEXT("Idle");
	//�����ð����� ��ٸ��ٰ� ���¸� Move�� �ٲ�����
	//1. �ð��� �귶���ϱ�
	currentTime += GetWorld()->DeltaTimeSeconds;
	//2. ���ð��� �� �����ϱ�]
	if (currentTime > idleDelayTime)
	{	//3. ���¸� Move�� �ٲ�����.

		m_state = EEnemyState::Move;
		currentTime = 0;
		//Ÿ������Ʈ�� �����ϰ� �պ��Ѵ�.
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		GoToRandomWaypoint();
	}
}
//target point�� �����ϰ� �պ��Ѵ�
//���� ���� �Ÿ� ���� �ִ� �÷��̾ �ִٸ� Checkstate�� �ٲ�
//�ʿ�Ӽ� :  �÷��̾���� �Ÿ�
void AEnemyAIController::Movestate()
{	// ���� ���� �Ÿ� ���� �ִ� �÷��̾ �ִٸ� Checkstate�� �ٲ�
	//�ʿ�Ӽ�:check ����
	//1. �����Ÿ� ���� �÷��̾ �ִٸ�
		//player�� enemy�� �Ÿ�
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//FVector direction = Ptarget->GetActorLocation(); - me->GetActorLocation();
	FVector direction = playerCharacter->GetActorLocation(); - me->GetActorLocation();
	float distance = direction.Size();
	//2. Checkstate �� �ٲ�

	if (checkRange > distance)
	{
		m_state = EEnemyState::Check;


	}
	else 
	{
	//�ƴ϶�� idle�� �ٲ�
		m_state = EEnemyState::Idle;
	
	}

}
//���� door�� ���°� öâ���Ⱑ �ƴ϶�� Idle�� �ٲ�
// �ʿ�Ӽ� : Ÿ�� �÷��̾� ����
//�÷��̾��� ���°� öâ������ Endstate�� �ٲ�
void AEnemyAIController::Checkstate()
{
	//door ���°� öâ������ Endstate�� �ٲ�

	
	//if(isCutting)
	//{
	//	m_state = EEnemyState::End;


	//}
	// öâ���� �ƴ϶�� idle�� �ٲ�
	/*else*/
	//{
		//m_state = EEnemyState::Idle;
	//}
	

}

void AEnemyAIController::Endstate()
{

}





ATargetPoint* AEnemyAIController::GetRandomWaypoint()
{
//�����ϰ� ����Ʈ ����
auto index = FMath::RandRange(0, Waypoints.Num()-1);
return Cast<ATargetPoint>(Waypoints[index]);
}

void AEnemyAIController::GoToRandomWaypoint()
{
	//���� ����Ʈ �̵�
	MoveToActor(GetRandomWaypoint());
}

