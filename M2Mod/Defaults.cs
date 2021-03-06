﻿using M2Mod.Config;
using M2Mod.Interop.Structures;

namespace M2Mod
{
    public static class Defaults
    {
        public static Settings Settings => new Settings()
        {
            WorkingDirectory = "",
            OutputDirectory = "",
            MappingsDirectory = "",
            ForceLoadExpansion = Expansion.None,
            MergeBones = true,
            MergeAttachments = true,
            MergeCameras = true,
            FixSeams = false,
            FixEdgeNormals = true,
            IgnoreOriginalMeshIndexes = false,
            FixAnimationsTest = false,
            CustomFilesStartIndex = 0,
        };

        public static SettingsProfile SettingsProfile => new SettingsProfile("Default", Settings, new Configuration());
    };
}
