// Shoot Them Up Game. All Rights Reserved


#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
    }

    //if (QuitGameButton)
    //{
    //    QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
    //}

    //InitLevelItems();
}

void USTUMenuWidget::OnStartGame()
{
    const FName StartupLevelName = "TestLevel";
    UGameplayStatics::OpenLevel(this, StartupLevelName);
}