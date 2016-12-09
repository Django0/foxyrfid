#include <windows.h>
#include <conio.h>
#include <iostream>
#include "NTAG_I2C_API.h"
#include "BoardDemo.h"

namespace NTAG_I2C_Demo
{
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
			//Now we have to adapt the size of the window to the size of the screen
			if (dpiX == 120)
			{
				this->Size = System::Drawing::Size(365, 559);
				this->label1->Location = System::Drawing::Point(75, 263);
				this->label2->Location = System::Drawing::Point(55, 323);
				this->pictureBox1->Location = System::Drawing::Point(75, 94);
				this->button1->Location = System::Drawing::Point(140, 500);
			}
			else //dpiX == 96 for instance
			{
				this->Size = System::Drawing::Size(273, 455);
				this->label1->Location = System::Drawing::Point(30, 263);
				this->label2->Location = System::Drawing::Point(30, 323);
				this->pictureBox1->Location = System::Drawing::Point(23, 94);
				this->button1->Location = System::Drawing::Point(98, 408);
			}
			this->TabIndex = 0;
			this->TabStop = false;
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 11.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(200, 108);
			this->label1->TabIndex = 1;
			this->label1->Text = labelText;
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(240, 50);
			this->label2->TabIndex = 2;
			this->label2->BackColor = System::Drawing::Color::Black;
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->setLabel(this->label2Text);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = this->Logo;
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(225, 139);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->BackgroundImage = this->backImage;
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
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


}