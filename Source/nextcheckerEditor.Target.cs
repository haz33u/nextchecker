using UnrealBuildTool;
using System.Collections.Generic;

public class nextcheckerEditorTarget : TargetRules
{
    public nextcheckerEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.AddRange(new string[] { "nextchecker" });
    }
}
