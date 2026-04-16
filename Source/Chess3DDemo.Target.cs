// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Chess3DDemoTarget : TargetRules
{
	public Chess3DDemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		CppStandard = CppStandardVersion.Cpp20;

		ExtraModuleNames.AddRange( new string[] { "Chess3DDemo" } );
	}
}
