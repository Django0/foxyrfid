#pragma once

namespace NTAG_I2C_Demo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ReadMemForm
	/// </summary>
	public ref class ReadMemForm : public System::Windows::Forms::Form
	{
	public:
		ReadMemForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			BYTE data[4 * 0x1E1] = { 0 };
			data[40] = 80;

			label1->Text = "";
			int i = 0, elm = 0;
			for (; i < 4; i++, elm += 4)
				label1->Text += L"[" + i.ToString("X3") + L"]   " + data[elm].ToString("X2") + ":" + data[elm + 1].ToString("X2")
				+ ":" + data[elm + 2].ToString("X2") + ":" + data[elm + 3].ToString("X2") + "\n";
			for (; i <= 0x1E0; i++, elm += 4)
			{
				String^ str = "";
				for (int j = elm; j < elm + 4; j++)
				{
					if (data[j] < 0x20 || data[j] > 0x7D)
						str += ".";
					else
						str += (wchar_t)data[j];
				}
				label1->Text += L"[" + i.ToString("X3") + L"]   " + data[elm].ToString("X2") + ":" + data[elm + 1].ToString("X2")
					+ ":" + data[elm + 2].ToString("X2") + ":" + data[elm + 3].ToString("X2") + "  |" + str + "|\n";
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ReadMemForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Panel^  panelReadMemory;

	private: System::Windows::Forms::Label^  label1;
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
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->panelReadMemory = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->panelReadMemory->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->panelReadMemory);
			this->groupBox1->Location = System::Drawing::Point(5, 1);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(275, 451);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			// 
			// panelReadMemory
			// 
			this->panelReadMemory->AutoScroll = true;
			this->panelReadMemory->Controls->Add(this->label1);
			this->panelReadMemory->Location = System::Drawing::Point(3, 16);
			this->panelReadMemory->Name = L"panelReadMemory";
			this->panelReadMemory->Size = System::Drawing::Size(272, 427);
			this->panelReadMemory->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(3, 1);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(63, 14);
			this->label1->TabIndex = 0;
			this->label1->Text = L"testtest";
			this->label1->MouseEnter += gcnew System::EventHandler(this, &ReadMemForm::label1_MouseEnter);
			// 
			// ReadMemForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(284, 457);
			this->Controls->Add(this->groupBox1);
			this->Name = L"ReadMemForm";
			this->Text = L"ReadMemForm";
			this->groupBox1->ResumeLayout(false);
			this->panelReadMemory->ResumeLayout(false);
			this->panelReadMemory->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
		private:
			System::Void label1_MouseEnter(System::Object^  sender, System::EventArgs^  e)
			{
				this->panel1->Focus();
			}
	};
}
