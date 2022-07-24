// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TopPawn_Cpp : ModuleRules
{
	public TopPawn_Cpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 

			"HeadMountedDisplay", 
			"NavigationSystem", 
			"AIModule", 
			"Niagara",

			"Slate",
			"SlateCore",
			"UMG",

			"SimpleScreenMove", 
			"SimplePopup" 
		
		
		
		
		});
    }
}
