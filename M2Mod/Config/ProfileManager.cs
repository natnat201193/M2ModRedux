﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;
using Newtonsoft.Json;

namespace M2Mod.Config
{
    public static class ProfileManager
    {
        private static readonly string ProfilesFile = "profiles.json";

        private static readonly List<SettingsProfile> Profiles = new List<SettingsProfile>();

        static ProfileManager()
        {
        }

        public static SettingsProfile CurrentProfile { get; set; }

        public static void AddProfile(SettingsProfile profile) => Profiles.Add(profile);

        public static void RemoveProfile(Guid id) => Profiles.RemoveAll(_ => _.Id == id);

        public static bool Load(string file, bool createDefault)
        {
            var config = new ConfigFile();
            try
            {
                if (string.IsNullOrWhiteSpace(file))
                    file = Path.Combine(Path.GetDirectoryName(Assembly.GetEntryAssembly()?.Location) ?? "",
                        ProfilesFile);

                config = LoadProfiles(file);
            }
            catch
            {
                MessageBox.Show("Failed to load profiles", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            if (config.Profiles.Count == 0 && createDefault)
                config.Profiles.Add(Defaults.SettingsProfile);

            if (config.Profiles.Count > 0)
            {
                Profiles.Clear();
                Profiles.AddRange(config.Profiles);

                CurrentProfile = Profiles.FirstOrDefault(_ => _.Id == config.ActiveProfile) ?? Profiles.First();

                return true;
            }

            return false;
        }

        public static void Save()
        {
            try
            {
                SaveProfiles();
            }
            catch
            {
                MessageBox.Show("Failed to save profiles", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private static ConfigFile LoadProfiles(string file)
        {
            if (!File.Exists(file))
                return new ConfigFile();

            using (var reader = File.OpenText(file))
            {
                var serializer = new JsonSerializer();

                return (ConfigFile)serializer.Deserialize(reader, typeof(ConfigFile));
            }
        }

        private static void SaveProfiles()
        {
            using (var writer = File.CreateText("profiles.json"))
            {
                var obj = new ConfigFile() {
                    ActiveProfile = CurrentProfile?.Id ?? Guid.Empty,
                    Profiles = Profiles
                };

                var serializer = new JsonSerializer {Formatting = Formatting.Indented};

                serializer.Serialize(writer, obj);
            }
        }

        public static List<SettingsProfile> GetProfiles()
        {
            return Profiles;
        }

        public static void MoveProfile(Guid id, bool down)
        {
            var index = Profiles.FindIndex(_ => _.Id == id);
            if (index == -1)
                return;

            if (down)
            {
                if (index + 1 < Profiles.Count)
                    SwapProfiles(index, index + 1);
            }
            else
            {
                if (index - 1 >= 0)
                    SwapProfiles(index, index - 1);
            }
        }

        private static void SwapProfiles(int i, int j)
        {
            var tmp = Profiles[i];
            Profiles[i] = Profiles[j];
            Profiles[j] = tmp;
        }
    }
}
