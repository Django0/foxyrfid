#include <windows.h>
#include <conio.h>
#include "BoardDemo.h"
#include "Ntag_I2C.h"
#include "stdafx.h"
#include "Registers.h"

#pragma once

namespace NTAG_I2C_Demo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::Runtime::InteropServices;

	[DllImport("uxtheme.dll")]
	extern "C" HRESULT SetWindowTheme(HWND hWnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList);

	// TreeView that uses black and white arrows instead of the + and - signs
	public ref class NativeTreeView : System::Windows::Forms::TreeView
	{
	protected:
		void CreateHandle() override
		{
			System::Windows::Forms::TreeView::CreateHandle();

			SetWindowTheme(static_cast<HWND>(this->Handle.ToPointer()), L"explorer", NULL);
		}
	};
	
	// Button that has a gradient color (buttons in the LED tab)
	public ref class GradButton : public Button
	{
	public:
		Color^ gradientTop = Color::FromArgb(255, 90, 177, 220);
		Color^ gradientBottom = Color::FromArgb(255, 47, 102, 153);

	private:
		bool isPressed = false;	// Tracks if the button is pressed

	protected:
		// Paints the button
		void OnPaint(PaintEventArgs^ pevent) override
		{
			Graphics^ g = pevent->Graphics;
			this->PaintGradButton(g);
		}

		// Updates the isPressed variable and paints the button
		void OnMouseDown(MouseEventArgs^ mevent) override
		{
			isPressed = true;

			Graphics^g = CreateGraphics();
			this->PaintGradButton(g);
		}

		// Updates the isPressed variable and paints the button
		void OnMouseUp(MouseEventArgs^ mevent) override
		{
			isPressed = false;

			Graphics^g = CreateGraphics();
			this->PaintGradButton(g);

			this->OnClick(gcnew EventArgs());
		}

		// Returns a path of a rectangle with round corners
		GraphicsPath^ RoundedRectangle(System::Drawing::Rectangle^ boundingRect, int cornerRadius, int margin) {
			GraphicsPath^ roundedRect = gcnew GraphicsPath();
			roundedRect->AddArc(boundingRect->X + margin, boundingRect->Y + margin, cornerRadius * 2, cornerRadius * 2, 180, 90);
			roundedRect->AddArc(boundingRect->X + boundingRect->Width - margin - cornerRadius * 2, boundingRect->Y + margin, cornerRadius * 2, cornerRadius * 2, 270, 90);
			roundedRect->AddArc(boundingRect->X + boundingRect->Width - margin - cornerRadius * 2, boundingRect->Y + boundingRect->Height - margin - cornerRadius * 2, cornerRadius * 2, cornerRadius * 2, 0, 90);
			roundedRect->AddArc(boundingRect->X + margin, boundingRect->Y + boundingRect->Height - margin - cornerRadius * 2, cornerRadius * 2, cornerRadius * 2, 90, 90);
			roundedRect->CloseFigure();
			return roundedRect;
		}

		// Paints the button, taking into account if it is pressed or not
		virtual void PaintGradButton(Graphics^ g)
		{
			// Fill the background
			SolidBrush^ backgroundBrush = gcnew SolidBrush(System::Drawing::Color::White);
			g->FillRectangle(backgroundBrush, this->ClientRectangle);

			// Paint the outer rounded rectangle
			g->SmoothingMode = SmoothingMode::AntiAlias;
			System::Drawing::Rectangle^ outerRect = gcnew System::Drawing::Rectangle(ClientRectangle.X, ClientRectangle.Y, ClientRectangle.Width - 1, ClientRectangle.Height - 1);
			GraphicsPath^ outerPath = RoundedRectangle(outerRect, 5, 0);
			LinearGradientBrush^ outerBrush;
			if (!isPressed)
				outerBrush = gcnew LinearGradientBrush(*outerRect, *gradientTop, *gradientBottom, LinearGradientMode::Vertical);
			else
				outerBrush = gcnew LinearGradientBrush(*outerRect, *gradientTop, *gradientTop, LinearGradientMode::Vertical);
			g->FillPath(outerBrush, outerPath);
			Pen^ outlinePen = gcnew Pen(*gradientBottom);
			g->DrawPath(outlinePen, outerPath);

			// Paint the text
			TextRenderer::DrawText(g, this->Text, this->Font, *outerRect, this->ForeColor, Color::Transparent, TextFormatFlags::HorizontalCenter | TextFormatFlags::VerticalCenter | TextFormatFlags::EndEllipsis);
		}
	};

	// Button that behaves as a GradButton when it is active, and is black when it is passive (the buttons in the NDEF tab and in the Read/Write Config Registers option)
	public ref class GrackButton : public GradButton
	{
	public:
		bool isActive = false;

		// Paints the button, taking into account if it is active or not and if it is pressed or not
		void PaintGradButton(Graphics^ g) override
		{
			if (isActive)
				GradButton::PaintGradButton(g);
			else
			{
				// Paint the button
				SolidBrush^ brush = gcnew SolidBrush(System::Drawing::Color::Black);
				g->FillRectangle(brush, this->ClientRectangle);

				// Paint the text
				System::Drawing::Rectangle^ rect = gcnew System::Drawing::Rectangle(ClientRectangle.X, ClientRectangle.Y, ClientRectangle.Width - 1, ClientRectangle.Height - 1);
				TextRenderer::DrawText(g, this->Text, this->Font, *rect, this->ForeColor, Color::Transparent, TextFormatFlags::HorizontalCenter | TextFormatFlags::VerticalCenter | TextFormatFlags::EndEllipsis);
			}
		}
	}; 


	// Group box that appears when tapping Write NDEF in the NDEF tab	----		//NDEF tab - Write NDEF button
	public ref class WriteNDEFBox : public GroupBox
	{
		public: System::Windows::Forms::RadioButton^  radioButton_NDEFT_Text;
		public: System::Windows::Forms::RadioButton^  radioButton_NDEFT_URI;
		public: System::Windows::Forms::RadioButton^  radioButton_NDEFT_BT;
		public: System::Windows::Forms::RadioButton^  radioButton_NDEFT_SP;
		public: System::Windows::Forms::Panel^  panel1;
		public: System::Windows::Forms::Label^  label1;
		public: System::Windows::Forms::Label^  label2;
		public: System::Windows::Forms::Label^  label3;
		public: System::Windows::Forms::Label^  label4;
		public: System::Windows::Forms::Label^  label5;
		public: System::Windows::Forms::Label^  label6;
		public: System::Windows::Forms::TextBox^  textBox1;
		public: System::Windows::Forms::TextBox^  textBox2;
		public: System::Windows::Forms::TextBox^  textBox3;
		public: System::Windows::Forms::TextBox^  textBox4;
		public: System::Windows::Forms::TextBox^  textBox5;
		public: System::Windows::Forms::TextBox^  textBox6;
		public: NTAG_I2C_Demo::CheckBox^  checkBox1;
		public: NTAG_I2C_Demo::GradButton^  gButton_NDEFT_WriteDef;

		//Variables created in order to detect windows form size in dpi
		HDC screen = GetDC(0);
		int dpiX = GetDeviceCaps(screen, LOGPIXELSX);

	public:
		int selOption = TYPE_NDEF_TEXT;
		bool ButSwi = false;

	protected:
		void OnCreateControl() override
		{
			System::Windows::Forms::GroupBox::CreateControl();
			
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->radioButton_NDEFT_Text = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton_NDEFT_URI = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton_NDEFT_BT = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton_NDEFT_SP = (gcnew System::Windows::Forms::RadioButton());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->gButton_NDEFT_WriteDef = (gcnew NTAG_I2C_Demo::GradButton());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox8
			// 
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->radioButton_NDEFT_Text);
			this->Controls->Add(this->radioButton_NDEFT_URI);
			this->Controls->Add(this->radioButton_NDEFT_BT);
			this->Controls->Add(this->radioButton_NDEFT_SP);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->checkBox1);
			//this->Controls->Add(this->gButton_NDEFT_WriteDef);
			
			this->Location = System::Drawing::Point(15, 90);
			this->textBox1->Location = System::Drawing::Point(12, 9);
			this->textBox4->Location = System::Drawing::Point(87, 9);
			this->textBox3->Location = System::Drawing::Point(87, 37);
			this->textBox2->Location = System::Drawing::Point(87, 64);
			this->Size = System::Drawing::Size(247, 223);
			this->panel1->Size = System::Drawing::Size(230, 100);
			this->checkBox1->Location = System::Drawing::Point(16, 165);
			this->textBox2->Size = System::Drawing::Size(131, 21);
			this->textBox3->Size = System::Drawing::Size(131, 21);
			this->textBox4->Size = System::Drawing::Size(131, 21);
			this->textBox5->Size = System::Drawing::Size(131, 21);
			this->textBox6->Size = System::Drawing::Size(131, 21);
			this->textBox1->Size = System::Drawing::Size(206, 21);
			
			this->Name = L"writeNDEFBox1";
			this->TabIndex = 3;
			this->TabStop = false;
			// 
			// radioButton_NDEFT_SP former radioButton4
			// 
			this->radioButton_NDEFT_SP->AutoSize = true;
			this->radioButton_NDEFT_SP->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton_NDEFT_SP->Location = System::Drawing::Point(185, 34);
			this->radioButton_NDEFT_SP->Name = L"radioButton_NDEFT_SP";
			this->radioButton_NDEFT_SP->Size = System::Drawing::Size(62, 19);
			this->radioButton_NDEFT_SP->TabIndex = 4;
			this->radioButton_NDEFT_SP->Text = L"SP";
			this->radioButton_NDEFT_SP->UseVisualStyleBackColor = true;
			this->radioButton_NDEFT_SP->CheckedChanged += gcnew System::EventHandler(this, &WriteNDEFBox::radioButton_NDEFT_SP_CheckedChanged);
			// 
			// radioButton_NDEFT_BT former radioButton3
			// 
			this->radioButton_NDEFT_BT->AutoSize = true;
			this->radioButton_NDEFT_BT->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton_NDEFT_BT->Location = System::Drawing::Point(130, 34);
			this->radioButton_NDEFT_BT->Name = L"radioButton_NDEFT_BT";
			this->radioButton_NDEFT_BT->Size = System::Drawing::Size(62, 19);
			this->radioButton_NDEFT_BT->TabIndex = 3;
			this->radioButton_NDEFT_BT->Text = L"BT";
			this->radioButton_NDEFT_BT->UseVisualStyleBackColor = true;
			this->radioButton_NDEFT_BT->CheckedChanged += gcnew System::EventHandler(this, &WriteNDEFBox::radioButton_NDEFT_BT_CheckedChanged);
			// 
			// radioButton_NDEFT_URI former radioButton2
			// 
			this->radioButton_NDEFT_URI->AutoSize = true;
			this->radioButton_NDEFT_URI->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton_NDEFT_URI->Location = System::Drawing::Point(72, 34);
			this->radioButton_NDEFT_URI->Name = L"radioButton_NDEFT_URI";
			this->radioButton_NDEFT_URI->Size = System::Drawing::Size(46, 19);
			this->radioButton_NDEFT_URI->TabIndex = 2;
			this->radioButton_NDEFT_URI->Text = L"URI";
			this->radioButton_NDEFT_URI->UseVisualStyleBackColor = true;
			this->radioButton_NDEFT_URI->CheckedChanged += gcnew System::EventHandler(this, &WriteNDEFBox::radioButton_NDEFT_URI_CheckedChanged);
			// 
			// radioButton_NDEFT_Text former:radioButton1
			// 
			this->radioButton_NDEFT_Text->AutoSize = true;
			this->radioButton_NDEFT_Text->Checked = true;
			this->radioButton_NDEFT_Text->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton_NDEFT_Text->Location = System::Drawing::Point(17, 34);
			this->radioButton_NDEFT_Text->Name = L"radioButton_NDEFT_Text";
			this->radioButton_NDEFT_Text->Size = System::Drawing::Size(46, 19);
			this->radioButton_NDEFT_Text->TabIndex = 1;
			this->radioButton_NDEFT_Text->TabStop = true;
			this->radioButton_NDEFT_Text->Text = L"Text";
			this->radioButton_NDEFT_Text->UseVisualStyleBackColor = true;
			this->radioButton_NDEFT_Text->CheckedChanged += gcnew System::EventHandler(this, &WriteNDEFBox::radioButton_NDEFT_Text_CheckedChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(6, 14);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(181, 15);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Tap tag to write NDEF message";
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(244)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->label6);
			this->panel1->Controls->Add(this->textBox2);
			this->panel1->Controls->Add(this->textBox3);
			this->panel1->Controls->Add(this->textBox4);
			this->panel1->Controls->Add(this->textBox5);
			this->panel1->Controls->Add(this->textBox6);
			this->panel1->Location = System::Drawing::Point(9, 60);
			this->panel1->Name = L"panel1";
			//this->panel1->Size = System::Drawing::Size(230, 100);
			this->panel1->TabIndex = 4;
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(244)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->textBox1->Location = System::Drawing::Point(12, 9);
			this->textBox1->Name = L"textBox1";
			//this->textBox1->Size = System::Drawing::Size(206, 21);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"NDEF Message";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(1, 12);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(83, 15);
			this->label2->TabIndex = 5;
			this->label2->Text = L"MAC Address:";
			this->label2->Hide();
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(1, 40);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(84, 15);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Device Name:";
			this->label3->Hide();
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(1, 68);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(83, 15);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Device Class:";
			this->label4->Hide();
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(1, 12);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(83, 15);
			this->label5->TabIndex = 8;
			this->label5->Text = L"Title:";
			this->label5->Hide();
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(1, 40);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(84, 15);
			this->label6->TabIndex = 9;
			this->label6->Text = L"Link:";
			this->label6->Hide();
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(244)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->textBox2->Location = System::Drawing::Point(87, 65);
			this->textBox2->Name = L"textBox2";
			//this->textBox2->Size = System::Drawing::Size(131, 21);
			this->textBox2->TabIndex = 2;
			this->textBox2->Hide();
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(244)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->textBox3->Location = System::Drawing::Point(87, 37);
			this->textBox3->Name = L"textBox3";
			//this->textBox3->Size = System::Drawing::Size(131, 21);
			this->textBox3->TabIndex = 1;
			this->textBox3->Hide();
			// 
			// textBox4
			// 
			this->textBox4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(244)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->textBox4->Location = System::Drawing::Point(87, 9);
			this->textBox4->Name = L"textBox4";
			//this->textBox4->Size = System::Drawing::Size(131, 21);
			this->textBox4->TabIndex = 0;
			this->textBox4->Hide();
			// 
			// textBox5
			// 
			this->textBox5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(244)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox5->Location = System::Drawing::Point(35, 37);
			this->textBox5->Name = L"textBox5";
			//this->textBox5->Size = System::Drawing::Size(183, 21);
			this->textBox5->TabIndex = 1;
			this->textBox5->Text = L"http://www.";
			this->textBox5->Hide();
			// 
			// textBox6
			// 
			this->textBox6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(244)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox6->Location = System::Drawing::Point(35, 9);
			this->textBox6->Name = L"textBox6";
			//this->textBox6->Size = System::Drawing::Size(183, 21);
			this->textBox6->TabIndex = 0;
			this->textBox6->Hide();
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Arial", 8.5));
			//this->checkBox1->Location = System::Drawing::Point(16, 165);
			this->checkBox1->Name = L"checkBox2";
			this->checkBox1->Size = System::Drawing::Size(159, 18);
			this->checkBox1->TabIndex = 9;
			this->checkBox1->Text = L"Add NTAG I2C Demo AAR";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// gButton_NDEFT_WriteDef
			// 
			this->gButton_NDEFT_WriteDef->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gButton_NDEFT_WriteDef->Location = System::Drawing::Point(120, 188);
			this->gButton_NDEFT_WriteDef->Name = L"gButton_NDEFT_WriteDef";
			this->gButton_NDEFT_WriteDef->Size = System::Drawing::Size(140, 27);
			this->gButton_NDEFT_WriteDef->TabIndex = 9;
			this->gButton_NDEFT_WriteDef->Text = L"Write default NDEF";
			this->gButton_NDEFT_WriteDef->UseVisualStyleBackColor = true;
			this->gButton_NDEFT_WriteDef->Click += gcnew System::EventHandler(this, &WriteNDEFBox::gradButton1_Click);
			this->gButton_NDEFT_WriteDef->gradientTop = Color::FromArgb(255, 250, 250, 250);
			this->gButton_NDEFT_WriteDef->gradientBottom = Color::FromArgb(255, 200, 200, 200);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
		}

		System::Void radioButton_NDEFT_Text_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			this->label2->Hide();
			this->label3->Hide();
			this->label4->Hide();
			this->textBox2->Hide();
			this->textBox3->Hide();
			this->textBox4->Hide();
			this->label5->Hide();
			this->label6->Hide();
			this->textBox5->Hide();
			this->textBox6->Hide();
			this->textBox1->Show();
			this->textBox1->Text = L"NDEF Message";
			this->selOption = TYPE_NDEF_TEXT;
		}

		System::Void radioButton_NDEFT_URI_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			this->label2->Hide();
			this->label3->Hide();
			this->label4->Hide();
			this->textBox2->Hide();
			this->textBox3->Hide();
			this->textBox4->Hide();
			this->label5->Hide();
			this->label6->Hide();
			this->textBox5->Hide();
			this->textBox6->Hide();
			this->textBox1->Show();
			this->textBox1->Text = L"http://www.";
			this->selOption = TYPE_NDEF_URI;
		}

		System::Void radioButton_NDEFT_BT_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			this->textBox1->Hide();
			this->label5->Hide();
			this->label6->Hide();
			this->textBox5->Hide();
			this->textBox6->Hide();
			this->label2->Show();
			this->label3->Show();
			this->label4->Show();
			this->textBox2->Show();
			this->textBox3->Show();
			this->textBox4->Show();
			this->selOption = TYPE_NDEF_BTPAIR;
		}

		System::Void radioButton_NDEFT_SP_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			this->textBox1->Hide();
			this->label2->Hide();
			this->label3->Hide();
			this->label4->Hide();
			this->textBox2->Hide();
			this->textBox3->Hide();
			this->textBox4->Hide();
			this->label5->Show();
			this->label6->Show();
			this->textBox5->Show();
			this->textBox6->Show();
			this->selOption = TYPE_NDEF_SP;
		}

		// Write default NDEF message button
		System::Void gradButton1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->radioButton_NDEFT_SP->Checked = true;
			this->textBox6->Text = L"NTAG I2C EXPLORER";
			this->textBox5->Text = L"http://www.nxp.com/demoboard/OM5569";
			this->checkBox1->Checked = true;
			this->label1->Text = L"Tap tag to write NDEF message";
			if (this->ButSwi == false)
				this->ButSwi = true;
			else
				this->ButSwi = false;
		}
	};

	// Auxiliar and General group box when waiting to tap the I2C board	----		//Multiple uses when waiting to tap => Read tag memory/Reset tag memory/Read sessions reg/RWConfig Reg/About ...?
	public ref class TapTagBox : public GroupBox
	{
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::PictureBox^  pictureBox1;
		private: System::Windows::Forms::Button^  button1;

		public: System::String^ labelText;		// Text that will be in the label
		private: System::String^ label2Text;		// Text that will be in label2
		public: System::Drawing::Image^ Logo;	// Image that will appear in the picture box
		public: System::Drawing::Image^ backImage;	// Image for the going back button

		public: bool swi = false;

	protected:
		void OnCreateControl() override
		{
			System::Windows::Forms::GroupBox::CreateControl();
			
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TapTagBox::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			// 
			// groupBox1
			// 
			this->BackColor = System::Drawing::Color::White;
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Location = System::Drawing::Point(5, -2);
			this->Name = L"tapTagBox1";

		//	this->Anchor = (AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right | AnchorStyles::Top);
		//	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		//	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
		//	this->ClientSize = System::Drawing::Size(284, 457);
			this->Size = System::Drawing::Size(273, 455);
			this->label1->Location = System::Drawing::Point(30, 263);
			this->label2->Location = System::Drawing::Point(30, 323);
			this->pictureBox1->Location = System::Drawing::Point(23, 94);
			this->button1->Location = System::Drawing::Point(98, 408);
			
			this->TabIndex = 0;
			this->TabStop = false;
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 11.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label1->Location = System::Drawing::Point(75, 263); //(30, 263);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(200, 108);
			this->label1->TabIndex = 1;
			this->label1->Text = labelText;
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
//			this->label1->Click += gcnew System::EventHandler(this, &TapTagBox::label1_Click);
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label2->Location = System::Drawing::Point(75, 323); //(30, 323);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(240, 50);
			this->label2->TabIndex = 2;
			this->label2->BackColor = System::Drawing::Color::Black;
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
//			this->label2->Click += gcnew System::EventHandler(this, &TapTagBox::label2_Click);
			this->setLabel(this->label2Text);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = this->Logo;
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			//this->pictureBox1->Location = System::Drawing::Point(75, 94); //(23, 94);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(225, 139);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
//			this->pictureBox1->Click += gcnew System::EventHandler(this, &TapTagBox::pictureBox1_Click);
			// 
			// button1
			// 
			this->button1->BackgroundImage = this->backImage;
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			//this->button1->Location = System::Drawing::Point(150, 408); //(98, 408);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(60, 40);
			this->button1->TabIndex = 2;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &TapTagBox::button1_Click);
			// 
			// TapTagForm
			// 
			this->ResumeLayout(false);
			this->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
		}

		// If the user presses the button, is as if he'd pressed the group box
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->swi == false)
			{
				this->swi = true;
				this->OnClick(e);
			}
			else
				this->swi = false;
		}

	public:
		// Sets the content of label2
		System::Void setLabel(System::String^ text)
		{
			this->label2Text = text;
			if (this->label2 != nullptr)
			{
				if (text == "")
					this->label2->Hide();
				else
				{
					this->label2->Text = text;
					this->label2->Show();
				}
			}
			this->Refresh();
		}
	};

	// Group box from 'Flash' waiting to the Tag or FW selection		----		//Demo tab - Information - Flash (waiting for Tag or FW selection)
	public ref class TapTagBoxFLA : public GroupBox
	{
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	//private: System::Windows::Forms::Button^  button1;
	//private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	public: System::Windows::Forms::TextBox^  textBox;
	private: System::Windows::Forms::Label^  label3;
	private: NTAG_I2C_Demo::GradButton^  button2;
	private: NTAG_I2C_Demo::GradButton^  button1;

	public: System::String^ labelText;		// Text that will be in the label
	public: System::String^ label2Text;
	public: System::String^ textBoxFile;
	public: System::Drawing::Image^ Logo;	// Image that will appear in the picture box
	public: System::Drawing::Image^ backImage;	// Image for the going back button
	public:	event System::EventHandler^ backButtonClick;	// Event that is fired when the back button is pressed

	public: bool swi = false;
	public: bool dwi = false;
	public: bool mwi = false;

	//Variables created in order to detect windows form size in dpi
	HDC screen = GetDC(0);
	int dpiX = GetDeviceCaps(screen, LOGPIXELSX);

	protected:
		void OnCreateControl() override
		{
			System::Windows::Forms::GroupBox::CreateControl();

			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TapTagBox::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew NTAG_I2C_Demo::GradButton());
			this->button2 = (gcnew NTAG_I2C_Demo::GradButton());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			// 
			// groupBox1
			// 
			this->BackColor = System::Drawing::Color::White;
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button3);
			this->Location = System::Drawing::Point(5, -2);
			this->Name = L"tapTagBox1";
			//Now we have to adapt the size of the window to the size of the screen
			if (dpiX == 120)
			{
				this->Size = System::Drawing::Size(365, 559);
				this->label1->Location = System::Drawing::Point(86, 180);
				this->pictureBox1->Location = System::Drawing::Point(75, 15);
				this->pictureBox1->Size = System::Drawing::Size(225, 139);
				this->button1->Location = System::Drawing::Point(20, 300);
				this->button2->Location = System::Drawing::Point(190, 300);
				this->button3->Location = System::Drawing::Point(140, 500);
				this->label3->Location = System::Drawing::Point(130, 410);
				this->textBox->Size = System::Drawing::Size(206, 21);
				this->textBox->Location = System::Drawing::Point(80, 430);
				this->label1->Size = System::Drawing::Size(200, 108);
				this->button2->Size = System::Drawing::Size(150, 45);
				this->button1->Size = System::Drawing::Size(150, 45);
			}
			else //dpiX == 96 for instance
			{
				this->Size = System::Drawing::Size(273, 455);
				this->label1->Location = System::Drawing::Point(30, 200);
				this->pictureBox1->Location = System::Drawing::Point(23, 20);
				this->pictureBox1->Size = System::Drawing::Size(225, 139);
				this->button1->Location = System::Drawing::Point(15, 270);
				this->button2->Location = System::Drawing::Point(150, 270);
				this->button3->Location = System::Drawing::Point(100, 410);
				this->label3->Location = System::Drawing::Point(90, 350);
				this->textBox->Size = System::Drawing::Size(206, 21);
				this->textBox->Location = System::Drawing::Point(30, 370);
				this->label1->Size = System::Drawing::Size(200, 70);
				this->button2->Size = System::Drawing::Size(110, 35);
				this->button1->Size = System::Drawing::Size(110, 35);
			}
			this->TabIndex = 0;
			this->TabStop = false;
			// 
			// textBox
			// 
			/*this->textBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>()), static_cast<System::Int32>(static_cast<System::Byte>()),
				static_cast<System::Int32>(static_cast<System::Byte>(000)));*/
			this->textBox->BackColor = System::Drawing::Color::White;
			this->textBox->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox->Name = L"textBox1";
			this->textBox->TabIndex = 0;
			this->textBox->Text = this->textBoxFile;
			// 
			// label3
			// 
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(100, 20);
			this->label3->TabIndex = 1;
			this->label3->Text = L"Current File: ";
			this->label3->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label2->Location = System::Drawing::Point(75, 323); //(30, 323);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(200, 32);
			this->label2->TabIndex = 2;
			this->label2->BackColor = System::Drawing::Color::Black;
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			//			this->label2->Click += gcnew System::EventHandler(this, &TapTagBox::label2_Click);
			this->setLabel(this->label2Text);
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 11.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Name = L"label1";
			//this->label1->Size = System::Drawing::Size(200, 108);
			this->label1->TabIndex = 1;
			this->label1->Text = labelText;
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = this->Logo;
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Name = L"button1";
			//this->button1->Size = System::Drawing::Size(150, 45);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Select from App";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->gradientTop = Color::FromArgb(255, 123, 177, 219);
			this->button1->gradientBottom = Color::FromArgb(255, 44, 85, 177);
			this->button1->Click += gcnew System::EventHandler(this, &TapTagBoxFLA::button1_Click);
			// 
			// button2
			// 
			this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button2->ForeColor = System::Drawing::Color::White;
			this->button2->FlatAppearance->BorderSize = 0;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Name = L"button2";
			//this->button2->Size = System::Drawing::Size(150, 45);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Select from Storage";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->gradientTop = Color::FromArgb(255, 123, 177, 219);
			this->button2->gradientBottom = Color::FromArgb(255, 44, 85, 177);
			this->button2->Click += gcnew System::EventHandler(this, &TapTagBoxFLA::button2_Click);
			// 
			// button3
			// 
			this->button3->BackgroundImage = this->backImage;
			this->button3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button3->FlatAppearance->BorderSize = 0;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(60, 40);
			this->button3->TabIndex = 2;
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &TapTagBoxFLA::button3_Click);
			// 
			// TapTagForm
			// 
			this->ResumeLayout(false);
			this->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
		}

		// If the user presses the button, is as if he'd pressed the group box
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->dwi == false)
			{
				this->dwi = true;
				this->OnClick(e);
			}
			else
				this->dwi = false;
		}
		// If the user presses the button, is as if he'd pressed the group box
		System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->swi == false)
			{
				this->swi = true;
				this->OnClick(e);
			}
			else
				this->swi = false;
		}
		// If the user presses the button, is as if he'd pressed the group box
		System::Void button3_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->mwi == false)
			{
				this->mwi = true;
				this->OnClick(e);
			}
			else
				this->mwi = false;
		}
		public:
			// Sets the content of label4
			System::Void setLabel(System::String^ text)
			{
				this->label2Text = text;
				if (this->label2 != nullptr)
				{
					if (text == "")
						this->label2->Hide();
					else
					{
						this->label2->Text = text;
						this->label2->Show();
					}
				}
				this->Refresh();
			}
	};

	// Group box for selecting which FW to flash						----		//Demo tab - Information - Flash - Select from App
	public ref class SelectFlash : public GroupBox
	{
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::RadioButton^  button1;
	private: System::Windows::Forms::RadioButton^  button2;
	private: System::Windows::Forms::Button^  button3;

	public: System::Drawing::Image^ Logo;	// Image that will appear in the picture box
	public: System::Drawing::Image^ backImage;	// Image for the going back button
	public:	event System::EventHandler^ backButtonClick;	// Event that is fired when the back button is pressed

	public: bool swi, dwi, mwi,selBlink,selDemo = false;

	//Variables created in order to detect windows form size in dpi
	HDC screen = GetDC(0);
	int dpiX = GetDeviceCaps(screen, LOGPIXELSX);

	protected:
		void OnCreateControl() override
		{
			System::Windows::Forms::GroupBox::CreateControl();

			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(SelectFlash::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::RadioButton());
			this->button2 = (gcnew System::Windows::Forms::RadioButton());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			// 
			// groupBox1
			// 
			this->BackColor = System::Drawing::Color::White;
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button3);
			this->Location = System::Drawing::Point(5, -2);
			this->Name = L"SelectFlashing1";
			//Now we have to adapt the size of the window to the size of the screen
			if (dpiX == 120)
			{
				this->Size = System::Drawing::Size(365, 559);
				this->label1->Location = System::Drawing::Point(70, 240);
				this->pictureBox1->Location = System::Drawing::Point(75, 60);
				this->pictureBox1->Size = System::Drawing::Size(225, 139);
				this->button1->Location = System::Drawing::Point(50, 350);
				this->button2->Location = System::Drawing::Point(210, 350);
				this->button3->Location = System::Drawing::Point(140, 500);
				this->label1->Size = System::Drawing::Size(250, 108);
				this->button2->Size = System::Drawing::Size(150, 40);
				this->button1->Size = System::Drawing::Size(150, 40);
			}
			else //dpiX == 96 for instance
			{
				this->Size = System::Drawing::Size(273, 455);
				this->label1->Location = System::Drawing::Point(30, 263);
				this->pictureBox1->Location = System::Drawing::Point(23, 94);
				this->pictureBox1->Size = System::Drawing::Size(225, 139);
				this->button1->Location = System::Drawing::Point(40, 320);
				this->button2->Location = System::Drawing::Point(140, 320);
				this->button3->Location = System::Drawing::Point(95, 380);
				this->label1->Size = System::Drawing::Size(200, 50);
				this->button2->Size = System::Drawing::Size(100, 43);
				this->button1->Size = System::Drawing::Size(100, 43);
			}
			this->TabIndex = 0;
			this->TabStop = false;
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 11.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Name = L"label1";
			//this->label1->Size = System::Drawing::Size(200, 108);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Select Firmware to Flash: ";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = this->Logo;
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Name = L"button1";
			//this->button1->Size = System::Drawing::Size(100, 43);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Demo App"; 
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &SelectFlash::button1_Click);
			// 
			// button2
			// 
			this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button2->FlatAppearance->BorderSize = 0;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Name = L"button2";
			//this->button2->Size = System::Drawing::Size(100, 43);
			this->button2->TabIndex = 2;
			this->button2->Text = L"LED Blinker";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &SelectFlash::button2_Click);
			// 
			// button3
			// 
			this->button3->BackgroundImage = this->backImage;
			this->button3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button3->FlatAppearance->BorderSize = 0;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(60, 40);
			this->button3->TabIndex = 2;
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &SelectFlash::button3_Click);
			// 
			// TapTagForm
			// 
			this->ResumeLayout(false);
			this->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
		}

		// If the user presses the button, is as if he'd pressed the group box
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->swi == false)
			{
				this->swi = true;
				this->OnClick(e);
			}
			else
				this->swi = false;
		}
		// If the user presses the button, is as if he'd pressed the group box
		System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->dwi == false)
			{
				this->dwi = true;
				this->OnClick(e);
			}
			else
				this->dwi = false;
		}
		// If the user presses the button, is as if he'd pressed the group box
		System::Void button3_Click(System::Object^  sender, System::EventArgs^  e)
		{
			//backButtonClick(this, gcnew EventArgs());
			if (this->mwi == false)
			{
				this->mwi = true;
				this->OnClick(e);
			}
			else
				this->mwi = false;
		}
	public:
		// Sets the content of label4
		/*System::Void setLabel(System::String^ text)
		{
			this->label2Text = text;
			if (this->label2 != nullptr)
			{
				if (text == "")
					this->label2->Hide();
				else
				{
					this->label2->Text = text;
					this->label2->Show();
				}
			}
			this->Refresh();
		}*/
	};

	// Group box from 'Flash' option in when already Flashing			----		//Demo tab - Information - Flash (when flashing)
	public ref class FlashingBox : public GroupBox
	{
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::Label^  label4;
		private: System::Windows::Forms::Label^  label5;
		private: System::Windows::Forms::PictureBox^  pictureBox1;
		public: System::Windows::Forms::ProgressBar^  progressBarFlash;
		public: System::Windows::Forms::TextBox^  textBoxFlashPerformance;
		public: System::Windows::Forms::TextBox^  textBoxFile;
		private: System::Windows::Forms::Button^  buttonf3;

		public: System::String^ labelText;		// Text that will be in the label
		public: System::String^ textBoxarg;
		public: System::Drawing::Image^ Logo;	// Image that will appear in the picture box
		public: System::Drawing::Image^ backImage;	// Image for the going back button
		public:	event System::EventHandler^ backButtonClick;

		public: bool swi = false;

		//Variables created in order to detect windows form size in dpi
		HDC screen = GetDC(0);
		int dpiX = GetDeviceCaps(screen, LOGPIXELSX);

	protected:
		void OnCreateControl() override
		{
			System::Windows::Forms::GroupBox::CreateControl();

			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FlashingBox::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->progressBarFlash = (gcnew System::Windows::Forms::ProgressBar());
			this->textBoxFlashPerformance = (gcnew System::Windows::Forms::TextBox());
			this->textBoxFile = (gcnew System::Windows::Forms::TextBox());
			this->buttonf3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			// 
			// groupBox1
			// 
			this->BackColor = System::Drawing::Color::White;
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->progressBarFlash);
			this->Controls->Add(this->textBoxFlashPerformance);
			this->Controls->Add(this->textBoxFile);
			this->Controls->Add(this->buttonf3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label5);
			this->Location = System::Drawing::Point(5, -2);
			this->Name = L"FlashingBox1";
			//Now we have to adapt the size of the window to the size of the screen
			if (dpiX == 120)
			{
				this->Size = System::Drawing::Size(365, 559);
				this->label1->Location = System::Drawing::Point(5, 15);
				this->label2->Location = System::Drawing::Point(75, 253);
				this->label2->Size = System::Drawing::Size(200, 19);
				this->textBoxFile->Location = System::Drawing::Point(75, 283);
				this->textBoxFile->Size = System::Drawing::Size(200, 32);
				this->label4->Location = System::Drawing::Point(2, 405);
				this->label4->Size = System::Drawing::Size(150, 35);
				this->pictureBox1->Location = System::Drawing::Point(75, 50);
				this->pictureBox1->Size = System::Drawing::Size(200, 130);
				this->progressBarFlash->Location = System::Drawing::Point(59, 340);
				this->progressBarFlash->Size = System::Drawing::Size(248, 32);
				this->textBoxFlashPerformance->Size = System::Drawing::Size(350, 50);
				this->textBoxFlashPerformance->Location = System::Drawing::Point(5, 430);
				this->buttonf3->Location = System::Drawing::Point(140, 500);
				this->buttonf3->Size = System::Drawing::Size(60, 40);
				this->label1->Size = System::Drawing::Size(350, 25);
				this->label5->Location = System::Drawing::Point(75, 375);
			}
			else //dpiX == 96 for instance
			{
				this->Size = System::Drawing::Size(273, 455);
				this->label1->Location = System::Drawing::Point(10, 15);
				this->label1->Size = System::Drawing::Size(240, 45);
				this->label2->Location = System::Drawing::Point(90, 190);
				this->label2->Size = System::Drawing::Size(100, 20);
				this->textBoxFile->Location = System::Drawing::Point(65, 205);
				this->textBoxFile->Size = System::Drawing::Size(150, 35);
				this->label4->Location = System::Drawing::Point(2, 330);
				this->label4->Size = System::Drawing::Size(150, 20);
				this->pictureBox1->Location = System::Drawing::Point(50, 70);
				this->pictureBox1->Size = System::Drawing::Size(180, 100);
				this->progressBarFlash->Location = System::Drawing::Point(29,250);
				this->progressBarFlash->Size = System::Drawing::Size(220, 30);
				this->textBoxFlashPerformance->Size = System::Drawing::Size(265, 45);
				this->textBoxFlashPerformance->Location = System::Drawing::Point(5, 350);
				this->buttonf3->Location = System::Drawing::Point(105, 408);
				this->buttonf3->Size = System::Drawing::Size(60, 40);
				this->label5->Location = System::Drawing::Point(30, 290);
			}
			this->TabIndex = 0;
			this->TabStop = false;
			// 
			// textBoxFile
			//
			this->textBoxFile->BackColor = System::Drawing::Color::White;
			this->textBoxFile->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBoxFile->Name = L"textBoxFile";
			this->textBoxFile->TabIndex = 0;
			this->textBoxFile->Text = this->textBoxarg;
			// 
			// label5
			// 
			this->label5->Font = (gcnew System::Drawing::Font(L"Arial", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(250, 20);
			this->label5->TabIndex = 2;
			this->label5->BackColor = System::Drawing::Color::Black;
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			//			this->label2->Click += gcnew System::EventHandler(this, &TapTagBox::label2_Click);
			this->label5->BringToFront();
			this->setLabel(this->labelText);
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label2->Location = System::Drawing::Point(75, 253); //(30, 323);
			this->label2->Name = L"label2";
			//this->label2->Size = System::Drawing::Size(200, 19);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Current file: ";
			this->label2->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			//			this->label2->Click += gcnew System::EventHandler(this, &TapTagBox::label2_Click);
			// 
			// label4
			// 
			this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label4->Location = System::Drawing::Point(2, 405); //(30, 323);
			this->label4->Name = L"label4";
			//this->label4->Size = System::Drawing::Size(150, 35);
			this->label4->TabIndex = 4;
			this->label4->Text = L"Flash statistics: ";
			this->label4->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = this->Logo;
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			//this->pictureBox1->Location = System::Drawing::Point(75, 50); //(23, 94);
			this->pictureBox1->Name = L"pictureBox1";
			//this->pictureBox1->Size = System::Drawing::Size(200, 130);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			//			this->pictureBox1->Click += gcnew System::EventHandler(this, &TapTagBox::pictureBox1_Click);
			// 
			// progressBarFlash
			// 
			//this->progressBarFlash->Location = System::Drawing::Point(59, 340);
			this->progressBarFlash->Name = L"progressBarFlash";
			//this->progressBarFlash->Size = System::Drawing::Size(248, 32);
			this->progressBarFlash->TabIndex = 0;
			// 
			// textBoxFlashPerformance
			// 
			this->textBoxFlashPerformance->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(244)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->textBoxFlashPerformance->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBoxFlashPerformance->Enabled = false;
			this->textBoxFlashPerformance->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->textBoxFlashPerformance->Location = System::Drawing::Point(5, 430);
			this->textBoxFlashPerformance->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxFlashPerformance->Multiline = true;
			this->textBoxFlashPerformance->Name = L"textBoxFlashPerformance";
			this->textBoxFlashPerformance->ReadOnly = true;
			//this->textBoxFlashPerformance->Size = System::Drawing::Size(350, 50);
			this->textBoxFlashPerformance->TabIndex = 0;
			// 
			// button3
			// 
			this->buttonf3->BackgroundImage = this->backImage;
			this->buttonf3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->buttonf3->FlatAppearance->BorderSize = 0;
			this->buttonf3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			//this->buttonf3->Location = System::Drawing::Point(140, 510); //(98, 408);
			this->buttonf3->Name = L"button3";
			//this->buttonf3->Size = System::Drawing::Size(61, 33);
			this->buttonf3->TabIndex = 4;
			this->buttonf3->UseVisualStyleBackColor = true;
			this->buttonf3->Click += gcnew System::EventHandler(this, &FlashingBox::buttonf3_Click);
			// 
			//FlashingForm
			// 
			this->ResumeLayout(false);
			this->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
		}
		// When button1 is pressed, it fires a backButtonClick event
		System::Void buttonf3_Click(System::Object^  sender, System::EventArgs^  e)
		{
			backButtonClick(this, gcnew EventArgs());
		}
	public:
		// Sets the content of label2
		System::Void setLabel(System::String^ text)
		{
			this->labelText = text;
			if (this->label5 != nullptr)
			{
				if (text == "")
					this->label5->Hide();
				else
				{
					this->label5->Text = text;
					this->label5->Show();
				}
			}
			this->Refresh();
		}
	};

	// Group box from 'About' option in Demo Tab						----		//Demo tab - Information - About
	public ref class VersionBox : public GroupBox
	{
		private: NTAG_I2C_Demo::NativeTreeView^  treeView1;
		private: System::Windows::Forms::Panel^  panel1;
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::Label^  label3;
		private: System::Windows::Forms::Label^  label4;
		private: System::Windows::Forms::Button^  button1;
		private: System::Windows::Forms::Label^  label10;

		private: Versions_t* versions = new Versions_t();	// Struct containing the read data
		private: String^ appVersion = gcnew String("");	// String that contains the app version
		private: String^ FWVersion = gcnew String("");	// String that contains the app version
		private: System::String^ label10Text;		// Text that will be in label10
		public: System::Drawing::Image^ backImage;	// Image for the going back button
		public:	event System::EventHandler^ backButtonClick;	// Event that is fired when the back button is pressed

		//Variables created in order to detect windows form size in dpi
		HDC screen = GetDC(0);
		int dpiX = GetDeviceCaps(screen, LOGPIXELSX);

	protected:
		void OnCreateControl() override
		{
			System::Windows::Forms::GroupBox::CreateControl();

			System::Windows::Forms::TreeNode^  treeNode1 = (gcnew System::Windows::Forms::TreeNode(L"Board Version:"));
			System::Windows::Forms::TreeNode^  treeNode2 = (gcnew System::Windows::Forms::TreeNode(L"Board FW Version:"));
			System::Windows::Forms::TreeNode^  treeNode3 = (gcnew System::Windows::Forms::TreeNode(L"App version:"));
			System::Windows::Forms::TreeNode^  treeNode5 = (gcnew System::Windows::Forms::TreeNode(L"Identiv FW Version:"));
			System::Windows::Forms::TreeNode^  treeNode4 = (gcnew System::Windows::Forms::TreeNode(L"VERSION INFORMATION",
				gcnew cli::array< System::Windows::Forms::TreeNode^  >(4) {treeNode1, treeNode2, treeNode3,treeNode5}));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->treeView1 = (gcnew NTAG_I2C_Demo::NativeTreeView());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->Controls->Add(this->button1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label10);
			this->Location = System::Drawing::Point(5, -2);
			this->Name = L"groupBox1";
			//Now we have to adapt the size of the window to the size of the screen
			if (dpiX == 120)
			{
				this->Size = System::Drawing::Size(365, 559);
				this->label1->Location = System::Drawing::Point(175, 16);
				this->label2->Location = System::Drawing::Point(175, 16);
				this->label3->Location = System::Drawing::Point(175, 16);
				this->label4->Location = System::Drawing::Point(175, 16);
				this->button1->Location = System::Drawing::Point(140, 500);
				this->panel1->Size = System::Drawing::Size(365, 450);
				this->label10->Location = System::Drawing::Point(30, 353);
			}
			else //dpiX == 96 for instance
			{
				this->Size = System::Drawing::Size(273, 455);
				this->label1->Location = System::Drawing::Point(150, 16);
				this->label2->Location = System::Drawing::Point(150, 16);
				this->label3->Location = System::Drawing::Point(150, 16);
				this->label4->Location = System::Drawing::Point(150, 16);
				this->button1->Location = System::Drawing::Point(98, 408);
				this->panel1->Size = System::Drawing::Size(273, 455);
				this->label10->Location = System::Drawing::Point(30, 353);
			}
			this->TabIndex = 0;
			this->TabStop = false;
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->BackColor = System::Drawing::Color::Transparent;
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->treeView1);
			this->panel1->Location = System::Drawing::Point(0, 16);
			this->panel1->Name = L"panel1";
			//this->panel1->Size = System::Drawing::Size(273, 389);
			this->panel1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label1->Location = System::Drawing::Point(135, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(120, 18);
			this->label1->TabIndex = 12;
			this->label1->Text = L"label1";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label2->Location = System::Drawing::Point(135, 16);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(120, 18);
			this->label2->TabIndex = 12;
			this->label2->Text = L"label2";
			this->label2->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label3->Location = System::Drawing::Point(135, 16);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(120, 18);
			this->label3->TabIndex = 12;
			this->label3->Text = L"label3";
			this->label3->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label4
			// 
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label4->Location = System::Drawing::Point(135, 16);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(120, 18);
			this->label4->TabIndex = 12;
			this->label4->Text = L"label4";
			this->label4->TextAlign = System::Drawing::ContentAlignment::TopRight;
			//
			// hiddenElements
			//
			this->label1->Hide();
			this->label2->Hide();
			this->label3->Hide();
			this->label4->Hide();
			//
			// treeView1			For the 'About' functionality
			// 
			this->treeView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->treeView1->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->treeView1->Location = System::Drawing::Point(3, 0);
			this->treeView1->Name = L"treeView1";
			treeNode1->Name = L"Node1";
			treeNode1->Text = L"Board Version:";
			treeNode2->Name = L"Node2";
			treeNode2->Text = L"Board FW Version:";
			treeNode3->Name = L"Node3";
			treeNode3->Text = L"App Version:";
			treeNode5->Name = L"Node5";
			treeNode5->Text = L"Identiv FW Version:";
			treeNode4->Name = L"Node0";
			treeNode4->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode4->Text = L"VERSION INFORMATION";
			this->treeView1->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(1) {treeNode4});			//Establish the 4th node as the higher level node
			this->treeView1->Scrollable = false;
			this->treeView1->ShowLines = false;
			this->treeView1->Size = System::Drawing::Size(240, 364);
			this->treeView1->TabIndex = 0;
			this->treeView1->AfterCollapse += gcnew System::Windows::Forms::TreeViewEventHandler(this, &VersionBox::treeView1_AfterExplapse);
			this->treeView1->AfterExpand += gcnew System::Windows::Forms::TreeViewEventHandler(this, &VersionBox::treeView1_AfterExplapse);
			this->treeView1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &VersionBox::treeView1_MouseWheel);
			this->treeView1->Nodes[0]->Expand();
			// 
			// button1
			// 
			this->button1->BackgroundImage = this->backImage;
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			//this->button1->Location = System::Drawing::Point(98, 408);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(60, 40);
			this->button1->TabIndex = 2;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &VersionBox::button1_Click);
			// 
			// label10
			// 
			this->label10->Font = (gcnew System::Drawing::Font(L"Arial", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label10->Location = System::Drawing::Point(30, 353);
			this->label10->Name = L"label2";
			this->label10->Size = System::Drawing::Size(200, 32);
			this->label10->TabIndex = 2;
			this->label10->BackColor = System::Drawing::Color::Black;
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label10->BringToFront();
			this->setLabel(this->label10Text);
			// 
			// VersionForm
			// 
			this->updateParsing();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
		}

			// Every time a tree node expands or collapses we need to resize the tree view according to the new size (so that the srollbar from the panel appears
			// when it is needed) and check if the checkboxes need to be shown or hidden
			System::Void treeView1_AfterExplapse(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
			{
				int maxPos = this->treeView1->Nodes[0]->Bounds.Location.Y;
				if (this->treeView1->Nodes[0]->LastNode->Bounds.Location.Y != 0)
					maxPos = this->treeView1->Nodes[0]->LastNode->Bounds.Location.Y;
				this->treeView1->Size = System::Drawing::Size(this->treeView1->Size.Width, maxPos + 30);

				if (this->treeView1->Nodes[0]->Nodes[0]->IsVisible)
				{
					this->label1->Location = System::Drawing::Point(this->label1->Location.X, this->treeView1->Nodes[0]->Nodes[0]->Bounds.Location.Y);
					this->label1->Show();
				}
				else
					this->label1->Hide();
				if (this->treeView1->Nodes[0]->Nodes[1]->IsVisible)
				{
					this->label2->Location = System::Drawing::Point(this->label2->Location.X, this->treeView1->Nodes[0]->Nodes[1]->Bounds.Location.Y);
					this->label2->Show();
				}
				else
					this->label2->Hide();
				if (this->treeView1->Nodes[0]->Nodes[2]->IsVisible)
				{
					this->label3->Location = System::Drawing::Point(this->label3->Location.X, this->treeView1->Nodes[0]->Nodes[2]->Bounds.Location.Y);
					this->label3->Show();
				}
				else
					this->label3->Hide();
				if (this->treeView1->Nodes[0]->Nodes[3]->IsVisible)
				{
					this->label4->Location = System::Drawing::Point(this->label4->Location.X, this->treeView1->Nodes[0]->Nodes[3]->Bounds.Location.Y);
					this->label4->Show();
				}
				else
					this->label4->Hide();
			}

			// This way, the mouse wheel controls the scrollbar of the panel when the mouse is over the tree view
			System::Void treeView1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			{
				this->panel1->Focus();
			}

			// When button1 is pressed, it fires a backButtonClick event
			System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
			{
				backButtonClick(this, gcnew EventArgs());
			}

			// Internal function for initializing the SessionRegistersBox
			System::Void updateParsing()
			{
				// Convert from ASCII to Unicode
				int strLength = strlen(this->versions->Board_Version);
				this->label1->Text = "";
				for (int i = 0; i < strLength; i++)
					this->label1->Text += (wchar_t)this->versions->Board_Version[i];
				strLength = strlen(this->versions->Board_FW_Version);
				this->label2->Text = "";
				for (int i = 0; i < strLength; i++)
					this->label2->Text += (wchar_t)this->versions->Board_FW_Version[i];
				this->label3->Text = this->appVersion;
				this->label4->Text = this->FWVersion;
			}

		public:
			// Initializes the SessionRegistersBox according to the structure passed as a parameter
			System::Void updateBox(Versions_t versions, String^ appVersion, String^ FWVersion)
			{
				*this->versions = versions;
				this->appVersion = appVersion;
				this->FWVersion = FWVersion;

				if (this->label2 != nullptr)
					this->updateParsing();
			}

			// Sets the content of label10
			System::Void setLabel(System::String^ text)
			{
				this->label10Text = text;
				if (this->label10 != nullptr)
				{
					if (text == "")
						this->label10->Hide();
					else
					{
						this->label10->Text = text;
						this->label10->Show();
					}
				}
				this->Refresh();
			}
	};

	// Group box appears on the 'Learn More' option in DemoTab			----		//Demo tab - Information - Learn more
	public ref class HelpBox : public GroupBox
	{
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::LinkLabel^  linkLabel1;
		private: System::Windows::Forms::LinkLabel^  linkLabel2;
		private: System::Windows::Forms::LinkLabel^  linkLabel3;
		private: System::Windows::Forms::LinkLabel^  linkLabel4;
		private: System::Windows::Forms::LinkLabel^  linkLabel5;
		private: System::Windows::Forms::PictureBox^  pictureBox1;
		private: System::Windows::Forms::Button^  button1;
		public: System::Drawing::Image^ Logo;	// Image that will appear in the picture box
		public: System::Drawing::Image^ backImage;	// Image for the going back button

		//Variables created in order to detect windows form size in dpi
		HDC screen = GetDC(0);
		int dpiX = GetDeviceCaps(screen, LOGPIXELSX);
		public: bool mwi;

	protected:
		void OnCreateControl() override
		{
			System::Windows::Forms::GroupBox::CreateControl();

			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(HelpBox::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->linkLabel2 = (gcnew System::Windows::Forms::LinkLabel());
			this->linkLabel3 = (gcnew System::Windows::Forms::LinkLabel());
			this->linkLabel4 = (gcnew System::Windows::Forms::LinkLabel());
			this->linkLabel5 = (gcnew System::Windows::Forms::LinkLabel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			// 
			// groupBox1
			// 
			this->BackColor = System::Drawing::Color::White;
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->linkLabel1);
			this->Controls->Add(this->linkLabel2);
			this->Controls->Add(this->linkLabel3);
			this->Controls->Add(this->linkLabel4);
			this->Controls->Add(this->linkLabel5);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Location = System::Drawing::Point(6, -2);
			this->Name = L"helpBox1";
			//Now we have to adapt the size of the window to the size of the screen
			if (dpiX == 120)
			{
				this->Size = System::Drawing::Size(365, 559);
				this->label1->Location = System::Drawing::Point(60, 20);
				this->label1->Size = System::Drawing::Size(250, 70);
				this->label2->Location = System::Drawing::Point(60, 295);
				this->label2->Size = System::Drawing::Size(250, 30);
				this->linkLabel1->Location = System::Drawing::Point(60, 90);
				this->linkLabel1->Size = System::Drawing::Size(220, 30);
				this->linkLabel2->Location = System::Drawing::Point(60, 125);
				this->linkLabel2->Size = System::Drawing::Size(220, 30);
				this->linkLabel3->Location = System::Drawing::Point(60, 160);
				this->linkLabel3->Size = System::Drawing::Size(220, 50);
				this->linkLabel4->Location = System::Drawing::Point(60, 215);
				this->linkLabel4->Size = System::Drawing::Size(220, 30);
				this->linkLabel5->Location = System::Drawing::Point(60, 250);
				this->linkLabel5->Size = System::Drawing::Size(220, 30);
				this->pictureBox1->Location = System::Drawing::Point(60, 330);
				this->pictureBox1->Size = System::Drawing::Size(245, 70);
				this->button1->Location = System::Drawing::Point(140, 500);
				this->button1->Size = System::Drawing::Size(60, 40);
			}
			else //dpiX == 96 for instance
			{
				this->Size = System::Drawing::Size(273, 400);
				this->label1->Location = System::Drawing::Point(13, 20);
				this->label1->Size = System::Drawing::Size(250, 70);
				this->label2->Location = System::Drawing::Point(20, 295);
				this->label2->Size = System::Drawing::Size(250, 30);
				this->linkLabel1->Location = System::Drawing::Point(20, 90);
				this->linkLabel1->Size = System::Drawing::Size(220, 30);
				this->linkLabel2->Location = System::Drawing::Point(20, 125);
				this->linkLabel2->Size = System::Drawing::Size(220, 30);
				this->linkLabel3->Location = System::Drawing::Point(20, 160);
				this->linkLabel3->Size = System::Drawing::Size(220, 50);
				this->linkLabel4->Location = System::Drawing::Point(20, 215);
				this->linkLabel4->Size = System::Drawing::Size(220, 30);
				this->linkLabel5->Location = System::Drawing::Point(20, 250);
				this->linkLabel5->Size = System::Drawing::Size(220, 30);
				this->pictureBox1->Location = System::Drawing::Point(20, 330);
				this->pictureBox1->Size = System::Drawing::Size(245, 70);
				this->button1->Location = System::Drawing::Point(110, 405);
				this->button1->Size = System::Drawing::Size(60, 40);
			}
			this->AutoSize = true;
			this->TabIndex = 0;
			this->TabStop = false;
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label1->Location = System::Drawing::Point(60, 20); //Before 13,20
			this->label1->Name = L"label1";
			this->AutoSize = true;
			//this->label1->Size = System::Drawing::Size(250, 70);
			this->label1->TabIndex = 1;
			this->label1->Text = L"This application can be used with the NTAG I2C Demo Kit as well as with the NTAG I2C Explorer Kit.";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopLeft;
			//this->label1->Click += gcnew System::EventHandler(this, &HelpBox::label1_Click);
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 13.F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label2->Location = System::Drawing::Point(60, 295);
			this->label2->Name = L"label2";
			//this->label2->Size = System::Drawing::Size(250, 30);
			this->label2->TabIndex = 1;
			this->label2->Text = L"NTAG I2C Demo Kit:";
			this->label2->TextAlign = System::Drawing::ContentAlignment::TopLeft;
			//this->label2->Click += gcnew System::EventHandler(this, &HelpBox::label2_Click);
			// 
			// linkLabel1
			//
			this->linkLabel1->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->linkLabel1->Location = System::Drawing::Point(60, 90);
			this->linkLabel1->Name = L"linkLabel1";
			//this->linkLabel1->Size = System::Drawing::Size(220, 30);
			this->linkLabel1->TabIndex = 1;
			this->linkLabel1->Text = L"Webpage NTAG I2C";
			this->linkLabel1->TextAlign = System::Drawing::ContentAlignment::TopLeft;
			this->linkLabel1->Click += gcnew System::EventHandler(this, &HelpBox::linkLabel1_Click);
			// 
			// linkLabel2
			//
			this->linkLabel2->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->linkLabel2->Location = System::Drawing::Point(60, 125);
			this->linkLabel2->Name = L"linkLabel2";
			//this->linkLabel2->Size = System::Drawing::Size(220, 30);
			this->linkLabel2->TabIndex = 1;
			this->linkLabel2->Text = L"Datasheet NTAG I2C";
			this->linkLabel2->TextAlign = System::Drawing::ContentAlignment::TopLeft;
			this->linkLabel2->Click += gcnew System::EventHandler(this, &HelpBox::linkLabel2_Click);
			// 
			// linkLabel3
			//
			this->linkLabel3->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->linkLabel3->Location = System::Drawing::Point(60, 160);
			this->linkLabel3->Name = L"linkLabel3";
			//this->linkLabel3->Size = System::Drawing::Size(220, 50);
			this->linkLabel3->TabIndex = 1;
			this->linkLabel3->Text = L"Application note NTAG I2C demo application for Android";
			this->linkLabel3->TextAlign = System::Drawing::ContentAlignment::TopLeft;
			this->linkLabel3->Click += gcnew System::EventHandler(this, &HelpBox::linkLabel3_Click);
			// 
			// linkLabel4
			//
			this->linkLabel4->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->linkLabel4->Location = System::Drawing::Point(60, 215);
			this->linkLabel4->Name = L"linkLabel4";
			//this->linkLabel4->Size = System::Drawing::Size(220, 30);
			this->linkLabel4->TabIndex = 1;
			this->linkLabel4->Text = L"Design files NTAG I2C Demo Kit";
			this->linkLabel4->TextAlign = System::Drawing::ContentAlignment::TopLeft;
			this->linkLabel4->Click += gcnew System::EventHandler(this, &HelpBox::linkLabel4_Click);
			// 
			// linkLabel5
			//
			this->linkLabel5->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->linkLabel5->Location = System::Drawing::Point(60, 250);
			this->linkLabel5->Name = L"linkLabel5";
			//this->linkLabel5->Size = System::Drawing::Size(220, 30);
			this->linkLabel5->TabIndex = 1;
			this->linkLabel5->Text = L"Android application source code NTAG I2C";
			this->linkLabel5->TextAlign = System::Drawing::ContentAlignment::TopLeft;
			this->linkLabel5->Click += gcnew System::EventHandler(this, &HelpBox::linkLabel5_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = this->Logo;
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			//this->pictureBox1->Location = System::Drawing::Point(60, 330);
			this->pictureBox1->Name = L"pictureBox1";
			//this->pictureBox1->Size = System::Drawing::Size(245, 70);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			//this->pictureBox1->Click += gcnew System::EventHandler(this, &HelpBox::pictureBox1_Click);
			// 
			// button1
			// 
			this->button1->BackgroundImage = this->backImage;
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			//this->button1->Location = System::Drawing::Point(150, 458);
			this->button1->Name = L"button1";
			//this->button1->Size = System::Drawing::Size(71, 43);
			this->button1->TabIndex = 2;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &HelpBox::button1_Click);
			// 
			// HelpForm
			// 
			this->ResumeLayout(false);
			this->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
		}

		// If the user presses the picture, is as if he'd pressed the group box
		System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->OnClick(e);
		}

		// If the user presses the label, is as if he'd pressed the group box
		System::Void label1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->OnClick(e);
		}

		// If the user presses the label, is as if he'd pressed the group box
		System::Void label2_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->OnClick(e);
		}

		// If the user presses the link label, it jumps to the corresponding website
		System::Void linkLabel1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			// Specify that the link was visited
			this->linkLabel1->LinkVisited = true;
			// Navigate to a URL
			System::Diagnostics::Process::Start("http://www.nxp.com/products/identification_and_security/smart_label_and_tag_ics/connected_tag_solutions/series/NT3H1101_NT3H1201.html");
		}

		// If the user presses the link label, it jumps to the corresponding website
		System::Void linkLabel2_Click(System::Object^  sender, System::EventArgs^  e)
		{
			// Specify that the link was visited
			this->linkLabel2->LinkVisited = true;
			// Navigate to a URL
			System::Diagnostics::Process::Start("http://www.nxp.com/documents/data_sheet/NT3H1101_1201.pdf");
		}

		// If the user presses the link label, it jumps to the corresponding website
		System::Void linkLabel3_Click(System::Object^  sender, System::EventArgs^  e)
		{
			// Specify that the link was visited
			this->linkLabel3->LinkVisited = true;
			// Navigate to a URL
			System::Diagnostics::Process::Start("http://www.nxp.com/documents/application_note/AN11597.pdf");
		}

		// If the user presses the link label, it jumps to the corresponding website
		System::Void linkLabel4_Click(System::Object^  sender, System::EventArgs^  e)
		{
			// Specify that the link was visited
			this->linkLabel4->LinkVisited = true;
			// Navigate to a URL
			System::Diagnostics::Process::Start("http://www.nxp.com/documents/software/SW309111.zip");
		}

		// If the user presses the link label, it jumps to the corresponding website
		System::Void linkLabel5_Click(System::Object^  sender, System::EventArgs^  e)
		{
			// Specify that the link was visited
			this->linkLabel5->LinkVisited = true;
			// Navigate to a URL
			System::Diagnostics::Process::Start("http://www.nxp.com/documents/software/SW309711.zip");
		}

		// If the user presses the button, is as if he'd pressed the group box
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->mwi == false)
			{
				this->mwi = true;
				this->OnClick(e);
			}
			else
				this->mwi = false;
		}
	};

	// Group box that shows the memory content of the tag				----		//Config tab - Read Tag Memory
	public ref class ReadMemBox : public Panel
	{
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;

	private: System::String^ textBoxText;		// Text that contains the read speed
	private: System::String^ labelText;			// Text that contains the content of the memory
	private: System::String^ label2Text;		// Text that will be in label2
	public: System::Drawing::Image^ backImage;	// Image for the going back button

	//Variables created in order to detect windows form size in dpi
	HDC screen = GetDC(0);
	int dpiX = GetDeviceCaps(screen, LOGPIXELSX);

	protected:
		void OnCreateControl() override
		{
			System::Windows::Forms::Panel::CreateControl();

			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			//
			// ReadMemBox
			//
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->label2);
			this->Location = System::Drawing::Point(0, 0);
			this->Name = L"readMemBox1";
			//this->Size = System::Drawing::Size(278, 455);
			this->TabIndex = 0;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->panel1);
			this->groupBox1->Location = System::Drawing::Point(5, -2);
			this->groupBox1->Name = L"groupBox1";
			//this->groupBox1->Size = System::Drawing::Size(273, 340);
			//Now we have to adapt the size of the window to the size of the screen
			if (dpiX == 120)
			{
				this->groupBox1->Size = System::Drawing::Size(365, 420);
				this->groupBox2->Size = System::Drawing::Size(365, 140);
				this->groupBox2->Location = System::Drawing::Point(5, 420);
				this->Size = System::Drawing::Size(370, 559);
				this->panel1->Location = System::Drawing::Point(3, 16);
				this->panel1->Size = System::Drawing::Size(363, 400);
				this->label1->Location = System::Drawing::Point(3, 1);
				this->label2->Location = System::Drawing::Point(30, 353);
				this->textBox1->Location = System::Drawing::Point(11, 20);
				this->button1->Location = System::Drawing::Point(140, 90);
				this->textBox1->Size = System::Drawing::Size(345, 62);
			}
			else //dpiX == 96 for instance
			{
				this->groupBox1->Size = System::Drawing::Size(273, 340);
				this->groupBox2->Size = System::Drawing::Size(273, 111);
				this->groupBox2->Location = System::Drawing::Point(5, 342);
				this->Size = System::Drawing::Size(278, 455);
				this->textBox1->Size = System::Drawing::Size(247, 32);
				this->panel1->Location = System::Drawing::Point(3, 16);
				this->panel1->Size = System::Drawing::Size(268, 315);
				this->label1->Location = System::Drawing::Point(3, 1);
				this->label2->Location = System::Drawing::Point(30, 353);
				this->textBox1->Location = System::Drawing::Point(11, 20);
				this->button1->Location = System::Drawing::Point(103, 75);
			}
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
//			this->groupBox1->Click += gcnew System::EventHandler(this, &ReadMemBox::groupBox1_Click);
			//
			// groupBox2
			//
			this->groupBox2->Controls->Add(this->textBox1);
			this->groupBox2->Controls->Add(this->button1);
			//this->groupBox2->Location = System::Drawing::Point(5, 342);
			this->groupBox2->Name = L"groupBox1";
			//this->groupBox2->Size = System::Drawing::Size(273, 60);
			this->groupBox2->TabIndex = 0;
			this->groupBox2->TabStop = false;
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox2->Text = L"Read Performance";
//			this->groupBox2->Click += gcnew System::EventHandler(this, &ReadMemBox::groupBox2_Click);
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->Controls->Add(this->label1);
			//this->panel1->Location = System::Drawing::Point(3, 16);
			this->panel1->Name = L"panel1";
			//this->panel1->Size = System::Drawing::Size(272, 315);
			this->panel1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label1->Location = System::Drawing::Point(3, 1);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(49, 14);
			this->label1->TabIndex = 0;
			this->label1->Text = this->labelText;
			this->label1->MouseEnter += gcnew System::EventHandler(this, &ReadMemBox::label1_MouseEnter);
