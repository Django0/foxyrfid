namespace PeekAndPoke
{
    partial class I2CAddress
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
            this.labelCurrentI2C = new System.Windows.Forms.Label();
            this.labelNewI2C = new System.Windows.Forms.Label();
            this.currentAddressTextBox = new System.Windows.Forms.TextBox();
            this.newAddressTextBox = new System.Windows.Forms.TextBox();
            this.buttonOK = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // labelCurrentI2C
            // 
            this.labelCurrentI2C.AutoSize = true;
            this.labelCurrentI2C.Location = new System.Drawing.Point(44, 34);
            this.labelCurrentI2C.Name = "labelCurrentI2C";
            this.labelCurrentI2C.Size = new System.Drawing.Size(140, 17);
            this.labelCurrentI2C.TabIndex = 0;
            this.labelCurrentI2C.Text = "Current I²C Address: ";
            // 
            // labelNewI2C
            // 
            this.labelNewI2C.AutoSize = true;
            this.labelNewI2C.Location = new System.Drawing.Point(47, 98);
            this.labelNewI2C.Name = "labelNewI2C";
            this.labelNewI2C.Size = new System.Drawing.Size(115, 17);
            this.labelNewI2C.TabIndex = 1;
            this.labelNewI2C.Text = "New I²C address:";
            // 
            // currentAddressTextBox
            // 
            this.currentAddressTextBox.Location = new System.Drawing.Point(220, 31);
            this.currentAddressTextBox.Name = "currentAddressTextBox";
            this.currentAddressTextBox.ReadOnly = true;
            this.currentAddressTextBox.Size = new System.Drawing.Size(33, 22);
            this.currentAddressTextBox.TabIndex = 2;
            // 
            // newAddressTextBox
            // 
            this.newAddressTextBox.Location = new System.Drawing.Point(220, 95);
            this.newAddressTextBox.MaxLength = 2;
            this.newAddressTextBox.Name = "newAddressTextBox";
            this.newAddressTextBox.Size = new System.Drawing.Size(33, 22);
            this.newAddressTextBox.TabIndex = 3;
            // 
            // buttonOK
            // 
            this.buttonOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonOK.Location = new System.Drawing.Point(38, 154);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(90, 42);
            this.buttonOK.TabIndex = 4;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.button1_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonCancel.Location = new System.Drawing.Point(187, 154);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(90, 42);
            this.buttonCancel.TabIndex = 5;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.button2_Click);
            // 
            // I2CAddress
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(320, 227);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.newAddressTextBox);
            this.Controls.Add(this.currentAddressTextBox);
            this.Controls.Add(this.labelNewI2C);
            this.Controls.Add(this.labelCurrentI2C);
            this.Name = "I2CAddress";
            this.Text = "Edit I²C Address";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelCurrentI2C;
        private System.Windows.Forms.Label labelNewI2C;
        private System.Windows.Forms.TextBox currentAddressTextBox;
        private System.Windows.Forms.TextBox newAddressTextBox;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.Button buttonCancel;
    }
}