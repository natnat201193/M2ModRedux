﻿using System;
using System.IO;
using System.Windows.Forms;
using M2Mod.Config;
using M2Mod.Dialogs;
using M2Mod.Interop;
using M2Mod.Interop.Structures;

namespace M2Mod.Tools
{
    public partial class CompareModelsForm : Form
    {
        public CompareModelsForm()
        {
            InitializeComponent();

            this.Icon = Properties.Resources.Icon;

            oldM2TextBox.Text = ProfileManager.CurrentProfile.Configuration.OldCompareM2;
            newM2TextBox.Text = ProfileManager.CurrentProfile.Configuration.NewCompareM2;
            weightThresholdTextBox.Text = ProfileManager.CurrentProfile.Configuration.CompareWeightThreshold.ToString();
        }

        private void OldM2BrowseButton_Click(object sender, EventArgs e)
        {
            using (var dialog = new OpenFileDialog())
            {
                dialog.Filter = Filters.M2;
                dialog.FileName = Path.GetFileName(oldM2TextBox.Text);
                dialog.InitialDirectory = oldM2TextBox.Text.Length > 0 ? Path.GetDirectoryName(oldM2TextBox.Text) : ProfileManager.CurrentProfile.Settings.WorkingDirectory;

                var result = dialog.ShowDialog();
                if (result != DialogResult.OK)
                    return;

                oldM2TextBox.Text = dialog.FileName;
            }
        }

        private void NewM2BrowseButton_Click(object sender, EventArgs e)
        {
            using (var dialog = new OpenFileDialog())
            {
                dialog.Filter = Filters.M2;
                dialog.FileName = Path.GetFileName(newM2TextBox.Text);
                dialog.InitialDirectory = newM2TextBox.Text.Length > 0 ? Path.GetDirectoryName(newM2TextBox.Text) : ProfileManager.CurrentProfile.Settings.WorkingDirectory;

                var result = dialog.ShowDialog();
                if (result != DialogResult.OK)
                    return;

                newM2TextBox.Text = dialog.FileName;
            }
        }

        private void CompareButton_Click(object sender, EventArgs e)
        {
            Compare();
        }

        private void Compare()
        {
            if (!File.Exists(oldM2TextBox.Text))
            {
                MessageBox.Show($"No such file: '{oldM2TextBox.Text}'", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            if (!File.Exists(newM2TextBox.Text))
            {
                MessageBox.Show($"No such file: '{newM2TextBox.Text}'", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            ProfileManager.CurrentProfile.Configuration.OldCompareM2 = oldM2TextBox.Text;
            ProfileManager.CurrentProfile.Configuration.NewCompareM2 = newM2TextBox.Text;

            if (!float.TryParse(weightThresholdTextBox.Text,
                out ProfileManager.CurrentProfile.Configuration.CompareWeightThreshold))
            {
                ProfileManager.CurrentProfile.Configuration.CompareWeightThreshold = 0.0f;
                weightThresholdTextBox.Text = "0";
            }

            if (!float.TryParse(scaleTextBox.Text,
                out ProfileManager.CurrentProfile.Configuration.CompareSourceScale))
            {
                ProfileManager.CurrentProfile.Configuration.CompareSourceScale = 1.0f;
                scaleTextBox.Text = "1";
            }

            ProfileManager.CurrentProfile.Configuration.PredictScale = predictScaleCheckBox.Checked;

            var oldSettings = new Settings()
            {
                WorkingDirectory = PropagateWorkingDirectory(oldM2TextBox.Text),
                MappingsDirectory = ProfileManager.CurrentProfile.Settings.MappingsDirectory,
            };

            var oldM2 = Imports.M2_Create(ref oldSettings);
            var errorStatus = Imports.M2_Load(oldM2, oldM2TextBox.Text);
            if (errorStatus != M2LibError.OK)
            {
                MessageBox.Show(string.Format("Failed load old m2: {0}", Imports.GetErrorText(errorStatus)), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Imports.M2_Free(oldM2);
                return;
            }

            var newSettings = new Settings()
            {
                WorkingDirectory = PropagateWorkingDirectory(newM2TextBox.Text),
                MappingsDirectory = ProfileManager.CurrentProfile.Settings.MappingsDirectory,
            };

            var newM2 = Imports.M2_Create(ref newSettings);
            errorStatus = Imports.M2_Load(newM2, newM2TextBox.Text);
            if (errorStatus != M2LibError.OK)
            {
                MessageBox.Show(string.Format("Failed load new m2: {0}", Imports.GetErrorText(errorStatus)), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Imports.M2_Free(oldM2);
                Imports.M2_Free(newM2);
                return;
            }

            IntPtr wrapper = Imports.Wrapper_Create(oldM2, newM2,
                ProfileManager.CurrentProfile.Configuration.CompareWeightThreshold,
                true,
                ProfileManager.CurrentProfile.Configuration.PredictScale,
                ref ProfileManager.CurrentProfile.Configuration.CompareSourceScale);

            resultsTextBox.Text = "";
            if (Imports.Wrapper_DiffSize(wrapper) == 0)
            {
                MessageBox.Show("Empty result from bone comparator");
                Imports.Wrapper_Free(wrapper);
                Imports.M2_Free(oldM2);
                Imports.M2_Free(newM2);
                return;
            }

            resultsTextBox.Text = Imports.Wrapper_GetStringResult(wrapper);

            Imports.Wrapper_Free(wrapper);
            Imports.M2_Free(oldM2);
            Imports.M2_Free(newM2);
        }

        private string PropagateWorkingDirectory(string filePath)
        {
            var fileName = Path.GetFileName(filePath);

            var storage = Imports.FileStorage_Get(ProfileManager.CurrentProfile.Settings.MappingsDirectory);

            var info = Imports.FileStorage_GetFileInfoByPartialPath(storage, '/' + fileName);
            if (info == IntPtr.Zero)
                return "";

            var infoPath = Imports.FileInfo_GetPath(info);
            var arr = infoPath.Split('/');
            var path = filePath;
            for (var i = 0; i < arr.Length; ++i)
                path = Path.GetDirectoryName(path);

            return path;
        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            using (var dialog = new SaveFileDialog())
            {
                dialog.CheckPathExists = true;
                dialog.Filter = Filters.Txt;

                if (oldM2TextBox.Text.Length > 0)
                {
                    var name = Path.GetFileNameWithoutExtension(oldM2TextBox.Text);
                    if (name.Length > 0)
                        dialog.FileName = $"bone_migration_{name}.txt";
                }

                var result = dialog.ShowDialog();
                if (result != DialogResult.OK)
                    return;

                File.WriteAllText(dialog.FileName, resultsTextBox.Text);
            }
        }

        private void ResultsTextBox_TextChanged(object sender, EventArgs e)
        {
            saveButton.Enabled = resultsTextBox.Text.Length > 0;
        }

        private void PredictScaleCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            scaleTextBox.Enabled = !predictScaleCheckBox.Checked;
        }
    }
}