//			this->label1->Click += gcnew System::EventHandler(this, &ReadMemBox::label1_Click);
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label2->Location = System::Drawing::Point(30, 353);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(200, 32);
			this->label2->TabIndex = 2;
			this->label2->BackColor = System::Drawing::Color::Black;
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
//			this->label2->Click += gcnew System::EventHandler(this, &ReadMemBox::label2_Click);
			this->label2->BringToFront();
			this->setLabel(this->label2Text);
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(244)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Enabled = false;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->ForeColor = System::Drawing::SystemColors::WindowText;
			//this->textBox1->Location = System::Drawing::Point(11, 20);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			//this->textBox1->Size = System::Drawing::Size(247, 32);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = this->textBoxText;
			// 
			// button1
			// 
			this->button1->BackgroundImage = this->backImage;
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			//this->button1->Location = System::Drawing::Point(103, 406);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(60, 40);
			this->button1->TabIndex = 2;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->BringToFront();
			this->button1->Click += gcnew System::EventHandler(this, &ReadMemBox::button1_Click);
			// 
			// ReadMemForm
			// 
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);			
		}

	private:
		// This way, the mouse wheel controls the scrollbar of the panel when the mouse is over the label
		System::Void label1_MouseEnter(System::Object^  sender, System::EventArgs^  e)
		{
			this->panel1->Focus();
		}
		// If the user presses the button, is as if he'd pressed the read mem box
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->OnClick(e);
		}

	public:
		// Parses the data received to be visualized
		System::Void updateLabel(BYTE* data, DWORD readBytes)
		{
			this->labelText = "";
			unsigned int i = 0, elm = 0;
			for (; i < 4; i++, elm += 4)
				this->labelText += L"[" + i.ToString("X3") + L"]   " + data[elm].ToString("X2") + ":" + data[elm + 1].ToString("X2")
				+ ":" + data[elm + 2].ToString("X2") + ":" + data[elm + 3].ToString("X2") + "\n";
			for (; elm < readBytes; i++, elm += 4)
			{
				String^ str = "";
				for (unsigned int j = elm; j < elm + 4; j++)
				{
					if (data[j] < 0x20 || data[j] > 0x7D)
						str += ".";
					else
						str += (wchar_t)data[j];
				}
				this->labelText += L"[" + i.ToString("X3") + L"]   " + data[elm].ToString("X2") + ":" + data[elm + 1].ToString("X2")
					+ ":" + data[elm + 2].ToString("X2") + ":" + data[elm + 3].ToString("X2") + "  |" + str + "|\n";
			}

			// If the control has not been created yet, it will be copied when it is created
			if (this->label1 != nullptr)
				label1->Text = labelText;
		}

		// Sets the content of label2
		System::Void setLabel(System::String^ text)
		{
			this->label2Text = text;
			if (this->label2 != nullptr)
			{
				if (text == "")
					this->label2->Hide();
				else
				{
					this->label2->Text = text;
					this->label2->Show();
				}
			}
			this->Refresh();
		}

		// Sets the content of textBox1
		System::Void setTextBox(System::String^ text)
		{
			this->textBoxText = text;
			if (this->textBox1 != nullptr)
				this->textBox1->Text = text;
			this->Refresh();
		}
	};
	
	// Group box that appears when the tag memory has been reset		----		//Config tab - Reset Tag Memory
	public ref class ResetMemBox : public Panel
	{
		private: System::Windows::Forms::GroupBox^  groupBox1;
		private: System::Windows::Forms::GroupBox^  groupBox2;
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::PictureBox^  pictureBox1;
		private: System::Windows::Forms::TextBox^  textBox1;
		private: System::Windows::Forms::Button^  button1;

		private: System::String^ textBoxText;		// Text that contains the reset speed
		public: System::String^ labelText;		// Text that will be in the label2
		public: System::Drawing::Image^ Logo;	// Image that will appear in the picture box
		public: System::Drawing::Image^ backImage;	// Image for the going back button
				//Variables created in order to detect windows form size in dpi
				HDC screen = GetDC(0);
				int dpiX = GetDeviceCaps(screen, LOGPIXELSX);
	protected:
		void OnCreateControl() override
		{
			System::Windows::Forms::Panel::CreateControl();

			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TapTagBox::typeid));
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			// 
			// ResetMemBox
			// 
			this->BackColor = System::Drawing::Color::White;
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Location = System::Drawing::Point(0, 0);
			this->Name = L"resetMemBox1";
			//Now we have to adapt the size of the window to the size of the screen
			if (dpiX == 120)
			{
				this->Size = System::Drawing::Size(365, 559);
				this->groupBox1->Size = System::Drawing::Size(365, 420);
				this->groupBox2->Location = System::Drawing::Point(5, 420);
				this->groupBox2->Size = System::Drawing::Size(365, 135);
				this->label1->Location = System::Drawing::Point(60, 300);
				this->label1->Size = System::Drawing::Size(250, 30);
				this->pictureBox1->Size = System::Drawing::Size(220, 150);
				this->pictureBox1->Location = System::Drawing::Point(80, 100);
				this->button1->Location = System::Drawing::Point(140, 500);
				this->button1->Size = System::Drawing::Size(60, 40);
				this->label2->Location = System::Drawing::Point(80, 400);
				this->label2->Size = System::Drawing::Size(200, 60);
				this->textBox1->Size = System::Drawing::Size(340, 45);
			}
			else //dpiX == 96 for instance
			{
				this->Size = System::Drawing::Size(273, 455);
				this->groupBox1->Size = System::Drawing::Size(273, 340);
				this->groupBox2->Location = System::Drawing::Point(5, 342);
				this->groupBox2->Size = System::Drawing::Size(273, 111);
				this->label1->Location = System::Drawing::Point(30, 255);
				this->label1->Size = System::Drawing::Size(200, 30);
				this->pictureBox1->Size = System::Drawing::Size(225, 139);
				this->pictureBox1->Location = System::Drawing::Point(23, 94);
				this->button1->Location = System::Drawing::Point(110, 410);
				this->button1->Size = System::Drawing::Size(60, 40);
				this->label2->Location = System::Drawing::Point(10, 295);
				this->label2->Size = System::Drawing::Size(50, 50);
				this->textBox1->Size = System::Drawing::Size(247, 32);
			}
			this->AutoSize = true;
			this->TabIndex = 0;
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::White;
			this->groupBox1->Controls->Add(this->label1);
			//this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Location = System::Drawing::Point(5, -2);
			this->groupBox1->Name = L"groupBox1";
			//this->groupBox1->Size = System::Drawing::Size(365, 340); //(273,340)
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
//			this->groupBox1->Click += gcnew System::EventHandler(this, &ResetMemBox::groupBox1_Click);
			//
			// groupBox2
			//
			this->groupBox2->Controls->Add(this->textBox1);
			//this->groupBox2->Location = System::Drawing::Point(5, 342);
			this->groupBox2->Name = L"groupBox1";
			//this->groupBox2->Size = System::Drawing::Size(365, 80); //(273, 60);
			this->groupBox2->TabIndex = 0;
			this->groupBox2->TabStop = false;
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox2->Text = L"Reset Performance";
//			this->groupBox2->Click += gcnew System::EventHandler(this, &ResetMemBox::groupBox2_Click);
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 11.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label1->Location = System::Drawing::Point(30, 255);
			this->label1->Name = L"label1";
			//this->label1->Size = System::Drawing::Size(200, 30);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Tap tag to reset its content";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
