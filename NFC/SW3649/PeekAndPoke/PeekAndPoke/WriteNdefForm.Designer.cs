namespace PeekAndPoke
{
    partial class WriteNdefForm
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
            this.textNdef_Label = new System.Windows.Forms.Label();
            this.textNdef_textBox = new System.Windows.Forms.TextBox();
            this.textNdef_write_Btn = new System.Windows.Forms.Button();
            this.cancel_Btn = new System.Windows.Forms.Button();
            this.textNdef_Box = new System.Windows.Forms.GroupBox();
            this.defaultNdef_Box = new System.Windows.Forms.GroupBox();
            this.defaultNdef_Label = new System.Windows.Forms.Label();
            this.defaultNdef_write_Btn = new System.Windows.Forms.Button();
            this.textNdef_Box.SuspendLayout();
            this.defaultNdef_Box.SuspendLayout();
            this.SuspendLayout();
            // 
            // textNdef_Label
            // 
            this.textNdef_Label.Location = new System.Drawing.Point(11, 42);
            this.textNdef_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.textNdef_Label.Name = "textNdef_Label";
            this.textNdef_Label.Size = new System.Drawing.Size(348, 34);
            this.textNdef_Label.TabIndex = 0;
            this.textNdef_Label.Text = "Write the text you want to be written in the NTAG I²C:";
            // 
            // textNdef_textBox
            // 
            this.textNdef_textBox.Location = new System.Drawing.Point(9, 85);
            this.textNdef_textBox.Margin = new System.Windows.Forms.Padding(4);
            this.textNdef_textBox.Name = "textNdef_textBox";
            this.textNdef_textBox.Size = new System.Drawing.Size(349, 22);
            this.textNdef_textBox.TabIndex = 1;
            // 
            // textNdef_write_Btn
            // 
            this.textNdef_write_Btn.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.textNdef_write_Btn.Location = new System.Drawing.Point(112, 146);
            this.textNdef_write_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.textNdef_write_Btn.Name = "textNdef_write_Btn";
            this.textNdef_write_Btn.Size = new System.Drawing.Size(140, 38);
            this.textNdef_write_Btn.TabIndex = 2;
            this.textNdef_write_Btn.Text = "Write";
            this.textNdef_write_Btn.UseVisualStyleBackColor = true;
            this.textNdef_write_Btn.Click += new System.EventHandler(this.writeTextNdef);
            // 
            // cancel_Btn
            // 
            this.cancel_Btn.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancel_Btn.Location = new System.Drawing.Point(304, 213);
            this.cancel_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.cancel_Btn.Name = "cancel_Btn";
            this.cancel_Btn.Size = new System.Drawing.Size(140, 38);
            this.cancel_Btn.TabIndex = 3;
            this.cancel_Btn.Text = "Cancel";
            this.cancel_Btn.UseVisualStyleBackColor = true;
            // 
            // textNdef_Box
            // 
            this.textNdef_Box.Controls.Add(this.textNdef_textBox);
            this.textNdef_Box.Controls.Add(this.textNdef_Label);
            this.textNdef_Box.Controls.Add(this.textNdef_write_Btn);
            this.textNdef_Box.Location = new System.Drawing.Point(5, 6);
            this.textNdef_Box.Margin = new System.Windows.Forms.Padding(4);
            this.textNdef_Box.Name = "textNdef_Box";
            this.textNdef_Box.Padding = new System.Windows.Forms.Padding(4);
            this.textNdef_Box.Size = new System.Drawing.Size(368, 199);
            this.textNdef_Box.TabIndex = 4;
            this.textNdef_Box.TabStop = false;
            this.textNdef_Box.Text = "Text NDEF message";
            // 
            // defaultNdef_Box
            // 
            this.defaultNdef_Box.Controls.Add(this.defaultNdef_Label);
            this.defaultNdef_Box.Controls.Add(this.defaultNdef_write_Btn);
            this.defaultNdef_Box.Location = new System.Drawing.Point(379, 6);
            this.defaultNdef_Box.Margin = new System.Windows.Forms.Padding(4);
            this.defaultNdef_Box.Name = "defaultNdef_Box";
            this.defaultNdef_Box.Padding = new System.Windows.Forms.Padding(4);
            this.defaultNdef_Box.Size = new System.Drawing.Size(368, 199);
            this.defaultNdef_Box.TabIndex = 5;
            this.defaultNdef_Box.TabStop = false;
            this.defaultNdef_Box.Text = "Default NDEF message";
            // 
            // defaultNdef_Label
            // 
            this.defaultNdef_Label.Location = new System.Drawing.Point(13, 42);
            this.defaultNdef_Label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.defaultNdef_Label.Name = "defaultNdef_Label";
            this.defaultNdef_Label.Size = new System.Drawing.Size(345, 94);
            this.defaultNdef_Label.TabIndex = 0;
            this.defaultNdef_Label.Text = "Write the default NDEF message into the NTAG I²C:\r\n  - Smart Poster:\r\n      - Tex" +
    "t: NTAG I2C EXPLORER\r\n      - URI: http://www.nxp.com/demoboard/OM5569\r\n  - AAR:" +
    " com.nxp.ntagi2cdemo";
            // 
            // defaultNdef_write_Btn
            // 
            this.defaultNdef_write_Btn.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.defaultNdef_write_Btn.Location = new System.Drawing.Point(123, 146);
            this.defaultNdef_write_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.defaultNdef_write_Btn.Name = "defaultNdef_write_Btn";
            this.defaultNdef_write_Btn.Size = new System.Drawing.Size(140, 38);
            this.defaultNdef_write_Btn.TabIndex = 2;
            this.defaultNdef_write_Btn.Text = "Write";
            this.defaultNdef_write_Btn.UseVisualStyleBackColor = true;
            this.defaultNdef_write_Btn.Click += new System.EventHandler(this.writeDefaultNdef);
            // 
            // WriteNdefForm
            // 
            this.AcceptButton = this.cancel_Btn;
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancel_Btn;
            this.ClientSize = new System.Drawing.Size(752, 258);
            this.Controls.Add(this.defaultNdef_Box);
            this.Controls.Add(this.textNdef_Box);
            this.Controls.Add(this.cancel_Btn);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "WriteNdefForm";
            this.ShowIcon = false;
            this.Text = "Write NDEF message";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.WriteNdefForm_FormClosing);
            this.textNdef_Box.ResumeLayout(false);
            this.textNdef_Box.PerformLayout();
            this.defaultNdef_Box.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label textNdef_Label;
        private System.Windows.Forms.TextBox textNdef_textBox;
        private System.Windows.Forms.Button textNdef_write_Btn;
        private System.Windows.Forms.Button cancel_Btn;
        private System.Windows.Forms.GroupBox textNdef_Box;
        private System.Windows.Forms.GroupBox defaultNdef_Box;
        private System.Windows.Forms.Label defaultNdef_Label;
        private System.Windows.Forms.Button defaultNdef_write_Btn;
    }
}