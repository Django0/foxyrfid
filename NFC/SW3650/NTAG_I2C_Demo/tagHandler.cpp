#include "tagHandler.h"
#include <Windows.h>

using namespace NTAG_I2C_Demo;

		// Constructor
		tagHandler::tagHandler(NTAG_I2C_API* api_in)
		{
			api = api_in;
			api->readerInit();
		}

		// Destructor
		tagHandler::~tagHandler()
		{
			api->releaseContext();
		}

		// Secondary thread
		void tagHandler::FireOnTag()
		{
			// PC/SC variables
			SCARD_READERSTATE sReaderState;
			memset(&sReaderState, 0, sizeof(SCARD_READERSTATE));
			sReaderState.szReader = this->api->my_rf->sCardReader->szReader;

			while (this->killThread == false)
			{
				this->endWait = false;

				// Wait until a tag is detected
				do
				{
					System::Threading::Thread::Sleep(100);
					SCardGetStatusChange(*this->api->my_rf->sCardReader->phContext, INFINITE, &sReaderState, 1);
				} while ((sReaderState.dwEventState & SCARD_STATE_PRESENT) != SCARD_STATE_PRESENT && this->killThread == false);
				if (this->killThread == false)
				{
					TagEvent(this, gcnew System::EventArgs());
					
					// Wait until the tag is lost
					do
					{
						System::Threading::Thread::Sleep(100);
						if (!this->killThread && this->isLedDemo)
						{
							TagEvent(this, gcnew System::EventArgs());
						}
					} while (!this->endWait && !this->killThread && !this->tagOut);
					if (this->tagOut)
					{
						this->tagOut = false;
					}
				}
			}
		}