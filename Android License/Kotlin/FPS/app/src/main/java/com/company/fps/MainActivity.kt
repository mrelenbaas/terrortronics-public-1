/*
 * Title: MainActivity file.
 * Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * Version: 2
 * Date: September 15, 2023
 *
 * Intellectual Property:
 * Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 *
 * License:
 * This file is owned by Terrortronics / Bradley Elenbaas.
 * This file observes the Android License.
 */

package com.company.fps

import android.os.Bundle
import android.os.SystemClock
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity


// Original Source: https://www.youtube.com/watch?v=ICiLCEtiwnY&list=PLejN69rU111NiOAX74MS7-nSAIY3uoXYo&index=9&t=209s
/**
 * The main function.
 */
class MainActivity : AppCompatActivity() {

    private lateinit var tvText: TextView

    private var PERIOD = 1000L
    private var fpsPrevious = 0
    private var fpsCurrent = 0
    private var timePrevious = 0L
    private var timeCurrent = 0L
    private var timeDelta  = 0L
    private var timeThisSecond = 0L

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        tvText = findViewById(R.id.tv_text)
        timeCurrent = SystemClock.elapsedRealtime()
        timePrevious = timeCurrent
        timeCurrent = SystemClock.elapsedRealtime()
        timeDelta = timeCurrent - timePrevious;
        tvText.setOnTouchListener { _, event ->
            timePrevious = timeCurrent;
            timeCurrent = SystemClock.elapsedRealtime();
            timeDelta = timeCurrent - timePrevious;
            timeThisSecond += timeDelta;
            if (timeThisSecond >= PERIOD) {
                fpsPrevious = fpsCurrent;
                fpsCurrent = 0;
                timeThisSecond -= PERIOD;
                tvText.text = fpsPrevious.toString();
            } else {
                fpsCurrent++;
            }
            true
        }
    }
}