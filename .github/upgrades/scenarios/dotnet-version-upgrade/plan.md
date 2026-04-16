# Upgrade Plan

## Strategy
Target the repo-owned Unreal project settings that cause upgrade warnings during build, then validate with a focused build of the Chess3DDemo editor target.

### 01-fix-chess3ddemo-warnings: Fix Chess3DDemo Warnings
Update the repo-owned Unreal target settings and source code so the Chess3DDemo editor target builds cleanly under the installed engine.

**Done when**:
- `Source/Chess3DDemoEditor.Target.cs` uses the modern Unreal build defaults required by the engine version in use.
- `Source/Chess3DDemo.Target.cs` is aligned with the same baseline settings where appropriate.
- `Chess3DDemo.uproject` no longer references the unavailable `VisualStudioTools` plugin.
- The focused `Chess3DDemoEditor` build succeeds with no repo-owned upgrade warnings or compile errors.

## Scope
- Update the project target rules in `Source/Chess3DDemoEditor.Target.cs`.
- Apply the same baseline build setting modernization to `Source/Chess3DDemo.Target.cs` for consistency.
- Remove the unavailable project plugin reference from `Chess3DDemo.uproject` if needed for the installed engine.
- Fix any repo-owned compile warnings surfaced by the focused build.