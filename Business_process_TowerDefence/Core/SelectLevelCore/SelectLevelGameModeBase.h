// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SelectLevelGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API ASelectLevelGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASelectLevelGameModeBase();

	virtual void BeginPlay() override;
};
