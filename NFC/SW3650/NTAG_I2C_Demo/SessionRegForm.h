#pragma once

namespace NTAG_I2C_Demo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SessionRegForm
	/// </summary>
	public ref class SessionRegForm : public System::Windows::Forms::Form
	{
	public:
		SessionRegForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->checkBox1->Hide();
			this->checkBox2->Hide();
			this->checkBox3->Hide();
			this->checkBox4->Hide();
			this->checkBox5->Hide();
			this->checkBox6->Hide();
			this->checkBox7->Hide();
			this->checkBox8->Hide();
			this->checkBox9->Hide();
			this->checkBox10->Hide();
			this->checkBox11->Hide();
			this->label1->Hide();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SessionRegForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBox1;
	protected:
	private: System::Windows::Forms::TreeView^  treeView1;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::CheckBox^  checkBox11;
	private: System::Windows::Forms::CheckBox^  checkBox10;
	private: System::Windows::Forms::CheckBox^  checkBox9;
	private: System::Windows::Forms::CheckBox^  checkBox8;
	private: System::Windows::Forms::CheckBox^  checkBox7;
	private: System::Windows::Forms::CheckBox^  checkBox6;
	private: System::Windows::Forms::CheckBox^  checkBox5;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(SessionRegForm::typeid));
			System::Windows::Forms::TreeNode^  treeNode1 = (gcnew System::Windows::Forms::TreeNode(L"IC Product:"));
			System::Windows::Forms::TreeNode^  treeNode2 = (gcnew System::Windows::Forms::TreeNode(L"User memory:"));
			System::Windows::Forms::TreeNode^  treeNode3 = (gcnew System::Windows::Forms::TreeNode(L"GENERAL CHIP INFORMATION", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {
				treeNode1,
					treeNode2
			}));
			System::Windows::Forms::TreeNode^  treeNode4 = (gcnew System::Windows::Forms::TreeNode(L"I2C RST on start is:"));
			System::Windows::Forms::TreeNode^  treeNode5 = (gcnew System::Windows::Forms::TreeNode(L"NTAG CONFIGURATION", gcnew cli::array< System::Windows::Forms::TreeNode^  >(1) { treeNode4 }));
			System::Windows::Forms::TreeNode^  treeNode6 = (gcnew System::Windows::Forms::TreeNode(L"FD_OFF is:"));
			System::Windows::Forms::TreeNode^  treeNode7 = (gcnew System::Windows::Forms::TreeNode(L"FD_ON is:"));
			System::Windows::Forms::TreeNode^  treeNode8 = (gcnew System::Windows::Forms::TreeNode(L"Last NDEF Page is:"));
			System::Windows::Forms::TreeNode^  treeNode9 = (gcnew System::Windows::Forms::TreeNode(L"NDEF Data Read is:"));
			System::Windows::Forms::TreeNode^  treeNode10 = (gcnew System::Windows::Forms::TreeNode(L"RF field present is:"));
			System::Windows::Forms::TreeNode^  treeNode11 = (gcnew System::Windows::Forms::TreeNode(L"FIELD DETECTION", gcnew cli::array< System::Windows::Forms::TreeNode^  >(5) {
				treeNode6,
					treeNode7, treeNode8, treeNode9, treeNode10
			}));
			System::Windows::Forms::TreeNode^  treeNode12 = (gcnew System::Windows::Forms::TreeNode(L"Pass Through is:"));
			System::Windows::Forms::TreeNode^  treeNode13 = (gcnew System::Windows::Forms::TreeNode(L"I2C locked is:"));
			System::Windows::Forms::TreeNode^  treeNode14 = (gcnew System::Windows::Forms::TreeNode(L"RF locked is:"));
			System::Windows::Forms::TreeNode^  treeNode15 = (gcnew System::Windows::Forms::TreeNode(L"SRAM I2C ready is:"));
			System::Windows::Forms::TreeNode^  treeNode16 = (gcnew System::Windows::Forms::TreeNode(L"SRAM RF ready is:"));
			System::Windows::Forms::TreeNode^  treeNode17 = (gcnew System::Windows::Forms::TreeNode(L"FromRF to I2C is:"));
			System::Windows::Forms::TreeNode^  treeNode18 = (gcnew System::Windows::Forms::TreeNode(L"PASS THROUGH", gcnew cli::array< System::Windows::Forms::TreeNode^  >(6) {
				treeNode12,
					treeNode13, treeNode14, treeNode15, treeNode16, treeNode17
			}));
			System::Windows::Forms::TreeNode^  treeNode19 = (gcnew System::Windows::Forms::TreeNode(L"SRAM Mirror is:"));
			System::Windows::Forms::TreeNode^  treeNode20 = (gcnew System::Windows::Forms::TreeNode(L"SRAM Mirror block is:"));
			System::Windows::Forms::TreeNode^  treeNode21 = (gcnew System::Windows::Forms::TreeNode(L"SRAM MIRROR", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {
				treeNode19,
					treeNode20
			}));
			System::Windows::Forms::TreeNode^  treeNode22 = (gcnew System::Windows::Forms::TreeNode(L"WD_LS Timer is:"));
			System::Windows::Forms::TreeNode^  treeNode23 = (gcnew System::Windows::Forms::TreeNode(L"WD_MS Timer is:"));
			System::Windows::Forms::TreeNode^  treeNode24 = (gcnew System::Windows::Forms::TreeNode(L"I2C Clock Stretch is:"));
			System::Windows::Forms::TreeNode^  treeNode25 = (gcnew System::Windows::Forms::TreeNode(L"I2C", gcnew cli::array< System::Windows::Forms::TreeNode^  >(3) {
				treeNode22,
					treeNode23, treeNode24
			}));
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->checkBox11 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox10 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox9 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox8 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox7 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->groupBox1->SuspendLayout();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Controls->Add(this->panel1);
			this->groupBox1->Location = System::Drawing::Point(6, -2);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(273, 455);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(98, 408);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(71, 43);
			this->button1->TabIndex = 2;
			this->button1->UseVisualStyleBackColor = true;
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->BackColor = System::Drawing::Color::Transparent;
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->checkBox11);
			this->panel1->Controls->Add(this->checkBox10);
			this->panel1->Controls->Add(this->checkBox9);
			this->panel1->Controls->Add(this->checkBox8);
			this->panel1->Controls->Add(this->checkBox7);
			this->panel1->Controls->Add(this->checkBox6);
			this->panel1->Controls->Add(this->checkBox5);
			this->panel1->Controls->Add(this->checkBox4);
			this->panel1->Controls->Add(this->checkBox3);
			this->panel1->Controls->Add(this->checkBox2);
			this->panel1->Controls->Add(this->checkBox1);
			this->panel1->Controls->Add(this->treeView1);
			this->panel1->Location = System::Drawing::Point(0, 16);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(273, 389);
			this->panel1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(135, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(120, 18);
			this->label1->TabIndex = 12;
			this->label1->Text = L"label1";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// checkBox11
			// 
			this->checkBox11->AutoSize = true;
			this->checkBox11->Enabled = false;
			this->checkBox11->Location = System::Drawing::Point(240, 370);
			this->checkBox11->Name = L"checkBox11";
			this->checkBox11->Size = System::Drawing::Size(15, 14);
			this->checkBox11->TabIndex = 11;
			this->checkBox11->UseVisualStyleBackColor = true;
			// 
			// checkBox10
			// 
			this->checkBox10->AutoSize = true;
			this->checkBox10->Enabled = false;
			this->checkBox10->Location = System::Drawing::Point(240, 332);
			this->checkBox10->Name = L"checkBox10";
			this->checkBox10->Size = System::Drawing::Size(15, 14);
			this->checkBox10->TabIndex = 10;
			this->checkBox10->UseVisualStyleBackColor = true;
			// 
			// checkBox9
			// 
			this->checkBox9->AutoSize = true;
			this->checkBox9->Enabled = false;
			this->checkBox9->Location = System::Drawing::Point(240, 292);
			this->checkBox9->Name = L"checkBox9";
			this->checkBox9->Size = System::Drawing::Size(15, 14);
			this->checkBox9->TabIndex = 9;
			this->checkBox9->UseVisualStyleBackColor = true;
			// 
			// checkBox8
			// 
			this->checkBox8->AutoSize = true;
			this->checkBox8->Enabled = false;
			this->checkBox8->Location = System::Drawing::Point(240, 257);
			this->checkBox8->Name = L"checkBox8";
			this->checkBox8->Size = System::Drawing::Size(15, 14);
			this->checkBox8->TabIndex = 8;
			this->checkBox8->UseVisualStyleBackColor = true;
			// 
			// checkBox7
			// 
			this->checkBox7->AutoSize = true;
			this->checkBox7->Enabled = false;
			this->checkBox7->Location = System::Drawing::Point(240, 219);
			this->checkBox7->Name = L"checkBox7";
			this->checkBox7->Size = System::Drawing::Size(15, 14);
			this->checkBox7->TabIndex = 7;
			this->checkBox7->UseVisualStyleBackColor = true;
			// 
			// checkBox6
			// 
			this->checkBox6->AutoSize = true;
			this->checkBox6->Enabled = false;
			this->checkBox6->Location = System::Drawing::Point(240, 183);
			this->checkBox6->Name = L"checkBox6";
			this->checkBox6->Size = System::Drawing::Size(15, 14);
			this->checkBox6->TabIndex = 6;
			this->checkBox6->UseVisualStyleBackColor = true;
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Enabled = false;
			this->checkBox5->Location = System::Drawing::Point(240, 151);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(15, 14);
			this->checkBox5->TabIndex = 5;
			this->checkBox5->UseVisualStyleBackColor = true;
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Enabled = false;
			this->checkBox4->Location = System::Drawing::Point(240, 120);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(15, 14);
			this->checkBox4->TabIndex = 4;
			this->checkBox4->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Enabled = false;
			this->checkBox3->Location = System::Drawing::Point(240, 89);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(15, 14);
			this->checkBox3->TabIndex = 3;
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Enabled = false;
			this->checkBox2->Location = System::Drawing::Point(240, 57);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(15, 14);
			this->checkBox2->TabIndex = 2;
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Enabled = false;
			this->checkBox1->Location = System::Drawing::Point(240, 28);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(15, 14);
			this->checkBox1->TabIndex = 1;
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// treeView1
			// 
			this->treeView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->treeView1->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->treeView1->Location = System::Drawing::Point(3, 0);
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
			treeNode4->Text = L"I2C RST on start is:";
			treeNode5->Name = L"Node3";
			treeNode5->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode5->Text = L"NTAG CONFIGURATION";
			treeNode6->Name = L"Node6";
			treeNode6->Text = L"FD_OFF is:";
			treeNode7->Name = L"Node7";
			treeNode7->Text = L"FD_ON is:";
			treeNode8->Name = L"Node8";
			treeNode8->Text = L"Last NDEF Page is:";
			treeNode9->Name = L"Node0";
			treeNode9->Text = L"NDEF Data Read is:";
			treeNode10->Name = L"Node1";
			treeNode10->Text = L"RF field present is:";
			treeNode11->Name = L"Node5";
			treeNode11->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode11->Text = L"FIELD DETECTION";
			treeNode12->Name = L"Node3";
			treeNode12->Text = L"Pass Through is:";
			treeNode13->Name = L"Node4";
			treeNode13->Text = L"I2C locked is:";
			treeNode14->Name = L"Node5";
			treeNode14->Text = L"RF locked is:";
			treeNode15->Name = L"Node6";
			treeNode15->Text = L"SRAM I2C ready is:";
			treeNode16->Name = L"Node7";
			treeNode16->Text = L"SRAM RF ready is:";
			treeNode17->Name = L"Node8";
			treeNode17->Text = L"FromRF to I2C is:";
			treeNode18->Name = L"Node2";
			treeNode18->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode18->Text = L"PASS THROUGH";
			treeNode19->Name = L"Node10";
			treeNode19->Text = L"SRAM Mirror is:";
			treeNode20->Name = L"Node11";
			treeNode20->Text = L"SRAM Mirror block is:";
			treeNode21->Name = L"Node9";
			treeNode21->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode21->Text = L"SRAM MIRROR";
			treeNode22->Name = L"Node13";
			treeNode22->Text = L"WD_LS Timer is:";
			treeNode23->Name = L"Node14";
			treeNode23->Text = L"WD_MS Timer is:";
			treeNode24->Name = L"Node15";
			treeNode24->Text = L"I2C Clock Stretch is:";
			treeNode25->Name = L"Node12";
			treeNode25->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode25->Text = L"I2C";
			this->treeView1->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(6) {
				treeNode3, treeNode5, treeNode11,
					treeNode18, treeNode21, treeNode25
			});
			this->treeView1->Scrollable = false;
			this->treeView1->ShowLines = false;
			this->treeView1->Size = System::Drawing::Size(240, 364);
			this->treeView1->TabIndex = 0;
			this->treeView1->AfterCollapse += gcnew System::Windows::Forms::TreeViewEventHandler(this, &SessionRegForm::treeView1_AfterExplapse);
			this->treeView1->AfterExpand += gcnew System::Windows::Forms::TreeViewEventHandler(this, &SessionRegForm::treeView1_AfterExplapse);
			this->treeView1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &SessionRegForm::treeView1_MouseWheel);
			// 
			// SessionRegForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(284, 457);
			this->Controls->Add(this->groupBox1);
			this->Name = L"SessionRegForm";
			this->Text = L"SessionRegForm";
			this->groupBox1->ResumeLayout(false);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
		private:
			System::Void treeView1_AfterExplapse(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
			{
				int maxPos = this->treeView1->Nodes[5]->Bounds.Location.Y;
				if (this->treeView1->Nodes[5]->LastNode->Bounds.Location.Y != 0)
					maxPos = this->treeView1->Nodes[5]->LastNode->Bounds.Location.Y;
				this->treeView1->Size = System::Drawing::Size(this->treeView1->Size.Width, maxPos + 30);
				
				if (this->treeView1->Nodes[0]->Nodes[0]->IsVisible)
				{
					this->label1->Location = System::Drawing::Point(this->label1->Location.X, this->treeView1->Nodes[0]->Nodes[0]->Bounds.Location.Y);
					this->label1->Show();
				}
				else
					this->label1->Hide();
				if (this->treeView1->Nodes[1]->Nodes[0]->IsVisible)
				{
					this->checkBox1->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[1]->Nodes[0]->Bounds.Location.Y + 4);
					this->checkBox1->Show();
				}
				else
					this->checkBox1->Hide();
				if (this->treeView1->Nodes[2]->Nodes[3]->IsVisible)
				{
					this->checkBox2->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[2]->Nodes[3]->Bounds.Location.Y + 4);
					this->checkBox2->Show();
				}
				else
					this->checkBox2->Hide();
				if (this->treeView1->Nodes[2]->Nodes[4]->IsVisible)
				{
					this->checkBox3->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[2]->Nodes[4]->Bounds.Location.Y + 4);
					this->checkBox3->Show();
				}
				else
					this->checkBox3->Hide();
				if (this->treeView1->Nodes[3]->Nodes[0]->IsVisible)
				{
					this->checkBox4->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[3]->Nodes[0]->Bounds.Location.Y + 4);
					this->checkBox4->Show();
				}
				else
					this->checkBox4->Hide();
				if (this->treeView1->Nodes[3]->Nodes[1]->IsVisible)
				{
					this->checkBox5->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[3]->Nodes[1]->Bounds.Location.Y + 4);
					this->checkBox5->Show();
				}
				else
					this->checkBox5->Hide();
				if (this->treeView1->Nodes[3]->Nodes[2]->IsVisible)
				{
					this->checkBox6->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[3]->Nodes[2]->Bounds.Location.Y + 4);
					this->checkBox6->Show();
				}
				else
					this->checkBox6->Hide();
				if (this->treeView1->Nodes[3]->Nodes[3]->IsVisible)
				{
					this->checkBox7->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[3]->Nodes[3]->Bounds.Location.Y + 4);
					this->checkBox7->Show();
				}
				else
					this->checkBox7->Hide();
				if (this->treeView1->Nodes[3]->Nodes[4]->IsVisible)
				{
					this->checkBox8->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[3]->Nodes[4]->Bounds.Location.Y + 4);
					this->checkBox8->Show();
				}
				else
					this->checkBox8->Hide();
				if (this->treeView1->Nodes[3]->Nodes[5]->IsVisible)
				{
					this->checkBox9->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[3]->Nodes[5]->Bounds.Location.Y + 4);
					this->checkBox9->Show();
				}
				else
					this->checkBox9->Hide();
				if (this->treeView1->Nodes[4]->Nodes[0]->IsVisible)
				{
					this->checkBox10->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[4]->Nodes[0]->Bounds.Location.Y + 4);
					this->checkBox10->Show();
				}
				else
					this->checkBox10->Hide();
				if (this->treeView1->Nodes[5]->Nodes[2]->IsVisible)
				{
					this->checkBox11->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[5]->Nodes[2]->Bounds.Location.Y + 4);
					this->checkBox11->Show();
				}
				else
					this->checkBox11->Hide();
			}

			System::Void treeView1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			{
				this->panel1->Focus();
			}
};
}
