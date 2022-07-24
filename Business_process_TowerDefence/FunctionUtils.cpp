// Copyright Epic Games, Inc. All Rights Reserved.

#include "FunctionUtils.h"
//#include "Business_process_2\FunctionUtils.h"


#include "Character/Core/RuleOfTheCharacter.h"
#include "Core/GameCore/TowerDefencePlayerController.h"

#include "Components/StaticMeshComponent.h"			//������
#include "Engine/StaticMesh.h"
#include "Engine\StaticMeshActor.h"

#include "RawMesh\Public\RawMesh.h"////��ȡ����������

#include "SkeletalRenderPublic.h"
#include "Rendering/SkeletalMeshRenderData.h"
#include "Rendering/SkeletalMeshLODRenderData.h"
#include "Components/SkeletalMeshComponent.h"


void FunctionUtils::CallUpdateAllClient(UWorld* World, TFunction<void(ATowerDefencePlayerController* MyPlayerController)> InImplement)
{
	if (World)
	{
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			if (ATowerDefencePlayerController* MyPlayerController = Cast<ATowerDefencePlayerController>(It->Get()))
			{
				InImplement(MyPlayerController);
			}
		}
	}
}


ARuleOfTheCharacter* FunctionUtils::FindTargetRecently(const TArray<ARuleOfTheCharacter*>& InCharacters, const FVector& Loc)
{
	if (InCharacters.Num())
	{
		float TargetDistance = 99999999;
		int32 Index = INDEX_NONE;

		for (int32 i = 0; i < InCharacters.Num(); i++)
		{
			if (ARuleOfTheCharacter* TCharacter = InCharacters[i])
			{
				FVector Location = TCharacter->GetActorLocation();
				FVector TmpVector = Location - Loc;
				float Distance = TmpVector.Size();

				if (Distance < TargetDistance && TCharacter->IsActive())
				{
					Index = i;
					TargetDistance = Distance;
				}
			}
		}

		if (Index != INDEX_NONE)
		{
			return InCharacters[Index];
		}
	}
	
	return nullptr;
}

ARuleOfTheBullet* FunctionUtils::SpawnBullet(UWorld* World, ARuleOfTheCharacter* Onwer, const int32 SkillID, const FVector& Loc, const FRotator& Rot)
{
	/*ARuleOfTheBullet* NewBullet = nullptr;
	if (World)
	{
		if (ATowersDefenceGameState* InGameState = World->GetGameState<ATowersDefenceGameState>())
		{
			if (const FSkillData* InData = InGameState->GetSkillData(SkillID))
			{
				if (ARuleOfTheBullet* Bullet = FunctionUtils::SpawnBullet(World, Onwer, InData->BulletClass, Loc, Rot))
				{
					NewBullet = Bullet;
				}
			}
		}
	}*/
	return nullptr;
}

ARuleOfTheBullet* FunctionUtils::SpawnBullet(UWorld* World, FGuid CharacterID, UClass* InClass)
{
	/*TArray<ARuleOfTheCharacter*> Characters;
	FunctionUtils::GetAllActor(World, Characters);

	for (auto& Tmp : Characters)
	{
		if (Tmp->GUID == CharacterID)
		{
			return SpawnBullet(World, Tmp, InClass, Tmp->GetFirePoint()->GetComponentLocation(), Tmp->GetFirePoint()->GetComponentRotation());
		}
	}*/
	return nullptr;
}

ARuleOfTheBullet* FunctionUtils::SpawnBullet(UWorld* World, APawn* NewPawn, UClass* InClass, const FVector& Loc, const FRotator& Rot)
{
	if (World && NewPawn && InClass)
	{
		FTransform Transform;
		Transform.SetLocation(Loc);
		Transform.SetRotation(Rot.Quaternion());

		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Instigator = NewPawn;

		if (ARuleOfTheBullet* Bullet = World->SpawnActor<ARuleOfTheBullet>(InClass, Transform, ActorSpawnParameters))
		{
			return Bullet;
		}
	}
	
	return nullptr;
}

