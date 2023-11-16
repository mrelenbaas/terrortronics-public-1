/*
 * Title: JoystickDiscovery file.
 * Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * Version: 2
 * Date: September 15, 2023
 *
 * Intellectual Property:
 * Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 *
 * License:
 * This file is owned by Terrortronics / Bradley Elenbaas.
 * This file observes the Unity License.
 */

using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.XR;

public class JoystickDiscovery : MonoBehaviour
{
    [SerializeField]
    private USB arduinoIO;

    private const int JOYSTICK_MAX = 4;

    private static Vector3[] joysticks = new Vector3[JOYSTICK_MAX];

    private int joystickIndex;
    private bool isBlocked;
    private bool isExitBlocked;

    Process process = null;
    StreamWriter messageStream;

    private const int SW_SHOWNORMAL = 1;

    [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
    private static extern bool ShowWindow(IntPtr hwnd, int nCmdShow);

    [DllImport("user32.dll", SetLastError = true)]
    private static extern bool SetForegroundWindow(IntPtr hwnd);


    void Start()
    {
        for (var i = 0; i < JOYSTICK_MAX; i++)
        {
            joysticks[i] = new Vector3(
                0.0f,
                0.0f,
                0.0f);
        }
    }

    /// <summary>
    /// The main loop.
    /// </summary>
    /// <remarks>
    /// ## Remarks
    /// None.
    /// </remarks>
    void Update()
    {
        if (joystickIndex >= 4)
        {
            if (process == null)
            {
                //StartProcessWrapper();
            }
        }
        try
        {
            var j = joystickIndex + 1;
            //print(Input.GetJoystickNames()[joystickIndex] + "[" + joystickIndex + "]: " + Input.GetAxis("JoyStick" + j + "_Horizontal"));
            joystickIndex++;
        }
        catch (System.Exception e)
        {

        }
        for (int i = 0; i < joystickIndex; i++)
        {
            var j = i + 1;
            if (j > 4)
            {
                return;
            }
            if (Mathf.Abs(Input.GetAxis("JoyStick" + j + "_Horizontal")) != 0)
            {
                //print(Input.GetJoystickNames()[i] + "[" + i + "]: " + Input.GetAxis("JoyStick" + j + "_Horizontal"));
            }
            if (Mathf.Abs(Input.GetAxis("JoyStick" + j + "_Vertical")) != 0)
            {
                //print(Input.GetJoystickNames()[i] + "[" + i + "]: " + Input.GetAxis("JoyStick" + j + "_Vertical"));
            }
            joysticks[i] = new Vector3(
                Input.GetAxis("JoyStick" + j + "_Horizontal"),
                0.0f,
                Input.GetAxis("JoyStick" + j + "_Vertical"));
        }
    }

    public static Vector3 GetJoystick(int index)
    {
        return new Vector3(
            joysticks[index].x,
            joysticks[index].y,
            joysticks[index].z);
    }

    void CheckProcess()
    {
        if (process.HasExited
            && !isExitBlocked)
        {
            isBlocked = false;
            print("Game Has Exited");
            isExitBlocked = true;
        }
    }

    private void SetForeground(Process process)
    {
        ShowWindow(process.MainWindowHandle, SW_SHOWNORMAL);
        SetForegroundWindow(process.MainWindowHandle);
    }

    public void StartProcessWrapper(string filename)
    {
        if (isBlocked)
        {
            return;
        }
        isBlocked = true;
        isExitBlocked = false;
        if (filename.Contains("Veridian Expanse"))
        {
            process = StartProcess("C:\\Users\\mrele\\Desktop\\TCTA\\GAMESTART.BAT");
        }
        else if (filename.Contains("Thetawave"))
        {
            process = StartProcess("C:\\Users\\mrele\\Desktop\\TCTA\\GAMESTART2.BAT");
        }
        else if (filename.Contains("arcadeCabinet"))
        {
            process = StartProcess("C:\\Users\\mrele\\Desktop\\TCTA\\GAMESTART3.BAT");
        }
        else if (filename.Contains("unnamedCookieClicker"))
        {
            process = StartProcess("C:\\Users\\mrele\\Desktop\\TCTA\\GAMESTART4.BAT");
        }
        else if (filename.Contains("fancyBox"))
        {
            process = StartProcess("C:\\Users\\mrele\\Desktop\\TCTA\\GAMESTART5.BAT");
        }
        else if (filename.Equals("usb"))
        {
            process = StartProcess("C:\\Users\\mrele\\Desktop\\TCTA\\GAMESTART6.BAT");
        }
        else
        {
            process = StartProcess(filename);
        }
        InvokeRepeating("CheckProcess", 0.0f, 1.0f);
    }
    Process StartProcess(string filename)
    {
        Process tempProcess = null;
        try
        {
            tempProcess = new Process();
            tempProcess.EnableRaisingEvents = false;
            tempProcess.StartInfo.FileName = filename;
            tempProcess.StartInfo.UseShellExecute = false;
            tempProcess.StartInfo.RedirectStandardOutput = true;
            tempProcess.StartInfo.RedirectStandardInput = true;
            tempProcess.StartInfo.RedirectStandardError = true;
            tempProcess.OutputDataReceived += new DataReceivedEventHandler(DataReceived);
            tempProcess.ErrorDataReceived += new DataReceivedEventHandler(ErrorReceived);
            tempProcess.Start();
            tempProcess.BeginOutputReadLine();
            messageStream = tempProcess.StandardInput;
            //SetForeground(tempProcess);
            //arduinoIO.AltTab();
            UnityEngine.Debug.Log("Successfully launched app");
        }
        catch (Exception e)
        {
            UnityEngine.Debug.LogError("Unable to launch app: " + e.Message);
        }
        return tempProcess;
    }

    void DataReceived(object sender, DataReceivedEventArgs eventArgs)
    {
        // Handle it
    }


    void ErrorReceived(object sender, DataReceivedEventArgs eventArgs)
    {
        UnityEngine.Debug.LogError(eventArgs.Data);
    }


    void OnApplicationQuit()
    {
        if (process != null && !process.HasExited)
        {
            process.Kill();
        }
    }
}
