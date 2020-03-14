// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_KwangAIController.h"
#include "UObject/ConstructorHelpers.h" 
#include "ARPGBoss_Kwang.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ABoss_KwangAIController::ABoss_KwangAIController() 
{
	BehaviorTreeCompo = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));

	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
}

void ABoss_KwangAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	AARPGBoss_Kwang* BossCharacter = Cast<AARPGBoss_Kwang>(InPawn);
	if (BossCharacter) 
	{
		if (BehaviorTreeCompo) 
		{
			if (BossCharacter->BehaviorTree)
			{
				if (BBComponent)
				{
					BBComponent->InitializeBlackboard(*(BossCharacter->BehaviorTree->BlackboardAsset));
				}
				BehaviorTreeCompo->StartTree(*(BossCharacter->BehaviorTree));
			}
		}

	}
	return;
}

void ABoss_KwangAIController::OnUnPossess()
{
	if (BehaviorTreeCompo)
	{
		BehaviorTreeCompo->StopTree(EBTStopMode::Safe);
	}

}