AStaticMeshActor* FunctionUtils::SpawnTowersDoll(UWorld* World, int32 ID) 
{
	AStaticMeshActor* OutActor = nullptr;

	if (World)
	{
		//��State�л�ȡ ע���
		if (ATowerDefenceGameState* InGameState = World->GetGameState<ATowerDefenceGameState>())
		{
			const TArray<FCharacterData*>& InDatas = InGameState->GetTowerDataFormTable();
			//�����ҵ���Ҫ������ ������
			for (const auto& Tmp : InDatas)
			{
				if (Tmp->ID == ID)
				{
					UClass* NewClass = Tmp->CharacterBlueprintKey.LoadSynchronous();
					if (NewClass)
					{
						FVector SpawnVector = FVector::ZeroVector;
						SpawnVector.Z = 9999;
						//������ɫ (ֻΪ��ȡMesh)
						if (ARuleOfTheCharacter* RuleOfTheCharacter = World->SpawnActor<ARuleOfTheCharacter>(NewClass, SpawnVector, FRotator::ZeroRotator))
						{
							//����AStaticMeshActor
							if (AStaticMeshActor* MeshActor = World->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator))
							{
								FTransform Transform;
								//��ȡMesh ��Mesh��ֵ��MeshActor
								if (UStaticMesh* InMesh = RuleOfTheCharacter->GetMesh(Transform, ID))
								{
									MeshActor->SetMobility(EComponentMobility::Movable);
									MeshActor->GetStaticMeshComponent()->SetRelativeTransform(Transform);
									MeshActor->GetStaticMeshComponent()->SetStaticMesh(InMesh);
									MeshActor->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
									MeshActor->GetStaticMeshComponent()->SetCollisionProfileName(TEXT("NoCollision"));//��ʱ�ӵ�
									OutActor = MeshActor;
									RuleOfTheCharacter->Destroy();
								}
								else
								{
									MeshActor->Destroy();
									RuleOfTheCharacter->Destroy();
								}
							}
							else
							{
								RuleOfTheCharacter->Destroy();
							}
						}
					}

					break;
				}
			}
		}
	}

	return OutActor;
}



struct FMeshTracker
{
	FMeshTracker()
		:bValidColors(false)
	{
		FMemory::Memset(bValidTexCoords, 0);
	}

	bool bValidTexCoords[MAX_MESH_TEXTURE_COORDS]; //��ЧUV
	bool bValidColors;//��ɫ
};

