# 01-fix-chess3ddemo-warnings: Fix Chess3DDemo Warnings

## Objective
Update the repo-owned Unreal target rules so the Chess3DDemo project builds without the upgrade warnings produced by UnrealBuildTool.

## Scope
- `Source/Chess3DDemoEditor.Target.cs`
- `Source/Chess3DDemo.Target.cs` (for consistency)
- Validation via a focused build of the Chess3DDemo editor target

## Research Notes
- The solution contains many Unreal Engine source projects outside the repository under `F:\UnrealEngine_5.7.4\UE_5.7`.
- The full Visual Studio solution build reports unrelated external failures (for example, unsupported program targets and access denied in LiveLinkHub).
- The only repo-owned upgrade warning observed so far is the UnrealBuildTool upgrade warning in `Chess3DDemoEditor.Target.cs` about backward-compatible build settings and include order.
- The editor target also requires a unique build environment before stricter build settings can be enabled.

## Planned Fixes
1. Update `Chess3DDemoEditor.Target.cs` to current Unreal defaults:
   - `DefaultBuildSettings = BuildSettingsVersion.V6`
   - `IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7`
   - `CppStandard = CppStandardVersion.Cpp20`
   - `BuildEnvironment = TargetBuildEnvironment.Unique`
2. Apply the same modern defaults to `Chess3DDemo.Target.cs` where appropriate.
3. Rebuild the Chess3DDemo editor target and confirm the repo-owned warning is gone.

## Validation Plan
- Build the Chess3DDemo editor target after the code change.
- If the full solution build still reports unrelated external engine failures, document them separately and use the targeted build as the primary validation for the repo-owned project.

## Validation Result
- The focused `Chess3DDemoEditor` build succeeded after the target rule and source fixes.
