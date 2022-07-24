#pragma once

#include "CoreMinimal.h"
#include "Data/Core/DataCore.h"
#include "Business_process_2\EnumType.h"
#include "SkillData.generated.h"

class ARuleOfTheBulletl;

USTRUCT(BlueprintType)
struct FSkillData : public FDataCore
{
	GENERATED_USTRUCT_BODY()



	typedef FDataCore Super;

	FSkillData();

	virtual void Init() override;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Attribute")
	FSkillType SkillType;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Attribute")
	TAssetPtr<class UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Attribute")
	TSubclassOf<AActor> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Attribute")
	FText SkillIntroduce;

	UPROPERTY()
	ESubmissionSkillRequestType SubmissionSkillRequestType;

	//��ӽ��
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
	float Glod;

	//�������ֵ
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
	float Health;

	//��ӹ�����
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
	float PhysicalAttack;

	//��ӻ���
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
	float Armor;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
	float AttackSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
	float WalkSpeed;

	//0 ����ȫ�������е��� 
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
	float AttackRange;

	//���ܳ���ʱ��
	UPROPERTY(EditDefaultsOnly, Category = "Dynamic Skills")
	float MaxSkillDuration;

	//���ܶ� ����Ч��ά��һ���׶�
	UPROPERTY()//"Dynamic Skills"
	float SkillDuration;

	//���ܼ�� ���� ÿ��һ�뼤��һ�� ����Ǿ�����ֵ Ϊ�������͵ļ�����׼��
	UPROPERTY()//"Dynamic Skills"
	float SkillDurationTime;

	//���ܳ���ʱ��
	UPROPERTY(EditDefaultsOnly, Category = "Main Skill")
	float CD;

	UPROPERTY()
	float CDTime;

	UPROPERTY()
	bool bBecomeEffective;

	//��̬����
	float GetDurationPercent() const;

	//������
	float GetCDPercent() const;

	//ֻ�����ڶ�̬����
	void ResetDuration();

	//������������
	void ResetCD();

	friend bool operator==(const FSkillData& X, const FSkillData& Y)
	{
		return X.ID == Y.ID;
	}
};
