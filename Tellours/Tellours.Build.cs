// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Tellours : ModuleRules
{
	public Tellours(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "NavigationSystem", "AIModule", "GameplayTasks", "Niagara", "PhysicsCore" });
		//PublicDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks"});
    }
}
