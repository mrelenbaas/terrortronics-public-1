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

/** @file usb.c
 *  @brief Function prototypes for the console driver.
 *
 *  This contains the prototypes for the console
 *  driver and eventually any macros, constants,
 *  or global variables you will need.
 *
 *  @author Harry Q. Bovik (hqbovik)
 *  @author Fred Hacker (fhacker)
 *  @bug No known bugs.
 */
 // https://stackoverflow.com/questions/10192903/time-in-milliseconds-in-c

#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>
#include <windows.h>
#include <sys/time.h>

struct timespec start, end;

struct timespec timeAtStart;
uint64_t timeSinceStart;
uint64_t TIME_MAX = 1000000;
struct timespec timeNow;
int fpsPrevious;
int fpsCurrent;
uint64_t delta_us;
uint64_t timeDelta;

/**
 * The main function.
 */
int main()
{
  clock_gettime(CLOCK_MONOTONIC, &start);
  clock_gettime(CLOCK_MONOTONIC, &end);

  while(1)
  {
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
      printf("%u\n", fpsPrevious); 
    }
    else
    {
      fpsCurrent++;
    }
  }

  //printf("%I64u\n", delta_us); 

  // Exit.
  return 0;
}
