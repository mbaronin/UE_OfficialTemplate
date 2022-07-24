#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataCore.generated.h"

//名字 ID 金币 钻石 铜币

USTRUCT(BlueprintType)
struct FDataCore : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FDataCore();

	virtual void Init();
	//根据if(ID==-1)判断是否有意义
	virtual bool IsValid() const;

	//名字
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	FName Name;
	//ID
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	int32 ID;
	//金币
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	int32 GameGlod;
	
	//钻石
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	int32 Diamonds;

	//铜币 
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	int32 Copper;
};