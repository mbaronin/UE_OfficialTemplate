
#pragma once

#include "CoreMinimal.h"
#include "Global\ManageCore.h"
#include "CachePoolManagement.generated.h"

class UStaticMesh;
/**
 * FManagementCore<FGlobalManagement> GManagement;
	FManagementCore<FDollMeshPoolManage> GDollMeshPoolManage;
 */

USTRUCT()
struct BUSINESS_PROCESS_2_API FDollMeshPoolManage
{
	GENERATED_USTRUCT_BODY()

		void Constructor(UWorld* InWorld);
	void Destructural();

	void Add(int32, UStaticMesh*);
	UStaticMesh* GetStaticMesh(int32);

protected:

	UPROPERTY()
		TMap<int32, TWeakObjectPtr<UStaticMesh>> StaticMeshMapping;
};

