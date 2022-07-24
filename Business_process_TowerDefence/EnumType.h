#pragma once

#include "CoreMinimal.h"
#include "EnumType.generated.h"

DECLARE_DELEGATE_OneParam(FSimpleOneInt32Delegate, int32)


//����ETeam
//��ɫ����ECharacterType

//struct FMapSize
//{
//	FVector2D BigMapRealSize;
//};

UENUM()
enum ETeam
{
	RED,
	BLUE,
	MAX,
};


UENUM(BlueprintType)
enum class ECharacterType :uint8
{
	TOWER,
	MAIN_TOWER,
	MONSTER,
	BOSS_MONSTER,
	NONE,
};

//�ӵ�����
UENUM(BlueprintType)
enum class EBulletType :uint8
{
	BULLET_NONE,			//�������κ�Ч��

	BULLET_DIRECT_LINE,		//���ϰ�ֱ�߹�������͸
	BULLET_LINE,			//�Ǹ������ͣ����ӵ���
	BULLET_TRACK_LINE,		//��������
	BULLET_TRACK_LINE_SP,	//��������
	BULLET_RANGE_THROW,		//��Χ�˺��������ף�
	BULLET_RANGE,			//��Χ�˺��������Ա���
	BULLET_CHAIN,			//�������ͣ������˺�����;
};



//UENUM(BlueprintType)
//namespace EGameCharacterType
//{
//	enum Type
//	{
//		MINI,
//		BOSS,
//		MAX,
//	};
//}
//
//UENUM(BlueprintType)
//enum class EMiniMapType :uint8
//{
//	REAL_MAP,
//	GRAPHICAL_MAP,
//};
//
//enum EGameSaveType
//{
//	NONE = 0b0000,
//	ARCHIVES = 0b0001,
//};

 
 
UENUM(BlueprintType)
enum class ESubmissionSkillRequestType :uint8
{
	AUTO,			//����Ȩ������������
	MANUAL,			//����Ȩ�������ͻ���
};



//SKILL::
UENUM(BlueprintType)
enum class ESkillType :uint8
{
	BURST,		//һ����ɵ��˺�
	SECTION,	//��һ����Χ���������� ʱ������ͻ�ԭ
	ITERATION,	//����һ��ʱ���ڽ��лָ�
};

UENUM(BlueprintType)
enum class ESkillTargetType :uint8
{
	FRIENDLY_FORCES = 0,
	ENEMY,
};

UENUM(BlueprintType)
enum class ESkillEffectType :uint8
{
	ADD,
	SUBTRACT,
};

USTRUCT(BlueprintType)
struct FSkillType
{
	GENERATED_USTRUCT_BODY()

		FSkillType()
		:SkillType(ESkillType::SECTION)
		, TargetType(ESkillTargetType::FRIENDLY_FORCES)
		, SkillEffectType(ESkillEffectType::ADD)
	{

	}

	UPROPERTY(EditDefaultsOnly, Category = "Type")
		ESkillType SkillType;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
		ESkillTargetType TargetType;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
		ESkillEffectType SkillEffectType;
};
