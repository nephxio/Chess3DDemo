# Upgrade Plan

## Strategy
Target the repo-owned Unreal project settings that cause upgrade warnings during build, then validate with a focused build of the Chess3DDemo editor target.

## Scope
- Update the project target rules in `Source/Chess3DDemoEditor.Target.cs`.
- Apply the same baseline build setting modernization to `Source/Chess3DDemo.Target.cs` for consistency.
- Rebuild the Chess3DDemo editor target and confirm the upgrade warnings are resolved for the repo-owned project.

## Tasks
- `01-fix-chess3ddemo-warnings` — Update target rules and validate the build.