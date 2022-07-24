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

	//��Ļ�ƶ����
	float ScreenMoveSpeed;
	bool CanScreenMove;
	//��קʱ ���λ�û�����BUG ˫�ؼ��
	bool Tmpbool;
	bool DoubleTmpbool;



protected:
	//�����Ļ�ƶ����
	FScreenMoveUnits ScreenMoveUnits;

	FHitResult MouseHitPoint;

	//Ԥ�����������
		UMaterialInterface* RedMaterial;
	//Ԥ�����������
		UMaterialInterface* GreenMaterial;

public:
	//������������ӿ���
	void SetInputModeGameAndUI();

	//�����밴��
	virtual void SetupInputComponent()override;

	//������ ���ֿ���
	void MouseWheelUp();
	void MouseWheelDown();


	//�������Ĵ���
	FSimpleDelegate EventMouseRightPressed;
	//�ɿ����Ĵ���
	FSimpleDelegate EventMouseRightReleased;

	void MouseRightButtonPressed();
	void MouseRightButtonReleased();

	//�����ӵ��Ĵ���
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
