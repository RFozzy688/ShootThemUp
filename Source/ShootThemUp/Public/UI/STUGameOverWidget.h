// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;
    
protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

    //UPROPERTY(meta = (BindWidget))
    //UButton* ResetLevelButton;

private:
    void OnMatchStateChanged(ESTUMatchState State);
    void UpdatePlayersStat();

    //UFUNCTION()
    //void OnResetLevel();
};
