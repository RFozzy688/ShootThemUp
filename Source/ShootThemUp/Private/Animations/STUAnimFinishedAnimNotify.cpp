// Shoot Them Up Game. All Rights Reserved


#include "Animations/STUAnimFinishedAnimNotify.h"

void USTUAnimFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{
    OnNotified.Broadcast(MeshComp);

    Super::Notify(MeshComp, Animation);
}
