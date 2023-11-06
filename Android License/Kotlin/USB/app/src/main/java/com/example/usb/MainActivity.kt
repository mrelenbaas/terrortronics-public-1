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

package com.example.usb

// https://developer.android.com/guide/topics/connectivity/usb/host#kotlin
// http://android-er.blogspot.com/2014/09/send-data-from-android-to-arduino-uno.html

import android.content.Context
import android.hardware.usb.UsbDevice
import android.hardware.usb.UsbManager
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.usb.ui.theme.USBTheme

/**
 * The main function.
 */
class MainActivity : ComponentActivity() {
    var name2: String = "Holmes, Sherlock"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            USBTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    Greeting(name2)
                }
            }
        }
        var temp = ""
        Log.d("TAGXYG", "START")
        name2 = "START"

        //val device: UsbDevice? = intent.getParcelableExtra(UsbManager.EXTRA_DEVICE)
        // vendor-id="9025" product-id="0067"

        val manager = getSystemService(Context.USB_SERVICE) as UsbManager
        //val deviceList = manager.getDeviceList()
        //val device = deviceList.get("deviceName")
        //val manager = getSystemService(Context.USB_SERVICE) as UsbManager
        val deviceList: HashMap<String, UsbDevice> = manager.deviceList
        Log.d("TAGXYG", deviceList.toString())
        //name2 = deviceList.size.toString()
        name2 = deviceList.values.size.toString();
        //name2 = "SOMETHING"
        deviceList.values.forEach { device ->
            print("HERE")
            name2 = "HERE"
            //your code
            Log.d("TAGXYG", "message")
        }
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        //text = "Hello $name!",
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    USBTheme {
        Greeting("Android")
    }
}