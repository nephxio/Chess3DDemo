# Preferences

## Flow Mode
- **Automatic**

## Source Control
- Source branch: `master`
- Working branch: `upgrade-to-NET10`
- Pending changes: committed before starting the upgrade flow

## Target Framework
- Upgrade target: **.NET 10.0 (LTS)**

## Scope Notes
- Focus on repo-owned project files and build warnings that affect the Chess3DDemo project.
- External Unreal Engine source under `F:\UnrealEngine_5.7.4\UE_5.7` is treated as out of scope unless a fix is required in the repo itself.

## Commit Strategy
- **After Each Task**