// Shoot Them Up Game. All Rights Reserved


#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"
#include "Components/STUAIPerceptionComponent.h"

ASTUAIController::ASTUAIController() 
{
    AIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("AIPerceptionComponent");
    SetPerceptionComponent(*AIPerceptionComponent);
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (const auto STUCharacter = Cast<ASTUAICharacter>(InPawn))
    {
        RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
    }
}

void ASTUAIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    const auto AimActor = AIPerceptionComponent->GetClosestEnemy();
    SetFocus(AimActor);
}
