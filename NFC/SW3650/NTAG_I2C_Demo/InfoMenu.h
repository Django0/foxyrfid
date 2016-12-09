#include "CommonResources.h"


namespace NTAG_I2C_Demo
{
// Group box from 'Flash' waiting to the Tag or FW selection		----		//Demo tab - Information - Flash (waiting for Tag or FW selection)
public ref class TapTagBoxFLA : public GroupBox
{
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::PictureBox^  pictureBox1;
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

public: bool swi, dwi, mwi, selBlink, selDemo = false;

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
			this->progressBarFlash->Location = System::Drawing::Point(29, 250);
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
			gcnew cli::array< System::Windows::Forms::TreeNode^  >(4) { treeNode1, treeNode2, treeNode3, treeNode5 }));
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
		this->treeView1->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(1) { treeNode4 });			//Establish the 4th node as the higher level node
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


}

