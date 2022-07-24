#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataCore.generated.h"

//���� ID ��� ��ʯ ͭ��

USTRUCT(BlueprintType)
struct FDataCore : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FDataCore();

	virtual void Init();
	//����if(ID==-1)�ж��Ƿ�������
	virtual bool IsValid() const;

	//����
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	FName Name;
	//ID
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	int32 ID;
	//���
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	int32 GameGlod;
	
	//��ʯ
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	int32 Diamonds;

	//ͭ�� 
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	int32 Copper;
};