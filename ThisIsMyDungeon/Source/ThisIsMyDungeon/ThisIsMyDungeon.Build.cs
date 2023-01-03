// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ThisIsMyDungeon : ModuleRules
{
	public ThisIsMyDungeon(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "Niagara" });
	}
}
