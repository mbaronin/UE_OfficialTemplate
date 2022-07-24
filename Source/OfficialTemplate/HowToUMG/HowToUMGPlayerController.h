// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HowToUMGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OFFICIALTEMPLATE_API AHowToUMGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
