namespace PeekAndPoke
{
    partial class ConfigRegPanel_Noplus
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ConfigRegPanel));
            this.closeConfig_Btn = new System.Windows.Forms.Button();
            this.readConfig_Btn = new System.Windows.Forms.Button();
            this.REG_LOCK_Box = new System.Windows.Forms.GroupBox();
            this.rfLocked_CheckBox = new System.Windows.Forms.CheckBox();
            this.i2cLocked_CheckBox = new System.Windows.Forms.CheckBox();
            this.REG_LOCK_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.SRAM_MIRROR_Box = new System.Windows.Forms.GroupBox();
            this.SRAM_Block_TextBox = new System.Windows.Forms.TextBox();
            this.SRAM_Block_Label = new System.Windows.Forms.Label();
            this.SRAM_MIRROR_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.I2C_CLOCK_STR_Box = new System.Windows.Forms.GroupBox();
            this.I2C_CLOCK_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.I2C_CLOCK_EN_Chcekbox = new System.Windows.Forms.CheckBox();
            this.WDT_Box = new System.Windows.Forms.GroupBox();
            this.watchDog_Label = new System.Windows.Forms.Label();
            this.WDT_LS_TextBox = new System.Windows.Forms.TextBox();
            this.WDT_MS_TextBox = new System.Windows.Forms.TextBox();
            this.WDT_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.LAST_NDEF_BLOCK_Box = new System.Windows.Forms.GroupBox();
            this.Last_Ndef_Msg_textBox = new System.Windows.Forms.TextBox();
            this.Last_Ndef_Msg_Label = new System.Windows.Forms.Label();
            this.LAST_NDEF_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.NC_REG_Box = new System.Windows.Forms.GroupBox();
            this.NC_REG_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.Transfer_DIR_Checkbox = new System.Windows.Forms.CheckBox();
            this.SRAM_MIRROR_CheckBox = new System.Windows.Forms.CheckBox();
            this.FD_ON_Combo = new System.Windows.Forms.ComboBox();
            this.FD_ON_Label = new System.Windows.Forms.Label();
            this.FD_OFF_Combo = new System.Windows.Forms.ComboBox();
            this.FD_OFF_Label = new System.Windows.Forms.Label();
            this.PTHRU_CheckBox = new System.Windows.Forms.CheckBox();
            this.I2C_RST_CheckBox = new System.Windows.Forms.CheckBox();
            this.writeConfig_Btn = new System.Windows.Forms.Button();
            this.REG_LOCK_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.REG_LOCK_Info_PicBox)).BeginInit();
            this.SRAM_MIRROR_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SRAM_MIRROR_Info_PicBox)).BeginInit();
            this.I2C_CLOCK_STR_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.I2C_CLOCK_Info_PicBox)).BeginInit();
            this.WDT_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.WDT_Info_PicBox)).BeginInit();
            this.LAST_NDEF_BLOCK_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.LAST_NDEF_Info_PicBox)).BeginInit();
            this.NC_REG_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NC_REG_Info_PicBox)).BeginInit();
            this.SuspendLayout();
            // 
            // closeConfig_Btn
            // 
            this.closeConfig_Btn.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.closeConfig_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.closeConfig_Btn.Location = new System.Drawing.Point(327, 343);
            this.closeConfig_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.closeConfig_Btn.Name = "closeConfig_Btn";
            this.closeConfig_Btn.Size = new System.Drawing.Size(113, 33);
            this.closeConfig_Btn.TabIndex = 31;
            this.closeConfig_Btn.Text = "Close";
            this.closeConfig_Btn.UseVisualStyleBackColor = true;
            // 
            // readConfig_Btn
            // 
            this.readConfig_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.readConfig_Btn.Location = new System.Drawing.Point(327, 306);
            this.readConfig_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.readConfig_Btn.Name = "readConfig_Btn";
            this.readConfig_Btn.Size = new System.Drawing.Size(113, 33);
            this.readConfig_Btn.TabIndex = 30;
            this.readConfig_Btn.Text = "Read Config";
            this.readConfig_Btn.UseVisualStyleBackColor = true;
            this.readConfig_Btn.Click += new System.EventHandler(this.readConfigRegAndShow);
            // 
            // REG_LOCK_Box
            // 
            this.REG_LOCK_Box.Controls.Add(this.rfLocked_CheckBox);
            this.REG_LOCK_Box.Controls.Add(this.i2cLocked_CheckBox);
            this.REG_LOCK_Box.Controls.Add(this.REG_LOCK_Info_PicBox);
            this.REG_LOCK_Box.Location = new System.Drawing.Point(501, 132);
            this.REG_LOCK_Box.Margin = new System.Windows.Forms.Padding(4);
            this.REG_LOCK_Box.Name = "REG_LOCK_Box";
            this.REG_LOCK_Box.Padding = new System.Windows.Forms.Padding(4);
            this.REG_LOCK_Box.Size = new System.Drawing.Size(239, 249);
            this.REG_LOCK_Box.TabIndex = 29;
            this.REG_LOCK_Box.TabStop = false;
            this.REG_LOCK_Box.Text = "REG_LOCK : 0x";
            // 
            // rfLocked_CheckBox
            // 
            this.rfLocked_CheckBox.AutoSize = true;
            this.rfLocked_CheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rfLocked_CheckBox.Location = new System.Drawing.Point(8, 68);
            this.rfLocked_CheckBox.Margin = new System.Windows.Forms.Padding(4);
            this.rfLocked_CheckBox.Name = "rfLocked_CheckBox";
            this.rfLocked_CheckBox.Size = new System.Drawing.Size(108, 20);
            this.rfLocked_CheckBox.TabIndex = 15;
            this.rfLocked_CheckBox.Text = "RF_LOCKED";
            this.rfLocked_CheckBox.UseVisualStyleBackColor = true;
            // 
            // i2cLocked_CheckBox
            // 
            this.i2cLocked_CheckBox.AutoSize = true;
            this.i2cLocked_CheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.i2cLocked_CheckBox.Location = new System.Drawing.Point(8, 46);
            this.i2cLocked_CheckBox.Margin = new System.Windows.Forms.Padding(4);
            this.i2cLocked_CheckBox.Name = "i2cLocked_CheckBox";
            this.i2cLocked_CheckBox.Size = new System.Drawing.Size(109, 20);
            this.i2cLocked_CheckBox.TabIndex = 14;
            this.i2cLocked_CheckBox.Text = "I2C_LOCKED";
            this.i2cLocked_CheckBox.UseVisualStyleBackColor = true;
            // 
            // REG_LOCK_Info_PicBox
            // 
            this.REG_LOCK_Info_PicBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("REG_LOCK_Info_PicBox.BackgroundImage")));
            this.REG_LOCK_Info_PicBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.REG_LOCK_Info_PicBox.Location = new System.Drawing.Point(204, 17);
            this.REG_LOCK_Info_PicBox.Margin = new System.Windows.Forms.Padding(4);
            this.REG_LOCK_Info_PicBox.Name = "REG_LOCK_Info_PicBox";
            this.REG_LOCK_Info_PicBox.Size = new System.Drawing.Size(24, 22);
            this.REG_LOCK_Info_PicBox.TabIndex = 13;
            this.REG_LOCK_Info_PicBox.TabStop = false;
            this.REG_LOCK_Info_PicBox.Click += new System.EventHandler(this.show_NS_REG_Info);
            // 
            // SRAM_MIRROR_Box
            // 
            this.SRAM_MIRROR_Box.Controls.Add(this.SRAM_Block_TextBox);
            this.SRAM_MIRROR_Box.Controls.Add(this.SRAM_Block_Label);
            this.SRAM_MIRROR_Box.Controls.Add(this.SRAM_MIRROR_Info_PicBox);
            this.SRAM_MIRROR_Box.Location = new System.Drawing.Point(255, 132);
            this.SRAM_MIRROR_Box.Margin = new System.Windows.Forms.Padding(4);
            this.SRAM_MIRROR_Box.Name = "SRAM_MIRROR_Box";
            this.SRAM_MIRROR_Box.Padding = new System.Windows.Forms.Padding(4);
            this.SRAM_MIRROR_Box.Size = new System.Drawing.Size(239, 121);
            this.SRAM_MIRROR_Box.TabIndex = 25;
            this.SRAM_MIRROR_Box.TabStop = false;
            this.SRAM_MIRROR_Box.Text = "SRAM_MIRROR_BLOCK : 0x";
            // 
            // SRAM_Block_TextBox
            // 
            this.SRAM_Block_TextBox.Location = new System.Drawing.Point(157, 50);
            this.SRAM_Block_TextBox.Margin = new System.Windows.Forms.Padding(4);
            this.SRAM_Block_TextBox.Name = "SRAM_Block_TextBox";
            this.SRAM_Block_TextBox.Size = new System.Drawing.Size(27, 22);
            this.SRAM_Block_TextBox.TabIndex = 13;
            this.SRAM_Block_TextBox.Text = "F8";
            // 
            // SRAM_Block_Label
            // 
            this.SRAM_Block_Label.AutoSize = true;
            this.SRAM_Block_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SRAM_Block_Label.Location = new System.Drawing.Point(32, 54);
            this.SRAM_Block_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.SRAM_Block_Label.Name = "SRAM_Block_Label";
            this.SRAM_Block_Label.Size = new System.Drawing.Size(116, 16);
            this.SRAM_Block_Label.TabIndex = 13;
            this.SRAM_Block_Label.Text = "I²C block address";
            // 
            // SRAM_MIRROR_Info_PicBox
            // 
            this.SRAM_MIRROR_Info_PicBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("SRAM_MIRROR_Info_PicBox.BackgroundImage")));
            this.SRAM_MIRROR_Info_PicBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.SRAM_MIRROR_Info_PicBox.Location = new System.Drawing.Point(204, 17);
            this.SRAM_MIRROR_Info_PicBox.Margin = new System.Windows.Forms.Padding(4);
            this.SRAM_MIRROR_Info_PicBox.Name = "SRAM_MIRROR_Info_PicBox";
            this.SRAM_MIRROR_Info_PicBox.Size = new System.Drawing.Size(24, 22);
            this.SRAM_MIRROR_Info_PicBox.TabIndex = 11;
            this.SRAM_MIRROR_Info_PicBox.TabStop = false;
            this.SRAM_MIRROR_Info_PicBox.Click += new System.EventHandler(this.show_SRAM_Block_Info);
            // 
            // I2C_CLOCK_STR_Box
            // 
            this.I2C_CLOCK_STR_Box.Controls.Add(this.I2C_CLOCK_Info_PicBox);
            this.I2C_CLOCK_STR_Box.Controls.Add(this.I2C_CLOCK_EN_Chcekbox);
            this.I2C_CLOCK_STR_Box.Location = new System.Drawing.Point(8, 260);
            this.I2C_CLOCK_STR_Box.Margin = new System.Windows.Forms.Padding(4);
            this.I2C_CLOCK_STR_Box.Name = "I2C_CLOCK_STR_Box";
            this.I2C_CLOCK_STR_Box.Padding = new System.Windows.Forms.Padding(4);
            this.I2C_CLOCK_STR_Box.Size = new System.Drawing.Size(239, 121);
            this.I2C_CLOCK_STR_Box.TabIndex = 26;
            this.I2C_CLOCK_STR_Box.TabStop = false;
            this.I2C_CLOCK_STR_Box.Text = "I2C_CLOCK_STR : 0x";
            // 
            // I2C_CLOCK_Info_PicBox
            // 
            this.I2C_CLOCK_Info_PicBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("I2C_CLOCK_Info_PicBox.BackgroundImage")));
            this.I2C_CLOCK_Info_PicBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.I2C_CLOCK_Info_PicBox.Location = new System.Drawing.Point(204, 17);
            this.I2C_CLOCK_Info_PicBox.Margin = new System.Windows.Forms.Padding(4);
            this.I2C_CLOCK_Info_PicBox.Name = "I2C_CLOCK_Info_PicBox";
            this.I2C_CLOCK_Info_PicBox.Size = new System.Drawing.Size(24, 22);
            this.I2C_CLOCK_Info_PicBox.TabIndex = 11;
            this.I2C_CLOCK_Info_PicBox.TabStop = false;
            this.I2C_CLOCK_Info_PicBox.Click += new System.EventHandler(this.show_I2C_Clock_STR_Info);
            // 
            // I2C_CLOCK_EN_Chcekbox
            // 
            this.I2C_CLOCK_EN_Chcekbox.AutoSize = true;
            this.I2C_CLOCK_EN_Chcekbox.Checked = true;
            this.I2C_CLOCK_EN_Chcekbox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.I2C_CLOCK_EN_Chcekbox.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.I2C_CLOCK_EN_Chcekbox.Location = new System.Drawing.Point(21, 49);
            this.I2C_CLOCK_EN_Chcekbox.Margin = new System.Windows.Forms.Padding(4);
            this.I2C_CLOCK_EN_Chcekbox.Name = "I2C_CLOCK_EN_Chcekbox";
            this.I2C_CLOCK_EN_Chcekbox.Size = new System.Drawing.Size(191, 20);
            this.I2C_CLOCK_EN_Chcekbox.TabIndex = 10;
            this.I2C_CLOCK_EN_Chcekbox.Text = "I2C_CLOCK_STR: Enabled";
            this.I2C_CLOCK_EN_Chcekbox.UseVisualStyleBackColor = true;
            this.I2C_CLOCK_EN_Chcekbox.CheckedChanged += new System.EventHandler(this.show_I2C_CLOCK_STR_Value);
            // 
            // WDT_Box
            // 
            this.WDT_Box.Controls.Add(this.watchDog_Label);
            this.WDT_Box.Controls.Add(this.WDT_LS_TextBox);
            this.WDT_Box.Controls.Add(this.WDT_MS_TextBox);
            this.WDT_Box.Controls.Add(this.WDT_Info_PicBox);
            this.WDT_Box.Location = new System.Drawing.Point(501, 4);
            this.WDT_Box.Margin = new System.Windows.Forms.Padding(4);
            this.WDT_Box.Name = "WDT_Box";
            this.WDT_Box.Padding = new System.Windows.Forms.Padding(4);
            this.WDT_Box.Size = new System.Drawing.Size(239, 121);
            this.WDT_Box.TabIndex = 27;
            this.WDT_Box.TabStop = false;
            this.WDT_Box.Text = "WDT : 0x";
            // 
            // watchDog_Label
            // 
            this.watchDog_Label.AutoSize = true;
            this.watchDog_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.watchDog_Label.Location = new System.Drawing.Point(20, 58);
            this.watchDog_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.watchDog_Label.Name = "watchDog_Label";
            this.watchDog_Label.Size = new System.Drawing.Size(185, 16);
            this.watchDog_Label.TabIndex = 16;
            this.watchDog_Label.Text = "Watchdog time-out: 20.000 ms";
            // 
            // WDT_LS_TextBox
            // 
            this.WDT_LS_TextBox.Location = new System.Drawing.Point(120, 30);
            this.WDT_LS_TextBox.Margin = new System.Windows.Forms.Padding(4);
            this.WDT_LS_TextBox.Name = "WDT_LS_TextBox";
            this.WDT_LS_TextBox.Size = new System.Drawing.Size(27, 22);
            this.WDT_LS_TextBox.TabIndex = 15;
            this.WDT_LS_TextBox.Text = "48";
            this.WDT_LS_TextBox.TextChanged += new System.EventHandler(this.show_WDT_LS_Value);
            // 
            // WDT_MS_TextBox
            // 
            this.WDT_MS_TextBox.Location = new System.Drawing.Point(89, 30);
            this.WDT_MS_TextBox.Margin = new System.Windows.Forms.Padding(4);
            this.WDT_MS_TextBox.Name = "WDT_MS_TextBox";
            this.WDT_MS_TextBox.Size = new System.Drawing.Size(28, 22);
            this.WDT_MS_TextBox.TabIndex = 14;
            this.WDT_MS_TextBox.Text = "08";
            this.WDT_MS_TextBox.TextChanged += new System.EventHandler(this.show_WDT_MS_Value);
            // 
            // WDT_Info_PicBox
            // 
            this.WDT_Info_PicBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("WDT_Info_PicBox.BackgroundImage")));
            this.WDT_Info_PicBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.WDT_Info_PicBox.Location = new System.Drawing.Point(204, 17);
            this.WDT_Info_PicBox.Margin = new System.Windows.Forms.Padding(4);
            this.WDT_Info_PicBox.Name = "WDT_Info_PicBox";
            this.WDT_Info_PicBox.Size = new System.Drawing.Size(24, 22);
            this.WDT_Info_PicBox.TabIndex = 11;
            this.WDT_Info_PicBox.TabStop = false;
            this.WDT_Info_PicBox.Click += new System.EventHandler(this.show_WDT_Info);
            // 
            // LAST_NDEF_BLOCK_Box
            // 
            this.LAST_NDEF_BLOCK_Box.Controls.Add(this.Last_Ndef_Msg_textBox);
            this.LAST_NDEF_BLOCK_Box.Controls.Add(this.Last_Ndef_Msg_Label);
            this.LAST_NDEF_BLOCK_Box.Controls.Add(this.LAST_NDEF_Info_PicBox);
            this.LAST_NDEF_BLOCK_Box.Location = new System.Drawing.Point(255, 4);
            this.LAST_NDEF_BLOCK_Box.Margin = new System.Windows.Forms.Padding(4);
            this.LAST_NDEF_BLOCK_Box.Name = "LAST_NDEF_BLOCK_Box";
            this.LAST_NDEF_BLOCK_Box.Padding = new System.Windows.Forms.Padding(4);
            this.LAST_NDEF_BLOCK_Box.Size = new System.Drawing.Size(239, 121);
            this.LAST_NDEF_BLOCK_Box.TabIndex = 28;
            this.LAST_NDEF_BLOCK_Box.TabStop = false;
            this.LAST_NDEF_BLOCK_Box.Text = "LAST_NDEF_BLOCK : 0x";
            // 
            // Last_Ndef_Msg_textBox
            // 
            this.Last_Ndef_Msg_textBox.Location = new System.Drawing.Point(199, 50);
            this.Last_Ndef_Msg_textBox.Margin = new System.Windows.Forms.Padding(4);
            this.Last_Ndef_Msg_textBox.Name = "Last_Ndef_Msg_textBox";
            this.Last_Ndef_Msg_textBox.Size = new System.Drawing.Size(27, 22);
            this.Last_Ndef_Msg_textBox.TabIndex = 3;
            this.Last_Ndef_Msg_textBox.Text = "00";
            // 
            // Last_Ndef_Msg_Label
            // 
            this.Last_Ndef_Msg_Label.AutoSize = true;
            this.Last_Ndef_Msg_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Last_Ndef_Msg_Label.Location = new System.Drawing.Point(8, 54);
            this.Last_Ndef_Msg_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Last_Ndef_Msg_Label.Name = "Last_Ndef_Msg_Label";
            this.Last_Ndef_Msg_Label.Size = new System.Drawing.Size(179, 16);
            this.Last_Ndef_Msg_Label.TabIndex = 11;
            this.Last_Ndef_Msg_Label.Text = "Last BLOCK NDEF message";
            // 
            // LAST_NDEF_Info_PicBox
            // 
            this.LAST_NDEF_Info_PicBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("LAST_NDEF_Info_PicBox.BackgroundImage")));
            this.LAST_NDEF_Info_PicBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.LAST_NDEF_Info_PicBox.Location = new System.Drawing.Point(204, 17);
            this.LAST_NDEF_Info_PicBox.Margin = new System.Windows.Forms.Padding(4);
            this.LAST_NDEF_Info_PicBox.Name = "LAST_NDEF_Info_PicBox";
            this.LAST_NDEF_Info_PicBox.Size = new System.Drawing.Size(24, 22);
            this.LAST_NDEF_Info_PicBox.TabIndex = 11;
            this.LAST_NDEF_Info_PicBox.TabStop = false;
            this.LAST_NDEF_Info_PicBox.Click += new System.EventHandler(this.show_LAST_NDEF_Block_Info);
            // 
            // NC_REG_Box
            // 
            this.NC_REG_Box.Controls.Add(this.NC_REG_Info_PicBox);
            this.NC_REG_Box.Controls.Add(this.Transfer_DIR_Checkbox);
            this.NC_REG_Box.Controls.Add(this.SRAM_MIRROR_CheckBox);
            this.NC_REG_Box.Controls.Add(this.FD_ON_Combo);
            this.NC_REG_Box.Controls.Add(this.FD_ON_Label);
            this.NC_REG_Box.Controls.Add(this.FD_OFF_Combo);
            this.NC_REG_Box.Controls.Add(this.FD_OFF_Label);
            this.NC_REG_Box.Controls.Add(this.PTHRU_CheckBox);
            this.NC_REG_Box.Controls.Add(this.I2C_RST_CheckBox);
            this.NC_REG_Box.Location = new System.Drawing.Point(8, 4);
            this.NC_REG_Box.Margin = new System.Windows.Forms.Padding(4);
            this.NC_REG_Box.Name = "NC_REG_Box";
            this.NC_REG_Box.Padding = new System.Windows.Forms.Padding(4);
            this.NC_REG_Box.Size = new System.Drawing.Size(239, 249);
            this.NC_REG_Box.TabIndex = 24;
            this.NC_REG_Box.TabStop = false;
            this.NC_REG_Box.Text = "NC_REG : 0x";
            // 
            // NC_REG_Info_PicBox
            // 
            this.NC_REG_Info_PicBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("NC_REG_Info_PicBox.BackgroundImage")));
            this.NC_REG_Info_PicBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.NC_REG_Info_PicBox.Location = new System.Drawing.Point(204, 17);
            this.NC_REG_Info_PicBox.Margin = new System.Windows.Forms.Padding(4);
            this.NC_REG_Info_PicBox.Name = "NC_REG_Info_PicBox";
            this.NC_REG_Info_PicBox.Size = new System.Drawing.Size(24, 22);
            this.NC_REG_Info_PicBox.TabIndex = 10;
            this.NC_REG_Info_PicBox.TabStop = false;
            this.NC_REG_Info_PicBox.Click += new System.EventHandler(this.show_NC_REG_Info);
            // 
            // Transfer_DIR_Checkbox
            // 
            this.Transfer_DIR_Checkbox.AutoSize = true;
            this.Transfer_DIR_Checkbox.Checked = true;
            this.Transfer_DIR_Checkbox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.Transfer_DIR_Checkbox.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Transfer_DIR_Checkbox.Location = new System.Drawing.Point(21, 185);
            this.Transfer_DIR_Checkbox.Margin = new System.Windows.Forms.Padding(4);
            this.Transfer_DIR_Checkbox.Name = "Transfer_DIR_Checkbox";
            this.Transfer_DIR_Checkbox.Size = new System.Drawing.Size(134, 20);
            this.Transfer_DIR_Checkbox.TabIndex = 7;
            this.Transfer_DIR_Checkbox.Text = "TRANSFER_DIR";
            this.Transfer_DIR_Checkbox.UseVisualStyleBackColor = true;
            // 
            // SRAM_MIRROR_CheckBox
            // 
            this.SRAM_MIRROR_CheckBox.AutoSize = true;
            this.SRAM_MIRROR_CheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SRAM_MIRROR_CheckBox.Location = new System.Drawing.Point(21, 162);
            this.SRAM_MIRROR_CheckBox.Margin = new System.Windows.Forms.Padding(4);
            this.SRAM_MIRROR_CheckBox.Name = "SRAM_MIRROR_CheckBox";
            this.SRAM_MIRROR_CheckBox.Size = new System.Drawing.Size(190, 20);
            this.SRAM_MIRROR_CheckBox.TabIndex = 6;
            this.SRAM_MIRROR_CheckBox.Text = "SRAM_MIRROR_ON_OFF";
            this.SRAM_MIRROR_CheckBox.UseVisualStyleBackColor = true;
            // 
            // FD_ON_Combo
            // 
            this.FD_ON_Combo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FD_ON_Combo.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FD_ON_Combo.FormattingEnabled = true;
            this.FD_ON_Combo.Items.AddRange(new object[] {
            "00: Field presence",
            "01: Valid start-of-frame",
            "10: Tag selection",
            "11: Data ready"});
            this.FD_ON_Combo.Location = new System.Drawing.Point(33, 133);
            this.FD_ON_Combo.Margin = new System.Windows.Forms.Padding(4);
            this.FD_ON_Combo.Name = "FD_ON_Combo";
            this.FD_ON_Combo.Size = new System.Drawing.Size(160, 23);
            this.FD_ON_Combo.TabIndex = 5;
            // 
            // FD_ON_Label
            // 
            this.FD_ON_Label.AutoSize = true;
            this.FD_ON_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FD_ON_Label.Location = new System.Drawing.Point(17, 113);
            this.FD_ON_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.FD_ON_Label.Name = "FD_ON_Label";
            this.FD_ON_Label.Size = new System.Drawing.Size(53, 16);
            this.FD_ON_Label.TabIndex = 4;
            this.FD_ON_Label.Text = "FD_ON";
            // 
            // FD_OFF_Combo
            // 
            this.FD_OFF_Combo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FD_OFF_Combo.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FD_OFF_Combo.FormattingEnabled = true;
            this.FD_OFF_Combo.Items.AddRange(new object[] {
            "00: Field switched off",
            "01: Field off or tag halted",
            "10: Field off or NDEF read",
            "11: Field off or if last I²C data written"});
            this.FD_OFF_Combo.Location = new System.Drawing.Point(33, 86);
            this.FD_OFF_Combo.Margin = new System.Windows.Forms.Padding(4);
            this.FD_OFF_Combo.Name = "FD_OFF_Combo";
            this.FD_OFF_Combo.Size = new System.Drawing.Size(160, 23);
            this.FD_OFF_Combo.TabIndex = 3;
            // 
            // FD_OFF_Label
            // 
            this.FD_OFF_Label.AutoSize = true;
            this.FD_OFF_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FD_OFF_Label.Location = new System.Drawing.Point(17, 66);
            this.FD_OFF_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.FD_OFF_Label.Name = "FD_OFF_Label";
            this.FD_OFF_Label.Size = new System.Drawing.Size(59, 16);
            this.FD_OFF_Label.TabIndex = 2;
            this.FD_OFF_Label.Text = "FD_OFF";
            // 
            // PTHRU_CheckBox
            // 
            this.PTHRU_CheckBox.AutoSize = true;
            this.PTHRU_CheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PTHRU_CheckBox.Location = new System.Drawing.Point(21, 46);
            this.PTHRU_CheckBox.Margin = new System.Windows.Forms.Padding(4);
            this.PTHRU_CheckBox.Name = "PTHRU_CheckBox";
            this.PTHRU_CheckBox.Size = new System.Drawing.Size(138, 20);
            this.PTHRU_CheckBox.TabIndex = 1;
            this.PTHRU_CheckBox.Text = "PTHRU_ON_OFF";
            this.PTHRU_CheckBox.UseVisualStyleBackColor = true;
            // 
            // I2C_RST_CheckBox
            // 
            this.I2C_RST_CheckBox.AutoSize = true;
            this.I2C_RST_CheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.I2C_RST_CheckBox.Location = new System.Drawing.Point(21, 23);
            this.I2C_RST_CheckBox.Margin = new System.Windows.Forms.Padding(4);
            this.I2C_RST_CheckBox.Name = "I2C_RST_CheckBox";
            this.I2C_RST_CheckBox.Size = new System.Drawing.Size(144, 20);
            this.I2C_RST_CheckBox.TabIndex = 0;
            this.I2C_RST_CheckBox.Text = "I2C_RST_ON_OFF";
            this.I2C_RST_CheckBox.UseVisualStyleBackColor = true;
            // 
            // writeConfig_Btn
            // 
            this.writeConfig_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.writeConfig_Btn.Location = new System.Drawing.Point(327, 271);
            this.writeConfig_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.writeConfig_Btn.Name = "writeConfig_Btn";
            this.writeConfig_Btn.Size = new System.Drawing.Size(113, 33);
            this.writeConfig_Btn.TabIndex = 32;
            this.writeConfig_Btn.Text = "Write Config";
            this.writeConfig_Btn.UseVisualStyleBackColor = true;
            this.writeConfig_Btn.Click += new System.EventHandler(this.writeFormValuesToConfigReg);
            // 
            // ConfigRegPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(747, 384);
            this.Controls.Add(this.writeConfig_Btn);
            this.Controls.Add(this.closeConfig_Btn);
            this.Controls.Add(this.readConfig_Btn);
            this.Controls.Add(this.REG_LOCK_Box);
            this.Controls.Add(this.SRAM_MIRROR_Box);
            this.Controls.Add(this.I2C_CLOCK_STR_Box);
            this.Controls.Add(this.WDT_Box);
            this.Controls.Add(this.LAST_NDEF_BLOCK_Box);
            this.Controls.Add(this.NC_REG_Box);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ConfigRegPanel";
            this.Text = "Configuration Registers";
            this.REG_LOCK_Box.ResumeLayout(false);
            this.REG_LOCK_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.REG_LOCK_Info_PicBox)).EndInit();
            this.SRAM_MIRROR_Box.ResumeLayout(false);
            this.SRAM_MIRROR_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SRAM_MIRROR_Info_PicBox)).EndInit();
            this.I2C_CLOCK_STR_Box.ResumeLayout(false);
            this.I2C_CLOCK_STR_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.I2C_CLOCK_Info_PicBox)).EndInit();
            this.WDT_Box.ResumeLayout(false);
            this.WDT_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.WDT_Info_PicBox)).EndInit();
            this.LAST_NDEF_BLOCK_Box.ResumeLayout(false);
            this.LAST_NDEF_BLOCK_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.LAST_NDEF_Info_PicBox)).EndInit();
            this.NC_REG_Box.ResumeLayout(false);
            this.NC_REG_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NC_REG_Info_PicBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button closeConfig_Btn;
        private System.Windows.Forms.GroupBox REG_LOCK_Box;
        private System.Windows.Forms.CheckBox rfLocked_CheckBox;
        private System.Windows.Forms.CheckBox i2cLocked_CheckBox;
        private System.Windows.Forms.PictureBox REG_LOCK_Info_PicBox;
        private System.Windows.Forms.GroupBox SRAM_MIRROR_Box;
        private System.Windows.Forms.TextBox SRAM_Block_TextBox;
        private System.Windows.Forms.Label SRAM_Block_Label;
        private System.Windows.Forms.PictureBox SRAM_MIRROR_Info_PicBox;
        private System.Windows.Forms.GroupBox I2C_CLOCK_STR_Box;
        private System.Windows.Forms.PictureBox I2C_CLOCK_Info_PicBox;
        private System.Windows.Forms.CheckBox I2C_CLOCK_EN_Chcekbox;
        private System.Windows.Forms.GroupBox WDT_Box;
        private System.Windows.Forms.Label watchDog_Label;
        private System.Windows.Forms.TextBox WDT_LS_TextBox;
        private System.Windows.Forms.TextBox WDT_MS_TextBox;
        private System.Windows.Forms.PictureBox WDT_Info_PicBox;
        private System.Windows.Forms.GroupBox LAST_NDEF_BLOCK_Box;
        private System.Windows.Forms.TextBox Last_Ndef_Msg_textBox;
        private System.Windows.Forms.Label Last_Ndef_Msg_Label;
        private System.Windows.Forms.PictureBox LAST_NDEF_Info_PicBox;
        private System.Windows.Forms.GroupBox NC_REG_Box;
        private System.Windows.Forms.PictureBox NC_REG_Info_PicBox;
        private System.Windows.Forms.CheckBox Transfer_DIR_Checkbox;
        private System.Windows.Forms.CheckBox SRAM_MIRROR_CheckBox;
        private System.Windows.Forms.ComboBox FD_ON_Combo;
        private System.Windows.Forms.Label FD_ON_Label;
        private System.Windows.Forms.ComboBox FD_OFF_Combo;
        private System.Windows.Forms.Label FD_OFF_Label;
        private System.Windows.Forms.CheckBox PTHRU_CheckBox;
        private System.Windows.Forms.CheckBox I2C_RST_CheckBox;
        private System.Windows.Forms.Button writeConfig_Btn;
        public System.Windows.Forms.Button readConfig_Btn;

    }
}