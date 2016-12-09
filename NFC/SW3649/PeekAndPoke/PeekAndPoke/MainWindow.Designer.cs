using System.Drawing;
namespace PeekAndPoke
{
    partial class MainWindow
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle6 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.operationsStatus_Label = new System.Windows.Forms.ToolStripStatusLabel();
            this.deviceStatus_Label = new System.Windows.Forms.ToolStripStatusLabel();
            this.flagStatus_Label = new System.Windows.Forms.ToolStripStatusLabel();
            this.fwVersion_Label = new System.Windows.Forms.ToolStripStatusLabel();
            this.rightContainer = new System.Windows.Forms.SplitContainer();
            this.leftContainer = new System.Windows.Forms.SplitContainer();
            this.memoryTreeView = new System.Windows.Forms.TreeView();
            this.label2 = new System.Windows.Forms.Label();
            this.regBtnsPanel = new System.Windows.Forms.Panel();
            this.accessReg_Btn = new System.Windows.Forms.Button();
            this.configReg_Btn = new System.Windows.Forms.Button();
            this.sessionReg_Btn = new System.Windows.Forms.Button();
            this.clearLogging_Btn = new System.Windows.Forms.Button();
            this.usbLogging_ChckBox = new System.Windows.Forms.CheckBox();
            this.loggingPanel = new System.Windows.Forms.Panel();
            this.loggingText = new System.Windows.Forms.Label();
            this.memTablesContainer = new System.Windows.Forms.SplitContainer();
            this.hexaTable = new System.Windows.Forms.DataGridView();
            this.asciiTable = new System.Windows.Forms.DataGridView();
            this.navBarStripContainer = new System.Windows.Forms.ToolStripContainer();
            this.files_navBarStrip = new System.Windows.Forms.ToolStrip();
            this.saveFile_Btn = new System.Windows.Forms.ToolStripButton();
            this.openFile_Btn = new System.Windows.Forms.ToolStripButton();
            this.address_navBarStrip = new System.Windows.Forms.ToolStrip();
            this.i2cAddressAdd_Btn = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.scan_Btn = new System.Windows.Forms.ToolStripButton();
            this.actions_navBarStrip = new System.Windows.Forms.ToolStrip();
            this.writeBlock_Btn = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.readBlock_Btn = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.writeAll_Btn = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.readAll_Btn = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.writeNdef_Btn = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.reset_Btn = new System.Windows.Forms.ToolStripButton();
            this.devType_navBarStrip = new System.Windows.Forms.ToolStrip();
            this.deviceTypeLabel = new System.Windows.Forms.ToolStripLabel();
            this.tagTypeComboBox = new System.Windows.Forms.ToolStripComboBox();
            this.misc_navBarStrip = new System.Windows.Forms.ToolStrip();
            this.changeBusSpeed_Combo = new System.Windows.Forms.ToolStripComboBox();
            this.info_Btn = new System.Windows.Forms.ToolStripButton();
            this.i2cAddressInput = new System.Windows.Forms.ToolStripTextBox();
            this.addressLock_Btn = new System.Windows.Forms.ToolStripButton();
            this.checkDevtimer = new System.Windows.Forms.Timer(this.components);
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.statusStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.rightContainer)).BeginInit();
            this.rightContainer.Panel1.SuspendLayout();
            this.rightContainer.Panel2.SuspendLayout();
            this.rightContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.leftContainer)).BeginInit();
            this.leftContainer.Panel1.SuspendLayout();
            this.leftContainer.Panel2.SuspendLayout();
            this.leftContainer.SuspendLayout();
            this.regBtnsPanel.SuspendLayout();
            this.loggingPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.memTablesContainer)).BeginInit();
            this.memTablesContainer.Panel1.SuspendLayout();
            this.memTablesContainer.Panel2.SuspendLayout();
            this.memTablesContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.hexaTable)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.asciiTable)).BeginInit();
            this.navBarStripContainer.BottomToolStripPanel.SuspendLayout();
            this.navBarStripContainer.ContentPanel.SuspendLayout();
            this.navBarStripContainer.TopToolStripPanel.SuspendLayout();
            this.navBarStripContainer.SuspendLayout();
            this.files_navBarStrip.SuspendLayout();
            this.address_navBarStrip.SuspendLayout();
            this.actions_navBarStrip.SuspendLayout();
            this.devType_navBarStrip.SuspendLayout();
            this.misc_navBarStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // statusStrip1
            // 
            this.statusStrip1.Dock = System.Windows.Forms.DockStyle.None;
            this.statusStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.operationsStatus_Label,
            this.deviceStatus_Label,
            this.flagStatus_Label,
            this.fwVersion_Label});
            this.statusStrip1.Location = new System.Drawing.Point(0, 0);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(1576, 24);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // operationsStatus_Label
            // 
            this.operationsStatus_Label.AutoSize = false;
            this.operationsStatus_Label.BorderStyle = System.Windows.Forms.Border3DStyle.Adjust;
            this.operationsStatus_Label.Name = "operationsStatus_Label";
            this.operationsStatus_Label.Size = new System.Drawing.Size(226, 19);
            // 
            // deviceStatus_Label
            // 
            this.deviceStatus_Label.AutoSize = false;
            this.deviceStatus_Label.Name = "deviceStatus_Label";
            this.deviceStatus_Label.Size = new System.Drawing.Size(300, 19);
            this.deviceStatus_Label.Text = "toolStripStatusLabel  2";
            // 
            // flagStatus_Label
            // 
            this.flagStatus_Label.AutoSize = false;
            this.flagStatus_Label.Name = "flagStatus_Label";
            this.flagStatus_Label.Size = new System.Drawing.Size(200, 19);
            // 
            // fwVersion_Label
            // 
            this.fwVersion_Label.AutoSize = false;
            this.fwVersion_Label.Name = "fwVersion_Label";
            this.fwVersion_Label.Size = new System.Drawing.Size(200, 19);
            // 
            // rightContainer
            // 
            this.rightContainer.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.rightContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.rightContainer.IsSplitterFixed = true;
            this.rightContainer.Location = new System.Drawing.Point(0, 0);
            this.rightContainer.Margin = new System.Windows.Forms.Padding(4);
            this.rightContainer.Name = "rightContainer";
            // 
            // rightContainer.Panel1
            // 
            this.rightContainer.Panel1.Controls.Add(this.leftContainer);
            this.rightContainer.Panel1.Controls.Add(this.loggingPanel);
            // 
            // rightContainer.Panel2
            // 
            this.rightContainer.Panel2.Controls.Add(this.memTablesContainer);
            this.rightContainer.Size = new System.Drawing.Size(1576, 631);
            this.rightContainer.SplitterDistance = 424;
            this.rightContainer.SplitterWidth = 5;
            this.rightContainer.TabIndex = 2;
            // 
            // leftContainer
            // 
            this.leftContainer.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.leftContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.leftContainer.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.leftContainer.Location = new System.Drawing.Point(0, 0);
            this.leftContainer.Margin = new System.Windows.Forms.Padding(4);
            this.leftContainer.Name = "leftContainer";
            this.leftContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // leftContainer.Panel1
            // 
            this.leftContainer.Panel1.Controls.Add(this.memoryTreeView);
            this.leftContainer.Panel1.Controls.Add(this.label2);
            this.leftContainer.Panel1.Controls.Add(this.regBtnsPanel);
            this.leftContainer.Panel1.RightToLeft = System.Windows.Forms.RightToLeft.No;
            // 
            // leftContainer.Panel2
            // 
            this.leftContainer.Panel2.Controls.Add(this.clearLogging_Btn);
            this.leftContainer.Panel2.Controls.Add(this.usbLogging_ChckBox);
            this.leftContainer.Panel2.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.leftContainer.Size = new System.Drawing.Size(424, 630);
            this.leftContainer.SplitterDistance = 563;
            this.leftContainer.SplitterWidth = 5;
            this.leftContainer.TabIndex = 1;
            // 
            // memoryTreeView
            // 
            this.memoryTreeView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.memoryTreeView.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.memoryTreeView.HideSelection = false;
            this.memoryTreeView.Location = new System.Drawing.Point(0, 0);
            this.memoryTreeView.Margin = new System.Windows.Forms.Padding(4);
            this.memoryTreeView.Name = "memoryTreeView";
            this.memoryTreeView.Size = new System.Drawing.Size(420, 500);
            this.memoryTreeView.TabIndex = 2;
            this.memoryTreeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.selectNodeOnTreeView);
            // 
            // label2
            // 
            this.label2.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.label2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label2.Location = new System.Drawing.Point(0, 0);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(420, 500);
            this.label2.TabIndex = 1;
            // 
            // regBtnsPanel
            // 
            this.regBtnsPanel.Controls.Add(this.accessReg_Btn);
            this.regBtnsPanel.Controls.Add(this.configReg_Btn);
            this.regBtnsPanel.Controls.Add(this.sessionReg_Btn);
            this.regBtnsPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.regBtnsPanel.Location = new System.Drawing.Point(0, 500);
            this.regBtnsPanel.Margin = new System.Windows.Forms.Padding(4);
            this.regBtnsPanel.Name = "regBtnsPanel";
            this.regBtnsPanel.Size = new System.Drawing.Size(420, 59);
            this.regBtnsPanel.TabIndex = 0;
            // 
            // accessReg_Btn
            // 
            this.accessReg_Btn.Location = new System.Drawing.Point(291, 5);
            this.accessReg_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.accessReg_Btn.Name = "accessReg_Btn";
            this.accessReg_Btn.Size = new System.Drawing.Size(111, 48);
            this.accessReg_Btn.TabIndex = 2;
            this.accessReg_Btn.Text = "Access\r\nRegisters";
            this.accessReg_Btn.UseVisualStyleBackColor = true;
            this.accessReg_Btn.Click += new System.EventHandler(this.showAccessRegPanel_BtnClick);
            // 
            // configReg_Btn
            // 
            this.configReg_Btn.Location = new System.Drawing.Point(152, 5);
            this.configReg_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.configReg_Btn.Name = "configReg_Btn";
            this.configReg_Btn.Size = new System.Drawing.Size(111, 48);
            this.configReg_Btn.TabIndex = 1;
            this.configReg_Btn.Text = "Config\r\nRegisters";
            this.configReg_Btn.UseVisualStyleBackColor = true;
            this.configReg_Btn.Click += new System.EventHandler(this.showConfigRegPanel_BtnClick);
            // 
            // sessionReg_Btn
            // 
            this.sessionReg_Btn.Location = new System.Drawing.Point(12, 5);
            this.sessionReg_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.sessionReg_Btn.Name = "sessionReg_Btn";
            this.sessionReg_Btn.Size = new System.Drawing.Size(111, 48);
            this.sessionReg_Btn.TabIndex = 0;
            this.sessionReg_Btn.Text = "Session\r\nRegisters";
            this.sessionReg_Btn.UseVisualStyleBackColor = true;
            this.sessionReg_Btn.Click += new System.EventHandler(this.showSessionRegPanel_BtnClick);
            // 
            // clearLogging_Btn
            // 
            this.clearLogging_Btn.Location = new System.Drawing.Point(221, 7);
            this.clearLogging_Btn.Margin = new System.Windows.Forms.Padding(4);
            this.clearLogging_Btn.Name = "clearLogging_Btn";
            this.clearLogging_Btn.Size = new System.Drawing.Size(93, 31);
            this.clearLogging_Btn.TabIndex = 1;
            this.clearLogging_Btn.Text = "Clear";
            this.clearLogging_Btn.UseVisualStyleBackColor = true;
            this.clearLogging_Btn.Click += new System.EventHandler(this.clearLoggingPanel);
            // 
            // usbLogging_ChckBox
            // 
            this.usbLogging_ChckBox.AutoSize = true;
            this.usbLogging_ChckBox.Location = new System.Drawing.Point(12, 14);
            this.usbLogging_ChckBox.Margin = new System.Windows.Forms.Padding(4);
            this.usbLogging_ChckBox.Name = "usbLogging_ChckBox";
            this.usbLogging_ChckBox.Size = new System.Drawing.Size(172, 21);
            this.usbLogging_ChckBox.TabIndex = 0;
            this.usbLogging_ChckBox.Text = "USB Logging Disabled";
            this.usbLogging_ChckBox.UseVisualStyleBackColor = true;
            this.usbLogging_ChckBox.CheckedChanged += new System.EventHandler(this.showOrHideLoggingPanel);
            // 
            // loggingPanel
            // 
            this.loggingPanel.Controls.Add(this.loggingText);
            this.loggingPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.loggingPanel.Location = new System.Drawing.Point(0, 630);
            this.loggingPanel.Margin = new System.Windows.Forms.Padding(4);
            this.loggingPanel.Name = "loggingPanel";
            this.loggingPanel.Size = new System.Drawing.Size(424, 1);
            this.loggingPanel.TabIndex = 0;
            // 
            // loggingText
            // 
            this.loggingText.BackColor = System.Drawing.SystemColors.GrayText;
            this.loggingText.Dock = System.Windows.Forms.DockStyle.Fill;
            this.loggingText.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.loggingText.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.loggingText.Location = new System.Drawing.Point(0, 0);
            this.loggingText.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.loggingText.Name = "loggingText";
            this.loggingText.Size = new System.Drawing.Size(424, 1);
            this.loggingText.TabIndex = 0;
            // 
            // memTablesContainer
            // 
            this.memTablesContainer.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.memTablesContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.memTablesContainer.IsSplitterFixed = true;
            this.memTablesContainer.Location = new System.Drawing.Point(0, 0);
            this.memTablesContainer.Margin = new System.Windows.Forms.Padding(4);
            this.memTablesContainer.Name = "memTablesContainer";
            // 
            // memTablesContainer.Panel1
            // 
            this.memTablesContainer.Panel1.Controls.Add(this.hexaTable);
            // 
            // memTablesContainer.Panel2
            // 
            this.memTablesContainer.Panel2.Controls.Add(this.asciiTable);
            this.memTablesContainer.Panel2.Enabled = false;
            this.memTablesContainer.Size = new System.Drawing.Size(1147, 631);
            this.memTablesContainer.SplitterDistance = 623;
            this.memTablesContainer.SplitterWidth = 5;
            this.memTablesContainer.TabIndex = 0;
            // 
            // hexaTable
            // 
            this.hexaTable.AllowUserToAddRows = false;
            this.hexaTable.AllowUserToDeleteRows = false;
            this.hexaTable.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F);
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.hexaTable.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.hexaTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.hexaTable.DefaultCellStyle = dataGridViewCellStyle2;
            this.hexaTable.Dock = System.Windows.Forms.DockStyle.Fill;
            this.hexaTable.GridColor = System.Drawing.SystemColors.Control;
            this.hexaTable.Location = new System.Drawing.Point(0, 0);
            this.hexaTable.Margin = new System.Windows.Forms.Padding(4);
            this.hexaTable.MultiSelect = false;
            this.hexaTable.Name = "hexaTable";
            dataGridViewCellStyle3.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle3.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.75F);
            dataGridViewCellStyle3.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle3.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle3.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.hexaTable.RowHeadersDefaultCellStyle = dataGridViewCellStyle3;
            this.hexaTable.RowHeadersWidth = 65;
            this.hexaTable.RowTemplate.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.hexaTable.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.hexaTable.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect;
            this.hexaTable.Size = new System.Drawing.Size(619, 627);
            this.hexaTable.TabIndex = 0;
            this.hexaTable.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.checkAndSetChangeOnHexaTable_List);
            this.hexaTable.CurrentCellChanged += new System.EventHandler(this.selectCellOnHexaTable);
            this.hexaTable.Scroll += new System.Windows.Forms.ScrollEventHandler(this.scrollAsciiAsHexaTable);
            // 
            // asciiTable
            // 
            this.asciiTable.AllowUserToAddRows = false;
            this.asciiTable.AllowUserToDeleteRows = false;
            this.asciiTable.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.asciiTable.BorderStyle = System.Windows.Forms.BorderStyle.None;
            dataGridViewCellStyle4.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle4.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle4.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle4.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle4.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle4.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.asciiTable.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle4;
            this.asciiTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle5.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle5.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle5.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle5.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle5.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle5.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.asciiTable.DefaultCellStyle = dataGridViewCellStyle5;
            this.asciiTable.Dock = System.Windows.Forms.DockStyle.Fill;
            this.asciiTable.GridColor = System.Drawing.SystemColors.Control;
            this.asciiTable.Location = new System.Drawing.Point(0, 0);
            this.asciiTable.Margin = new System.Windows.Forms.Padding(4);
            this.asciiTable.MultiSelect = false;
            this.asciiTable.Name = "asciiTable";
            dataGridViewCellStyle6.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle6.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle6.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle6.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle6.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle6.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle6.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.asciiTable.RowHeadersDefaultCellStyle = dataGridViewCellStyle6;
            this.asciiTable.RowHeadersWidth = 20;
            this.asciiTable.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.asciiTable.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.asciiTable.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect;
            this.asciiTable.Size = new System.Drawing.Size(515, 627);
            this.asciiTable.TabIndex = 1;
            this.asciiTable.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.showPanelifRegPressed_AsciiClick);
            this.asciiTable.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.checkAndSetChangeOnAsciiTable_List);
            this.asciiTable.CurrentCellChanged += new System.EventHandler(this.selectCellOnAsciiTable);
            this.asciiTable.EditingControlShowing += new System.Windows.Forms.DataGridViewEditingControlShowingEventHandler(this.moveToNextCellOnAsciiTable);
            this.asciiTable.Scroll += new System.Windows.Forms.ScrollEventHandler(this.scrollHexaAsAsciiTable);
            this.asciiTable.KeyDown += new System.Windows.Forms.KeyEventHandler(this.setCellToZero);
            // 
            // navBarStripContainer
            // 
            // 
            // navBarStripContainer.BottomToolStripPanel
            // 
            this.navBarStripContainer.BottomToolStripPanel.Controls.Add(this.statusStrip1);
            // 
            // navBarStripContainer.ContentPanel
            // 
            this.navBarStripContainer.ContentPanel.AutoScroll = true;
            this.navBarStripContainer.ContentPanel.Controls.Add(this.rightContainer);
            this.navBarStripContainer.ContentPanel.Margin = new System.Windows.Forms.Padding(4);
            this.navBarStripContainer.ContentPanel.Size = new System.Drawing.Size(1576, 631);
            this.navBarStripContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.navBarStripContainer.LeftToolStripPanelVisible = false;
            this.navBarStripContainer.Location = new System.Drawing.Point(0, 0);
            this.navBarStripContainer.Margin = new System.Windows.Forms.Padding(4);
            this.navBarStripContainer.Name = "navBarStripContainer";
            this.navBarStripContainer.RightToolStripPanelVisible = false;
            this.navBarStripContainer.Size = new System.Drawing.Size(1576, 692);
            this.navBarStripContainer.TabIndex = 3;
            this.navBarStripContainer.Text = "toolStripContainer1";
            // 
            // navBarStripContainer.TopToolStripPanel
            // 
            this.navBarStripContainer.TopToolStripPanel.Controls.Add(this.files_navBarStrip);
            this.navBarStripContainer.TopToolStripPanel.Controls.Add(this.address_navBarStrip);
            this.navBarStripContainer.TopToolStripPanel.Controls.Add(this.actions_navBarStrip);
            this.navBarStripContainer.TopToolStripPanel.Controls.Add(this.devType_navBarStrip);
            this.navBarStripContainer.TopToolStripPanel.Controls.Add(this.misc_navBarStrip);
            this.navBarStripContainer.TopToolStripPanel.MaximumSize = new System.Drawing.Size(0, 37);
            this.navBarStripContainer.TopToolStripPanel.MinimumSize = new System.Drawing.Size(0, 37);
            // 
            // files_navBarStrip
            // 
            this.files_navBarStrip.AutoSize = false;
            this.files_navBarStrip.Dock = System.Windows.Forms.DockStyle.None;
            this.files_navBarStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.files_navBarStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.saveFile_Btn,
            this.openFile_Btn});
            this.files_navBarStrip.Location = new System.Drawing.Point(3, 0);
            this.files_navBarStrip.MinimumSize = new System.Drawing.Size(72, 36);
            this.files_navBarStrip.Name = "files_navBarStrip";
            this.files_navBarStrip.Size = new System.Drawing.Size(72, 36);
            this.files_navBarStrip.TabIndex = 0;
            this.files_navBarStrip.TabStop = true;
            // 
            // saveFile_Btn
            // 
            this.saveFile_Btn.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.saveFile_Btn.AutoSize = false;
            this.saveFile_Btn.AutoToolTip = false;
            this.saveFile_Btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.saveFile_Btn.Image = ((System.Drawing.Image)(resources.GetObject("saveFile_Btn.Image")));
            this.saveFile_Btn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.saveFile_Btn.Name = "saveFile_Btn";
            this.saveFile_Btn.Size = new System.Drawing.Size(24, 24);
            this.saveFile_Btn.Text = "toolStripButton1";
            this.saveFile_Btn.Click += new System.EventHandler(this.save);
            // 
            // openFile_Btn
            // 
            this.openFile_Btn.AutoSize = false;
            this.openFile_Btn.AutoToolTip = false;
            this.openFile_Btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.openFile_Btn.Image = ((System.Drawing.Image)(resources.GetObject("openFile_Btn.Image")));
            this.openFile_Btn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.openFile_Btn.Name = "openFile_Btn";
            this.openFile_Btn.Size = new System.Drawing.Size(24, 24);
            this.openFile_Btn.Text = "toolStripButton2";
            this.openFile_Btn.Click += new System.EventHandler(this.openHexFile);
            // 
            // address_navBarStrip
            // 
            this.address_navBarStrip.Dock = System.Windows.Forms.DockStyle.None;
            this.address_navBarStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.address_navBarStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.i2cAddressAdd_Btn,
            this.toolStripSeparator1,
            this.scan_Btn});
            this.address_navBarStrip.Location = new System.Drawing.Point(75, 0);
            this.address_navBarStrip.MinimumSize = new System.Drawing.Size(0, 38);
            this.address_navBarStrip.Name = "address_navBarStrip";
            this.address_navBarStrip.ShowItemToolTips = false;
            this.address_navBarStrip.Size = new System.Drawing.Size(151, 38);
            this.address_navBarStrip.TabIndex = 70;
            this.address_navBarStrip.Text = "I²C Address";
            // 
            // i2cAddressAdd_Btn
            // 
            this.i2cAddressAdd_Btn.BackColor = System.Drawing.Color.Gainsboro;
            this.i2cAddressAdd_Btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.i2cAddressAdd_Btn.Image = ((System.Drawing.Image)(resources.GetObject("i2cAddressAdd_Btn.Image")));
            this.i2cAddressAdd_Btn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.i2cAddressAdd_Btn.Name = "i2cAddressAdd_Btn";
            this.i2cAddressAdd_Btn.Size = new System.Drawing.Size(89, 35);
            this.i2cAddressAdd_Btn.Text = "I²C Address";
            this.i2cAddressAdd_Btn.ToolTipText = "I²C Address";
            this.i2cAddressAdd_Btn.Click += new System.EventHandler(this.i2cAddressAdd_Btn_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 38);
            // 
            // scan_Btn
            // 
            this.scan_Btn.BackColor = System.Drawing.Color.Gainsboro;
            this.scan_Btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.scan_Btn.Image = ((System.Drawing.Image)(resources.GetObject("scan_Btn.Image")));
            this.scan_Btn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.scan_Btn.Name = "scan_Btn";
            this.scan_Btn.Size = new System.Drawing.Size(44, 35);
            this.scan_Btn.Text = "Scan";
            this.scan_Btn.Click += new System.EventHandler(this.addressScan_Click);
            // 
            // actions_navBarStrip
            // 
            this.actions_navBarStrip.AllowMerge = false;
            this.actions_navBarStrip.Dock = System.Windows.Forms.DockStyle.None;
            this.actions_navBarStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.actions_navBarStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.writeBlock_Btn,
            this.toolStripSeparator2,
            this.readBlock_Btn,
            this.toolStripSeparator3,
            this.writeAll_Btn,
            this.toolStripSeparator4,
            this.readAll_Btn,
            this.toolStripSeparator5,
            this.writeNdef_Btn,
            this.toolStripSeparator6,
            this.reset_Btn});
            this.actions_navBarStrip.Location = new System.Drawing.Point(226, 0);
            this.actions_navBarStrip.MinimumSize = new System.Drawing.Size(400, 38);
            this.actions_navBarStrip.Name = "actions_navBarStrip";
            this.actions_navBarStrip.ShowItemToolTips = false;
            this.actions_navBarStrip.Size = new System.Drawing.Size(497, 38);
            this.actions_navBarStrip.TabIndex = 1;
            // 
            // writeBlock_Btn
            // 
            this.writeBlock_Btn.BackColor = System.Drawing.Color.Gainsboro;
            this.writeBlock_Btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.writeBlock_Btn.Image = ((System.Drawing.Image)(resources.GetObject("writeBlock_Btn.Image")));
            this.writeBlock_Btn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.writeBlock_Btn.Name = "writeBlock_Btn";
            this.writeBlock_Btn.Size = new System.Drawing.Size(89, 35);
            this.writeBlock_Btn.Text = "Write Block";
            this.writeBlock_Btn.Click += new System.EventHandler(this.writeBlock_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 38);
            // 
            // readBlock_Btn
            // 
            this.readBlock_Btn.BackColor = System.Drawing.Color.Gainsboro;
            this.readBlock_Btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.readBlock_Btn.Image = ((System.Drawing.Image)(resources.GetObject("readBlock_Btn.Image")));
            this.readBlock_Btn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.readBlock_Btn.Name = "readBlock_Btn";
            this.readBlock_Btn.Size = new System.Drawing.Size(87, 35);
            this.readBlock_Btn.Text = "Read Block";
            this.readBlock_Btn.Click += new System.EventHandler(this.readBlock_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 38);
            // 
            // writeAll_Btn
            // 
            this.writeAll_Btn.BackColor = System.Drawing.Color.Gainsboro;
            this.writeAll_Btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.writeAll_Btn.Image = ((System.Drawing.Image)(resources.GetObject("writeAll_Btn.Image")));
            this.writeAll_Btn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.writeAll_Btn.Name = "writeAll_Btn";
            this.writeAll_Btn.Size = new System.Drawing.Size(71, 35);
            this.writeAll_Btn.Text = "Write All";
            this.writeAll_Btn.Click += new System.EventHandler(this.writeAllMemory_Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(6, 38);
            // 
            // readAll_Btn
            // 
            this.readAll_Btn.BackColor = System.Drawing.Color.Gainsboro;
            this.readAll_Btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.readAll_Btn.Image = ((System.Drawing.Image)(resources.GetObject("readAll_Btn.Image")));
            this.readAll_Btn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.readAll_Btn.Name = "readAll_Btn";
            this.readAll_Btn.Size = new System.Drawing.Size(69, 35);
            this.readAll_Btn.Text = "Read All";
            this.readAll_Btn.Click += new System.EventHandler(this.readAllMemory_Click);
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(6, 38);
            // 
            // writeNdef_Btn
            // 
            this.writeNdef_Btn.BackColor = System.Drawing.Color.Gainsboro;
            this.writeNdef_Btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.writeNdef_Btn.Image = ((System.Drawing.Image)(resources.GetObject("writeNdef_Btn.Image")));
            this.writeNdef_Btn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.writeNdef_Btn.Name = "writeNdef_Btn";
            this.writeNdef_Btn.Size = new System.Drawing.Size(90, 35);
            this.writeNdef_Btn.Text = "Write NDEF";
            this.writeNdef_Btn.Click += new System.EventHandler(this.writeNDefButton_Click);
            // 
            // toolStripSeparator6
            // 
            this.toolStripSeparator6.Name = "toolStripSeparator6";
            this.toolStripSeparator6.Size = new System.Drawing.Size(6, 38);
            // 
            // reset_Btn
            // 
            this.reset_Btn.BackColor = System.Drawing.Color.Gainsboro;
            this.reset_Btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.reset_Btn.Image = ((System.Drawing.Image)(resources.GetObject("reset_Btn.Image")));
            this.reset_Btn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.reset_Btn.Name = "reset_Btn";
            this.reset_Btn.Size = new System.Drawing.Size(49, 35);
            this.reset_Btn.Text = "Reset";
            this.reset_Btn.Click += new System.EventHandler(this.resetToDefaultValue_Click);
            // 
            // devType_navBarStrip
            // 
            this.devType_navBarStrip.Dock = System.Windows.Forms.DockStyle.None;
            this.devType_navBarStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.devType_navBarStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.deviceTypeLabel,
            this.tagTypeComboBox});
            this.devType_navBarStrip.Location = new System.Drawing.Point(723, 0);
            this.devType_navBarStrip.MaximumSize = new System.Drawing.Size(240, 0);
            this.devType_navBarStrip.MinimumSize = new System.Drawing.Size(290, 38);
            this.devType_navBarStrip.Name = "devType_navBarStrip";
            this.devType_navBarStrip.ShowItemToolTips = false;
            this.devType_navBarStrip.Size = new System.Drawing.Size(290, 38);
            this.devType_navBarStrip.TabIndex = 60;
            // 
            // deviceTypeLabel
            // 
            this.deviceTypeLabel.Name = "deviceTypeLabel";
            this.deviceTypeLabel.Size = new System.Drawing.Size(90, 35);
            this.deviceTypeLabel.Text = "Device Type";
            // 
            // tagTypeComboBox
            // 
            this.tagTypeComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.tagTypeComboBox.DropDownWidth = 112;
            this.tagTypeComboBox.Items.AddRange(new object[] {
            "NT3H1101 (1 kB)",
            "NT3H1201 (2 kB)",
            "NT3H2111 (1 kB Plus)",
            "NT3H2211 (2 kB Plus)"});
            this.tagTypeComboBox.Name = "tagTypeComboBox";
            this.tagTypeComboBox.Size = new System.Drawing.Size(170, 38);
            this.tagTypeComboBox.SelectedIndexChanged += new System.EventHandler(this.changeNtagType_Listener);
            // 
            // misc_navBarStrip
            // 
            this.misc_navBarStrip.Dock = System.Windows.Forms.DockStyle.None;
            this.misc_navBarStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.misc_navBarStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.changeBusSpeed_Combo,
            this.info_Btn});
            this.misc_navBarStrip.Location = new System.Drawing.Point(1013, 0);
            this.misc_navBarStrip.MinimumSize = new System.Drawing.Size(120, 38);
            this.misc_navBarStrip.Name = "misc_navBarStrip";
            this.misc_navBarStrip.ShowItemToolTips = false;
            this.misc_navBarStrip.Size = new System.Drawing.Size(120, 38);
            this.misc_navBarStrip.TabIndex = 99;
            // 
            // changeBusSpeed_Combo
            // 
            this.changeBusSpeed_Combo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.changeBusSpeed_Combo.Items.AddRange(new object[] {
            "10 kHz",
            "25 kHz",
            "50 kHz",
            "100 kHz",
            "200 kHz",
            "400 kHz"});
            this.changeBusSpeed_Combo.Name = "changeBusSpeed_Combo";
            this.changeBusSpeed_Combo.Size = new System.Drawing.Size(80, 38);
            this.changeBusSpeed_Combo.SelectedIndexChanged += new System.EventHandler(this.changeBusSpeed_Listener);
            // 
            // info_Btn
            // 
            this.info_Btn.AutoSize = false;
            this.info_Btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.info_Btn.Image = ((System.Drawing.Image)(resources.GetObject("info_Btn.Image")));
            this.info_Btn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.info_Btn.Name = "info_Btn";
            this.info_Btn.Size = new System.Drawing.Size(23, 35);
            this.info_Btn.Text = "toolStripButton10";
            this.info_Btn.Click += new System.EventHandler(this.showAboutForm_Click);
            // 
            // i2cAddressInput
            // 
            this.i2cAddressInput.AutoSize = false;
            this.i2cAddressInput.Enabled = false;
            this.i2cAddressInput.Name = "i2cAddressInput";
            this.i2cAddressInput.Size = new System.Drawing.Size(25, 38);
            this.i2cAddressInput.Text = "AA";
            // 
            // addressLock_Btn
            // 
            this.addressLock_Btn.BackColor = System.Drawing.Color.Gold;
            this.addressLock_Btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.addressLock_Btn.Image = ((System.Drawing.Image)(resources.GetObject("addressLock_Btn.Image")));
            this.addressLock_Btn.ImageTransparentColor = System.Drawing.SystemColors.Control;
            this.addressLock_Btn.Name = "addressLock_Btn";
            this.addressLock_Btn.Size = new System.Drawing.Size(24, 35);
            this.addressLock_Btn.Text = "toolStripButton8";
            this.addressLock_Btn.Click += new System.EventHandler(this.lockButton_Click);
            // 
            // checkDevtimer
            // 
            this.checkDevtimer.Interval = 500;
            this.checkDevtimer.Tick += new System.EventHandler(this.checkDevicePresence_Tick);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.DefaultExt = "hex";
            this.openFileDialog1.Filter = ".hex files|*.hex|All files|*.*";
            this.openFileDialog1.Title = "Open NTAG data file";
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.DefaultExt = "hex";
            this.saveFileDialog1.Filter = ".hex files|*.hex|All files|*.*";
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(1576, 692);
            this.Controls.Add(this.navBarStripContainer);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(1594, 1090);
            this.MinimumSize = new System.Drawing.Size(1594, 721);
            this.Name = "MainWindow";
            this.Text = "NTAG I²C Explorer - Peek and Poke Utility";
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.rightContainer.Panel1.ResumeLayout(false);
            this.rightContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.rightContainer)).EndInit();
            this.rightContainer.ResumeLayout(false);
            this.leftContainer.Panel1.ResumeLayout(false);
            this.leftContainer.Panel2.ResumeLayout(false);
            this.leftContainer.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.leftContainer)).EndInit();
            this.leftContainer.ResumeLayout(false);
            this.regBtnsPanel.ResumeLayout(false);
            this.loggingPanel.ResumeLayout(false);
            this.memTablesContainer.Panel1.ResumeLayout(false);
            this.memTablesContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.memTablesContainer)).EndInit();
            this.memTablesContainer.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.hexaTable)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.asciiTable)).EndInit();
            this.navBarStripContainer.BottomToolStripPanel.ResumeLayout(false);
            this.navBarStripContainer.BottomToolStripPanel.PerformLayout();
            this.navBarStripContainer.ContentPanel.ResumeLayout(false);
            this.navBarStripContainer.TopToolStripPanel.ResumeLayout(false);
            this.navBarStripContainer.TopToolStripPanel.PerformLayout();
            this.navBarStripContainer.ResumeLayout(false);
            this.navBarStripContainer.PerformLayout();
            this.files_navBarStrip.ResumeLayout(false);
            this.files_navBarStrip.PerformLayout();
            this.address_navBarStrip.ResumeLayout(false);
            this.address_navBarStrip.PerformLayout();
            this.actions_navBarStrip.ResumeLayout(false);
            this.actions_navBarStrip.PerformLayout();
            this.devType_navBarStrip.ResumeLayout(false);
            this.devType_navBarStrip.PerformLayout();
            this.misc_navBarStrip.ResumeLayout(false);
            this.misc_navBarStrip.PerformLayout();
            this.ResumeLayout(false);

        }      

    #endregion

            private System.Windows.Forms.StatusStrip statusStrip1;
            private System.Windows.Forms.ToolStripStatusLabel operationsStatus_Label;
            private System.Windows.Forms.ToolStripStatusLabel deviceStatus_Label;
            private System.Windows.Forms.ToolStripStatusLabel flagStatus_Label;
            private System.Windows.Forms.ToolStripStatusLabel fwVersion_Label;
            private System.Windows.Forms.SplitContainer rightContainer;
            private System.Windows.Forms.SplitContainer memTablesContainer;
            private System.Windows.Forms.DataGridView hexaTable;
            private System.Windows.Forms.DataGridView asciiTable;
            private System.Windows.Forms.ToolStripContainer navBarStripContainer;
            private System.Windows.Forms.ToolStrip files_navBarStrip;
            private System.Windows.Forms.ToolStripButton saveFile_Btn;
            private System.Windows.Forms.ToolStripButton openFile_Btn;
            private System.Windows.Forms.ToolStrip actions_navBarStrip;
            private System.Windows.Forms.ToolStripButton writeBlock_Btn;
            private System.Windows.Forms.ToolStripButton readBlock_Btn;
            private System.Windows.Forms.ToolStripButton writeAll_Btn;
            private System.Windows.Forms.ToolStripButton readAll_Btn;
            private System.Windows.Forms.ToolStripButton reset_Btn;
            private System.Windows.Forms.ToolStrip devType_navBarStrip;
            private System.Windows.Forms.ToolStripLabel deviceTypeLabel;
            private System.Windows.Forms.ToolStripComboBox tagTypeComboBox;
            private System.Windows.Forms.ToolStrip address_navBarStrip;
            private System.Windows.Forms.ToolStripTextBox i2cAddressInput;
            private System.Windows.Forms.ToolStripButton addressLock_Btn;
            private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
            private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
            private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
            private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
            private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
            private System.Windows.Forms.ToolStripSeparator toolStripSeparator6;
            private System.Windows.Forms.ToolStripButton scan_Btn;
            private System.Windows.Forms.ToolStrip misc_navBarStrip;
            private System.Windows.Forms.ToolStripComboBox changeBusSpeed_Combo;
            private System.Windows.Forms.ToolStripButton info_Btn;
            private System.Windows.Forms.SplitContainer leftContainer;
            private System.Windows.Forms.CheckBox usbLogging_ChckBox;
            private System.Windows.Forms.Panel loggingPanel;
            private System.Windows.Forms.Button clearLogging_Btn;
            private System.Windows.Forms.Label loggingText;
            private System.Windows.Forms.Label label2;
            private System.Windows.Forms.Panel regBtnsPanel;
            private System.Windows.Forms.Button configReg_Btn;
            private System.Windows.Forms.Button sessionReg_Btn;
            private System.Windows.Forms.Timer checkDevtimer;
            private System.Windows.Forms.TreeView memoryTreeView;
            private System.Windows.Forms.ToolStripButton writeNdef_Btn;
            private System.Windows.Forms.OpenFileDialog openFileDialog1;
            private System.Windows.Forms.SaveFileDialog saveFileDialog1;
            private System.Windows.Forms.ToolStripButton i2cAddressAdd_Btn;
            private System.Windows.Forms.Button accessReg_Btn;
    }
}

