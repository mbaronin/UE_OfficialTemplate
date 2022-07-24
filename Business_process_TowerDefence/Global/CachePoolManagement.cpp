#include "Global\CachePoolManagement.h"

void FDollMeshPoolManage::Constructor(UWorld* InWorld)
{

}

void FDollMeshPoolManage::Destructural()
{

}

void FDollMeshPoolManage::Add(int32 MeshID, UStaticMesh* NewMesh)
{
	if (StaticMeshMapping.Contains(MeshID))
	{
		StaticMeshMapping[MeshID] = NewMesh;
	}
	else
	{
		StaticMeshMapping.Add(MeshID, NewMesh);
	}
}

UStaticMesh* FDollMeshPoolManage::GetStaticMesh(int32 MeshID)
{
	if (StaticMeshMapping.Contains(MeshID))
	{
		return StaticMeshMapping[MeshID].Get();
	}

	return nullptr;
}