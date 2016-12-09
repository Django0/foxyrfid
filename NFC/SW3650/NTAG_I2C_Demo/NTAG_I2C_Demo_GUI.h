#include <windows.h>
#include <conio.h>
#include "resource.h"
#include "BoardDemo.h"
#include "stdafx.h"
#include "NTAG_I2C_Logic.h"
#include "NTAG_I2C_API.h"
#include "GUI_Utils.h"
#include "tagHandler.h"
#include "Password_Form.h"
#pragma once

namespace NTAG_I2C_Demo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Text;
	using namespace System::Drawing::Drawing2D;
	using namespace System::Runtime::InteropServices;
	using namespace System::Reflection;
	using namespace System::IO;

	[DllImport("uxtheme.dll")]
	extern "C" HRESULT SetWindowTheme(HWND hWnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList);

	/// <summary>
	/// Summary for NTAG_I2C_Demo_GUI
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	static ref class NTAG_I2C_Demo_GUI : public System::Windows::Forms::Form
	{

	public:
		event System::EventHandler^ TagEvent;
		event System::EventHandler^ TagRemovedEvent;
		System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(NTAG_I2C_Demo_GUI::typeid));

		bool checkTag = false;
		BoardDemo* board_demo = new BoardDemo();
		NTAG_I2C_API* my_api = board_demo->api;
		tagHandler^ taghandler = gcnew tagHandler(board_demo->api);
		bool tagBlocked = false;
		bool authenticated = false;
		bool isTagPlus = false;
		bool firstTime = true;
		bool firstTimeLockIcon = true;
		bool firstTimeFalse = true;
		bool firstNDEF = true;
		bool firstSPEED = false;
		bool firstREG = true;
		bool protectedRead = false;
		bool sramProtected = false;
		bool hasBeenFlashed = false;
		int countCheck;
		BYTE tagVersion;
		String^ password;

		LONG retu;

		BOOL transferDir;

		NTAG_I2C_Demo_GUI(void)
		{
			InitializeComponent();
			
			// 
			// gradButtons
			//
			this->gButton_LedDemoT_Orange->gradientTop = Color::FromArgb(255, 249, 181, 0);
			this->gButton_LedDemoT_Orange->gradientBottom = Color::FromArgb(255, 153, 47, 47);
			this->gButton_LedDemoT_Blue->gradientTop = Color::FromArgb(255, 123, 177, 219);
			this->gButton_LedDemoT_Blue->gradientBottom = Color::FromArgb(255, 44, 85, 177);
			this->gButton_LedDemoT_Green->gradientTop = Color::FromArgb(255, 201, 210, 0);
			this->gButton_LedDemoT_Green->gradientBottom = Color::FromArgb(255, 83, 147, 63);
			// 
			// grackButton1
			//
			this->gButton_NDEFT_ReadNDEF->isActive = true;
			// 
			// writeNDEFBox1
			//
			this->writeNDEFBox1 = gcnew WriteNDEFBox();
			this->writeNDEFBox1->Hide();
			this->tabNDEF->Controls->Add(this->writeNDEFBox1);
			// 
			// tapTagBoxReadMem
			//
			this->tapTagBoxReadMem = gcnew TapTagBox();
			this->tapTagBoxReadMem->Logo = this->imageIdentivReader->Images[0];
			this->tapTagBoxReadMem->backImage = this->imageList2->Images[1];
			this->tapTagBoxReadMem->labelText = L"Tap tag to read content";
			this->tapTagBoxReadMem->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::tapTagBoxReadMem_Click);
			this->tapTagBoxReadMem->Hide();
			this->Controls->Add(this->tapTagBoxReadMem);
			// 
			// tapTagBoxResetMem
			//
			this->tapTagBoxResetMem = gcnew TapTagBox();
			this->tapTagBoxResetMem->Logo = this->imageIdentivReader->Images[0];
			this->tapTagBoxResetMem->backImage = this->imageList2->Images[1];
			this->tapTagBoxResetMem->labelText = L"Tap tag to reset its content";
			this->tapTagBoxResetMem->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::tapTagBoxResetMem_Click);
			this->tapTagBoxResetMem->Hide();
			this->Controls->Add(this->tapTagBoxResetMem);
			// 
			// tapTagBoxReadSessionReg
			//
			this->tapTagBoxReadSessionReg = gcnew TapTagBox();
			this->tapTagBoxReadSessionReg->Logo = this->imageIdentivReader->Images[0];
			this->tapTagBoxReadSessionReg->backImage = this->imageList2->Images[1];
			this->tapTagBoxReadSessionReg->labelText = L"Tap tag to read session registers";
			this->tapTagBoxReadSessionReg->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::tapTagBoxReadSessionReg_Click);
			this->tapTagBoxReadSessionReg->Hide();
			this->Controls->Add(this->tapTagBoxReadSessionReg);
			// 
			// tapTagBoxRWConfigReg
			//
			this->tapTagBoxRWConfigReg = gcnew TapTagBox();
			this->tapTagBoxRWConfigReg->Logo = this->imageIdentivReader->Images[0];
			this->tapTagBoxRWConfigReg->backImage = this->imageList2->Images[1];
			this->tapTagBoxRWConfigReg->labelText = L"Tap tag to read/write config registers";
			this->tapTagBoxRWConfigReg->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::tapTagBoxRWConfigReg_Click);
			this->tapTagBoxRWConfigReg->Hide();
			this->Controls->Add(this->tapTagBoxRWConfigReg);
			// 
			// tapTagBoxAbout
			//
			this->tapTagBoxAbout = gcnew TapTagBox();
			this->tapTagBoxAbout->Logo = this->imageIdentivReader->Images[0];
			this->tapTagBoxAbout->backImage = this->imageList2->Images[1];
			this->tapTagBoxAbout->labelText = L"NTAG I²C Demo\n" + this->AppVersion + L"\nFebruary 2016\n\nTap tag to get the board version information";
			this->tapTagBoxAbout->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::tapTagBoxAbout_Click);
			this->tapTagBoxAbout->Hide();
			this->Controls->Add(this->tapTagBoxAbout);
			// 
			// tapTagBoxFlashing
			//
			this->tapTagBoxFlashing = gcnew TapTagBoxFLA();
			this->tapTagBoxFlashing->Logo = this->imageIdentivReader->Images[0];
			this->tapTagBoxFlashing->backImage = this->imageList2->Images[1];
			this->tapTagBoxFlashing->labelText = L"Select a file and later tap the tag while the right button is pressed";
			this->tapTagBoxFlashing->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::tapTagBoxFlashing_Click);
			this->tapTagBoxFlashing->Hide();
			this->Controls->Add(this->tapTagBoxFlashing);
			// 
			// SelectFlashing
			//
			this->SelectFlashing = gcnew SelectFlash();
			this->SelectFlashing->Logo = this->imageIdentivReader->Images[0];
			this->SelectFlashing->backImage = this->imageList2->Images[1];
			this->SelectFlashing->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::SelectFlashing_Click);
			this->SelectFlashing->Hide();
			this->Controls->Add(this->SelectFlashing);
			//
			// versionBox1
			//
			this->versionBox1 = gcnew VersionBox();
			this->versionBox1->backImage = this->imageList2->Images[1];
			this->versionBox1->backButtonClick += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::versionsBackButton_Click);
			this->versionBox1->Hide();
			this->Controls->Add(this->versionBox1);
			// 
			// helpBox1
			//
			this->helpBox1 = gcnew HelpBox();
			this->helpBox1->LogoPlus = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"NTAGPlus.BackgroundImage")));
			this->helpBox1->backImage = this->imageList2->Images[1];
			this->helpBox1->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::helpBox1_Click);
			this->helpBox1->Hide();
			this->Controls->Add(this->helpBox1);
			//
			// readMemBox1
			//
			this->readMemBox1 = gcnew ReadMemBox();
			this->readMemBox1->backImage = this->imageList2->Images[1];
			this->readMemBox1->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::readMemBox1_Click);
			this->readMemBox1->Hide();
			this->Controls->Add(this->readMemBox1);
			// 
			// resetMemBox1
			//
			this->resetMemBox1 = gcnew ResetMemBox();
			this->resetMemBox1->Logo = this->imageIdentivReader->Images[0];
			this->resetMemBox1->backImage = this->imageList2->Images[1];
			this->resetMemBox1->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::resetMemBox1_Click);
			this->resetMemBox1->Hide();
			this->Controls->Add(this->resetMemBox1);
			//
			// sessionRegBox1
			//
			this->sessionRegBox1 = gcnew SessionRegBox();
			this->sessionRegBox1->backImage = this->imageList2->Images[1];
			this->sessionRegBox1->backButtonClick += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::sessionRegBackButton_Click);
			this->sessionRegBox1->Hide();
			this->Controls->Add(this->sessionRegBox1);
			//
			// configRegBox1
			//
			this->configRegBox1 = gcnew ConfigRegBox();
			this->configRegBox1->backImage = this->imageList2->Images[1];
			this->configRegBox1->backButtonClick += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::configRegBackButton_Click);
			this->configRegBox1->Hide();
			this->Controls->Add(this->configRegBox1);
			//
			// configRegBoxAccess
			//
			this->configRegBoxAccess = gcnew ConfigRegBoxAccess();
			this->configRegBoxAccess->backImage = this->imageList2->Images[1];
			this->configRegBoxAccess->backButtonClick += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::configRegAccessBackButton_Click);
			this->configRegBoxAccess->Hide();
			this->Controls->Add(this->configRegBoxAccess);
			//
			// BoxFlashing
			//
			this->BoxFlashing = gcnew FlashingBox();
			this->BoxFlashing->backImage = this->imageList2->Images[1];
			this->BoxFlashing->Logo = this->imageIdentivReader->Images[0];
			this->BoxFlashing->backButtonClick += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::FlashingBackButton_Click);
			this->BoxFlashing->Hide();
			this->Controls->Add(this->BoxFlashing);
			//
			// tabControl1
			//
			this->tabControl1->Selected += gcnew TabControlEventHandler(this, &NTAG_I2C_Demo_GUI::tabControl1_Selected);
			// 
			// openFileDialog1
			//
			this->openFileDialog1->InitialDirectory = Environment::CurrentDirectory;

			if (my_api->isReaderConnected())
			{
				this->taghandler->TagEvent += gcnew EventHandler(this, &NTAG_I2C_Demo_GUI::OnTagEvent);
				ThreadStart^ sThread = gcnew ThreadStart(taghandler, &tagHandler::FireOnTag);
				this->devThread = gcnew Thread(sThread);
				this->devThread->Start();
			}
			else
			{
				MessageBox::Show("Identiv CLOUD 3700 F reader needed to run NTAG I²C Demo Application. Check our website for more info: http://www.nxp.com/demoboard/OM5569.html ");
				this->Close();
			}
		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NTAG_I2C_Demo_GUI()
		{
			if (components)
			{
				delete components;
			}
			if (my_api->isReaderConnected())
			{
				LONG lReturn;
				taghandler->killThread = true;
				Sleep(500);
				this->my_api->releaseContext();
				Sleep(500);
				this->my_api->releaseConnection(lReturn);
				Sleep(500);
			}
		}
		//Variables created in order to detect windows form size in dpi
		HDC screen = GetDC(0);
		int dpiX = GetDeviceCaps(screen, LOGPIXELSX);

	private: bool buttonSmartPosterNDEF = false;
	private: bool buttonWriteNDEF = false;
	public: String^ dir;
	public: String^ checking;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabLEDDemo;
	private: System::Windows::Forms::TabPage^  tabNDEF;
	private: System::Windows::Forms::TabPage^  tabSpeed;
	private: System::Windows::Forms::GroupBox^  groupBoxBoardStatus;
	private: System::Windows::Forms::GroupBox^  groupBoxBoardConfig;
	private: System::Windows::Forms::Label^  label_LedDemoT_BoardStatus;
	private: System::Windows::Forms::Label^  labelNTAGlogo;
	private: System::Windows::Forms::TabPage^  tabConfig;
	private: System::Windows::Forms::TabPage^  tabFlash;
	private: System::Windows::Forms::PictureBox^  pic_LedDemoT_NTAGlogo;
	public: System::IO::BinaryReader^  str;
	private: System::Windows::Forms::ImageList^  imageList_NTAGlogo;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::GroupBox^  groupBoxF;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  buttonConfigRWConfigReg;
	private: System::Windows::Forms::Button^  buttonConfigReadSessionReg;
	private: System::Windows::Forms::Button^  buttonConfigResetTag;
	private: System::Windows::Forms::Button^  buttonConfigReadTag;
	private: System::Windows::Forms::ImageList^  imageList2;
	private: NTAG_I2C_Demo::GradButton^  gButton_LedDemoT_Orange;
	private: NTAG_I2C_Demo::GradButton^  gButton_LedDemoT_Blue;
	private: NTAG_I2C_Demo::GradButton^  gButton_LedDemoT_Green;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::RadioButton^  radioButtonSRAM;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::RadioButton^  radioButtonEEPROM;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::TextBox^  textBox_SpeedT_PerformBody;
	private: System::Windows::Forms::Label^  textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine;
	private: System::Windows::Forms::GroupBox^  groupBox7;
	private: NTAG_I2C_Demo::GrackButton^  gButton_NDEFT_WriteNDEF;
	private: NTAG_I2C_Demo::GrackButton^  gButton_NDEFT_ReadNDEF;
	private: System::Windows::Forms::GroupBox^  groupBox8;
	private: System::Windows::Forms::Label^  label_NDEFT_Content;
	private: System::Windows::Forms::TextBox^  textBoxNDEFcontent;
	private: System::Windows::Forms::Label^  label_NDEFT_MsgType;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::PictureBox^  pictureBox9;
	private: System::Windows::Forms::PictureBox^  pictureBox8;
	private: System::Windows::Forms::CheckBox^  checkBoxNDEFmsg;
	private: System::Windows::Forms::CheckBox^  cBox_NDEFT_Loop;
	private: System::Windows::Forms::PictureBox^  pictureLockGreen;
	private: System::Windows::Forms::PictureBox^  pictureLockRed;
	private: System::Windows::Forms::PictureBox^  pictureUnlockBlack;
	private: System::Windows::Forms::PictureBox^  pictureUnlockGreen;
	private: System::Windows::Forms::PictureBox^  pictureInfo;
	private: System::Windows::Forms::PictureBox^  pictureInfo_ndef;
	private: System::Windows::Forms::PictureBox^  pictureInfo_speed;
	private: System::Windows::Forms::PictureBox^  pictureInfo_config;
	private: System::Windows::Forms::PictureBox^  pictureLockGreen_NDEF;
	private: System::Windows::Forms::PictureBox^  pictureLockRed_NDEF;
	private: System::Windows::Forms::PictureBox^  pictureUnlockBlack_NDEF;
	private: System::Windows::Forms::PictureBox^  pictureUnlockGreen_NDEF;
	private: System::Windows::Forms::PictureBox^  pictureLockGreen_Speed;
	private: System::Windows::Forms::PictureBox^  pictureLockRed_Speed;
	private: System::Windows::Forms::PictureBox^  pictureUnlockBlack_Speed;
	private: System::Windows::Forms::PictureBox^  pictureUnlockGreen_Speed;
	private: System::Windows::Forms::PictureBox^  pictureLockGreen_Config;
	private: System::Windows::Forms::PictureBox^  pictureLockRed_Config;
	private: System::Windows::Forms::PictureBox^  pictureUnlockBlack_Config;
	private: System::Windows::Forms::PictureBox^  pictureUnlockGreen_Config;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  feedbackToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  flashToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: NTAG_I2C_Demo::GradButton^  gButton_SpeedT_Start;
	private: NTAG_I2C_Demo::GradButton^  ndef;
	private: System::Windows::Forms::CheckBox^  cBox_LedDemoT_LCD;
	private: System::Windows::Forms::CheckBox^  cBox_LedDemoT_TempSensor;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::TextBox^  textBoxNDEFPerformance;
	private: System::Windows::Forms::PictureBox^  pic_LedDemoT_NXP;
	private: System::Windows::Forms::ImageList^  imageList_NXPlogo;
	private: System::Windows::Forms::ImageList^  imageIdentivReader;
	private: System::ComponentModel::IContainer^  components;

	//Flashing
	private: System::Windows::Forms::Label^  labelf1;
	private: System::Windows::Forms::Label^  labelf2;
	private: System::Windows::Forms::Label^  labelf3;
	private: System::Windows::Forms::Label^  labelf4;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::ProgressBar^  progressBarFlash;
	private: System::Windows::Forms::TextBox^  textBoxFlashPerformance;
	public: System::Drawing::Image^ Logo;	// Image that will appear in the picture box
	public: System::Drawing::Image^ backImage;	// Image for the going back button

	protected:
		bool written = true, read = false;

	private:


		/// <summary>
		/// Required designer variable.
		/// </summary>
