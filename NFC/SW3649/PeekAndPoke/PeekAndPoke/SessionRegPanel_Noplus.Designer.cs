namespace PeekAndPoke
{
    partial class SessionRegPanel_Noplus
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
            System.Windows.Forms.Label SRAM_Addr_Label;
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SessionRegPanel));
            this.NC_REG_Box = new System.Windows.Forms.GroupBox();
            this.NC_REG_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.WriteNC_REG_Btn = new System.Windows.Forms.Button();
            this.ReadNC_REG_Btn = new System.Windows.Forms.Button();
            this.Transfer_DIR_Checkbox = new System.Windows.Forms.CheckBox();
            this.SRAM_MIRROR_Checkbox = new System.Windows.Forms.CheckBox();
            this.FD_ON_Combo = new System.Windows.Forms.ComboBox();
            this.FD_ON_Label = new System.Windows.Forms.Label();
            this.FD_OFF_Combo = new System.Windows.Forms.ComboBox();
            this.FD_OFF_Label = new System.Windows.Forms.Label();
            this.PTHRU_CheckBox = new System.Windows.Forms.CheckBox();
            this.I2C_RST_CheckBox = new System.Windows.Forms.CheckBox();
            this.LAST_NDEF_Box = new System.Windows.Forms.GroupBox();
            this.WriteNdef_Btn = new System.Windows.Forms.Button();
            this.ReadNdef_Btn = new System.Windows.Forms.Button();
            this.LstNdefBlock_TextBox = new System.Windows.Forms.TextBox();
            this.LstNdefBlock_Label = new System.Windows.Forms.Label();
            this.LAST_NDEF_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.WDT_Box = new System.Windows.Forms.GroupBox();
            this.WriteWDT_Btn = new System.Windows.Forms.Button();
            this.ReadWDT_Btn = new System.Windows.Forms.Button();
            this.WatchDog_Label = new System.Windows.Forms.Label();
            this.WDT_LS_TextBox = new System.Windows.Forms.TextBox();
            this.WDT_MS_TextBox = new System.Windows.Forms.TextBox();
            this.WDT_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.I2C_CLOCK_Box = new System.Windows.Forms.GroupBox();
            this.I2C_CLOCK_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.ReadI2C_STR_Btn = new System.Windows.Forms.Button();
            this.I2C_Clock_EN_ChckB = new System.Windows.Forms.CheckBox();
            this.SRAM_MIRROR_Box = new System.Windows.Forms.GroupBox();
            this.WriteSM_Reg_Btn = new System.Windows.Forms.Button();
            this.ReadSM_Reg_Btn = new System.Windows.Forms.Button();
            this.SRAM_Addr_TextBox = new System.Windows.Forms.TextBox();
            this.SRAM_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.NS_REG_Box = new System.Windows.Forms.GroupBox();
            this.WriteNS_REG_Btn = new System.Windows.Forms.Button();
            this.ReadNS_REG_Btn = new System.Windows.Forms.Button();
            this.RF_F_Present_ChB = new System.Windows.Forms.CheckBox();
            this.EEPROM_BSY_ChB = new System.Windows.Forms.CheckBox();
            this.EEPROM_ERR_ChB = new System.Windows.Forms.CheckBox();
            this.SRAM_RF_RDY_ChB = new System.Windows.Forms.CheckBox();
            this.SRAM_I2C_RDY_ChB = new System.Windows.Forms.CheckBox();
            this.RF_LOCKED_ChB = new System.Windows.Forms.CheckBox();
            this.I2C_LOCKED_ChB = new System.Windows.Forms.CheckBox();
            this.NS_REG_Info_PicBox = new System.Windows.Forms.PictureBox();
            this.NDEF_READ_ChBox = new System.Windows.Forms.CheckBox();
            this.ReadAll_Btn = new System.Windows.Forms.Button();
            this.button13 = new System.Windows.Forms.Button();
            SRAM_Addr_Label = new System.Windows.Forms.Label();
            this.NC_REG_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NC_REG_Info_PicBox)).BeginInit();
            this.LAST_NDEF_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.LAST_NDEF_Info_PicBox)).BeginInit();
            this.WDT_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.WDT_Info_PicBox)).BeginInit();
            this.I2C_CLOCK_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.I2C_CLOCK_Info_PicBox)).BeginInit();
            this.SRAM_MIRROR_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SRAM_Info_PicBox)).BeginInit();
            this.NS_REG_Box.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NS_REG_Info_PicBox)).BeginInit();
            this.SuspendLayout();
            // 
            // SRAM_Addr_Label
            // 
            SRAM_Addr_Label.AutoSize = true;
            SRAM_Addr_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            SRAM_Addr_Label.Location = new System.Drawing.Point(32, 54);
            SRAM_Addr_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            SRAM_Addr_Label.Name = "SRAM_Addr_Label";
            SRAM_Addr_Label.Size = new System.Drawing.Size(116, 16);
            SRAM_Addr_Label.TabIndex = 13;
            SRAM_Addr_Label.Text = "I²C block address";
            // 
            // NC_REG_Box
            // 
            this.NC_REG_Box.Controls.Add(this.NC_REG_Info_PicBox);
            this.NC_REG_Box.Controls.Add(this.WriteNC_REG_Btn);
            this.NC_REG_Box.Controls.Add(this.ReadNC_REG_Btn);
            this.NC_REG_Box.Controls.Add(this.Transfer_DIR_Checkbox);
            this.NC_REG_Box.Controls.Add(this.SRAM_MIRROR_Checkbox);
            this.NC_REG_Box.Controls.Add(this.FD_ON_Combo);
            this.NC_REG_Box.Controls.Add(this.FD_ON_Label);
            this.NC_REG_Box.Controls.Add(this.FD_OFF_Combo);
            this.NC_REG_Box.Controls.Add(this.FD_OFF_Label);
            this.NC_REG_Box.Controls.Add(this.PTHRU_CheckBox);
            this.NC_REG_Box.Controls.Add(this.I2C_RST_CheckBox);
            this.NC_REG_Box.Location = new System.Drawing.Point(7, 4);
            this.NC_REG_Box.Margin = new System.Windows.Forms.Padding(4);
            this.NC_REG_Box.Name = "NC_REG_Box";
            this.NC_REG_Box.Padding = new System.Windows.Forms.Padding(4);
            this.NC_REG_Box.Size = new System.Drawing.Size(239, 249);
            this.NC_REG_Box.TabIndex = 0;
            this.NC_REG_Box.TabStop = false;
            this.NC_REG_Box.Text = "NC_REG : 0xFE:0";
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
            this.NC_REG_Info_PicBox.Click += new System.EventHandler(this.showNC_REG_Info);
            // 
            // WriteNC_REG_Btn
            // 
            this.WriteNC_REG_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.WriteNC_REG_Btn.Location = new System.Drawing.Point(119, 208);
            this.WriteNC_REG_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.WriteNC_REG_Btn.Name = "WriteNC_REG_Btn";
            this.WriteNC_REG_Btn.Size = new System.Drawing.Size(113, 33);
            this.WriteNC_REG_Btn.TabIndex = 9;
            this.WriteNC_REG_Btn.Text = "Write NC_REG";
            this.WriteNC_REG_Btn.UseVisualStyleBackColor = true;
            this.WriteNC_REG_Btn.Click += new System.EventHandler(this.write_NC_REF);
            // 
            // ReadNC_REG_Btn
            // 
            this.ReadNC_REG_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ReadNC_REG_Btn.Location = new System.Drawing.Point(4, 208);
            this.ReadNC_REG_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.ReadNC_REG_Btn.Name = "ReadNC_REG_Btn";
            this.ReadNC_REG_Btn.Size = new System.Drawing.Size(113, 33);
            this.ReadNC_REG_Btn.TabIndex = 8;
            this.ReadNC_REG_Btn.Text = "Read NC_REG";
            this.ReadNC_REG_Btn.UseVisualStyleBackColor = true;
            this.ReadNC_REG_Btn.Click += new System.EventHandler(this.updateRead_NC_REG);
            // 
            // Transfer_DIR_Checkbox
            // 
            this.Transfer_DIR_Checkbox.AutoSize = true;
            this.Transfer_DIR_Checkbox.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Transfer_DIR_Checkbox.Location = new System.Drawing.Point(21, 185);
            this.Transfer_DIR_Checkbox.Margin = new System.Windows.Forms.Padding(4);
            this.Transfer_DIR_Checkbox.Name = "Transfer_DIR_Checkbox";
            this.Transfer_DIR_Checkbox.Size = new System.Drawing.Size(134, 20);
            this.Transfer_DIR_Checkbox.TabIndex = 7;
            this.Transfer_DIR_Checkbox.Text = "TRANSFER_DIR";
            this.Transfer_DIR_Checkbox.UseVisualStyleBackColor = true;
            // 
            // SRAM_MIRROR_Checkbox
            // 
            this.SRAM_MIRROR_Checkbox.AutoSize = true;
            this.SRAM_MIRROR_Checkbox.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SRAM_MIRROR_Checkbox.Location = new System.Drawing.Point(21, 162);
            this.SRAM_MIRROR_Checkbox.Margin = new System.Windows.Forms.Padding(4);
            this.SRAM_MIRROR_Checkbox.Name = "SRAM_MIRROR_Checkbox";
            this.SRAM_MIRROR_Checkbox.Size = new System.Drawing.Size(190, 20);
            this.SRAM_MIRROR_Checkbox.TabIndex = 6;
            this.SRAM_MIRROR_Checkbox.Text = "SRAM_MIRROR_ON_OFF";
            this.SRAM_MIRROR_Checkbox.UseVisualStyleBackColor = true;
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
            // LAST_NDEF_Box
            // 
            this.LAST_NDEF_Box.Controls.Add(this.WriteNdef_Btn);
            this.LAST_NDEF_Box.Controls.Add(this.ReadNdef_Btn);
            this.LAST_NDEF_Box.Controls.Add(this.LstNdefBlock_TextBox);
            this.LAST_NDEF_Box.Controls.Add(this.LstNdefBlock_Label);
            this.LAST_NDEF_Box.Controls.Add(this.LAST_NDEF_Info_PicBox);
            this.LAST_NDEF_Box.Location = new System.Drawing.Point(253, 4);
            this.LAST_NDEF_Box.Margin = new System.Windows.Forms.Padding(4);
            this.LAST_NDEF_Box.Name = "LAST_NDEF_Box";
            this.LAST_NDEF_Box.Padding = new System.Windows.Forms.Padding(4);
            this.LAST_NDEF_Box.Size = new System.Drawing.Size(239, 121);
            this.LAST_NDEF_Box.TabIndex = 1;
            this.LAST_NDEF_Box.TabStop = false;
            this.LAST_NDEF_Box.Text = "LAST_NDEF_BLOCK : 0xFE:1";
            // 
            // WriteNdef_Btn
            // 
            this.WriteNdef_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.WriteNdef_Btn.Location = new System.Drawing.Point(120, 81);
            this.WriteNdef_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.WriteNdef_Btn.Name = "WriteNdef_Btn";
            this.WriteNdef_Btn.Size = new System.Drawing.Size(113, 33);
            this.WriteNdef_Btn.TabIndex = 12;
            this.WriteNdef_Btn.Text = "Write NDEF";
            this.WriteNdef_Btn.UseVisualStyleBackColor = true;
            this.WriteNdef_Btn.Click += new System.EventHandler(this.writeLast_Ndef_BlockToReg);
            // 
            // ReadNdef_Btn
            // 
            this.ReadNdef_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ReadNdef_Btn.Location = new System.Drawing.Point(5, 81);
            this.ReadNdef_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.ReadNdef_Btn.Name = "ReadNdef_Btn";
            this.ReadNdef_Btn.Size = new System.Drawing.Size(113, 33);
            this.ReadNdef_Btn.TabIndex = 11;
            this.ReadNdef_Btn.Text = "Read NDEF";
            this.ReadNdef_Btn.UseVisualStyleBackColor = true;
            this.ReadNdef_Btn.Click += new System.EventHandler(this.updateLAST_Ndef_Block);
            // 
            // LstNdefBlock_TextBox
            // 
            this.LstNdefBlock_TextBox.Location = new System.Drawing.Point(199, 50);
            this.LstNdefBlock_TextBox.Margin = new System.Windows.Forms.Padding(4);
            this.LstNdefBlock_TextBox.Name = "LstNdefBlock_TextBox";
            this.LstNdefBlock_TextBox.Size = new System.Drawing.Size(27, 22);
            this.LstNdefBlock_TextBox.TabIndex = 3;
            this.LstNdefBlock_TextBox.Text = "00";
            // 
            // LstNdefBlock_Label
            // 
            this.LstNdefBlock_Label.AutoSize = true;
            this.LstNdefBlock_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LstNdefBlock_Label.Location = new System.Drawing.Point(8, 54);
            this.LstNdefBlock_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.LstNdefBlock_Label.Name = "LstNdefBlock_Label";
            this.LstNdefBlock_Label.Size = new System.Drawing.Size(179, 16);
            this.LstNdefBlock_Label.TabIndex = 11;
            this.LstNdefBlock_Label.Text = "Last BLOCK NDEF message";
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
            this.LAST_NDEF_Info_PicBox.Click += new System.EventHandler(this.showLast_Ndef_Block_Info);
            // 
            // WDT_Box
            // 
            this.WDT_Box.Controls.Add(this.WriteWDT_Btn);
            this.WDT_Box.Controls.Add(this.ReadWDT_Btn);
            this.WDT_Box.Controls.Add(this.WatchDog_Label);
            this.WDT_Box.Controls.Add(this.WDT_LS_TextBox);
            this.WDT_Box.Controls.Add(this.WDT_MS_TextBox);
            this.WDT_Box.Controls.Add(this.WDT_Info_PicBox);
            this.WDT_Box.Location = new System.Drawing.Point(500, 4);
            this.WDT_Box.Margin = new System.Windows.Forms.Padding(4);
            this.WDT_Box.Name = "WDT_Box";
            this.WDT_Box.Padding = new System.Windows.Forms.Padding(4);
            this.WDT_Box.Size = new System.Drawing.Size(239, 121);
            this.WDT_Box.TabIndex = 1;
            this.WDT_Box.TabStop = false;
            this.WDT_Box.Text = "WDT : 0xFE:[4:3]";
            // 
            // WriteWDT_Btn
            // 
            this.WriteWDT_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.WriteWDT_Btn.Location = new System.Drawing.Point(120, 81);
            this.WriteWDT_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.WriteWDT_Btn.Name = "WriteWDT_Btn";
            this.WriteWDT_Btn.Size = new System.Drawing.Size(113, 33);
            this.WriteWDT_Btn.TabIndex = 18;
            this.WriteWDT_Btn.Text = "Write WDT";
            this.WriteWDT_Btn.UseVisualStyleBackColor = true;
            this.WriteWDT_Btn.Click += new System.EventHandler(this.writeWDT_ToReg);
            // 
            // ReadWDT_Btn
            // 
            this.ReadWDT_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ReadWDT_Btn.Location = new System.Drawing.Point(5, 81);
            this.ReadWDT_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.ReadWDT_Btn.Name = "ReadWDT_Btn";
            this.ReadWDT_Btn.Size = new System.Drawing.Size(113, 33);
            this.ReadWDT_Btn.TabIndex = 17;
            this.ReadWDT_Btn.Text = "Read WDT";
            this.ReadWDT_Btn.UseVisualStyleBackColor = true;
            this.ReadWDT_Btn.Click += new System.EventHandler(this.updateWDT);
            // 
            // WatchDog_Label
            // 
            this.WatchDog_Label.AutoSize = true;
            this.WatchDog_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.WatchDog_Label.Location = new System.Drawing.Point(20, 58);
            this.WatchDog_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.WatchDog_Label.Name = "WatchDog_Label";
            this.WatchDog_Label.Size = new System.Drawing.Size(185, 16);
            this.WatchDog_Label.TabIndex = 16;
            this.WatchDog_Label.Text = "Watchdog time-out: 20.000 ms";
            // 
            // WDT_LS_TextBox
            // 
            this.WDT_LS_TextBox.Location = new System.Drawing.Point(120, 30);
            this.WDT_LS_TextBox.Margin = new System.Windows.Forms.Padding(4);
            this.WDT_LS_TextBox.Name = "WDT_LS_TextBox";
            this.WDT_LS_TextBox.Size = new System.Drawing.Size(27, 22);
            this.WDT_LS_TextBox.TabIndex = 15;
            this.WDT_LS_TextBox.Text = "48";
            this.WDT_LS_TextBox.TextChanged += new System.EventHandler(this.updateWatchdog_withWDT_LS);
            // 
            // WDT_MS_TextBox
            // 
            this.WDT_MS_TextBox.Location = new System.Drawing.Point(89, 30);
            this.WDT_MS_TextBox.Margin = new System.Windows.Forms.Padding(4);
            this.WDT_MS_TextBox.Name = "WDT_MS_TextBox";
            this.WDT_MS_TextBox.Size = new System.Drawing.Size(27, 22);
            this.WDT_MS_TextBox.TabIndex = 14;
            this.WDT_MS_TextBox.Text = "08";
            this.WDT_MS_TextBox.TextChanged += new System.EventHandler(this.updateWatchdog_withWDT_MS);
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
            this.WDT_Info_PicBox.Click += new System.EventHandler(this.showWDT_Info);
            // 
            // I2C_CLOCK_Box
            // 
            this.I2C_CLOCK_Box.Controls.Add(this.I2C_CLOCK_Info_PicBox);
            this.I2C_CLOCK_Box.Controls.Add(this.ReadI2C_STR_Btn);
            this.I2C_CLOCK_Box.Controls.Add(this.I2C_Clock_EN_ChckB);
            this.I2C_CLOCK_Box.Location = new System.Drawing.Point(7, 260);
            this.I2C_CLOCK_Box.Margin = new System.Windows.Forms.Padding(4);
            this.I2C_CLOCK_Box.Name = "I2C_CLOCK_Box";
            this.I2C_CLOCK_Box.Padding = new System.Windows.Forms.Padding(4);
            this.I2C_CLOCK_Box.Size = new System.Drawing.Size(239, 121);
            this.I2C_CLOCK_Box.TabIndex = 1;
            this.I2C_CLOCK_Box.TabStop = false;
            this.I2C_CLOCK_Box.Text = "I2C_CLOCK_STR : 0xFE:5";
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
            this.I2C_CLOCK_Info_PicBox.Click += new System.EventHandler(this.showI2C_CLOCK_STR_Info);
            // 
            // ReadI2C_STR_Btn
            // 
            this.ReadI2C_STR_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ReadI2C_STR_Btn.Location = new System.Drawing.Point(60, 78);
            this.ReadI2C_STR_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.ReadI2C_STR_Btn.Name = "ReadI2C_STR_Btn";
            this.ReadI2C_STR_Btn.Size = new System.Drawing.Size(113, 33);
            this.ReadI2C_STR_Btn.TabIndex = 10;
            this.ReadI2C_STR_Btn.Text = "Read I2C_STR";
            this.ReadI2C_STR_Btn.UseVisualStyleBackColor = true;
            this.ReadI2C_STR_Btn.Click += new System.EventHandler(this.updateRead_I2C_STR);
            // 
            // I2C_Clock_EN_ChckB
            // 
            this.I2C_Clock_EN_ChckB.AutoSize = true;
            this.I2C_Clock_EN_ChckB.Checked = true;
            this.I2C_Clock_EN_ChckB.CheckState = System.Windows.Forms.CheckState.Checked;
            this.I2C_Clock_EN_ChckB.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.I2C_Clock_EN_ChckB.Location = new System.Drawing.Point(21, 49);
            this.I2C_Clock_EN_ChckB.Margin = new System.Windows.Forms.Padding(4);
            this.I2C_Clock_EN_ChckB.Name = "I2C_Clock_EN_ChckB";
            this.I2C_Clock_EN_ChckB.Size = new System.Drawing.Size(191, 20);
            this.I2C_Clock_EN_ChckB.TabIndex = 10;
            this.I2C_Clock_EN_ChckB.Text = "I2C_CLOCK_STR: Enabled";
            this.I2C_Clock_EN_ChckB.UseVisualStyleBackColor = true;
            this.I2C_Clock_EN_ChckB.CheckedChanged += new System.EventHandler(this.updateI2C_CLOCK_STR_ChckChanged);
            // 
            // SRAM_MIRROR_Box
            // 
            this.SRAM_MIRROR_Box.Controls.Add(this.WriteSM_Reg_Btn);
            this.SRAM_MIRROR_Box.Controls.Add(this.ReadSM_Reg_Btn);
            this.SRAM_MIRROR_Box.Controls.Add(this.SRAM_Addr_TextBox);
            this.SRAM_MIRROR_Box.Controls.Add(SRAM_Addr_Label);
            this.SRAM_MIRROR_Box.Controls.Add(this.SRAM_Info_PicBox);
            this.SRAM_MIRROR_Box.Location = new System.Drawing.Point(253, 132);
            this.SRAM_MIRROR_Box.Margin = new System.Windows.Forms.Padding(4);
            this.SRAM_MIRROR_Box.Name = "SRAM_MIRROR_Box";
            this.SRAM_MIRROR_Box.Padding = new System.Windows.Forms.Padding(4);
            this.SRAM_MIRROR_Box.Size = new System.Drawing.Size(239, 121);
            this.SRAM_MIRROR_Box.TabIndex = 1;
            this.SRAM_MIRROR_Box.TabStop = false;
            this.SRAM_MIRROR_Box.Text = "SRAM_MIRROR_BLOCK : 0xFE:2";
            // 
            // WriteSM_Reg_Btn
            // 
            this.WriteSM_Reg_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.WriteSM_Reg_Btn.Location = new System.Drawing.Point(121, 80);
            this.WriteSM_Reg_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.WriteSM_Reg_Btn.Name = "WriteSM_Reg_Btn";
            this.WriteSM_Reg_Btn.Size = new System.Drawing.Size(113, 33);
            this.WriteSM_Reg_Btn.TabIndex = 15;
            this.WriteSM_Reg_Btn.Text = "Write SM_REG";
            this.WriteSM_Reg_Btn.UseVisualStyleBackColor = true;
            this.WriteSM_Reg_Btn.Click += new System.EventHandler(this.writeSRAM_MIRROR_ToReg);
            // 
            // ReadSM_Reg_Btn
            // 
            this.ReadSM_Reg_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ReadSM_Reg_Btn.Location = new System.Drawing.Point(4, 80);
            this.ReadSM_Reg_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.ReadSM_Reg_Btn.Name = "ReadSM_Reg_Btn";
            this.ReadSM_Reg_Btn.Size = new System.Drawing.Size(116, 33);
            this.ReadSM_Reg_Btn.TabIndex = 14;
            this.ReadSM_Reg_Btn.Text = "Read SM_REG";
            this.ReadSM_Reg_Btn.UseVisualStyleBackColor = true;
            this.ReadSM_Reg_Btn.Click += new System.EventHandler(this.updateSRAM_MIRROR);
            // 
            // SRAM_Addr_TextBox
            // 
            this.SRAM_Addr_TextBox.Location = new System.Drawing.Point(157, 50);
            this.SRAM_Addr_TextBox.Margin = new System.Windows.Forms.Padding(4);
            this.SRAM_Addr_TextBox.Name = "SRAM_Addr_TextBox";
            this.SRAM_Addr_TextBox.Size = new System.Drawing.Size(27, 22);
            this.SRAM_Addr_TextBox.TabIndex = 13;
            this.SRAM_Addr_TextBox.Text = "F8";
            // 
            // SRAM_Info_PicBox
            // 
            this.SRAM_Info_PicBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("SRAM_Info_PicBox.BackgroundImage")));
            this.SRAM_Info_PicBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.SRAM_Info_PicBox.Location = new System.Drawing.Point(204, 17);
            this.SRAM_Info_PicBox.Margin = new System.Windows.Forms.Padding(4);
            this.SRAM_Info_PicBox.Name = "SRAM_Info_PicBox";
            this.SRAM_Info_PicBox.Size = new System.Drawing.Size(24, 22);
            this.SRAM_Info_PicBox.TabIndex = 11;
            this.SRAM_Info_PicBox.TabStop = false;
            this.SRAM_Info_PicBox.Click += new System.EventHandler(this.showSRAM_MIRROR_Info);
            // 
            // NS_REG_Box
            // 
            this.NS_REG_Box.Controls.Add(this.WriteNS_REG_Btn);
            this.NS_REG_Box.Controls.Add(this.ReadNS_REG_Btn);
            this.NS_REG_Box.Controls.Add(this.RF_F_Present_ChB);
            this.NS_REG_Box.Controls.Add(this.EEPROM_BSY_ChB);
            this.NS_REG_Box.Controls.Add(this.EEPROM_ERR_ChB);
            this.NS_REG_Box.Controls.Add(this.SRAM_RF_RDY_ChB);
            this.NS_REG_Box.Controls.Add(this.SRAM_I2C_RDY_ChB);
            this.NS_REG_Box.Controls.Add(this.RF_LOCKED_ChB);
            this.NS_REG_Box.Controls.Add(this.I2C_LOCKED_ChB);
            this.NS_REG_Box.Controls.Add(this.NS_REG_Info_PicBox);
            this.NS_REG_Box.Controls.Add(this.NDEF_READ_ChBox);
            this.NS_REG_Box.Location = new System.Drawing.Point(500, 132);
            this.NS_REG_Box.Margin = new System.Windows.Forms.Padding(4);
            this.NS_REG_Box.Name = "NS_REG_Box";
            this.NS_REG_Box.Padding = new System.Windows.Forms.Padding(4);
            this.NS_REG_Box.Size = new System.Drawing.Size(239, 249);
            this.NS_REG_Box.TabIndex = 2;
            this.NS_REG_Box.TabStop = false;
            this.NS_REG_Box.Text = "NS_REG : 0xFE:6";
            // 
            // WriteNS_REG_Btn
            // 
            this.WriteNS_REG_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.WriteNS_REG_Btn.Location = new System.Drawing.Point(120, 207);
            this.WriteNS_REG_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.WriteNS_REG_Btn.Name = "WriteNS_REG_Btn";
            this.WriteNS_REG_Btn.Size = new System.Drawing.Size(113, 33);
            this.WriteNS_REG_Btn.TabIndex = 22;
            this.WriteNS_REG_Btn.Text = "Write NS_REG";
            this.WriteNS_REG_Btn.UseVisualStyleBackColor = true;
            this.WriteNS_REG_Btn.Click += new System.EventHandler(this.writeNS_REG_ToReg);
            // 
            // ReadNS_REG_Btn
            // 
            this.ReadNS_REG_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ReadNS_REG_Btn.Location = new System.Drawing.Point(5, 207);
            this.ReadNS_REG_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.ReadNS_REG_Btn.Name = "ReadNS_REG_Btn";
            this.ReadNS_REG_Btn.Size = new System.Drawing.Size(113, 33);
            this.ReadNS_REG_Btn.TabIndex = 21;
            this.ReadNS_REG_Btn.Text = "Read NS_REG";
            this.ReadNS_REG_Btn.UseVisualStyleBackColor = true;
            this.ReadNS_REG_Btn.Click += new System.EventHandler(this.updateNS_REG);
            // 
            // RF_F_Present_ChB
            // 
            this.RF_F_Present_ChB.AutoSize = true;
            this.RF_F_Present_ChB.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RF_F_Present_ChB.Location = new System.Drawing.Point(8, 178);
            this.RF_F_Present_ChB.Margin = new System.Windows.Forms.Padding(4);
            this.RF_F_Present_ChB.Name = "RF_F_Present_ChB";
            this.RF_F_Present_ChB.Size = new System.Drawing.Size(195, 20);
            this.RF_F_Present_ChB.TabIndex = 20;
            this.RF_F_Present_ChB.Text = "RF_FIELD_PRESENT (RO)";
            this.RF_F_Present_ChB.UseVisualStyleBackColor = true;
            // 
            // EEPROM_BSY_ChB
            // 
            this.EEPROM_BSY_ChB.AutoSize = true;
            this.EEPROM_BSY_ChB.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EEPROM_BSY_ChB.Location = new System.Drawing.Point(8, 156);
            this.EEPROM_BSY_ChB.Margin = new System.Windows.Forms.Padding(4);
            this.EEPROM_BSY_ChB.Name = "EEPROM_BSY_ChB";
            this.EEPROM_BSY_ChB.Size = new System.Drawing.Size(193, 20);
            this.EEPROM_BSY_ChB.TabIndex = 19;
            this.EEPROM_BSY_ChB.Text = "EEPROM_WR_BUSY (RO)";
            this.EEPROM_BSY_ChB.UseVisualStyleBackColor = true;
            // 
            // EEPROM_ERR_ChB
            // 
            this.EEPROM_ERR_ChB.AutoSize = true;
            this.EEPROM_ERR_ChB.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EEPROM_ERR_ChB.Location = new System.Drawing.Point(8, 134);
            this.EEPROM_ERR_ChB.Margin = new System.Windows.Forms.Padding(4);
            this.EEPROM_ERR_ChB.Name = "EEPROM_ERR_ChB";
            this.EEPROM_ERR_ChB.Size = new System.Drawing.Size(154, 20);
            this.EEPROM_ERR_ChB.TabIndex = 18;
            this.EEPROM_ERR_ChB.Text = "EEPROM_WR_ERR";
            this.EEPROM_ERR_ChB.UseVisualStyleBackColor = true;
            // 
            // SRAM_RF_RDY_ChB
            // 
            this.SRAM_RF_RDY_ChB.AutoSize = true;
            this.SRAM_RF_RDY_ChB.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SRAM_RF_RDY_ChB.Location = new System.Drawing.Point(8, 112);
            this.SRAM_RF_RDY_ChB.Margin = new System.Windows.Forms.Padding(4);
            this.SRAM_RF_RDY_ChB.Name = "SRAM_RF_RDY_ChB";
            this.SRAM_RF_RDY_ChB.Size = new System.Drawing.Size(179, 20);
            this.SRAM_RF_RDY_ChB.TabIndex = 17;
            this.SRAM_RF_RDY_ChB.Text = "SRAM_RF_READY (RO)";
            this.SRAM_RF_RDY_ChB.UseVisualStyleBackColor = true;
            // 
            // SRAM_I2C_RDY_ChB
            // 
            this.SRAM_I2C_RDY_ChB.AutoSize = true;
            this.SRAM_I2C_RDY_ChB.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SRAM_I2C_RDY_ChB.Location = new System.Drawing.Point(8, 90);
            this.SRAM_I2C_RDY_ChB.Margin = new System.Windows.Forms.Padding(4);
            this.SRAM_I2C_RDY_ChB.Name = "SRAM_I2C_RDY_ChB";
            this.SRAM_I2C_RDY_ChB.Size = new System.Drawing.Size(180, 20);
            this.SRAM_I2C_RDY_ChB.TabIndex = 16;
            this.SRAM_I2C_RDY_ChB.Text = "SRAM_I2C_READY (RO)";
            this.SRAM_I2C_RDY_ChB.UseVisualStyleBackColor = true;
            // 
            // RF_LOCKED_ChB
            // 
            this.RF_LOCKED_ChB.AutoSize = true;
            this.RF_LOCKED_ChB.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RF_LOCKED_ChB.Location = new System.Drawing.Point(8, 68);
            this.RF_LOCKED_ChB.Margin = new System.Windows.Forms.Padding(4);
            this.RF_LOCKED_ChB.Name = "RF_LOCKED_ChB";
            this.RF_LOCKED_ChB.Size = new System.Drawing.Size(139, 20);
            this.RF_LOCKED_ChB.TabIndex = 15;
            this.RF_LOCKED_ChB.Text = "RF_LOCKED (RO)";
            this.RF_LOCKED_ChB.UseVisualStyleBackColor = true;
            // 
            // I2C_LOCKED_ChB
            // 
            this.I2C_LOCKED_ChB.AutoSize = true;
            this.I2C_LOCKED_ChB.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.I2C_LOCKED_ChB.Location = new System.Drawing.Point(8, 46);
            this.I2C_LOCKED_ChB.Margin = new System.Windows.Forms.Padding(4);
            this.I2C_LOCKED_ChB.Name = "I2C_LOCKED_ChB";
            this.I2C_LOCKED_ChB.Size = new System.Drawing.Size(109, 20);
            this.I2C_LOCKED_ChB.TabIndex = 14;
            this.I2C_LOCKED_ChB.Text = "I2C_LOCKED";
            this.I2C_LOCKED_ChB.UseVisualStyleBackColor = true;
            // 
            // NS_REG_Info_PicBox
            // 
            this.NS_REG_Info_PicBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("NS_REG_Info_PicBox.BackgroundImage")));
            this.NS_REG_Info_PicBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.NS_REG_Info_PicBox.Location = new System.Drawing.Point(204, 17);
            this.NS_REG_Info_PicBox.Margin = new System.Windows.Forms.Padding(4);
            this.NS_REG_Info_PicBox.Name = "NS_REG_Info_PicBox";
            this.NS_REG_Info_PicBox.Size = new System.Drawing.Size(24, 22);
            this.NS_REG_Info_PicBox.TabIndex = 13;
            this.NS_REG_Info_PicBox.TabStop = false;
            this.NS_REG_Info_PicBox.Click += new System.EventHandler(this.showNS_REG_Info);
            // 
            // NDEF_READ_ChBox
            // 
            this.NDEF_READ_ChBox.AutoSize = true;
            this.NDEF_READ_ChBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.NDEF_READ_ChBox.Location = new System.Drawing.Point(8, 23);
            this.NDEF_READ_ChBox.Margin = new System.Windows.Forms.Padding(4);
            this.NDEF_READ_ChBox.Name = "NDEF_READ_ChBox";
            this.NDEF_READ_ChBox.Size = new System.Drawing.Size(187, 20);
            this.NDEF_READ_ChBox.TabIndex = 12;
            this.NDEF_READ_ChBox.Text = "NDEF_DATA_READ (RO)";
            this.NDEF_READ_ChBox.UseVisualStyleBackColor = true;
            // 
            // ReadAll_Btn
            // 
            this.ReadAll_Btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ReadAll_Btn.Location = new System.Drawing.Point(325, 283);
            this.ReadAll_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.ReadAll_Btn.Name = "ReadAll_Btn";
            this.ReadAll_Btn.Size = new System.Drawing.Size(113, 33);
            this.ReadAll_Btn.TabIndex = 22;
            this.ReadAll_Btn.Text = "Read All";
            this.ReadAll_Btn.UseVisualStyleBackColor = true;
            this.ReadAll_Btn.Click += new System.EventHandler(this.readAllRegistersAndShow);
            // 
            // button13
            // 
            this.button13.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.button13.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button13.Location = new System.Drawing.Point(325, 338);
            this.button13.Margin = new System.Windows.Forms.Padding(4);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(113, 33);
            this.button13.TabIndex = 23;
            this.button13.Text = "Close";
            this.button13.UseVisualStyleBackColor = true;
            // 
            // SessionRegPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(747, 384);
            this.Controls.Add(this.button13);
            this.Controls.Add(this.ReadAll_Btn);
            this.Controls.Add(this.NS_REG_Box);
            this.Controls.Add(this.SRAM_MIRROR_Box);
            this.Controls.Add(this.I2C_CLOCK_Box);
            this.Controls.Add(this.WDT_Box);
            this.Controls.Add(this.LAST_NDEF_Box);
            this.Controls.Add(this.NC_REG_Box);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SessionRegPanel";
            this.Text = "Session Registers";
            this.NC_REG_Box.ResumeLayout(false);
            this.NC_REG_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NC_REG_Info_PicBox)).EndInit();
            this.LAST_NDEF_Box.ResumeLayout(false);
            this.LAST_NDEF_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.LAST_NDEF_Info_PicBox)).EndInit();
            this.WDT_Box.ResumeLayout(false);
            this.WDT_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.WDT_Info_PicBox)).EndInit();
            this.I2C_CLOCK_Box.ResumeLayout(false);
            this.I2C_CLOCK_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.I2C_CLOCK_Info_PicBox)).EndInit();
            this.SRAM_MIRROR_Box.ResumeLayout(false);
            this.SRAM_MIRROR_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SRAM_Info_PicBox)).EndInit();
            this.NS_REG_Box.ResumeLayout(false);
            this.NS_REG_Box.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NS_REG_Info_PicBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox NC_REG_Box;
        private System.Windows.Forms.PictureBox I2C_CLOCK_Info_PicBox;
        private System.Windows.Forms.PictureBox NC_REG_Info_PicBox;
        private System.Windows.Forms.Button WriteNC_REG_Btn;
        private System.Windows.Forms.Button ReadNC_REG_Btn;
        private System.Windows.Forms.CheckBox Transfer_DIR_Checkbox;
        private System.Windows.Forms.CheckBox SRAM_MIRROR_Checkbox;
        private System.Windows.Forms.ComboBox FD_ON_Combo;
        private System.Windows.Forms.Label FD_ON_Label;
        private System.Windows.Forms.ComboBox FD_OFF_Combo;
        private System.Windows.Forms.Label FD_OFF_Label;
        private System.Windows.Forms.CheckBox PTHRU_CheckBox;
        private System.Windows.Forms.CheckBox I2C_RST_CheckBox;
        private System.Windows.Forms.GroupBox LAST_NDEF_Box;
        private System.Windows.Forms.GroupBox WDT_Box;
        private System.Windows.Forms.GroupBox I2C_CLOCK_Box;
        private System.Windows.Forms.Button ReadI2C_STR_Btn;
        private System.Windows.Forms.CheckBox I2C_Clock_EN_ChckB;
        private System.Windows.Forms.GroupBox SRAM_MIRROR_Box;
        private System.Windows.Forms.GroupBox NS_REG_Box;
        private System.Windows.Forms.Button WriteNdef_Btn;
        private System.Windows.Forms.Button ReadNdef_Btn;
        private System.Windows.Forms.TextBox LstNdefBlock_TextBox;
        private System.Windows.Forms.Label LstNdefBlock_Label;
        private System.Windows.Forms.PictureBox LAST_NDEF_Info_PicBox;
        private System.Windows.Forms.Button WriteWDT_Btn;
        private System.Windows.Forms.Button ReadWDT_Btn;
        private System.Windows.Forms.Label WatchDog_Label;
        private System.Windows.Forms.TextBox WDT_LS_TextBox;
        private System.Windows.Forms.TextBox WDT_MS_TextBox;
        private System.Windows.Forms.PictureBox WDT_Info_PicBox;
        private System.Windows.Forms.Button WriteSM_Reg_Btn;
        private System.Windows.Forms.Button ReadSM_Reg_Btn;
        private System.Windows.Forms.TextBox SRAM_Addr_TextBox;
        private System.Windows.Forms.PictureBox SRAM_Info_PicBox;
        private System.Windows.Forms.Button WriteNS_REG_Btn;
        private System.Windows.Forms.Button ReadNS_REG_Btn;
        private System.Windows.Forms.CheckBox RF_F_Present_ChB;
        private System.Windows.Forms.CheckBox EEPROM_BSY_ChB;
        private System.Windows.Forms.CheckBox EEPROM_ERR_ChB;
        private System.Windows.Forms.CheckBox SRAM_RF_RDY_ChB;
        private System.Windows.Forms.CheckBox SRAM_I2C_RDY_ChB;
        private System.Windows.Forms.CheckBox RF_LOCKED_ChB;
        private System.Windows.Forms.CheckBox I2C_LOCKED_ChB;
        private System.Windows.Forms.PictureBox NS_REG_Info_PicBox;
        private System.Windows.Forms.CheckBox NDEF_READ_ChBox;
        private System.Windows.Forms.Button button13;
        public System.Windows.Forms.Button ReadAll_Btn;
    }
}