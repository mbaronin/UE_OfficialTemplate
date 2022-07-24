// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Business_process_2 : ModuleRules
{
	public Business_process_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"UMG",
			"ScreenMoveTool",
			"SimpleScreenLoading" ,
			"SimpleArchives",
			"SimpleGameSettings",
			"SimpleTutoria",
			"ApexDestruction",/*破碎模块*/
			"Slate",
			"SlateCore",

			"AIModule",//AI服务 任务
			"SimpleDrawText",/*伤害反馈*/
			"RawMesh",//数据 用于骨骼Mesh中提取SMesh
			//"ImageWrapper",
			//"SimplePopup",
			//"Landscape"


		});/*添加插件生成*/

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
