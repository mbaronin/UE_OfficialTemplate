// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "HowToUMGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class OFFICIALTEMPLATE_API AHowToUMGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    /** 移除当前菜单控件，并在指定类（如有）中新建控件。*/
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
        void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
    /** 游戏开始时调用。*/
    virtual void BeginPlay() override;

    /** 游戏开始时，用作菜单的控件类。*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
        TSubclassOf<UUserWidget> StartingWidgetClass;

    /** 用作菜单的控件实例。*/
    UPROPERTY()
        UUserWidget* CurrentWidget;

};