#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabLEDDemo = (gcnew System::Windows::Forms::TabPage());
			this->pictureInfo = (gcnew System::Windows::Forms::PictureBox());
			this->pictureUnlockBlack = (gcnew System::Windows::Forms::PictureBox());
			this->pictureUnlockBlack_NDEF = (gcnew System::Windows::Forms::PictureBox());
			this->pictureUnlockGreen_NDEF = (gcnew System::Windows::Forms::PictureBox());
			this->pictureLockGreen_NDEF = (gcnew System::Windows::Forms::PictureBox());
			this->pictureLockRed_NDEF = (gcnew System::Windows::Forms::PictureBox());
			this->pictureUnlockBlack_Speed = (gcnew System::Windows::Forms::PictureBox());
			this->pictureUnlockGreen_Speed = (gcnew System::Windows::Forms::PictureBox());
			this->pictureLockGreen_Speed = (gcnew System::Windows::Forms::PictureBox());
			this->pictureLockRed_Speed = (gcnew System::Windows::Forms::PictureBox());
			this->pictureUnlockBlack_Config = (gcnew System::Windows::Forms::PictureBox());
			this->pictureUnlockGreen_Config = (gcnew System::Windows::Forms::PictureBox());
			this->pictureLockGreen_Config = (gcnew System::Windows::Forms::PictureBox());
			this->pictureLockRed_Config = (gcnew System::Windows::Forms::PictureBox());
			this->groupBoxBoardStatus = (gcnew System::Windows::Forms::GroupBox());
			this->label_LedDemoT_BoardStatus = (gcnew System::Windows::Forms::Label());
			this->pic_LedDemoT_NXP = (gcnew System::Windows::Forms::PictureBox());
			this->groupBoxBoardConfig = (gcnew System::Windows::Forms::GroupBox());
			this->cBox_LedDemoT_LCD = (gcnew System::Windows::Forms::CheckBox());
			this->cBox_LedDemoT_TempSensor = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxNDEFmsg = (gcnew System::Windows::Forms::CheckBox());
			this->gButton_LedDemoT_Green = (gcnew NTAG_I2C_Demo::GradButton());
			this->gButton_LedDemoT_Blue = (gcnew NTAG_I2C_Demo::GradButton());
			this->gButton_LedDemoT_Orange = (gcnew NTAG_I2C_Demo::GradButton());
			this->pic_LedDemoT_NTAGlogo = (gcnew System::Windows::Forms::PictureBox());
			this->labelNTAGlogo = (gcnew System::Windows::Forms::Label());
			this->tabNDEF = (gcnew System::Windows::Forms::TabPage());
			this->pictureInfo_ndef = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxNDEFPerformance = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->label_NDEFT_MsgType = (gcnew System::Windows::Forms::Label());
			this->textBoxNDEFcontent = (gcnew System::Windows::Forms::TextBox());
			this->label_NDEFT_Content = (gcnew System::Windows::Forms::Label());
			this->cBox_NDEFT_Loop = (gcnew System::Windows::Forms::CheckBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->gButton_NDEFT_WriteNDEF = (gcnew NTAG_I2C_Demo::GrackButton());
			this->gButton_NDEFT_ReadNDEF = (gcnew NTAG_I2C_Demo::GrackButton());
			this->ndef = (gcnew NTAG_I2C_Demo::GradButton());
			this->tabSpeed = (gcnew System::Windows::Forms::TabPage());
			this->pictureInfo_speed = (gcnew System::Windows::Forms::PictureBox());
			this->gButton_SpeedT_Start = (gcnew NTAG_I2C_Demo::GradButton());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox_SpeedT_PerformBody = (gcnew System::Windows::Forms::TextBox());
			this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine = (gcnew System::Windows::Forms::Label());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonEEPROM = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonSRAM = (gcnew System::Windows::Forms::RadioButton());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->tabConfig = (gcnew System::Windows::Forms::TabPage());
			this->pictureInfo_config = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->buttonConfigRWConfigReg = (gcnew System::Windows::Forms::Button());
			this->buttonConfigReadSessionReg = (gcnew System::Windows::Forms::Button());
			this->buttonConfigResetTag = (gcnew System::Windows::Forms::Button());
			this->buttonConfigReadTag = (gcnew System::Windows::Forms::Button());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureLockGreen = (gcnew System::Windows::Forms::PictureBox());
			this->pictureLockRed = (gcnew System::Windows::Forms::PictureBox());
			this->pictureUnlockGreen = (gcnew System::Windows::Forms::PictureBox());
			this->groupBoxF = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->tabFlash = (gcnew System::Windows::Forms::TabPage());
			this->labelf3 = (gcnew System::Windows::Forms::Label());
			this->labelf2 = (gcnew System::Windows::Forms::Label());
			this->labelf1 = (gcnew System::Windows::Forms::Label());
			this->labelf4 = (gcnew System::Windows::Forms::Label());
			this->progressBarFlash = (gcnew System::Windows::Forms::ProgressBar());
			this->textBoxFlashPerformance = (gcnew System::Windows::Forms::TextBox());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->flashToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->feedbackToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->imageList_NTAGlogo = (gcnew System::Windows::Forms::ImageList(this->components));
			this->imageList2 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->imageList_NXPlogo = (gcnew System::Windows::Forms::ImageList(this->components));
			this->imageIdentivReader = (gcnew System::Windows::Forms::ImageList(this->components));
			this->tabControl1->SuspendLayout();
			this->tabLEDDemo->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureInfo))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockBlack))->BeginInit();
			this->groupBoxBoardStatus->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockBlack_NDEF))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockGreen_NDEF))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockGreen_NDEF))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockRed_NDEF))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockBlack_Speed))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockGreen_Speed))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockGreen_Speed))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockRed_Speed))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockBlack_Config))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockGreen_Config))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockGreen_Config))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockRed_Config))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pic_LedDemoT_NXP))->BeginInit();
			this->groupBoxBoardConfig->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pic_LedDemoT_NTAGlogo))->BeginInit();
			this->tabNDEF->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureInfo_ndef))->BeginInit();
			this->groupBox5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			this->groupBox8->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			this->groupBox7->SuspendLayout();
			this->tabSpeed->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureInfo_speed))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			this->groupBox6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			this->groupBox4->SuspendLayout();
			this->tabConfig->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureInfo_config))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->BeginInit();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockGreen))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockRed))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockGreen))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->contextMenuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabLEDDemo);
			this->tabControl1->Controls->Add(this->tabNDEF);
			this->tabControl1->Controls->Add(this->tabSpeed);
			this->tabControl1->Controls->Add(this->tabConfig);
			this->tabControl1->Font = (gcnew System::Drawing::Font(L"Arial", 6.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tabControl1->ItemSize = System::Drawing::Size(68, 21);
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(379, 562);
			this->tabControl1->TabIndex = 4;
			// 
			// tabLEDDemo
			// 
			this->tabLEDDemo->Controls->Add(this->pictureInfo);
			this->tabLEDDemo->Controls->Add(this->pictureUnlockBlack);
			this->tabLEDDemo->Controls->Add(this->groupBoxBoardStatus);
			this->tabLEDDemo->Controls->Add(this->groupBoxBoardConfig);
			this->tabLEDDemo->Location = System::Drawing::Point(4, 25);
			this->tabLEDDemo->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->tabLEDDemo->Name = L"tabLEDDemo";
			this->tabLEDDemo->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->tabLEDDemo->Size = System::Drawing::Size(371, 533);
			this->tabLEDDemo->TabIndex = 0;
			this->tabLEDDemo->Text = L"     DEMO     ";
			this->tabLEDDemo->UseVisualStyleBackColor = true;
			// 
			// pictureInfo
			// 
			this->pictureInfo->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureInfo.BackgroundImage")));
			this->pictureInfo->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureInfo->Location = System::Drawing::Point(341, 4);
			this->pictureInfo->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureInfo->Name = L"pictureInfo";
			this->pictureInfo->Size = System::Drawing::Size(24, 21);
			this->pictureInfo->TabIndex = 8;
			this->pictureInfo->TabStop = false;
			this->pictureInfo->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureInfo_Click);
			// 
			// pictureUnlockBlack
			// 
			this->pictureUnlockBlack->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureUnlockBlack.BackgroundImage")));
			this->pictureUnlockBlack->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureUnlockBlack->Location = System::Drawing::Point(308, 4);
			this->pictureUnlockBlack->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureUnlockBlack->Name = L"pictureUnlockBlack";
			this->pictureUnlockBlack->Size = System::Drawing::Size(24, 21);
			this->pictureUnlockBlack->TabIndex = 8;
			this->pictureUnlockBlack->TabStop = false;

			// 
			// pictureLockGreen
			// 
			this->pictureLockGreen->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureLockGreen.BackgroundImage")));
			this->pictureLockGreen->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureLockGreen->Size = System::Drawing::Size(18, 17);
			this->pictureLockGreen->Location = System::Drawing::Point(231, 3);
			this->pictureLockGreen->Name = L"pictureLockGreen";
			this->pictureLockGreen->TabIndex = 8;
			this->pictureLockGreen->TabStop = false;
			this->pictureLockGreen->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureLockGreen_Click);
			// 
			// pictureLockRed
			// 
			this->pictureLockRed->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureLockRed.BackgroundImage")));
			this->pictureLockRed->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureLockRed->Location = System::Drawing::Point(231, 3);
			this->pictureLockRed->Size = System::Drawing::Size(18, 17);
			this->pictureLockRed->Name = L"pictureLockRed";
			this->pictureLockRed->TabIndex = 8;
			this->pictureLockRed->TabStop = false;
			this->pictureLockRed->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureLockRed_Click);
			// 
			// pictureUnlockGreen
			// 
			this->pictureUnlockGreen->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureUnlockGreen.BackgroundImage")));
			this->pictureUnlockGreen->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureUnlockGreen->Location = System::Drawing::Point(231, 3);
			this->pictureUnlockGreen->Size = System::Drawing::Size(18, 17);
			this->pictureUnlockGreen->Name = L"pictureUnlockGreen";
			this->pictureUnlockGreen->TabIndex = 8;
			this->pictureUnlockGreen->TabStop = false;
			this->pictureUnlockGreen->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureUnlockGreen_Click);
			// 
			// groupBoxBoardStatus
			// 
			this->groupBoxBoardStatus->Controls->Add(this->label_LedDemoT_BoardStatus);
			this->groupBoxBoardStatus->Controls->Add(this->pic_LedDemoT_NXP);
			this->groupBoxBoardStatus->Font = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBoxBoardStatus->Location = System::Drawing::Point(16, 325);
			this->groupBoxBoardStatus->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBoxBoardStatus->Name = L"groupBoxBoardStatus";
			this->groupBoxBoardStatus->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBoxBoardStatus->Size = System::Drawing::Size(336, 198);
			this->groupBoxBoardStatus->TabIndex = 5;
			this->groupBoxBoardStatus->TabStop = false;
			this->groupBoxBoardStatus->Text = L"Board Status";
			// 
			// label_LedDemoT_BoardStatus
			// 
			this->label_LedDemoT_BoardStatus->AutoSize = true;
			this->label_LedDemoT_BoardStatus->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_LedDemoT_BoardStatus->Location = System::Drawing::Point(24, 30);
			this->label_LedDemoT_BoardStatus->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label_LedDemoT_BoardStatus->Name = L"label_LedDemoT_BoardStatus";
			this->label_LedDemoT_BoardStatus->Size = System::Drawing::Size(189, 34);
			this->label_LedDemoT_BoardStatus->TabIndex = 4;
			this->label_LedDemoT_BoardStatus->Text = L"Transfer: No\r\nTap tag to read board status";
			// 
			// pic_LedDemoT_NXP
			// 
			this->pic_LedDemoT_NXP->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pic_LedDemoT_NXP.BackgroundImage")));
			this->pic_LedDemoT_NXP->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pic_LedDemoT_NXP->Location = System::Drawing::Point(49, 70);
			this->pic_LedDemoT_NXP->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pic_LedDemoT_NXP->Name = L"pic_LedDemoT_NXP";
			this->pic_LedDemoT_NXP->Size = System::Drawing::Size(233, 114);
			this->pic_LedDemoT_NXP->TabIndex = 9;
			this->pic_LedDemoT_NXP->TabStop = false;
			// 
			// groupBoxBoardConfig
			// 
			this->groupBoxBoardConfig->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->groupBoxBoardConfig->Controls->Add(this->cBox_LedDemoT_LCD);
			this->groupBoxBoardConfig->Controls->Add(this->cBox_LedDemoT_TempSensor);
			this->groupBoxBoardConfig->Controls->Add(this->checkBoxNDEFmsg);
			this->groupBoxBoardConfig->Controls->Add(this->gButton_LedDemoT_Green);
			this->groupBoxBoardConfig->Controls->Add(this->gButton_LedDemoT_Blue);
			this->groupBoxBoardConfig->Controls->Add(this->gButton_LedDemoT_Orange);
			this->groupBoxBoardConfig->Controls->Add(this->pic_LedDemoT_NTAGlogo);
			this->groupBoxBoardConfig->Controls->Add(this->labelNTAGlogo);
			this->groupBoxBoardConfig->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->groupBoxBoardConfig->Font = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBoxBoardConfig->Location = System::Drawing::Point(16, 20);
			this->groupBoxBoardConfig->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBoxBoardConfig->Name = L"groupBoxBoardConfig";
			this->groupBoxBoardConfig->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBoxBoardConfig->Size = System::Drawing::Size(336, 298);
			this->groupBoxBoardConfig->TabIndex = 4;
			this->groupBoxBoardConfig->TabStop = false;
			this->groupBoxBoardConfig->Text = L"Board Configuration";
			// 
			// cBox_LedDemoT_LCD
			// 
			this->cBox_LedDemoT_LCD->AutoSize = true;
			this->cBox_LedDemoT_LCD->Font = (gcnew System::Drawing::Font(L"Arial", 8));
			this->cBox_LedDemoT_LCD->Location = System::Drawing::Point(21, 242);
			this->cBox_LedDemoT_LCD->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->cBox_LedDemoT_LCD->Name = L"cBox_LedDemoT_LCD";
			this->cBox_LedDemoT_LCD->Size = System::Drawing::Size(106, 20);
			this->cBox_LedDemoT_LCD->TabIndex = 10;
			this->cBox_LedDemoT_LCD->Text = L"Enable LCD";
			this->cBox_LedDemoT_LCD->UseVisualStyleBackColor = true;
			this->cBox_LedDemoT_LCD->CheckedChanged += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::cBox_LedDemoT_LCD_CheckedChanged);
			// 
			// cBox_LedDemoT_TempSensor
			// 
			this->cBox_LedDemoT_TempSensor->AutoSize = true;
			this->cBox_LedDemoT_TempSensor->Font = (gcnew System::Drawing::Font(L"Arial", 8));
			this->cBox_LedDemoT_TempSensor->Location = System::Drawing::Point(21, 215);
			this->cBox_LedDemoT_TempSensor->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->cBox_LedDemoT_TempSensor->Name = L"cBox_LedDemoT_TempSensor";
			this->cBox_LedDemoT_TempSensor->Size = System::Drawing::Size(207, 20);
			this->cBox_LedDemoT_TempSensor->TabIndex = 9;
			this->cBox_LedDemoT_TempSensor->Text = L"Enable Temperature Sensor";
			this->cBox_LedDemoT_TempSensor->UseVisualStyleBackColor = true;
			// 
			// checkBoxNDEFmsg
			// 
			this->checkBoxNDEFmsg->AutoSize = true;
			this->checkBoxNDEFmsg->Enabled = false;
			this->checkBoxNDEFmsg->Font = (gcnew System::Drawing::Font(L"Arial", 8));
			this->checkBoxNDEFmsg->Location = System::Drawing::Point(49, 267);
			this->checkBoxNDEFmsg->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxNDEFmsg->Name = L"checkBoxNDEFmsg";
			this->checkBoxNDEFmsg->Size = System::Drawing::Size(230, 20);
			this->checkBoxNDEFmsg->TabIndex = 8;
			this->checkBoxNDEFmsg->Text = L"Display NDEF message on LCD";
			this->checkBoxNDEFmsg->UseVisualStyleBackColor = true;
			this->checkBoxNDEFmsg->Visible = false;
			// 
			// gButton_LedDemoT_Green
			// 
			this->gButton_LedDemoT_Green->ForeColor = System::Drawing::Color::White;
			this->gButton_LedDemoT_Green->Location = System::Drawing::Point(11, 149);
			this->gButton_LedDemoT_Green->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->gButton_LedDemoT_Green->Name = L"gButton_LedDemoT_Green";
			this->gButton_LedDemoT_Green->Size = System::Drawing::Size(180, 52);
			this->gButton_LedDemoT_Green->TabIndex = 7;
			this->gButton_LedDemoT_Green->Text = L"Green";
			this->gButton_LedDemoT_Green->UseVisualStyleBackColor = true;
			this->gButton_LedDemoT_Green->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::gButton_LedDemoT_Green_Click);
			// 
			// gButton_LedDemoT_Blue
			// 
			this->gButton_LedDemoT_Blue->ForeColor = System::Drawing::Color::White;
			this->gButton_LedDemoT_Blue->Location = System::Drawing::Point(9, 90);
			this->gButton_LedDemoT_Blue->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->gButton_LedDemoT_Blue->Name = L"gButton_LedDemoT_Blue";
			this->gButton_LedDemoT_Blue->Size = System::Drawing::Size(181, 52);
			this->gButton_LedDemoT_Blue->TabIndex = 6;
			this->gButton_LedDemoT_Blue->Text = L"Blue";
			this->gButton_LedDemoT_Blue->UseVisualStyleBackColor = true;
			this->gButton_LedDemoT_Blue->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::gButton_LedDemoT_Blue_Click);
			// 
			// gButton_LedDemoT_Orange
			// 
			this->gButton_LedDemoT_Orange->ForeColor = System::Drawing::Color::White;
			this->gButton_LedDemoT_Orange->Location = System::Drawing::Point(9, 30);
			this->gButton_LedDemoT_Orange->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->gButton_LedDemoT_Orange->Name = L"gButton_LedDemoT_Orange";
			this->gButton_LedDemoT_Orange->Size = System::Drawing::Size(181, 52);
			this->gButton_LedDemoT_Orange->TabIndex = 5;
			this->gButton_LedDemoT_Orange->Text = L"Orange";
			this->gButton_LedDemoT_Orange->UseVisualStyleBackColor = true;
			this->gButton_LedDemoT_Orange->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::gButton_LedDemoT_Orange_Click);
			// 
			// pic_LedDemoT_NTAGlogo
			// 
			this->pic_LedDemoT_NTAGlogo->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pic_LedDemoT_NTAGlogo.BackgroundImage")));
			this->pic_LedDemoT_NTAGlogo->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pic_LedDemoT_NTAGlogo->Location = System::Drawing::Point(216, 59);
			this->pic_LedDemoT_NTAGlogo->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pic_LedDemoT_NTAGlogo->Name = L"pic_LedDemoT_NTAGlogo";
			this->pic_LedDemoT_NTAGlogo->Size = System::Drawing::Size(100, 96);
			this->pic_LedDemoT_NTAGlogo->TabIndex = 4;
			this->pic_LedDemoT_NTAGlogo->TabStop = false;
			this->pic_LedDemoT_NTAGlogo->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pic_LedDemoT_NTAGlogo_Click);
			// 
			// labelNTAGlogo
			// 
			this->labelNTAGlogo->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelNTAGlogo->Location = System::Drawing::Point(200, 160);
			this->labelNTAGlogo->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelNTAGlogo->Name = L"labelNTAGlogo";
			this->labelNTAGlogo->Size = System::Drawing::Size(131, 18);
			this->labelNTAGlogo->TabIndex = 3;
			this->labelNTAGlogo->Text = L"Tap to switch off";
			this->labelNTAGlogo->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// tabNDEF
			// 
			this->tabNDEF->Controls->Add(this->pictureInfo_ndef);
			this->tabNDEF->Controls->Add(this->pictureUnlockBlack_NDEF);
			this->tabNDEF->Controls->Add(this->groupBox5);
			this->tabNDEF->Controls->Add(this->pictureBox5);
			this->tabNDEF->Controls->Add(this->groupBox8);
			this->tabNDEF->Controls->Add(this->pictureBox4);
			this->tabNDEF->Controls->Add(this->groupBox7);
			this->tabNDEF->Controls->Add(this->ndef);
			this->tabNDEF->Location = System::Drawing::Point(4, 25);
			this->tabNDEF->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->tabNDEF->Name = L"tabNDEF";
			this->tabNDEF->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->tabNDEF->Size = System::Drawing::Size(371, 533);
			this->tabNDEF->TabIndex = 1;
			this->tabNDEF->Text = L"     NDEF     ";
			this->tabNDEF->UseVisualStyleBackColor = true;
			// 
			// pictureUnlockBlack
			// 
			this->pictureUnlockBlack_NDEF->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureUnlockBlack.BackgroundImage")));
			this->pictureUnlockBlack_NDEF->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureUnlockBlack_NDEF->Location = System::Drawing::Point(308, 4);
			this->pictureUnlockBlack_NDEF->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureUnlockBlack_NDEF->Name = L"pictureUnlockBlack";
			this->pictureUnlockBlack_NDEF->Size = System::Drawing::Size(24, 21);
			this->pictureUnlockBlack_NDEF->TabIndex = 8;
			this->pictureUnlockBlack_NDEF->TabStop = false;

			// 
			// pictureLockGreen
			// 
			this->pictureLockGreen_NDEF->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureLockGreen.BackgroundImage")));
			this->pictureLockGreen_NDEF->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureLockGreen_NDEF->Size = System::Drawing::Size(18, 17);
			this->pictureLockGreen_NDEF->Location = System::Drawing::Point(231, 3);
			this->pictureLockGreen_NDEF->Name = L"pictureLockGreen";
			this->pictureLockGreen_NDEF->TabIndex = 8;
			this->pictureLockGreen_NDEF->TabStop = false;
			this->pictureLockGreen_NDEF->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureLockGreen_Click);
			// 
			// pictureLockRed
			// 
			this->pictureLockRed_NDEF->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureLockRed.BackgroundImage")));
			this->pictureLockRed_NDEF->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureLockRed_NDEF->Location = System::Drawing::Point(231, 3);
			this->pictureLockRed_NDEF->Size = System::Drawing::Size(18, 17);
			this->pictureLockRed_NDEF->Name = L"pictureLockRed";
			this->pictureLockRed_NDEF->TabIndex = 8;
			this->pictureLockRed_NDEF->TabStop = false;
			this->pictureLockRed_NDEF->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureLockRed_Click);
			// 
			// pictureUnlockGreen
			// 
			this->pictureUnlockGreen_NDEF->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureUnlockGreen.BackgroundImage")));
			this->pictureUnlockGreen_NDEF->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureUnlockGreen_NDEF->Location = System::Drawing::Point(231, 3);
			this->pictureUnlockGreen_NDEF->Size = System::Drawing::Size(18, 17);
			this->pictureUnlockGreen_NDEF->Name = L"pictureUnlockGreen";
			this->pictureUnlockGreen_NDEF->TabIndex = 8;
			this->pictureUnlockGreen_NDEF->TabStop = false;
			this->pictureUnlockGreen_NDEF->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureUnlockGreen_Click);
			// 
			// pictureInfo_ndef
			// 
			this->pictureInfo_ndef->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureInfo_ndef.BackgroundImage")));
			this->pictureInfo_ndef->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureInfo_ndef->Location = System::Drawing::Point(341, 4);
			this->pictureInfo_ndef->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureInfo_ndef->Name = L"pictureInfo_ndef";
			this->pictureInfo_ndef->Size = System::Drawing::Size(24, 21);
			this->pictureInfo_ndef->TabIndex = 8;
			this->pictureInfo_ndef->TabStop = false;
			this->pictureInfo_ndef->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureInfo_ndef_Click);
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->textBoxNDEFPerformance);
			this->groupBox5->Font = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold));
			this->groupBox5->Location = System::Drawing::Point(19, 389);
			this->groupBox5->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox5->Size = System::Drawing::Size(329, 74);
			this->groupBox5->TabIndex = 10;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Read Performance";
			// 
			// textBoxNDEFPerformance
			// 
			this->textBoxNDEFPerformance->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(244)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->textBoxNDEFPerformance->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBoxNDEFPerformance->Enabled = false;
			this->textBoxNDEFPerformance->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBoxNDEFPerformance->Location = System::Drawing::Point(15, 25);
			this->textBoxNDEFPerformance->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxNDEFPerformance->Multiline = true;
			this->textBoxNDEFPerformance->Name = L"textBoxNDEFPerformance";
			this->textBoxNDEFPerformance->ReadOnly = true;
			this->textBoxNDEFPerformance->Size = System::Drawing::Size(300, 39);
			this->textBoxNDEFPerformance->TabIndex = 0;
			// 
			// pictureBox5
			// 
			this->pictureBox5->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox5.BackgroundImage")));
			this->pictureBox5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox5->Location = System::Drawing::Point(312, 481);
			this->pictureBox5->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(56, 46);
			this->pictureBox5->TabIndex = 8;
			this->pictureBox5->TabStop = false;
			// 
			// groupBox8
			// 
			this->groupBox8->Controls->Add(this->label_NDEFT_MsgType);
			this->groupBox8->Controls->Add(this->textBoxNDEFcontent);
			this->groupBox8->Controls->Add(this->label_NDEFT_Content);
			this->groupBox8->Controls->Add(this->cBox_NDEFT_Loop);
			this->groupBox8->Location = System::Drawing::Point(19, 111);
			this->groupBox8->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox8->Size = System::Drawing::Size(329, 274);
			this->groupBox8->TabIndex = 1;
			this->groupBox8->TabStop = false;
			// 
			// label_NDEFT_MsgType
			// 
			this->label_NDEFT_MsgType->AutoSize = true;
			this->label_NDEFT_MsgType->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_NDEFT_MsgType->Location = System::Drawing::Point(28, 217);
			this->label_NDEFT_MsgType->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label_NDEFT_MsgType->Name = L"label_NDEFT_MsgType";
			this->label_NDEFT_MsgType->Size = System::Drawing::Size(118, 17);
			this->label_NDEFT_MsgType->TabIndex = 2;
			this->label_NDEFT_MsgType->Text = L"NDEF Msg Type:";
			// 
			// textBoxNDEFcontent
			// 
			this->textBoxNDEFcontent->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(244)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->textBoxNDEFcontent->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBoxNDEFcontent->Enabled = false;
			this->textBoxNDEFcontent->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBoxNDEFcontent->ForeColor = System::Drawing::Color::Black;
			this->textBoxNDEFcontent->Location = System::Drawing::Point(12, 46);
			this->textBoxNDEFcontent->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxNDEFcontent->Multiline = true;
			this->textBoxNDEFcontent->Name = L"textBoxNDEFcontent";
			this->textBoxNDEFcontent->ReadOnly = true;
			this->textBoxNDEFcontent->Size = System::Drawing::Size(307, 164);
			this->textBoxNDEFcontent->TabIndex = 1;
			// 
			// label_NDEFT_Content
			// 
			this->label_NDEFT_Content->AutoSize = true;
			this->label_NDEFT_Content->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_NDEFT_Content->Location = System::Drawing::Point(8, 17);
			this->label_NDEFT_Content->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label_NDEFT_Content->Name = L"label_NDEFT_Content";
			this->label_NDEFT_Content->Size = System::Drawing::Size(200, 17);
			this->label_NDEFT_Content->TabIndex = 0;
			this->label_NDEFT_Content->Text = L"Tap tag to read NDEF content";
			// 
			// cBox_NDEFT_Loop
			// 
			this->cBox_NDEFT_Loop->AutoSize = true;
			this->cBox_NDEFT_Loop->Font = (gcnew System::Drawing::Font(L"Arial", 8));
			this->cBox_NDEFT_Loop->Location = System::Drawing::Point(20, 245);
			this->cBox_NDEFT_Loop->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->cBox_NDEFT_Loop->Name = L"cBox_NDEFT_Loop";
			this->cBox_NDEFT_Loop->Size = System::Drawing::Size(179, 20);
			this->cBox_NDEFT_Loop->TabIndex = 8;
			this->cBox_NDEFT_Loop->Text = L"Enable NDEF read loop";
			this->cBox_NDEFT_Loop->UseVisualStyleBackColor = true;
			this->cBox_NDEFT_Loop->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::checkBox_Click);
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.BackgroundImage")));
			this->pictureBox4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox4->Location = System::Drawing::Point(0, 481);
			this->pictureBox4->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(108, 46);
			this->pictureBox4->TabIndex = 8;
			this->pictureBox4->TabStop = false;
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->gButton_NDEFT_WriteNDEF);
			this->groupBox7->Controls->Add(this->gButton_NDEFT_ReadNDEF);
			this->groupBox7->Location = System::Drawing::Point(19, 23);
			this->groupBox7->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox7->Size = System::Drawing::Size(331, 80);
			this->groupBox7->TabIndex = 0;
			this->groupBox7->TabStop = false;
			// 
			// gButton_NDEFT_WriteNDEF
			// 
			this->gButton_NDEFT_WriteNDEF->Font = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gButton_NDEFT_WriteNDEF->ForeColor = System::Drawing::Color::White;
			this->gButton_NDEFT_WriteNDEF->Location = System::Drawing::Point(168, 16);
			this->gButton_NDEFT_WriteNDEF->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->gButton_NDEFT_WriteNDEF->Name = L"gButton_NDEFT_WriteNDEF";
			this->gButton_NDEFT_WriteNDEF->Size = System::Drawing::Size(155, 52);
			this->gButton_NDEFT_WriteNDEF->TabIndex = 1;
			this->gButton_NDEFT_WriteNDEF->Text = L"Write NDEF";
			this->gButton_NDEFT_WriteNDEF->UseVisualStyleBackColor = true;
			this->gButton_NDEFT_WriteNDEF->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::gButton_NDEFT_WriteNDEF_Click);
			// 
			// gButton_NDEFT_ReadNDEF
			// 
			this->gButton_NDEFT_ReadNDEF->Font = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gButton_NDEFT_ReadNDEF->ForeColor = System::Drawing::Color::White;
			this->gButton_NDEFT_ReadNDEF->Location = System::Drawing::Point(8, 16);
			this->gButton_NDEFT_ReadNDEF->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->gButton_NDEFT_ReadNDEF->Name = L"gButton_NDEFT_ReadNDEF";
			this->gButton_NDEFT_ReadNDEF->Size = System::Drawing::Size(155, 52);
			this->gButton_NDEFT_ReadNDEF->TabIndex = 0;
			this->gButton_NDEFT_ReadNDEF->Text = L"Read NDEF";
			this->gButton_NDEFT_ReadNDEF->UseVisualStyleBackColor = true;
			this->gButton_NDEFT_ReadNDEF->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::gButton_NDEFT_ReadNDEF_Click);
			// 
			// ndef
			// 
			this->ndef->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ndef->ForeColor = System::Drawing::Color::White;
			this->ndef->Location = System::Drawing::Point(189, 350);
			this->ndef->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->ndef->Name = L"ndef";
			this->ndef->Size = System::Drawing::Size(140, 27);
			this->ndef->TabIndex = 9;
			this->ndef->Text = L"Write default NDEF";
			this->ndef->UseVisualStyleBackColor = true;
			this->ndef->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::ndef_Click);
			// 
			// tabSpeed
			// 
			this->tabSpeed->Controls->Add(this->pictureInfo_speed);
			this->tabSpeed->Controls->Add(this->pictureUnlockBlack_Speed);
			this->tabSpeed->Controls->Add(this->gButton_SpeedT_Start);
			this->tabSpeed->Controls->Add(this->pictureBox7);
			this->tabSpeed->Controls->Add(this->groupBox6);
			this->tabSpeed->Controls->Add(this->pictureBox6);
			this->tabSpeed->Controls->Add(this->groupBox4);
			this->tabSpeed->Location = System::Drawing::Point(4, 25);
			this->tabSpeed->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->tabSpeed->Name = L"tabSpeed";
			this->tabSpeed->Size = System::Drawing::Size(371, 533);
			this->tabSpeed->TabIndex = 2;
			this->tabSpeed->Text = L"     SPEED     ";
			this->tabSpeed->UseVisualStyleBackColor = true;
			// 
			// pictureInfo_speed
			// 
			this->pictureInfo_speed->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureInfo_speed.BackgroundImage")));
			this->pictureInfo_speed->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureInfo_speed->Location = System::Drawing::Point(341, 4);
			this->pictureInfo_speed->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureInfo_speed->Name = L"pictureInfo_speed";
			this->pictureInfo_speed->Size = System::Drawing::Size(24, 21);
			this->pictureInfo_speed->TabIndex = 8;
			this->pictureInfo_speed->TabStop = false;
			this->pictureInfo_speed->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureInfo_speed_Click);
			// 
			// pictureUnlockBlack
			// 
			this->pictureUnlockBlack_Speed->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureUnlockBlack.BackgroundImage")));
			this->pictureUnlockBlack_Speed->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureUnlockBlack_Speed->Location = System::Drawing::Point(308, 4);
			this->pictureUnlockBlack_Speed->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureUnlockBlack_Speed->Name = L"pictureUnlockBlack_Speed";
			this->pictureUnlockBlack_Speed->Size = System::Drawing::Size(24, 21);
			this->pictureUnlockBlack_Speed->TabIndex = 8;
			this->pictureUnlockBlack_Speed->TabStop = false;

			// 
			// pictureLockGreen
			// 
			this->pictureLockGreen_Speed->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureLockGreen.BackgroundImage")));
			this->pictureLockGreen_Speed->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureLockGreen_Speed->Size = System::Drawing::Size(18, 17);
			this->pictureLockGreen_Speed->Location = System::Drawing::Point(231, 3);
			this->pictureLockGreen_Speed->Name = L"pictureLockGreen_Speed";
			this->pictureLockGreen_Speed->TabIndex = 8;
			this->pictureLockGreen_Speed->TabStop = false;
			this->pictureLockGreen_Speed->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureLockGreen_Click);
			// 
			// pictureLockRed
			// 
			this->pictureLockRed_Speed->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureLockRed.BackgroundImage")));
			this->pictureLockRed_Speed->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureLockRed_Speed->Location = System::Drawing::Point(231, 3);
			this->pictureLockRed_Speed->Size = System::Drawing::Size(18, 17);
			this->pictureLockRed_Speed->Name = L"pictureLockRed_Speed";
			this->pictureLockRed_Speed->TabIndex = 8;
			this->pictureLockRed_Speed->TabStop = false;
			this->pictureLockRed_Speed->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureLockRed_Click);
			// 
			// pictureUnlockGreen
			// 
			this->pictureUnlockGreen_Speed->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureUnlockGreen.BackgroundImage")));
			this->pictureUnlockGreen_Speed->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureUnlockGreen_Speed->Location = System::Drawing::Point(231, 3);
			this->pictureUnlockGreen_Speed->Size = System::Drawing::Size(18, 17);
			this->pictureUnlockGreen_Speed->Name = L"pictureUnlockGreen_Speed";
			this->pictureUnlockGreen_Speed->TabIndex = 8;
			this->pictureUnlockGreen_Speed->TabStop = false;
			this->pictureUnlockGreen_Speed->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureUnlockGreen_Click);
			// 
			// gButton_SpeedT_Start
			// 
			this->gButton_SpeedT_Start->Font = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold));
			this->gButton_SpeedT_Start->ForeColor = System::Drawing::Color::White;
			this->gButton_SpeedT_Start->Location = System::Drawing::Point(279, 37);
			this->gButton_SpeedT_Start->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->gButton_SpeedT_Start->Name = L"gButton_SpeedT_Start";
			this->gButton_SpeedT_Start->Size = System::Drawing::Size(73, 41);
			this->gButton_SpeedT_Start->TabIndex = 10;
			this->gButton_SpeedT_Start->Text = L"Start";
			this->gButton_SpeedT_Start->UseVisualStyleBackColor = true;
			this->gButton_SpeedT_Start->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::gButton_SpeedT_Start_Click);
			// 
			// pictureBox7
			// 
			this->pictureBox7->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox7.BackgroundImage")));
			this->pictureBox7->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox7->Location = System::Drawing::Point(312, 481);
			this->pictureBox7->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(56, 46);
			this->pictureBox7->TabIndex = 9;
			this->pictureBox7->TabStop = false;
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->textBox_SpeedT_PerformBody);
			this->groupBox6->Controls->Add(this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine);
			this->groupBox6->Font = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox6->Location = System::Drawing::Point(11, 160);
			this->groupBox6->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox6->Size = System::Drawing::Size(347, 198);
			this->groupBox6->TabIndex = 2;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Performance";
			// 
			// textBox_SpeedT_PerformBody
			// 
			this->textBox_SpeedT_PerformBody->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(244)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->textBox_SpeedT_PerformBody->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox_SpeedT_PerformBody->Enabled = false;
			this->textBox_SpeedT_PerformBody->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox_SpeedT_PerformBody->ForeColor = System::Drawing::SystemColors::WindowText;
			this->textBox_SpeedT_PerformBody->Location = System::Drawing::Point(8, 60);
			this->textBox_SpeedT_PerformBody->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox_SpeedT_PerformBody->Multiline = true;
			this->textBox_SpeedT_PerformBody->Name = L"textBox_SpeedT_PerformBody";
			this->textBox_SpeedT_PerformBody->ReadOnly = true;
			this->textBox_SpeedT_PerformBody->Size = System::Drawing::Size(329, 130);
			this->textBox_SpeedT_PerformBody->TabIndex = 1;
			// 
			// textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine
			// 
			this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->AutoSize = true;
			this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Location = System::Drawing::Point(12, 30);
			this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Name = L"textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine";
			this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Size = System::Drawing::Size(216, 17);
			this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->TabIndex = 0;
			this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = L"Tap tag to evaluate performance";
			// 
			// pictureBox6
			// 
			this->pictureBox6->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox6.BackgroundImage")));
			this->pictureBox6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox6->Location = System::Drawing::Point(0, 481);
			this->pictureBox6->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(108, 46);
			this->pictureBox6->TabIndex = 9;
			this->pictureBox6->TabStop = false;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->radioButtonEEPROM);
			this->groupBox4->Controls->Add(this->radioButtonSRAM);
			this->groupBox4->Controls->Add(this->label9);
			this->groupBox4->Controls->Add(this->label8);
			this->groupBox4->Controls->Add(this->textBox1);
			this->groupBox4->Controls->Add(this->label7);
			this->groupBox4->Font = (gcnew System::Drawing::Font(L"Arial", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox4->Location = System::Drawing::Point(11, 22);
			this->groupBox4->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox4->Size = System::Drawing::Size(347, 130);
			this->groupBox4->TabIndex = 1;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Board Configuration";
			// 
			// radioButtonEEPROM
			// 
			this->radioButtonEEPROM->AutoSize = true;
			this->radioButtonEEPROM->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButtonEEPROM->Location = System::Drawing::Point(195, 95);
			this->radioButtonEEPROM->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->radioButtonEEPROM->Name = L"radioButtonEEPROM";
			this->radioButtonEEPROM->Size = System::Drawing::Size(98, 22);
			this->radioButtonEEPROM->TabIndex = 5;
			this->radioButtonEEPROM->Text = L"EEPROM";
			this->radioButtonEEPROM->UseVisualStyleBackColor = true;
			this->radioButtonEEPROM->CheckedChanged += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::radioButtonEEPROM_CheckedChanged);
			// 
			// radioButtonSRAM
			// 
			this->radioButtonSRAM->AutoSize = true;
			this->radioButtonSRAM->Checked = true;
			this->radioButtonSRAM->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButtonSRAM->Location = System::Drawing::Point(89, 95);
			this->radioButtonSRAM->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->radioButtonSRAM->Name = L"radioButtonSRAM";
			this->radioButtonSRAM->Size = System::Drawing::Size(75, 22);
			this->radioButtonSRAM->TabIndex = 4;
			this->radioButtonSRAM->TabStop = true;
			this->radioButtonSRAM->Text = L"SRAM";
			this->radioButtonSRAM->UseVisualStyleBackColor = true;
			this->radioButtonSRAM->CheckedChanged += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::radioButtonSRAM_CheckedChanged);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(8, 97);
			this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(68, 18);
			this->label9->TabIndex = 3;
			this->label9->Text = L"Memory:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(177, 60);
			this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(72, 16);
			this->label8->TabIndex = 2;
			this->label8->Text = L"x 64 bytes";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Arial", 9.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(111, 55);
			this->textBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(63, 25);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"10";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(8, 58);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(91, 18);
			this->label7->TabIndex = 0;
			this->label7->Text = L"Data length:";
			// 
			// tabConfig
			// 
			this->tabConfig->Controls->Add(this->pictureInfo_config);
			this->tabConfig->Controls->Add(this->pictureUnlockBlack_Config);
			this->tabConfig->Controls->Add(this->pictureBox9);
			this->tabConfig->Controls->Add(this->groupBox3);
			this->tabConfig->Controls->Add(this->pictureBox8);
			this->tabConfig->Location = System::Drawing::Point(4, 25);
			this->tabConfig->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->tabConfig->Name = L"tabConfig";
			this->tabConfig->Size = System::Drawing::Size(371, 533);
			this->tabConfig->TabIndex = 3;
			this->tabConfig->Text = L"   CONFIG    ";
			this->tabConfig->UseVisualStyleBackColor = true;
			// 
			// pictureInfo_config
			// 
			this->pictureInfo_config->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureInfo_config.BackgroundImage")));
			this->pictureInfo_config->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureInfo_config->Location = System::Drawing::Point(341, 4);
			this->pictureInfo_config->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureInfo_config->Name = L"pictureInfo_config";
			this->pictureInfo_config->Size = System::Drawing::Size(24, 21);
			this->pictureInfo_config->TabIndex = 8;
			this->pictureInfo_config->TabStop = false;
			this->pictureInfo_config->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureInfo_config_Click);
			// 
			// pictureUnlockBlack
			// 
			this->pictureUnlockBlack_Config->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureUnlockBlack.BackgroundImage")));
			this->pictureUnlockBlack_Config->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureUnlockBlack_Config->Location = System::Drawing::Point(308, 4);
			this->pictureUnlockBlack_Config->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureUnlockBlack_Config->Name = L"pictureUnlockBlack_Config";
			this->pictureUnlockBlack_Config->Size = System::Drawing::Size(24, 21);
			this->pictureUnlockBlack_Config->TabIndex = 8;
			this->pictureUnlockBlack_Config->TabStop = false;

			// 
			// pictureLockGreen
			// 
			this->pictureLockGreen_Config->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureLockGreen.BackgroundImage")));
			this->pictureLockGreen_Config->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureLockGreen_Config->Size = System::Drawing::Size(18, 17);
			this->pictureLockGreen_Config->Location = System::Drawing::Point(231, 3);
			this->pictureLockGreen_Config->Name = L"pictureLockGreen_Speed";
			this->pictureLockGreen_Config->TabIndex = 8;
			this->pictureLockGreen_Config->TabStop = false;
			this->pictureLockGreen_Config->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureLockGreen_Click);
			// 
			// pictureLockRed
			// 
			this->pictureLockRed_Config->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureLockRed.BackgroundImage")));
			this->pictureLockRed_Config->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureLockRed_Config->Location = System::Drawing::Point(231, 3);
			this->pictureLockRed_Config->Size = System::Drawing::Size(18, 17);
			this->pictureLockRed_Config->Name = L"pictureLockRed_Config";
			this->pictureLockRed_Config->TabIndex = 8;
			this->pictureLockRed_Config->TabStop = false;
			this->pictureLockRed_Config->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureLockRed_Click);
			// 
			// pictureUnlockGreen
			// 
			this->pictureUnlockGreen_Config->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureUnlockGreen.BackgroundImage")));
			this->pictureUnlockGreen_Config->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureUnlockGreen_Config->Location = System::Drawing::Point(231, 3);
			this->pictureUnlockGreen_Config->Size = System::Drawing::Size(18, 17);
			this->pictureUnlockGreen_Config->Name = L"pictureUnlockGreen_Config";
			this->pictureUnlockGreen_Config->TabIndex = 8;
			this->pictureUnlockGreen_Config->TabStop = false;
			this->pictureUnlockGreen_Config->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::pictureUnlockGreen_Click);
			// 
			// pictureBox9
			// 
			this->pictureBox9->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox9.BackgroundImage")));
			this->pictureBox9->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox9->Location = System::Drawing::Point(312, 481);
			this->pictureBox9->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(56, 46);
			this->pictureBox9->TabIndex = 10;
			this->pictureBox9->TabStop = false;
			// 
			// groupBox3
			// 
			this->groupBox3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Controls->Add(this->label4);
			this->groupBox3->Controls->Add(this->label3);
			this->groupBox3->Controls->Add(this->buttonConfigRWConfigReg);
			this->groupBox3->Controls->Add(this->buttonConfigReadSessionReg);
			this->groupBox3->Controls->Add(this->buttonConfigResetTag);
			this->groupBox3->Controls->Add(this->buttonConfigReadTag);
			this->groupBox3->Location = System::Drawing::Point(8, 26);
			this->groupBox3->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox3->Size = System::Drawing::Size(351, 368);
			this->groupBox3->TabIndex = 3;
			this->groupBox3->TabStop = false;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(184, 318);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(131, 32);
			this->label6->TabIndex = 3;
			this->label6->Text = L"Read/write config\r\nregisters";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(32, 318);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(103, 32);
			this->label5->TabIndex = 3;
			this->label5->Text = L"Read session\r\nregisters";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(183, 155);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(134, 16);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Reset tag memory";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(16, 155);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(129, 16);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Read tag memory";
			// 
			// buttonConfigRWConfigReg
			// 
			this->buttonConfigRWConfigReg->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonConfigRWConfigReg.BackgroundImage")));
			this->buttonConfigRWConfigReg->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->buttonConfigRWConfigReg->FlatAppearance->BorderSize = 0;
			this->buttonConfigRWConfigReg->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonConfigRWConfigReg->Location = System::Drawing::Point(192, 192);
			this->buttonConfigRWConfigReg->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->buttonConfigRWConfigReg->Name = L"buttonConfigRWConfigReg";
			this->buttonConfigRWConfigReg->Size = System::Drawing::Size(136, 121);
			this->buttonConfigRWConfigReg->TabIndex = 3;
			this->buttonConfigRWConfigReg->UseVisualStyleBackColor = true;
			this->buttonConfigRWConfigReg->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::buttonConfigRWConfigReg_Click);
			// 
			// buttonConfigReadSessionReg
			// 
			this->buttonConfigReadSessionReg->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonConfigReadSessionReg.BackgroundImage")));
			this->buttonConfigReadSessionReg->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->buttonConfigReadSessionReg->FlatAppearance->BorderSize = 0;
			this->buttonConfigReadSessionReg->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonConfigReadSessionReg->Location = System::Drawing::Point(19, 192);
			this->buttonConfigReadSessionReg->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->buttonConfigReadSessionReg->Name = L"buttonConfigReadSessionReg";
			this->buttonConfigReadSessionReg->Size = System::Drawing::Size(136, 121);
			this->buttonConfigReadSessionReg->TabIndex = 3;
			this->buttonConfigReadSessionReg->UseVisualStyleBackColor = true;
			this->buttonConfigReadSessionReg->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::buttonConfigReadSessionReg_Click);
			// 
			// buttonConfigResetTag
			// 
			this->buttonConfigResetTag->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonConfigResetTag.BackgroundImage")));
			this->buttonConfigResetTag->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->buttonConfigResetTag->FlatAppearance->BorderSize = 0;
			this->buttonConfigResetTag->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonConfigResetTag->Location = System::Drawing::Point(187, 25);
			this->buttonConfigResetTag->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->buttonConfigResetTag->Name = L"buttonConfigResetTag";
			this->buttonConfigResetTag->Size = System::Drawing::Size(136, 121);
			this->buttonConfigResetTag->TabIndex = 3;
			this->buttonConfigResetTag->UseVisualStyleBackColor = true;
			this->buttonConfigResetTag->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::buttonConfigResetTag_Click);
			// 
			// buttonConfigReadTag
			// 
			this->buttonConfigReadTag->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonConfigReadTag.BackgroundImage")));
			this->buttonConfigReadTag->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->buttonConfigReadTag->FlatAppearance->BorderSize = 0;
			this->buttonConfigReadTag->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonConfigReadTag->Location = System::Drawing::Point(19, 25);
			this->buttonConfigReadTag->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->buttonConfigReadTag->Name = L"buttonConfigReadTag";
			this->buttonConfigReadTag->Size = System::Drawing::Size(136, 121);
			this->buttonConfigReadTag->TabIndex = 3;
			this->buttonConfigReadTag->UseVisualStyleBackColor = true;
			this->buttonConfigReadTag->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::buttonConfigReadTag_Click);
			// 
			// pictureBox8
			// 
			this->pictureBox8->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox8.BackgroundImage")));
			this->pictureBox8->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox8->Location = System::Drawing::Point(0, 481);
			this->pictureBox8->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(108, 46);
			this->pictureBox8->TabIndex = 10;
			this->pictureBox8->TabStop = false;
			// 
			// groupBoxF
			// 
			this->groupBoxF->Location = System::Drawing::Point(0, 0);
			this->groupBoxF->Name = L"groupBoxF";
			this->groupBoxF->Size = System::Drawing::Size(200, 100);
			this->groupBoxF->TabIndex = 0;
			this->groupBoxF->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(100, 50);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// tabFlash
			// 
			this->tabFlash->Location = System::Drawing::Point(0, 0);
			this->tabFlash->Name = L"tabFlash";
			this->tabFlash->Size = System::Drawing::Size(200, 100);
			this->tabFlash->TabIndex = 0;
			// 
			// labelf3
			// 
			this->labelf3->Location = System::Drawing::Point(0, 0);
			this->labelf3->Name = L"labelf3";
			this->labelf3->Size = System::Drawing::Size(100, 23);
			this->labelf3->TabIndex = 0;
			// 
			// labelf2
			// 
			this->labelf2->Location = System::Drawing::Point(0, 0);
			this->labelf2->Name = L"labelf2";
			this->labelf2->Size = System::Drawing::Size(100, 23);
			this->labelf2->TabIndex = 0;
			// 
			// labelf1
			// 
			this->labelf1->Location = System::Drawing::Point(0, 0);
			this->labelf1->Name = L"labelf1";
			this->labelf1->Size = System::Drawing::Size(100, 23);
			this->labelf1->TabIndex = 0;
			// 
			// labelf4
			// 
			this->labelf4->Location = System::Drawing::Point(0, 0);
			this->labelf4->Name = L"labelf4";
			this->labelf4->Size = System::Drawing::Size(100, 23);
			this->labelf4->TabIndex = 0;
			// 
			// progressBarFlash
			// 
			this->progressBarFlash->Location = System::Drawing::Point(0, 0);
			this->progressBarFlash->Name = L"progressBarFlash";
			this->progressBarFlash->Size = System::Drawing::Size(100, 23);
			this->progressBarFlash->TabIndex = 0;
			// 
			// textBoxFlashPerformance
			// 
			this->textBoxFlashPerformance->Location = System::Drawing::Point(0, 0);
			this->textBoxFlashPerformance->Name = L"textBoxFlashPerformance";
			this->textBoxFlashPerformance->Size = System::Drawing::Size(100, 22);
			this->textBoxFlashPerformance->TabIndex = 0;
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->flashToolStripMenuItem,
					this->aboutToolStripMenuItem, this->feedbackToolStripMenuItem, this->helpToolStripMenuItem
			});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(158, 108);
			// 
			// flashToolStripMenuItem
			// 
			this->flashToolStripMenuItem->Name = L"flashToolStripMenuItem";
			this->flashToolStripMenuItem->Size = System::Drawing::Size(157, 26);
			this->flashToolStripMenuItem->Text = L"Flash";
			this->flashToolStripMenuItem->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::flashToolStripMenuItem_Click);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(157, 26);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::aboutToolStripMenuItem_Click);
			// 
			// feedbackToolStripMenuItem
			// 
			this->feedbackToolStripMenuItem->Name = L"feedbackToolStripMenuItem";
			this->feedbackToolStripMenuItem->Size = System::Drawing::Size(157, 26);
			this->feedbackToolStripMenuItem->Text = L"Feedback";
			this->feedbackToolStripMenuItem->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::feedbackToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(157, 26);
			this->helpToolStripMenuItem->Text = L"Learn more";
			this->helpToolStripMenuItem->Click += gcnew System::EventHandler(this, &NTAG_I2C_Demo_GUI::helpToolStripMenuItem_Click);
			// 
			// imageList_NTAGlogo
			// 
			this->imageList_NTAGlogo->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList_NTAGlogo.ImageStream")));
			this->imageList_NTAGlogo->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList_NTAGlogo->Images->SetKeyName(0, L"ntagblue.png");
			this->imageList_NTAGlogo->Images->SetKeyName(1, L"ntaggreen.png");
			this->imageList_NTAGlogo->Images->SetKeyName(2, L"ntagorange.png");
			this->imageList_NTAGlogo->Images->SetKeyName(3, L"ntaggrey.png");
			// 
			// imageList2
			// 
			this->imageList2->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList2.ImageStream")));
			this->imageList2->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList2->Images->SetKeyName(0, L"taptag.png");
			this->imageList2->Images->SetKeyName(1, L"backButton2.png");
			this->imageList2->Images->SetKeyName(2, L"help.png");
			this->imageList2->Images->SetKeyName(3, L"NTAG_I2C_LowRes_Rev_1.3.jpg");
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->DefaultExt = L"bin";
			this->openFileDialog1->Filter = L".bin files|*.bin|All files|*.*";
			this->openFileDialog1->Title = L"Select firmware file";
			// 
			// imageList_NXPlogo
			// 
			this->imageList_NXPlogo->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList_NXPlogo.ImageStream")));
			this->imageList_NXPlogo->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList_NXPlogo->Images->SetKeyName(0, L"all_pressed.png");
			this->imageList_NXPlogo->Images->SetKeyName(1, L"left_middle_pressed.png");
			this->imageList_NXPlogo->Images->SetKeyName(2, L"left_pressed.png");
			this->imageList_NXPlogo->Images->SetKeyName(3, L"middle_pressed.png");
			this->imageList_NXPlogo->Images->SetKeyName(4, L"middle_right_pressed.png");
			this->imageList_NXPlogo->Images->SetKeyName(5, L"no_pressed.png");
			this->imageList_NXPlogo->Images->SetKeyName(6, L"right_left_pressed.png");
			this->imageList_NXPlogo->Images->SetKeyName(7, L"right_pressed.png");
			// 
			// imageIdentivReader
			// 
			this->imageIdentivReader->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageIdentivReader.ImageStream")));
			this->imageIdentivReader->TransparentColor = System::Drawing::Color::Transparent;
			this->imageIdentivReader->Images->SetKeyName(0, L"identiv_reader.png");
			// 
			// NTAG_I2C_Demo_GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(379, 562);
			this->Controls->Add(this->tabControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->MaximizeBox = false;
			this->Name = L"NTAG_I2C_Demo_GUI";
			this->Text = L"NTAG I²C Demo";
			this->tabControl1->ResumeLayout(false);
			this->tabLEDDemo->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureInfo))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockBlack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockBlack_NDEF))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockGreen_NDEF))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockGreen_NDEF))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockRed_NDEF))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockBlack_Speed))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockGreen_Speed))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockGreen_Speed))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockRed_Speed))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockBlack_Config))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockGreen_Config))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockGreen_Config))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockRed_Config))->EndInit();
			this->groupBoxBoardStatus->ResumeLayout(false);
			this->groupBoxBoardStatus->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pic_LedDemoT_NXP))->EndInit();
			this->groupBoxBoardConfig->ResumeLayout(false);
			this->groupBoxBoardConfig->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pic_LedDemoT_NTAGlogo))->EndInit();
			this->tabNDEF->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureInfo_ndef))->EndInit();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			this->groupBox8->ResumeLayout(false);
			this->groupBox8->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			this->groupBox7->ResumeLayout(false);
			this->tabSpeed->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureInfo_speed))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->tabConfig->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureInfo_config))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockGreen))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureLockRed))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureUnlockGreen))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->contextMenuStrip1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		WriteNDEFBox^ writeNDEFBox1;
		TapTagBox^ tapTagBoxReadMem;
		TapTagBox^ tapTagBoxResetMem;
		TapTagBox^ tapTagBoxReadSessionReg;
		TapTagBox^ tapTagBoxRWConfigReg;
		TapTagBox^ tapTagBoxAbout;
		TapTagBoxFLA^ tapTagBoxFlashing;
		SelectFlash^ SelectFlashing;
		FlashingBox^ BoxFlashing;
		HelpBox^ helpBox1;
		VersionBox^ versionBox1;
		ReadMemBox^ readMemBox1;
		ResetMemBox^ resetMemBox1;
		SessionRegBox^ sessionRegBox1;
		ConfigRegBox^ configRegBox1;
		ConfigRegBoxAccess^ configRegBoxAccess;

		char ledColor = 2;
		char previuosLedColor = 0;
		String^ FWVersion = "Unknown";
		String^ AppVersion = "1.4";
		String^ IdentivVer = "Unknown";

		Thread^ devThread;
		Thread^ flaThread;
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////// DEMO TAB ////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// Red button
		System::Void gButton_LedDemoT_Orange_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->ledColor = RED;
			this->previuosLedColor = RED;
			this->labelNTAGlogo->Text = L"Tap to switch off";
			this->pic_LedDemoT_NTAGlogo->BackgroundImage = this->imageList_NTAGlogo->Images[2];
		}

		// Blue button
		System::Void gButton_LedDemoT_Blue_Click(System::Object^  sender, System::EventArgs^  e) {
			this->ledColor = BLUE;
			this->previuosLedColor = BLUE;
			this->labelNTAGlogo->Text = L"Tap to switch off";
			this->pic_LedDemoT_NTAGlogo->BackgroundImage = this->imageList_NTAGlogo->Images[0];
		}

		// Green button
		System::Void gButton_LedDemoT_Green_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->ledColor = GREEN;
			this->previuosLedColor = GREEN;
			this->labelNTAGlogo->Text = L"Tap to switch off";
			this->pic_LedDemoT_NTAGlogo->BackgroundImage = this->imageList_NTAGlogo->Images[1];
		}

		// Switch ON/ OFF LED by clicking N logo
		System::Void pic_LedDemoT_NTAGlogo_Click(System::Object^  sender, System::EventArgs^  e) {

			if (ledColor == OFF){
				this->ledColor = this->previuosLedColor;
				this->previuosLedColor = this->ledColor;
				this->labelNTAGlogo->Text = L"Tap to switch off";
				if (this->ledColor == RED)
					this->pic_LedDemoT_NTAGlogo->BackgroundImage = this->imageList_NTAGlogo->Images[2];
				else if (this->ledColor == BLUE)
					this->pic_LedDemoT_NTAGlogo->BackgroundImage = this->imageList_NTAGlogo->Images[0];
				else if (this->ledColor == GREEN)
					this->pic_LedDemoT_NTAGlogo->BackgroundImage = this->imageList_NTAGlogo->Images[1];
			}
			else {
				this->previuosLedColor = this->ledColor;
				this->ledColor = OFF;
				this->labelNTAGlogo->Text = L"Tap to switch on";
				this->pic_LedDemoT_NTAGlogo->BackgroundImage = this->imageList_NTAGlogo->Images[3];

			}
		}
		// Check box NDEF read loop
		System::Void checkBox_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->cBox_NDEFT_Loop->Checked == true)
			{
				OnNdefDemo();
			}
		}
		// Enable LCD check box
		System::Void cBox_LedDemoT_LCD_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->cBox_LedDemoT_LCD->Checked) {
				this->checkBoxNDEFmsg->Enabled = true;
				this->checkBoxNDEFmsg->Visible = true;
			}
			else {
				this->checkBoxNDEFmsg->Checked = false;
				this->checkBoxNDEFmsg->Enabled = false;
				this->checkBoxNDEFmsg->Visible = false;
			}
		}

		// Information button
		System::Void pictureInfo_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->contextMenuStrip1->Show(Cursor->Position.X - this->contextMenuStrip1->Width, Cursor->Position.Y);
		}

		// Lockpad buttons
		System::Void pictureLockGreen_Click(System::Object^  sender, System::EventArgs^  e)
		{
			System::Windows::Forms::DialogResult dr;
			Password_Form^ pwd = gcnew Password_Form(this->authenticated, this->tagBlocked);
			dr = pwd->ShowDialog();
			LONG lReturn;

			if (pwd->ReturnValue == "STAR")
			{
				if (this->password == pwd->ReturnValue)
				{
					if (MessageBox::Show("Are you sure to disable authentication?", "Exit authentication mode", MessageBoxButtons::YesNo,
						MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
					{
						lReturn = my_api->setAuthentication("STAR");
						my_api->unlockTag();
						this->my_api->sram->auth = false;
						this->my_api->sram->blocked = false;
						this->my_api->eeprom->auth = false;
						this->my_api->eeprom->blocked = false;
						this->authenticated = false;
						this->tagBlocked = false;
					}
				}
				else
				{
					MessageBox::Show("Invalid password");
				}
			}
			else if (pwd->ReturnValue == "SUN")
			{
				if (this->password == pwd->ReturnValue)
				{
					if (MessageBox::Show("Are you sure to disable authentication?", "Exit authentication mode", MessageBoxButtons::YesNo,
						MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
					{
						lReturn = my_api->setAuthentication("SUN");
						my_api->unlockTag();
						this->my_api->sram->auth = false;
						this->my_api->sram->blocked = false;
						this->my_api->eeprom->auth = false;
						this->my_api->eeprom->blocked = false;
						this->authenticated = false;
						this->tagBlocked = false;
					}
				}
				else
				{
					MessageBox::Show("Invalid password");
				}
			}
			else if (pwd->ReturnValue == "MOON")
			{
				if (this->password == pwd->ReturnValue)
				{
					if (MessageBox::Show("Are you sure to disable authentication?", "Exit authentication mode", MessageBoxButtons::YesNo,
						MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
					{
						lReturn = my_api->setAuthentication("MOON");
						my_api->unlockTag();
						this->my_api->sram->auth = false;
						this->my_api->sram->blocked = false;
						this->my_api->eeprom->auth = false;
						this->my_api->eeprom->blocked = false;
						this->authenticated = false;
						this->tagBlocked = false;
					}
				}
				else
				{
					MessageBox::Show("Invalid password");
				}
			}
			if (this->tabControl1->SelectedTab->TabIndex != 0 ) this->taghandler->endWait = true;
		}

		System::Void pictureLockRed_Click(System::Object^  sender, System::EventArgs^  e)
		{
			System::Windows::Forms::DialogResult dr;
			Password_Form^ pwd = gcnew Password_Form(this->authenticated, this->tagBlocked);
			dr = pwd->ShowDialog();
			LONG lReturn;

			if (pwd->ReturnValue == "STAR")
			{
				this->password = "STAR";
				this->my_api->sram->pass_sram = "STAR";
				this->my_api->ndef->pass_ndef = "STAR";
				this->my_api->eeprom->pass_eeprom = "STAR";

				lReturn = my_api->setAuthentication("STAR");
				if (lReturn == SCARD_S_SUCCESS)
				{
					this->my_api->sram->auth = true;
					this->my_api->sram->blocked = true;
					this->my_api->eeprom->auth = true;
					this->my_api->eeprom->blocked = true;
					this->authenticated = true;
					this->tagBlocked = true;
				}
			}
			else if (pwd->ReturnValue == "SUN")
			{
				this->password = "SUN";
				this->my_api->sram->pass_sram = "SUN";
				this->my_api->ndef->pass_ndef = "SUN";
				this->my_api->eeprom->pass_eeprom = "SUN";

				lReturn = my_api->setAuthentication("SUN");
				if (lReturn == SCARD_S_SUCCESS)
				{
					this->my_api->sram->auth = true;
					this->my_api->sram->blocked = true;
					this->my_api->eeprom->auth = true;
					this->my_api->eeprom->blocked = true;
					this->authenticated = true;
					this->tagBlocked = true;
				}
			}
			else if (pwd->ReturnValue == "MOON")
			{
				this->password = "MOON";
				this->my_api->sram->pass_sram = "MOON";
				this->my_api->ndef->pass_ndef = "MOON";
				this->my_api->eeprom->pass_eeprom = "MOON";

				lReturn = my_api->setAuthentication("MOON");
				if (lReturn == SCARD_S_SUCCESS)
				{
					this->my_api->sram->auth = true;
					this->my_api->sram->blocked = true;
					this->my_api->eeprom->auth = true;
					this->my_api->eeprom->blocked = true;
					this->authenticated = true;
					this->tagBlocked = true;
				}
			}
			if (this->tabControl1->SelectedTab->TabIndex != 0) this->taghandler->endWait = true;
		}
		
		System::Void pictureUnlockGreen_Click(System::Object^  sender, System::EventArgs^  e)
		{
			System::Windows::Forms::DialogResult dr;
			Password_Form^ pwd = gcnew Password_Form(this->authenticated, this->tagBlocked);
			dr = pwd->ShowDialog();
			LONG lReturn;
			if (pwd->ReturnValue == "STAR")
			{
				this->password = "STAR";
				this->my_api->sram->pass_sram = "STAR";
				this->my_api->ndef->pass_ndef = "STAR";
				this->my_api->eeprom->pass_eeprom = "STAR";
				lReturn = my_api->setPassword("STAR");
				
				if (lReturn == SCARD_S_SUCCESS)
				{
					my_api->setAuthentication("STAR");
					my_api->lockTag();
					this->my_api->sram->auth = true;
					this->my_api->sram->blocked = true;
					this->my_api->eeprom->auth = true;
					this->my_api->eeprom->blocked = true;
					this->authenticated = true;
					this->tagBlocked = true;
				}
				else
				{
					MessageBox::Show("Password can't be established, please untap and tap the tag again");
				}
			}
			else if (pwd->ReturnValue == "SUN")
			{
				this->password = "SUN";
				this->my_api->sram->pass_sram = "SUN";
				this->my_api->ndef->pass_ndef = "SUN";
				this->my_api->eeprom->pass_eeprom = "SUN";
				lReturn = my_api->setPassword("SUN");
				
				if (lReturn == SCARD_S_SUCCESS)
				{
					my_api->setAuthentication("SUN");
					my_api->lockTag();
					this->my_api->sram->auth = true;
					this->my_api->sram->blocked = true;
					this->my_api->eeprom->auth = true;
					this->my_api->eeprom->blocked = true;
					this->authenticated = true;
					this->tagBlocked = true;
				}
				else
				{
					MessageBox::Show("Password can't be established, please untap and tap the tag again");
				}
			}
			else if (pwd->ReturnValue == "MOON")
			{
				this->password = "MOON";
				this->my_api->sram->pass_sram = "MOON";
				this->my_api->ndef->pass_ndef = "MOON";
				this->my_api->eeprom->pass_eeprom = "MOON";
				lReturn = my_api->setPassword("MOON");
				
				if (lReturn == SCARD_S_SUCCESS)
				{
					my_api->setAuthentication("MOON");
					my_api->lockTag();
					this->my_api->sram->auth = true;
					this->my_api->sram->blocked = true;
					this->my_api->eeprom->auth = true;
					this->my_api->eeprom->blocked = true;
					this->authenticated = true;
					this->tagBlocked = true;
				}
				else
				{
					MessageBox::Show("Password can't be established, please untap and tap the tag again");
				}
			}
			if (this->tabControl1->SelectedTab->TabIndex != 0) this->taghandler->endWait = true;
		}

		//Info images

		System::Void pictureInfo_ndef_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->contextMenuStrip1->Show(Cursor->Position.X - this->contextMenuStrip1->Width, Cursor->Position.Y);		
		}

		System::Void pictureInfo_speed_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->contextMenuStrip1->Show(Cursor->Position.X - this->contextMenuStrip1->Width, Cursor->Position.Y);	
		}

		System::Void pictureInfo_config_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->contextMenuStrip1->Show(Cursor->Position.X - this->contextMenuStrip1->Width, Cursor->Position.Y);	
		}

		// About option inside the information menu
		System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->tabControl1->Hide();
			this->tapTagBoxAbout->setLabel("");
			
			taghandler->endWait = true;
			this->tapTagBoxAbout->Show();
		}

		// About groupbox 
		System::Void tapTagBoxAbout_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->tapTagBoxAbout->swi == true)
			{
				this->tapTagBoxAbout->swi = false;
				this->tapTagBoxAbout->Hide();
				this->tabControl1->Show();
			}
		}

		// Flash option inside the information menu
		System::Void flashToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (!(this->checkTag))
			{
				this->tabControl1->Hide();
				this->tapTagBoxFlashing->setLabel("");
				this->tapTagBoxFlashing->Show();
			}
			else
			{
				MessageBox::Show("Please untap the tag");
			}
		}

		// Flash groupbox 
		System::Void tapTagBoxFlashing_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->tapTagBoxFlashing->swi == true) //From storage
			{
				this->tapTagBoxFlashing->swi = false;
				if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					String^ fileName = this->openFileDialog1->FileName;
					int ind = this->openFileDialog1->FileName->LastIndexOf('\\');
					String^ file = this->openFileDialog1->FileName->Substring(ind + 1);

					this->tapTagBoxFlashing->textBox->Text = file;
					this->tapTagBoxFlashing->Refresh();

					taghandler->endWait = true;
				}
			}
			else if (this->tapTagBoxFlashing->dwi == true) //From APP
			{
				this->tapTagBoxFlashing->dwi = false;

				this->tapTagBoxFlashing->Hide();
				this->SelectFlashing->Show();

			}
			else if (this->tapTagBoxFlashing->mwi == true)
			{
				this->tapTagBoxFlashing->mwi = false;

				this->tapTagBoxFlashing->Hide();
				this->tabControl1->Show();
				taghandler->endWait = true;
			}
		}
		// SelectFlash groupbox 
		System::Void SelectFlashing_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->SelectFlashing->swi == true) //Demo App selected
			{
				this->SelectFlashing->swi = false;
				if (this->SelectFlashing->selDemo == false)
				{
					this->SelectFlashing->selDemo = true;
				}
				dir = "NTAG_I2C_Explorer_Demo.bin";
				this->tapTagBoxFlashing->textBox->Text = dir;
				this->tapTagBoxFlashing->Refresh();

				this->SelectFlashing->Hide();
				this->tapTagBoxFlashing->Show();

			}
			else if (this->SelectFlashing->dwi == true) //LED Blinker selected
			{
				this->SelectFlashing->dwi = false;
				if (this->SelectFlashing->selBlink == false)
				{
					this->SelectFlashing->selBlink = true;
				}
				dir = "NTAG_I2C_Explorer_Blink.bin";

				this->tapTagBoxFlashing->textBox->Text = dir;
				this->tapTagBoxFlashing->Refresh();

				this->SelectFlashing->Hide();
				this->tapTagBoxFlashing->Show();
			}
			else if (this->SelectFlashing->mwi == true)
			{
				this->SelectFlashing->Hide();
				this->tapTagBoxFlashing->Show();
			}

		}
		// Versions groupbox back button
		System::Void versionsBackButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->versionBox1->Hide();
			this->tabControl1->Show();
			taghandler->endWait = true;
		}

		// Feedback option inside the information menu
		System::Void feedbackToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			HKEY hKey;

			String^ mailto = "mailto:mobileapp.support@nxp.com?subject=NTAG I2C Demo Feedback&body=";
			BYTE lpData[100];
			DWORD dwLength;
			wchar_t wData[100];
			String^ sData;

			if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS)
			{
				// e.g.: Windows edition: Windows 7 Professional
				dwLength = 100;
				if (RegQueryValueEx(hKey, L"ProductName", NULL, NULL, lpData, &dwLength) == ERROR_SUCCESS)
				{
					memcpy(wData, lpData, dwLength);
					wData[dwLength / 2 - 1] = '\0';	// To be sure...
					sData = gcnew String(wData);
					mailto += "Windows edition: " + sData + "%0D";
				}

				// e.g.: CSD Version: Service Pack 1
				dwLength = 100;
				if (RegQueryValueEx(hKey, L"CSDVersion", NULL, NULL, lpData, &dwLength) == ERROR_SUCCESS)
				{
					memcpy(wData, lpData, dwLength);
					wData[dwLength / 2 - 1] = '\0';	// To be sure...
					sData = gcnew String(wData);
					mailto += "CSD Version: " + sData + "%0D";
				}
				RegCloseKey(hKey);
			}

			if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\OEMInformation", 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS)
			{
				// e.g.: Manufacturer: Dell
				dwLength = 100;
				if (RegQueryValueEx(hKey, L"Manufacturer", NULL, NULL, lpData, &dwLength) == ERROR_SUCCESS)
				{
					memcpy(wData, lpData, dwLength);
					wData[dwLength / 2 - 1] = '\0';	// To be sure...
					sData = gcnew String(wData);
					mailto += "Manufacturer: " + sData + "%0D";
				}

				// e.g.: Model: Latitude E5440
				dwLength = 100;
				if (RegQueryValueEx(hKey, L"Model", NULL, NULL, lpData, &dwLength) == ERROR_SUCCESS)
				{
					memcpy(wData, lpData, dwLength);
					wData[dwLength / 2 - 1] = '\0';	// To be sure...
					sData = gcnew String(wData);
					mailto += "Model: " + sData + "%0D";
				}
				RegCloseKey(hKey);
			}

			if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
			{
				// e.g.: Processor: Intel(R) Core(TM) i5-4300U CPU @ 1.90GHz  2,494 GHz  64-bit
				dwLength = 100;
				if (RegQueryValueEx(hKey, L"ProcessorNameString", NULL, NULL, lpData, &dwLength) == ERROR_SUCCESS)
				{
					memcpy(wData, lpData, dwLength);
					wData[dwLength / 2 - 1] = '\0';	// To be sure...
					sData = gcnew String(wData);
					mailto += "Processor: " + sData;

					DWORD dwNum;
					dwLength = 100;
					if (RegQueryValueEx(hKey, L"~MHz", NULL, NULL, lpData, &dwLength) == ERROR_SUCCESS)
					{
						memcpy(&dwNum, lpData, sizeof(dwNum));
						float fNum = (float)dwNum / 1000;
						mailto += "  " + fNum.ToString() + " GHz";
					}
					dwLength = 100;
					if (RegQueryValueEx(hKey, L"Platform ID", NULL, NULL, lpData, &dwLength) == ERROR_SUCCESS)
					{
						memcpy(&dwNum, lpData, sizeof(dwNum));
						mailto += "  " + dwNum.ToString() + "-bit";
					}
				}
				mailto += "%0D";
				RegCloseKey(hKey);
			}

			// e.g.: Installed memory (RAM): 3,91 GB
			MEMORYSTATUSEX memStat;
			memStat.dwLength = sizeof(memStat);
			if (GlobalMemoryStatusEx(&memStat) != 0)
			{
				float fNum = (float)memStat.ullTotalPhys / (1024 * 1024 * 1024);
				mailto += "Installed memory (RAM): " + fNum.ToString("0.00") + " GB%0D";
			}

			if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment", 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS)
			{
				// e.g.: System type: 64-bit Operating System
				dwLength = 100;
				if (RegQueryValueEx(hKey, L"PROCESSOR_ARCHITECTURE", NULL, NULL, lpData, &dwLength) == ERROR_SUCCESS)
				{
					memcpy(wData, lpData, dwLength);
					wData[dwLength / 2 - 1] = '\0';	// To be sure...
					if (wcscmp(wData, L"x86") == 0)
						mailto += "System type: 32-bit Operating System%0D";
					if (wcscmp(wData, L"AMD64") == 0)
						mailto += "System type: 64-bit Operating System%0D";
				}
				RegCloseKey(hKey);
			}

			System::Diagnostics::Process::Start(mailto);
		}

		// Learn more option inside the information menu
		System::Void helpToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->tabControl1->Hide();
			this->helpBox1->Show();
		}

		// Help groupbox 
		System::Void helpBox1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->helpBox1->mwi == true)
			{
				this->helpBox1->mwi = false;
				this->helpBox1->Hide();
				this->tabControl1->Show();
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////// NDEF TAB ////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// Read NDEF button
		System::Void gButton_NDEFT_ReadNDEF_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->gButton_NDEFT_ReadNDEF->isActive = true;
			this->gButton_NDEFT_WriteNDEF->isActive = false;
			this->gButton_NDEFT_ReadNDEF->Refresh();
			this->gButton_NDEFT_WriteNDEF->Refresh();
			this->ndef->Refresh();
			this->label_NDEFT_Content->Text = L"Tap tag to read NDEF content";
			this->writeNDEFBox1->Hide();
			this->buttonWriteNDEF = false;
			this->buttonSmartPosterNDEF = false;
			firstNDEF = true;
			this->groupBox8->Show();
			this->groupBox5->Text = L"Read performance";
			taghandler->endWait = true;
		}

		// Write NDEF button
		System::Void gButton_NDEFT_WriteNDEF_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->buttonWriteNDEF == false)
			{
				/*if (this->gButton_NDEFT_WriteNDEF->isActive == true)
				{
					this->buttonWriteNDEF = true;
				}
				else*/
				this->buttonWriteNDEF = true;
			}
			/*else if (this->buttonWriteNDEF == true)
			{
				this->buttonWriteNDEF = false;
			}*/
			this->gButton_NDEFT_ReadNDEF->isActive = false;
			this->gButton_NDEFT_WriteNDEF->isActive = true;
			this->gButton_NDEFT_ReadNDEF->Refresh();
			this->gButton_NDEFT_WriteNDEF->Refresh();
			this->ndef->Refresh();
			if (this->writeNDEFBox1->label1 != nullptr)
				this->writeNDEFBox1->label1->Text = "Tap tag to write NDEF message";
			this->writeNDEFBox1->Show();
			firstNDEF = true;
			this->groupBox8->Hide();
			this->groupBox5->Text = L"Write Performance";
			this->textBoxNDEFPerformance->Text = "";
			taghandler->endWait = true;
		}
		
		// Write default NDEF button
		System::Void ndef_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->gButton_NDEFT_ReadNDEF->isActive = false;
			this->gButton_NDEFT_WriteNDEF->isActive = true;
			this->gButton_NDEFT_ReadNDEF->Refresh();
			this->gButton_NDEFT_WriteNDEF->Refresh();
			this->ndef->Refresh();
			this->buttonSmartPosterNDEF = true;
			firstNDEF = true;
			if (this->writeNDEFBox1->label1 != nullptr)
				this->writeNDEFBox1->label1->Text = "Tap tag to write NDEF message";
			this->writeNDEFBox1->Show();
			this->groupBox8->Hide();
			this->groupBox5->Text = L"Write performance";
			this->textBoxNDEFPerformance->Text = "";
			
			taghandler->endWait = true;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////// SPEED TAB ///////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// SRAM radio button
		System::Void radioButtonSRAM_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			this->label8->Text = L"x 64 bytes";
			this->textBox1->Text = "10";
		}

		// EEPROM radio button
		System::Void radioButtonEEPROM_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			this->label8->Text = L"+12 overhead bytes";
			this->textBox1->Text = "640";
		}

		// Start button
		System::Void gButton_SpeedT_Start_Click(System::Object^  sender, System::EventArgs^  e)
		{
			firstSPEED = true;
			taghandler->endWait = true;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////// CONFIG TAB //////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// Read tag memory button
		System::Void buttonConfigReadTag_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->tabControl1->Hide();
			this->tapTagBoxReadMem->setLabel("");
			this->tapTagBoxReadMem->Show();
			taghandler->endWait = true;
		}

		// Reset tag memory button
		System::Void buttonConfigResetTag_Click(System::Object^  sender, System::EventArgs^  e)
		{
			taghandler->endWait = true;
			this->tabControl1->Hide();
			this->tapTagBoxResetMem->setLabel("");
			this->tapTagBoxResetMem->Show();
		}

		// Read session registers button
		System::Void buttonConfigReadSessionReg_Click(System::Object^  sender, System::EventArgs^  e)
		{
			taghandler->endWait = true;
			this->tabControl1->Hide();
			this->tapTagBoxReadSessionReg->setLabel("");
			this->tapTagBoxReadSessionReg->Show();
		}

		// Read/write config registers button
		System::Void buttonConfigRWConfigReg_Click(System::Object^  sender, System::EventArgs^  e)
		{
			taghandler->endWait = true;
			this->tabControl1->Hide();
			this->tapTagBoxRWConfigReg->setLabel("");
			this->tapTagBoxRWConfigReg->Show();
		}

		// Read tag memory groupbox 
		System::Void tapTagBoxReadMem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->tapTagBoxReadMem->swi == true)
			{
				firstREG = true;
				this->tapTagBoxReadMem->swi = false;
				this->tapTagBoxReadMem->Hide();
				this->tabControl1->Show();
			}
		}

		// Reset tag memory groupbox
		System::Void tapTagBoxResetMem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->tapTagBoxResetMem->swi == true)
			{
				firstREG = true;
				this->tapTagBoxResetMem->swi = false;
				this->tapTagBoxResetMem->Hide();
				this->tabControl1->Show();
			}
		}

		// Read session registers groupbox
		System::Void tapTagBoxReadSessionReg_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->tapTagBoxReadSessionReg->swi == true)
			{
				firstREG = true;
				this->tapTagBoxReadSessionReg->swi = false;
				this->tapTagBoxReadSessionReg->Hide();
				this->tabControl1->Show();
			}
		}

		// Read/write config registers groupbox
		System::Void tapTagBoxRWConfigReg_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->tapTagBoxRWConfigReg->swi == true)
			{
				firstREG = true;
				this->tapTagBoxRWConfigReg->swi = false;
				this->tapTagBoxRWConfigReg->Hide();
				this->tabControl1->Show();
			}
		}

		// Tag memory groupbox
		System::Void readMemBox1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			firstREG = true;
			this->readMemBox1->Hide();
			this->tabControl1->Show();
		}

		// Tag memory reset groupbox
		System::Void resetMemBox1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			firstREG = true;
			this->resetMemBox1->Hide();
			this->tabControl1->Show();
		}

		// Session registers groupbox back button
		System::Void sessionRegBackButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			firstREG = true;
			this->sessionRegBox1->Hide();
			this->tabControl1->Show();
		}

		// Config registers groupbox back button
		System::Void configRegBackButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			firstREG = true;
			this->configRegBox1->Hide();
			this->tabControl1->Show();
		}

		// Config registers groupbox back button
		System::Void configRegAccessBackButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			firstREG = true;
			this->configRegBoxAccess->Hide();
			this->tabControl1->Show();
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////// FLASHING TAG ////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// Flashing form groupbox back button
		System::Void FlashingBackButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			/*if (this->BoxFlashing->swi == true)
			{
			this->BoxFlashing->swi = false;*/
			this->BoxFlashing->Hide();
			this->tabControl1->Show();
			MessageBox::Show("Please untap the device to start using the new firmware");
			this->hasBeenFlashed = false;
			this->checkTag = false;
			taghandler->endWait = true;
			//	}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////// OTHER FUNCTIONS /////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// Action taken when clicking on tabs "DEMO" or "NDEF"
		System::Void tabControl1_Selected(System::Object^  sender, TabControlEventArgs^  e)
		{
			if (this->tabControl1->SelectedTab->TabIndex == 0)
				taghandler->endWait = true;
			if (this->tabControl1->SelectedTab->TabIndex == 1)
			{
				if (this->writeNDEFBox1->label1 != nullptr)
					this->writeNDEFBox1->label1->Text = "Tap tag to write NDEF message";
				this->label_NDEFT_Content->Text = "Tap tag to read NDEF content";
				taghandler->endWait = true;
			}
			if (this->tabControl1->SelectedTab->TabIndex == 2)
				taghandler->endWait = true;
			if (this->tabControl1->SelectedTab->TabIndex == 3)
				taghandler->endWait = true;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////// TAP EVENT ///////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		System::Void OnTagEvent(System::Object^  sender, System::EventArgs^  e)
		{
			OnTagEventSafe();
		}

		delegate void OnTagEventDelegate();

		void OnTagEventSafe()
		{
			DWORD dwAP; //Active protocol
			LONG lReturn;

			if (this->tabControl1->InvokeRequired)
			{
				if (firstTimeFalse)
				{
					retu = this->my_api->my_rf->establishConnection(SCARD_SHARE_EXCLUSIVE, &dwAP);
					if (retu == SCARD_S_SUCCESS)
					{
						firstTimeFalse = false;
						this->checkTag = true;
						firstREG = true;
						firstSPEED = true;
						
						if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
						{
							if (checkStatus()) //If the tag is blocked
							{
								this->tagBlocked = true;
							}

							//Check if NFC PROT is active
							Ntag_I2C_Access_Registers_t accessReg;
							lReturn = my_api->ReadAccessRegisters(&accessReg);
							if (accessReg.REG_NFC_PROT == false)
							{
								this->protectedRead = false;
							}
							else
							{
								this->protectedRead = true;
							}

							//Check if the SRAM is protected
							BYTE data[NTAG_MEM_SIZE_SRAM];
							if (this->my_api->sram->ReadSram(data) == SCARD_S_SUCCESS)
							{
								this->sramProtected = false;
							}
							else
							{
								this->sramProtected = true;
							}
						}
						if (this->authenticated)
						{
							this->my_api->setAuthentication(this->password);
						}
					}
				}
				OnTagEventDelegate^ d = gcnew OnTagEventDelegate(this, &NTAG_I2C_Demo_GUI::OnTagEventSafe);
				this->Invoke(d);
			}
			else
			{
				// If isLedDemo is true, it means that the Led Demo is ongoing. Reset the isLedDemo variable and then check if the current tab is the BoardDemo tab
				// Note that it could happen that isLedDemo is true and the current tab is another one, because the user has just changed from the Led Demo tab to another one with the tag on the reader
				// In this case, the application shall not enter in any of the options, and shall wait until the tag is removed
				if (this->taghandler->isLedDemo == true)
				{
					this->taghandler->isLedDemo = false;
					if (this->tabControl1->SelectedTab->TabIndex == 0)
					{	
						// LED Demo
						OnLedDemo();
						tagVersion = my_api->GetVersion();
						setLockIcon(tagVersion);
					}
				}
				else
				{
					switch (this->tabControl1->SelectedTab->TabIndex)
					{
					case 0:
						// LED Demo
						OnLedDemo();
						tagVersion = my_api->GetVersion();
						setLockIcon(tagVersion);
						break;
					case 1:
						// NDEF Demo
						OnNdefDemo();
						tagVersion = my_api->GetVersion();
						setLockIcon(tagVersion);
						break;
					case 2:
						// Speed Test Demo
						OnSpeedTestDemo();
						tagVersion = my_api->GetVersion();
						setLockIcon(tagVersion);
						break;
					case 3:
						// Config Options
						if (!this->hasBeenFlashed)
						{
							OnConfigOption();
							tagVersion = my_api->GetVersion();
							setLockIcon(tagVersion);
						}
						break;
					default:
						MessageBox::Show("Non-valid tab selected");
						break;
					}
				}
			}
		}

		// This function is executed again and again when the current tab is the Led Demo and the tag is on the reader
		// It is also executed when the user has clicked on info -> Flash and info -> About, but in this case it is only executed once: when it enters (if the tag is already there) or when the tag is tapped
		void OnLedDemo()
		{
			LONG lReturn;

			if (this->versionBox1->Visible)
			{
				// Read the board version
				this->versionBox1->setLabel("Reading the board version...");
				Versions_t versions;
				lReturn = board_demo->ReadVersions(&versions);
				if (lReturn == SCARD_S_SUCCESS)
				{
					this->versionBox1->updateBox(versions, this->AppVersion, this->IdentivVer);
					this->versionBox1->setLabel("");
				}
				else
					this->versionBox1->setLabel("Error while reading the board version");
			}
			else if (this->tapTagBoxAbout->Visible)
			{
				if (retu == SCARD_S_SUCCESS)
				{
					char  IdentivReaderFWversion[3];
					my_api->readIdentivFWversion(IdentivReaderFWversion);

					String^ strNew = gcnew String(IdentivReaderFWversion);

					this->IdentivVer = strNew;

					// Read the board version
					this->tapTagBoxAbout->setLabel("Reading the board version...");
					Versions_t versions;
					lReturn = board_demo->ReadVersions(&versions);
					if (lReturn == SCARD_S_SUCCESS)
					{
						this->versionBox1->updateBox(versions, this->AppVersion, this->IdentivVer);
						this->versionBox1->setLabel("");
						this->versionBox1->Show();
						this->tapTagBoxAbout->Hide();
					}
					else
						this->tapTagBoxAbout->setLabel("Error while reading the board version");
				}
			}
			else if (this->BoxFlashing->Visible)
			{
				checking = "";
				if (this->tapTagBoxFlashing->textBox->Text == checking)
				{
					//MessageBox::Show("Please select a valid file");
					this->BoxFlashing->Hide();
					this->tapTagBoxFlashing->Show();
				}
				else
				{
					this->BoxFlashing->setLabel("Flashing memory content...");
					
					if (this->tagBlocked && !this->authenticated)
					{
						authenticate();
					}

					if (this->SelectFlashing->selBlink == true)
					{
						this->BoxFlashing->textBoxFile->Text = "NTAG_I2C_Explorer_Blink.bin";
					}
					else if (this->SelectFlashing->selDemo == true)
					{
						this->BoxFlashing->textBoxFile->Text = "NTAG_I2C_Explorer_Demo.bin";
					}
					else
					{
						String^ fileName = this->openFileDialog1->FileName;
						int ind = this->openFileDialog1->FileName->LastIndexOf('\\');
						String^ file = this->openFileDialog1->FileName->Substring(ind + 1);

						this->BoxFlashing->textBoxFile->Text = file;
					}
					Sleep(1000);
					this->BoxFlashing->setLabel("");
					this->BoxFlashing->textBoxFlashPerformance->Text = "";

					const int maxFWLength = 16384;	// The maximum firmware that can be flashed is 16384 (4 sectors of 4096 bytes each)
					System::IO::Stream^ newFWStream = nullptr;
					System::IO::Stream^ DemoStream = nullptr;

					if (this->SelectFlashing->selBlink == true)
					{
						this->SelectFlashing->selBlink = false;
						String^ path = ".\\rsc\\NTAG_I2C_Explorer_Blink.bin";
						FileStream^ fs = File::OpenRead(path);

						DemoStream = fs;

						int newFWLength = (int)DemoStream->Length;
						int currentLength = 0;
						this->BoxFlashing->progressBarFlash->Step = 64;
						this->BoxFlashing->progressBarFlash->Value = 0;
						if (newFWLength > 12288)
							this->BoxFlashing->progressBarFlash->Maximum = maxFWLength;
						else if (newFWLength > 8192)
							this->BoxFlashing->progressBarFlash->Maximum = 12288;
						else if (newFWLength > 4096)
							this->BoxFlashing->progressBarFlash->Maximum = 8192;
						else
							this->BoxFlashing->progressBarFlash->Maximum = 4096;

						// Check that the firmware is not too big
						if (newFWLength <= maxFWLength)
						{
							DWORD flashBytes;
							float flashTime;

							// Convert the Stream variable to a BYTE array
							BYTE newFW[maxFWLength];
							array<Byte>^ newFWArray = gcnew array<Byte>(newFWLength);
							int n = DemoStream->Read(newFWArray, 0, newFWLength);
							DemoStream->Close();
							for (int i = 0; i < newFWLength; i++)
							{
								newFW[i] = (BYTE)newFWArray[i];
							}

							lReturn = FlashMemory(newFW, newFWLength, &flashBytes, &flashTime, this->BoxFlashing->progressBarFlash);

							if (lReturn == SCARD_S_SUCCESS)
							{
								this->BoxFlashing->setLabel("Memory flash completed successfully");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->tapTagBoxFlashing->Refresh();
								this->BoxFlashing->textBoxFlashPerformance->Text = " Speed(" + flashBytes + " B / " + flashTime + " ms): " +
									(1000.0 * flashBytes / flashTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
							}
							else
							{
								this->BoxFlashing->setLabel("Error during memory flash");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->tapTagBoxFlashing->Refresh();
							}
						}
						else
							this->BoxFlashing->setLabel("The file is too big. Maximum size: 16384 bytes (16 kB)");
					}

					else if (this->SelectFlashing->selDemo == true)
					{
						this->SelectFlashing->selDemo = false;
						String^ path = ".\\rsc\\NTAG_I2C_Explorer_Demo.bin";
						FileStream^ fs = File::OpenRead(path);

						DemoStream = fs;

						int newFWLength = (int)DemoStream->Length;
						int currentLength = 0;
						this->BoxFlashing->progressBarFlash->Step = 64;
						this->BoxFlashing->progressBarFlash->Value = 0;
						if (newFWLength > 12288)
							this->BoxFlashing->progressBarFlash->Maximum = maxFWLength;
						else if (newFWLength > 8192)
							this->BoxFlashing->progressBarFlash->Maximum = 12288;
						else if (newFWLength > 4096)
							this->BoxFlashing->progressBarFlash->Maximum = 8192;
						else
							this->BoxFlashing->progressBarFlash->Maximum = 4096;

						// Check that the firmware is not too big
						if (newFWLength <= maxFWLength)
						{
							DWORD flashBytes;
							float flashTime;

							// Convert the Stream variable to a BYTE array
							BYTE newFW[maxFWLength];
							array<Byte>^ newFWArray = gcnew array<Byte>(newFWLength);
							int n = DemoStream->Read(newFWArray, 0, newFWLength);
							DemoStream->Close();
							for (int i = 0; i < newFWLength; i++)
							{
								newFW[i] = (BYTE)newFWArray[i];
							}

							lReturn = FlashMemory(newFW, newFWLength, &flashBytes, &flashTime, this->BoxFlashing->progressBarFlash);

							if (lReturn == SCARD_S_SUCCESS)
							{
								this->BoxFlashing->setLabel("Memory flash completed successfully");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->tapTagBoxFlashing->Refresh();
								this->BoxFlashing->textBoxFlashPerformance->Text = " Speed(" + flashBytes + " B / " + flashTime + " ms): " +
									(1000.0 * flashBytes / flashTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
							}
							else
							{
								this->BoxFlashing->setLabel("Error during memory flash");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->tapTagBoxFlashing->Refresh();
							}
						}
						else
							this->BoxFlashing->setLabel("The file is too big. Maximum size: 16384 bytes (16 kB)");
					}
					// Read the file in a Stream variable
					else if ((newFWStream = this->openFileDialog1->OpenFile()) != nullptr)
					{
						int newFWLength = (int)newFWStream->Length;
						int currentLength = 0;
						// Check that the firmware is not too big
						if (newFWLength <= maxFWLength)
						{
							this->BoxFlashing->progressBarFlash->Step = 64;
							this->BoxFlashing->progressBarFlash->Value = 0;
							if (newFWLength > 12288)
								this->BoxFlashing->progressBarFlash->Maximum = maxFWLength;
							else if (newFWLength > 8192)
								this->BoxFlashing->progressBarFlash->Maximum = 12288;
							else if (newFWLength > 4096)
								this->BoxFlashing->progressBarFlash->Maximum = 8192;
							else
								this->BoxFlashing->progressBarFlash->Maximum = 4096;

							DWORD flashBytes;
							float flashTime;

							// Convert the Stream variable to a BYTE array
							BYTE newFW[maxFWLength];
							array<Byte>^ newFWArray = gcnew array<Byte>(newFWLength);
							int n = newFWStream->Read(newFWArray, 0, newFWLength);
							newFWStream->Close();
							for (int i = 0; i < newFWLength; i++)
							{
								newFW[i] = (BYTE)newFWArray[i];
							}

							lReturn = FlashMemory(newFW, newFWLength, &flashBytes, &flashTime, this->BoxFlashing->progressBarFlash);

							if (lReturn == SCARD_S_SUCCESS)
							{
								this->BoxFlashing->setLabel("Memory flash completed successfully");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->tapTagBoxFlashing->Refresh();

								if (this->BoxFlashing->progressBarFlash->Value == this->BoxFlashing->progressBarFlash->Maximum)
								{
									this->BoxFlashing->progressBarFlash->PerformStep();
									this->BoxFlashing->progressBarFlash->Value = 0;
								}

								this->BoxFlashing->textBoxFlashPerformance->Text = " Speed(" + flashBytes + " B / " + flashTime + " ms): " +
									(1000.0 * flashBytes / flashTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
							}
							else
							{
								this->BoxFlashing->setLabel("Error during memory flash");
								Sleep(1000);
								this->BoxFlashing->setLabel("");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->tapTagBoxFlashing->Refresh();
							}
						}
						else
						{
							this->BoxFlashing->setLabel("The file is too big. Maximum size: 16384 bytes (16 kB)");
							Sleep(1000);
							this->BoxFlashing->setLabel("");
						}

					}
					else
					{
						this->BoxFlashing->setLabel("Could not open the file");
						Sleep(1000);
						this->BoxFlashing->setLabel("");
					}
				}
			}
			else if (this->tapTagBoxFlashing->Visible)
			{
				checking = "";
				if (this->tapTagBoxFlashing->textBox->Text != checking)
				{
					String^ file = nullptr;
					if (this->tapTagBoxFlashing->swi == true) //From storage
					{
						String^ fileName = this->openFileDialog1->FileName;
						int ind = this->openFileDialog1->FileName->LastIndexOf('\\');
						file = this->openFileDialog1->FileName->Substring(ind + 1);
						this->tapTagBoxFlashing->swi = false;
						this->BoxFlashing->textBoxFile->Text = file;
						this->BoxFlashing->Refresh();
					}
					else if (this->tapTagBoxFlashing->dwi == true)
					{
						if (this->SelectFlashing->selDemo == true) //Demo App selected
						{
							file = L"NTAG_I2C_Explorer_Demo.bin";
						}
						else if (this->SelectFlashing->selBlink == true) //LED Blinker selected
						{
							file = L"NTAG_I2C_Explorer_Blink.bin";
						}
						this->tapTagBoxFlashing->dwi = false;
						this->BoxFlashing->textBoxFile->Text = file;
						this->BoxFlashing->Refresh();
					}

					this->BoxFlashing->setLabel("");
					this->BoxFlashing->Show();
					this->BoxFlashing->textBoxFlashPerformance->Text = "";
					this->tapTagBoxFlashing->Hide();
										
					taghandler->endWait = true;
				}
				else
				{
					this->tapTagBoxFlashing->setLabel("Error while flashing the memory");
					checking = "";
					this->tapTagBoxFlashing->textBox->Text = checking;
				}
			}
			else
			{
				this->cBox_NDEFT_Loop->Checked = false;

				// Perform the LED Demo
				BOOL rightButton = 0, middleButton = 0, leftButton = 0;
				float tempC, tempF, voltage, version;
				BOOL enTemp = this->cBox_LedDemoT_TempSensor->Checked;
				BOOL enLCD = this->cBox_LedDemoT_LCD->Checked;
				BOOL dispNDEF = this->checkBoxNDEFmsg->Checked;

				if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
				{
					Sleep(10);
					lReturn = board_demo->Run(this->ledColor, enTemp, enLCD, dispNDEF, &leftButton, &middleButton, &rightButton, &tempC, &tempF, &voltage, &version);
					Sleep(10);
					if (lReturn == SCARD_S_SUCCESS)
					{
						// Show what buttons are pressed
						if (leftButton != 0)
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[2];
						if (middleButton != 0)
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[3];
						if (rightButton != 0)
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[7];
						if ((rightButton != 0) && (middleButton != 0))
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[4];
						if ((rightButton != 0) && (leftButton != 0))
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[6];
						if ((leftButton != 0) && (middleButton != 0))
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[1];
						if ((rightButton != 0) && (middleButton != 0))
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[4];
						if ((rightButton != 0) && (middleButton != 0) && (leftButton != 0))
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[0];
						if ((rightButton == 0) && (middleButton == 0) && (leftButton == 0))
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[5];

						// Show the temperature and voltage
						this->label_LedDemoT_BoardStatus->Location = System::Drawing::Point(this->label_LedDemoT_BoardStatus->Location.X, 18);

						//Show arrow moving when the tag is connected
						if (transferDir != 1)
						{
							this->label_LedDemoT_BoardStatus->Text = "Transfer: Device --> Tag \nTemperature: ";
							transferDir = 1;
						}
						else
						{
							this->label_LedDemoT_BoardStatus->Text = "Transfer: Device <-- Tag \nTemperature: ";
							transferDir = 0;
						}
						if (enTemp)
							this->label_LedDemoT_BoardStatus->Text += tempC.ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " ºC / " +
							tempF.ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " ºF";
						else
							this->label_LedDemoT_BoardStatus->Text += "Not available";
						this->label_LedDemoT_BoardStatus->Text += "\nVoltage: " + voltage.ToString("0.0", System::Globalization::CultureInfo::InvariantCulture) + " V";

						// Update the version
						this->FWVersion = version.ToString("0.0", System::Globalization::CultureInfo::InvariantCulture);

						// Ensure that the values are updated dynamically
						this->taghandler->isLedDemo = true;

						this->checkTag = true;
					}
					else
					{
						this->countCheck = checkConnection();
						if (this->countCheck >= 4)
						{
							this->taghandler->tagOut = true;
							this->authenticated = false;
							this->checkTag = false;
							this->firstTime = true;
							firstTimeFalse = true;
							setLockIcon(1);
						}
						else
						{
							this->checkTag = false;
							this->taghandler->endWait = true;
						}
						this->label_LedDemoT_BoardStatus->Location = System::Drawing::Point(this->label_LedDemoT_BoardStatus->Location.X, 24);
						this->label_LedDemoT_BoardStatus->Text = "Transfer: No\nTap a tag to read configuration";
					}
				}
				else if (sramProtected == false)
				{
					Sleep(10);
					lReturn = board_demo->Run(this->ledColor, enTemp, enLCD, dispNDEF, &leftButton, &middleButton, &rightButton, &tempC, &tempF, &voltage, &version);
					Sleep(10);
					if (lReturn == SCARD_S_SUCCESS)
					{
						// Show what buttons are pressed
						if (leftButton != 0)
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[2];
						if (middleButton != 0)
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[3];
						if (rightButton != 0)
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[7];
						if ((rightButton != 0) && (middleButton != 0))
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[4];
						if ((rightButton != 0) && (leftButton != 0))
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[6];
						if ((leftButton != 0) && (middleButton != 0))
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[1];
						if ((rightButton != 0) && (middleButton != 0))
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[4];
						if ((rightButton != 0) && (middleButton != 0) && (leftButton != 0))
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[0];
						if ((rightButton == 0) && (middleButton == 0) && (leftButton == 0))
							this->pic_LedDemoT_NXP->BackgroundImage = this->imageList_NXPlogo->Images[5];

						// Show the temperature and voltage
						this->label_LedDemoT_BoardStatus->Location = System::Drawing::Point(this->label_LedDemoT_BoardStatus->Location.X, 18);

						//Show arrow moving when the tag is connected
						if (transferDir != 1)
						{
							this->label_LedDemoT_BoardStatus->Text = "Transfer: Device --> Tag \nTemperature: ";
							transferDir = 1;
						}
						else
						{
							this->label_LedDemoT_BoardStatus->Text = "Transfer: Device <-- Tag \nTemperature: ";
							transferDir = 0;
						}
						if (enTemp)
							this->label_LedDemoT_BoardStatus->Text += tempC.ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " ºC / " +
							tempF.ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " ºF";
						else
							this->label_LedDemoT_BoardStatus->Text += "Not available";
						this->label_LedDemoT_BoardStatus->Text += "\nVoltage: " + voltage.ToString("0.0", System::Globalization::CultureInfo::InvariantCulture) + " V";

						// Update the version
						this->FWVersion = version.ToString("0.0", System::Globalization::CultureInfo::InvariantCulture);

						// Ensure that the values are updated dynamically
						this->taghandler->isLedDemo = true;

						this->checkTag = true;
					}
					else
					{
						this->countCheck = checkConnection();
						if (this->countCheck >= 4)
						{
							this->taghandler->tagOut = true;
							this->authenticated = false;
							this->checkTag = false;
							this->firstTime = true;
							firstTimeFalse = true;
							setLockIcon(1);
						}
						else
						{
							this->checkTag = false;
							this->taghandler->endWait = true;
						}
						this->label_LedDemoT_BoardStatus->Location = System::Drawing::Point(this->label_LedDemoT_BoardStatus->Location.X, 24);
						this->label_LedDemoT_BoardStatus->Text = "Transfer: No\nTap a tag to read configuration";
					}
				}
				else
				{
					this->label_LedDemoT_BoardStatus->Text = L"Transfer: No\r\nAuthentication is needed";
					this->taghandler->endWait = true;
				}
			}
		}

		// This function is executed when the current tab is the NDEF demo and the tag is tapped against the reader
		// It is also executed when the user clicks on the Read or Write buttons in order to read or write an NDEF message into the tag
		void OnNdefDemo()
		{
			LONG lReturn;
			int i = 0;

			if (this->versionBox1->Visible)
			{
				// Read the board version
				this->versionBox1->setLabel("Reading the board version...");
				Versions_t versions;
				lReturn = board_demo->ReadVersions(&versions);
				if (lReturn == SCARD_S_SUCCESS)
				{
					this->versionBox1->updateBox(versions, this->AppVersion, this->IdentivVer);
					this->versionBox1->setLabel("");
				}
				else
					this->versionBox1->setLabel("Error while reading the board version");
			}
			else if (this->tapTagBoxAbout->Visible)
			{
				if (retu == SCARD_S_SUCCESS)
				{
					char  IdentivReaderFWversion[3];
					my_api->readIdentivFWversion(IdentivReaderFWversion);

					String^ strNew = gcnew String(IdentivReaderFWversion);

					this->IdentivVer = strNew;

					// Read the board version
					this->tapTagBoxAbout->setLabel("Reading the board version...");
					Versions_t versions;
					lReturn = board_demo->ReadVersions(&versions);
					if (lReturn == SCARD_S_SUCCESS)
					{
						this->versionBox1->updateBox(versions, this->AppVersion, this->IdentivVer);
						this->versionBox1->setLabel("");
						this->versionBox1->Show();
						this->tapTagBoxAbout->Hide();
					}
					else
						this->tapTagBoxAbout->setLabel("Error while reading the board version");
				}
			}
			else if (this->BoxFlashing->Visible)
			{
				checking = "";
				if (this->tapTagBoxFlashing->textBox->Text == checking)
				{
					//MessageBox::Show("Please select a valid file");
					this->BoxFlashing->Hide();
					this->tapTagBoxFlashing->Show();
				}
				else
				{
					this->BoxFlashing->setLabel("Flashing memory content...");

					if (this->tagBlocked && !this->authenticated)
					{
						authenticate();
					}

					if (this->SelectFlashing->selBlink == true)
					{
						this->BoxFlashing->textBoxFile->Text = "NTAG_I2C_Explorer_Blink.bin";
					}
					else if (this->SelectFlashing->selDemo == true)
					{
						this->BoxFlashing->textBoxFile->Text = "NTAG_I2C_Explorer_Demo.bin";
					}
					else
					{
						String^ fileName = this->openFileDialog1->FileName;
						int ind = this->openFileDialog1->FileName->LastIndexOf('\\');
						String^ file = this->openFileDialog1->FileName->Substring(ind + 1);

						this->BoxFlashing->textBoxFile->Text = file;
					}
					Sleep(1000);
					this->BoxFlashing->setLabel("");
					this->BoxFlashing->textBoxFlashPerformance->Text = "";

					const int maxFWLength = 16384;	// The maximum firmware that can be flashed is 16384 (4 sectors of 4096 bytes each)
					System::IO::Stream^ newFWStream = nullptr;
					System::IO::Stream^ DemoStream = nullptr;

					if (this->SelectFlashing->selBlink == true)
					{
						this->SelectFlashing->selBlink = false;
						String^ path = ".\\rsc\\NTAG_I2C_Explorer_Blink.bin";
						FileStream^ fs = File::OpenRead(path);

						DemoStream = fs;

						int newFWLength = (int)DemoStream->Length;
						int currentLength = 0;
						this->BoxFlashing->progressBarFlash->Step = 64;
						this->BoxFlashing->progressBarFlash->Value = 0;
						if (newFWLength > 12288)
							this->BoxFlashing->progressBarFlash->Maximum = maxFWLength;
						else if (newFWLength > 8192)
							this->BoxFlashing->progressBarFlash->Maximum = 12288;
						else if (newFWLength > 4096)
							this->BoxFlashing->progressBarFlash->Maximum = 8192;
						else
							this->BoxFlashing->progressBarFlash->Maximum = 4096;

						// Check that the firmware is not too big
						if (newFWLength <= maxFWLength)
						{
							DWORD flashBytes;
							float flashTime;

							// Convert the Stream variable to a BYTE array
							BYTE newFW[maxFWLength];
							array<Byte>^ newFWArray = gcnew array<Byte>(newFWLength);
							int n = DemoStream->Read(newFWArray, 0, newFWLength);
							DemoStream->Close();
							for (int i = 0; i < newFWLength; i++)
							{
								newFW[i] = (BYTE)newFWArray[i];
							}

							lReturn = FlashMemory(newFW, newFWLength, &flashBytes, &flashTime, this->BoxFlashing->progressBarFlash);

							if (lReturn == SCARD_S_SUCCESS)
							{
								this->BoxFlashing->setLabel("Memory flash completed successfully");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->BoxFlashing->textBoxFlashPerformance->Text = " Speed(" + flashBytes + " B / " + flashTime + " ms): " +
									(1000.0 * flashBytes / flashTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
							}
							else
							{
								this->BoxFlashing->setLabel("Error during memory flash");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
							}
						}
						else
							this->BoxFlashing->setLabel("The file is too big. Maximum size: 16384 bytes (16 kB)");
					}

					else if (this->SelectFlashing->selDemo == true)
					{
						this->SelectFlashing->selDemo = false;
						String^ path = ".\\rsc\\NTAG_I2C_Explorer_Demo.bin";
						FileStream^ fs = File::OpenRead(path);

						DemoStream = fs;

						int newFWLength = (int)DemoStream->Length;
						int currentLength = 0;
						this->BoxFlashing->progressBarFlash->Step = 64;
						this->BoxFlashing->progressBarFlash->Value = 0;
						if (newFWLength > 12288)
							this->BoxFlashing->progressBarFlash->Maximum = maxFWLength;
						else if (newFWLength > 8192)
							this->BoxFlashing->progressBarFlash->Maximum = 12288;
						else if (newFWLength > 4096)
							this->BoxFlashing->progressBarFlash->Maximum = 8192;
						else
							this->BoxFlashing->progressBarFlash->Maximum = 4096;

						// Check that the firmware is not too big
						if (newFWLength <= maxFWLength)
						{
							DWORD flashBytes;
							float flashTime;

							// Convert the Stream variable to a BYTE array
							BYTE newFW[maxFWLength];
							array<Byte>^ newFWArray = gcnew array<Byte>(newFWLength);
							int n = DemoStream->Read(newFWArray, 0, newFWLength);
							DemoStream->Close();
							for (int i = 0; i < newFWLength; i++)
							{
								newFW[i] = (BYTE)newFWArray[i];
							}

							lReturn = FlashMemory(newFW, newFWLength, &flashBytes, &flashTime, this->BoxFlashing->progressBarFlash);

							if (lReturn == SCARD_S_SUCCESS)
							{
								this->BoxFlashing->setLabel("Memory flash completed successfully");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->BoxFlashing->textBoxFlashPerformance->Text = " Speed(" + flashBytes + " B / " + flashTime + " ms): " +
									(1000.0 * flashBytes / flashTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
							}
							else
							{
								this->BoxFlashing->setLabel("Error during memory flash");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
							}
						}
						else
							this->BoxFlashing->setLabel("The file is too big. Maximum size: 16384 bytes (16 kB)");
					}
					// Read the file in a Stream variable
					else if ((newFWStream = this->openFileDialog1->OpenFile()) != nullptr)
					{
						int newFWLength = (int)newFWStream->Length;
						int currentLength = 0;
						// Check that the firmware is not too big
						if (newFWLength <= maxFWLength)
						{
							this->BoxFlashing->progressBarFlash->Step = 64;
							this->BoxFlashing->progressBarFlash->Value = 0;
							if (newFWLength > 12288)
								this->BoxFlashing->progressBarFlash->Maximum = maxFWLength;
							else if (newFWLength > 8192)
								this->BoxFlashing->progressBarFlash->Maximum = 12288;
							else if (newFWLength > 4096)
								this->BoxFlashing->progressBarFlash->Maximum = 8192;
							else
								this->BoxFlashing->progressBarFlash->Maximum = 4096;

							DWORD flashBytes;
							float flashTime;

							// Convert the Stream variable to a BYTE array
							BYTE newFW[maxFWLength];
							array<Byte>^ newFWArray = gcnew array<Byte>(newFWLength);
							int n = newFWStream->Read(newFWArray, 0, newFWLength);
							newFWStream->Close();
							for (int i = 0; i < newFWLength; i++)
							{
								newFW[i] = (BYTE)newFWArray[i];
							}

							lReturn = FlashMemory(newFW, newFWLength, &flashBytes, &flashTime, this->BoxFlashing->progressBarFlash);

							if (lReturn == SCARD_S_SUCCESS)
							{
								this->BoxFlashing->setLabel("Memory flash completed successfully");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								if (this->BoxFlashing->progressBarFlash->Value == this->BoxFlashing->progressBarFlash->Maximum)
								{
									this->BoxFlashing->progressBarFlash->PerformStep();
									this->BoxFlashing->progressBarFlash->Value = 0;
								}
								this->BoxFlashing->textBoxFlashPerformance->Text = " Speed(" + flashBytes + " B / " + flashTime + " ms): " +
									(1000.0 * flashBytes / flashTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
							}
							else
							{
								this->BoxFlashing->setLabel("Error during memory flash");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								Sleep(1000);
								this->BoxFlashing->setLabel("");
							}
						}
						else
						{
							this->BoxFlashing->setLabel("The file is too big. Maximum size: 16384 bytes (16 kB)");
							Sleep(1000);
							this->BoxFlashing->setLabel("");
						}
					}
					else
					{
						this->BoxFlashing->setLabel("Could not open the file");
						Sleep(1000);
						this->BoxFlashing->setLabel("");
					}
				}
			}
			else if (this->tapTagBoxFlashing->Visible)
			{
				checking = "";
				if (this->tapTagBoxFlashing->textBox->Text != checking)
				{
					String^ file = nullptr;
					if (this->tapTagBoxFlashing->swi == true) //From storage
					{
						String^ fileName = this->openFileDialog1->FileName;
						int ind = this->openFileDialog1->FileName->LastIndexOf('\\');
						file = this->openFileDialog1->FileName->Substring(ind + 1);
						this->tapTagBoxFlashing->swi = false;
						this->BoxFlashing->textBoxFile->Text = file;
						this->BoxFlashing->Refresh();
					}
					else if (this->tapTagBoxFlashing->dwi == true)
					{
						if (this->SelectFlashing->selDemo == true) //Demo App selected
						{
							file = L"NTAG_I2C_Explorer_Demo.bin";
						}
						else if (this->SelectFlashing->selBlink == true) //LED Blinker selected
						{
							file = L"NTAG_I2C_Explorer_Blink.bin";
						}
						this->tapTagBoxFlashing->dwi = false;
						this->BoxFlashing->textBoxFile->Text = file;
						checking = "";
						this->tapTagBoxFlashing->textBox->Text = checking;
						this->BoxFlashing->Refresh();
					}

					this->BoxFlashing->setLabel("");
					this->BoxFlashing->Show();
					this->BoxFlashing->textBoxFlashPerformance->Text = "";

					this->tapTagBoxFlashing->Hide();
					taghandler->endWait = true;
				}
				else
					this->tapTagBoxFlashing->setLabel("Error while flashing the memory");
			}

			else if (this->gButton_NDEFT_ReadNDEF->isActive == true)
			{
				if (this->cBox_NDEFT_Loop->Checked)
				{
						// Read NDEF Demo
						this->label_NDEFT_Content->Text = "Reading NDEF message...            ";
						this->label_NDEFT_Content->Update();
						int NdefType, payloadSize, AARSize;
						BYTE payload[MAX_MEM_SIZE];
						BOOL AARPresent = FALSE;
						BYTE AAR[MAX_MEM_SIZE];
						DWORD readBytes;
						Sleep(10);
						float readTime;

						lReturn = my_api->ReadNdef(&NdefType, payload, &payloadSize, &AARPresent, AAR, &AARSize, &readBytes, &readTime);
						//Sleep(100);
						if (lReturn == SCARD_S_SUCCESS)
						{
							int end;
							readTime += 1;
							this->textBoxNDEFPerformance->Text = " Speed(" + readBytes + " B / " + readTime + " ms): " +
								(1000.0 * readBytes / readTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
							switch (NdefType)
							{
							case TYPE_NDEF_TEXT:
								this->textBoxNDEFcontent->Text = "#1 Text record:\r\n";
								// Convert from ASCII to Unicode
								for (i = 0; i < payloadSize; i++)
									this->textBoxNDEFcontent->Text += (wchar_t)payload[i];
								this->label_NDEFT_MsgType->Text = "NDEF Msg Type: Text";
								break;
							case TYPE_NDEF_URI:
								this->textBoxNDEFcontent->Text = "#1 URI record:\r\n";
								// Convert from ASCII to Unicode
								for (i = 0; i < payloadSize; i++)
									this->textBoxNDEFcontent->Text += (wchar_t)payload[i];
								this->label_NDEFT_MsgType->Text = "NDEF Msg Type: URI";
								break;
							case TYPE_NDEF_BTPAIR:
								this->textBoxNDEFcontent->Text = "#1 Handover Select record\r\n\r\n#2 MIME record:\r\n";
								// The string I receive is: MIME type length + MIME type + MAC address length + MAC address + Name length + Name + Class length + Class + '\0'
								// Convert from ASCII to Unicode
								// MIME type
								for (i = 1, end = 1 + payload[0]; i < end; i++)
									this->textBoxNDEFcontent->Text += (wchar_t)payload[i];

								this->label_NDEFT_MsgType->Text = "NDEF Msg Type: Handover Select";
								break;
							case TYPE_NDEF_SP:
								this->textBoxNDEFcontent->Text = "#1 Smart Poster record:\r\n";
								// The string I receive is: Title Length + Title + Link Length + Link
								// Convert from ASCII to Unicode
								this->textBoxNDEFcontent->Text += "#1.1 Text record:\r\n";
								end = payload[0] + 1;
								for (i = 1; i < end; i++)
									this->textBoxNDEFcontent->Text += (wchar_t)payload[i];
								this->textBoxNDEFcontent->Text += "\r\n#1.2 URI record:\r\n";
								end += payload[i] + 1;
								for (i++; i < end; i++)
									this->textBoxNDEFcontent->Text += (wchar_t)payload[i];
								this->label_NDEFT_MsgType->Text = "NDEF Msg Type: Smart Poster";
								break;
							default:
								this->label_NDEFT_MsgType->Text = "NDEF Msg Type: unknown";
								break;
							}
							// Check if the NDEF message contains an AAR record
							if (AARPresent)
							{
								if (NdefType == TYPE_NDEF_BTPAIR)
									this->textBoxNDEFcontent->Text += "\r\n\r\n#3 Android Application record:\r\n";
								else
									this->textBoxNDEFcontent->Text += "\r\n\r\n#2 Android Application record:\r\n";
								// Convert from ASCII to Unicode
								for (i = 0; i < AARSize; i++)
									this->textBoxNDEFcontent->Text += (wchar_t)AAR[i];
							}
							taghandler->endWait = true;
						}
						else if (lReturn == SCARD_E_INVALID_TARGET)
						{
							this->label_NDEFT_Content->Text = "The tag is not NDEF formatted";
							this->textBoxNDEFcontent->Text = "";
							taghandler->endWait = true;
						}
						else
						{
							this->label_NDEFT_Content->Text = "Error while reading the NDEF message";
							this->textBoxNDEFcontent->Text = "";
							taghandler->endWait = true;
						}
				}
				else
				{
					if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
					{
						if (checkStatus())
						{
							this->checkTag = true;
							showWindowAuth();
						}
					}
					if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
					{
						if (firstNDEF && (retu == SCARD_S_SUCCESS))
						{
							firstNDEF = false;
						 
							// Read NDEF Demo
							this->label_NDEFT_Content->Text = "Reading NDEF message...            ";
							this->label_NDEFT_Content->Update();
							int NdefType, payloadSize, AARSize;
							BYTE payload[MAX_MEM_SIZE];
							BOOL AARPresent = FALSE;
							BYTE AAR[MAX_MEM_SIZE];
							DWORD readBytes;
							float readTime;
							lReturn = my_api->ReadNdef(&NdefType, payload, &payloadSize, &AARPresent, AAR, &AARSize, &readBytes, &readTime);
							//Sleep(1000);
							if (lReturn == SCARD_S_SUCCESS)
							{
								readTime += 1;
								int end;
								this->label_NDEFT_Content->Text = "NDEF message read successfully";
								this->textBoxNDEFPerformance->Text = " Speed(" + readBytes + " B / " + readTime + " ms): " +
									(1000.0 * readBytes / readTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
								switch (NdefType)
								{
								case TYPE_NDEF_TEXT:
									this->textBoxNDEFcontent->Text = "#1 Text record:\r\n";
									// Convert from ASCII to Unicode
									for (i = 0; i < payloadSize; i++)
										this->textBoxNDEFcontent->Text += (wchar_t)payload[i];
									this->label_NDEFT_MsgType->Text = "NDEF Msg Type: Text";
									break;
								case TYPE_NDEF_URI:
									this->textBoxNDEFcontent->Text = "#1 URI record:\r\n";
									// Convert from ASCII to Unicode
									for (i = 0; i < payloadSize; i++)
										this->textBoxNDEFcontent->Text += (wchar_t)payload[i];
									this->label_NDEFT_MsgType->Text = "NDEF Msg Type: URI";
									break;
								case TYPE_NDEF_BTPAIR:
									this->textBoxNDEFcontent->Text = "#1 Handover Select record\r\n\r\n#2 MIME record:\r\n";
									// The string I receive is: MIME type length + MIME type + MAC address length + MAC address + Name length + Name + Class length + Class + '\0'
									// Convert from ASCII to Unicode
									// MIME type
									for (i = 1, end = 1 + payload[0]; i < end; i++)
										this->textBoxNDEFcontent->Text += (wchar_t)payload[i];

									this->label_NDEFT_MsgType->Text = "NDEF Msg Type: Handover Select";
									break;
								case TYPE_NDEF_SP:
									this->textBoxNDEFcontent->Text = "#1 Smart Poster record:\r\n";
									// The string I receive is: Title Length + Title + Link Length + Link
									// Convert from ASCII to Unicode
									this->textBoxNDEFcontent->Text += "#1.1 Text record:\r\n";
									end = payload[0] + 1;
									for (i = 1; i < end; i++)
										this->textBoxNDEFcontent->Text += (wchar_t)payload[i];
									this->textBoxNDEFcontent->Text += "\r\n#1.2 URI record:\r\n";
									end += payload[i] + 1;
									for (i++; i < end; i++)
										this->textBoxNDEFcontent->Text += (wchar_t)payload[i];
									this->label_NDEFT_MsgType->Text = "NDEF Msg Type: Smart Poster";
									break;
								default:
									this->label_NDEFT_MsgType->Text = "NDEF Msg Type: unknown";
									break;
								}
								// Check if the NDEF message contains an AAR record
								if (AARPresent)
								{
									if (NdefType == TYPE_NDEF_BTPAIR)
										this->textBoxNDEFcontent->Text += "\r\n\r\n#3 Android Application record:\r\n";
									else
										this->textBoxNDEFcontent->Text += "\r\n\r\n#2 Android Application record:\r\n";
									// Convert from ASCII to Unicode
									for (i = 0; i < AARSize; i++)
										this->textBoxNDEFcontent->Text += (wchar_t)AAR[i];
								}
							}
							else if (lReturn == SCARD_E_INVALID_TARGET)
							{
								this->label_NDEFT_Content->Text = "The tag is not NDEF formatted";
								this->textBoxNDEFcontent->Text = "";
							}
							else
							{
								this->textBoxNDEFcontent->Text = "";
							}
						}
						else
						{
							Sleep(1000);
							int countCheck = checkConnection();
							if (countCheck >= 4)
							{
								firstNDEF = true;
								firstTimeFalse = true;
								this->checkTag = false;
								this->firstTime = true;
								this->authenticated = false;
								this->label_NDEFT_Content->Text = "Tap tag to read NDEF content";
							}
							/*else
							{
								this->checkTag = false;
							}*/
						}

						this->taghandler->endWait = true;
					}
					else
					{
						//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
						this->checkTag = false;
						this->taghandler->endWait = true;
					}
				}
			}
			else
			{
				if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
				{
					if (checkStatus())
					{
						showWindowAuth();
						this->checkTag = true;
					}
				}

				if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
				{
						if (firstNDEF && (retu == SCARD_S_SUCCESS))
						{
							firstNDEF = false;

							// Write NDEF Demo
							this->writeNDEFBox1->label1->Update();
							BYTE payload[MAX_MEM_SIZE];
							int payloadSize;
							DWORD writeBytes;
							float writeTime;
							BOOL addAAR = this->writeNDEFBox1->checkBox1->Checked;
							array<Char>^ unicode_array;
							bool ok_length;
							int i, j, i2;
							if (this->buttonSmartPosterNDEF == true)
							{
								BOOL addAAR = 1;
								this->writeNDEFBox1->label1->Text = "Tap tag to write NDEF message";
								this->buttonSmartPosterNDEF = false;
								this->writeNDEFBox1->radioButton_NDEFT_SP->Checked = true;
								this->writeNDEFBox1->textBox6->Text = L"NTAG I2C EXPLORER";
								this->writeNDEFBox1->textBox5->Text = L"http://www.nxp.com/demoboard/OM5569";
								this->writeNDEFBox1->checkBox1->Checked = true;

								// The string I send is: Title Length + Title + Link Length + Link
								// Convert from Unicode to ASCII
								payload[0] = this->writeNDEFBox1->textBox6->Text->Length;
								unicode_array = this->writeNDEFBox1->textBox6->Text->ToCharArray();
								for (i = 0; i < payload[0]; i++)
									payload[i + 1] = (BYTE)unicode_array[i];
								payload[payload[0] + 1] = this->writeNDEFBox1->textBox5->Text->Length;
								unicode_array = this->writeNDEFBox1->textBox5->Text->ToCharArray();
								for (i = 0; i < payload[payload[0] + 1]; i++)
									payload[i + payload[0] + 2] = (BYTE)unicode_array[i];
								payload[i + payload[0] + 2] = '\0';
								payloadSize = i + payload[0] + 2;
								lReturn = my_api->WriteNdef(TYPE_NDEF_SP, payload, payloadSize, addAAR, &writeBytes, &writeTime);
								Sleep(1000);
								if (lReturn == SCARD_S_SUCCESS)
								{
									this->writeNDEFBox1->label1->Text = "Smart Poster NDEF written succesfully";
									this->textBoxNDEFPerformance->Text = " NDEF message write\r\n Speed(" + writeBytes + " B / " + writeTime + " ms): " +
										(1000.0 * writeBytes / writeTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
								}
							}
							else
							{
								this->writeNDEFBox1->label1->Text = "Tap tag to write NDEF message";
								if (this->buttonWriteNDEF == true)
								{
									switch (this->writeNDEFBox1->selOption)
									{
									case TYPE_NDEF_TEXT:
										// Convert from Unicode to ASCII
										unicode_array = this->writeNDEFBox1->textBox1->Text->ToCharArray();
										payloadSize = this->writeNDEFBox1->textBox1->Text->Length;
										if (payloadSize != 0)
										{
											for (i = 0; i < payloadSize; i++)
												payload[i] = (BYTE)unicode_array[i];
											lReturn = my_api->WriteNdef(TYPE_NDEF_TEXT, payload, payloadSize, addAAR, &writeBytes, &writeTime);
											Sleep(100);
											if (lReturn == SCARD_S_SUCCESS)
											{
												this->writeNDEFBox1->label1->Text = "Text NDEF written succesfully";
												this->textBoxNDEFPerformance->Text = " NDEF message write\r\n Speed(" + writeBytes + " B / " + writeTime + " ms): " +
													(1000.0 * writeBytes / writeTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
											}
											else
											{
												this->label_NDEFT_Content->Text = "Error while writing the NDEF message";
												this->textBoxNDEFcontent->Text = "";
											}
										}
										else
										{
											MessageBox::Show("Non-valid format");
										}
										break;
									case TYPE_NDEF_URI:
										// Convert from Unicode to ASCII
										unicode_array = this->writeNDEFBox1->textBox1->Text->ToCharArray();
										payloadSize = this->writeNDEFBox1->textBox1->Text->Length;

										for (i = 0; i < payloadSize; i++)
										{
											payload[i] = (BYTE)unicode_array[i];
										}
										payload[i] = '\0';
										if (payload[11] != '\0')
										{
											lReturn = my_api->WriteNdef(TYPE_NDEF_URI, payload, payloadSize, addAAR, &writeBytes, &writeTime);
											Sleep(100);
											if (lReturn == SCARD_S_SUCCESS)
											{
												this->writeNDEFBox1->label1->Text = "URI NDEF written succesfully";
												this->textBoxNDEFPerformance->Text = " NDEF message write\r\n Speed(" + writeBytes + " B / " + writeTime + " ms): " +
													(1000.0 * writeBytes / writeTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
											}
											else
											{
												this->label_NDEFT_Content->Text = "Error while writing the NDEF message";
												this->textBoxNDEFcontent->Text = "";
											}
										}
										else
										{
											MessageBox::Show("Non-valid format");
										}
										break;
									case TYPE_NDEF_BTPAIR:
										// The string I send is: MAC address + Name length + Name + Class length + Class + '\0'
										// Convert from Unicode to ASCII
										i = 0;
										ok_length = true;
										// MAC address
										unicode_array = this->writeNDEFBox1->textBox4->Text->ToCharArray();
										payloadSize = this->writeNDEFBox1->textBox4->Text->Length;
										for (j = 0; j < payloadSize; i++, j++)
										{
											// Copy numbers and letters from 'A' to 'F' (as values from 0x30 to 0x3F), and ignore the rest
											if (unicode_array[j] >= '0' && unicode_array[j] <= '9')
												payload[i] = (BYTE)unicode_array[j];
											else if (unicode_array[j] >= 'A' && unicode_array[j] <= 'F')
												payload[i] = (BYTE)unicode_array[j] - 'A' + '0' + 0x0A;
											else if (unicode_array[j] >= 'a' && unicode_array[j] <= 'f')
												payload[i] = (BYTE)unicode_array[j] - 'a' + '0' + 0x0A;
											else
												i--;
										}
										// Check if the MAC address has 12 characters
										if (i == 12)
										{
											// Device name
											unicode_array = this->writeNDEFBox1->textBox3->Text->ToCharArray();
											payloadSize = this->writeNDEFBox1->textBox3->Text->Length;
											if (payloadSize == 0) ok_length = false;
											payload[i] = payloadSize;
											i++;
											for (j = 0; j < payloadSize; i++, j++)
											{
												payload[i] = (BYTE)unicode_array[j];
											}
											// Device class
											unicode_array = this->writeNDEFBox1->textBox2->Text->ToCharArray();
											payloadSize = this->writeNDEFBox1->textBox2->Text->Length;
											if (payloadSize == 0) ok_length = false;
											i2 = i;
											i++;
											for (j = 0; j < payloadSize; i++, j++)
											{
												// Copy numbers and letters from 'A' to 'F' (as values from 0x40 to 0x4F, to avoid the ';' = 0x3B), and ignore the rest
												if (unicode_array[j] >= '0' && unicode_array[j] <= '9')
													payload[i] = (BYTE)unicode_array[j];
												else if (unicode_array[j] >= 'A' && unicode_array[j] <= 'F')
													payload[i] = (BYTE)unicode_array[j] - 'A' + '0' + 0x0A;
												else if (unicode_array[j] >= 'a' && unicode_array[j] <= 'f')
													payload[i] = (BYTE)unicode_array[j] - 'a' + '0' + 0x0A;
												else
													i--;
											}
											payload[i2] = i - i2 - 1;
											payload[i] = '\0';
											payloadSize = i;
											if (ok_length)
											{
												lReturn = my_api->WriteNdef(TYPE_NDEF_BTPAIR, payload, payloadSize, addAAR, &writeBytes, &writeTime);
												Sleep(100);
												if (lReturn == SCARD_S_SUCCESS)
												{
													this->writeNDEFBox1->label1->Text = "BT pairing NDEF written succesfully";
													this->textBoxNDEFPerformance->Text = " NDEF message write\r\n Speed(" + writeBytes + " B / " + writeTime + " ms): " +
														(1000.0 * writeBytes / writeTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
												}
												else
												{
													this->label_NDEFT_Content->Text = "Error while writing the NDEF message";
													this->textBoxNDEFcontent->Text = "";
												}
											}
											else
											{
												MessageBox::Show("Non-valid format");
											}
										}
										else
											this->writeNDEFBox1->label1->Text = "The MAC address must be 6 bytes";
										break;
									case TYPE_NDEF_SP:
										ok_length = true;

										// The string I send is: Title Length + Title + Link Length + Link
										// Convert from Unicode to ASCII
										payload[0] = this->writeNDEFBox1->textBox6->Text->Length;
										if (payload[0] == 0) ok_length = false;

										unicode_array = this->writeNDEFBox1->textBox6->Text->ToCharArray();
										for (i = 0; i < payload[0]; i++)
											payload[i + 1] = (BYTE)unicode_array[i];

										payload[payload[0] + 1] = this->writeNDEFBox1->textBox5->Text->Length;
										unicode_array = this->writeNDEFBox1->textBox5->Text->ToCharArray();

										for (i = 0; i < payload[payload[0] + 1]; i++)
											payload[i + payload[0] + 2] = (BYTE)unicode_array[i];
										payload[i + payload[0] + 2] = '\0';
										payloadSize = i + payload[0] + 2;
										if (ok_length)
										{
											lReturn = my_api->WriteNdef(TYPE_NDEF_SP, payload, payloadSize, addAAR, &writeBytes, &writeTime);
											Sleep(100);
											if (lReturn == SCARD_S_SUCCESS)
											{
												this->writeNDEFBox1->label1->Text = "Smart Poster NDEF written succesfully";
												this->textBoxNDEFPerformance->Text = " NDEF message write\r\n Speed(" + writeBytes + " B / " + writeTime + " ms): " +
													(1000.0 * writeBytes / writeTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
											}
											else
											{
												this->label_NDEFT_Content->Text = "Error while writing the NDEF message";
												this->textBoxNDEFcontent->Text = "";
											}
										}
										else
										{
											MessageBox::Show("Non-valid format");
										}
										break;
									default:
										MessageBox::Show("Non-valid radio button selected");
										break;
									}

								}
							}
						}
						else
						{
							Sleep(1000);
							int countCheck = checkConnection();
							Sleep(1000);
							if (countCheck >= 4)
							{
								firstNDEF = true;
								firstTimeFalse = true;
								this->firstTime = true;
								this->checkTag = false;
								this->authenticated = false;
								this->writeNDEFBox1->label1->Text = "Tap tag to write NDEF message";
							}
							/*else
							{
								this->checkTag = false;
								this->taghandler->endWait = true;
							}*/
						}
						this->taghandler->endWait = true;
					}
					else
					{
						//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
						this->checkTag = false;
						this->taghandler->endWait = true;
					}
			}
		}

		// This function is executed when the current tab is the Speed Test demo and the tag is tapped against the reader
		// It is also executed when the user clicks on the Start button
		void OnSpeedTestDemo()
		{
			LONG lReturn;
			this->cBox_NDEFT_Loop->Checked = false;

			if (this->versionBox1->Visible)
			{
				// Read the board version
				this->versionBox1->setLabel("Reading the board version...");
				Versions_t versions;
				lReturn = board_demo->ReadVersions(&versions);
				if (lReturn == SCARD_S_SUCCESS)
				{
					this->versionBox1->updateBox(versions, this->AppVersion, this->IdentivVer);
					this->versionBox1->setLabel("");
				}
				else
					this->versionBox1->setLabel("Error while reading the board version");
			}
			else if (this->tapTagBoxAbout->Visible)
			{
				if (retu == SCARD_S_SUCCESS)
				{
					char  IdentivReaderFWversion[3];
					my_api->readIdentivFWversion(IdentivReaderFWversion);

					String^ strNew = gcnew String(IdentivReaderFWversion);

					this->IdentivVer = strNew;

					// Read the board version
					this->tapTagBoxAbout->setLabel("Reading the board version...");
					Versions_t versions;
					lReturn = board_demo->ReadVersions(&versions);
					if (lReturn == SCARD_S_SUCCESS)
					{
						this->versionBox1->updateBox(versions, this->AppVersion, this->IdentivVer);
						this->versionBox1->setLabel("");
						this->versionBox1->Show();
						this->tapTagBoxAbout->Hide();
					}
					else
						this->tapTagBoxAbout->setLabel("Error while reading the board version");
				}
			}
			else if (this->BoxFlashing->Visible)
			{
				checking = "";
				if (this->tapTagBoxFlashing->textBox->Text == checking)
				{
					//MessageBox::Show("Please select a valid file");
					this->BoxFlashing->Hide();
					this->tapTagBoxFlashing->Show();
				}
				else
				{
					this->BoxFlashing->setLabel("Flashing memory content...");

					if (this->tagBlocked && !this->authenticated)
					{
						authenticate();
					}

					if (this->SelectFlashing->selBlink == true)
					{
						this->BoxFlashing->textBoxFile->Text = "NTAG_I2C_Explorer_Blink.bin";
					}
					else if (this->SelectFlashing->selDemo == true)
					{
						this->BoxFlashing->textBoxFile->Text = "NTAG_I2C_Explorer_Demo.bin";
					}
					else
					{
						String^ fileName = this->openFileDialog1->FileName;
						int ind = this->openFileDialog1->FileName->LastIndexOf('\\');
						String^ file = this->openFileDialog1->FileName->Substring(ind + 1);

						this->BoxFlashing->textBoxFile->Text = file;
					}
					Sleep(1000);
					this->BoxFlashing->setLabel("");
					this->BoxFlashing->textBoxFlashPerformance->Text = "";

					const int maxFWLength = 16384;	// The maximum firmware that can be flashed is 16384 (4 sectors of 4096 bytes each)
					System::IO::Stream^ newFWStream = nullptr;
					System::IO::Stream^ DemoStream = nullptr;

					if (this->SelectFlashing->selBlink == true)
					{
						this->SelectFlashing->selBlink = false;
						String^ path = ".\\rsc\\NTAG_I2C_Explorer_Blink.bin";
						FileStream^ fs = File::OpenRead(path);

						DemoStream = fs;

						int newFWLength = (int)DemoStream->Length;
						int currentLength = 0;
						this->BoxFlashing->progressBarFlash->Step = 64;
						this->BoxFlashing->progressBarFlash->Value = 0;
						if (newFWLength > 12288)
							this->BoxFlashing->progressBarFlash->Maximum = maxFWLength;
						else if (newFWLength > 8192)
							this->BoxFlashing->progressBarFlash->Maximum = 12288;
						else if (newFWLength > 4096)
							this->BoxFlashing->progressBarFlash->Maximum = 8192;
						else
							this->BoxFlashing->progressBarFlash->Maximum = 4096;

						// Check that the firmware is not too big
						if (newFWLength <= maxFWLength)
						{
							DWORD flashBytes;
							float flashTime;

							// Convert the Stream variable to a BYTE array
							BYTE newFW[maxFWLength];
							array<Byte>^ newFWArray = gcnew array<Byte>(newFWLength);
							int n = DemoStream->Read(newFWArray, 0, newFWLength);
							DemoStream->Close();
							for (int i = 0; i < newFWLength; i++)
							{
								newFW[i] = (BYTE)newFWArray[i];
							}

							lReturn = FlashMemory(newFW, newFWLength, &flashBytes, &flashTime, this->BoxFlashing->progressBarFlash);

							if (lReturn == SCARD_S_SUCCESS)
							{
								this->BoxFlashing->setLabel("Memory flash completed successfully");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->tapTagBoxFlashing->Refresh();
								this->BoxFlashing->textBoxFlashPerformance->Text = " Speed(" + flashBytes + " B / " + flashTime + " ms): " +
									(1000.0 * flashBytes / flashTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
							}
							else
							{
								this->BoxFlashing->setLabel("Error during memory flash");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->tapTagBoxFlashing->Refresh();
							}
						}
						else
							this->BoxFlashing->setLabel("The file is too big. Maximum size: 16384 bytes (16 kB)");
					}

					else if (this->SelectFlashing->selDemo == true)
					{
						this->SelectFlashing->selDemo = false;
						String^ path = ".\\rsc\\NTAG_I2C_Explorer_Demo.bin";
						FileStream^ fs = File::OpenRead(path);

						DemoStream = fs;

						int newFWLength = (int)DemoStream->Length;
						int currentLength = 0;
						this->BoxFlashing->progressBarFlash->Step = 64;
						this->BoxFlashing->progressBarFlash->Value = 0;
						if (newFWLength > 12288)
							this->BoxFlashing->progressBarFlash->Maximum = maxFWLength;
						else if (newFWLength > 8192)
							this->BoxFlashing->progressBarFlash->Maximum = 12288;
						else if (newFWLength > 4096)
							this->BoxFlashing->progressBarFlash->Maximum = 8192;
						else
							this->BoxFlashing->progressBarFlash->Maximum = 4096;

						// Check that the firmware is not too big
						if (newFWLength <= maxFWLength)
						{
							DWORD flashBytes;
							float flashTime;

							// Convert the Stream variable to a BYTE array
							BYTE newFW[maxFWLength];
							array<Byte>^ newFWArray = gcnew array<Byte>(newFWLength);
							int n = DemoStream->Read(newFWArray, 0, newFWLength);
							DemoStream->Close();
							for (int i = 0; i < newFWLength; i++)
							{
								newFW[i] = (BYTE)newFWArray[i];
							}

							lReturn = FlashMemory(newFW, newFWLength, &flashBytes, &flashTime, this->BoxFlashing->progressBarFlash);

							if (lReturn == SCARD_S_SUCCESS)
							{
								this->BoxFlashing->setLabel("Memory flash completed successfully");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->tapTagBoxFlashing->Refresh();
								this->BoxFlashing->textBoxFlashPerformance->Text = " Speed(" + flashBytes + " B / " + flashTime + " ms): " +
									(1000.0 * flashBytes / flashTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
							}
							else
							{
								this->BoxFlashing->setLabel("Error during memory flash");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->tapTagBoxFlashing->Refresh();
							}
						}
						else
							this->BoxFlashing->setLabel("The file is too big. Maximum size: 16384 bytes (16 kB)");
					}
					// Read the file in a Stream variable
					else if ((newFWStream = this->openFileDialog1->OpenFile()) != nullptr)
					{
						int newFWLength = (int)newFWStream->Length;
						int currentLength = 0;
						// Check that the firmware is not too big
						if (newFWLength <= maxFWLength)
						{
							this->BoxFlashing->progressBarFlash->Step = 64;
							this->BoxFlashing->progressBarFlash->Value = 0;
							if (newFWLength > 12288)
								this->BoxFlashing->progressBarFlash->Maximum = maxFWLength;
							else if (newFWLength > 8192)
								this->BoxFlashing->progressBarFlash->Maximum = 12288;
							else if (newFWLength > 4096)
								this->BoxFlashing->progressBarFlash->Maximum = 8192;
							else
								this->BoxFlashing->progressBarFlash->Maximum = 4096;

							DWORD flashBytes;
							float flashTime;

							// Convert the Stream variable to a BYTE array
							BYTE newFW[maxFWLength];
							array<Byte>^ newFWArray = gcnew array<Byte>(newFWLength);
							int n = newFWStream->Read(newFWArray, 0, newFWLength);
							newFWStream->Close();
							for (int i = 0; i < newFWLength; i++)
							{
								newFW[i] = (BYTE)newFWArray[i];
							}

							lReturn = FlashMemory(newFW, newFWLength, &flashBytes, &flashTime, this->BoxFlashing->progressBarFlash);

							if (lReturn == SCARD_S_SUCCESS)
							{
								this->BoxFlashing->setLabel("Memory flash completed successfully");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->tapTagBoxFlashing->Refresh();
								if (this->BoxFlashing->progressBarFlash->Value == this->BoxFlashing->progressBarFlash->Maximum)
								{
									this->BoxFlashing->progressBarFlash->PerformStep();
									this->BoxFlashing->progressBarFlash->Value = 0;
								}
								//this->BoxFlashing->setLabel("");
								this->BoxFlashing->textBoxFlashPerformance->Text = " Speed(" + flashBytes + " B / " + flashTime + " ms): " +
									(1000.0 * flashBytes / flashTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
							}
							else
							{
								this->BoxFlashing->setLabel("Error during memory flash");
								Sleep(1000);
								this->BoxFlashing->setLabel("");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->tapTagBoxFlashing->Refresh();
							}
						}
						else
						{
							this->BoxFlashing->setLabel("The file is too big. Maximum size: 16384 bytes (16 kB)");
							Sleep(1000);
							this->BoxFlashing->setLabel("");
						}
					}
					else
					{
						this->BoxFlashing->setLabel("Could not open the file");
						Sleep(1000);
						this->BoxFlashing->setLabel("");
					}
				}
			}
			else if (this->tapTagBoxFlashing->Visible)
			{
				checking = "";
				if (this->tapTagBoxFlashing->textBox->Text != checking)
				{
					String^ file = nullptr;
					if (this->tapTagBoxFlashing->swi == true) //From storage
					{
						String^ fileName = this->openFileDialog1->FileName;
						int ind = this->openFileDialog1->FileName->LastIndexOf('\\');
						file = this->openFileDialog1->FileName->Substring(ind + 1);
						this->tapTagBoxFlashing->swi = false;
						this->BoxFlashing->textBoxFile->Text = file;
						this->BoxFlashing->Refresh();
					}
					else if (this->tapTagBoxFlashing->dwi == true)
					{
						if (this->SelectFlashing->selDemo == true) //Demo App selected
						{
							file = L"NTAG_I2C_Explorer_Demo.bin";
						}
						else if (this->SelectFlashing->selBlink == true) //LED Blinker selected
						{
							file = L"NTAG_I2C_Explorer_Blink.bin";
						}
						this->tapTagBoxFlashing->dwi = false;
						this->BoxFlashing->textBoxFile->Text = file;
						this->BoxFlashing->Refresh();
					}

					this->BoxFlashing->setLabel("");
					this->BoxFlashing->Show();
					this->BoxFlashing->textBoxFlashPerformance->Text = "";

					this->tapTagBoxFlashing->Hide();
					taghandler->endWait = true;
				}
				else
				{
					this->tapTagBoxFlashing->setLabel("Error while flashing the memory");
					checking = "";
					this->tapTagBoxFlashing->textBox->Text = checking;
				}
			}

			else if (this->radioButtonSRAM->Checked == true)
			{
				if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
				{
					if (checkStatus())
					{
						showWindowAuth();
					}
				}

				if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
				{
					if (firstSPEED)
					{
						firstSPEED = false;

							// SRAM Speed Test Demo
							this->textBox_SpeedT_PerformBody->Text = "";
							this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "Performing SRAM Speed Test...";
							this->groupBox6->Refresh();
							try
							{
								int chMultiplier = Convert::ToUInt32(this->textBox1->Text);
								bool integritySent, integrityRecv;
								float writeTime, readTime;
								Sleep(1000);
								lReturn = my_api->SRAMSpeedTest(chMultiplier, FALSE, &integritySent, &integrityRecv, &writeTime, &readTime);
								Sleep(1000);
								if (chMultiplier <= 9999)
								{
									if (lReturn == SCARD_S_SUCCESS)
									{
										this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "SRAM Speed Test performed successfully";
										this->textBox_SpeedT_PerformBody->Text = "Integrity of the sent data: " + (integritySent ? "OK" : "Error");
										this->textBox_SpeedT_PerformBody->Text += "\r\nIntegrity of the received data: " + (integrityRecv ? "OK" : "Error");
										this->textBox_SpeedT_PerformBody->Text += "\r\nTransfer NFC device to BoardDemo";
										this->textBox_SpeedT_PerformBody->Text += "\r\nSpeed (" + chMultiplier * 64 + " B / " + writeTime + " ms): " +
											(64000.0 * chMultiplier / writeTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
										this->textBox_SpeedT_PerformBody->Text += "\r\nTransfer BoardDemo to NFC device";
										this->textBox_SpeedT_PerformBody->Text += "\r\nSpeed (" + chMultiplier * 64 + " B / " + readTime + " ms): " +
											(64000.0 * chMultiplier / readTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
									}

								}
								else
								{
									this->textBox1->Text = "";
									this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "Tap tag to evaluate performance";
									this->textBox_SpeedT_PerformBody->Text = "";
									MessageBox::Show("Number too high, maximun length allowed 9999");
									return;
								}
							}
							catch (...)
							{
								this->textBox1->Text = "";
								this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "Tap tag to evaluate performance";
								this->textBox_SpeedT_PerformBody->Text = "";
								MessageBox::Show("Not a Number or Number too high");
								return;
							}
							this->checkTag = true;
						}
						else
						{
							Sleep(1000);
							this->countCheck = checkConnection();
							Sleep(1000);
							if (this->countCheck >= 4)
							{
								firstSPEED = true;
								firstTimeFalse = true;
								this->checkTag = false;
								this->authenticated = false;
								this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "Tap tag to evaluate performance";
								this->textBox_SpeedT_PerformBody->Text = "";
							}
							/*else
							{
								this->checkTag = false;
							}*/
						}
						this->taghandler->endWait = true;
				}
				else if (sramProtected == false)
				{
					if (firstSPEED)
					{
						firstSPEED = false;

						// SRAM Speed Test Demo
						this->textBox_SpeedT_PerformBody->Text = "";
						this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "Performing SRAM Speed Test...";
						this->groupBox6->Refresh();
						try
						{
							int chMultiplier = Convert::ToUInt32(this->textBox1->Text);
							bool integritySent, integrityRecv;
							float writeTime, readTime;
							Sleep(1000);
							lReturn = my_api->SRAMSpeedTest(chMultiplier, FALSE, &integritySent, &integrityRecv, &writeTime, &readTime);
							Sleep(1000);
							if (chMultiplier <= 9999)
							{
								if (lReturn == SCARD_S_SUCCESS)
								{
									this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "SRAM Speed Test performed successfully";
									this->textBox_SpeedT_PerformBody->Text = "Integrity of the sent data: " + (integritySent ? "OK" : "Error");
									this->textBox_SpeedT_PerformBody->Text += "\r\nIntegrity of the received data: " + (integrityRecv ? "OK" : "Error");
									this->textBox_SpeedT_PerformBody->Text += "\r\nTransfer NFC device to BoardDemo";
									this->textBox_SpeedT_PerformBody->Text += "\r\nSpeed (" + chMultiplier * 64 + " B / " + writeTime + " ms): " +
										(64000.0 * chMultiplier / writeTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
									this->textBox_SpeedT_PerformBody->Text += "\r\nTransfer BoardDemo to NFC device";
									this->textBox_SpeedT_PerformBody->Text += "\r\nSpeed (" + chMultiplier * 64 + " B / " + readTime + " ms): " +
										(64000.0 * chMultiplier / readTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
								}

							}
							else
							{
								this->textBox1->Text = "";
								this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "Tap tag to evaluate performance";
								this->textBox_SpeedT_PerformBody->Text = "";
								MessageBox::Show("Number too high, maximun length allowed 9999");
								return;
							}
						}
						catch (...)
						{
							this->textBox1->Text = "";
							this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "Tap tag to evaluate performance";
							this->textBox_SpeedT_PerformBody->Text = "";
							MessageBox::Show("Not a Number or Number too high");
							return;
						}
						this->checkTag = true;
					}
					else
					{
						Sleep(1000);
						this->countCheck = checkConnection();
						Sleep(1000);
						if (this->countCheck >= 4)
						{
							firstSPEED = true;
							firstTimeFalse = true;
							this->checkTag = false;
							this->authenticated = false;
							this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "Tap tag to evaluate performance";
							this->textBox_SpeedT_PerformBody->Text = "";
						}
						/*else
						{
							this->checkTag = false;
						}*/
					}
					this->taghandler->endWait = true;
				}
				else
				{
					//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
					this->checkTag = false;
					this->taghandler->endWait = true;
				}
			}
			else
			{
				if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
				{
					if (checkStatus())
					{
						showWindowAuth();
					}
				}

				const int maxFWLength = 16384;
				if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
				{
					if (firstSPEED)
					{
							firstSPEED = false;
							// EEPROM Speed Test Demo
							this->textBox_SpeedT_PerformBody->Text = "";
							this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "Performing EEPROM Speed Test...";
							this->groupBox6->Refresh();
							int chMultiplier = Convert::ToInt32(this->textBox1->Text);
							if ((chMultiplier < 857) && (chMultiplier >= 0))
							{
								int nWrittenBytes, nReadBytes, i, payloadNDEFSize;
								BYTE ascii_array[50] = " ";
								BYTE payloadNDEF[MAX_MEM_SIZE];
								float writeTime, readTime, writeTimeNDEF;
								BOOL AARPresent = FALSE, addAARNDEF = true;
								DWORD writtenBytesNDEF;
								array<Char>^ unicode_array;
								LONG lReturn2;
								Sleep(1000);
								lReturn = my_api->EEPROMSpeedTest(chMultiplier, ascii_array, &nWrittenBytes, &writeTime, &nReadBytes, &readTime);
								Sleep(1000);
								//After the EEPROM Speed Test we write a Default NDEF Message (not included in Read/Write time)
								System::Windows::Forms::TextBox^ AuxTextBox1 = (gcnew System::Windows::Forms::TextBox());
								System::Windows::Forms::TextBox^ AuxTextBox2 = (gcnew System::Windows::Forms::TextBox());
								AuxTextBox1->Text = L"NTAG I2C EXPLORER";
								AuxTextBox2->Text = L"http://www.nxp.com/demoboard/OM5569";

								// The string I send is: Title Length + Title + Link Length + Link
								// Convert from Unicode to ASCII
								payloadNDEF[0] = AuxTextBox1->Text->Length;
								unicode_array = AuxTextBox1->Text->ToCharArray();
								for (i = 0; i < payloadNDEF[0]; i++)
									payloadNDEF[i + 1] = (BYTE)unicode_array[i];
								payloadNDEF[payloadNDEF[0] + 1] = AuxTextBox2->Text->Length;
								unicode_array = AuxTextBox2->Text->ToCharArray();
								for (i = 0; i < payloadNDEF[payloadNDEF[0] + 1]; i++)
									payloadNDEF[i + payloadNDEF[0] + 2] = (BYTE)unicode_array[i];
								payloadNDEF[i + payloadNDEF[0] + 2] = '\0';
								payloadNDEFSize = i + payloadNDEF[0] + 2;
								Sleep(1000);
								lReturn2 = my_api->WriteNdef(TYPE_NDEF_SP, payloadNDEF, payloadNDEFSize, addAARNDEF, &writtenBytesNDEF, &writeTimeNDEF);
								Sleep(1000);
								if (lReturn2 != SCARD_S_SUCCESS){
									lReturn = lReturn2;
								}

								int overhead = my_api->numberBytes2Write(chMultiplier) - chMultiplier;

								if (overhead + chMultiplier <= maxFWLength)
								{
									String^ overhead_text = Convert::ToString(overhead);
									this->label8->Text = "+" + overhead + " overhead bytes";
									if (lReturn == SCARD_S_SUCCESS)
									{
										this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "EEPROM Test performed successfully";
										this->textBox_SpeedT_PerformBody->Text += "Transfer NFC device to BoardDemo ";
										this->textBox_SpeedT_PerformBody->Text += "\r\nSpeed (" + nWrittenBytes + " B / " + writeTime + " ms): " +
											(1000.0 * nWrittenBytes / writeTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
										this->textBox_SpeedT_PerformBody->Text += "\r\nTransfer BoardDemo to NFC device";
										this->textBox_SpeedT_PerformBody->Text += "\r\nSpeed (" + nReadBytes + " B / " + readTime + " ms): " +
											(1000.0 * nReadBytes / readTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
									}
								}
								else
								{
									this->textBox1->Text = "";
									this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "Tap tag to evaluate performance";
									this->textBox_SpeedT_PerformBody->Text = "";
									MessageBox::Show("Number too high, maximun length allowed 888 Bytes");
									return;
								}
							}
							else
							{
								this->textBox1->Text = "640";
								this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "Tap tag to evaluate performance";
								this->textBox_SpeedT_PerformBody->Text = chMultiplier + " is not a valid data length.";
								MessageBox::Show("Not a Number or Number too high");
								return;
							}
							this->checkTag = true;
						}
						else
						{
							Sleep(1000);
							this->countCheck = checkConnection();
							Sleep(1000);
							if (this->countCheck >= 4)
							{
								firstSPEED = true;
								firstTimeFalse = true;
								this->authenticated = false;
								this->checkTag = false;
								this->textBox_SpeedT_PerNTAG_I2C_Demo_GUIstLine->Text = "Tap tag to evaluate performance";
								this->textBox_SpeedT_PerformBody->Text = "";
							}
							/*else
							{
								this->checkTag = false;
							}*/
						}
						this->taghandler->endWait = true;
					}
					else
					{
						//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
						this->checkTag = false;
						this->taghandler->endWait = true;
					}
				}
		}

		// This function is executed when the current tab is the Config demo and the tag is tapped against the reader
		void OnConfigOption()
		{
			LONG lReturn;
			this->cBox_NDEFT_Loop->Checked = false;

			if (this->versionBox1->Visible)
			{
				// Read the board version
				this->versionBox1->setLabel("Reading the board version...");
				Versions_t versions;
				lReturn = board_demo->ReadVersions(&versions);
				if (lReturn == SCARD_S_SUCCESS)
				{
					this->versionBox1->updateBox(versions, this->AppVersion, this->IdentivVer);
					this->versionBox1->setLabel("");
				}
				else
					this->versionBox1->setLabel("Error while reading the board version");
			}
			else if (this->tapTagBoxAbout->Visible)
			{
				if (retu == SCARD_S_SUCCESS)
				{
					char  IdentivReaderFWversion[3];
					my_api->readIdentivFWversion(IdentivReaderFWversion);

					String^ strNew = gcnew String(IdentivReaderFWversion);

					this->IdentivVer = strNew;

					// Read the board version
					this->tapTagBoxAbout->setLabel("Reading the board version...");
					Versions_t versions;
					lReturn = board_demo->ReadVersions(&versions);
					if (lReturn == SCARD_S_SUCCESS)
					{
						this->versionBox1->updateBox(versions, this->AppVersion, this->IdentivVer);
						this->versionBox1->setLabel("");
						this->versionBox1->Show();
						this->tapTagBoxAbout->Hide();
					}
					else
						this->tapTagBoxAbout->setLabel("Error while reading the board version");
				}
			}
			else if (this->BoxFlashing->Visible)
			{
				checking = "";
				if (this->tapTagBoxFlashing->textBox->Text == checking)
				{
					//MessageBox::Show("Please select a valid file");
					this->BoxFlashing->Hide();
					this->tapTagBoxFlashing->Show();
				}
				else
				{
					this->BoxFlashing->setLabel("Flashing memory content...");

					if (this->tagBlocked && !this->authenticated)
					{
						authenticate();
					}

					if (this->SelectFlashing->selBlink == true)
					{
						this->BoxFlashing->textBoxFile->Text = "NTAG_I2C_Explorer_Blink.bin";
					}
					else if (this->SelectFlashing->selDemo == true)
					{
						this->BoxFlashing->textBoxFile->Text = "NTAG_I2C_Explorer_Demo.bin";
					}
					else
					{
						String^ fileName = this->openFileDialog1->FileName;
						int ind = this->openFileDialog1->FileName->LastIndexOf('\\');
						String^ file = this->openFileDialog1->FileName->Substring(ind + 1);

						this->BoxFlashing->textBoxFile->Text = file;
					}
					Sleep(1000);
					this->BoxFlashing->setLabel("");
					this->BoxFlashing->textBoxFlashPerformance->Text = "";

					const int maxFWLength = 16384;	// The maximum firmware that can be flashed is 16384 (4 sectors of 4096 bytes each)
					System::IO::Stream^ newFWStream = nullptr;
					System::IO::Stream^ DemoStream = nullptr;

					if (this->SelectFlashing->selBlink == true)
					{
						this->SelectFlashing->selBlink = false;
						String^ path = ".\\rsc\\NTAG_I2C_Explorer_Blink.bin";
						FileStream^ fs = File::OpenRead(path);

						DemoStream = fs;

						int newFWLength = (int)DemoStream->Length;
						int currentLength = 0;
						this->BoxFlashing->progressBarFlash->Step = 64;
						this->BoxFlashing->progressBarFlash->Value = 0;
						if (newFWLength > 12288)
							this->BoxFlashing->progressBarFlash->Maximum = maxFWLength;
						else if (newFWLength > 8192)
							this->BoxFlashing->progressBarFlash->Maximum = 12288;
						else if (newFWLength > 4096)
							this->BoxFlashing->progressBarFlash->Maximum = 8192;
						else
							this->BoxFlashing->progressBarFlash->Maximum = 4096;

						// Check that the firmware is not too big
						if (newFWLength <= maxFWLength)
						{
							DWORD flashBytes;
							float flashTime;

							// Convert the Stream variable to a BYTE array
							BYTE newFW[maxFWLength];
							array<Byte>^ newFWArray = gcnew array<Byte>(newFWLength);
							int n = DemoStream->Read(newFWArray, 0, newFWLength);
							DemoStream->Close();
							for (int i = 0; i < newFWLength; i++)
							{
								newFW[i] = (BYTE)newFWArray[i];
							}

							lReturn = FlashMemory(newFW, newFWLength, &flashBytes, &flashTime, this->BoxFlashing->progressBarFlash);

							if (lReturn == SCARD_S_SUCCESS)
							{
								this->hasBeenFlashed = true;
								this->BoxFlashing->setLabel("Memory flash completed successfully");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->BoxFlashing->textBoxFlashPerformance->Text = " Speed(" + flashBytes + " B / " + flashTime + " ms): " +
									(1000.0 * flashBytes / flashTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
							}
							else
							{
								this->BoxFlashing->setLabel("Error during memory flash");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
							}
						}
						else
							this->BoxFlashing->setLabel("The file is too big. Maximum size: 16384 bytes (16 kB)");
					}

					else if (this->SelectFlashing->selDemo == true)
					{
						this->SelectFlashing->selDemo = false;
						String^ path = ".\\rsc\\NTAG_I2C_Explorer_Demo.bin";
						FileStream^ fs = File::OpenRead(path);

						DemoStream = fs;

						int newFWLength = (int)DemoStream->Length;
						int currentLength = 0;
						this->BoxFlashing->progressBarFlash->Step = 64;
						this->BoxFlashing->progressBarFlash->Value = 0;
						if (newFWLength > 12288)
							this->BoxFlashing->progressBarFlash->Maximum = maxFWLength;
						else if (newFWLength > 8192)
							this->BoxFlashing->progressBarFlash->Maximum = 12288;
						else if (newFWLength > 4096)
							this->BoxFlashing->progressBarFlash->Maximum = 8192;
						else
							this->BoxFlashing->progressBarFlash->Maximum = 4096;

						// Check that the firmware is not too big
						if (newFWLength <= maxFWLength)
						{
							DWORD flashBytes;
							float flashTime;

							// Convert the Stream variable to a BYTE array
							BYTE newFW[maxFWLength];
							array<Byte>^ newFWArray = gcnew array<Byte>(newFWLength);
							int n = DemoStream->Read(newFWArray, 0, newFWLength);
							DemoStream->Close();
							for (int i = 0; i < newFWLength; i++)
							{
								newFW[i] = (BYTE)newFWArray[i];
							}

							lReturn = FlashMemory(newFW, newFWLength, &flashBytes, &flashTime, this->BoxFlashing->progressBarFlash);

							if (lReturn == SCARD_S_SUCCESS)
							{
								this->hasBeenFlashed = true;
								this->BoxFlashing->setLabel("Memory flash completed successfully");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								this->BoxFlashing->textBoxFlashPerformance->Text = " Speed(" + flashBytes + " B / " + flashTime + " ms): " +
									(1000.0 * flashBytes / flashTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
							}
							else
							{
								this->BoxFlashing->setLabel("Error during memory flash");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
							}
						}
						else
							this->BoxFlashing->setLabel("The file is too big. Maximum size: 16384 bytes (16 kB)");
					}
					// Read the file in a Stream variable
					else if ((newFWStream = this->openFileDialog1->OpenFile()) != nullptr)
					{
						int newFWLength = (int)newFWStream->Length;
						int currentLength = 0;
						// Check that the firmware is not too big
						if (newFWLength <= maxFWLength)
						{
							this->BoxFlashing->progressBarFlash->Step = 64;
							this->BoxFlashing->progressBarFlash->Value = 0;
							if (newFWLength > 12288)
								this->BoxFlashing->progressBarFlash->Maximum = maxFWLength;
							else if (newFWLength > 8192)
								this->BoxFlashing->progressBarFlash->Maximum = 12288;
							else if (newFWLength > 4096)
								this->BoxFlashing->progressBarFlash->Maximum = 8192;
							else
								this->BoxFlashing->progressBarFlash->Maximum = 4096;

							DWORD flashBytes;
							float flashTime;

							// Convert the Stream variable to a BYTE array
							BYTE newFW[maxFWLength];
							array<Byte>^ newFWArray = gcnew array<Byte>(newFWLength);
							int n = newFWStream->Read(newFWArray, 0, newFWLength);
							newFWStream->Close();
							for (int i = 0; i < newFWLength; i++)
							{
								newFW[i] = (BYTE)newFWArray[i];
							}

							lReturn = FlashMemory(newFW, newFWLength, &flashBytes, &flashTime, this->BoxFlashing->progressBarFlash);

							if (lReturn == SCARD_S_SUCCESS)
							{
								this->hasBeenFlashed = true;
								this->BoxFlashing->setLabel("Memory flash completed successfully");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								if (this->BoxFlashing->progressBarFlash->Value == this->BoxFlashing->progressBarFlash->Maximum)
								{
									this->BoxFlashing->progressBarFlash->PerformStep();
									this->BoxFlashing->progressBarFlash->Value = 0;
								}
								this->BoxFlashing->textBoxFlashPerformance->Text = " Speed(" + flashBytes + " B / " + flashTime + " ms): " +
									(1000.0 * flashBytes / flashTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s";
							}
							else
							{
								this->BoxFlashing->setLabel("Error during memory flash");
								checking = "";
								this->tapTagBoxFlashing->textBox->Text = checking;
								Sleep(1000);
								this->BoxFlashing->setLabel("");
							}
						}
						else
						{
							this->BoxFlashing->setLabel("The file is too big. Maximum size: 16384 bytes (16 kB)");
							Sleep(1000);
							this->BoxFlashing->setLabel("");
						}
					}
					else
					{
						this->BoxFlashing->setLabel("Could not open the file");
						Sleep(1000);
						this->BoxFlashing->setLabel("");
					}
				}
			}
			else if (this->tapTagBoxFlashing->Visible)
			{
				checking = "";
				if (this->tapTagBoxFlashing->textBox->Text != checking)
				{
					String^ file = nullptr;
					if (this->tapTagBoxFlashing->swi == true) //From storage
					{
						String^ fileName = this->openFileDialog1->FileName;
						int ind = this->openFileDialog1->FileName->LastIndexOf('\\');
						file = this->openFileDialog1->FileName->Substring(ind + 1);
						this->tapTagBoxFlashing->swi = false;
						this->BoxFlashing->textBoxFile->Text = file;
						this->BoxFlashing->Refresh();
					}
					else if (this->tapTagBoxFlashing->dwi == true)
					{
						if (this->SelectFlashing->selDemo == true) //Demo App selected
						{
							file = L"NTAG_I2C_Explorer_Demo.bin";
						}
						else if (this->SelectFlashing->selBlink == true) //LED Blinker selected
						{
							file = L"NTAG_I2C_Explorer_Blink.bin";
						}
						this->tapTagBoxFlashing->dwi = false;
						this->BoxFlashing->textBoxFile->Text = file;
						checking = "";
						this->tapTagBoxFlashing->textBox->Text = checking;
						this->BoxFlashing->Refresh();
					}

					this->BoxFlashing->setLabel("");
					this->BoxFlashing->Show();
					this->BoxFlashing->textBoxFlashPerformance->Text = "";

					this->tapTagBoxFlashing->Hide();
					taghandler->endWait = true;
				}
				else
					this->tapTagBoxFlashing->setLabel("Error while flashing the memory");
			}

			else if (this->readMemBox1->Visible)
			{
				BYTE data[MAX_MEM_SIZE];
				DWORD readBytes;
				float readTime;

				if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
				{
					if (checkStatus())
					{
						showWindowAuth();
					}
				}

				if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
				{
					if (firstREG)
					{
						firstREG = false;

						this->readMemBox1->setLabel("Reading the tag memory...");

						// Read tag memory
						lReturn = my_api->Read_EEPROM(data, &readBytes, &readTime);
						Sleep(500);
						this->readMemBox1->setTextBox("");
						if (lReturn == SCARD_S_SUCCESS)
						{
							this->readMemBox1->updateLabel(data, readBytes, this->isTagPlus);
							this->readMemBox1->setLabel("");
							this->readMemBox1->setTextBox(" NTAG memory read\r\n Speed(" + readBytes + " B / " + readTime + " ms): " +
								(1000.0 * readBytes / readTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s");
						}
						else
						{
							this->readMemBox1->setLabel("Error while reading the tag memory");
						}
					}
					else
					{
						this->countCheck = checkConnection();
						if (this->countCheck >= 4)
						{
							this->checkTag = false;
							firstTimeFalse = true;
							this->tapTagBoxReadMem->setLabel("");
							this->readMemBox1->Hide();
							this->tapTagBoxReadMem->Show();
						}
					}
					this->taghandler->endWait = true;
				}
				else if (this->protectedRead == false)
				{
					if (firstREG)
					{
						firstREG = false;

						this->tapTagBoxReadMem->setLabel("Reading the tag memory...");
						// Read tag memory
						if (this->authenticated) this->my_api->setAuthentication(this->password);
						lReturn = my_api->Read_EEPROM(data, &readBytes, &readTime);
						Sleep(500);
						if (lReturn == SCARD_S_SUCCESS)
						{
							this->readMemBox1->updateLabel(data, readBytes, this->isTagPlus);
							this->readMemBox1->setLabel("");
							this->readMemBox1->setTextBox(" NTAG memory read\r\n Speed(" + readBytes + " B / " + readTime + " ms): " +
								(1000.0 * readBytes / readTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s");
							this->readMemBox1->Show();
							this->tapTagBoxReadMem->Hide();
						}
						else
						{
							this->tapTagBoxReadMem->setLabel("Error while reading the tag memory");
						}
					}
					else
					{
						this->countCheck = checkConnection();
						if (this->countCheck >= 4)
						{
							this->taghandler->tagOut = true;
							this->checkTag = false;
							this->firstTime = true;
							firstTimeFalse = true;
						}
					}
					this->taghandler->endWait = true;
				}
				else
				{
					//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
				}
			}
			else if (this->tapTagBoxReadMem->Visible)
			{
				BYTE data[MAX_MEM_SIZE];
				DWORD readBytes;
				float readTime;

				if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
				{
					if (checkStatus())
					{
						showWindowAuth();
					}
				}

				if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
				{
					if (firstREG)
					{
						firstREG = false;

						this->tapTagBoxReadMem->setLabel("Reading the tag memory...");
						// Read tag memory
						if(this->authenticated) this->my_api->setAuthentication(this->password);
						lReturn = my_api->Read_EEPROM(data, &readBytes, &readTime);
						Sleep(500);
						if (lReturn == SCARD_S_SUCCESS)
						{
							this->readMemBox1->updateLabel(data, readBytes, this->isTagPlus);
							this->readMemBox1->setLabel("");
							this->readMemBox1->setTextBox(" NTAG memory read\r\n Speed(" + readBytes + " B / " + readTime + " ms): " +
								(1000.0 * readBytes / readTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s");
							this->readMemBox1->Show();
							this->tapTagBoxReadMem->Hide();
						}
						else
						{
							this->tapTagBoxReadMem->setLabel("Error while reading the tag memory");
						}
					}
					else
					{
						this->countCheck = checkConnection();
						if (this->countCheck >= 4)
						{
							this->taghandler->tagOut = true;
							this->checkTag = false;
							this->firstTime = true;
							firstTimeFalse = true;
						}
					}
					this->taghandler->endWait = true;
				}
				else if (this->protectedRead == false)
				{
					if (firstREG)
					{
						firstREG = false;

						this->tapTagBoxReadMem->setLabel("Reading the tag memory...");
						// Read tag memory
						if (this->authenticated) this->my_api->setAuthentication(this->password);
						lReturn = my_api->Read_EEPROM(data, &readBytes, &readTime);
						Sleep(500);
						if (lReturn == SCARD_S_SUCCESS)
						{
							this->readMemBox1->updateLabel(data, readBytes, this->isTagPlus);
							this->readMemBox1->setLabel("");
							this->readMemBox1->setTextBox(" NTAG memory read\r\n Speed(" + readBytes + " B / " + readTime + " ms): " +
								(1000.0 * readBytes / readTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s");
							this->readMemBox1->Show();
							this->tapTagBoxReadMem->Hide();
						}
						else
						{
							this->tapTagBoxReadMem->setLabel("Error while reading the tag memory");
						}
					}
					else
					{
						this->countCheck = checkConnection();
						if (this->countCheck >= 4)
						{
							this->taghandler->tagOut = true;
							this->checkTag = false;
							this->firstTime = true;
							firstTimeFalse = true;
						}
					}
					this->taghandler->endWait = true;
				}
				else
				{
					//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
				}
			}
			if (this->resetMemBox1->Visible)
			{
				DWORD resetBytes;
				float resetTime;

				if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
				{
					if (checkStatus())
					{
						showWindowAuth();
					}
				}

				if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
				{
					if (firstREG)
					{
						if (retu == SCARD_S_SUCCESS)
						{
							firstREG = false;

							this->resetMemBox1->setLabel("Resetting the tag memory...");
							this->resetMemBox1->setTextBox("");

							if (this->authenticated) this->my_api->setAuthentication(this->password);
							// Reset tag memory
							lReturn = my_api->ResetEEPROMMemory(&resetBytes, &resetTime);
							Sleep(500);
							if (lReturn == SCARD_S_SUCCESS)
							{
								this->resetMemBox1->setLabel("Tag memory reset performed succesfully");
								this->authenticated = false;
								this->tagBlocked = false;
								Sleep(1000);
								this->resetMemBox1->setLabel("");
								this->resetMemBox1->setTextBox(" NTAG memory read\r\n Speed(" + resetBytes + " B / " + resetTime + " ms): " +
									(1000.0 * resetBytes / resetTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s");
							}
							else if (lReturn == SCARD_P_STATIC_LOCKED)
								this->resetMemBox1->setLabel("Static Lockbits set, cannot reset (use I²C instead to reset)");
							else if (lReturn == SCARD_P_DYNAMIC_LOCKED)
								this->resetMemBox1->setLabel("Dynamic Lockbits set, cannot reset (use I²C instead to reset)");
							else if (lReturn == SCARD_P_CC_WRONG)
								this->resetMemBox1->setLabel("Capability Container wrong (use I²C instead to reset)");
							else if (lReturn == SCARD_P_CONFIG_LOCKED)
								this->resetMemBox1->setLabel("Configuration cannot be updated via RF");
							else
							{
								this->resetMemBox1->setLabel("Error while resetting the tag memory");
							}
						}
						else
						{
							this->countCheck = checkConnection();
							if (this->countCheck >= 4)
							{
								this->taghandler->tagOut = true;
								this->checkTag = false;
								this->firstTime = true;
								firstTimeFalse = true;
							}
						}
						this->taghandler->endWait = true;
					}
				}
				else
				{
					//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
				}
			}
			if (this->tapTagBoxResetMem->Visible)
			{

				if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
				{
					if (checkStatus())
					{
						showWindowAuth();
					}
				}

				if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
				{
					if (firstREG)
					{
						if (retu == SCARD_S_SUCCESS)
						{
							firstREG = false;
							// Reset tag memory
							this->tapTagBoxResetMem->setLabel("Resetting the tag memory...");
							DWORD resetBytes;
							float resetTime;
							if (this->authenticated) this->my_api->setAuthentication(this->password);
							lReturn = my_api->ResetEEPROMMemory(&resetBytes, &resetTime);
							Sleep(500);
							if (lReturn == SCARD_S_SUCCESS)
							{
								this->tapTagBoxResetMem->setLabel("Tag memory reset performed succesfully");
								this->authenticated = false;
								this->tagBlocked = false;
								Sleep(1000);
								this->resetMemBox1->setLabel("");
								this->resetMemBox1->setTextBox(" NTAG memory reset\r\n Speed(" + resetBytes + " B / " + resetTime + " ms): " +
									(1000.0 * resetBytes / resetTime).ToString("0.00", System::Globalization::CultureInfo::InvariantCulture) + " B/s");
								this->resetMemBox1->Show();
								this->tapTagBoxResetMem->Hide();
							}
							else if (lReturn == SCARD_P_STATIC_LOCKED)
								this->tapTagBoxResetMem->setLabel("Static Lockbits set, cannot reset (use I²C instead to reset)");
							else if (lReturn == SCARD_P_DYNAMIC_LOCKED)
								this->tapTagBoxResetMem->setLabel("Dynamic Lockbits set, cannot reset (use I²C instead to reset)");
							else if (lReturn == SCARD_P_CC_WRONG)
								this->tapTagBoxResetMem->setLabel("Capability Container wrong (use I²C instead to reset)");
							else if (lReturn == SCARD_P_CONFIG_LOCKED)
								this->tapTagBoxResetMem->setLabel("Configuration cannot be updated via RF");
							else
							{
								this->tapTagBoxResetMem->setLabel("Error while resetting the tag memory");
							}
						}
						else
						{
							this->countCheck = checkConnection();
							if (this->countCheck >= 4)
							{
								this->taghandler->tagOut = true;
								this->checkTag = false;
								this->firstTime = true;
								firstTimeFalse = true;
							}
						}
						this->taghandler->endWait = true;
					}
				}
				else
				{
					//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
				}
			}
			else if (this->sessionRegBox1->Visible)
			{
				if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
				{
					if (checkStatus())
					{
						showWindowAuth();
					}
				}

				if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
				{
					if (firstREG)
					{
						firstREG = false;

						// Read session registers
						this->sessionRegBox1->setLabel("Reading the session registers...");
						Ntag_I2C_Registers_t sessionReg;
						if (this->authenticated) this->my_api->setAuthentication(this->password);
						lReturn = my_api->ReadSessionRegisters(&sessionReg);
						Sleep(500);
						if (lReturn == SCARD_S_SUCCESS)
						{
							this->sessionRegBox1->updateBox(sessionReg);
							this->sessionRegBox1->setLabel("");
						}
						else
						{
							this->sessionRegBox1->setLabel("Error while reading the session registers");
						}
					}
					else
					{
						this->countCheck = checkConnection();
						if (this->countCheck >= 4)
						{
							this->taghandler->tagOut = true;
							this->checkTag = false;
							this->firstTime = true;
							firstTimeFalse = true;
						}
					}
					this->taghandler->endWait = true;
				}
				else if (this->protectedRead == false)
				{
					if (firstREG)
					{
						firstREG = false;

						// Read session registers
						this->sessionRegBox1->setLabel("Reading the session registers...");
						Ntag_I2C_Registers_t sessionReg;
						if (this->authenticated) this->my_api->setAuthentication(this->password);
						lReturn = my_api->ReadSessionRegisters(&sessionReg);
						Sleep(500);
						if (lReturn == SCARD_S_SUCCESS)
						{
							this->sessionRegBox1->updateBox(sessionReg);
							this->sessionRegBox1->setLabel("");
						}
						else
						{
							this->sessionRegBox1->setLabel("Error while reading the session registers");
						}
					}
					else
					{
						this->countCheck = checkConnection();
						if (this->countCheck >= 4)
						{
							this->taghandler->tagOut = true;
							this->checkTag = false;
							this->firstTime = true;
							firstTimeFalse = true;
						}
					}
					this->taghandler->endWait = true;
				}
				else
				{
					//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
				}
			}
			else if (this->tapTagBoxReadSessionReg->Visible)
			{
				if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
				{
					if (checkStatus())
					{
						showWindowAuth();
					}
				}

				if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
				{
					if (firstREG)
					{
						firstREG = false;
						// Read session registers
						this->tapTagBoxReadSessionReg->setLabel("Reading the session registers...");
						Ntag_I2C_Registers_t sessionReg;
						if (this->authenticated) this->my_api->setAuthentication(this->password);
						lReturn = my_api->ReadSessionRegisters(&sessionReg);
						Sleep(500);
						if (lReturn == SCARD_S_SUCCESS)
						{
							this->sessionRegBox1->updateBox(sessionReg);
							this->sessionRegBox1->setLabel("");
							this->sessionRegBox1->Show();
							this->tapTagBoxReadSessionReg->Hide();
						}
						else
						{
							this->tapTagBoxReadSessionReg->setLabel("Error while reading the session registers");
						}
					}
					else
					{
						this->countCheck = checkConnection();
						if (this->countCheck >= 4)
						{
							this->taghandler->tagOut = true;
							this->checkTag = false;
							this->firstTime = true;
							firstTimeFalse = true;
						}
					}
					this->taghandler->endWait = true;
				}
				else if (this->protectedRead == false)
				{
					if (firstREG)
					{
						firstREG = false;
						// Read session registers
						this->tapTagBoxReadSessionReg->setLabel("Reading the session registers...");
						Ntag_I2C_Registers_t sessionReg;
						if (this->authenticated) this->my_api->setAuthentication(this->password);
						lReturn = my_api->ReadSessionRegisters(&sessionReg);
						Sleep(500);
						if (lReturn == SCARD_S_SUCCESS)
						{
							this->sessionRegBox1->updateBox(sessionReg);
							this->sessionRegBox1->setLabel("");
							this->sessionRegBox1->Show();
							this->tapTagBoxReadSessionReg->Hide();
						}
						else
						{
							this->tapTagBoxReadSessionReg->setLabel("Error while reading the session registers");
						}
					}
					else
					{
						this->countCheck = checkConnection();
						if (this->countCheck >= 4)
						{
							this->taghandler->tagOut = true;
							this->checkTag = false;
							this->firstTime = true;
							firstTimeFalse = true;
						}
					}
					this->taghandler->endWait = true;
				}
				else
				{
					//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
				}
			}
			else if (this->configRegBox1->Visible)
			{
				taghandler->endWait = true;
				if (configRegBox1->pressed)
				{
					if (configRegBox1->grackButton1->isActive)
					{
						if (configRegBox1->g1wasActive)
						{
							if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
							{
								if (checkStatus())
								{
									showWindowAuth();
								}
							}

							if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
							{
								// Read config registers
								Ntag_I2C_Registers_t configReg;
								Ntag_I2C_Access_Registers_t accessReg;
								if (this->authenticated) this->my_api->setAuthentication(this->password);
								lReturn = my_api->ReadConfigRegisters(&configReg);
								Sleep(500);
								if (lReturn == SCARD_S_SUCCESS)
								{
										this->configRegBox1->setLabel("Reading the configuration registers...");
										this->configRegBox1->updateBox(configReg);
										this->configRegBox1->setLabel("Read completed successfully");
										Sleep(1000);
										this->configRegBox1->setLabel("");
								}
								configRegBox1->pressed = false;
								this->taghandler->endWait = true;
							}
							else if (this->protectedRead == false)
							{
								// Read config registers
								Ntag_I2C_Registers_t configReg;
								Ntag_I2C_Access_Registers_t accessReg;
								if (this->authenticated) this->my_api->setAuthentication(this->password);
								lReturn = my_api->ReadConfigRegisters(&configReg);
								Sleep(500);
								if (lReturn == SCARD_S_SUCCESS)
								{
									this->configRegBox1->setLabel("Reading the configuration registers...");
									this->configRegBox1->updateBox(configReg);
									this->configRegBox1->setLabel("Read completed successfully");
									Sleep(1000);
									this->configRegBox1->setLabel("");
								}
								configRegBox1->pressed = false;
								this->taghandler->endWait = true;
							}
							else
							{
								//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
							}
						}
					}
					else
					{
						if (configRegBox1->g2wasActive)
						{
							if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
							{
								if (checkStatus())
								{
									showWindowAuth();
								}
							}

							if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
							{
									// Write config registers
									Ntag_I2C_Registers_t configReg;
									Ntag_I2C_Access_Registers_t accessReg;

										this->configRegBox1->setLabel("Writing the configuration registers...");
										this->configRegBox1->parseBox(&configReg); 
										if (this->authenticated) this->my_api->setAuthentication(this->password);
										lReturn = my_api->WriteConfigRegisters(configReg);
										Sleep(500);
										if (lReturn == SCARD_S_SUCCESS)
										{
											this->configRegBox1->setLabel("Write completed successfully");
											Sleep(1000);
											this->configRegBox1->setLabel("");
										}

										configRegBox1->pressed = false;

								this->taghandler->endWait = true;
							}
							else
							{
								//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
							}
						}
					}
				}
				else
				{
					if (configRegBox1->grackButton1->isActive)
					{
						if (configRegBox1->g1wasActive)
						{
							if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
							{
								if (checkStatus())
								{
									showWindowAuth();
								}
							}
							if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
							{
								if (firstREG)
								{
									firstREG = false;
									// Read config registers
									Ntag_I2C_Registers_t configReg;
									if (this->authenticated) this->my_api->setAuthentication(this->password);
									lReturn = my_api->ReadConfigRegisters(&configReg);
									Sleep(500);
									if (lReturn == SCARD_S_SUCCESS)
									{
										this->configRegBox1->setLabel("Reading the configuration registers...");
										this->configRegBox1->updateBox(configReg);
										this->configRegBox1->setLabel("Read completed successfully");
										Sleep(1000);
										this->configRegBox1->setLabel("");
									}
								}
								else
								{
									this->countCheck = checkConnection();
									if (this->countCheck >= 4)
									{
										this->taghandler->tagOut = true;
										this->checkTag = false;
										this->firstTime = true;
										firstTimeFalse = true;
									}
								}

								this->taghandler->endWait = true;
							}
							else if (this->protectedRead == false)
							{
								// Read config registers
								Ntag_I2C_Registers_t configReg;
								Ntag_I2C_Access_Registers_t accessReg;
								if (this->authenticated) this->my_api->setAuthentication(this->password);
								lReturn = my_api->ReadConfigRegisters(&configReg);
								Sleep(500);
								if (lReturn == SCARD_S_SUCCESS)
								{
									this->configRegBox1->setLabel("Reading the configuration registers...");
									this->configRegBox1->updateBox(configReg);
									this->configRegBox1->setLabel("Read completed successfully");
									Sleep(1000);
									this->configRegBox1->setLabel("");
								}
								configRegBox1->pressed = false;
								this->taghandler->endWait = true;
							}
							else
							{
								//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
							}
						}
					}
					else
					{
						if (configRegBox1->g2wasActive)
						{
							if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
							{
								if (checkStatus())
								{
									showWindowAuth();
								}
							}
							if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
							{
								if (firstREG)
								{
									firstREG = false;
									// Write config registers
									Ntag_I2C_Registers_t configReg;

									this->configRegBox1->setLabel("Writing the configuration registers...");
									this->configRegBox1->parseBox(&configReg);
									if (this->authenticated) this->my_api->setAuthentication(this->password);
									lReturn = my_api->WriteConfigRegisters(configReg);
									Sleep(500);
									if (lReturn == SCARD_S_SUCCESS)
									{
										this->configRegBox1->setLabel("Write completed successfully");
										Sleep(1000);
										this->configRegBox1->setLabel("");
									}
								}
								else
								{
									this->countCheck = checkConnection();
									if (this->countCheck >= 4)
									{
										this->taghandler->tagOut = true;
										this->checkTag = false;
										this->firstTime = true;
										firstTimeFalse = true;
									}
								}

								this->taghandler->endWait = true;
							}
							else
							{
								//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
							}
						}
					}
				}
			}
			else if (this->configRegBoxAccess->Visible)
			{
				taghandler->endWait = true;
				if (configRegBoxAccess->pressed)
				{
					if (configRegBoxAccess->grackButton1->isActive)
					{
						if (configRegBoxAccess->g1wasActive)
						{
							if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
							{
								if (checkStatus())
								{
									showWindowAuth();
								}
							}
							if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
							{
								// Read config registers
								Ntag_I2C_Registers_t configReg;
								Ntag_I2C_Access_Registers_t accessReg;
								if (this->authenticated) this->my_api->setAuthentication(this->password);
								lReturn = my_api->ReadConfigRegisters(&configReg);
								Sleep(500);
								if (lReturn == SCARD_S_SUCCESS)
								{
									this->configRegBoxAccess->setLabel("Reading the configuration registers...");
									if (this->authenticated) this->my_api->setAuthentication(this->password);
									lReturn = my_api->ReadAccessRegisters(&accessReg);
									Sleep(500);
									this->configRegBoxAccess->updateBoxAccess(configReg, accessReg);
									this->configRegBoxAccess->setLabel("Read completed successfully");
									Sleep(1000);
									this->configRegBoxAccess->setLabel("");
								}
								configRegBoxAccess->pressed = false;
								this->taghandler->endWait = true;
							}
							else if (this->protectedRead == false)
							{
								// Read config registers
								Ntag_I2C_Registers_t configReg;
								Ntag_I2C_Access_Registers_t accessReg;
								if (this->authenticated) this->my_api->setAuthentication(this->password);
								lReturn = my_api->ReadConfigRegisters(&configReg);
								Sleep(500);
								if (lReturn == SCARD_S_SUCCESS)
								{
									this->configRegBoxAccess->setLabel("Reading the configuration registers...");
									if (this->authenticated) this->my_api->setAuthentication(this->password);
									lReturn = my_api->ReadAccessRegisters(&accessReg);
									Sleep(500);
									this->configRegBoxAccess->updateBoxAccess(configReg, accessReg);
									this->configRegBoxAccess->setLabel("Read completed successfully");
									Sleep(1000);
									this->configRegBoxAccess->setLabel("");
								}
								configRegBoxAccess->pressed = false;
								this->taghandler->endWait = true;
							}
							else
							{
								//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
							}
						}
					}
					else
					{
						if (configRegBoxAccess->g2wasActive)
						{
							if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
							{
								if (checkStatus())
								{
									showWindowAuth();
								}
							}
							if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
							{
								// Write config registers
								Ntag_I2C_Registers_t configReg;
								Ntag_I2C_Access_Registers_t accessReg;

									this->configRegBoxAccess->setLabel("Writing the configuration registers...");
									this->configRegBoxAccess->parseBoxAccess(&configReg, &accessReg);
									if (this->authenticated) this->my_api->setAuthentication(this->password);
									lReturn = my_api->WriteAccessRegisters(accessReg);
									Sleep(500);
									if (this->authenticated) this->my_api->setAuthentication(this->password);
									lReturn = my_api->WriteConfigRegisters(configReg);
									Sleep(500);
									if (lReturn == SCARD_S_SUCCESS)
									{
										this->configRegBoxAccess->setLabel("Write completed successfully");
										Sleep(1000);
										this->configRegBoxAccess->setLabel("");
									}

									configRegBoxAccess->pressed = false;
								
								this->taghandler->endWait = true;
							}
							else
							{
								//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
							}
						}
					}
				}
				else
				{
					if (configRegBoxAccess->grackButton1->isActive)
					{
						if (configRegBoxAccess->g1wasActive)
						{
							if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
							{
								if (checkStatus())
								{
									showWindowAuth();
								}
							}
							if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
							{
								if (firstREG)
								{
									firstREG = false;
									// Read config registers
									Ntag_I2C_Registers_t configReg;
									Ntag_I2C_Access_Registers_t accessReg;
									if (this->authenticated) this->my_api->setAuthentication(this->password);
									lReturn = my_api->ReadConfigRegisters(&configReg);
									Sleep(500);
									if (lReturn == SCARD_S_SUCCESS)
									{
										this->configRegBoxAccess->setLabel("Reading the configuration registers...");
										if (this->authenticated) this->my_api->setAuthentication(this->password);
										lReturn = my_api->ReadAccessRegisters(&accessReg);
										Sleep(500);
										this->configRegBoxAccess->updateBoxAccess(configReg, accessReg);
										this->configRegBoxAccess->setLabel("Read completed successfully");
										Sleep(1000);
										this->configRegBoxAccess->setLabel("");
									}
								}
								else
								{
									this->countCheck = checkConnection();
									if (this->countCheck >= 4)
									{
										this->taghandler->tagOut = true;
										this->checkTag = false;
										this->firstTime = true;
										firstTimeFalse = true;
									}
								}

								this->taghandler->endWait = true;
							}
							else
							{
								//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
							}
						}
					}
					else
					{
						if (configRegBoxAccess->g2wasActive)
						{
							if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
							{
								if (checkStatus())
								{
									showWindowAuth();
								}
							}
							if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
							{
								if (firstREG)
								{
									firstREG = false;
								// Write config registers
								Ntag_I2C_Registers_t configReg;
								Ntag_I2C_Access_Registers_t accessReg;

									this->configRegBoxAccess->setLabel("Writing the configuration registers...");
									this->configRegBoxAccess->parseBoxAccess(&configReg, &accessReg);
									if (this->authenticated) this->my_api->setAuthentication(this->password);
									lReturn = my_api->WriteAccessRegisters(accessReg);
									Sleep(500);
									if (this->authenticated) this->my_api->setAuthentication(this->password);
									lReturn = my_api->WriteConfigRegisters(configReg);
									Sleep(500);
									if (lReturn == SCARD_S_SUCCESS)
									{
										this->configRegBoxAccess->setLabel("Write completed successfully");
										Sleep(1000);
										this->configRegBoxAccess->setLabel("");
									}
								}
								else
								{
									this->countCheck = checkConnection();
									if (this->countCheck >= 4)
									{
										this->taghandler->tagOut = true;
										this->checkTag = false;
										this->firstTime = true;
										firstTimeFalse = true;
									}
								}

								this->taghandler->endWait = true;
							}
							else
							{
								//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
							}
						}
					}
				}
			}
			else if (this->tapTagBoxRWConfigReg->Visible)
			{
				if ((my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
				{
					if (checkStatus())
					{
						showWindowAuth();
					}
				}
				if (((this->authenticated == true) && (this->tagBlocked == true)) || ((this->authenticated == false) && (this->tagBlocked == false)))
				{
					if (firstREG)
					{
						firstREG = false;
						// Read config registers
						this->tapTagBoxRWConfigReg->setLabel("Reading the configuration registers...");
						Ntag_I2C_Registers_t configReg;
						Ntag_I2C_Access_Registers_t accessReg;
						if (this->authenticated) this->my_api->setAuthentication(this->password);
						lReturn = my_api->ReadConfigRegisters(&configReg);
						Sleep(500);
						if (lReturn == SCARD_S_SUCCESS)
						{
							if ((this->my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (this->my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
							{
								if (this->authenticated) this->my_api->setAuthentication(this->password);
								lReturn = my_api->ReadAccessRegisters(&accessReg);
								Sleep(500);
								this->configRegBoxAccess->updateBoxAccess(configReg, accessReg);
								this->configRegBoxAccess->setLabel("");
								this->configRegBoxAccess->Show();
							}
							else
							{
								this->configRegBox1->updateBox(configReg);
								this->configRegBox1->setLabel("");
								this->configRegBox1->Show();
							}

							this->tapTagBoxRWConfigReg->Hide();
							taghandler->endWait = true;
						}
						else
						{
							//this->tapTagBoxReadSessionReg->setLabel("Error while reading the configuration registers");
						}
					}
					else
					{
						this->countCheck = checkConnection();
						if (this->countCheck >= 4)
						{
							this->taghandler->tagOut = true;
							this->checkTag = false;
							this->firstTime = true;
							firstTimeFalse = true;
						}
					}
					this->taghandler->endWait = true;
				}
				else if (this->protectedRead == false)
				{
					if (firstREG)
					{
						firstREG = false;
						// Read config registers
						this->tapTagBoxRWConfigReg->setLabel("Reading the configuration registers...");
						Ntag_I2C_Registers_t configReg;
						Ntag_I2C_Access_Registers_t accessReg;
						if (this->authenticated) this->my_api->setAuthentication(this->password);
						lReturn = my_api->ReadConfigRegisters(&configReg);
						Sleep(500);
						if (lReturn == SCARD_S_SUCCESS)
						{
							if ((this->my_api->GetVersion() == NTAG_VERSION_1K_PLUS) || (this->my_api->GetVersion() == NTAG_VERSION_2K_PLUS))
							{
								if (this->authenticated) this->my_api->setAuthentication(this->password);
								lReturn = my_api->ReadAccessRegisters(&accessReg);
								Sleep(500);
								this->configRegBoxAccess->updateBoxAccess(configReg, accessReg);
								this->configRegBoxAccess->setLabel("");
								this->configRegBoxAccess->Show();
							}
							else
							{
								this->configRegBox1->updateBox(configReg);
								this->configRegBox1->setLabel("");
								this->configRegBox1->Show();
							}

							this->tapTagBoxRWConfigReg->Hide();
							taghandler->endWait = true;
						}
						else
						{
							this->tapTagBoxReadSessionReg->setLabel("Error while reading the configuration registers");
						}
					}
					else
					{
						this->countCheck = checkConnection();
						if (this->countCheck >= 4)
						{
							this->taghandler->tagOut = true;
							this->checkTag = false;
							this->firstTime = true;
							firstTimeFalse = true;
						}
					}
					this->taghandler->endWait = true;
				}
				else
				{
					//MessageBox::Show("Please, untap the tag and authenticate again in the Led demo tab");
				}
			}
			else
			{
				/*this->countCheck = checkConnection();
				if (this->countCheck >= 4)
				{
					this->taghandler->tagOut = true;
					this->checkTag = false;
					this->firstTime = true;
					firstTimeFalse = true;
				}*/
				this->taghandler->endWait = true;
				this->countCheck = checkConnection();
				if (this->countCheck >= 4)
				{
					this->taghandler->tagOut = true;
					this->authenticated = false;
					this->checkTag = false;
					this->firstTime = true;
					firstTimeFalse = true;
					setLockIcon(1);
				}
				else
				{
					this->checkTag = true;
					this->taghandler->endWait = true;
				}
			}
		}
				
		LONG WaitForI2C()
		{
			// The reader can check if the microcontroller has finished reading by checking the bit SRAM_I2C_READY
			// As soon as the microcontroller finishes reading the SRAM the bit SRAM_I2C_READY is set to 1
			// The bit SRAM_I2C_READY is part of the session registers, located in sector 3
			// In order to avoid using the Sector Select commands, this has been implemented with timers
			System::Threading::Thread::Sleep(100);

			return SCARD_S_SUCCESS;
		}

		LONG FlashMemory(BYTE* newFW, int newFWLength, DWORD* flashBytes, float* flashTime, System::Windows::Forms::ProgressBar^ progressBar1)
		{
			LONG lReturn;
			BYTE sectorFW[SECTOR_SIZE];
			BYTE cmd[NTAG_MEM_SIZE_SRAM];
			BYTE resp[NTAG_MEM_SIZE_SRAM];
			  			
				*flashBytes = (int)ceil((float)(newFWLength + 2) / 4) * 4;
				*flashTime = (float)clock();
				
				// We divide the firmware in bunches of 4096 bytes, that will be written in one of the sectors of the microcontroller
				int nFlashSectors = newFWLength / SECTOR_SIZE + ((newFWLength % SECTOR_SIZE) == 0 ? 0 : 1);
				int h = 0;
				int j = 0;
				
				if (checkStatus())
				{
					showWindowAuth();
				}
				
				MessageBox::Show("Flashing in process. Please do not click on the screen, otherwise the application can freeze during flashing");

				do
				{
					// Write a whole sector onto the SRAM
					// Check if it is the last sector
					if (newFWLength - (h + 1) * SECTOR_SIZE < 0)
					{
						// If it is the last sector, we copy the remaining bytes of the firmware to the sectorFW array, and we fill the rest of the array with 0s
						memset(sectorFW, 0, SECTOR_SIZE);
						memcpy(sectorFW, newFW + h*SECTOR_SIZE, newFWLength % SECTOR_SIZE);
					}
					else
					{	// If it is not the last sector, we copy the corresponding sector of the firmware to the sectorFW arraw
						memcpy(sectorFW, newFW + h*SECTOR_SIZE, SECTOR_SIZE);
					}

					// Send SRAM command indicating that a whole new sector will be written
					int flashAddr = 0x4000 + h * SECTOR_SIZE;
					memset(cmd, 0, NTAG_MEM_SIZE_SRAM);
					cmd[52] = flashAddr >> 24 & 0xFF;
					cmd[53] = flashAddr >> 16 & 0xFF;
					cmd[54] = flashAddr >> 8 & 0xFF;
					cmd[55] = flashAddr & 0xFF;
					cmd[56] = SECTOR_SIZE >> 24 & 0xFF;
					cmd[57] = SECTOR_SIZE >> 16 & 0xFF;
					cmd[58] = SECTOR_SIZE >> 8 & 0xFF;
					cmd[59] = SECTOR_SIZE & 0xFF;
					cmd[60] = 'F';
					cmd[61] = 'P';
					
					Sleep(10);
					if (checkStatus())
					{
						my_api->setAuthentication(this->password);
						lReturn = my_api->sram->WriteSram(cmd);
					}
					else
					{
						lReturn = my_api->sram->WriteSram(cmd);
					}

					// Send several SRAM commands with the firmware of the sector indicated previously
					BYTE* pSectorFW = sectorFW;

					while (pSectorFW < sectorFW + SECTOR_SIZE && lReturn == SCARD_S_SUCCESS)
					{	
						// Wait for the microcontroller to process the information and to write the response into the SRAM
						lReturn = WaitForI2C();
						if (lReturn == SCARD_S_SUCCESS)
						{
							if (this->authenticated)
							{
								my_api->setAuthentication(this->password);
								lReturn = my_api->sram->WriteSram(pSectorFW);
							}
							else
							{
								lReturn = my_api->sram->WriteSram(pSectorFW);
							}
							progressBar1->PerformStep();
						}
						pSectorFW += NTAG_MEM_SIZE_SRAM;
					}
					if (lReturn == SCARD_S_SUCCESS)
					{
						// Wait for the microcontroller to process the information and to write the response into the SRAM
						lReturn = WaitForI2C();
						if (lReturn == SCARD_S_SUCCESS)
						{
							if (this->authenticated)
							{
								if (my_api->setAuthentication(this->password) == SCARD_S_SUCCESS)
								{
									Sleep(100);
									lReturn = my_api->Read_SRAM(resp);
									Sleep(100);
								}
							}
							else
							{
								Sleep(100);
								lReturn = my_api->Read_SRAM(resp);
								Sleep(100);
							}

							// Check if an error has occurred even though lReturn indicates success
							if (lReturn == SCARD_S_SUCCESS && (resp[60] != 'A' || resp[61] != 'C' || resp[62] != 'K'))
								lReturn = SCARD_E_COMM_DATA_LOST;
						}
					}

					h++;
				} while (h < nFlashSectors && lReturn == SCARD_S_SUCCESS);
				
				my_api->sram->checkIfSuccess(cmd, lReturn);
				*flashTime = (float)clock() - *flashTime;

			return lReturn;
		}
	
		System::Void setLockIcon(BYTE tagVersion)
		{
			if (this->firstTimeLockIcon && (tagVersion == NTAG_VERSION_1K_PLUS || tagVersion == NTAG_VERSION_2K_PLUS))
			{
				this->tagBlocked = checkStatus();
				this->firstTimeLockIcon = false;
			}

			switch (tagVersion)
			{
				//The locker is drawn in every tab

				case NTAG_VERSION_1K: 
					this->isTagPlus = false;
					this->tabLEDDemo->Controls->Remove(this->pictureLockGreen);
					this->tabLEDDemo->Controls->Remove(this->pictureUnlockGreen);
					this->tabLEDDemo->Controls->Remove(this->pictureLockRed);
					this->tabLEDDemo->Controls->Add(this->pictureUnlockBlack);
					this->tabLEDDemo->Controls->Add(this->groupBoxBoardConfig);

					this->tabNDEF->Controls->Remove(this->pictureLockGreen_NDEF);
					this->tabNDEF->Controls->Remove(this->pictureUnlockGreen_NDEF);
					this->tabNDEF->Controls->Remove(this->pictureLockRed_NDEF);
					this->tabNDEF->Controls->Add(this->pictureUnlockBlack_NDEF);
					this->tabNDEF->Controls->Add(this->groupBox7);

					this->tabSpeed->Controls->Remove(this->pictureLockGreen_Speed);
					this->tabSpeed->Controls->Remove(this->pictureUnlockGreen_Speed);
					this->tabSpeed->Controls->Remove(this->pictureLockRed_Speed);
					this->tabSpeed->Controls->Add(this->pictureUnlockBlack_Speed);
					this->tabSpeed->Controls->Add(this->groupBox4);

					this->tabConfig->Controls->Remove(this->pictureLockGreen_Config);
					this->tabConfig->Controls->Remove(this->pictureUnlockGreen_Config);
					this->tabConfig->Controls->Remove(this->pictureLockRed_Config);
					this->tabConfig->Controls->Add(this->pictureUnlockBlack_Config);
					this->tabConfig->Controls->Add(this->groupBox3);
				break;
				case NTAG_VERSION_2K: 
					this->isTagPlus = false;
					this->tabLEDDemo->Controls->Remove(this->pictureLockGreen);
					this->tabLEDDemo->Controls->Remove(this->pictureUnlockGreen);
					this->tabLEDDemo->Controls->Remove(this->pictureLockRed);
					this->tabLEDDemo->Controls->Add(this->pictureUnlockBlack);
					this->tabLEDDemo->Controls->Add(this->groupBoxBoardConfig);

					this->tabNDEF->Controls->Remove(this->pictureLockGreen_NDEF);
					this->tabNDEF->Controls->Remove(this->pictureUnlockGreen_NDEF);
					this->tabNDEF->Controls->Remove(this->pictureLockRed_NDEF);
					this->tabNDEF->Controls->Add(this->pictureUnlockBlack_NDEF);
					this->tabNDEF->Controls->Add(this->groupBox7);

					this->tabSpeed->Controls->Remove(this->pictureLockGreen_Speed);
					this->tabSpeed->Controls->Remove(this->pictureUnlockGreen_Speed);
					this->tabSpeed->Controls->Remove(this->pictureLockRed_Speed);
					this->tabSpeed->Controls->Add(this->pictureUnlockBlack_Speed);
					this->tabSpeed->Controls->Add(this->groupBox4);

					this->tabConfig->Controls->Remove(this->pictureLockGreen_Config);
					this->tabConfig->Controls->Remove(this->pictureUnlockGreen_Config);
					this->tabConfig->Controls->Remove(this->pictureLockRed_Config);
					this->tabConfig->Controls->Add(this->pictureUnlockBlack_Config);
					this->tabConfig->Controls->Add(this->groupBox3);
				break;
				case NTAG_VERSION_1K_PLUS: 
					this->isTagPlus = true;
					if (!(this->authenticated))
					{
						if (this->tagBlocked)
						{
							if (dpiX == 120)
							{
								this->pictureLockRed->Location = System::Drawing::Point(310, 3);
								this->pictureLockRed->Size = System::Drawing::Size(23, 23);
								this->pictureLockRed_NDEF->Location = System::Drawing::Point(310, 3);
								this->pictureLockRed_NDEF->Size = System::Drawing::Size(23, 23);
								this->pictureLockRed_Speed->Location = System::Drawing::Point(310, 3);
								this->pictureLockRed_Speed->Size = System::Drawing::Size(23, 23);
								this->pictureLockRed_Config->Location = System::Drawing::Point(310, 3);
								this->pictureLockRed_Config->Size = System::Drawing::Size(23, 23);
							}
							else
							{
								this->pictureLockRed->Location = System::Drawing::Point(230, 3);
								this->pictureLockRed->Size = System::Drawing::Size(18, 18);
								this->pictureLockRed_NDEF->Location = System::Drawing::Point(230, 3);
								this->pictureLockRed_NDEF->Size = System::Drawing::Size(18, 18);
								this->pictureLockRed_Speed->Location = System::Drawing::Point(230, 3);
								this->pictureLockRed_Speed->Size = System::Drawing::Size(18, 18);
								this->pictureLockRed_Config->Location = System::Drawing::Point(230, 3);
								this->pictureLockRed_Config->Size = System::Drawing::Size(18, 18);
							}
							
							this->tabLEDDemo->Controls->Remove(this->pictureUnlockBlack);
							this->tabLEDDemo->Controls->Remove(this->pictureUnlockGreen);
							this->tabLEDDemo->Controls->Remove(this->pictureLockGreen);

							this->tabLEDDemo->Controls->Add(this->pictureLockRed);
							this->tabLEDDemo->Controls->Add(this->groupBoxBoardConfig);
							
							this->tabNDEF->Controls->Remove(this->pictureUnlockBlack_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureUnlockGreen_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureLockGreen_NDEF);

							this->tabNDEF->Controls->Add(this->pictureLockRed_NDEF);
							this->tabNDEF->Controls->Add(this->groupBox7);

							this->tabSpeed->Controls->Remove(this->pictureUnlockBlack_Speed);
							this->tabSpeed->Controls->Remove(this->pictureUnlockGreen_Speed);
							this->tabSpeed->Controls->Remove(this->pictureLockGreen_Speed);

							this->tabSpeed->Controls->Add(this->pictureLockRed_Speed);
							this->tabSpeed->Controls->Add(this->groupBox4);

							this->tabConfig->Controls->Remove(this->pictureUnlockBlack_Config);
							this->tabConfig->Controls->Remove(this->pictureUnlockGreen_Config);
							this->tabConfig->Controls->Remove(this->pictureLockGreen_Config);

							this->tabConfig->Controls->Add(this->pictureLockRed_Config);
							this->tabConfig->Controls->Add(this->groupBox3);

							if (this->firstTime)
							{
								this->firstTime = false;
								System::Windows::Forms::DialogResult dr;
								Password_Form^ pwd = gcnew Password_Form(this->authenticated, this->tagBlocked);
								dr = pwd->ShowDialog();
								LONG lReturn;

								if (pwd->ReturnValue == "STAR")
								{
									this->password = "STAR";
									this->my_api->sram->pass_sram = "STAR";
									this->my_api->eeprom->pass_eeprom = "STAR";
									this->my_api->ndef->pass_ndef = "STAR";
									Sleep(500);
									lReturn = my_api->setAuthentication("STAR");
									if (lReturn == SCARD_S_SUCCESS)
									{
										this->my_api->sram->auth = true;
										this->my_api->sram->blocked = true;
										this->my_api->eeprom->auth = true;
										this->my_api->ndef->auth = true;
										this->my_api->eeprom->blocked = true;
										this->authenticated = true;
										this->tagBlocked = false;
									}
									else
										MessageBox::Show("Invalid authentication, please try again");
								}
								else if (pwd->ReturnValue == "SUN")
								{
									this->password = "SUN";
									this->my_api->sram->pass_sram = "SUN";
									this->my_api->eeprom->pass_eeprom = "SUN";
									this->my_api->ndef->pass_ndef = "SUN";
									Sleep(500);
									lReturn = my_api->setAuthentication("SUN");
									if (lReturn == SCARD_S_SUCCESS)
									{
										this->my_api->sram->auth = true;
										this->my_api->sram->blocked = true;
										this->my_api->ndef->auth = true;
										this->my_api->eeprom->auth = true;
										this->my_api->eeprom->blocked = true;
										this->authenticated = true;
										this->tagBlocked = false;
									}
									else
										MessageBox::Show("Invalid authentication, please try again");
								}
								else if (pwd->ReturnValue == "MOON")
								{
									this->password = "MOON";
									this->my_api->sram->pass_sram = "MOON";
									this->my_api->eeprom->pass_eeprom = "MOON";
									this->my_api->ndef->pass_ndef = "MOON";
									Sleep(500);
									lReturn = my_api->setAuthentication("MOON");
									if (lReturn == SCARD_S_SUCCESS)
									{
										this->my_api->sram->auth = true;
										this->my_api->sram->blocked = true;
										this->my_api->eeprom->auth = true;
										this->my_api->ndef->auth = true;
										this->my_api->eeprom->blocked = true;
										this->authenticated = true;
										this->tagBlocked = false;
									}
									else
										MessageBox::Show("Invalid authentication, please try again");
								}
								else
								{
									this->authenticated = false;
									this->tagBlocked = true;
								}
								this->taghandler->endWait = true;
							}
						}
						else
						{
							if (dpiX == 120)
							{
								this->pictureUnlockGreen->Location = System::Drawing::Point(310, 3);
								this->pictureUnlockGreen->Size = System::Drawing::Size(23, 23);
								this->pictureUnlockGreen_NDEF->Location = System::Drawing::Point(310, 3);
								this->pictureUnlockGreen_NDEF->Size = System::Drawing::Size(23, 23);
								this->pictureUnlockGreen_Speed->Location = System::Drawing::Point(310, 3);
								this->pictureUnlockGreen_Speed->Size = System::Drawing::Size(23, 23);
								this->pictureUnlockGreen_Config->Location = System::Drawing::Point(310, 3);
								this->pictureUnlockGreen_Config->Size = System::Drawing::Size(23, 23);
							}
							else
							{
								this->pictureUnlockGreen->Location = System::Drawing::Point(230, 3);
								this->pictureUnlockGreen->Size = System::Drawing::Size(18, 18);
								this->pictureUnlockGreen_NDEF->Location = System::Drawing::Point(230, 3);
								this->pictureUnlockGreen_NDEF->Size = System::Drawing::Size(18, 18);
								this->pictureUnlockGreen_Speed->Location = System::Drawing::Point(230, 3);
								this->pictureUnlockGreen_Speed->Size = System::Drawing::Size(18, 18);
								this->pictureUnlockGreen_Config->Location = System::Drawing::Point(230, 3);
								this->pictureUnlockGreen_Config->Size = System::Drawing::Size(18, 18);
							}

							this->tabLEDDemo->Controls->Remove(this->pictureUnlockBlack);
							this->tabLEDDemo->Controls->Remove(this->pictureLockGreen);
							this->tabLEDDemo->Controls->Remove(this->pictureLockRed);

							this->tabLEDDemo->Controls->Add(this->pictureUnlockGreen);
							this->tabLEDDemo->Controls->Add(this->groupBoxBoardConfig);

							this->tabNDEF->Controls->Remove(this->pictureUnlockBlack_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureLockGreen_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureLockRed_NDEF);

							this->tabNDEF->Controls->Add(this->pictureUnlockGreen_NDEF);
							this->tabNDEF->Controls->Add(this->groupBox7);

							this->tabSpeed->Controls->Remove(this->pictureUnlockBlack_Speed);
							this->tabSpeed->Controls->Remove(this->pictureLockGreen_Speed);
							this->tabSpeed->Controls->Remove(this->pictureLockRed_Speed);

							this->tabSpeed->Controls->Add(this->pictureUnlockGreen_Speed);
							this->tabSpeed->Controls->Add(this->groupBox4);

							this->tabConfig->Controls->Remove(this->pictureUnlockBlack_Config);
							this->tabConfig->Controls->Remove(this->pictureLockGreen_Config);
							this->tabConfig->Controls->Remove(this->pictureLockRed_Config);

							this->tabConfig->Controls->Add(this->pictureUnlockGreen_Config);
							this->tabConfig->Controls->Add(this->groupBox3);
						}
					}
					else
					{
						if (this->tagBlocked)
						{
							if (dpiX == 120)
							{
								this->pictureLockRed->Location = System::Drawing::Point(310, 3);
								this->pictureLockRed->Size = System::Drawing::Size(23, 23);
								this->pictureLockRed_NDEF->Location = System::Drawing::Point(310, 3);
								this->pictureLockRed_NDEF->Size = System::Drawing::Size(23, 23);
								this->pictureLockRed_Speed->Location = System::Drawing::Point(310, 3);
								this->pictureLockRed_Speed->Size = System::Drawing::Size(23, 23);
								this->pictureLockRed_Config->Location = System::Drawing::Point(310, 3);
								this->pictureLockRed_Config->Size = System::Drawing::Size(23, 23);
							}
							else
							{
								this->pictureLockRed->Location = System::Drawing::Point(230, 3);
								this->pictureLockRed->Size = System::Drawing::Size(18, 18);
								this->pictureLockRed_NDEF->Location = System::Drawing::Point(230, 3);
								this->pictureLockRed_NDEF->Size = System::Drawing::Size(18, 18);
								this->pictureLockRed_Speed->Location = System::Drawing::Point(230, 3);
								this->pictureLockRed_Speed->Size = System::Drawing::Size(18, 18);
								this->pictureLockRed_Config->Location = System::Drawing::Point(230, 3);
								this->pictureLockRed_Config->Size = System::Drawing::Size(18, 18);
							}

							this->tabLEDDemo->Controls->Remove(this->pictureUnlockBlack);
							this->tabLEDDemo->Controls->Remove(this->pictureUnlockGreen);
							this->tabLEDDemo->Controls->Remove(this->pictureLockGreen);

							this->tabLEDDemo->Controls->Add(this->pictureLockRed);
							this->tabLEDDemo->Controls->Add(this->groupBoxBoardConfig);

							this->tabNDEF->Controls->Remove(this->pictureUnlockBlack_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureUnlockGreen_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureLockGreen_NDEF);

							this->tabNDEF->Controls->Add(this->pictureLockRed_NDEF);
							this->tabNDEF->Controls->Add(this->groupBox7);

							this->tabSpeed->Controls->Remove(this->pictureUnlockBlack_Speed);
							this->tabSpeed->Controls->Remove(this->pictureUnlockGreen_Speed);
							this->tabSpeed->Controls->Remove(this->pictureLockGreen_Speed);

							this->tabSpeed->Controls->Add(this->pictureLockRed_Speed);
							this->tabSpeed->Controls->Add(this->groupBox4);

							this->tabConfig->Controls->Remove(this->pictureUnlockBlack_Config);
							this->tabConfig->Controls->Remove(this->pictureUnlockGreen_Config);
							this->tabConfig->Controls->Remove(this->pictureLockGreen_Config);

							this->tabConfig->Controls->Add(this->pictureLockRed_Config);
							this->tabConfig->Controls->Add(this->groupBox3);

						}
						else
						{
							if (dpiX == 120)
							{
								this->pictureLockGreen->Location = System::Drawing::Point(310, 3);
								this->pictureLockGreen->Size = System::Drawing::Size(23, 23);
								this->pictureLockGreen_NDEF->Location = System::Drawing::Point(310, 3);
								this->pictureLockGreen_NDEF->Size = System::Drawing::Size(23, 23);
								this->pictureLockGreen_Speed->Location = System::Drawing::Point(310, 3);
								this->pictureLockGreen_Speed->Size = System::Drawing::Size(23, 23);
								this->pictureLockGreen_Config->Location = System::Drawing::Point(310, 3);
								this->pictureLockGreen_Config->Size = System::Drawing::Size(23, 23);
							}
							else
							{
								this->pictureLockGreen->Location = System::Drawing::Point(230, 3);
								this->pictureLockGreen->Size = System::Drawing::Size(18, 18);
								this->pictureLockGreen_NDEF->Location = System::Drawing::Point(230, 3);
								this->pictureLockGreen_NDEF->Size = System::Drawing::Size(18, 18);
								this->pictureLockGreen_Speed->Location = System::Drawing::Point(230, 3);
								this->pictureLockGreen_Speed->Size = System::Drawing::Size(18, 18);
								this->pictureLockGreen_Config->Location = System::Drawing::Point(230, 3);
								this->pictureLockGreen_Config->Size = System::Drawing::Size(18, 18);
							}

							this->tabLEDDemo->Controls->Remove(this->pictureUnlockBlack);
							this->tabLEDDemo->Controls->Remove(this->pictureUnlockGreen);
							this->tabLEDDemo->Controls->Remove(this->pictureLockRed);

							this->tabLEDDemo->Controls->Add(this->pictureLockGreen);
							this->tabLEDDemo->Controls->Add(this->groupBoxBoardConfig);

							this->tabNDEF->Controls->Remove(this->pictureUnlockBlack_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureUnlockGreen_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureLockRed_NDEF);

							this->tabNDEF->Controls->Add(this->pictureLockGreen_NDEF);
							this->tabNDEF->Controls->Add(this->groupBox7);

							this->tabSpeed->Controls->Remove(this->pictureUnlockBlack_Speed);
							this->tabSpeed->Controls->Remove(this->pictureUnlockGreen_Speed);
							this->tabSpeed->Controls->Remove(this->pictureLockRed_Speed);

							this->tabSpeed->Controls->Add(this->pictureLockGreen_Speed);
							this->tabSpeed->Controls->Add(this->groupBox4);

							this->tabConfig->Controls->Remove(this->pictureUnlockBlack_Config);
							this->tabConfig->Controls->Remove(this->pictureUnlockGreen_Config);
							this->tabConfig->Controls->Remove(this->pictureLockRed_Config);

							this->tabConfig->Controls->Add(this->pictureLockGreen_Config);
							this->tabConfig->Controls->Add(this->groupBox3);
						}
					}
				break;
				case NTAG_VERSION_2K_PLUS: 
					this->isTagPlus = true;
					if (!(this->authenticated))
					{
						if (this->tagBlocked)
						{
							if (dpiX == 120)
							{
								this->pictureLockRed->Location = System::Drawing::Point(310, 3);
								this->pictureLockRed->Size = System::Drawing::Size(23, 23);
								this->pictureLockRed_NDEF->Location = System::Drawing::Point(310, 3);
								this->pictureLockRed_NDEF->Size = System::Drawing::Size(23, 23);
								this->pictureLockRed_Speed->Location = System::Drawing::Point(310, 3);
								this->pictureLockRed_Speed->Size = System::Drawing::Size(23, 23);
								this->pictureLockRed_Config->Location = System::Drawing::Point(310, 3);
								this->pictureLockRed_Config->Size = System::Drawing::Size(23, 23);
							}
							else
							{
								this->pictureLockRed->Location = System::Drawing::Point(230, 3);
								this->pictureLockRed->Size = System::Drawing::Size(18, 18);
								this->pictureLockRed_NDEF->Location = System::Drawing::Point(230, 3);
								this->pictureLockRed_NDEF->Size = System::Drawing::Size(18, 18);
								this->pictureLockRed_Speed->Location = System::Drawing::Point(230, 3);
								this->pictureLockRed_Speed->Size = System::Drawing::Size(18, 18);
								this->pictureLockRed_Config->Location = System::Drawing::Point(230, 3);
								this->pictureLockRed_Config->Size = System::Drawing::Size(18, 18);
							}

							this->tabLEDDemo->Controls->Remove(this->pictureUnlockBlack);
							this->tabLEDDemo->Controls->Remove(this->pictureUnlockGreen);
							this->tabLEDDemo->Controls->Remove(this->pictureLockGreen);

							this->tabLEDDemo->Controls->Add(this->pictureLockRed);
							this->tabLEDDemo->Controls->Add(this->groupBoxBoardConfig);

							this->tabNDEF->Controls->Remove(this->pictureUnlockBlack_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureUnlockGreen_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureLockGreen_NDEF);

							this->tabNDEF->Controls->Add(this->pictureLockRed_NDEF);
							this->tabNDEF->Controls->Add(this->groupBox7);

							this->tabSpeed->Controls->Remove(this->pictureUnlockBlack_Speed);
							this->tabSpeed->Controls->Remove(this->pictureUnlockGreen_Speed);
							this->tabSpeed->Controls->Remove(this->pictureLockGreen_Speed);

							this->tabSpeed->Controls->Add(this->pictureLockRed_Speed);
							this->tabSpeed->Controls->Add(this->groupBox4);

							this->tabConfig->Controls->Remove(this->pictureUnlockBlack_Config);
							this->tabConfig->Controls->Remove(this->pictureUnlockGreen_Config);
							this->tabConfig->Controls->Remove(this->pictureLockGreen_Config);

							this->tabConfig->Controls->Add(this->pictureLockRed_Config);
							this->tabConfig->Controls->Add(this->groupBox3);

							if (this->firstTime)
							{
								this->firstTime = false;
								System::Windows::Forms::DialogResult dr;
								Password_Form^ pwd = gcnew Password_Form(this->authenticated, this->tagBlocked);
								dr = pwd->ShowDialog();
								LONG lReturn;

								if (pwd->ReturnValue == "STAR")
								{
									this->password = "STAR";
									this->my_api->sram->pass_sram = "STAR";
									this->my_api->eeprom->pass_eeprom = "STAR";
									this->my_api->ndef->pass_ndef = "STAR";
									Sleep(500);
									lReturn = my_api->setAuthentication("STAR");
									if (lReturn == SCARD_S_SUCCESS)
									{
										this->my_api->sram->auth = true;
										this->my_api->sram->blocked = true;
										this->my_api->ndef->auth = true;
										this->my_api->eeprom->auth = true;
										this->my_api->eeprom->blocked = true;
										this->authenticated = true;
										this->tagBlocked = true;
									}
									else
										MessageBox::Show("Invalid authentication, please try again");
								}
								else if (pwd->ReturnValue == "SUN")
								{
									this->password = "SUN";
									this->my_api->sram->pass_sram = "SUN";
									this->my_api->eeprom->pass_eeprom = "SUN";
									this->my_api->ndef->pass_ndef = "SUN";
									Sleep(500);
									lReturn = my_api->setAuthentication("SUN");
									if (lReturn == SCARD_S_SUCCESS)
									{
										this->my_api->sram->auth = true;
										this->my_api->sram->blocked = true;
										this->my_api->ndef->auth = true;
										this->my_api->eeprom->auth = true;
										this->my_api->eeprom->blocked = true;
										this->authenticated = true;
										this->tagBlocked = true;
									}
									else
										MessageBox::Show("Invalid authentication, please try again");
								}
								else if (pwd->ReturnValue == "MOON")
								{
									this->password = "MOON";
									this->my_api->sram->pass_sram = "MOON";
									this->my_api->eeprom->pass_eeprom = "MOON";
									this->my_api->ndef->pass_ndef = "MOON";
									Sleep(500);
									lReturn = my_api->setAuthentication("MOON");
									if (lReturn == SCARD_S_SUCCESS)
									{
										this->my_api->sram->auth = true;
										this->my_api->sram->blocked = true;
										this->my_api->ndef->auth = true;
										this->my_api->eeprom->auth = true;
										this->my_api->eeprom->blocked = true;
										this->authenticated = true;
										this->tagBlocked = true;
									}
									else
										MessageBox::Show("Invalid authentication, please try again");
								}
								else
								{
									this->authenticated = false;
									this->tagBlocked = true;
								}
								this->taghandler->endWait = true;
							}
						}
						else
						{
							if (dpiX == 120)
							{
								this->pictureUnlockGreen->Location = System::Drawing::Point(310, 3);
								this->pictureUnlockGreen->Size = System::Drawing::Size(23, 23);
								this->pictureUnlockGreen_NDEF->Location = System::Drawing::Point(310, 3);
								this->pictureUnlockGreen_NDEF->Size = System::Drawing::Size(23, 23);
								this->pictureUnlockGreen_Speed->Location = System::Drawing::Point(310, 3);
								this->pictureUnlockGreen_Speed->Size = System::Drawing::Size(23, 23);
								this->pictureUnlockGreen_Config->Location = System::Drawing::Point(310, 3);
								this->pictureUnlockGreen_Config->Size = System::Drawing::Size(23, 23);
							}
							else
							{
								this->pictureUnlockGreen->Location = System::Drawing::Point(230, 3);
								this->pictureUnlockGreen->Size = System::Drawing::Size(18, 18);
								this->pictureUnlockGreen_NDEF->Location = System::Drawing::Point(230, 3);
								this->pictureUnlockGreen_NDEF->Size = System::Drawing::Size(18, 18);
								this->pictureUnlockGreen_Speed->Location = System::Drawing::Point(230, 3);
								this->pictureUnlockGreen_Speed->Size = System::Drawing::Size(18, 18);
								this->pictureUnlockGreen_Config->Location = System::Drawing::Point(230, 3);
								this->pictureUnlockGreen_Config->Size = System::Drawing::Size(18, 18);
							}

							this->tabLEDDemo->Controls->Remove(this->pictureUnlockBlack);
							this->tabLEDDemo->Controls->Remove(this->pictureLockGreen);
							this->tabLEDDemo->Controls->Remove(this->pictureLockRed);

							this->tabLEDDemo->Controls->Add(this->pictureUnlockGreen);
							this->tabLEDDemo->Controls->Add(this->groupBoxBoardConfig);

							this->tabNDEF->Controls->Remove(this->pictureUnlockBlack_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureLockGreen_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureLockRed_NDEF);

							this->tabNDEF->Controls->Add(this->pictureUnlockGreen_NDEF);
							this->tabNDEF->Controls->Add(this->groupBox7);

							this->tabSpeed->Controls->Remove(this->pictureUnlockBlack_Speed);
							this->tabSpeed->Controls->Remove(this->pictureLockGreen_Speed);
							this->tabSpeed->Controls->Remove(this->pictureLockRed_Speed);

							this->tabSpeed->Controls->Add(this->pictureUnlockGreen_Speed);
							this->tabSpeed->Controls->Add(this->groupBox4);

							this->tabConfig->Controls->Remove(this->pictureUnlockBlack_Config);
							this->tabConfig->Controls->Remove(this->pictureLockGreen_Config);
							this->tabConfig->Controls->Remove(this->pictureLockRed_Config);

							this->tabConfig->Controls->Add(this->pictureUnlockGreen_Config);
							this->tabConfig->Controls->Add(this->groupBox3);
						}
					}
					else
					{
						if (this->tagBlocked)
						{
							if (dpiX == 120)
							{
								this->pictureLockGreen->Location = System::Drawing::Point(310, 3);
								this->pictureLockGreen->Size = System::Drawing::Size(23, 23);
								this->pictureLockGreen_NDEF->Location = System::Drawing::Point(310, 3);
								this->pictureLockGreen_NDEF->Size = System::Drawing::Size(23, 23);
								this->pictureLockGreen_Speed->Location = System::Drawing::Point(310, 3);
								this->pictureLockGreen_Speed->Size = System::Drawing::Size(23, 23);
								this->pictureLockGreen_Config->Location = System::Drawing::Point(310, 3);
								this->pictureLockGreen_Config->Size = System::Drawing::Size(23, 23);
							}
							else
							{
								this->pictureLockGreen->Location = System::Drawing::Point(230, 3);
								this->pictureLockGreen->Size = System::Drawing::Size(18, 18);
								this->pictureLockGreen_NDEF->Location = System::Drawing::Point(230, 3);
								this->pictureLockGreen_NDEF->Size = System::Drawing::Size(18, 18);
								this->pictureLockGreen_Speed->Location = System::Drawing::Point(230, 3);
								this->pictureLockGreen_Speed->Size = System::Drawing::Size(18, 18);
								this->pictureLockGreen_Config->Location = System::Drawing::Point(230, 3);
								this->pictureLockGreen_Config->Size = System::Drawing::Size(18, 18);
							}

							this->tabLEDDemo->Controls->Remove(this->pictureUnlockBlack);
							this->tabLEDDemo->Controls->Remove(this->pictureUnlockGreen);
							this->tabLEDDemo->Controls->Remove(this->pictureLockRed);

							this->tabLEDDemo->Controls->Add(this->pictureLockGreen);
							this->tabLEDDemo->Controls->Add(this->groupBoxBoardConfig);

							this->tabNDEF->Controls->Remove(this->pictureUnlockBlack_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureUnlockGreen_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureLockRed_NDEF);

							this->tabNDEF->Controls->Add(this->pictureLockGreen_NDEF);
							this->tabNDEF->Controls->Add(this->groupBox7);

							this->tabSpeed->Controls->Remove(this->pictureUnlockBlack_Speed);
							this->tabSpeed->Controls->Remove(this->pictureUnlockGreen_Speed);
							this->tabSpeed->Controls->Remove(this->pictureLockRed_Speed);

							this->tabSpeed->Controls->Add(this->pictureLockGreen_Speed);
							this->tabSpeed->Controls->Add(this->groupBox4);

							this->tabConfig->Controls->Remove(this->pictureUnlockBlack_Config);
							this->tabConfig->Controls->Remove(this->pictureUnlockGreen_Config);
							this->tabConfig->Controls->Remove(this->pictureLockRed_Config);

							this->tabConfig->Controls->Add(this->pictureLockGreen_Config);
							this->tabConfig->Controls->Add(this->groupBox3);
						}
						else
						{
							if (dpiX == 120)
							{
								this->pictureUnlockGreen->Location = System::Drawing::Point(310, 3);
								this->pictureUnlockGreen->Size = System::Drawing::Size(23, 23);
								this->pictureUnlockGreen_NDEF->Location = System::Drawing::Point(310, 3);
								this->pictureUnlockGreen_NDEF->Size = System::Drawing::Size(23, 23);
								this->pictureUnlockGreen_Speed->Location = System::Drawing::Point(310, 3);
								this->pictureUnlockGreen_Speed->Size = System::Drawing::Size(23, 23);
								this->pictureUnlockGreen_Config->Location = System::Drawing::Point(310, 3);
								this->pictureUnlockGreen_Config->Size = System::Drawing::Size(23, 23);
							}
							else
							{
								this->pictureUnlockGreen->Location = System::Drawing::Point(230, 3);
								this->pictureUnlockGreen->Size = System::Drawing::Size(18, 18);
								this->pictureUnlockGreen_NDEF->Location = System::Drawing::Point(230, 3);
								this->pictureUnlockGreen_NDEF->Size = System::Drawing::Size(18, 18);
								this->pictureUnlockGreen_Speed->Location = System::Drawing::Point(230, 3);
								this->pictureUnlockGreen_Speed->Size = System::Drawing::Size(18, 18);
								this->pictureUnlockGreen_Config->Location = System::Drawing::Point(230, 3);
								this->pictureUnlockGreen_Config->Size = System::Drawing::Size(18, 18);
							}

							this->tabLEDDemo->Controls->Remove(this->pictureUnlockBlack);
							this->tabLEDDemo->Controls->Remove(this->pictureLockGreen);
							this->tabLEDDemo->Controls->Remove(this->pictureLockRed);

							this->tabLEDDemo->Controls->Add(this->pictureUnlockGreen);
							this->tabLEDDemo->Controls->Add(this->groupBoxBoardConfig);

							this->tabNDEF->Controls->Remove(this->pictureUnlockBlack_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureLockGreen_NDEF);
							this->tabNDEF->Controls->Remove(this->pictureLockRed_NDEF);

							this->tabNDEF->Controls->Add(this->pictureUnlockGreen_NDEF);
							this->tabNDEF->Controls->Add(this->groupBox7);

							this->tabSpeed->Controls->Remove(this->pictureUnlockBlack_Speed);
							this->tabSpeed->Controls->Remove(this->pictureLockGreen_Speed);
							this->tabSpeed->Controls->Remove(this->pictureLockRed_Speed);

							this->tabSpeed->Controls->Add(this->pictureUnlockGreen_Speed);
							this->tabSpeed->Controls->Add(this->groupBox4);

							this->tabConfig->Controls->Remove(this->pictureUnlockBlack_Config);
							this->tabConfig->Controls->Remove(this->pictureLockGreen_Config);
							this->tabConfig->Controls->Remove(this->pictureLockRed_Config);

							this->tabConfig->Controls->Add(this->pictureUnlockGreen_Config);
							this->tabConfig->Controls->Add(this->groupBox3);
						}
					}
				break;
				default: this->tabLEDDemo->Controls->Remove(this->pictureUnlockGreen);
					this->tabLEDDemo->Controls->Remove(this->pictureLockGreen);
					this->tabLEDDemo->Controls->Remove(this->pictureLockRed);
					this->tabLEDDemo->Controls->Add(this->pictureUnlockBlack);
					this->tabLEDDemo->Controls->Add(this->groupBoxBoardConfig);

					this->tabNDEF->Controls->Remove(this->pictureUnlockGreen_NDEF);
					this->tabNDEF->Controls->Remove(this->pictureLockGreen_NDEF);
					this->tabNDEF->Controls->Remove(this->pictureLockRed_NDEF);
					this->tabNDEF->Controls->Add(this->pictureUnlockBlack_NDEF);
					this->tabNDEF->Controls->Add(this->groupBox7);

					this->tabSpeed->Controls->Remove(this->pictureUnlockGreen_Speed);
					this->tabSpeed->Controls->Remove(this->pictureLockGreen_Speed);
					this->tabSpeed->Controls->Remove(this->pictureLockRed_Speed);
					this->tabSpeed->Controls->Add(this->pictureUnlockBlack_Speed);
					this->tabSpeed->Controls->Add(this->groupBox4);

					this->tabConfig->Controls->Remove(this->pictureUnlockGreen_Config);
					this->tabConfig->Controls->Remove(this->pictureLockGreen_Config);
					this->tabConfig->Controls->Remove(this->pictureLockRed_Config);
					this->tabConfig->Controls->Add(this->pictureUnlockBlack_Config);
					this->tabConfig->Controls->Add(this->groupBox3);

					this->label_LedDemoT_BoardStatus->Text = "Transfer: No\nTap a tag to read configuration";
					firstTimeFalse = true;
					this->firstTime = true;
					break;
			}
		}
		
		Void authenticate()
		{
			System::Windows::Forms::DialogResult dr;
			Password_Form^ pwd = gcnew Password_Form(this->authenticated, this->tagBlocked);
			dr = pwd->ShowDialog();
			LONG lReturn;

			if (pwd->ReturnValue == "STAR")
			{
				this->password = "STAR";
				Sleep(500);
				lReturn = my_api->setAuthentication("STAR");
				if (lReturn == SCARD_S_SUCCESS)
				{
					this->authenticated = true;
					this->tagBlocked = false;
				}
				else
					MessageBox::Show("Invalid authentication, please try again");
			}
			else if (pwd->ReturnValue == "SUN")
			{
				this->password = "SUN";
				Sleep(500);
				lReturn = my_api->setAuthentication("SUN");
				if (lReturn == SCARD_S_SUCCESS)
				{
					this->authenticated = true;
					this->tagBlocked = false;
				}
				else
					MessageBox::Show("Invalid authentication, please try again");
			}
			else if (pwd->ReturnValue == "MOON")
			{
				this->password = "MOON";
				Sleep(500);
				lReturn = my_api->setAuthentication("MOON");
				if (lReturn == SCARD_S_SUCCESS)
				{
					this->authenticated = true;
					this->tagBlocked = false;
				}
				else
					MessageBox::Show("Invalid authentication, please try again");
			}
		}

		int checkConnection()
		{
			int res;
			BYTE version;

			for (res = 0; res < 4; res++)
			{
				if (this->my_api->my_rf->GET_VERSION(&version) == SCARD_S_SUCCESS) break;
			}
			return res;
		}

		BOOLEAN checkStatus()
		{
			BYTE auth0[4];
			BOOLEAN ret;

			//Read AUTH0
			if (my_api->my_rf->FAST_READ(AUTH0_PAGE, AUTH0_PAGE, auth0) == SCARD_S_SUCCESS)
			{
				if (auth0[3] > 0xEB)
				{
					ret = false;
				}
				else
				{
					ret = true;
				}
			}
			else
			{
				ret = true;
			}

			return ret;
		}

		void showWindowAuth()
		{
			LONG lReturn;
			tagVersion = my_api->GetVersion();

				if ((!this->authenticated) && (tagVersion == NTAG_VERSION_1K_PLUS || tagVersion == NTAG_VERSION_2K_PLUS))
				{
						if (retu == SCARD_S_SUCCESS)
						{
							System::Windows::Forms::DialogResult dr;
							Password_Form^ pwd = gcnew Password_Form(this->authenticated, this->tagBlocked);
							dr = pwd->ShowDialog();

							if (pwd->ReturnValue == "STAR")
							{
								this->password = "STAR";
								this->my_api->sram->pass_sram = "STAR";
								this->my_api->eeprom->pass_eeprom = "STAR";
								this->my_api->ndef->pass_ndef = "STAR";
								Sleep(500);
								lReturn = my_api->setAuthentication("STAR");
								if (lReturn == SCARD_S_SUCCESS)
								{
									this->my_api->sram->auth = true;
									this->my_api->sram->blocked = true;
									this->my_api->eeprom->auth = true;
									this->my_api->ndef->auth = true;
									this->my_api->eeprom->blocked = true;
									this->authenticated = true;
									this->tagBlocked = false;
								}
								else
								{
									MessageBox::Show("Invalid authentication, please try again");
								}
							}
							else if (pwd->ReturnValue == "SUN")
							{
								this->password = "SUN";
								this->my_api->sram->pass_sram = "SUN";
								this->my_api->eeprom->pass_eeprom = "SUN";
								this->my_api->ndef->pass_ndef = "SUN";
								Sleep(500);
								lReturn = my_api->setAuthentication("SUN");
								if (lReturn == SCARD_S_SUCCESS)
								{
									this->my_api->sram->auth = true;
									this->my_api->sram->blocked = true;
									this->my_api->ndef->auth = true;
									this->my_api->eeprom->auth = true;
									this->my_api->eeprom->blocked = true;
									this->authenticated = true;
									this->tagBlocked = false;
								}
								else
								{
									MessageBox::Show("Invalid authentication, please try again");
								}
							}
							else if (pwd->ReturnValue == "MOON")
							{
								this->password = "MOON";
								this->my_api->sram->pass_sram = "MOON";
								this->my_api->eeprom->pass_eeprom = "MOON";
								this->my_api->ndef->pass_ndef = "MOON";
								Sleep(500);
								lReturn = my_api->setAuthentication("MOON");
								if (lReturn == SCARD_S_SUCCESS)
								{
									this->my_api->sram->auth = true;
									this->my_api->sram->blocked = true;
									this->my_api->eeprom->auth = true;
									this->my_api->ndef->auth = true;
									this->my_api->eeprom->blocked = true;
									this->authenticated = true;
									this->tagBlocked = false;
								}
								else
								{
									MessageBox::Show("Invalid authentication, please try again");
								}
							}
						}
				}
		}
	};

}
