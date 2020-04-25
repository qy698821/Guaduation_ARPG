// Fill out your copyright notice in the Description page of Project Settings.


#include "Down_Minions_Controller.h"
#include "UObject/ConstructorHelpers.h" 
#include "ARPGMinions_Down.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ADown_Minions_Controller::ADown_Minions_Controller()
{
	BehaviorTreeCompo = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));

	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
}

void ADown_Minions_Controller::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	AARPGMinions_Down* MinionsCharacter = Cast<AARPGMinions_Down>(InPawn);
	if (MinionsCharacter)
	{
		if (BehaviorTreeCompo)
		{
			if (MinionsCharacter->BehaviorTree)
			{
				if (BBComponent)
				{
					BBComponent->InitializeBlackboard(*(MinionsCharacter->BehaviorTree->BlackboardAsset));
				}
				BehaviorTreeCompo->StartTree(*(MinionsCharacter->BehaviorTree));
			}
		}

	}
	return;
}

void ADown_Minions_Controller::OnUnPossess()
{
	if (BehaviorTreeCompo)
	{
		BehaviorTreeCompo->StopTree(EBTStopMode::Safe);
	}

}
