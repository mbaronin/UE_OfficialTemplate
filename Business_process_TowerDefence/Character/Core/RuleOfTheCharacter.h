// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/GameCore/TowerDefencePlayerController.h"//player controller
#include "Core/GameCore/TowerDefenceGameState.h"//game State
#include "Core/GameCore/TowerDefencePlayerState.h"//player State

#include "Resources/Core/TDGameResources.h"//GameType û����
#include "Business_process_2\EnumType.h"

#include "Data/Core/CharacterData.h"		//��ɫ���� ��ɾ��

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
	//��ʱ��
	void AdvanceTimer();
	FTimerHandle CountdownTimerHandle;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/*
	ģ��
	*/

	//���߲�׽����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* TraceShowCharacterInformation;
	//�����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		UArrowComponent* OpenFriePoint;
	//��Ϣ��ʾ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* Widget;
	//����Ŀ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		USceneComponent* HomePoint;



	/*
	�ӿ�
	*/

protected:

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


public:
	//��ȡPlayerController
	FORCEINLINE ATowerDefencePlayerController* GetGameController() { return GetWorld() ? GetWorld()->GetFirstPlayerController<ATowerDefencePlayerController>() : nullptr; }
	//��ȡGameState
	FORCEINLINE ATowerDefenceGameState* GetGameState() { return GetWorld() ? GetWorld()->GetGameState<ATowerDefenceGameState>() : nullptr; }
	//��ȡ���state
	FORCEINLINE ATowerDefencePlayerState* GetPlayerState() { return GetGameController()->GetPlayerState<ATowerDefencePlayerState>(); }
	//��ȡ���ٵ�
	FORCEINLINE USceneComponent* GetHommingPoint() const { return HomePoint; }
	//��ȡ�����
	FORCEINLINE UArrowComponent* GetFirePoint() const { return OpenFriePoint; }


	
	//UI
public:
	UFUNCTION(BlueprintCallable)
	void UpdateUI();

	/*
	����
	*/

public:
	//���˷�����
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

	//������n�������
	UPROPERTY(EditDefaultsOnly, Category = Death)
		float DelayDeath;
//	UPROPERTY(EditDefaultsOnly, Category = Type)
//		TEnumAsByte<EGameCharacterType::Type>  CharacterType;
//	//��������
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

	//���±�������
//	void UpdateSkill(int32);
//
//	UFUNCTION(/*Client*/)
//		void InitSkill();
//
//	UFUNCTION(BlueprintCallable, Category = "Add Skill request")
//		void SubmissionSkillRequest(int32 SkillID);
//	//��ɫ����
//public:
//	//�ɷ���������
//	virtual void RegisterTeam() {}

	/*public:
		FORCEINLINE ATowersDefencePlayerController* GetGameController() { return GetWorld() ? GetWorld()->GetFirstPlayerController<ATowersDefencePlayerController>() : nullptr; }
		FORCEINLINE ATowersDefenceGameState* GetGameState() { return GetWorld() ? GetWorld()->GetGameState<ATowersDefenceGameState>() : nullptr; }
		FORCEINLINE ATowersDefencePlayerState* GetPlayerState() { return GetGameController()->GetPlayerState<ATowersDefencePlayerState>(); }

		FORCEINLINE USceneComponent* GetHommingPoint() const { return HomePoint; }
		FORCEINLINE UArrowComponent* GetFirePoint() const { return OpenFriePoint; }*/


};
