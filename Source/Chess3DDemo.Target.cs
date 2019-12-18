// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Chess3DDemoTarget : TargetRules
{
	public Chess3DDemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Chess3DDemo" } );

        DefaultBuildSettings = BuildSettingsVersion.V2;

    }
}
