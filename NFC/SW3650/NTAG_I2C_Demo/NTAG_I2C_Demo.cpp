#include "stdafx.h"
#include "GUI_Utils.h"
#include "NTAG_I2C_Demo_GUI.h"

using namespace NTAG_I2C_Demo;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{

	try{
		// Enabling Windows visual effects before any controls are created
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		// Create the main window and run it
		Application::Run(gcnew NTAG_I2C_Demo_GUI());
	}
	catch (ObjectDisposedException^)
	{
	}

	return 0;
}
