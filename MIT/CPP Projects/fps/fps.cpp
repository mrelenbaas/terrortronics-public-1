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
 * This file observes the no License.
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
