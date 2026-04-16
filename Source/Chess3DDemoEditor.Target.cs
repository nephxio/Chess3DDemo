// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Chess3DDemoEditorTarget : TargetRules
{
	public Chess3DDemoEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		CppStandard = CppStandardVersion.Cpp20;
       bOverrideBuildEnvironment = true;

		ExtraModuleNames.AddRange( new string[] { "Chess3DDemo" } );
	}
}
