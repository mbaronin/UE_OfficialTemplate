// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/GameCore/TowerDefencePlayerController.h"
#include "Core/GameCore/TowerDefencePlayerState.h"
#include "Core/GameCore/TowerDefenceGameState.h"
#include "Business_process_2\Business_process_2GameModeBase.h"

#include "UI_RuleOfTheWidget.generated.h"

/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API UUI_RuleOfTheWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void NativeConstruct();
	//报错
	//UUI_RuleOfTheWidget(const FObjectInitializer& ObjectInitializer);//对象初始值设定项

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
		FGuid GUID;

	class UWidgetAnimation* GetNameWidgetAnimation(const FString& WidgetAnimationName) const;


	//获取State playercontroller
	class ATowerDefenceGameState* GetGameState();
	class ATowerDefencePlayerState* GetPlayerState();
	class ATowerDefencePlayerController* GetPlayerController();
	class ABusiness_process_2GameModeBase* GetGameMode();

	void testfunction(FString string) { GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, string); };
	
	void testfunction(float Infloat) {	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::SanitizeFloat(Infloat));	};
};




	