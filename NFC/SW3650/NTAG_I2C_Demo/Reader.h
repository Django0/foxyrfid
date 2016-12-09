#ifndef Reader_H
#define Reader_H

#include <windows.h>
#include <winscard.h>

#define IOCTL_CCID_ESCAPE SCARD_CTL_CODE (0xDAC)

///
/// The namespace for all the classes
/// is the same: NTAG_I2C_Demo.
///

namespace NTAG_I2C_Demo {

	///
	/// Reader is the lowest layer of the project
	/// it will implement all the functionality of the reader
	/// (setting the context, initializing, releasing context, connections, etc.).
	///
	class Reader
	{
	public:

		SCARDCONTEXT* phContext; /**< This atribute will be a pointer to the current context. */
		LPCTSTR szReader; /**< This atribute refers to the current reader i.e. Identiv CLOUD 3700 F Contactless Reader. */
		SCARDHANDLE* phCardHandle; /**< This atribute will handle the communication between the reader and the card. */
		SCARD_IO_REQUEST* ppioSendPci; /**< This atribute will store the configuration of the PCI. */
		bool isReader; /**< This atribute is going to check if the reader is connected. */

		//Constructors
		Reader();

		Reader(LPCTSTR readerIdentifierString);

		/** @brief Sets the context of the reader.
		*
		*  This method will reserve memory for the reader
		*  and will establish the context.
		*
		*  @return EstablishContext result (if success it will be 0).
		*/
		long setContext();

		/** @brief Releases the context of the reader.
		*
		*  This method is used to release the context previously
		*  created in setContext(). This will free the memory reserved before.
		*
		*  @return ReleaseContext result (if success it will be 0).
		*/
		long releaseContext();
		
		/** @brief Reads the firmware version of the reader.
		*
		*  First of all we set a context for the communication,
		*  later we establish a connection in DIRECT mode and finally
		*  we send a command to the reader in order to get its FW version.
		*
		*  @param IdentivReaderFWversion is a pointer to the array that holds the firmware version of the reader.
		*  @return Returns a long value, if this value is 0 means that we have been able to read correctly the firmware of the reader.
		*/
		long readIdentivFWversion(char* IdentivReaderFWversion);

		/** @brief Connects with the tag in direct mode.
		*
		*  It will create memory space for the handler and
		*  if will try to connect in direct mode using the handler created.
		*
		*  @param pActiveProtocol is a pointer to the active protocol of the communication.
		*  @return Returns a long value, if this value is 0 means that we have been able to connect in direct mode.
		*/
		long cardConnect_DIRECT_Mode(DWORD* pActiveProtocol);

		/** @brief Connects with the tag in shared mode.
		*
		*  It will create memory space for the handler and
		*  if will try to connect in shared mode using the handler created.
		*
		*  @param pActiveProtocol is a pointer to the active protocol of the communication.
		*  @return Returns a long value, if this value is 0 means that we have been able to connect in shared mode.
		*/
		long cardConnect_SHARED_Mode(DWORD* pActiveProtocol);

		/** @brief Connects with the tag in exclusive mode.
		*
		*  It will create memory space for the handler and
		*  if will try to connect in exclusive mode using the handler created.
		*
		*  @param pActiveProtocol is a pointer to the active protocol of the communication.
		*  @return Returns a long value, if this value is 0 means that we have been able to connect in exclusive mode.
		*/
		long cardConnect_EXCLUSIVE_Mode(DWORD* pActiveProtocol);

		/** @brief Sets the PCI configuration.
		*
		*  It will reserve memory space and it will add there the protocol identifier and the PCI length.
		*
		*  @param nr_dwAP this value will set the protocol identifier.
		*/
		void sendPciConfig(DWORD nr_dwAP);

		/** @brief Transmits data to the card.
		*
		*  @param rpSendBuffer Buffer that stores the sent data.
		*  @param rSendLength Length of the sent data.
		*  @param rpRecvPci Received PCI.
		*  @param rpRecvBuffer Buffer that stores the received data.
		*  @param rpRecvLength Length of the received data.
		*  @return Returns a long value, if this value is 0 means that we have been able to transmit information to the card.
		*/
		long cardTransmit(LPCBYTE rpSendBuffer, DWORD rSendLength, LPSCARD_IO_REQUEST rpRecvPci, LPBYTE rpRecvBuffer, LPDWORD rpRecvLength);

		/** @brief Disconects the current tag.
		*
		*  @return Returns a long value, if this value is 0 means that we have been able to disconnect the card.
		*/
		long cardDisconnect();
		
		/** @brief Returns the value of the atribute 'isReader'
		*
		*  @return Returns a boolean with the value of the atribue 'isReader'.
		*/
		boolean isReaderConnected();

		/** @brief Gets the readers connected to the PC
		*
		*  @return Returns SCardListReaders listing the readers connected.
		*/
		long getConnectedReaders(LPTSTR* pmszReaders, DWORD* cch);

	};
}
#endif

