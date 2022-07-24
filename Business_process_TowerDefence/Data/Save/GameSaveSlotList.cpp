
#include "Data/Save/GameSaveSlotList.h"

//#include "IImageWrapperModule.h"
//#include "ModuleManager.h"
//#include "IImageWrapper.h"
//#include "HAL/PlatformFilemanager.h"
//#include "FileHelper.h"



void UGameSaveSlotList::InitSaveGame(UWorld *InWorld)
{
	SlotList.InitSlot();
}

void UGameSaveSlotList::InitSaveGameFromArchives(UWorld *InWorld)
{
	for (auto &Tmp : SlotList.Slots)
	{
		Tmp.Value.GameThumbnail.InitResources();
	}
}


