/*
 * Title: usb file.
 * Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * Version: 2
 * Date: September 15, 2023
 *
 * Intellectual Property:
 * Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 *
 * License:
 * This file is owned by Terrortronics / Bradley Elenbaas.
 * This file observes the MIT License.
 */
 
 /**
   @file usb.cpp

   @mainpage usb

   @section author Attribution
   - Title: FPS file.
   - Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   - Version: 2
   - Date: November 6, 2023.

   @section ip Intellectual Property
   - Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

   @section license License
   Permission is hereby granted, free of charge, to any person
   obtaining a copy of this software and associated documentation files
   (the “Software”), to deal in the Software without restriction,
   including without limitation the rights to use, copy, modify, merge,
   publish, distribute, sublicense, and/or sell copies of the Software,
   and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

   @section description Description
   Empty.

   @section pins Pins
   - empty

   @section resources Resources
   - https://playground.arduino.cc/Interfacing/CPPWindows/

   @section warnings WARNINGS
   - empty
*/

#include "usb.h"

Serial::Serial(const char *portName)
{
    //We're not yet connected
    this->connected = false;

    //Try to connect to the given port throuh CreateFile
    this->hSerial = CreateFile(portName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

    //Check if the connection was successfull
    if(this->hSerial==INVALID_HANDLE_VALUE)
    {
        //If not success full display an Error
        if(GetLastError()==ERROR_FILE_NOT_FOUND){

            //Print Error if neccessary
            printf(" ERROR: Handle was not attached. Reason: %s not available.\n", portName);

        }
        else
        {
            printf(" ERROR!!!\n");
        }
    }
    else
    {
        //If connected we try to set the comm parameters
        DCB dcbSerialParams = {0};

        //Try to get the current
        if (!GetCommState(this->hSerial, &dcbSerialParams))
        {
            //If impossible, show an error
            printf("failed to get current serial parameters!\n");
        }
        else
        {
            //Define serial connection parameters for the arduino board
            dcbSerialParams.BaudRate=BAUD_RATE;
            dcbSerialParams.ByteSize=8;
            dcbSerialParams.StopBits=ONESTOPBIT;
            dcbSerialParams.Parity=NOPARITY;
            //Setting the DTR to Control_Enable ensures that the Arduino is properly
            //reset upon establishing a connection
            dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

             //Set the parameters and check for their proper application
             if(!SetCommState(hSerial, &dcbSerialParams))
             {
                printf("ALERT: Could not set Serial Port parameters\n");
             }
             else
             {
                 //If everything went fine we're connected
                 this->connected = true;
                 //Flush any remaining characters in the buffers 
                 PurgeComm(this->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
             }
        }
    }

}

Serial::~Serial()
{
    //Check if we are connected before trying to disconnect
    if(this->connected)
    {
        //We're no longer connected
        this->connected = false;
        //Close the serial handler
        CloseHandle(this->hSerial);
    }
}

int Serial::ReadData(char *buffer, unsigned int nbChar)
{
    //Number of bytes we'll have read
    DWORD bytesRead;
    //Number of bytes we'll really ask to read
    unsigned int toRead;

    //Use the ClearCommError function to get status info on the Serial port
    ClearCommError(this->hSerial, &this->errors, &this->status);

    //Check if there is something to read
    if(this->status.cbInQue>0)
    {
        //If there is we check if there is enough data to read the required number
        //of characters, if not we'll read only the available characters to prevent
        //locking of the application.
        if(this->status.cbInQue>nbChar)
        {
            toRead = nbChar;
        }
        else
        {
            toRead = this->status.cbInQue;
        }

        //Try to read the require number of chars, and return the number of read bytes on success
        if(ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL) )
        {
            return bytesRead;
        }

    }

    //If nothing has been read, or that an error was detected return 0
    return 0;

}


bool Serial::WriteData(const char *buffer, unsigned int nbChar)
{
    DWORD bytesSend;

    //Try to write the buffer on the Serial port
    if(!WriteFile(this->hSerial, (void *)buffer, nbChar, &bytesSend, 0))
    {
        //In case it don't work get comm error and return false
        ClearCommError(this->hSerial, &this->errors, &this->status);

        return false;
    }
    else
        return true;
}

bool Serial::IsConnected()
{
    //Simply return the connection status
    return this->connected;
}

// application reads from the specified serial port and reports the collected data
/**
 * The main function.
*/
int _tmain(int argc, _TCHAR* argv[])
{
  int timeAtStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  int timeSinceStart = 0;
  int fpsPrevious = 0;
  int fpsCurrent = 0;
  
  printf("Welcome to the serial test app!\n\n");
  
  char device[] = {'\\', '\\', '.', '\\', 'C', 'O', 'M', '\0', '\0', '\0', '\0'};
  Serial* SP;
  for(int i = 2; i < 256; ++i)
  {
    if (i < 10)
    {
      device[7] = 48 + i;
      device[8] = '\0';
      device[9] = '\0';
    }
    else if (i < 100)
    {
      device[7] = 48 + (i / 10);
      device[8] = 48 + (i % 10);
      device[9] = '\0';
    }
    else
    {
      device[7] = 48 + (i / 100);
      device[8] = 48 + (i % 100 / 10);
      device[9] = 48 + (i % 100 % 10);
    }
    printf(device);
    
    SP = new Serial(device);
    if (SP->IsConnected())
		{
      printf("We're connected\n");
      break;
    }
    else
    {
      //i++;
      printf("\n");
    }
  }

	if (SP->IsConnected())
		printf("We're connected\n");

  while (isRunning && SP->IsConnected()) {
    timeSinceStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - timeAtStart;
    if (timeSinceStart >= 1000) {
      fpsPrevious = fpsCurrent;
      fpsCurrent = 0;
      timeAtStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
      std::cout << "FPS: " << fpsPrevious << "s\n";
    } else {
      ++fpsCurrent;
    }
  
    milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    readResult = SP->ReadData(incomingData, dataLength);
    incomingData[readResult] = 0;
    if(strcmp(incomingData, "\n") != 0)
    {
      std::cout << incomingData;
    }
    else
    {
      std::cout << std::endl;
    }
  }
	return 0;
}
