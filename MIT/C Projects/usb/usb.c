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
   @file usb.c

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
   - https://stackoverflow.com/questions/1722112/what-are-the-most-common-naming-conventions-in-c
   - https://www.cs.cmu.edu/~410/doc/doxygen.html

   @section warnings WARNINGS
   - empty
*/

#include "usb.h"

#ifdef _WIN32
#else
  int open_serial_port(const char * device, uint32_t baud_rate)
  {
    int port = open(device, O_RDWR | O_NOCTTY);
    if (port == -1)
    {
          perror(device);
          return -1;
    }
    
    //int result = tcflush(port, TCIOFLUSH);
    //if (result)
    //{
    //  perror("tcflush failed");
    //}
    
    struct termios options;
    result = tcgetattr(port, &options);
    if (result)
    {
          perror("tcgetattr failed\n");
          close(port);
          return -1;
    }
    
    options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
    options.c_oflag &= ~(ONLCR | OCRNL);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    
    options.c_cc[VTIME] = TIMEOUT;
    options.c_cc[VMIN] = 0;
    
    switch (baud_rate)
    {
    case 4800:   cfsetospeed(&options, B4800);   break;
    case 9600:   cfsetospeed(&options, B9600);   break;
    case 19200:  cfsetospeed(&options, B19200);  break;
    case 38400:  cfsetospeed(&options, B38400);  break;
    case 115200: cfsetospeed(&options, B115200); break;
    default:
      fprintf(stderr, "warning: baud rate %u is not supported, using 9600.\n", baud_rate);
      cfsetospeed(&options, B9600);
      break;
    }
    cfsetispeed(&options, cfgetospeed(&options));
       
    result = tcsetattr(port, TCSANOW, &options);
    if (result)
    {
      perror("tcsetattr failed\n");
      close(port);
      return -1;
    }
    
    result = write(port, "0", 1);
    if (result != 1)
    {
      perror("failed to write to port\n");
      return -1;
    }
    else
    {
      printf("HERE HERE HERE\n");
    }
    
    return port;
  }
#endif

