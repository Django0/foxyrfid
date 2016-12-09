#include "GUI_Utils.h"
#pragma once

namespace NTAG_I2C_Demo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Password_Form
	/// </summary>
	public ref class Password_Form : public System::Windows::Forms::Form
	{
	public:
		System::String^ ReturnValue;
		System::String^ ntag_status;

		Password_Form(bool status, bool blocked)
		{
			//
			//TODO: Add the constructor code here
			//
			if ((status == true) && (blocked == true))
			{
				ntag_status = "Authenticated";
			}
			else if ((status == false) && (blocked == true))
			{
				ntag_status = "Protected";
			}
			else if ((status == false) && (blocked == false))
			{
				ntag_status = "Unprotected";
			}
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Password_Form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  labelSelectPWD;
	protected:
	private: System::Windows::Forms::Label^  labelAUTH;
	private: System::Windows::Forms::Label^  labelSTATUS;
	private: NTAG_I2C_Demo::GrackButton^  PWD_SUN;
	private: NTAG_I2C_Demo::GrackButton^  PWD_STAR;
	private: NTAG_I2C_Demo::GrackButton^  PWD_MOON;
			 
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
			this->labelSelectPWD = (gcnew System::Windows::Forms::Label());
			this->labelAUTH = (gcnew System::Windows::Forms::Label());
			this->labelSTATUS = (gcnew System::Windows::Forms::Label());
			this->PWD_SUN = (gcnew NTAG_I2C_Demo::GrackButton());
			this->PWD_STAR = (gcnew NTAG_I2C_Demo::GrackButton());
			this->PWD_MOON = (gcnew NTAG_I2C_Demo::GrackButton());
			this->SuspendLayout();
			// 
			// labelSelectPWD
			// 
			this->labelSelectPWD->Location = System::Drawing::Point(85, 27);
			this->labelSelectPWD->Name = L"labelSelectPWD";
			this->labelSelectPWD->Text = L"Select password";
			this->labelSelectPWD->Size = System::Drawing::Size(120, 22);
			this->labelSelectPWD->TabIndex = 0;
			// 
			// labelAUTH
			// 
			this->labelAUTH->Location = System::Drawing::Point(40, 280);
			this->labelAUTH->Name = L"labelAUTH";
			this->labelAUTH->Text = L"Current Authentication status";
			this->labelAUTH->Size = System::Drawing::Size(300, 22);
			this->labelAUTH->TabIndex = 1;
			// 
			// labelSTATUS
			// 
			this->labelSTATUS->Location = System::Drawing::Point(90, 300);
			this->labelSTATUS->Name = L"labelSTATUS";
			this->labelSTATUS->Text = this->ntag_status;
			this->labelSTATUS->Font = (gcnew System::Drawing::Font(L"Arial", 10.00F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelSTATUS->Size = System::Drawing::Size(120, 22);
			this->labelSTATUS->TabIndex = 2;
			// 
			// PWD_SUN
			// 
			this->PWD_SUN->Font = (gcnew System::Drawing::Font(L"Arial", 10.00F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PWD_SUN->ForeColor = System::Drawing::Color::White;
			this->PWD_SUN->Location = System::Drawing::Point(35, 70);
			this->PWD_SUN->Name = L"PWD_SUN";
			this->PWD_SUN->Size = System::Drawing::Size(220, 50);
			this->PWD_SUN->TabIndex = 1;
			this->PWD_SUN->Text = L"SUN";
			this->PWD_SUN->UseVisualStyleBackColor = true;
			this->PWD_SUN->Click += gcnew System::EventHandler(this, &Password_Form::PDW_1_Click);
			// 
			// PWD_STAR
			// 
			this->PWD_STAR->Font = (gcnew System::Drawing::Font(L"Arial", 10.00F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PWD_STAR->ForeColor = System::Drawing::Color::White;
			this->PWD_STAR->Location = System::Drawing::Point(35, 140);
			this->PWD_STAR->Name = L"PWD_STAR";
			this->PWD_STAR->Size = System::Drawing::Size(220, 50);
			this->PWD_STAR->TabIndex = 1;
			this->PWD_STAR->Text = L"STAR";
			this->PWD_STAR->UseVisualStyleBackColor = true;
			this->PWD_STAR->Click += gcnew System::EventHandler(this, &Password_Form::PDW_2_Click);
			// 
			// PWD_MOON
			// 
			this->PWD_MOON->Font = (gcnew System::Drawing::Font(L"Arial", 10.00F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PWD_MOON->ForeColor = System::Drawing::Color::White;
			this->PWD_MOON->Location = System::Drawing::Point(35, 210);
			this->PWD_MOON->Name = L"PWD_MOON";
			this->PWD_MOON->Size = System::Drawing::Size(220, 50);
			this->PWD_MOON->TabIndex = 1;
			this->PWD_MOON->Text = L"MOON";
			this->PWD_MOON->UseVisualStyleBackColor = true;
			this->PWD_MOON->Click += gcnew System::EventHandler(this, &Password_Form::PDW_3_Click);
			
			// 
			// Password_Form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(284, 457);
			this->MaximizeBox = false;
			this->Controls->Add(this->labelSTATUS);
			this->Controls->Add(this->labelSelectPWD);
			this->Controls->Add(this->labelAUTH);
			this->Controls->Add(this->PWD_SUN);
			this->Controls->Add(this->PWD_STAR);
			this->Controls->Add(this->PWD_MOON);
			this->Name = L"Password_Form";
			this->Text = L"Password";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		// PWD_SUN_click
		System::Void PDW_1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->PWD_SUN->isActive = true;
			this->PWD_SUN->Refresh();
			this->PWD_STAR->isActive = false;
			this->PWD_STAR->Refresh();
			this->PWD_MOON->isActive = false;
			this->PWD_MOON->Refresh();

			this->ReturnValue = "SUN";
			this->Close();
		}
		// PWD_STAR_click
		System::Void PDW_2_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->PWD_SUN->isActive = false;
			this->PWD_SUN->Refresh();
			this->PWD_STAR->isActive = true;
			this->PWD_STAR->Refresh();
			this->PWD_MOON->isActive = false;
			this->PWD_MOON->Refresh();

			this->ReturnValue = "STAR";
			this->Close();
		}
		// PWD_MOON_click
		System::Void PDW_3_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->PWD_SUN->isActive = false;
			this->PWD_SUN->Refresh();
			this->PWD_STAR->isActive = false;
			this->PWD_STAR->Refresh();
			this->PWD_MOON->isActive = true;
			this->PWD_MOON->Refresh();

			this->ReturnValue = "MOON";
			this->Close();
		}
	};
}
