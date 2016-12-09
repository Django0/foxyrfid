#pragma once

namespace NTAG_I2C_Demo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ConfigRegForm
	/// </summary>
	public ref class ConfigRegForm : public System::Windows::Forms::Form
	{
	public:
		ConfigRegForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->grackButton1->isActive = true;
			this->label1->Hide();
			this->label2->Hide();
			this->comboBox1->Hide();
			this->comboBox2->Hide();
			this->grackButton3->Hide();
			this->grackButton4->Hide();
			this->grackButton5->Hide();
			this->textBox3->Hide();
			this->grackButton6->Hide();
			this->textBox4->Hide();
			this->textBox5->Hide();
			this->textBox6->Hide();
			this->grackButton7->Hide();
			this->grackButton8->Hide();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ConfigRegForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: NTAG_I2C_Demo::GrackButton^  grackButton1;
	private: NTAG_I2C_Demo::GrackButton^  grackButton2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::TreeView^  treeView1;
	private: System::Windows::Forms::Panel^  panel2;

	private: System::Windows::Forms::Label^  label1;



	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox6;


	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox4;

	private: System::Windows::Forms::TextBox^  textBox3;


	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: NTAG_I2C_Demo::GrackButton^  grackButton3;
	private: NTAG_I2C_Demo::GrackButton^  grackButton4;
	private: NTAG_I2C_Demo::GrackButton^  grackButton6;
	private: NTAG_I2C_Demo::GrackButton^  grackButton5;
	private: NTAG_I2C_Demo::GrackButton^  grackButton8;
	private: NTAG_I2C_Demo::GrackButton^  grackButton7;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ConfigRegForm::typeid));
			System::Windows::Forms::TreeNode^  treeNode1 = (gcnew System::Windows::Forms::TreeNode(L"IC Product:"));
			System::Windows::Forms::TreeNode^  treeNode2 = (gcnew System::Windows::Forms::TreeNode(L"User memory:"));
			System::Windows::Forms::TreeNode^  treeNode3 = (gcnew System::Windows::Forms::TreeNode(L"GENERAL CHIP INFORMATION", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {
				treeNode1,
					treeNode2
			}));
			System::Windows::Forms::TreeNode^  treeNode4 = (gcnew System::Windows::Forms::TreeNode(L"FD_OFF is:"));
			System::Windows::Forms::TreeNode^  treeNode5 = (gcnew System::Windows::Forms::TreeNode(L"FD_ON is:"));
			System::Windows::Forms::TreeNode^  treeNode6 = (gcnew System::Windows::Forms::TreeNode(L"FIELD DETECTION", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {
				treeNode4,
					treeNode5
			}));
			System::Windows::Forms::TreeNode^  treeNode7 = (gcnew System::Windows::Forms::TreeNode(L"Functionality is:"));
			System::Windows::Forms::TreeNode^  treeNode8 = (gcnew System::Windows::Forms::TreeNode(L"Direction:"));
			System::Windows::Forms::TreeNode^  treeNode9 = (gcnew System::Windows::Forms::TreeNode(L"Write from RF is:"));
			System::Windows::Forms::TreeNode^  treeNode10 = (gcnew System::Windows::Forms::TreeNode(L"PASS THROUGH", gcnew cli::array< System::Windows::Forms::TreeNode^  >(3) {
				treeNode7,
					treeNode8, treeNode9
			}));
			System::Windows::Forms::TreeNode^  treeNode11 = (gcnew System::Windows::Forms::TreeNode(L"Last NDEF Page is:"));
			System::Windows::Forms::TreeNode^  treeNode12 = (gcnew System::Windows::Forms::TreeNode(L"SRAM Mirror is:"));
			System::Windows::Forms::TreeNode^  treeNode13 = (gcnew System::Windows::Forms::TreeNode(L"SRAM Mirror Block is:"));
			System::Windows::Forms::TreeNode^  treeNode14 = (gcnew System::Windows::Forms::TreeNode(L"SRAM EEPROM SETTINGS", gcnew cli::array< System::Windows::Forms::TreeNode^  >(3) {
				treeNode11,
					treeNode12, treeNode13
			}));
			System::Windows::Forms::TreeNode^  treeNode15 = (gcnew System::Windows::Forms::TreeNode(L"WD_LS Timer is:"));
			System::Windows::Forms::TreeNode^  treeNode16 = (gcnew System::Windows::Forms::TreeNode(L"WD_MS Timer is:"));
			System::Windows::Forms::TreeNode^  treeNode17 = (gcnew System::Windows::Forms::TreeNode(L"I2C Clock stretch is:"));
			System::Windows::Forms::TreeNode^  treeNode18 = (gcnew System::Windows::Forms::TreeNode(L"I2C RST on start is:"));
			System::Windows::Forms::TreeNode^  treeNode19 = (gcnew System::Windows::Forms::TreeNode(L"I2C SETTINGS", gcnew cli::array< System::Windows::Forms::TreeNode^  >(4) {
				treeNode15,
					treeNode16, treeNode17, treeNode18
			}));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->grackButton2 = (gcnew NTAG_I2C_Demo::GrackButton());
			this->grackButton1 = (gcnew NTAG_I2C_Demo::GrackButton());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->grackButton8 = (gcnew NTAG_I2C_Demo::GrackButton());
			this->grackButton7 = (gcnew NTAG_I2C_Demo::GrackButton());
			this->grackButton6 = (gcnew NTAG_I2C_Demo::GrackButton());
			this->grackButton5 = (gcnew NTAG_I2C_Demo::GrackButton());
			this->grackButton4 = (gcnew NTAG_I2C_Demo::GrackButton());
			this->grackButton3 = (gcnew NTAG_I2C_Demo::GrackButton());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->panel1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->panel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->groupBox1);
			this->panel1->Controls->Add(this->groupBox2);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(284, 457);
			this->panel1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(104, 408);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(71, 43);
			this->button1->TabIndex = 1;
			this->button1->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->grackButton2);
			this->groupBox1->Controls->Add(this->grackButton1);
			this->groupBox1->Location = System::Drawing::Point(6, 0);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(273, 65);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			// 
			// grackButton2
			// 
			this->grackButton2->Font = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold));
			this->grackButton2->ForeColor = System::Drawing::Color::White;
			this->grackButton2->Location = System::Drawing::Point(142, 14);
			this->grackButton2->Name = L"grackButton2";
			this->grackButton2->Size = System::Drawing::Size(119, 42);
			this->grackButton2->TabIndex = 1;
			this->grackButton2->Text = L"Write Config";
			this->grackButton2->UseVisualStyleBackColor = true;
			this->grackButton2->Click += gcnew System::EventHandler(this, &ConfigRegForm::grackButton2_Click);
			// 
			// grackButton1
			// 
			this->grackButton1->Font = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold));
			this->grackButton1->ForeColor = System::Drawing::Color::White;
			this->grackButton1->Location = System::Drawing::Point(11, 14);
			this->grackButton1->Name = L"grackButton1";
			this->grackButton1->Size = System::Drawing::Size(119, 42);
			this->grackButton1->TabIndex = 0;
			this->grackButton1->Text = L"Read Config";
			this->grackButton1->UseVisualStyleBackColor = true;
			this->grackButton1->Click += gcnew System::EventHandler(this, &ConfigRegForm::grackButton1_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->panel2);
			this->groupBox2->Location = System::Drawing::Point(5, 66);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(273, 341);
			this->groupBox2->TabIndex = 2;
			this->groupBox2->TabStop = false;
			// 
			// panel2
			// 
			this->panel2->AutoScroll = true;
			this->panel2->BackColor = System::Drawing::Color::Transparent;
			this->panel2->Controls->Add(this->grackButton8);
			this->panel2->Controls->Add(this->grackButton7);
			this->panel2->Controls->Add(this->grackButton6);
			this->panel2->Controls->Add(this->grackButton5);
			this->panel2->Controls->Add(this->grackButton4);
			this->panel2->Controls->Add(this->grackButton3);
			this->panel2->Controls->Add(this->comboBox2);
			this->panel2->Controls->Add(this->comboBox1);
			this->panel2->Controls->Add(this->textBox6);
			this->panel2->Controls->Add(this->textBox5);
			this->panel2->Controls->Add(this->textBox4);
			this->panel2->Controls->Add(this->textBox3);
			this->panel2->Controls->Add(this->label2);
			this->panel2->Controls->Add(this->label1);
			this->panel2->Controls->Add(this->treeView1);
			this->panel2->Location = System::Drawing::Point(1, 16);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(272, 315);
			this->panel2->TabIndex = 1;
			// 
			// grackButton8
			// 
			this->grackButton8->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->grackButton8->ForeColor = System::Drawing::Color::White;
			this->grackButton8->Location = System::Drawing::Point(210, 260);
			this->grackButton8->Name = L"grackButton8";
			this->grackButton8->Size = System::Drawing::Size(43, 17);
			this->grackButton8->TabIndex = 22;
			this->grackButton8->Text = L"grackButton8";
			this->grackButton8->UseVisualStyleBackColor = true;
			this->grackButton8->Click += gcnew System::EventHandler(this, &ConfigRegForm::grackButton8_Click);
			// 
			// grackButton7
			// 
			this->grackButton7->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->grackButton7->ForeColor = System::Drawing::Color::White;
			this->grackButton7->Location = System::Drawing::Point(210, 237);
			this->grackButton7->Name = L"grackButton7";
			this->grackButton7->Size = System::Drawing::Size(43, 17);
			this->grackButton7->TabIndex = 21;
			this->grackButton7->Text = L"grackButton7";
			this->grackButton7->UseVisualStyleBackColor = true;
			this->grackButton7->Click += gcnew System::EventHandler(this, &ConfigRegForm::grackButton7_Click);
			// 
			// grackButton6
			// 
			this->grackButton6->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->grackButton6->ForeColor = System::Drawing::Color::White;
			this->grackButton6->Location = System::Drawing::Point(210, 158);
			this->grackButton6->Name = L"grackButton6";
			this->grackButton6->Size = System::Drawing::Size(43, 17);
			this->grackButton6->TabIndex = 20;
			this->grackButton6->Text = L"grackButton6";
			this->grackButton6->UseVisualStyleBackColor = true;
			this->grackButton6->Click += gcnew System::EventHandler(this, &ConfigRegForm::grackButton6_Click);
			// 
			// grackButton5
			// 
			this->grackButton5->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->grackButton5->ForeColor = System::Drawing::Color::White;
			this->grackButton5->Location = System::Drawing::Point(210, 110);
			this->grackButton5->Name = L"grackButton5";
			this->grackButton5->Size = System::Drawing::Size(43, 17);
			this->grackButton5->TabIndex = 19;
			this->grackButton5->Text = L"grackButton5";
			this->grackButton5->UseVisualStyleBackColor = true;
			this->grackButton5->Click += gcnew System::EventHandler(this, &ConfigRegForm::grackButton5_Click);
			// 
			// grackButton4
			// 
			this->grackButton4->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->grackButton4->ForeColor = System::Drawing::Color::White;
			this->grackButton4->Location = System::Drawing::Point(177, 87);
			this->grackButton4->Name = L"grackButton4";
			this->grackButton4->Size = System::Drawing::Size(76, 17);
			this->grackButton4->TabIndex = 18;
			this->grackButton4->Text = L"grackButton4";
			this->grackButton4->UseVisualStyleBackColor = true;
			this->grackButton4->Click += gcnew System::EventHandler(this, &ConfigRegForm::grackButton4_Click);
			// 
			// grackButton3
			// 
			this->grackButton3->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->grackButton3->ForeColor = System::Drawing::Color::White;
			this->grackButton3->Location = System::Drawing::Point(210, 63);
			this->grackButton3->Name = L"grackButton3";
			this->grackButton3->Size = System::Drawing::Size(43, 17);
			this->grackButton3->TabIndex = 17;
			this->grackButton3->Text = L"grackButton3";
			this->grackButton3->UseVisualStyleBackColor = true;
			this->grackButton3->Click += gcnew System::EventHandler(this, &ConfigRegForm::grackButton3_Click);
			// 
			// comboBox2
			// 
			this->comboBox2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->comboBox2->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"00b - field switched on", L"01b - first valid Start-of-Frame",
					L"10b - selection of Tag", L"11b - data is ready to read from I2C / data is read by RF"
			});
			this->comboBox2->Location = System::Drawing::Point(107, 44);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(147, 23);
			this->comboBox2->TabIndex = 16;
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"00b - field switched off", L"01b - field switched off or set to HALT",
					L"10b - field switched off or LAST_NDEF_PAGE read", L"11b - field switched of or Data is read/written by I2C"
			});
			this->comboBox1->Location = System::Drawing::Point(107, 24);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(147, 23);
			this->comboBox1->TabIndex = 15;
			// 
			// textBox6
			// 
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox6->Location = System::Drawing::Point(187, 209);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(68, 22);
			this->textBox6->TabIndex = 14;
			// 
			// textBox5
			// 
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox5->Location = System::Drawing::Point(187, 191);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(68, 22);
			this->textBox5->TabIndex = 11;
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox4->Location = System::Drawing::Point(187, 176);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(68, 22);
			this->textBox4->TabIndex = 10;
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(187, 135);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(68, 22);
			this->textBox3->TabIndex = 8;
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(134, 14);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(120, 18);
			this->label2->TabIndex = 2;
			this->label2->Text = L"label2";
			this->label2->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(133, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(120, 18);
			this->label1->TabIndex = 1;
			this->label1->Text = L"label1";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// treeView1
			// 
			this->treeView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->treeView1->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->treeView1->Location = System::Drawing::Point(0, 3);
			this->treeView1->Name = L"treeView1";
			treeNode1->Name = L"Node1";
			treeNode1->Text = L"IC Product:";
			treeNode2->Name = L"Node2";
			treeNode2->Text = L"User memory:";
			treeNode3->Name = L"Node0";
			treeNode3->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode3->Text = L"GENERAL CHIP INFORMATION";
			treeNode4->Name = L"Node4";
			treeNode4->Text = L"FD_OFF is:";
			treeNode5->Name = L"Node5";
			treeNode5->Text = L"FD_ON is:";
			treeNode6->Name = L"Node3";
			treeNode6->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode6->Text = L"FIELD DETECTION";
			treeNode7->Name = L"Node7";
			treeNode7->Text = L"Functionality is:";
			treeNode8->Name = L"Node8";
			treeNode8->Text = L"Direction:";
			treeNode9->Name = L"Node9";
			treeNode9->Text = L"Write from RF is:";
			treeNode10->Name = L"Node6";
			treeNode10->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode10->Text = L"PASS THROUGH";
			treeNode11->Name = L"Node11";
			treeNode11->Text = L"Last NDEF Page is:";
			treeNode12->Name = L"Node12";
			treeNode12->Text = L"SRAM Mirror is:";
			treeNode13->Name = L"Node13";
			treeNode13->Text = L"SRAM Mirror Block is:";
			treeNode14->Name = L"Node10";
			treeNode14->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode14->Text = L"SRAM EEPROM SETTINGS";
			treeNode15->Name = L"Node15";
			treeNode15->Text = L"WD_LS Timer is:";
			treeNode16->Name = L"Node16";
			treeNode16->Text = L"WD_MS Timer is:";
			treeNode17->Name = L"Node17";
			treeNode17->Text = L"I2C Clock stretch is:";
			treeNode18->Name = L"Node18";
			treeNode18->Text = L"I2C RST on start is:";
			treeNode19->Name = L"Node14";
			treeNode19->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode19->Text = L"I2C SETTINGS";
			this->treeView1->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(5) {
				treeNode3, treeNode6, treeNode10,
					treeNode14, treeNode19
			});
			this->treeView1->Scrollable = false;
			this->treeView1->Size = System::Drawing::Size(238, 251);
			this->treeView1->TabIndex = 0;
			this->treeView1->AfterCollapse += gcnew System::Windows::Forms::TreeViewEventHandler(this, &ConfigRegForm::treeView1_AfterExplapse);
			this->treeView1->AfterExpand += gcnew System::Windows::Forms::TreeViewEventHandler(this, &ConfigRegForm::treeView1_AfterExplapse);
			this->treeView1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &ConfigRegForm::treeView1_MouseWheel);
			// 
			// ConfigRegForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(284, 457);
			this->Controls->Add(this->panel1);
			this->Name = L"ConfigRegForm";
			this->Text = L"ConfigRegForm";
			this->panel1->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
		private:
			System::Void grackButton1_Click(System::Object^  sender, System::EventArgs^  e)
			{
				this->grackButton1->isActive = true;
				this->grackButton2->isActive = false;
				this->grackButton1->Refresh();
				this->grackButton2->Refresh();
			}

			System::Void grackButton2_Click(System::Object^  sender, System::EventArgs^  e)
			{
				this->grackButton1->isActive = false;
				this->grackButton2->isActive = true;
				this->grackButton1->Refresh();
				this->grackButton2->Refresh();
			}

			System::Void treeView1_AfterExplapse(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
			{
				int maxPos = this->treeView1->Nodes[4]->Bounds.Location.Y;
				if (this->treeView1->Nodes[4]->LastNode->Bounds.Location.Y != 0)
					maxPos = this->treeView1->Nodes[4]->LastNode->Bounds.Location.Y;
				this->treeView1->Size = System::Drawing::Size(this->treeView1->Size.Width, maxPos + 30);

				if (this->treeView1->Nodes[0]->Nodes[0]->IsVisible)
				{
					this->label1->Location = System::Drawing::Point(this->label1->Location.X, this->treeView1->Nodes[0]->Nodes[0]->Bounds.Location.Y + 4);
					this->label1->Show();
				}
				else
					this->label1->Hide();
				if (this->treeView1->Nodes[0]->Nodes[1]->IsVisible)
				{
					this->label2->Location = System::Drawing::Point(this->label2->Location.X, this->treeView1->Nodes[0]->Nodes[1]->Bounds.Location.Y + 4);
					this->label2->Show();
				}
				else
					this->label2->Hide();
				if (this->treeView1->Nodes[1]->Nodes[0]->IsVisible)
				{
					this->comboBox1->Location = System::Drawing::Point(this->comboBox1->Location.X, this->treeView1->Nodes[1]->Nodes[0]->Bounds.Location.Y + 1);
					this->comboBox1->Show();
				}
				else
					this->comboBox1->Hide();
				if (this->treeView1->Nodes[1]->Nodes[1]->IsVisible)
				{
					this->comboBox2->Location = System::Drawing::Point(this->comboBox2->Location.X, this->treeView1->Nodes[1]->Nodes[1]->Bounds.Location.Y + 1);
					this->comboBox2->Show();
				}
				else
					this->comboBox2->Hide();
				if (this->treeView1->Nodes[2]->Nodes[0]->IsVisible)
				{
					this->grackButton3->Location = System::Drawing::Point(this->grackButton3->Location.X, this->treeView1->Nodes[2]->Nodes[0]->Bounds.Location.Y + 4);
					this->grackButton3->Show();
				}
				else
					this->grackButton3->Hide();
				if (this->treeView1->Nodes[2]->Nodes[1]->IsVisible)
				{
					this->grackButton4->Location = System::Drawing::Point(this->grackButton4->Location.X, this->treeView1->Nodes[2]->Nodes[1]->Bounds.Location.Y + 4);
					this->grackButton4->Show();
				}
				else
					this->grackButton4->Hide();
				if (this->treeView1->Nodes[2]->Nodes[2]->IsVisible)
				{
					this->grackButton5->Location = System::Drawing::Point(this->grackButton5->Location.X, this->treeView1->Nodes[2]->Nodes[2]->Bounds.Location.Y + 4);
					this->grackButton5->Show();
				}
				else
					this->grackButton5->Hide();
				if (this->treeView1->Nodes[3]->Nodes[0]->IsVisible)
				{
					this->textBox3->Location = System::Drawing::Point(this->textBox3->Location.X, this->treeView1->Nodes[3]->Nodes[0]->Bounds.Location.Y + 0);
					this->textBox3->Show();
				}
				else
					this->textBox3->Hide();
				if (this->treeView1->Nodes[3]->Nodes[1]->IsVisible)
				{
					this->grackButton6->Location = System::Drawing::Point(this->grackButton6->Location.X, this->treeView1->Nodes[3]->Nodes[1]->Bounds.Location.Y + 4);
					this->grackButton6->Show();
				}
				else
					this->grackButton6->Hide();
				if (this->treeView1->Nodes[3]->Nodes[2]->IsVisible)
				{
					this->textBox4->Location = System::Drawing::Point(this->textBox4->Location.X, this->treeView1->Nodes[3]->Nodes[2]->Bounds.Location.Y + 3);
					this->textBox4->Show();
				}
				else
					this->textBox4->Hide();
				if (this->treeView1->Nodes[4]->Nodes[0]->IsVisible)
				{
					this->textBox5->Location = System::Drawing::Point(this->textBox5->Location.X, this->treeView1->Nodes[4]->Nodes[0]->Bounds.Location.Y + 0);
					this->textBox5->Show();
				}
				else
					this->textBox5->Hide();
				if (this->treeView1->Nodes[4]->Nodes[1]->IsVisible)
				{
					this->textBox6->Location = System::Drawing::Point(this->textBox6->Location.X, this->treeView1->Nodes[4]->Nodes[1]->Bounds.Location.Y + 0);
					this->textBox6->Show();
				}
				else
					this->textBox6->Hide();
				if (this->treeView1->Nodes[4]->Nodes[2]->IsVisible)
				{
					this->grackButton7->Location = System::Drawing::Point(this->grackButton7->Location.X, this->treeView1->Nodes[4]->Nodes[2]->Bounds.Location.Y + 4);
					this->grackButton7->Show();
				}
				else
					this->grackButton7->Hide();
				if (this->treeView1->Nodes[4]->Nodes[3]->IsVisible)
				{
					this->grackButton8->Location = System::Drawing::Point(this->grackButton8->Location.X, this->treeView1->Nodes[4]->Nodes[3]->Bounds.Location.Y + 4);
					this->grackButton8->Show();
				}
				else
					this->grackButton8->Hide();
			}

			System::Void treeView1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			{
				this->panel2->Focus();
			}

			System::Void grackButton3_Click(System::Object^  sender, System::EventArgs^  e)
			{
				if (this->grackButton3->isActive == false)
				{
					this->grackButton3->isActive = true;
					this->grackButton3->Text = "ON";
				}
				else
				{
					this->grackButton3->isActive = false;
					this->grackButton3->Text = "OFF";
				}
			}
	
			System::Void grackButton4_Click(System::Object^  sender, System::EventArgs^  e)
			{
				if (this->grackButton4->isActive == false)
				{
					this->grackButton4->isActive = true;
					this->grackButton4->Text = "RF to I2C";
				}
				else
				{
					this->grackButton4->isActive = false;
					this->grackButton4->Text = "I2C to RF";
				}
			}

			System::Void grackButton5_Click(System::Object^  sender, System::EventArgs^  e)
			{
				if (this->grackButton5->isActive == false)
				{
					this->grackButton5->isActive = true;
					this->grackButton5->Text = "ON";
				}
				else
				{
					this->grackButton5->isActive = false;
					this->grackButton5->Text = "OFF";
				}
			}

			System::Void grackButton6_Click(System::Object^  sender, System::EventArgs^  e)
			{
				if (this->grackButton6->isActive == false)
				{
					this->grackButton6->isActive = true;
					this->grackButton6->Text = "ON";
				}
				else
				{
					this->grackButton6->isActive = false;
					this->grackButton6->Text = "OFF";
				}
			}

			System::Void grackButton7_Click(System::Object^  sender, System::EventArgs^  e)
			{
				if (this->grackButton7->isActive == false)
				{
					this->grackButton7->isActive = true;
					this->grackButton7->Text = "ON";
				}
				else
				{
					this->grackButton7->isActive = false;
					this->grackButton7->Text = "OFF";
				}
			}

			System::Void grackButton8_Click(System::Object^  sender, System::EventArgs^  e)
			{
				if (this->grackButton8->isActive == false)
				{
					this->grackButton8->isActive = true;
					this->grackButton8->Text = "ON";
				}
				else
				{
					this->grackButton8->isActive = false;
					this->grackButton8->Text = "OFF";
				}
			}
};
}
