#include <Windows.h>
#include <iostream>
#include "BoardDemo.h"

#include "NTAG_I2C_API.h"

namespace NTAG_I2C_Demo {

	///
	/// This class will take care of the handle of the tag.
	///
	public ref class tagHandler
	{
	private:

		NTAG_I2C_API* api;

	public:
		event System::EventHandler^ TagEvent; /**< This atribute will set the event we tapping the tap. */
		event System::EventHandler^ TagRemovedEvent; /**< This atribute will set the event we untapping the tap. */
		bool isLedDemo = false; /**< Checks if we are in the LedDemo tab. */
		bool isReader = false; /**< Checks if a valid reader is connected. */
		bool endWait; /**< When we set this boolean to true, we generate a new TagEvent programmatically. */
		bool killThread = false; /**< This atribute will kill the current thread. */
		bool tagOut = false;
		bool isRedLock = false;
		bool lockRedIsOut = false;

		// Constructor
		tagHandler(NTAG_I2C_API* api_in);

		// Destructor
		~tagHandler();

		/** @brief Main method of tagHandler class.
		*
		*  This method will keep checking if the current thread isn't killed,
		*  meanwhile it will wait until a tag is detected. When it is detected
		*  it will generate a new TagEvent and will wait until the tag is lost (untapped),
		*  once it detects that the tag is lost, it calls TagRemovedEvent.
		*
		*/
		void FireOnTag();
	};
}