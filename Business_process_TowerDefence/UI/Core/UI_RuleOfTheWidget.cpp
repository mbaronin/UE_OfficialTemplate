// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Core/UI_RuleOfTheWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h"


void UUI_RuleOfTheWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GUID = FGuid::NewGuid();
	//TxtDebugMsg = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtDebugMsg")));
}

//±¨´í
//UUI_RuleOfTheWidget::UUI_RuleOfTheWidget(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//	//GUID = FGuid::NewGuid();
//}




UWidgetAnimation* UUI_RuleOfTheWidget::GetNameWidgetAnimation(const FString& WidgetAnimationName) const
{
	if (UWidgetBlueprintGeneratedClass* WidgetBlueprintGenerated = Cast<UWidgetBlueprintGeneratedClass>(GetClass()))
	{
		TArray<UWidgetAnimation*> TArrayAnimations = WidgetBlueprintGenerated->Animations;
		UWidgetAnimation** MyTempAnimation = TArrayAnimations.FindByPredicate([&](const UWidgetAnimation* OurAnimation) {return OurAnimation->GetFName().ToString() == (WidgetAnimationName + FString("_INST")); });
		return *MyTempAnimation;
	}

	return nullptr;
}

ATowerDefenceGameState* UUI_RuleOfTheWidget::GetGameState()
{
	if (GetWorld())
	{
		return GetWorld()->GetGameState<ATowerDefenceGameState>();
	}

	return nullptr;
}

ATowerDefencePlayerState* UUI_RuleOfTheWidget::GetPlayerState()
{
	if (GetPlayerController())
	{
		return GetPlayerController()->GetPlayerState<ATowerDefencePlayerState>();
	}

	return nullptr;
}

ATowerDefencePlayerController* UUI_RuleOfTheWidget::GetPlayerController()
{
	if (ATowerDefencePlayerController* PlayerControl = 
		Cast<ATowerDefencePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
	
		return PlayerControl;
	}

	return nullptr;
}

ABusiness_process_2GameModeBase* UUI_RuleOfTheWidget::GetGameMode()
{
	if (GetWorld())
	{
		return GetWorld()->GetAuthGameMode<ABusiness_process_2GameModeBase>();

	}

	return nullptr;
	
}


