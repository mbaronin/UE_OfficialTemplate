// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "SaveGameCore.generated.h"

/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API USaveGameCore : public USaveGame
{
	GENERATED_BODY()
	
public:

	//������ʱ��ŵ��ã�����Ƕ�ȡ�Ͳ������
	virtual void InitSaveGame(UWorld *InWorld);

	//��ȡ�浵Ҳ����øú���
	virtual void InitSaveGameFromArchives(UWorld *InWorld){}
};
