/*
 * Title: fps file.
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
   @file fps.ino

   @mainpage fps

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
   - empty

   @section warnings WARNINGS
   - empty
*/

#include <iostream>
#include <chrono>
using namespace std::chrono;

/**
 * The main function. 
 */
int main() {
    int timeAtStart = duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();
    int timeSinceStart = 0;
    int fpsPrevious = 0;
    int fpsCurrent = 0;
    
    std::cout << "Hello World!";

    while(true) {
        timeSinceStart = duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count() - timeAtStart;
        if (timeSinceStart >= 1000) {
          fpsPrevious = fpsCurrent;
          fpsCurrent = 0;
          timeAtStart = duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();
          std::cout << fpsPrevious << "s\n";
        } else {
          ++fpsCurrent;
        }
      
        milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
        //std::cout << ms.count() << "s\n";
        //std::cout << fpsPrevious << "s\n";
    }
    return 0;
}