// TODO: Remember that this cannot be called "connect".
// Iterate through ports, and stop after the first success.
int connect_serial_port()
{
  // Definitions.
  int result = -1;
  // Loop through ports.
  for (int i = 0; i < DEVICE_MAX; i++)
  {
    #ifdef _WIN32
      // Define device.
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
      // Open port.
      port = CreateFileA(device, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      if (port == INVALID_HANDLE_VALUE)
      {
        printf("ERROR: Invalid handle value.\n");
        continue;
      }
      else
      {
        result = 0;
        break;
      }
    #else
      // Define device.
      if (i < 10)
      {
        device[11] = 48 + i;
        device[12] = '\0';
        device[13] = '\0';
      }
      else if (i < 100)
      {
        device[11] = 48 + (i / 10);
        device[12] = 48 + (i % 10);
        device[13] = '\0';
      }
      else
      {
        device[11] = 48 + (i / 100);
        device[12] = 48 + (i % 100 / 10);
        device[13] = 48 + (i % 100 % 10);
      }
      // Open port.
      port = open_serial_port(device, SERIAL_BAUD_RATE);
      result = tcflush(port, TCIOFLUSH);
      if (result)
      {
        perror("tcflush failed\n");
        continue;
      }
      else
      {
        result = 0;
        break;
      }
    #endif
  }
  return result;
}

/**
 * The main function.
 */
int main()
{
  for (int i = 0; i < INDEX_MAX; i++)
  {
    incomingChars[i] = '\0';
  }
  
  clock_gettime(CLOCK_MONOTONIC, &start);
  clock_gettime(CLOCK_MONOTONIC, &end);
  
  // Open port.
  if (connect_serial_port() == -1)
  {
    return -1;
  }
  
  // Flush port.
  #ifdef _WIN32
    success = FlushFileBuffers(port);
    if (!success)
    {
      printf("ERROR: Failed to flush serial port.\n");
      CloseHandle(port);
      return -1;
    }
  #else
  #endif
  
  // Set timeout.
  #ifdef _WIN32
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = TIMEOUT;
    timeouts.ReadTotalTimeoutConstant = 1;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    timeouts.WriteTotalTimeoutConstant = TIMEOUT;
    timeouts.WriteTotalTimeoutMultiplier = 0;
    success = SetCommTimeouts(port, &timeouts);
    if (!success)
    {
      printf("ERROR: Failed to set serial timeouts.\n");
      CloseHandle(port);
      return -1;
    }
  #else
  #endif
  
  // Set state.
  #ifdef _WIN32
    DCB state = {0};
    state.DCBlength = sizeof(DCB);
    state.BaudRate = SERIAL_BAUD_RATE;
    state.ByteSize = 8;
    state.Parity = NOPARITY;
    state.StopBits = ONESTOPBIT;
    success = SetCommState(port, &state);
    if (!success)
    {
      printf("ERROR: Failed to set serial settings.\n");
      CloseHandle(port);
      return -1;
    }
  #else
  #endif
  
  // Set start time.
  #ifdef _WIN32
    GetSystemTime(&currentTime);
  #else
  #endif
 
  // Set start time.
  #ifdef _WIN32
    while(isRunning)
  #else
    if (port < 0) { printf("ERROR: CONTINUE...\n"); }
    while(1)
  #endif
  //while(1)
  {
    // Update time.
    #ifdef _WIN32
      GetSystemTime(&currentTime);
      clock_gettime(CLOCK_MONOTONIC, &timeNow);
      timeSinceStart = (timeNow.tv_sec - timeAtStart.tv_sec) * 1000000 + (timeNow.tv_nsec - timeAtStart.tv_nsec) / 1000;
      delta_us = (timeNow.tv_sec - timeAtStart.tv_sec) * 1000000 + (timeNow.tv_nsec - timeAtStart.tv_nsec) / 1000;
      timeDelta += delta_us;
      //printf("--- %I64u\n", timeSinceStart); 
      //printf("--- %I64u >= %I64u (%I64u)\n", timeSinceStart, TIME_MAX, delta_us);
      if (timeSinceStart >= TIME_MAX)
      {
        fpsPrevious = fpsCurrent;
        fpsCurrent = 0;
        timeSinceStart = 0;
        clock_gettime(CLOCK_MONOTONIC, &timeAtStart);
        //printf("FPS: %u\n", fpsPrevious); 
      }
      else
      {
        fpsCurrent++;
      }
    #else
    #endif
    
    // Open port.
    #ifdef _WIN32
    #else
      if (connect_serial_port() == -1)
      {
        return -1;
      }
    #endif
    
    // Update incoming data.
    #ifdef _WIN32
      success = ReadFile(port, incomingBuffer, sizeof(incomingBuffer), &received, NULL);
      if (success && incomingBuffer[0] != INCOMING_BUFFER)
      {
        FILE *fp;
        fp = fopen("log.txt", "a");
        if ((int)incomingBuffer[0] != 10) {
          sprintf(incomingChar, "%c", incomingBuffer[0]);
          incomingChars[charIndex] = incomingBuffer[0];
          ++charIndex;
        } else {
          printf(
            "\n%02d %02d %02d %02d: ",
            currentTime.wHour,
            currentTime.wMinute,
            currentTime.wSecond,
            currentTime.wMilliseconds);
          printf(incomingChars);
          sprintf(hourTime, "%d", currentTime.wHour);
          sprintf(minuteTime, "%d", currentTime.wMinute);
          sprintf(secondTime, "%d", currentTime.wSecond);
          sprintf(millisecondsTime, "%d", currentTime.wMilliseconds);
          fputs(hourTime, fp);
          fputs(" ", fp);
          fputs(minuteTime, fp);
          fputs(" ", fp);
          fputs(secondTime, fp);
          fputs(" ", fp);
          fputs(millisecondsTime, fp);
          fputs(": ", fp);
          fputs(incomingChars, fp);
          for (int i = 0; i < INDEX_MAX; i++)
          {
            incomingChars[i] = '\0';
          }
          charIndex = 0;
        }
        fclose(fp);
        if ((int)incomingBuffer[0] == 36) {
          printf("GAME OVER RECEIVED\n");
          FILE *file = fopen("test3.txt", "r");
  
          char string[1000] = "";
          char str[256];
          unsigned long gameCount;
          char *end;
          fgets(string, sizeof(string), file);
          gameCount = strtoll(string, &end, 10);
          printf("%s\n", string);
          fclose(file);
  
          FILE *fp;
          fp = fopen("game_counter.txt", "w+");
          ++gameCount;
          sprintf(str, "%lu", gameCount);
          fputs(str, fp);
          fclose(fp);
        }
        incomingBuffer[0] = INCOMING_BUFFER;
      }
    #else
      r = read(port, incomingBuffer, sizeof(incomingBuffer));
      if (r < 0)
      {
        perror("failed to read from port\n");
      }
      printf("%c\n", incomingBuffer[0]);
    #endif
    
    if (is_running == 0)
    {
      // Update incoming data.
      #ifdef _WIN32
        success = WriteFile(port, "0", 4, &written, NULL);
      #else
        result = write(port, "0", 4);
        if (result != (ssize_t)4)
        {
          perror("failed to write to port\n");
          return -1;
        }
        else
        {
          is_running = 1;
        }
      #endif
    }
    if (is_running == 1)
    {
      // Update incoming data.
      #ifdef _WIN32
        success = WriteFile(port, "1", 4, &written, NULL);
      #else
        result = write(port, "1", 4);
        if (result != (ssize_t)4)
        {
          perror("failed to write to port\n");
          return -1;
        }
      #endif
    }
    
    // Close port.
    #ifdef _WIN32
    #else
      close(port);
    #endif
  }
  
  // Close port.
  #ifdef _WIN32
    CloseHandle(port);
  #else
  #endif

  // Exit.
  return 0;
}
