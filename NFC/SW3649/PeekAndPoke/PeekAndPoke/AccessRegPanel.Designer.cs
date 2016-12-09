namespace PeekAndPoke
{
    partial class AccessRegPanel
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AccessRegPanel));
            this.closeAccess_Btn = new System.Windows.Forms.Button();
            this.readAccess_Btn = new System.Windows.Forms.Button();
            this.AUTH0_Box = new System.Windows.Forms.GroupBox();
            this.AUTH0_TextBox = new System.Windows.Forms.TextBox();
            this.AUTH0_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.AUTH0_Label = new System.Windows.Forms.Label();
            this.AUTHLIM_Label = new System.Windows.Forms.Label();
            this.PACK_Label = new System.Windows.Forms.Label();
            this.PWD_Label = new System.Windows.Forms.Label();
            this.I2C_PROT_Label = new System.Windows.Forms.Label();
            this.ACCESS_Box = new System.Windows.Forms.GroupBox();
            this.NFC_PROT_CheckBox = new System.Windows.Forms.CheckBox();
            this.NFC_DIS_SEC1_CheckBox = new System.Windows.Forms.CheckBox();
            this.AUTHLIM_TextBox = new System.Windows.Forms.TextBox();
            this.ACCESS_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.PWD_Box = new System.Windows.Forms.GroupBox();
            this.PWD_TextBox = new System.Windows.Forms.TextBox();
            this.PWD_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.PACK_Box = new System.Windows.Forms.GroupBox();
            this.PACK_TextBox = new System.Windows.Forms.TextBox();
            this.PACK_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.PT_I2C_Box = new System.Windows.Forms.GroupBox();
            this.PT_I2C_Info_PicBox = new System.Windows.Forms.PictureBox();
            this._2K_PROT_CheckBox = new System.Windows.Forms.CheckBox();
            this.SRAM_PROT_CheckBox = new System.Windows.Forms.CheckBox();
            this.I2C_PROT_Combo = new System.Windows.Forms.ComboBox();
            this.writeAccess_Btn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.AUTH0_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.AUTH0_Info_PicBox)).BeginInit();
            this.ACCESS_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ACCESS_Info_PicBox)).BeginInit();
            this.PWD_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PWD_Info_PicBox)).BeginInit();
            this.PACK_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PACK_Info_PicBox)).BeginInit();
            this.PT_I2C_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PT_I2C_Info_PicBox)).BeginInit();
            this.SuspendLayout();
            // 
            // closeAccess_Btn
            // 
            this.closeAccess_Btn.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.closeAccess_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.closeAccess_Btn.Location = new System.Drawing.Point(308, 264);
            this.closeAccess_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.closeAccess_Btn.Name = "closeAccess_Btn";
            this.closeAccess_Btn.Size = new System.Drawing.Size(113, 33);
            this.closeAccess_Btn.TabIndex = 31;
            this.closeAccess_Btn.Text = "Close";
            this.closeAccess_Btn.UseVisualStyleBackColor = true;
            // 
            // readAccess_Btn
            // 
            this.readAccess_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.readAccess_Btn.Location = new System.Drawing.Point(308, 227);
            this.readAccess_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.readAccess_Btn.Name = "readAccess_Btn";
            this.readAccess_Btn.Size = new System.Drawing.Size(113, 33);
            this.readAccess_Btn.TabIndex = 30;
            this.readAccess_Btn.Text = "Read Access";
            this.readAccess_Btn.UseVisualStyleBackColor = true;
            this.readAccess_Btn.Click += new System.EventHandler(this.readAccessRegAndShow);
            // 
            // AUTH0_Box
            // 
            this.AUTH0_Box.Controls.Add(this.AUTH0_TextBox);
            this.AUTH0_Box.Controls.Add(this.AUTH0_Info_PicBox);
            this.AUTH0_Box.Controls.Add(this.AUTH0_Label);
            this.AUTH0_Box.Location = new System.Drawing.Point(13, 12);
            this.AUTH0_Box.Margin = new System.Windows.Forms.Padding(4);
            this.AUTH0_Box.Name = "AUTH0_Box";
            this.AUTH0_Box.Padding = new System.Windows.Forms.Padding(4);
            this.AUTH0_Box.Size = new System.Drawing.Size(247, 82);
            this.AUTH0_Box.TabIndex = 29;
            this.AUTH0_Box.TabStop = false;
            this.AUTH0_Box.Text = "AUTH0";
            // 
            // AUTH0_TextBox
            // 
            this.AUTH0_TextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.AUTH0_TextBox.Location = new System.Drawing.Point(83, 41);
            this.AUTH0_TextBox.Margin = new System.Windows.Forms.Padding(4);
            this.AUTH0_TextBox.MaxLength = 2;
            this.AUTH0_TextBox.Name = "AUTH0_TextBox";
            this.AUTH0_TextBox.Size = new System.Drawing.Size(43, 22);
            this.AUTH0_TextBox.TabIndex = 15;
            // 
            // AUTH0_Info_PicBox
            // 
            this.AUTH0_Info_PicBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("AUTH0_Info_PicBox.BackgroundImage")));
            this.AUTH0_Info_PicBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.AUTH0_Info_PicBox.Location = new System.Drawing.Point(212, 12);
            this.AUTH0_Info_PicBox.Name = "AUTH0_Info_PicBox";
            this.AUTH0_Info_PicBox.Size = new System.Drawing.Size(24, 22);
            this.AUTH0_Info_PicBox.TabIndex = 16;
            this.AUTH0_Info_PicBox.TabStop = false;
            this.AUTH0_Info_PicBox.Click += new System.EventHandler(this.AUTH0_Info_PicBox_Click);
            // 
            // AUTH0_Label
            // 
            this.AUTH0_Label.AutoSize = true;
            this.AUTH0_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.AUTH0_Label.Location = new System.Drawing.Point(8, 44);
            this.AUTH0_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.AUTH0_Label.Name = "AUTH0_Label";
            this.AUTH0_Label.Size = new System.Drawing.Size(56, 16);
            this.AUTH0_Label.TabIndex = 13;
            this.AUTH0_Label.Text = "AUTH0 ";
            // 
            // AUTHLIM_Label
            // 
            this.AUTHLIM_Label.AutoSize = true;
            this.AUTHLIM_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.AUTHLIM_Label.Location = new System.Drawing.Point(8, 44);
            this.AUTHLIM_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.AUTHLIM_Label.Name = "AUTHLIM_Label";
            this.AUTHLIM_Label.Size = new System.Drawing.Size(70, 16);
            this.AUTHLIM_Label.TabIndex = 13;
            this.AUTHLIM_Label.Text = "AUTHLIM ";
            // 
            // PACK_Label
            // 
            this.PACK_Label.AutoSize = true;
            this.PACK_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PACK_Label.Location = new System.Drawing.Point(18, 63);
            this.PACK_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.PACK_Label.Name = "PACK_Label";
            this.PACK_Label.Size = new System.Drawing.Size(46, 16);
            this.PACK_Label.TabIndex = 13;
            this.PACK_Label.Text = "PACK ";
            // 
            // PWD_Label
            // 
            this.PWD_Label.AutoSize = true;
            this.PWD_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PWD_Label.Location = new System.Drawing.Point(7, 64);
            this.PWD_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.PWD_Label.Name = "PWD_Label";
            this.PWD_Label.Size = new System.Drawing.Size(71, 16);
            this.PWD_Label.TabIndex = 13;
            this.PWD_Label.Text = "Password ";
            // 
            // I2C_PROT_Label
            // 
            this.I2C_PROT_Label.AutoSize = true;
            this.I2C_PROT_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.I2C_PROT_Label.Location = new System.Drawing.Point(7, 108);
            this.I2C_PROT_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.I2C_PROT_Label.Name = "I2C_PROT_Label";
            this.I2C_PROT_Label.Size = new System.Drawing.Size(75, 16);
            this.I2C_PROT_Label.TabIndex = 13;
            this.I2C_PROT_Label.Text = "I2C_PROT ";
            // 
            // ACCESS_Box
            // 
            this.ACCESS_Box.Controls.Add(this.NFC_PROT_CheckBox);
            this.ACCESS_Box.Controls.Add(this.NFC_DIS_SEC1_CheckBox);
            this.ACCESS_Box.Controls.Add(this.AUTHLIM_TextBox);
            this.ACCESS_Box.Controls.Add(this.AUTHLIM_Label);
            this.ACCESS_Box.Controls.Add(this.ACCESS_Info_PicBox);
            this.ACCESS_Box.Location = new System.Drawing.Point(281, 12);
            this.ACCESS_Box.Name = "ACCESS_Box";
            this.ACCESS_Box.Size = new System.Drawing.Size(197, 151);
            this.ACCESS_Box.TabIndex = 0;
            this.ACCESS_Box.TabStop = false;
            this.ACCESS_Box.Text = "ACCESS";
            // 
            // NFC_PROT_CheckBox
            // 
            this.NFC_PROT_CheckBox.Location = new System.Drawing.Point(6, 112);
            this.NFC_PROT_CheckBox.Name = "NFC_PROT_CheckBox";
            this.NFC_PROT_CheckBox.Size = new System.Drawing.Size(115, 24);
            this.NFC_PROT_CheckBox.TabIndex = 0;
            this.NFC_PROT_CheckBox.Text = "NFC_PROT";
            // 
            // NFC_DIS_SEC1_CheckBox
            // 
            this.NFC_DIS_SEC1_CheckBox.Location = new System.Drawing.Point(6, 82);
            this.NFC_DIS_SEC1_CheckBox.Name = "NFC_DIS_SEC1_CheckBox";
            this.NFC_DIS_SEC1_CheckBox.Size = new System.Drawing.Size(140, 24);
            this.NFC_DIS_SEC1_CheckBox.TabIndex = 0;
            this.NFC_DIS_SEC1_CheckBox.Text = "NFC_DIS_SEC1";
            // 
            // AUTHLIM_TextBox
            // 
            this.AUTHLIM_TextBox.Location = new System.Drawing.Point(85, 41);
            this.AUTHLIM_TextBox.MaxLength = 1;
            this.AUTHLIM_TextBox.Name = "AUTHLIM_TextBox";
            this.AUTHLIM_TextBox.Size = new System.Drawing.Size(55, 22);
            this.AUTHLIM_TextBox.TabIndex = 0;
            // 
            // ACCESS_Info_PicBox
            // 
            this.ACCESS_Info_PicBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("ACCESS_Info_PicBox.BackgroundImage")));
            this.ACCESS_Info_PicBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ACCESS_Info_PicBox.Location = new System.Drawing.Point(162, 12);
            this.ACCESS_Info_PicBox.Name = "ACCESS_Info_PicBox";
            this.ACCESS_Info_PicBox.Size = new System.Drawing.Size(24, 22);
            this.ACCESS_Info_PicBox.TabIndex = 0;
            this.ACCESS_Info_PicBox.TabStop = false;
            this.ACCESS_Info_PicBox.Click += new System.EventHandler(this.ACCESS_Info_PicBox_Click);
            // 
            // PWD_Box
            // 
            this.PWD_Box.Controls.Add(this.PWD_TextBox);
            this.PWD_Box.Controls.Add(this.PWD_Label);
            this.PWD_Box.Controls.Add(this.PWD_Info_PicBox);
            this.PWD_Box.Location = new System.Drawing.Point(13, 112);
            this.PWD_Box.Name = "PWD_Box";
            this.PWD_Box.Size = new System.Drawing.Size(247, 107);
            this.PWD_Box.TabIndex = 0;
            this.PWD_Box.TabStop = false;
            this.PWD_Box.Text = "PWD";
            // 
            // PWD_TextBox
            // 
            this.PWD_TextBox.Location = new System.Drawing.Point(86, 61);
            this.PWD_TextBox.MaxLength = 8;
            this.PWD_TextBox.Name = "PWD_TextBox";
            this.PWD_TextBox.Size = new System.Drawing.Size(131, 22);
            this.PWD_TextBox.TabIndex = 0;
            // 
            // PWD_Info_PicBox
            // 
            this.PWD_Info_PicBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PWD_Info_PicBox.BackgroundImage")));
            this.PWD_Info_PicBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PWD_Info_PicBox.Location = new System.Drawing.Point(212, 12);
            this.PWD_Info_PicBox.Name = "PWD_Info_PicBox";
            this.PWD_Info_PicBox.Size = new System.Drawing.Size(24, 22);
            this.PWD_Info_PicBox.TabIndex = 0;
            this.PWD_Info_PicBox.TabStop = false;
            this.PWD_Info_PicBox.Click += new System.EventHandler(this.PWD_Info_PicBox_Click);
            // 
            // PACK_Box
            // 
            this.PACK_Box.Controls.Add(this.PACK_TextBox);
            this.PACK_Box.Controls.Add(this.PACK_Label);
            this.PACK_Box.Controls.Add(this.PACK_Info_PicBox);
            this.PACK_Box.Location = new System.Drawing.Point(493, 181);
            this.PACK_Box.Name = "PACK_Box";
            this.PACK_Box.Size = new System.Drawing.Size(200, 100);
            this.PACK_Box.TabIndex = 0;
            this.PACK_Box.TabStop = false;
            this.PACK_Box.Text = "PACK";
            // 
            // PACK_TextBox
            // 
            this.PACK_TextBox.Location = new System.Drawing.Point(89, 63);
            this.PACK_TextBox.MaxLength = 4;
            this.PACK_TextBox.Name = "PACK_TextBox";
            this.PACK_TextBox.Size = new System.Drawing.Size(100, 22);
            this.PACK_TextBox.TabIndex = 0;
            // 
            // PACK_Info_PicBox
            // 
            this.PACK_Info_PicBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PACK_Info_PicBox.BackgroundImage")));
            this.PACK_Info_PicBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PACK_Info_PicBox.Location = new System.Drawing.Point(165, 11);
            this.PACK_Info_PicBox.Name = "PACK_Info_PicBox";
            this.PACK_Info_PicBox.Size = new System.Drawing.Size(24, 22);
            this.PACK_Info_PicBox.TabIndex = 0;
            this.PACK_Info_PicBox.TabStop = false;
            this.PACK_Info_PicBox.Click += new System.EventHandler(this.PACK_Info_PicBox_Click);
            // 
            // PT_I2C_Box
            // 
            this.PT_I2C_Box.Controls.Add(this.PT_I2C_Info_PicBox);
            this.PT_I2C_Box.Controls.Add(this._2K_PROT_CheckBox);
            this.PT_I2C_Box.Controls.Add(this.SRAM_PROT_CheckBox);
            this.PT_I2C_Box.Controls.Add(this.I2C_PROT_Label);
            this.PT_I2C_Box.Controls.Add(this.I2C_PROT_Combo);
            this.PT_I2C_Box.Location = new System.Drawing.Point(493, 12);
            this.PT_I2C_Box.Name = "PT_I2C_Box";
            this.PT_I2C_Box.Size = new System.Drawing.Size(200, 163);
            this.PT_I2C_Box.TabIndex = 0;
            this.PT_I2C_Box.TabStop = false;
            this.PT_I2C_Box.Text = "PT_I2C";
            // 
            // PT_I2C_Info_PicBox
            // 
            this.PT_I2C_Info_PicBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PT_I2C_Info_PicBox.BackgroundImage")));
            this.PT_I2C_Info_PicBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PT_I2C_Info_PicBox.Location = new System.Drawing.Point(165, 12);
            this.PT_I2C_Info_PicBox.Name = "PT_I2C_Info_PicBox";
            this.PT_I2C_Info_PicBox.Size = new System.Drawing.Size(24, 22);
            this.PT_I2C_Info_PicBox.TabIndex = 0;
            this.PT_I2C_Info_PicBox.TabStop = false;
            this.PT_I2C_Info_PicBox.Click += new System.EventHandler(this.PT_I2C_Info_PicBox_Click);
            // 
            // _2K_PROT_CheckBox
            // 
            this._2K_PROT_CheckBox.Location = new System.Drawing.Point(6, 74);
            this._2K_PROT_CheckBox.Name = "_2K_PROT_CheckBox";
            this._2K_PROT_CheckBox.Size = new System.Drawing.Size(130, 24);
            this._2K_PROT_CheckBox.TabIndex = 0;
            this._2K_PROT_CheckBox.Text = "2K_PROT";
            // 
            // SRAM_PROT_CheckBox
            // 
            this.SRAM_PROT_CheckBox.Location = new System.Drawing.Point(6, 44);
            this.SRAM_PROT_CheckBox.Name = "SRAM_PROT_CheckBox";
            this.SRAM_PROT_CheckBox.Size = new System.Drawing.Size(130, 24);
            this.SRAM_PROT_CheckBox.TabIndex = 0;
            this.SRAM_PROT_CheckBox.Text = "SRAM_PROT";
            // 
            // I2C_PROT_Combo
            // 
            this.I2C_PROT_Combo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.I2C_PROT_Combo.DropDownWidth = 250;
            this.I2C_PROT_Combo.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.I2C_PROT_Combo.FormattingEnabled = true;
            this.I2C_PROT_Combo.Items.AddRange(new object[] {
            "00: Entire memory accesible by I²C",
            "01: Protected area is read only",
            "1X: No access to protected area"});
            this.I2C_PROT_Combo.Location = new System.Drawing.Point(50, 127);
            this.I2C_PROT_Combo.Margin = new System.Windows.Forms.Padding(4);
            this.I2C_PROT_Combo.Name = "I2C_PROT_Combo";
            this.I2C_PROT_Combo.Size = new System.Drawing.Size(121, 23);
            this.I2C_PROT_Combo.TabIndex = 0;
            // 
            // writeAccess_Btn
            // 
            this.writeAccess_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.writeAccess_Btn.Location = new System.Drawing.Point(308, 192);
            this.writeAccess_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.writeAccess_Btn.Name = "writeAccess_Btn";
            this.writeAccess_Btn.Size = new System.Drawing.Size(113, 33);
            this.writeAccess_Btn.TabIndex = 32;
            this.writeAccess_Btn.Text = "Write Access";
            this.writeAccess_Btn.UseVisualStyleBackColor = true;
            this.writeAccess_Btn.Click += new System.EventHandler(this.writeFormValuesToAccessReg);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.Red;
            this.label1.Location = new System.Drawing.Point(12, 232);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(278, 68);
            this.label1.TabIndex = 17;
            this.label1.Text = "The fields PWD and PACK cannot be read \n and always returns 00..00.\n Be aware whe" +
    "n writing, PWD and PACK\n are overwritten.";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // AccessRegPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(702, 311);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.AUTH0_Box);
            this.Controls.Add(this.writeAccess_Btn);
            this.Controls.Add(this.closeAccess_Btn);
            this.Controls.Add(this.readAccess_Btn);
            this.Controls.Add(this.ACCESS_Box);
            this.Controls.Add(this.PWD_Box);
            this.Controls.Add(this.PACK_Box);
            this.Controls.Add(this.PT_I2C_Box);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AccessRegPanel";
            this.Text = "Access Registers";
            this.AUTH0_Box.ResumeLayout(false);
            this.AUTH0_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.AUTH0_Info_PicBox)).EndInit();
            this.ACCESS_Box.ResumeLayout(false);
            this.ACCESS_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ACCESS_Info_PicBox)).EndInit();
            this.PWD_Box.ResumeLayout(false);
            this.PWD_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PWD_Info_PicBox)).EndInit();
            this.PACK_Box.ResumeLayout(false);
            this.PACK_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PACK_Info_PicBox)).EndInit();
            this.PT_I2C_Box.ResumeLayout(false);
            this.PT_I2C_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PT_I2C_Info_PicBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button closeAccess_Btn;
        private System.Windows.Forms.GroupBox ACCESS_Box;
        private System.Windows.Forms.GroupBox AUTH0_Box;
        private System.Windows.Forms.GroupBox PWD_Box;
        private System.Windows.Forms.GroupBox PACK_Box;
        private System.Windows.Forms.GroupBox PT_I2C_Box;
        private System.Windows.Forms.TextBox AUTH0_TextBox;
        private System.Windows.Forms.TextBox PWD_TextBox;
        private System.Windows.Forms.TextBox PACK_TextBox;
        private System.Windows.Forms.TextBox AUTHLIM_TextBox;
        private System.Windows.Forms.Label PWD_Label;
        private System.Windows.Forms.Label AUTH0_Label;
        private System.Windows.Forms.Label AUTHLIM_Label;
        private System.Windows.Forms.Label PACK_Label;
        private System.Windows.Forms.Label I2C_PROT_Label;
        private System.Windows.Forms.PictureBox ACCESS_Info_PicBox;
        private System.Windows.Forms.PictureBox PWD_Info_PicBox;
        private System.Windows.Forms.PictureBox PACK_Info_PicBox;
        private System.Windows.Forms.PictureBox PT_I2C_Info_PicBox;
        private System.Windows.Forms.PictureBox AUTH0_Info_PicBox;
        private System.Windows.Forms.ComboBox I2C_PROT_Combo;
        private System.Windows.Forms.CheckBox NFC_PROT_CheckBox;
        private System.Windows.Forms.CheckBox NFC_DIS_SEC1_CheckBox;
        private System.Windows.Forms.CheckBox _2K_PROT_CheckBox;
        private System.Windows.Forms.CheckBox SRAM_PROT_CheckBox;
        private System.Windows.Forms.Button writeAccess_Btn;
        public System.Windows.Forms.Button readAccess_Btn ;
        private System.Windows.Forms.CheckBox checkPWD;
        private System.Windows.Forms.CheckBox checkPACK;
        private System.Windows.Forms.Label label1;

    }
}