// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveStruct.generated.h"

USTRUCT()
struct BUSINESS_PROCESS_2_API FGameArchivesThumbnail
{
	GENERATED_USTRUCT_BODY()

		FGameArchivesThumbnail();

	UPROPERTY(Transient)
		UTexture2D* GameThumbnail;

	UPROPERTY(SaveGame)
		FString ScrPath;

	void InitResources();
	void ReleaseResources();

	void LoadTexture2D(const FString& ImagePath);
};


USTRUCT()
struct BUSINESS_PROCESS_2_API FSaveSlot
{
	GENERATED_USTRUCT_BODY()

		FSaveSlot();

	//����ͼ
	UPROPERTY(SaveGame)
		FGameArchivesThumbnail GameThumbnail;

	//�洢�����ݺ�����
	UPROPERTY(SaveGame)
		FText DateText;

	//�ؿ�����
	UPROPERTY(SaveGame)
		FText LevelName;

	//�½�����
	UPROPERTY(SaveGame)
		FText ChapterName;

	//�Ƿ�浵
	UPROPERTY(SaveGame)
		bool bSave;

	void Init();
};

USTRUCT()
struct BUSINESS_PROCESS_2_API FSaveSlotList
{
	GENERATED_USTRUCT_BODY()
	
		FSaveSlotList();

	//���ⲿ����
	void InitSlot();

	//�浵λ
	UPROPERTY(SaveGame)
		TMap<int32, FSaveSlot> Slots;
	//����
	UPROPERTY(SaveGame)
		TMap<int32, float> DegreeOfCompletion;

	//��ȡ��Ч�洢λ
	int32 GetSerialNumber();

	bool RemoveAtGameData(int32 SlotNumber);
	bool AddGameDataByNumber(int32 SlotNumber);


};