//			this->label1->Click += gcnew System::EventHandler(this, &ResetMemBox::label1_Click);
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label2->Location = System::Drawing::Point(30, 295);
			this->label2->Name = L"label2";
			//this->label2->Size = System::Drawing::Size(200, 32);
			this->label2->TabIndex = 2;
			this->label2->BackColor = System::Drawing::Color::Black;
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label2->BringToFront();
//			this->label2->Click += gcnew System::EventHandler(this, &ResetMemBox::label2_Click);
			this->setLabel(this->labelText);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = this->Logo;
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			//this->pictureBox1->Location = System::Drawing::Point(23, 94);
			this->pictureBox1->Name = L"pictureBox1";
			//this->pictureBox1->Size = System::Drawing::Size(225, 139);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
//			this->pictureBox1->Click += gcnew System::EventHandler(this, &ResetMemBox::pictureBox1_Click);
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(244)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Enabled = false;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->ForeColor = System::Drawing::SystemColors::WindowText;
			this->textBox1->Location = System::Drawing::Point(11, 20);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			//this->textBox1->Size = System::Drawing::Size(340, 45); //(247, 32);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = this->textBoxText;
			// 
			// button1
			// 
			this->button1->BackgroundImage = this->backImage;
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			//this->button1->Location = System::Drawing::Point(153, 456);
			this->button1->Name = L"button1";
			//this->button1->Size = System::Drawing::Size(71, 43);
			this->button1->TabIndex = 2;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->BringToFront();
			this->button1->Click += gcnew System::EventHandler(this, &ResetMemBox::button1_Click);
			// 
			// ResetMemBox
			//
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
		}

		// If the user presses the button, is as if he'd pressed the reset mem box
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->OnClick(e);
		}
		
	public:
		// Sets the content of label2
		System::Void setLabel(System::String^ text)
		{
			this->labelText = text;
			if (this->label2 != nullptr)
			{
				if (text == "")
					this->label2->Hide();
				else
				{
					this->label2->Text = text;
					this->label2->Show();
				}
			}
			this->Refresh();
		}

		// Sets the content of textBox1
		System::Void setTextBox(System::String^ text)
		{
			this->textBoxText = text;
			if (this->textBox1 != nullptr)
				this->textBox1->Text = text;
			this->Refresh();
		}
	};
	
	// Group box that shows the session registers of the NTAG I2C		----		//Config tab - Read Session Registers
	public ref class SessionRegBox : public GroupBox
	{
		private: NTAG_I2C_Demo::NativeTreeView^  treeView1;
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
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::Label^  label3;
		private: System::Windows::Forms::Label^  label4;
		private: System::Windows::Forms::Label^  label5;
		private: System::Windows::Forms::Label^  label6;
		private: System::Windows::Forms::Label^  label7;
		private: System::Windows::Forms::Label^  label8;
		private: System::Windows::Forms::Button^  button1;			//Back button
		private: System::Windows::Forms::Label^  label10;

		private: Ntag_I2C_Registers_t* sessionReg = new Ntag_I2C_Registers_t();	// Struct containing the read data
		private: System::String^ label10Text;		// Text that will be in label10
		public: System::Drawing::Image^ backImage;	// Image for the going back button
		public:	event System::EventHandler^ backButtonClick;	// Event that is fired when the back button is pressed
		//Variables created in order to detect windows form size in dpi
		HDC screen = GetDC(0);
		int dpiX = GetDeviceCaps(screen, LOGPIXELSX);

	protected:
		void OnCreateControl() override
		{
			System::Windows::Forms::GroupBox::CreateControl();

			System::Windows::Forms::TreeNode^  treeNode26 = (gcnew System::Windows::Forms::TreeNode(L"IC Product:"));
			System::Windows::Forms::TreeNode^  treeNode27 = (gcnew System::Windows::Forms::TreeNode(L"User memory:"));
			System::Windows::Forms::TreeNode^  treeNode28 = (gcnew System::Windows::Forms::TreeNode(L"GENERAL CHIP INFORMATION", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {
				treeNode26,
					treeNode27
			}));
			System::Windows::Forms::TreeNode^  treeNode29 = (gcnew System::Windows::Forms::TreeNode(L"I2C RST on start is:"));
			System::Windows::Forms::TreeNode^  treeNode30 = (gcnew System::Windows::Forms::TreeNode(L"NTAG CONFIGURATION", gcnew cli::array< System::Windows::Forms::TreeNode^  >(1) { treeNode29 }));
			System::Windows::Forms::TreeNode^  treeNode31 = (gcnew System::Windows::Forms::TreeNode(L"FD_OFF is:"));
			System::Windows::Forms::TreeNode^  treeNode32 = (gcnew System::Windows::Forms::TreeNode(L"FD_ON is:"));
			System::Windows::Forms::TreeNode^  treeNode33 = (gcnew System::Windows::Forms::TreeNode(L"Last NDEF Block is:"));
			System::Windows::Forms::TreeNode^  treeNode34 = (gcnew System::Windows::Forms::TreeNode(L"NDEF Data Read is:"));
			System::Windows::Forms::TreeNode^  treeNode35 = (gcnew System::Windows::Forms::TreeNode(L"RF field present is:"));
			System::Windows::Forms::TreeNode^  treeNode36 = (gcnew System::Windows::Forms::TreeNode(L"FIELD DETECTION", gcnew cli::array< System::Windows::Forms::TreeNode^  >(5) {
				treeNode31,
					treeNode32, treeNode33, treeNode34, treeNode35
			}));
			System::Windows::Forms::TreeNode^  treeNode37 = (gcnew System::Windows::Forms::TreeNode(L"Pass Through is:"));
			System::Windows::Forms::TreeNode^  treeNode38 = (gcnew System::Windows::Forms::TreeNode(L"I2C locked is:"));
			System::Windows::Forms::TreeNode^  treeNode39 = (gcnew System::Windows::Forms::TreeNode(L"RF locked is:"));
			System::Windows::Forms::TreeNode^  treeNode40 = (gcnew System::Windows::Forms::TreeNode(L"SRAM I2C ready is:"));
			System::Windows::Forms::TreeNode^  treeNode41 = (gcnew System::Windows::Forms::TreeNode(L"SRAM RF ready is:"));
			System::Windows::Forms::TreeNode^  treeNode42 = (gcnew System::Windows::Forms::TreeNode(L"FromRF to I2C is:"));
			System::Windows::Forms::TreeNode^  treeNode43 = (gcnew System::Windows::Forms::TreeNode(L"PASS THROUGH", gcnew cli::array< System::Windows::Forms::TreeNode^  >(6) {
				treeNode37,
					treeNode38, treeNode39, treeNode40, treeNode41, treeNode42
			}));
			System::Windows::Forms::TreeNode^  treeNode44 = (gcnew System::Windows::Forms::TreeNode(L"SRAM Mirror is:"));
			System::Windows::Forms::TreeNode^  treeNode45 = (gcnew System::Windows::Forms::TreeNode(L"SRAM Mirror block is:"));
			System::Windows::Forms::TreeNode^  treeNode46 = (gcnew System::Windows::Forms::TreeNode(L"SRAM MIRROR", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {
				treeNode44,
					treeNode45
			}));
			System::Windows::Forms::TreeNode^  treeNode47 = (gcnew System::Windows::Forms::TreeNode(L"WD_LS Timer is:"));
			System::Windows::Forms::TreeNode^  treeNode48 = (gcnew System::Windows::Forms::TreeNode(L"WD_MS Timer is:"));
			System::Windows::Forms::TreeNode^  treeNode49 = (gcnew System::Windows::Forms::TreeNode(L"I2C Clock Stretch is:"));
			System::Windows::Forms::TreeNode^  treeNode50 = (gcnew System::Windows::Forms::TreeNode(L"I2C", gcnew cli::array< System::Windows::Forms::TreeNode^  >(3) {
				treeNode47,
					treeNode48, treeNode49
			}));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
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
			this->treeView1 = (gcnew NTAG_I2C_Demo::NativeTreeView());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->Controls->Add(this->button1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label10);
			this->Location = System::Drawing::Point(5, -2);
			this->Name = L"groupBox1";
			//Now we have to adapt the size of the window to the size of the screen
			if (dpiX == 120)
			{
				this->Size = System::Drawing::Size(365, 559);
				this->button1->Location = System::Drawing::Point(140, 500);
				this->panel1->Size = System::Drawing::Size(360, 480);
				this->treeView1->Size = System::Drawing::Size(360, 364);
				this->label1->Size = System::Drawing::Size(140, 18);
				this->label2->Size = System::Drawing::Size(120, 18);
				this->label3->Size = System::Drawing::Size(220, 18);
				this->label4->Size = System::Drawing::Size(230, 18);
				this->label5->Size = System::Drawing::Size(50, 18);
				this->label6->Size = System::Drawing::Size(50, 18);
				this->label7->Size = System::Drawing::Size(50, 18);
				this->label8->Size = System::Drawing::Size(50, 18);
				this->label1->Location = System::Drawing::Point(140, 16);
				this->label2->Location = System::Drawing::Point(140, 16);
				this->label3->Location = System::Drawing::Point(110, 16);
				this->label4->Location = System::Drawing::Point(110, 16);
				this->label5->Location = System::Drawing::Point(200, 16);
				this->label6->Location = System::Drawing::Point(200, 16);
				this->label7->Location = System::Drawing::Point(200, 16);
				this->label8->Location = System::Drawing::Point(200, 16);
				this->checkBox11->Size = System::Drawing::Size(15, 14);
				this->checkBox10->Size = System::Drawing::Size(15, 14);
				this->checkBox9->Size = System::Drawing::Size(15, 14);
				this->checkBox8->Size = System::Drawing::Size(15, 14);
				this->checkBox7->Size = System::Drawing::Size(15, 14);
				this->checkBox6->Size = System::Drawing::Size(15, 14);
				this->checkBox5->Size = System::Drawing::Size(15, 14);
				this->checkBox4->Size = System::Drawing::Size(15, 14);
				this->checkBox3->Size = System::Drawing::Size(15, 14);
				this->checkBox2->Size = System::Drawing::Size(15, 14);
				this->checkBox1->Size = System::Drawing::Size(15, 14);
				this->checkBox1->Location = System::Drawing::Point(240, 370);
				this->checkBox2->Location = System::Drawing::Point(240, 370);
				this->checkBox3->Location = System::Drawing::Point(240, 370);
				this->checkBox4->Location = System::Drawing::Point(240, 370);
				this->checkBox5->Location = System::Drawing::Point(240, 370);
				this->checkBox6->Location = System::Drawing::Point(240, 370);
				this->checkBox7->Location = System::Drawing::Point(240, 370);
				this->checkBox8->Location = System::Drawing::Point(240, 370);
				this->checkBox9->Location = System::Drawing::Point(240, 370);
				this->checkBox10->Location = System::Drawing::Point(240, 370);
				this->checkBox11->Location = System::Drawing::Point(240, 370);
			}
			else //dpiX == 96 for instance
			{
				this->Size = System::Drawing::Size(273, 455);
				this->button1->Location = System::Drawing::Point(98, 408);
				this->panel1->Size = System::Drawing::Size(273, 389);
				this->treeView1->Size = System::Drawing::Size(270, 364);
				this->label1->Size = System::Drawing::Size(130, 18);
				this->label2->Size = System::Drawing::Size(80, 18);
				this->label3->Size = System::Drawing::Size(175, 18);
				this->label4->Size = System::Drawing::Size(175, 18);
				this->label5->Size = System::Drawing::Size(50, 18);
				this->label6->Size = System::Drawing::Size(50, 18);
				this->label7->Size = System::Drawing::Size(50, 18);
				this->label8->Size = System::Drawing::Size(50, 18);
				this->label1->Location = System::Drawing::Point(120, 16);
				this->label2->Location = System::Drawing::Point(140, 16);
				this->label3->Location = System::Drawing::Point(87, 16);
				this->label4->Location = System::Drawing::Point(85, 16);
				this->label5->Location = System::Drawing::Point(180, 16);
				this->label6->Location = System::Drawing::Point(180, 16);
				this->label7->Location = System::Drawing::Point(180, 16);
				this->label8->Location = System::Drawing::Point(180, 16);
				this->checkBox11->Size = System::Drawing::Size(15, 14);
				this->checkBox10->Size = System::Drawing::Size(15, 14);
				this->checkBox9->Size = System::Drawing::Size(15, 14);
				this->checkBox8->Size = System::Drawing::Size(15, 14);
				this->checkBox7->Size = System::Drawing::Size(15, 14);
				this->checkBox6->Size = System::Drawing::Size(15, 14);
				this->checkBox5->Size = System::Drawing::Size(15, 14);
				this->checkBox4->Size = System::Drawing::Size(15, 14);
				this->checkBox3->Size = System::Drawing::Size(15, 14);
				this->checkBox2->Size = System::Drawing::Size(15, 14);
				this->checkBox1->Size = System::Drawing::Size(15, 14);
				this->checkBox1->Location = System::Drawing::Point(220, 370);
				this->checkBox2->Location = System::Drawing::Point(220, 370);
				this->checkBox3->Location = System::Drawing::Point(220, 370);
				this->checkBox4->Location = System::Drawing::Point(220, 370);
				this->checkBox5->Location = System::Drawing::Point(220, 370);
				this->checkBox6->Location = System::Drawing::Point(220, 370);
				this->checkBox7->Location = System::Drawing::Point(220, 370);
				this->checkBox8->Location = System::Drawing::Point(220, 370);
				this->checkBox9->Location = System::Drawing::Point(220, 370);
				this->checkBox10->Location = System::Drawing::Point(220, 370);
				this->checkBox11->Location = System::Drawing::Point(220, 370);
			}
			this->TabIndex = 0;
			this->TabStop = false;
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->BackColor = System::Drawing::Color::Transparent;
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
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->label6);
			this->panel1->Controls->Add(this->label7);
			this->panel1->Controls->Add(this->label8);
			this->panel1->Controls->Add(this->treeView1);
			this->panel1->Location = System::Drawing::Point(0, 16);
			this->panel1->Name = L"panel1";
			//this->panel1->Size = System::Drawing::Size(273, 389);
			this->panel1->TabIndex = 1;
			// 
			// checkBox11
			// 
			this->checkBox11->AutoSize = true;
			this->checkBox11->Enabled = false;
			//this->checkBox11->Location = System::Drawing::Point(240, 370);
			this->checkBox11->Name = L"checkBox11";
			//this->checkBox11->Size = System::Drawing::Size(15, 14);
			this->checkBox11->TabIndex = 11;
			this->checkBox11->UseVisualStyleBackColor = true;
			// 
			// checkBox10
			// 
			this->checkBox10->AutoSize = true;
			this->checkBox10->Enabled = false;
			//this->checkBox10->Location = System::Drawing::Point(240, 332);
			this->checkBox10->Name = L"checkBox10";
			//this->checkBox10->Size = System::Drawing::Size(15, 14);
			this->checkBox10->TabIndex = 10;
			this->checkBox10->UseVisualStyleBackColor = true;
			// 
			// checkBox9
			// 
			this->checkBox9->AutoSize = true;
			this->checkBox9->Enabled = false;
			//this->checkBox9->Location = System::Drawing::Point(240, 292);
			this->checkBox9->Name = L"checkBox9";
			//this->checkBox9->Size = System::Drawing::Size(15, 14);
			this->checkBox9->TabIndex = 9;
			this->checkBox9->UseVisualStyleBackColor = true;
			// 
			// checkBox8
			// 
			this->checkBox8->AutoSize = true;
			this->checkBox8->Enabled = false;
			//this->checkBox8->Location = System::Drawing::Point(240, 257);
			this->checkBox8->Name = L"checkBox8";
			//this->checkBox8->Size = System::Drawing::Size(15, 14);
			this->checkBox8->TabIndex = 8;
			this->checkBox8->UseVisualStyleBackColor = true;
			// 
			// checkBox7
			// 
			this->checkBox7->AutoSize = true;
			this->checkBox7->Enabled = false;
			//this->checkBox7->Location = System::Drawing::Point(240, 219);
			this->checkBox7->Name = L"checkBox7";
			//this->checkBox7->Size = System::Drawing::Size(15, 14);
			this->checkBox7->TabIndex = 7;
			this->checkBox7->UseVisualStyleBackColor = true;
			// 
			// checkBox6
			// 
			this->checkBox6->AutoSize = true;
			this->checkBox6->Enabled = false;
			//this->checkBox6->Location = System::Drawing::Point(240, 183);
			this->checkBox6->Name = L"checkBox6";
			//this->checkBox6->Size = System::Drawing::Size(15, 14);
			this->checkBox6->TabIndex = 6;
			this->checkBox6->UseVisualStyleBackColor = true;
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Enabled = false;
			//this->checkBox5->Location = System::Drawing::Point(240, 151);
			this->checkBox5->Name = L"checkBox5";
			//this->checkBox5->Size = System::Drawing::Size(15, 14);
			this->checkBox5->TabIndex = 5;
			this->checkBox5->UseVisualStyleBackColor = true;
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Enabled = false;
			//this->checkBox4->Location = System::Drawing::Point(240, 120);
			this->checkBox4->Name = L"checkBox4";
			//this->checkBox4->Size = System::Drawing::Size(15, 14);
			this->checkBox4->TabIndex = 4;
			this->checkBox4->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Enabled = false;
			//this->checkBox3->Location = System::Drawing::Point(240, 89);
			this->checkBox3->Name = L"checkBox3";
			//this->checkBox3->Size = System::Drawing::Size(15, 14);
			this->checkBox3->TabIndex = 3;
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Enabled = false;
			//this->checkBox2->Location = System::Drawing::Point(240, 57);
			this->checkBox2->Name = L"checkBox2";
			//this->checkBox2->Size = System::Drawing::Size(15, 14);
			this->checkBox2->TabIndex = 2;
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Enabled = false;
			//this->checkBox1->Location = System::Drawing::Point(240, 28);
			this->checkBox1->Name = L"checkBox1";
			//this->checkBox1->Size = System::Drawing::Size(15, 14);
			this->checkBox1->TabIndex = 1;
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label1->Location = System::Drawing::Point(135, 16);
			this->label1->Name = L"label1";
			//this->label1->Size = System::Drawing::Size(120, 18);
			this->label1->TabIndex = 12;
			this->label1->Text = L"label1";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label2->Location = System::Drawing::Point(135, 16);
			this->label2->Name = L"label2";
			//this->label2->Size = System::Drawing::Size(120, 18);
			this->label2->TabIndex = 12;
			this->label2->Text = L"label2";
			this->label2->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 8.00F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label3->Location = System::Drawing::Point(109, 16);
			this->label3->Name = L"label3";
			//this->label3->Size = System::Drawing::Size(146, 18);
			this->label3->TabIndex = 12;
			this->label3->Text = L"label3";
			//this->label3->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label4
			// 
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 8.00F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label4->Location = System::Drawing::Point(104, 16);
			this->label4->Name = L"label4";
			//this->label4->Size = System::Drawing::Size(151, 18);
			this->label4->TabIndex = 12;
			this->label4->Text = L"label4";
			//this->label4->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label5
			// 
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label5->Location = System::Drawing::Point(135, 16);
			this->label5->Name = L"label5";
			//this->label5->Size = System::Drawing::Size(120, 18);
			this->label5->TabIndex = 12;
			this->label5->Text = L"label5";
			this->label5->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label6
			// 
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label6->Location = System::Drawing::Point(135, 16);
			this->label6->Name = L"label6";
			//this->label6->Size = System::Drawing::Size(120, 18);
			this->label6->TabIndex = 12;
			this->label6->Text = L"label6";
			this->label6->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label7
			// 
			this->label7->BackColor = System::Drawing::Color::Transparent;
			this->label7->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label7->Location = System::Drawing::Point(135, 16);
			this->label7->Name = L"label7";
			//this->label7->Size = System::Drawing::Size(120, 18);
			this->label7->TabIndex = 12;
			this->label7->Text = L"label7";
			this->label7->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label8
			// 
			this->label8->BackColor = System::Drawing::Color::Transparent;
			this->label8->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label8->Location = System::Drawing::Point(135, 16);
			this->label8->Name = L"label8";
			//this->label8->Size = System::Drawing::Size(120, 18);
			this->label8->TabIndex = 12;
			this->label8->Text = L"label8";
			this->label8->TextAlign = System::Drawing::ContentAlignment::TopRight;
			//
			// hiddenElements
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
			this->label2->Hide();
			this->label3->Hide();
			this->label4->Hide();
			this->label5->Hide();
			this->label6->Hide();
			this->label7->Hide();
			this->label8->Hide();
			//
			// treeView1
			// 
			this->treeView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->treeView1->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->treeView1->Location = System::Drawing::Point(3, 0);
			this->treeView1->Name = L"treeView1";
			treeNode26->Name = L"Node1";
			treeNode26->Text = L"IC Product:";
			treeNode27->Name = L"Node2";
			treeNode27->Text = L"User memory:";
			treeNode28->Name = L"Node0";
			treeNode28->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode28->Text = L"GENERAL CHIP INFORMATION";
			treeNode29->Name = L"Node4";
			treeNode29->Text = L"I2C RST on start is:";
			treeNode30->Name = L"Node3";
			treeNode30->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode30->Text = L"NTAG CONFIGURATION";
			treeNode31->Name = L"Node6";
			treeNode31->Text = L"FD_OFF is:";
			treeNode32->Name = L"Node7";
			treeNode32->Text = L"FD_ON is:";
			treeNode33->Name = L"Node8";
			treeNode33->Text = L"Last NDEF Block is:";
			treeNode34->Name = L"Node0";
			treeNode34->Text = L"NDEF Data Read is:";
			treeNode35->Name = L"Node1";
			treeNode35->Text = L"RF field present is:";
			treeNode36->Name = L"Node5";
			treeNode36->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode36->Text = L"FIELD DETECTION";
			treeNode37->Name = L"Node3";
			treeNode37->Text = L"Pass Through is:";
			treeNode38->Name = L"Node4";
			treeNode38->Text = L"I2C locked is:";
			treeNode39->Name = L"Node5";
			treeNode39->Text = L"RF locked is:";
			treeNode40->Name = L"Node6";
			treeNode40->Text = L"SRAM I2C ready is:";
			treeNode41->Name = L"Node7";
			treeNode41->Text = L"SRAM RF ready is:";
			treeNode42->Name = L"Node8";
			treeNode42->Text = L"FromRF to I2C is:";
			treeNode43->Name = L"Node2";
			treeNode43->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode43->Text = L"PASS THROUGH";
			treeNode44->Name = L"Node10";
			treeNode44->Text = L"SRAM Mirror is:";
			treeNode45->Name = L"Node11";
			treeNode45->Text = L"SRAM Mirror block is:";
			treeNode46->Name = L"Node9";
			treeNode46->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode46->Text = L"SRAM MIRROR";
			treeNode47->Name = L"Node13";
			treeNode47->Text = L"WD_LS Timer is:";
			treeNode48->Name = L"Node14";
			treeNode48->Text = L"WD_MS Timer is:";
			treeNode49->Name = L"Node15";
			treeNode49->Text = L"I2C Clock Stretch is:";
			treeNode50->Name = L"Node12";
			treeNode50->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode50->Text = L"I2C";
			this->treeView1->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(6) {
				treeNode28, treeNode30, treeNode36,
					treeNode43, treeNode46, treeNode50
			});
			this->treeView1->Scrollable = false;
			this->treeView1->ShowLines = false;
			this->treeView1->Indent = 9;
			this->treeView1->TabIndex = 0;
			this->treeView1->AfterCollapse += gcnew System::Windows::Forms::TreeViewEventHandler(this, &SessionRegBox::treeView1_AfterExplapse);
			this->treeView1->AfterExpand += gcnew System::Windows::Forms::TreeViewEventHandler(this, &SessionRegBox::treeView1_AfterExplapse);
			this->treeView1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &SessionRegBox::treeView1_MouseWheel);
			this->treeView1->Nodes[0]->Expand();
			// 
			// button1
			// 
			this->button1->BackgroundImage = this->backImage;
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			//this->button1->Location = System::Drawing::Point(98, 408);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(60, 40);
			this->button1->TabIndex = 2;
			this->button1->BringToFront();
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &SessionRegBox::button1_Click);
			// 
			// label10
			// 
			this->label10->Font = (gcnew System::Drawing::Font(L"Arial", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(30, 353);
			this->label10->Name = L"label2";
			this->label10->Size = System::Drawing::Size(200, 32);
			this->label10->TabIndex = 2;
			this->label10->BackColor = System::Drawing::Color::Black;
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label10->BringToFront();
			this->setLabel(this->label10Text);
			// 
			// SessionRegForm
			// 
			this->updateParsing();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
		}

			// Every time a tree node expands or collapses we need to resize the tree view according to the new size (so that the srollbar from the panel appears
			// when it is needed) and check if the checkboxes need to be shown or hidden
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
					this->Refresh();
				}
				else
					this->label1->Hide();
				if (this->treeView1->Nodes[0]->Nodes[1]->IsVisible)
				{
					this->label2->Location = System::Drawing::Point(this->label2->Location.X, this->treeView1->Nodes[0]->Nodes[1]->Bounds.Location.Y);
					this->label2->Show();
					this->Refresh();
				}
				else
					this->label2->Hide();
				if (this->treeView1->Nodes[1]->Nodes[0]->IsVisible)
				{
					this->checkBox1->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[1]->Nodes[0]->Bounds.Location.Y + 4);
					this->checkBox1->Show();
					this->Refresh();
				}
				else
					this->checkBox1->Hide();
				if (this->treeView1->Nodes[2]->Nodes[0]->IsVisible)
				{
					this->label3->Location = System::Drawing::Point(this->label3->Location.X, this->treeView1->Nodes[2]->Nodes[0]->Bounds.Location.Y);
					this->label3->Show();
					this->Refresh();
				}
				else
					this->label3->Hide();
				if (this->treeView1->Nodes[2]->Nodes[1]->IsVisible)
				{
					this->label4->Location = System::Drawing::Point(this->label4->Location.X, this->treeView1->Nodes[2]->Nodes[1]->Bounds.Location.Y);
					this->label4->Show();
					this->Refresh();
				}
				else
					this->label4->Hide();
				if (this->treeView1->Nodes[2]->Nodes[2]->IsVisible)
				{
					this->label5->Location = System::Drawing::Point(this->label5->Location.X, this->treeView1->Nodes[2]->Nodes[2]->Bounds.Location.Y);
					this->label5->Show();
					this->Refresh();
				}
				else
					this->label5->Hide();
				if (this->treeView1->Nodes[2]->Nodes[3]->IsVisible)
				{
					this->checkBox2->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[2]->Nodes[3]->Bounds.Location.Y + 4);
					this->checkBox2->Show();
					this->Refresh();
				}
				else
					this->checkBox2->Hide();
				if (this->treeView1->Nodes[2]->Nodes[4]->IsVisible)
				{
					this->checkBox3->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[2]->Nodes[4]->Bounds.Location.Y + 4);
					this->checkBox3->Show();
					this->Refresh();
				}
				else
					this->checkBox3->Hide();
				if (this->treeView1->Nodes[3]->Nodes[0]->IsVisible)
				{
					this->checkBox4->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[3]->Nodes[0]->Bounds.Location.Y + 4);
					this->checkBox4->Show();
					this->Refresh();
				}
				else
					this->checkBox4->Hide();
				if (this->treeView1->Nodes[3]->Nodes[1]->IsVisible)
				{
					this->checkBox5->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[3]->Nodes[1]->Bounds.Location.Y + 4);
					this->checkBox5->Show();
					this->Refresh();
				}
				else
					this->checkBox5->Hide();
				if (this->treeView1->Nodes[3]->Nodes[2]->IsVisible)
				{
					this->checkBox6->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[3]->Nodes[2]->Bounds.Location.Y + 4);
					this->checkBox6->Show();
					this->Refresh();
				}
				else
					this->checkBox6->Hide();
				if (this->treeView1->Nodes[3]->Nodes[3]->IsVisible)
				{
					this->checkBox7->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[3]->Nodes[3]->Bounds.Location.Y + 4);
					this->checkBox7->Show();
					this->Refresh();
				}
				else
					this->checkBox7->Hide();
				if (this->treeView1->Nodes[3]->Nodes[4]->IsVisible)
				{
					this->checkBox8->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[3]->Nodes[4]->Bounds.Location.Y + 4);
					this->checkBox8->Show();
					this->Refresh();
				}
				else
					this->checkBox8->Hide();
				if (this->treeView1->Nodes[3]->Nodes[5]->IsVisible)
				{
					this->checkBox9->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[3]->Nodes[5]->Bounds.Location.Y + 4);
					this->checkBox9->Show();
					this->Refresh();
				}
				else
					this->checkBox9->Hide();
				if (this->treeView1->Nodes[4]->Nodes[0]->IsVisible)
				{
					this->checkBox10->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[4]->Nodes[0]->Bounds.Location.Y + 4);
					this->checkBox10->Show();
					this->Refresh();
				}
				else
					this->checkBox10->Hide();
				if (this->treeView1->Nodes[4]->Nodes[1]->IsVisible)
				{
					this->label6->Location = System::Drawing::Point(this->label6->Location.X, this->treeView1->Nodes[4]->Nodes[1]->Bounds.Location.Y);
					this->label6->Show();
					this->Refresh();
				}
				else
					this->label6->Hide();
				if (this->treeView1->Nodes[5]->Nodes[0]->IsVisible)
				{
					this->label7->Location = System::Drawing::Point(this->label7->Location.X, this->treeView1->Nodes[5]->Nodes[0]->Bounds.Location.Y);
					this->label7->Show();
					this->Refresh();
				}
				else
					this->label7->Hide();
				if (this->treeView1->Nodes[5]->Nodes[1]->IsVisible)
				{
					this->label8->Location = System::Drawing::Point(this->label8->Location.X, this->treeView1->Nodes[5]->Nodes[1]->Bounds.Location.Y);
					this->label8->Show();
					this->Refresh();
				}
				else
					this->label8->Hide();
				if (this->treeView1->Nodes[5]->Nodes[2]->IsVisible)
				{
					this->checkBox11->Location = System::Drawing::Point(this->checkBox1->Location.X, this->treeView1->Nodes[5]->Nodes[2]->Bounds.Location.Y + 4);
					this->checkBox11->Show();
					this->Refresh();
				}
				else
					this->checkBox11->Hide();
			}

			// This way, the mouse wheel controls the scrollbar of the panel when the mouse is over the tree view
			System::Void treeView1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			{
				this->panel1->Focus();
			}

			// When button1 is pressed, it fires a backButtonClick event
			System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
			{
				backButtonClick(this, gcnew EventArgs());
			}

			// Internal function for initializing the SessionRegistersBox
			System::Void updateParsing()
			{
				// Convert from ASCII to Unicode
				int strLength = strlen(this->sessionReg->REG_Manufacture);
				this->label1->Text = "";
				for (int i = 0; i < strLength; i++)
					this->label1->Text += (wchar_t)this->sessionReg->REG_Manufacture[i];
				this->label2->Text = this->sessionReg->REG_Mem_size + " Bytes";
				this->checkBox1->Checked = Convert::ToBoolean(this->sessionReg->REG_I2C_RST_ON_OFF);
				if (this->sessionReg->REG_FD_OFF[0] == '0')
					if (this->sessionReg->REG_FD_OFF[1] == '0')
						this->label3->Text = L"00b - Field switched off";
					else
						this->label3->Text = L"01b - Set to HALT or field off";
				else
					if (this->sessionReg->REG_FD_OFF[1] == '0')
						this->label3->Text = L"10b - LAST_NDEF_BLOCK read or fie.."; // LAST_NDEF_BLOCK read or field off
					else
						this->label3->Text = L"11b - Data R/W by I2C or field off";
				if (this->sessionReg->REG_FD_ON[0] == '0')
					if (this->sessionReg->REG_FD_ON[1] == '0')
						this->label4->Text = L"00b - Field switched on";
					else
						this->label4->Text = L"01b - First valid Start-of-Frame";
				else
					if (this->sessionReg->REG_FD_ON[1] == '0')
						this->label4->Text = L"10b - Selection of Tag";
					else
						this->label4->Text = L"11b - Data to read from I2C/data...";
				this->label5->Text = this->sessionReg->REG_LAST_NDEF_PAGE.ToString();
				this->checkBox2->Checked = Convert::ToBoolean(this->sessionReg->REG_NDEF_DATA_READ);
				this->checkBox3->Checked = Convert::ToBoolean(this->sessionReg->REG_RF_FIELD_PRESENT);
				this->checkBox4->Checked = Convert::ToBoolean(this->sessionReg->REG_PTHRU_ON_OFF);
				this->checkBox5->Checked = Convert::ToBoolean(this->sessionReg->REG_I2C_LOCKED);
				this->checkBox6->Checked = Convert::ToBoolean(this->sessionReg->REG_RF_LOCKED);
				this->checkBox7->Checked = Convert::ToBoolean(this->sessionReg->REG_SRAM_I2C_READY);
				this->checkBox8->Checked = Convert::ToBoolean(this->sessionReg->REG_SRAM_RF_READY);
				this->checkBox9->Checked = Convert::ToBoolean(this->sessionReg->REG_PTHRU_DIR);
				this->checkBox10->Checked = Convert::ToBoolean(this->sessionReg->REG_SRAM_MIRROR_ON_OFF);
				this->label6->Text = this->sessionReg->REG_SM_Reg.ToString();
				this->label7->Text = this->sessionReg->REG_WD_LS_Reg.ToString();
				this->label8->Text = this->sessionReg->REG_WD_MS_Reg.ToString();
				this->checkBox11->Checked = Convert::ToBoolean(this->sessionReg->REG_I2C_CLOCK_STR);
			}

		public:
			// Initializes the SessionRegistersBox according to the structure passed as a parameter
			System::Void updateBox(Ntag_I2C_Registers_t sessionReg)
			{
				*this->sessionReg = sessionReg;

				if (this->label2 != nullptr)
					this->updateParsing();
			}

			// Sets the content of label10
			System::Void setLabel(System::String^ text)
			{
				this->label10Text = text;
				if (this->label10 != nullptr)
				{
					if (text == "")
						this->label10->Hide();
					else
					{
						this->label10->Text = text;
						this->label10->Show();
					}
				}
				this->Refresh();
			}
	};

	// Group box that shows the config registers of the NTAG I2C		----		//Config tab - Read/Write config Registers
	public ref class ConfigRegBox : public Panel
	{
		private: System::Windows::Forms::GroupBox^  groupBox1;
		private: NTAG_I2C_Demo::GrackButton^  grackButton2;
		private: System::Windows::Forms::Button^  button1;
		private: System::Windows::Forms::GroupBox^  groupBox2;
		private: NTAG_I2C_Demo::NativeTreeView^  treeView1;					
		private: System::Windows::Forms::Panel^  panel2;
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::TextBox^  textBox6;
		private: System::Windows::Forms::TextBox^  textBox5;
		private: System::Windows::Forms::TextBox^  textBox4;
		private: System::Windows::Forms::TextBox^  textBox3;
		private: System::Windows::Forms::ComboBox^  comboBox2;
		private: System::Windows::Forms::ComboBox^  comboBox1;
		private: NTAG_I2C_Demo::GrackButton^  grackButton4;
		private: NTAG_I2C_Demo::GrackButton^  grackButton5;
		private: NTAG_I2C_Demo::GrackButton^  grackButton8;
		private: NTAG_I2C_Demo::GrackButton^  grackButton7;
		public: NTAG_I2C_Demo::GrackButton^  grackButton1;
		private: System::Windows::Forms::Label^  label10;

		private: Ntag_I2C_Registers_t* configReg = new Ntag_I2C_Registers_t();	// Struct containing the read data
		private: System::String^ label10Text;		// Text that will be in label10
		public: System::Drawing::Image^ backImage;	// Image for the going back button
		public:	event System::EventHandler^ backButtonClick;	// Event that is fired when the back button is pressed

		//Variables created in order to detect windows form size in dpi
		HDC screen = GetDC(0);
		int dpiX = GetDeviceCaps(screen, LOGPIXELSX);

	protected:
		void OnCreateControl() override
		{
			System::Windows::Forms::Panel::CreateControl();

			System::Windows::Forms::TreeNode^  treeNode39 = (gcnew System::Windows::Forms::TreeNode(L"IC Product:"));
			System::Windows::Forms::TreeNode^  treeNode40 = (gcnew System::Windows::Forms::TreeNode(L"User memory:"));
			System::Windows::Forms::TreeNode^  treeNode41 = (gcnew System::Windows::Forms::TreeNode(L"GENERAL CHIP INFORMATION", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {
				treeNode39,
					treeNode40
			}));
			System::Windows::Forms::TreeNode^  treeNode42 = (gcnew System::Windows::Forms::TreeNode(L"FD_OFF is:"));
			System::Windows::Forms::TreeNode^  treeNode43 = (gcnew System::Windows::Forms::TreeNode(L"FD_ON is:"));
			System::Windows::Forms::TreeNode^  treeNode44 = (gcnew System::Windows::Forms::TreeNode(L"FIELD DETECTION", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {
				treeNode42,
					treeNode43
			}));
			System::Windows::Forms::TreeNode^  treeNode46 = (gcnew System::Windows::Forms::TreeNode(L"Direction:"));
			System::Windows::Forms::TreeNode^  treeNode47 = (gcnew System::Windows::Forms::TreeNode(L"Write from RF is:"));
			System::Windows::Forms::TreeNode^  treeNode48 = (gcnew System::Windows::Forms::TreeNode(L"PASS THROUGH", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {
					treeNode46, treeNode47
			}));
			System::Windows::Forms::TreeNode^  treeNode49 = (gcnew System::Windows::Forms::TreeNode(L"Last NDEF Block is:"));
			System::Windows::Forms::TreeNode^  treeNode51 = (gcnew System::Windows::Forms::TreeNode(L"SRAM Mirror Block is:"));
			System::Windows::Forms::TreeNode^  treeNode52 = (gcnew System::Windows::Forms::TreeNode(L"SRAM EEPROM SETTINGS", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {
				treeNode49, treeNode51
			}));
			System::Windows::Forms::TreeNode^  treeNode53 = (gcnew System::Windows::Forms::TreeNode(L"WD_LS Timer is:"));
			System::Windows::Forms::TreeNode^  treeNode54 = (gcnew System::Windows::Forms::TreeNode(L"WD_MS Timer is:"));
			System::Windows::Forms::TreeNode^  treeNode55 = (gcnew System::Windows::Forms::TreeNode(L"I2C Clock stretch is:"));
			System::Windows::Forms::TreeNode^  treeNode56 = (gcnew System::Windows::Forms::TreeNode(L"I2C RST on start is:"));
			System::Windows::Forms::TreeNode^  treeNode57 = (gcnew System::Windows::Forms::TreeNode(L"I2C SETTINGS", gcnew cli::array< System::Windows::Forms::TreeNode^  >(4) {
				treeNode53,
					treeNode54, treeNode55, treeNode56
			}));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->grackButton2 = (gcnew NTAG_I2C_Demo::GrackButton());
			this->grackButton1 = (gcnew NTAG_I2C_Demo::GrackButton());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->grackButton5 = (gcnew NTAG_I2C_Demo::GrackButton());
			this->grackButton4 = (gcnew NTAG_I2C_Demo::GrackButton());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->treeView1 = (gcnew NTAG_I2C_Demo::NativeTreeView());
			this->grackButton7 = (gcnew NTAG_I2C_Demo::GrackButton());
			this->grackButton8 = (gcnew NTAG_I2C_Demo::GrackButton());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->panel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->Controls->Add(this->button1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->label10);
			this->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Location = System::Drawing::Point(0, 0);
			this->Name = L"panel1";
			//this->Size = System::Drawing::Size(284, 457);
			//Now we have to adapt the size of the window to the size of the screen
			if (dpiX == 120)
			{
				this->Size = System::Drawing::Size(365, 559);
				this->button1->Location = System::Drawing::Point(140, 500);
				this->groupBox1->Size = System::Drawing::Size(365, 65);
				this->groupBox2->Size = System::Drawing::Size(365, 490);
				this->groupBox2->Location = System::Drawing::Point(5, 66);
				this->grackButton2->Location = System::Drawing::Point(190, 14);
				this->grackButton1->Location = System::Drawing::Point(11, 14);
				this->label10->Location = System::Drawing::Point(90, 430);
				this->panel2->Size = System::Drawing::Size(360, 380);
				this->textBox6->Size = System::Drawing::Size(48, 22);
				this->textBox5->Size = System::Drawing::Size(48, 22);
				this->textBox4->Size = System::Drawing::Size(48, 22);
				this->textBox3->Size = System::Drawing::Size(48, 22);
				this->textBox3->Location = System::Drawing::Point(250, 135);
				this->textBox4->Location = System::Drawing::Point(250, 135);
				this->textBox5->Location = System::Drawing::Point(250, 135);
				this->textBox6->Location = System::Drawing::Point(250, 135);
				this->label1->Size = System::Drawing::Size(120, 18);
				this->label2->Size = System::Drawing::Size(120, 18);
				this->label1->Location = System::Drawing::Point(200, 0);
				this->label2->Location = System::Drawing::Point(200, 0);
				this->comboBox1->Location = System::Drawing::Point(120, 24);
				this->comboBox2->Location = System::Drawing::Point(120, 24);
				this->comboBox1->Size = System::Drawing::Size(240, 23);
				this->comboBox2->Size = System::Drawing::Size(240, 23);
				this->grackButton4->Location = System::Drawing::Point(250, 87);
				this->grackButton5->Location = System::Drawing::Point(250, 87);
				this->grackButton7->Location = System::Drawing::Point(250, 87);
				this->grackButton8->Location = System::Drawing::Point(250, 87);
				this->grackButton2->Size = System::Drawing::Size(166, 42);
				this->grackButton1->Size = System::Drawing::Size(166, 42);
			}
			else //dpiX == 96 for instance
			{
				this->Size = System::Drawing::Size(273, 455);
				this->button1->Location = System::Drawing::Point(104, 408);
				this->groupBox1->Size = System::Drawing::Size(273, 65);
				this->groupBox2->Size = System::Drawing::Size(273, 388);
				this->groupBox2->Location = System::Drawing::Point(5, 66);
				this->grackButton2->Location = System::Drawing::Point(142, 14);
				this->grackButton1->Location = System::Drawing::Point(11, 14);
				this->label10->Location = System::Drawing::Point(30, 353);
				this->panel2->Size = System::Drawing::Size(272, 315);
				this->textBox6->Size = System::Drawing::Size(48, 22);
				this->textBox5->Size = System::Drawing::Size(48, 22);
				this->textBox4->Size = System::Drawing::Size(48, 22);
				this->textBox3->Size = System::Drawing::Size(48, 22);
				this->textBox3->Location = System::Drawing::Point(180, 135);
				this->textBox4->Location = System::Drawing::Point(180, 135);
				this->textBox5->Location = System::Drawing::Point(180, 135);
				this->textBox6->Location = System::Drawing::Point(180, 135);
				this->label1->Size = System::Drawing::Size(150, 18);
				this->label2->Size = System::Drawing::Size(100, 18);
				this->label1->Location = System::Drawing::Point(103, 0);
				this->label2->Location = System::Drawing::Point(120, 0);
				this->comboBox1->Location = System::Drawing::Point(105, 24);
				this->comboBox2->Location = System::Drawing::Point(105, 24);
				this->comboBox1->Size = System::Drawing::Size(150, 23);
				this->comboBox2->Size = System::Drawing::Size(150, 23);
				this->grackButton4->Location = System::Drawing::Point(177, 87);
				this->grackButton5->Location = System::Drawing::Point(177, 87);
				this->grackButton7->Location = System::Drawing::Point(177, 87);
				this->grackButton8->Location = System::Drawing::Point(177, 87);
				this->grackButton2->Size = System::Drawing::Size(115, 42);
				this->grackButton1->Size = System::Drawing::Size(115, 42);
			}
			this->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->BackgroundImage = this->backImage;
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			//this->button1->Location = System::Drawing::Point(104, 408);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(60, 40);
			this->button1->TabIndex = 1;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->BringToFront();
			this->button1->Click += gcnew System::EventHandler(this, &ConfigRegBox::button1_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->grackButton2);
			this->groupBox1->Controls->Add(this->grackButton1);
			this->groupBox1->Location = System::Drawing::Point(6, 0);
			this->groupBox1->Name = L"groupBox1";
			//this->groupBox1->Size = System::Drawing::Size(273, 65);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			// 
			// grackButton2
			// 
			this->grackButton2->Font = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold));
			this->grackButton2->ForeColor = System::Drawing::Color::White;
			//this->grackButton2->Location = System::Drawing::Point(142, 14);
			this->grackButton2->Name = L"grackButton2";
			//this->grackButton2->Size = System::Drawing::Size(166, 42);
			this->grackButton2->TabIndex = 1;
			this->grackButton2->Text = L"Write Config";
			this->grackButton2->UseVisualStyleBackColor = true;
			this->grackButton2->Click += gcnew System::EventHandler(this, &ConfigRegBox::grackButton2_Click);
			// 
			// grackButton1
			// 
			this->grackButton1->Font = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold));
			this->grackButton1->ForeColor = System::Drawing::Color::White;
			//this->grackButton1->Location = System::Drawing::Point(11, 14);
			this->grackButton1->Name = L"grackButton1";
			//this->grackButton1->Size = System::Drawing::Size(166, 42);
			this->grackButton1->TabIndex = 0;
			this->grackButton1->Text = L"Read Config";
			this->grackButton1->UseVisualStyleBackColor = true;
			this->grackButton1->Click += gcnew System::EventHandler(this, &ConfigRegBox::grackButton1_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->panel2);
			//this->groupBox2->Location = System::Drawing::Point(5, 66);
			this->groupBox2->Name = L"groupBox2";
			//this->groupBox2->Size = System::Drawing::Size(273, 341);
			this->groupBox2->TabIndex = 2;
			this->groupBox2->TabStop = false;
			// 
			// panel2
			// 
			this->panel2->AutoScroll = true;
			this->panel2->BackColor = System::Drawing::Color::Transparent;
			this->panel2->Controls->Add(this->grackButton8);
			this->panel2->Controls->Add(this->grackButton7);
			this->panel2->Controls->Add(this->grackButton5);
			this->panel2->Controls->Add(this->grackButton4);
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
			this->panel2->TabIndex = 1;
			// 
			// grackButton5
			// 
			this->grackButton5->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->grackButton5->ForeColor = System::Drawing::Color::White;
			//this->grackButton5->Location = System::Drawing::Point(210, 110);
			this->grackButton5->Name = L"grackButton5";
			this->grackButton5->Size = System::Drawing::Size(43, 17);
			this->grackButton5->TabIndex = 19;
			this->grackButton5->Text = L"grackButton5";
			this->grackButton5->UseVisualStyleBackColor = true;
			this->grackButton5->Click += gcnew System::EventHandler(this, &ConfigRegBox::grackButton5_Click);
			// 
			// grackButton4
			// 
			this->grackButton4->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->grackButton4->ForeColor = System::Drawing::Color::White;
			//this->grackButton4->Location = System::Drawing::Point(177, 87);
			this->grackButton4->Name = L"grackButton4";
			this->grackButton4->Size = System::Drawing::Size(76, 17);
			this->grackButton4->TabIndex = 18;
			this->grackButton4->Text = L"grackButton4";
			this->grackButton4->UseVisualStyleBackColor = true;
			this->grackButton4->Click += gcnew System::EventHandler(this, &ConfigRegBox::grackButton4_Click);
			// 
			// comboBox2
			// 
			this->comboBox2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->comboBox2->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->DropDownWidth = 240;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"00b - Field switched on", L"01b - First valid Start-of-Frame",
					L"10b - Selection of Tag", L"11b - Data to read from I2C/data read by RF"
			});
			//this->comboBox2->Location = System::Drawing::Point(107, 44);
			this->comboBox2->Name = L"comboBox2";
			//this->comboBox2->Size = System::Drawing::Size(147, 23);
			this->comboBox2->TabIndex = 16;
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->DropDownWidth = 275;
			this->comboBox1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"00b - Field switched off", L"01b - Set to HALT or field switched off",
					L"10b - LAST_NDEF_BLOCK read field switched off", L"11b - Data R/W by I2C or field switched off"
			});
			//this->comboBox1->Location = System::Drawing::Point(107, 24);
			this->comboBox1->Name = L"comboBox1";
			//this->comboBox1->Size = System::Drawing::Size(147, 23);
			this->comboBox1->TabIndex = 15;
			// 
			// textBox6
			// 
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->textBox6->Location = System::Drawing::Point(207, 209);
			this->textBox6->Name = L"textBox6";
			//this->textBox6->Size = System::Drawing::Size(48, 22);
			this->textBox6->TabIndex = 14;
			// 
			// textBox5
			// 
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->textBox5->Location = System::Drawing::Point(207, 191);
			this->textBox5->Name = L"textBox5";
			//this->textBox5->Size = System::Drawing::Size(48, 22);
			this->textBox5->TabIndex = 11;
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->textBox4->Location = System::Drawing::Point(207, 176);
			this->textBox4->Name = L"textBox4";
			//this->textBox4->Size = System::Drawing::Size(48, 22);
			this->textBox4->TabIndex = 10;
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->textBox3->Location = System::Drawing::Point(207, 135);
			this->textBox3->Name = L"textBox3";
			//this->textBox3->Size = System::Drawing::Size(48, 22);
			this->textBox3->TabIndex = 8;
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label2->Location = System::Drawing::Point(134, 14);
			this->label2->Name = L"label2";
			//this->label2->Size = System::Drawing::Size(120, 18);
			this->label2->TabIndex = 2;
			this->label2->Text = L"label2";
			this->label2->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label1->Location = System::Drawing::Point(133, 0);
			this->label1->Name = L"label1";
			//this->label1->Size = System::Drawing::Size(120, 18);
			this->label1->TabIndex = 1;
			this->label1->Text = L"label1";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// treeView1				//Config tab - Read/Write config Registers - Read Config	||		Tree for displaying the results							
			// 
			this->treeView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->treeView1->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->treeView1->Location = System::Drawing::Point(0, 3);
			this->treeView1->Name = L"treeView1";
			treeNode39->Name = L"Node1";
			treeNode39->Text = L"IC Product:";
			treeNode40->Name = L"Node2";
			treeNode40->Text = L"User memory:";
			treeNode41->Name = L"Node0";
			treeNode41->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode41->Text = L"GENERAL CHIP INFORMATION";
			treeNode42->Name = L"Node4";
			treeNode42->Text = L"FD_OFF is:";
			treeNode43->Name = L"Node5";
			treeNode43->Text = L"FD_ON is:";
			treeNode44->Name = L"Node3";
			treeNode44->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode44->Text = L"FIELD DETECTION";
			treeNode46->Name = L"Node8";
			treeNode46->Text = L"Direction:";
			treeNode47->Name = L"Node9";
			treeNode47->Text = L"Write from RF is:";
			treeNode48->Name = L"Node6";
			treeNode48->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode48->Text = L"PASS THROUGH";
			treeNode49->Name = L"Node11";
			treeNode49->Text = L"Last NDEF Block is:";
			treeNode51->Name = L"Node13";
			treeNode51->Text = L"SRAM Mirror Block is:";
			treeNode52->Name = L"Node10";
			treeNode52->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode52->Text = L"SRAM EEPROM SETTINGS";
			treeNode53->Name = L"Node15";
			treeNode53->Text = L"WD_LS Timer is:";
			treeNode54->Name = L"Node16";
			treeNode54->Text = L"WD_MS Timer is:";
			treeNode55->Name = L"Node17";
			treeNode55->Text = L"I2C Clock stretch is:";
			treeNode56->Name = L"Node18";
			treeNode56->Text = L"I2C RST on start is:";
			treeNode57->Name = L"Node14";
			treeNode57->NodeFont = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			treeNode57->Text = L"I2C SETTINGS";
			this->treeView1->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(5) {
				treeNode41, treeNode44, treeNode48,
					treeNode52, treeNode57
			});
			this->treeView1->Scrollable = false;
			this->treeView1->ShowLines = false;
			this->treeView1->Size = System::Drawing::Size(238, 251);
			this->treeView1->TabIndex = 0;
			this->treeView1->AfterCollapse += gcnew System::Windows::Forms::TreeViewEventHandler(this, &ConfigRegBox::treeView1_AfterExplapse);
			this->treeView1->AfterExpand += gcnew System::Windows::Forms::TreeViewEventHandler(this, &ConfigRegBox::treeView1_AfterExplapse);
			this->treeView1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &ConfigRegBox::treeView1_MouseWheel);
			this->treeView1->Nodes[0]->Expand();
			// 
			// grackButton7
			// 
			this->grackButton7->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->grackButton7->ForeColor = System::Drawing::Color::White;
			//this->grackButton7->Location = System::Drawing::Point(210, 237);
			this->grackButton7->Name = L"grackButton7";
			this->grackButton7->Size = System::Drawing::Size(43, 17);
			this->grackButton7->TabIndex = 21;
			this->grackButton7->Text = L"grackButton7";
			this->grackButton7->UseVisualStyleBackColor = true;
			this->grackButton7->Click += gcnew System::EventHandler(this, &ConfigRegBox::grackButton7_Click);
			// 
			// grackButton8
			// 
			this->grackButton8->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->grackButton8->ForeColor = System::Drawing::Color::White;
		//	this->grackButton8->Location = System::Drawing::Point(210, 260);
			this->grackButton8->Name = L"grackButton8";
			this->grackButton8->Size = System::Drawing::Size(43, 17);
			this->grackButton8->TabIndex = 22;
			this->grackButton8->Text = L"grackButton8";
			this->grackButton8->UseVisualStyleBackColor = true;
			this->grackButton8->Click += gcnew System::EventHandler(this, &ConfigRegBox::grackButton8_Click);
			//
			// hiddenElements
			//
			this->grackButton1->isActive = true;
			this->grackButton2->isActive = false;
			this->comboBox1->Hide();
			this->comboBox2->Hide();
			this->grackButton4->Hide();
			this->grackButton5->Hide();
			this->textBox3->Hide();
			this->textBox4->Hide();
			this->textBox5->Hide();
			this->textBox6->Hide();
			this->grackButton7->Hide();
			this->grackButton8->Hide();
			// 
			// label10
			// 
			this->label10->Font = (gcnew System::Drawing::Font(L"Arial", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label10->Location = System::Drawing::Point(30, 353);
			this->label10->Name = L"label2";
			this->label10->Size = System::Drawing::Size(200, 32);
			this->label10->TabIndex = 2;
			this->label10->BackColor = System::Drawing::Color::Black;
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label10->BringToFront();
			this->setLabel(this->label10Text);
			// 
			// ConfigRegForm
			// 
			this->updateParsing();
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(284, 457);
			this->Name = L"ConfigRegForm";
			this->Text = L"ConfigRegForm";
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->ResumeLayout(false);
		}

		// When grackButton1 is pressed, this button is set to active and the other one to passive
		System::Void grackButton1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->grackButton1->isActive = true;
			this->grackButton2->isActive = false;
			this->grackButton1->Refresh();
			this->grackButton2->Refresh();
		}

		// When grackButton2 is pressed, this button is set to active and the other one to passive
		System::Void grackButton2_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->grackButton1->isActive = false;
			this->grackButton2->isActive = true;
			this->grackButton1->Refresh();
			this->grackButton2->Refresh();
		}

		// Every time a tree node expands or collapses we need to resize the tree view according to the new size (so that the srollbar from the panel appears
		// when it is needed) and check if the checkboxes need to be shown or hidden
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
				this->grackButton4->Location = System::Drawing::Point(this->grackButton4->Location.X, this->treeView1->Nodes[2]->Nodes[0]->Bounds.Location.Y + 4);
				this->grackButton4->Show();
			}
			else
				this->grackButton4->Hide();
			if (this->treeView1->Nodes[2]->Nodes[1]->IsVisible)
			{
				this->grackButton5->Location = System::Drawing::Point(this->grackButton5->Location.X, this->treeView1->Nodes[2]->Nodes[1]->Bounds.Location.Y + 4);
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
				this->textBox4->Location = System::Drawing::Point(this->textBox4->Location.X, this->treeView1->Nodes[3]->Nodes[1]->Bounds.Location.Y + 3);
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

		// This way, the mouse wheel controls the scrollbar of the panel when the mouse is over the tree view
		System::Void treeView1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			this->panel2->Focus();
		}

		// When button1 is pressed, it fires a backButtonClick event
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			backButtonClick(this, gcnew EventArgs());
		}

		// To use grackButton4 as a switch, together with grackButton5
		System::Void grackButton4_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->grackButton4->isActive == false)
			{
				this->grackButton4->isActive = true;
				this->grackButton4->Text = "RF to I2C";
				this->grackButton5->isActive = true;
				this->grackButton5->Text = "ON";
			}
			else
			{
				this->grackButton4->isActive = false;
				this->grackButton4->Text = "I2C to RF";
				this->grackButton5->isActive = false;
				this->grackButton5->Text = "OFF";
			}
		}

		// To use grackButton5 as a switch, together with grackButton4
		System::Void grackButton5_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->grackButton5->isActive == false)
			{
				this->grackButton5->isActive = true;
				this->grackButton5->Text = "ON";
				this->grackButton4->isActive = true;
				this->grackButton4->Text = "RF to I2C";
			}
			else
			{
				this->grackButton5->isActive = false;
				this->grackButton5->Text = "OFF";
				this->grackButton4->isActive = false;
				this->grackButton4->Text = "I2C to RF";
			}
		}

		// To use grackButton7 as a switch
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

		// To use grackButton8 as a switch
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

		public:
			public:
				// Initializes the ConfigRegistersBox according to the structure passed as a parameter
				System::Void updateBox(Ntag_I2C_Registers_t configReg)
				{
					*this->configReg = configReg;

					if (this->label2 != nullptr)
						this->updateParsing();
				}

			// Internal function for initializing Initializes the ConfigRegistersBox
			System::Void updateParsing()
			{
				this->grackButton1->isActive = true;
				this->grackButton2->isActive = false;

				// Convert from ASCII to Unicode
				int strLength = strlen(this->configReg->REG_Manufacture);
				this->label1->Text = "";
				for (int i = 0; i < strLength; i++)
					this->label1->Text += (wchar_t)this->configReg->REG_Manufacture[i];
				this->label2->Text = this->configReg->REG_Mem_size + " Bytes";
				this->comboBox1->SelectedIndex = (this->configReg->REG_FD_OFF[1] - '0') + (this->configReg->REG_FD_OFF[0] - '0') * 0x02;
				this->comboBox2->SelectedIndex = (this->configReg->REG_FD_ON[1] - '0') + (this->configReg->REG_FD_ON[0] - '0') * 0x02;
				if (this->configReg->REG_PTHRU_DIR)
				{
					this->grackButton4->isActive = true;
					this->grackButton4->Text = "RF to I2C";
					this->grackButton5->isActive = true;
					this->grackButton5->Text = "ON";
				}
				else
				{
					this->grackButton4->isActive = false;
					this->grackButton4->Text = "I2C to RF";
					this->grackButton5->isActive = false;
					this->grackButton5->Text = "OFF";
				}
				this->textBox3->Text = this->configReg->REG_LAST_NDEF_PAGE.ToString();
				this->textBox4->Text = this->configReg->REG_SM_Reg.ToString();
				this->textBox5->Text = this->configReg->REG_WD_LS_Reg.ToString();
				this->textBox6->Text = this->configReg->REG_WD_MS_Reg.ToString();
				if (this->configReg->REG_I2C_CLOCK_STR)
				{
					this->grackButton7->isActive = TRUE;
					this->grackButton7->Text = "ON";
				}
				else
				{
					this->grackButton7->isActive = false;
					this->grackButton7->Text = "OFF";
				}
				if (this->configReg->REG_I2C_RST_ON_OFF)
				{
					this->grackButton8->isActive = TRUE;
					this->grackButton8->Text = "ON";
				}
				else
				{
					this->grackButton8->isActive = false;
					this->grackButton8->Text = "OFF";
				}
			}

			// Returns the structure with the information from the ConfigRegistersBox
			System::Void parseBox(Ntag_I2C_Registers_t* configReg)
			{
				configReg->REG_FD_OFF[0] = (char)floor(this->comboBox1->SelectedIndex / 2) + '0';
				configReg->REG_FD_OFF[1] = this->comboBox1->SelectedIndex % 2 + '0';
				configReg->REG_FD_OFF[2] = 'b';
				configReg->REG_FD_ON[0] = (char)floor(this->comboBox2->SelectedIndex / 2) + '0';
				configReg->REG_FD_ON[1] = this->comboBox2->SelectedIndex % 2 + '0';
				configReg->REG_FD_ON[2] = 'b';
				configReg->REG_PTHRU_DIR = this->grackButton4->isActive;
				configReg->REG_LAST_NDEF_PAGE = System::Convert::ToInt32(this->textBox3->Text);
				configReg->REG_SM_Reg = System::Convert::ToInt32(this->textBox4->Text);
				configReg->REG_WD_LS_Reg = System::Convert::ToInt32(this->textBox5->Text);
				configReg->REG_WD_MS_Reg = System::Convert::ToInt32(this->textBox6->Text);
				configReg->REG_I2C_CLOCK_STR = this->grackButton7->isActive;
				configReg->REG_I2C_RST_ON_OFF = this->grackButton8->isActive;
			}

			// Sets the content of label10
			System::Void setLabel(System::String^ text)
			{
				this->label10Text = text;
				if (this->label10 != nullptr)
				{
					if (text == "")
						this->label10->Hide();
					else
					{
						this->label10->Text = text;
						this->label10->Show();
					}
				}
				this->Refresh();
			}
	};

}