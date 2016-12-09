#pragma once

namespace NTAG_I2C_Demo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for TapTagForm
	/// </summary>
	public ref class TapTagForm : public System::Windows::Forms::Form
	{
	public:
		TapTagForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TapTagForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBoxTapTag;
	protected:

	private: System::Windows::Forms::Label^  TapTagText;

	private: System::Windows::Forms::PictureBox^  pictureTapTag;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TapTagForm::typeid));
			this->groupBoxTapTag = (gcnew System::Windows::Forms::GroupBox());
			this->TapTagText = (gcnew System::Windows::Forms::Label());
			this->pictureTapTag = (gcnew System::Windows::Forms::PictureBox());
			this->groupBoxTapTag->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureTapTag))->BeginInit();
			this->SuspendLayout();
			// 
			// groupBoxTapTag
			// 
			this->groupBoxTapTag->AutoSize = true;
			this->groupBoxTapTag->BackColor = System::Drawing::Color::White;
			this->groupBoxTapTag->Controls->Add(this->TapTagText);
			this->groupBoxTapTag->Controls->Add(this->pictureTapTag);
			this->groupBoxTapTag->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBoxTapTag->Location = System::Drawing::Point(0, 0);
			this->groupBoxTapTag->Margin = System::Windows::Forms::Padding(4);
			this->groupBoxTapTag->Name = L"groupBoxTapTag";
			this->groupBoxTapTag->Padding = System::Windows::Forms::Padding(4);
			this->groupBoxTapTag->Size = System::Drawing::Size(379, 562);
			this->groupBoxTapTag->TabIndex = 0;
			this->groupBoxTapTag->TabStop = false;
			// 
			// TapTagText
			// 
			this->TapTagText->AutoSize = true;
			this->TapTagText->Font = (gcnew System::Drawing::Font(L"Arial", 11.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TapTagText->Location = System::Drawing::Point(67, 316);
			this->TapTagText->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->TapTagText->Name = L"TapTagText";
			this->TapTagText->Size = System::Drawing::Size(215, 23);
			this->TapTagText->TabIndex = 1;
			this->TapTagText->Text = L"Tap tag to read content";
			// 
			// pictureTapTag
			// 
			this->pictureTapTag->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureTapTag.BackgroundImage")));
			this->pictureTapTag->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureTapTag->Location = System::Drawing::Point(31, 116);
			this->pictureTapTag->Margin = System::Windows::Forms::Padding(4);
			this->pictureTapTag->Name = L"pictureTapTag";
			this->pictureTapTag->Size = System::Drawing::Size(300, 171);
			this->pictureTapTag->TabIndex = 0;
			this->pictureTapTag->TabStop = false;
			// 
			// TapTagForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(379, 562);
			this->Controls->Add(this->groupBoxTapTag);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"TapTagForm";
			this->Text = L"TapTagForm";
			this->groupBoxTapTag->ResumeLayout(false);
			this->groupBoxTapTag->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureTapTag))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
