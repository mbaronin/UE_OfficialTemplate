// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/GameCore/TowerDefencePlayerController.h"//player controller
#include "Core/GameCore/TowerDefenceGameState.h"//game State
#include "Core/GameCore/TowerDefencePlayerState.h"//player State

#include "Resources/Core/TDGameResources.h"//GameType 没用了
#include "Business_process_2\EnumType.h"

#include "Data/Core/CharacterData.h"		//角色数据 待删除

#include "RuleOfTheCharacter.generated.h"

class UBoxComponent;
class UArrowComponent;
class UWidgetComponent;
class USceneComponent;

UCLASS()
class BUSINESS_PROCESS_2_API ARuleOfTheCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARuleOfTheCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//计时器
	void AdvanceTimer();
	FTimerHandle CountdownTimerHandle;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/*
	模型
	*/

	//射线捕捉对象
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* TraceShowCharacterInformation;
	//开火点
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		UArrowComponent* OpenFriePoint;
	//信息提示框
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* Widget;
	//跟踪目标
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		USceneComponent* HomePoint;



	/*
	接口
	*/

protected:

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


public:
	//获取PlayerController
	FORCEINLINE ATowerDefencePlayerController* GetGameController() { return GetWorld() ? GetWorld()->GetFirstPlayerController<ATowerDefencePlayerController>() : nullptr; }
	//获取GameState
	FORCEINLINE ATowerDefenceGameState* GetGameState() { return GetWorld() ? GetWorld()->GetGameState<ATowerDefenceGameState>() : nullptr; }
	//获取玩家state
	FORCEINLINE ATowerDefencePlayerState* GetPlayerState() { return GetGameController()->GetPlayerState<ATowerDefencePlayerState>(); }
	//获取跟踪点
	FORCEINLINE USceneComponent* GetHommingPoint() const { return HomePoint; }
	//获取开火点
	FORCEINLINE UArrowComponent* GetFirePoint() const { return OpenFriePoint; }


	
	//UI
public:
	UFUNCTION(BlueprintCallable)
	void UpdateUI();

	/*
	数据
	*/

public:
	//受伤反馈类
	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<class ADrawText> DrawTextClass;

	//ID hash
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
		FGuid GUID;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool IsAttack = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float Health = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float MaxHealth = 0;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//	bool IsTeam = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackDistance = 150.0f;

	virtual ECharacterType GetCharacterType();
	
	virtual bool IsDeath();
	virtual float GetHealth();
	virtual float GetMaxHealth();
	//virtual ETeam GetTeamType();
	virtual FCharacterData* GetCharacterData();

	UFUNCTION(Blueprintable, BlueprintPure, Category = "Towers|Test")
		UStaticMesh* GetMesh(FTransform& Transform, int32 MeshID);

	UFUNCTION(Blueprintable, BlueprintPure)
		bool IsActive();
	/*
	UFUNCTION(Blueprintable, BlueprintPure)
		bool IsTeam();*/

//public:
//
//	UFUNCTION(BlueprintImplementableEvent)
//		void AttackBegin();
//
//	UFUNCTION(BlueprintImplementableEvent)
//		void AttackEnd();
//
//	UFUNCTION(BlueprintImplementableEvent)
//		void CharacterDeath();
//
//	UFUNCTION(BlueprintImplementableEvent)
//		void AnimTag();

	//死亡后n秒后销毁
	UPROPERTY(EditDefaultsOnly, Category = Death)
		float DelayDeath;
//	UPROPERTY(EditDefaultsOnly, Category = Type)
//		TEnumAsByte<EGameCharacterType::Type>  CharacterType;
//	//被动技能
//	UPROPERTY(EditDefaultsOnly, Category = "Skill")
//		TArray<int32> SkillIDs;
//	UFUNCTION(/*Server*/)
//		void ResetGUID();
//
//	UFUNCTION(/*Client*/)
//		void RemoveSkillSlot_Client(const FGuid& SlotID);
//
//	UFUNCTION(/*Client*/)
//		void AddSkillSlot_Client(const FGuid& SlotID);
	UFUNCTION()
		virtual void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	//更新被动技能
//	void UpdateSkill(int32);
//
//	UFUNCTION(/*Client*/)
//		void InitSkill();
//
//	UFUNCTION(BlueprintCallable, Category = "Add Skill request")
//		void SubmissionSkillRequest(int32 SkillID);
//	//角色属性
//public:
//	//由服务器调用
//	virtual void RegisterTeam() {}

	/*public:
		FORCEINLINE ATowersDefencePlayerController* GetGameController() { return GetWorld() ? GetWorld()->GetFirstPlayerController<ATowersDefencePlayerController>() : nullptr; }
		FORCEINLINE ATowersDefenceGameState* GetGameState() { return GetWorld() ? GetWorld()->GetGameState<ATowersDefenceGameState>() : nullptr; }
		FORCEINLINE ATowersDefencePlayerState* GetPlayerState() { return GetGameController()->GetPlayerState<ATowersDefencePlayerState>(); }

		FORCEINLINE USceneComponent* GetHommingPoint() const { return HomePoint; }
		FORCEINLINE UArrowComponent* GetFirePoint() const { return OpenFriePoint; }*/


};