void SkeletalMeshToRawMeshes(
	USkeletalMeshComponent* InComponent,
	int32 InOverallMaxLODs,
	const FMatrix& InComponentToWorld,
	FMeshTracker& MeshTracker,
	FRawMesh& RawMesh)
{
	FSkeletalMeshLODInfo& SrcLODInfo = *(InComponent->SkeletalMesh->GetLODInfo(InOverallMaxLODs));//��ȡLODInfo

	TArray<FFinalSkinVertex> FinalVertices;//����
	InComponent->GetCPUSkinnedVertices(FinalVertices, InOverallMaxLODs);//��ȡ���ж���
	FSkeletalMeshRenderData& SkeletalMeshRenderData = InComponent->MeshObject->GetSkeletalMeshRenderData();
	FSkeletalMeshLODRenderData& LODData = SkeletalMeshRenderData.LODRenderData[InOverallMaxLODs];
	//��������ӵ�RawMesh��
	for (int32 VertIndex = 0; VertIndex < FinalVertices.Num(); ++VertIndex)
	{
		RawMesh.VertexPositions.Add(InComponentToWorld.TransformPosition(FinalVertices[VertIndex].Position));
	}

	const uint32 NumTexCoords = FMath::Min(LODData.StaticVertexBuffers.StaticMeshVertexBuffer.GetNumTexCoords(), (uint32)MAX_MESH_TEXTURE_COORDS);
	const int32 NumSections = LODData.RenderSections.Num();

	FRawStaticIndexBuffer16or32Interface& IndexBuffer = *LODData.MultiSizeIndexContainer.GetIndexBuffer();
	for (int32 SectionIndex = 0; SectionIndex < NumSections; SectionIndex++)
	{
		const FSkelMeshRenderSection& SkelMeshSection = LODData.RenderSections[SectionIndex];
		if (InComponent->IsMaterialSectionShown(SkelMeshSection.MaterialIndex, InOverallMaxLODs))
		{
			const int32 NumWedges = SkelMeshSection.NumTriangles * 3;
			for (int32 WedgeIndex = 0; WedgeIndex < NumWedges; WedgeIndex++)
			{
				const int32 VertexIndexForWedge = IndexBuffer.Get(SkelMeshSection.BaseIndex + WedgeIndex);
				RawMesh.WedgeIndices.Add(VertexIndexForWedge);

				const FFinalSkinVertex& SkinnedVertex = FinalVertices[VertexIndexForWedge];
				const FVector TangentX = InComponentToWorld.TransformVector(SkinnedVertex.TangentX.ToFVector());
				const FVector TangentZ = InComponentToWorld.TransformVector(SkinnedVertex.TangentZ.ToFVector());
				const FVector4 UnpackedTangentX = SkinnedVertex.TangentX.ToFVector4();
				const FVector TangentY = (TangentZ ^ TangentX).GetSafeNormal() * UnpackedTangentX.W;

				RawMesh.WedgeTangentX.Add(TangentX);
				RawMesh.WedgeTangentY.Add(TangentY);
				RawMesh.WedgeTangentZ.Add(TangentZ);
				for (uint32 TexCoordIndex = 0; TexCoordIndex < MAX_MESH_TEXTURE_COORDS; TexCoordIndex++)
				{
					if (TexCoordIndex >= NumTexCoords)
					{
						RawMesh.WedgeTexCoords[TexCoordIndex].AddDefaulted();
					}
					else
					{
						RawMesh.WedgeTexCoords[TexCoordIndex].Add(LODData.StaticVertexBuffers.StaticMeshVertexBuffer.GetVertexUV(VertexIndexForWedge, TexCoordIndex));
						MeshTracker.bValidTexCoords[TexCoordIndex] = true;
					}
				}

				if (LODData.StaticVertexBuffers.ColorVertexBuffer.IsInitialized())
				{
					RawMesh.WedgeColors.Add(LODData.StaticVertexBuffers.ColorVertexBuffer.VertexColor(VertexIndexForWedge));
					MeshTracker.bValidColors = true;
				}
				else
				{
					RawMesh.WedgeColors.Add(FColor::White);
				}
			}

			int32 MaterialIndex = SkelMeshSection.MaterialIndex;
			if (SrcLODInfo.LODMaterialMap.IsValidIndex(SectionIndex) && SrcLODInfo.LODMaterialMap[SectionIndex] != INDEX_NONE)
			{
				MaterialIndex = FMath::Clamp<int32>(SrcLODInfo.LODMaterialMap[SectionIndex], 0, InComponent->SkeletalMesh->Materials.Num());
			}

			for (uint32 TriIndex = 0; TriIndex < SkelMeshSection.NumTriangles; TriIndex++)
			{
				RawMesh.FaceMaterialIndices.Add(MaterialIndex);
				RawMesh.FaceSmoothingMasks.Add(0);
			}
		}
	}
}


bool IsValidSkeletalMeshComponent(USkeletalMeshComponent* InComponent)
{
	return InComponent && InComponent->MeshObject && InComponent->IsVisible();
}



/////����Ϊ��Ҫ�ĺ���

