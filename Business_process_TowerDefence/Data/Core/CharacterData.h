#pragma once

#include "CoreMinimal.h"
#include "Data/Core/DataCore.h"
#include "Data/Core/SkillData.h"
#include "CharacterData.generated.h"


USTRUCT(BlueprintType)
struct FCharacterData : public FDataCore
{
	GENERATED_USTRUCT_BODY()

	typedef FDataCore Super;
public:
	FCharacterData();

	virtual void Init() override;

	//��Դ
	//////////////////////////////////////////////////////////////////////////
	//��ɫ��ͼʵ��
	UPROPERTY(EditDefaultsOnly, Category = "Table")
		TAssetSubclassOf<class ARuleOfTheCharacter> CharacterBlueprintKey;
	//��ͬ��Tsubofclass
	//��ɫͼƬ
	UPROPERTY(EditDefaultsOnly, Category = "Table")
		TAssetPtr<class UTexture2D> Icon;

	//����
	////////////////////////////////////////////////////////
	//�ȼ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Attribute")
	int32 Lv;

	//�������ֵ
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MaxHealth;

	//����ֵ
	UPROPERTY()
	float Health;

	//��������
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float PhysicalAttack;

	//����
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float Armor;

	//�ƶ��ٶ�
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float WalkSpeed;

	//�����ֵ
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MaxEmpircalValue;

	UPROPERTY()
	float EmpircalValue;

	//CD
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float CD;

	//�����ٶ�
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float AttackSpeed;

	//��������
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float AttackDistance;

	//������� ������Ѷ��ٽ�ҿ��Խ���
	//����ǹ��� �������������Ի�ȡ���ٽ��
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float Glod;

	//��ɫ���
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	FText Introduction;

	//����
	//////////////////////////////////////////////////////////////////////////
	//��ӽ��
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddGlod;

	//�������ֵ
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddHealth;

	//��ӹ�����
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddPhysicalAttack;

	//��ӻ���
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddArmor;

	//��Ӿ���ֵ
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddEmpiricalValue;

	//��ӹ����ٶ�
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddAttackSpeed;

	//�Զ��ָ�����ֵ
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float RestoreHealth;

	/*UPROPERTY()
	TEnumAsByte<ETeam> Team;*/

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FRotator Rotator;

	//����
	//////////////////////////////////////////////////////////////////////////
	//��ɫӵ�е�ʵ�弼������
	UPROPERTY()
	TArray<FSkillData> CharacterSkill;

	//��̬���� ����Ǳ�����ӵ�������߼���
	UPROPERTY()
	TMap<FGuid,FSkillData> AdditionalSkillData;
public:
	float GetEPPercent() const;

	void UpdateHealth();

	bool UpdateEP(float InExp);

	void UpdateLevel();

public:
	float GetMaxHealth() const;
	float GetAttack() const;
	float GetArmor() const;
	float GetCD() const;
	float GetAttackSpeed()const;
	float GetWalkSpeed()const;
};