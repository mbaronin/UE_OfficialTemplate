// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("this is DebugMessage!"));

//#include "Business_process_2\FunctionUtils.h"

class ARuleOfTheCharacter;
class ARuleOfTheBullet;

enum EGameSaveType
{
	/*NONE = 0b0000,
	ARCHIVES = 0b0001,*/
	NONE,
	ARCHIVES,
};


class ATowerDefencePlayerController;

//class USizeBox;
//class ARuleOfTheCharacter;//
//class IRuleCharacter;
class UStaticMesh;
class AStaticMeshActor;
class USkeletalMeshComponent;
//class UWorld;
//class ARuleOfTheBullet;//
//class APlayerSkillSlotActor;
//class ASceneCapture2D;

namespace FunctionUtils
{
	/*�ಥ*/
	void CallUpdateAllClient(UWorld* World, TFunction<void(ATowerDefencePlayerController* MyPlayerController)> InImplement);

	//Ѱ���������(�������� , �Ƚ�λ��)
	ARuleOfTheCharacter* FindTargetRecently(const TArray<ARuleOfTheCharacter*>& InCharacters, const FVector& Loc);
	
	//�����ӵ�
	ARuleOfTheBullet* SpawnBullet(UWorld* World, ARuleOfTheCharacter* Onwer, const int32 SkillID, const FVector& Loc, const FRotator& Rot);
	ARuleOfTheBullet* SpawnBullet(UWorld* World, FGuid CharacterID, UClass* InClass);
	ARuleOfTheBullet* SpawnBullet(UWorld* World, APawn* NewPawn, UClass* InClass, const FVector& Loc, const FRotator& Rot);

	AStaticMeshActor* SpawnTowersDoll(UWorld* World, int32 ID);

	UStaticMesh* SkeletalMeshToStaticMesh(USkeletalMeshComponent* SkeletalMeshComponent);

	template<class A, class B>
	void GetAllActor(UWorld* World, TArray<B*>& Array)
	{
		for (TActorIterator<A>It(World, A::StaticClass()); It; ++It)
		{
			if (B* Tmp = Cast<A>(*It))
			{
				Array.Add(Tmp);
			}
		}
	}

	template<class Type>
	void GetAllActor(UWorld* World, TArray<Type*>& Array)
	{
		for (TActorIterator<Type>It(World, Type::StaticClass()); It; ++It)
		{
			Array.Add(*It);
		}
	}

	//��ȡ�Ƚ��ٵ�����
	template<class Type>
	TArray<Type*> GetAllActor(UWorld* World)
	{
		TArray<Type*> Array;
		for (TActorIterator<Type>It(World, Type::StaticClass()); It; ++It)
		{
			if (Type* A = Cast<Type>(*It))
			{
				Array.Add(A);
			}
		}

		return Array;
	}






	template<class T>
	T* GetSave(UWorld* InWorld, const TCHAR* SaveName, int32 SaveIndex = INDEX_NONE, EGameSaveType InFlag = EGameSaveType::NONE)
	{
		T* InSlot = nullptr;

		auto InitSlot = [&]()
		{
			InSlot = Cast<T>(UGameplayStatics::CreateSaveGameObject(T::StaticClass()));
			if (InSlot)
			{
				InSlot->InitSaveGame(InWorld);
			}
		};

		if (InFlag & EGameSaveType::ARCHIVES)
		{
			FString SlotString;
			if (SaveIndex != INDEX_NONE)
			{
				//SlotString = FString::Printf(SaveName, SaveIndex);
			}
			else
			{
				SlotString = SaveName;
				if (SlotString.Contains("%i"))
				{
					SlotString.RemoveFromEnd("_%i");
					SlotString += TEXT("_0");
				}
			}

			InSlot = Cast<T>(UGameplayStatics::LoadGameFromSlot(SlotString, 0));
			if (!InSlot)
			{
				InitSlot();
			}
			else
			{
				InSlot->InitSaveGameFromArchives(InWorld);
			}
		}
		else
		{
			InitSlot();
		}

		return InSlot;
	}

}

