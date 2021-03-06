﻿namespace M2Mod.Tools
{
    partial class CompareModelsForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.weightThresholdLabel = new System.Windows.Forms.Label();
            this.weightThresholdTextBox = new System.Windows.Forms.TextBox();
            this.saveButton = new System.Windows.Forms.Button();
            this.compareButton = new System.Windows.Forms.Button();
            this.resultsTextBox = new System.Windows.Forms.TextBox();
            this.newM2BrowseButton = new System.Windows.Forms.Button();
            this.oldM2BrowseButton = new System.Windows.Forms.Button();
            this.newM2Label = new System.Windows.Forms.Label();
            this.oldM2Label = new System.Windows.Forms.Label();
            this.newM2TextBox = new System.Windows.Forms.TextBox();
            this.oldM2TextBox = new System.Windows.Forms.TextBox();
            this.scaleLabel = new System.Windows.Forms.Label();
            this.scaleTextBox = new System.Windows.Forms.TextBox();
            this.predictScaleCheckBox = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // weightThresholdLabel
            // 
            this.weightThresholdLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.weightThresholdLabel.AutoSize = true;
            this.weightThresholdLabel.Location = new System.Drawing.Point(391, 69);
            this.weightThresholdLabel.Name = "weightThresholdLabel";
            this.weightThresholdLabel.Size = new System.Drawing.Size(91, 13);
            this.weightThresholdLabel.TabIndex = 23;
            this.weightThresholdLabel.Text = "Weight Threshold";
            // 
            // weightThresholdTextBox
            // 
            this.weightThresholdTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.weightThresholdTextBox.Location = new System.Drawing.Point(488, 66);
            this.weightThresholdTextBox.Name = "weightThresholdTextBox";
            this.weightThresholdTextBox.Size = new System.Drawing.Size(44, 20);
            this.weightThresholdTextBox.TabIndex = 22;
            // 
            // saveButton
            // 
            this.saveButton.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.saveButton.Enabled = false;
            this.saveButton.Location = new System.Drawing.Point(305, 241);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(64, 30);
            this.saveButton.TabIndex = 21;
            this.saveButton.Text = "Save";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.SaveButton_Click);
            // 
            // compareButton
            // 
            this.compareButton.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.compareButton.Location = new System.Drawing.Point(235, 241);
            this.compareButton.Name = "compareButton";
            this.compareButton.Size = new System.Drawing.Size(64, 30);
            this.compareButton.TabIndex = 20;
            this.compareButton.Text = "Compare";
            this.compareButton.UseVisualStyleBackColor = true;
            this.compareButton.Click += new System.EventHandler(this.CompareButton_Click);
            // 
            // resultsTextBox
            // 
            this.resultsTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.resultsTextBox.Location = new System.Drawing.Point(17, 91);
            this.resultsTextBox.Multiline = true;
            this.resultsTextBox.Name = "resultsTextBox";
            this.resultsTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.resultsTextBox.Size = new System.Drawing.Size(578, 144);
            this.resultsTextBox.TabIndex = 19;
            this.resultsTextBox.TextChanged += new System.EventHandler(this.ResultsTextBox_TextChanged);
            // 
            // newM2BrowseButton
            // 
            this.newM2BrowseButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.newM2BrowseButton.Location = new System.Drawing.Point(543, 39);
            this.newM2BrowseButton.Name = "newM2BrowseButton";
            this.newM2BrowseButton.Size = new System.Drawing.Size(52, 20);
            this.newM2BrowseButton.TabIndex = 18;
            this.newM2BrowseButton.Text = "...";
            this.newM2BrowseButton.UseVisualStyleBackColor = true;
            this.newM2BrowseButton.Click += new System.EventHandler(this.NewM2BrowseButton_Click);
            // 
            // oldM2BrowseButton
            // 
            this.oldM2BrowseButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.oldM2BrowseButton.Location = new System.Drawing.Point(543, 12);
            this.oldM2BrowseButton.Name = "oldM2BrowseButton";
            this.oldM2BrowseButton.Size = new System.Drawing.Size(52, 20);
            this.oldM2BrowseButton.TabIndex = 17;
            this.oldM2BrowseButton.Text = "...";
            this.oldM2BrowseButton.UseVisualStyleBackColor = true;
            this.oldM2BrowseButton.Click += new System.EventHandler(this.OldM2BrowseButton_Click);
            // 
            // newM2Label
            // 
            this.newM2Label.AutoSize = true;
            this.newM2Label.Location = new System.Drawing.Point(8, 42);
            this.newM2Label.Name = "newM2Label";
            this.newM2Label.Size = new System.Drawing.Size(47, 13);
            this.newM2Label.TabIndex = 16;
            this.newM2Label.Text = "New M2";
            // 
            // oldM2Label
            // 
            this.oldM2Label.AutoSize = true;
            this.oldM2Label.Location = new System.Drawing.Point(14, 16);
            this.oldM2Label.Name = "oldM2Label";
            this.oldM2Label.Size = new System.Drawing.Size(41, 13);
            this.oldM2Label.TabIndex = 15;
            this.oldM2Label.Text = "Old M2";
            // 
            // newM2TextBox
            // 
            this.newM2TextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.newM2TextBox.Location = new System.Drawing.Point(61, 39);
            this.newM2TextBox.Name = "newM2TextBox";
            this.newM2TextBox.Size = new System.Drawing.Size(471, 20);
            this.newM2TextBox.TabIndex = 14;
            // 
            // oldM2TextBox
            // 
            this.oldM2TextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.oldM2TextBox.Location = new System.Drawing.Point(61, 13);
            this.oldM2TextBox.Name = "oldM2TextBox";
            this.oldM2TextBox.Size = new System.Drawing.Size(471, 20);
            this.oldM2TextBox.TabIndex = 13;
            // 
            // scaleLabel
            // 
            this.scaleLabel.AutoSize = true;
            this.scaleLabel.Location = new System.Drawing.Point(204, 69);
            this.scaleLabel.Name = "scaleLabel";
            this.scaleLabel.Size = new System.Drawing.Size(69, 13);
            this.scaleLabel.TabIndex = 25;
            this.scaleLabel.Text = "Source scale";
            // 
            // scaleTextBox
            // 
            this.scaleTextBox.Enabled = false;
            this.scaleTextBox.Location = new System.Drawing.Point(154, 66);
            this.scaleTextBox.Name = "scaleTextBox";
            this.scaleTextBox.Size = new System.Drawing.Size(44, 20);
            this.scaleTextBox.TabIndex = 24;
            // 
            // predictScaleCheckBox
            // 
            this.predictScaleCheckBox.AutoSize = true;
            this.predictScaleCheckBox.Checked = true;
            this.predictScaleCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.predictScaleCheckBox.Location = new System.Drawing.Point(61, 68);
            this.predictScaleCheckBox.Name = "predictScaleCheckBox";
            this.predictScaleCheckBox.Size = new System.Drawing.Size(87, 17);
            this.predictScaleCheckBox.TabIndex = 26;
            this.predictScaleCheckBox.Text = "Predict scale";
            this.predictScaleCheckBox.UseVisualStyleBackColor = true;
            this.predictScaleCheckBox.CheckedChanged += new System.EventHandler(this.PredictScaleCheckBox_CheckedChanged);
            // 
            // CompareModelsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(610, 276);
            this.Controls.Add(this.predictScaleCheckBox);
            this.Controls.Add(this.scaleLabel);
            this.Controls.Add(this.scaleTextBox);
            this.Controls.Add(this.weightThresholdLabel);
            this.Controls.Add(this.weightThresholdTextBox);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.compareButton);
            this.Controls.Add(this.resultsTextBox);
            this.Controls.Add(this.newM2BrowseButton);
            this.Controls.Add(this.oldM2BrowseButton);
            this.Controls.Add(this.newM2Label);
            this.Controls.Add(this.oldM2Label);
            this.Controls.Add(this.newM2TextBox);
            this.Controls.Add(this.oldM2TextBox);
            this.Name = "CompareModelsForm";
            this.Text = "Compare models";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label weightThresholdLabel;
        private System.Windows.Forms.TextBox weightThresholdTextBox;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button compareButton;
        private System.Windows.Forms.TextBox resultsTextBox;
        private System.Windows.Forms.Button newM2BrowseButton;
        private System.Windows.Forms.Button oldM2BrowseButton;
        private System.Windows.Forms.Label newM2Label;
        private System.Windows.Forms.Label oldM2Label;
        private System.Windows.Forms.TextBox newM2TextBox;
        private System.Windows.Forms.TextBox oldM2TextBox;
        private System.Windows.Forms.Label scaleLabel;
        private System.Windows.Forms.TextBox scaleTextBox;
        private System.Windows.Forms.CheckBox predictScaleCheckBox;
    }
}