UStaticMesh* FunctionUtils::SkeletalMeshToStaticMesh(USkeletalMeshComponent* SkeletalMeshComponent)
{
	UStaticMesh* StaticMesh = nullptr;

	if (UWorld* World = SkeletalMeshComponent->GetWorld())//NewObject��Ҫ����world
	{
		FRawMesh RawMesh;//ԭʼ����  ��Ҫ��build�а���
		FMeshTracker MeshTracker;//�Զ���ṹ�� //����׷��ģ��
		int32 OverallMaxLODs = 0;//���LOD(ֻ��ȡһ��LOD)

		const FTransform& InRootTransform = FTransform::Identity;//��ȡ�����任
		FMatrix WorldToRoot = InRootTransform.ToMatrixWithScale().Inverse();//ת��Ϊ���� ����
		FMatrix ComponentToWorld = SkeletalMeshComponent->GetComponentTransform().ToMatrixWithScale() * WorldToRoot;//������������ľ���
		//��֤����Mesh(��������������Ϸ��)
		if (IsValidSkeletalMeshComponent(SkeletalMeshComponent))
		{
			//����				//LOD			//����				//UV�ṹ��	//ԭʼ����
			SkeletalMeshToRawMeshes(SkeletalMeshComponent, OverallMaxLODs, ComponentToWorld, MeshTracker, RawMesh);
		}
		uint32 MaxInUseTextureCoordinate = 0;

		if (!MeshTracker.bValidColors)
		{
			RawMesh.WedgeColors.Empty();
		}

		for (uint32 TexCoordIndex = 0; TexCoordIndex < MAX_MESH_TEXTURE_COORDS; TexCoordIndex++)
		{
			if (!MeshTracker.bValidTexCoords[TexCoordIndex])
			{
				RawMesh.WedgeTexCoords[TexCoordIndex].Empty();
			}
			else
			{
				MaxInUseTextureCoordinate = FMath::Max(MaxInUseTextureCoordinate, TexCoordIndex);
			}
		}

		if (RawMesh.IsValidOrFixable())
		{
			FString MeshName = FGuid::NewGuid().ToString();//����SMesh �������
			StaticMesh = NewObject<UStaticMesh>(World, *MeshName, RF_Transient | RF_Standalone);
			StaticMesh->InitResources();//��ʼ����Դ

			StaticMesh->LightingGuid = FGuid::NewGuid();

			const uint32 LightMapIndex = FMath::Min(MaxInUseTextureCoordinate + 1, (uint32)8 - 1);

			FStaticMeshSourceModel& SrcModel = StaticMesh->AddSourceModel();
			SrcModel.BuildSettings.bRecomputeNormals = false;
			SrcModel.BuildSettings.bRecomputeTangents = false;
			SrcModel.BuildSettings.bRemoveDegenerates = true;
			SrcModel.BuildSettings.bUseHighPrecisionTangentBasis = false;
			SrcModel.BuildSettings.bUseFullPrecisionUVs = false;
			SrcModel.BuildSettings.bGenerateLightmapUVs = true;
			SrcModel.BuildSettings.SrcLightmapIndex = 0;
			SrcModel.BuildSettings.DstLightmapIndex = LightMapIndex;
			SrcModel.SaveRawMesh(RawMesh);

			for (const UMaterialInterface* Material : SkeletalMeshComponent->GetMaterials())
			{
				StaticMesh->StaticMaterials.Add(FStaticMaterial(const_cast<UMaterialInterface*>(Material)));
			}

			StaticMesh->ImportVersion = EImportStaticMeshVersion::LastVersion;
			StaticMesh->LightMapCoordinateIndex = LightMapIndex;

			TArray<int32> UniqueMaterialIndices;
			for (int32 MaterialIndex : RawMesh.FaceMaterialIndices)
			{
				UniqueMaterialIndices.AddUnique(MaterialIndex);
			}

			for (int32 i = 0; i < UniqueMaterialIndices.Num(); i++)
			{
				StaticMesh->GetSectionInfoMap().Set(0, i, FMeshSectionInfo(UniqueMaterialIndices[i]));
			}
			StaticMesh->GetOriginalSectionInfoMap().CopyFrom(StaticMesh->GetSectionInfoMap());

			StaticMesh->Build(false);
		}
	}

	return StaticMesh;
}
