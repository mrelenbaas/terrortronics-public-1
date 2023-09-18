/*
 * Title: USB file.
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
using System.IO;
using System.IO.Ports;
using System.Text;
using System.Threading;
using Unity.VisualScripting;
using UnityEditor;
using UnityEditor.VersionControl;
using UnityEngine;

/// <summary>
/// The USB library.
/// </summary>
public class USB : MonoBehaviour
{
    #region Debug Variables
    /// <summary>
    /// Check to print debug tracers to console.
    /// </summary>
    [SerializeField, Tooltip("Check to print debug tracers to console.")]
    private bool debug = false;
    #endregion

    #region Serial Variables
    /// <summary>
    /// Baud rates (pair with Arduino).
    /// </summary>
    private readonly int[] serialBaudRates = {
        9600,
        14400,
        19200,
        28800,
        31250,
        38400,
        57600,
        115200,
        300,
        600,
        1200,
        2400,
        4800,
    };
    /// <summary>
    /// Timeout for incoming data (milliseconds).
    /// </summary>
    private const int SERIAL_TIMEOUT = 1000;
    /// <summary>
    /// Minimum COM port (Windows).
    /// </summary>
    private const int SERIAL_POSTFIX_MIN_WINDOWS = 0;
    /// <summary>
    /// Minimum COM port (Linux).
    /// </summary>
    private const int SERIAL_POSTFIX_MIN_LINUX = 0;
    /// <summary>
    /// Minimum COM port (Mac).
    /// </summary>
    private const int SERIAL_POSTFIX_MIN_MAC = 0;
    /// <summary>
    /// Maximum COM port (Windows).
    /// </summary>
    private const int SERIAL_POSTFIX_MAX_WINDOWS = 256;
    /// <summary>
    /// Maximum COM port (Linux).
    /// </summary>
    private const int SERIAL_POSTFIX_MAX_LINUX = 256;
    /// <summary>
    /// Maximum COM port (Mac).
    /// </summary>
    private const int SERIAL_POSTFIX_MAX_MAC = 256;
    /// <summary>
    /// The device prefix (Windows).
    /// </summary>
    private const string SERIAL_PREFIX_WINDOWS = "COM";
    /// <summary>
    /// The device prefix (Linux).
    /// </summary>
    private const string SERIAL_PREFIX_LINUX = "/dev/ttyACM";
    /// <summary>
    /// The device prefix (Mac).
    /// </summary>
    private const string SERIAL_PREFIX_MAC = "";
    /// <summary>
    /// Successful serial port connections.
    /// </summary>
    private SerialPort[] serialPorts;
    #endregion

    #region Incoming Data
    /// <summary>
    /// A set of configs received from connected Arduinos.
    /// </summary>
    public static string[] Configs { get; private set; }
    /// <summary>
    /// Wait for incoming data using the Update() event function.
    /// </summary>
    private const int INCOMING_IN_UPDATE_FUNCTION = 0;
    /// <summary>
    /// Wait for incoming data using InvokeRepeating(string).
    /// </summary>
    private const int INCOMING_IN_INVOKED_FUNTION = 1;
    /// <summary>
    /// Wait for incoming data on a new thread.
    /// </summary>
    private const int INCOMING_IN_THREADED_FUNCTION = 2;
    /// <summary>
    /// Wait for incoming data on the UI thread.
    /// </summary>
    private const int INCOMING_IN_USER_INTERFACE_FUNCTION = 3;
    /// <summary>
    /// Enum of options for how to receive incoming data.
    /// </summary>
    public enum IncomingOption
    {
        UpdateFunction = INCOMING_IN_UPDATE_FUNCTION,
        InvokedFunction = INCOMING_IN_INVOKED_FUNTION,
        ThreadedFunction = INCOMING_IN_THREADED_FUNCTION,
        UserInterfaceFunction = INCOMING_IN_USER_INTERFACE_FUNCTION,
    };
    /// <summary>
    /// Choose when to receive incoming data.
    /// </summary>
    [SerializeField, Tooltip("Choose when to receive incoming data.")]
    private IncomingOption incomingOption;
    #endregion

    #region Outgoing Data
    /// <summary>
    /// Calls the Arduino's start() function.
    /// </summary>
    private const int OUTGOING_START = 0;
    /// <summary>
    /// Calls the Arduino's reset() function.
    /// </summary>
    private const int OUTGOING_RESET = 1;
    /// <summary>
    /// An enum of messages to be sent to any Arduino.
    /// </summary>
    /// <remarks>
    /// Max range of 256.
    /// Must be paired with a similar enum on Arduino.
    /// </remarks>
    public enum OutgoingMessages
    {
        Start = OUTGOING_START,
        Reset = OUTGOING_RESET,
    };
    #endregion

    #region Time
    #endregion

    #region Error
    #endregion

    #region Main Loop
    #endregion

    #region Thread Function Variables
    /// <summary>
    /// Incoming data from thread.
    /// </summary>
    public static string IncomingData { get; private set; } = "";
    /// <summary>
    /// A thread for <see cref="ThreadedFunction">ThreadedFunction()</see>.
    /// </summary>
    public static Thread threadedFunction;
    /// <summary>
    /// A mutex.
    /// </summary>
    private readonly Mutex mutex = new Mutex();
    #endregion

    #region Invoked Function Variables
    /// <summary>
    /// For use with InvokeRepeating(string, float, float) and CancelInvoke(string) functions.
    /// </summary>
    private const string INVOKED_FUNCTION = "ReceiveDatas";
    /// <summary>
    /// Delay between <see cref="ReceiveDatas">InvokedFunction()</see> calls.
    /// </summary>
    [SerializeField, Tooltip("Delay between InvokedFunction() calls.")]
    private float invokedFunctionDelay = 0.1f;
    #endregion

    #region Unity Event Functions
    /// <summary>
    /// Pseudo-Constructor.
    /// Calls the <see cref="ConnectSerialPorts">ConnectSerialPorts()</see> function.
    /// </summary>
    void Start()
    {
        EditorApplication.quitting += CloseSerialPorts;
        Application.targetFrameRate = 100000000;
        ConnectSerialPorts();
    }

    /// <summary>
    /// Pseudo-Destructor.
    /// Kills the <see cref="threadedFunction">threadedFunction</see> thread.
    /// </summary>
    private void OnApplicationQuit()
    {
        print("OnApplicationQuit");
        Teardown();
    }

    /// <summary>
    /// The user interface function.
    /// Receive incoming data.
    /// </summary>
    private void OnGUI()
    {
        switch (incomingOption)
        {
            case IncomingOption.UpdateFunction:
                break;
            case IncomingOption.InvokedFunction:
                break;
            case IncomingOption.ThreadedFunction:
                threadedFunction = new Thread(ThreadedFunction);
                threadedFunction.Start();
                break;
            case IncomingOption.UserInterfaceFunction:
                InvokedFunctionStart();
                break;
        }
    }

    /// <summary>
    /// The main function.
    /// Receive incoming data.
    /// </summary>
    private void Update()
    {
        switch (incomingOption)
        {
            case IncomingOption.UpdateFunction:
                for (var i = 0; i < serialPorts.Length; i++)
                {
                    ReceiveData(serialPorts[i], Configs[i], i);
                }
                break;
            case IncomingOption.InvokedFunction:
                break;
            case IncomingOption.ThreadedFunction:
                break;
            case IncomingOption.UserInterfaceFunction:
                break;
        }
        if (debug)
        {
            print(new StringBuilder()
                .Append("SUCCESS: incomingData: ")
                .Append(IncomingData)
                .ToString());
        }
    }
    #endregion

    #region Public Functions
    #endregion

    #region Private Functions
    /// <summary>
    /// Catenates the platform specific prefix and the iterated postfix.
    /// </summary>
    /// <remarks>
    /// Warning: In a UNITY_EDITOR_WIN build, the UNITY_STANDALONE_WIN section is being
    /// reached erroneously.
    /// </remarks>
    /// <param name="postfix">The iterated postfix.</param>
    /// <returns>
    /// Returns the catenated sum of the platform specific prefix and the iterated postfix.
    /// </returns>
    private string CatenateSerialPrefixAndPostfix(int postfix)
    {
#if UNITY_EDITOR_WIN
        return new StringBuilder()
            .Append(SERIAL_PREFIX_WINDOWS)
            .Append(postfix)
            .ToString();
#endif
#if UNITY_STANDALONE_WIN
        return new StringBuilder()
            .Append(SERIAL_PREFIX_WINDOWS)
            .Append(postfix)
            .ToString();
#endif
#if UNITY_EDITOR_OSX
        Debug.Log("UNITY_EDITOR_OSX");
        // TODO: Add OSX implementation.
#endif
#if UNITY_STANDALONE_OSX
        Debug.Log("UNITY_STANDALONE_OSX");
        // TODO: Add OSX implementation.
#endif
#if UNITY_EDITOR_LINUX
        Debug.Log("UNITY_EDITOR_LINUX");
        // TODO: Add Linux implementation.
#endif
#if UNITY_STANDALONE_LINUX
        Debug.Log("UNITY_STANDALONE_LINUX");
        // TODO: Add Linux implementation.
#endif
    }

    /// <summary>
    /// Close all serial ports.
    /// </summary>
    void CloseSerialPorts()
    {
        for (var i = 0; i < serialPorts.Length; i++)
        {
            serialPorts[i].Close();
        }
    }

    /// <summary>
    /// Open and return a single instance of SerialPort.
    /// </summary>
    /// <param name="index">The serial port index.</param>
    /// <param name="baudRate">The serial baud rate.</param>
    /// <returns>An instance of SerialPort.</returns>
    private SerialPort ConnectSerialPort(int index, int baudRate)
    {
        var device = CatenateSerialPrefixAndPostfix(index);
        var port = new SerialPort(device, baudRate);
        port.Open();
        return port;
    }

    /// <summary>
    /// Connect to all possible SerialPort connections.
    /// </summary>
    /// <remarks>
    /// <listheader>Cross-Platform Steps:</listheader>
    /// <list type="bullet">
    /// <item>Count the connected devices.</item>
    /// <item>Use count to define the size of <see cref="serialPorts">serialPorts</see> and
    /// <see cref="Configs">configs</see>.</item>
    /// <item>Populate <see cref="serialPorts">serialPorts</see> and
    /// <see cref="Configs">configs</see>.
    /// <item>Start a function to receive incoming data.</item>
    /// </list>
    /// <listheader>Warnings:</listheader>
    /// <item> In C, the namespace Connect is already taken.</item>
    /// </remarks>
    private void ConnectSerialPorts()
    {
        // Count the connected devices.
        var count = 0;
        for (var i = SERIAL_POSTFIX_MIN_WINDOWS; i < SERIAL_POSTFIX_MAX_WINDOWS; i++)
        {
            try
            {
                var port = ConnectSerialPort(i, serialBaudRates[0]);
                port.Close();
                count++;
            }
            catch (System.Exception e)
            {
                continue;
            }
        }
        // Use count to define the size of serialPorts and configs.
        serialPorts = new SerialPort[count];
        Configs = new string[count];
        // Populate serialPorts and configs.
        var serialPortIndex = 0;
        for (var i = SERIAL_POSTFIX_MIN_WINDOWS; i < SERIAL_POSTFIX_MAX_WINDOWS; i++)
        {
            for (var j = 0; j < serialBaudRates.Length; j++)
            {
                try
                {
                    serialPorts[serialPortIndex] = ConnectSerialPort(i, serialBaudRates[j]);
                    serialPorts[serialPortIndex].ReadTimeout = SERIAL_TIMEOUT;
                    serialPorts[serialPortIndex].Write(OutgoingMessageToString(OutgoingMessages.Start));
                    Configs[serialPortIndex] = new StringBuilder()
                        .Append("comPortIndex:")
                        .Append(i)
                        .ToString();
                    if (debug)
                    {
                        print(new StringBuilder()
                            .Append("SUCCESS: Connection made at: ")
                            .Append(CatenateSerialPrefixAndPostfix(i))
                            .ToString());
                    }
                    serialPortIndex++;
                }
                catch (System.Exception e)
                {
                    continue;
                }
            }
        }
        // Start a function to receive incoming data.
        switch (incomingOption)
        {
            case IncomingOption.UpdateFunction:
                break;
            case IncomingOption.InvokedFunction:
                InvokedFunctionStart();
                break;
            case IncomingOption.ThreadedFunction:
                break;
            case IncomingOption.UserInterfaceFunction:
                break;
        }
    }

    /// <summary>
    /// Start invoking the <see cref="InvokedFunction(void)">InvokedFunction()</see> function.
    /// </summary>
    private void InvokedFunctionStart()
    {
        InvokeRepeating(INVOKED_FUNCTION, 0f, invokedFunctionDelay);
    }

    /// <summary>
    /// Stop invoking the <see cref="InvokedFunction(void)">InvokedFunction()</see> function.
    /// </summary>
    private void InvokedFunctionStop()
    {
        CancelInvoke(INVOKED_FUNCTION);
    }

    /// <summary>
    /// Transform <see cref="OutgoingMessages">OutgoingMessages</see> enum into string.
    /// </summary>
    /// <param name="message">
    /// <see cref="OutgoingMessages">OutgoingMessages</see> member to transform.
    /// </param>
    /// <returns>
    /// A string transformed from a <see cref="OutgoingMessages">OutgoingMessages</see> member.
    /// </returns>
    private string OutgoingMessageToString(OutgoingMessages message)
    {
        return new StringBuilder()
            .Append((int)message)
            .ToString();
    }

    /// <summary>
    /// The Invoked function.
    /// Receive incoming data.
    /// </summary>
    /// <param name="serialPort">A member of <see cref="serialPorts">serialPorts</see>.</param>
    /// <param name="catenatedSerialPort">
    /// A member of <see cref="config">config</see> paired with a member of 
    /// <see cref="serialPorts">serialPorts</see>.
    /// </param>
    private void ReceiveData(SerialPort serialPort, string catenatedSerialPort, int configIndex)
    {
        try
        {
            var incomingMessage = serialPort.ReadLine();
            if (debug)
            {
                print(new StringBuilder()
                    .Append("SUCCESS: Incoming message: ")
                    .Append(incomingMessage)
                    .ToString());
            }
            if (incomingMessage.Contains("type:config"))
            {
                print("HERE: " + incomingMessage);
                //var temp = catenatedSerialPort;
                Configs[configIndex] = new StringBuilder()
                    .Append(catenatedSerialPort)
                    .Append(",")
                    .Append(incomingMessage)
                    .ToString();
            }
            IncomingData = incomingMessage;
        }
        catch (System.Exception e)
        {
        }
    }

    /// <summary>
    /// Starts one instance of 
    /// <see cref="InvokedFunction(SerialPort, string)">InvokedFunction(SerialPort, string)</see> per
    /// <see cref="serialPorts">serialPorts</see> member.
    /// </summary>
    private void ReceiveDatas()
    {
        for (var i = 0; i < serialPorts.Length; i++)
        {
            ReceiveData(serialPorts[i], Configs[i], i);
        }
    }

    /// <summary>
    /// Transform <see cref="IncomingOption">ReceiveOption</see> enum into string.
    /// </summary>
    /// <param name="option">
    /// <see cref="IncomingOption">ReceiveOption</see> member to transform.
    /// </param>
    /// <returns>
    /// A string transformed from a <see cref="IncomingOption">ReceiveOption</see> member.
    /// </returns>
    private string ReceiveOptionToString(IncomingOption option)
    {
        return new StringBuilder()
            .Append((int)option)
            .ToString();
    }

    /// <summary>
    /// Call the reset() function on each connected Arduino.
    /// </summary>
    /// <remarks>
    /// Cannot be named Reset.
    /// </remarks>
    private void ResetArduinos()
    {
        for (var i = 0; i < serialPorts.Length; i++)
        {
            print(Configs[i]);
            if (Configs[i].Contains("type:config") && Configs[i].Contains("function:reset"))
            {
                serialPorts[i].Write(OutgoingMessageToString(OutgoingMessages.Reset));
            }
        }
    }

    /// <summary>
    /// Pseudo-Destructor.
    /// Stop repeating functions, and shutdown Arduinos.
    /// </summary>
    private void Teardown()
    {
        switch (incomingOption)
        {
            case IncomingOption.UpdateFunction:
                break;
            case IncomingOption.InvokedFunction:
                InvokedFunctionStop();
                break;
            case IncomingOption.ThreadedFunction:
                threadedFunction.Abort();
                print("THREAD ABORTED");
                break;
            case IncomingOption.UserInterfaceFunction:
                break;
        }
        ResetArduinos();
        CloseSerialPorts();
    }

    /// <summary>
    /// The threaded function.
    /// Receive incoming data.
    /// </summary>
    private void ThreadedFunction()
    {
        while (true)
        {
            mutex.WaitOne();
            try
            {
                for (var i = 0; i < serialPorts.Length; i++)
                {
                    ReceiveData(serialPorts[i], Configs[i], i);
                }
            }
            catch (System.Exception e)
            {
                //print("ERROR");
            }
            mutex.ReleaseMutex();
        }
    }
    #endregion
}
