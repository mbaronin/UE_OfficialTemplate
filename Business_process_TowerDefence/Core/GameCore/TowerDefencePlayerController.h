// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ScreenMove.h"

#include "TowerDefencePlayerController.generated.h"


class UMaterialInterface;
/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API ATowerDefencePlayerController : public APlayerController
{
	GENERATED_BODY()



public:
	ATowerDefencePlayerController();

	virtual void Tick(float DeltaSeconds)override;

	virtual void BeginPlay()override;

	//屏幕移动插件
	float ScreenMoveSpeed;
	bool CanScreenMove;
	//拖拽时 光标位置会归零的BUG 双重检测
	bool Tmpbool;
	bool DoubleTmpbool;



protected:
	//添加屏幕移动插件
	FScreenMoveUnits ScreenMoveUnits;

	FHitResult MouseHitPoint;

	//预览网格体材质
		UMaterialInterface* RedMaterial;
	//预览网格体材质
		UMaterialInterface* GreenMaterial;

public:
	//将光标锁定在视口中
	void SetInputModeGameAndUI();

	//绑定输入按键
	virtual void SetupInputComponent()override;

	//鼠标操作 滚轮控制
	void MouseWheelUp();
	void MouseWheelDown();


	//按下鼠标的代理
	FSimpleDelegate EventMouseRightPressed;
	//松开鼠标的代理
	FSimpleDelegate EventMouseRightReleased;

	void MouseRightButtonPressed();
	void MouseRightButtonReleased();

	//生成子弹的代理
	//FSpawnBulletDelegate SpawnBulletDelegate;



	const FHitResult& GetHitResult();

//	class AStoneDefenceGameMode* GetGameMode();
//	class ATowersDefenceGameState* GetGameState();
//
//	UFUNCTION(/*Server*/)
//		void RemoveSkillSlot_Server(const FGuid& CharacterID, const FGuid& SlotID);
//
//	UFUNCTION(/*Server*/)
//		void AddSkillSlot_Server(const FGuid& CharacterID, const FGuid& SlotID);
//
//	UFUNCTION(/*Client*/)
//		void SpawnBullet_Client(const FGuid& CharacterID, const int32& SkillID);

	UFUNCTION(/*Client*/)
		void UpdateInventory_Client(const FGuid& InventorySlotGUID, bool bInCD);

//	UFUNCTION(/*Client*/)
//		void UpdatePlayerSkill_Client(const FGuid& PlayerSlotGUID, bool bInCD);
//
//	UFUNCTION(/*Client*/)
//		void SpawnPlayerSkill_Client(const int32& PlayerSKillID);
//public:
//	UFUNCTION()
//		ATowers* SpawnTowers(int32 CharacterID, int32 CharacterLevel, const FVector& Loction, const FRotator& Rotator);
//
//	UFUNCTION()
//		AMonsters* SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector& Loction, const FRotator& Rotator);
//

};
