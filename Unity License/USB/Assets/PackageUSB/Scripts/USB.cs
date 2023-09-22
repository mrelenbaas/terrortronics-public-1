/*
 * Title: USB file.
 * Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * Version: 2
 * Date: September 19, 2023
 * 
 * Intellectual Property:
 * Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 * 
 * License:
 * This file is owned by Terrortronics / Bradley Elenbaas.
 * This file observes the Unity License.
 */

/*
 * Unit Test: 
 */

/*
 * TODO: Update to work on Mac.
 * TODO: Replace while(True) loops with while(exitFlag) loops.
 * TODO: Refactor the namespace "serial port" to the namespace "port". Do this with Python code.
 * TODO: Remove bare exceptions.
 * TODO: XML document exceptions.
 */

using System.Collections;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using Unity.Collections;
using Unity.Jobs;
using Unity.VisualScripting;
using UnityEngine;

/// <summary>
/// The USB library.
/// </summary>
/// <details>
/// <listheader>Unit Tests</listheader>
/// <list type="table">
/// <item><description>Priority 1</description><term>Test each receive option.</term></item>
/// </list>
/// </details>
public class USB : MonoBehaviour
{
    #region Singleton Variables
    /// <summary>
    /// A singleton instance of the <see cref="USB">USB</see> class.
    /// </summary>
    public static USB Instance { get; private set; }
    #endregion

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
    /// <summary>
    /// Check to use HID input instead of traditional Arduino serial input.
    /// </summary>
    [SerializeField, Tooltip("Check to use HID input instead of traditional Arduino serial input.")]
    private bool isIncomingDataHID;
    /// <summary>
    /// Check to disable Rx.
    /// </summary>
    [SerializeField, Tooltip("Check to disable Rx.")]
    private bool isReadingDisabled;
    /// <summary>
    /// Check to disable Tx.
    /// </summary>
    [SerializeField, Tooltip("Check to disable Tx.")]
    private bool isWritingDisabled;
    #endregion

    #region FPS Variables
    /// <summary>
    /// The maximum frame rate.
    /// </summary>
    private const int TARGET_FPS = 100000000;
    #endregion

    #region Incoming Data
    /// <summary>
    /// A set of configs received from connected Arduinos.
    /// </summary>
    public static string[] Configs { get; private set; }
    /// <summary>
    /// When using HID input, this StringBuilder populates one character at a time until a newline
    /// is reached.
    /// </summary>
    private StringBuilder incomingDataHIDCurrent = new StringBuilder();
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
    /// Wait for incoming data in a coroutine.
    /// </summary>
    private const int INCOMING_IN_COROUTINE_FUNCTION = 4;
    /// <summary>
    /// Wait for incoming data in a Job System function.
    /// </summary>
    private const int INCOMING_IN_JOB_SYSTEM_FUNCTION = 5;
    /// <summary>
    /// Enum of options for how to receive incoming data.
    /// </summary>
    public enum IncomingOption
    {
        UpdateFunction = INCOMING_IN_UPDATE_FUNCTION,
        InvokedFunction = INCOMING_IN_INVOKED_FUNTION,
        ThreadedFunction = INCOMING_IN_THREADED_FUNCTION,
        UserInterfaceFunction = INCOMING_IN_USER_INTERFACE_FUNCTION,
        CoroutineFunction = INCOMING_IN_COROUTINE_FUNCTION,
        JobSystemFunction = INCOMING_IN_JOB_SYSTEM_FUNCTION,
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

    #region Invoked Function Variables
    /// <summary>
    /// For use with InvokeRepeating(string, float, float) and CancelInvoke(string) functions.
    /// </summary>
    private const string INVOKED_FUNCTION = "ReceiveDatas";
    #endregion

    #region Thread Function Variables
    /// <summary>
    /// Incoming data from thread.
    /// </summary>
    public static string IncomingData { get; private set; } = "";
    /// <summary>
    /// A thread for <see cref="ReceiveDataThreaded">ReceiveDataThreaded()</see>.
    /// </summary>
    public static Thread threadedFunction;
    /// <summary>
    /// A mutex.
    /// </summary>
    private readonly Mutex mutex = new Mutex();
    #endregion

    #region Job System Variables
    /// <summary>
    /// The size of <see cref="result">result</see>
    /// </summary>
    private int RESULT_SIZE = 10;
    // Create a native array of a single float to store the result. Using a 
    // NativeArray is the only way you can get the results of the job, whether
    // you're getting one value or an array of values.
    private NativeArray<char> result;
    // Create a JobHandle for the job
    private JobHandle handle;
    // Set up the job
    private int jobIndex;

    /// <summary>
    /// A struct dedicated to the job of receiving data.
    /// </summary>
    /// <remarks>
    /// <listheader>Warnings</listheader>
    /// <list type="bullet">
    /// <item>The job needs to open and close a single port at a time.</item>
    /// <item>The Burst compiler does not allow SerialPort and other non-atomics.</item>
    /// </list>
    /// </remarks>
    private struct ReceiveDataJob : IJob
    {
        #region Public Variables
        /// <summary>
        /// The incoming data.
        /// </summary>
        public NativeArray<char> receivedResult;
        /// <summary>
        /// The device name of a serial port to open in <see cref="Execute(void)">Execute()</see>.
        /// </summary>
        public NativeArray<char> serialPort;
        /// <summary>
        /// The baud rate of a serial port to open in <see cref="Execute(void)">Execute()</see>.
        /// </summary>
        public int baudRate;
        /// <summary>
        /// The timeout of a serial port to open in <see cref="Execute(void)">Execute()</see>.
        /// </summary>
        public int timeout;
        #endregion

        #region Public Functions
        /// <summary>
        /// The Job System function.
        /// Receive incoming data.
        /// </summary>
        public void Execute()
        {
            SerialPort sp = new SerialPort(
                new StringBuilder()
                    .Append(serialPort[0])
                    .Append(serialPort[1])
                    .Append(serialPort[2])
                    .Append(serialPort[3])
                    .Append(serialPort[4])
                    .ToString(),
                baudRate);
            sp.ReadTimeout = timeout;
            sp.Open();
            var incomingMessage = sp.ReadLine();
            sp.Close();
            foreach (char c in incomingMessage)
            {
                receivedResult.Append(c);
            }
            var i = 0;
            try
            {
                do
                {
                    receivedResult[i] = incomingMessage[i];
                    i++;
                } while (i < 10);
            }
            catch (System.Exception e)
            {
                receivedResult[i - 1] = '\0';
            }
        }
        #endregion
    }

    #endregion

    #region Delegate Function Variables
    /// <summary>
    /// A template of a delegate function to be reassigned.
    /// </summary>
    public delegate void delegateFunctionTemplate();
    /// <summary>
    /// An instance of a delegate function to be reassigned.
    /// </summary>
    public event delegateFunctionTemplate DelegateFunctionInstance;
    #endregion

    #region Unity Event Functions
    /// <summary>
    /// Pseudo-Constructor.
    /// Ensures that the <see cref="USB">USB</see> class is a singleton.
    /// </summary>
    private void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
            DontDestroyOnLoad(this.gameObject);
        }
        else
        {
            Destroy(gameObject);
        }
    }

    /// <summary>
    /// Pseudo-Constructor.
    /// Calls the <see cref="ConnectSerialPorts">ConnectSerialPorts()</see> function.
    /// </summary>
    void Start()
    {
        USB.Instance.DelegateFunctionInstance = DelegateFunction;
        Application.targetFrameRate = TARGET_FPS;
        ConnectSerialPorts();
        switch (incomingOption)
        {
            case IncomingOption.JobSystemFunction:
                CloseSerialPorts();
                break;
            default:
                break;
        }
    }

    /// <summary>
    /// Pseudo-Destructor.
    /// Kills the <see cref="threadedFunction">threadedFunction</see> thread.
    /// </summary>
    private void OnApplicationQuit()
    {
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
            case IncomingOption.ThreadedFunction:
                threadedFunction = new Thread(ReceiveDataThreaded);
                threadedFunction.Start();
                break;
            case IncomingOption.UserInterfaceFunction:
                InvokedFunctionStart();
                break;
            default:
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
                    ReceiveHIDOrUSB(i);
                }
                break;
            case IncomingOption.JobSystemFunction:
                result = new NativeArray<char>(RESULT_SIZE, Allocator.TempJob);
                NativeArray<char> tempSerialPort = new NativeArray<char>(
                    serialPorts[jobIndex].PortName.Length,
                    Allocator.TempJob);
                for (int i = 0; i < serialPorts[jobIndex].PortName.Length; i++)
                {
                    tempSerialPort[i] = serialPorts[jobIndex].PortName[i];
                    ReceiveDataJob jobData = new ReceiveDataJob
                    {
                        receivedResult = result,
                        serialPort = tempSerialPort,
                        baudRate = serialPorts[jobIndex].BaudRate,
                        timeout = SERIAL_TIMEOUT
                    };
                    handle = jobData.Schedule();
                }
                break;
            default:
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

    /// <summary>
    /// Received data from a job started in Update().
    /// </summary>
    private void LateUpdate()
    {
        switch (incomingOption)
        {
            case IncomingOption.JobSystemFunction:
                handle.Complete();
                StringBuilder stringBuilder = new StringBuilder();
                for (int i = 0; i < result.Length; i++)
                {
                    stringBuilder.Append(result[i]);
                }
                IncomingData = stringBuilder.ToString();
                USB.Instance.DelegateFunctionInstance();
                jobIndex++;
                if (jobIndex >= serialPorts.Length)
                {
                    jobIndex = 0;
                }
                result.Dispose();
                break;
            default:
                break;
        }
    }
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
        return "";
#endif
#if UNITY_STANDALONE_OSX
        Debug.Log("UNITY_STANDALONE_OSX");
        // TODO: Add OSX implementation.
        return "";
#endif
#if UNITY_EDITOR_LINUX
        return new StringBuilder()
            .Append("/dev/ttyACM")
            .Append(postfix)
            .ToString();
#endif
#if UNITY_STANDALONE_LINUX
        return new StringBuilder()
            .Append(SERIAL_PREFIX_LINUX)
            .Append(postfix)
            .ToString();
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
    private void ConnectSerialPorts()
    {
        int count;
#if UNITY_EDITOR_WIN
        count = DiscoverDevices(SERIAL_POSTFIX_MIN_WINDOWS, SERIAL_POSTFIX_MAX_WINDOWS);
#endif
#if UNITY_STANDALONE_WIN
        count = DiscoverDevices(SERIAL_POSTFIX_MIN_WINDOWS, SERIAL_POSTFIX_MAX_WINDOWS);
#endif
#if UNITY_EDITOR_OSX
        count = DiscoverDevices(SERIAL_POSTFIX_MIN_MAC, SERIAL_POSTFIX_MAX_MAC);
#endif
#if UNITY_STANDALONE_OSX
        count = DiscoverDevices(SERIAL_POSTFIX_MIN_MAC, SERIAL_POSTFIX_MAX_MAC);
#endif
#if UNITY_EDITOR_LINUX
        count = DiscoverDevices(SERIAL_POSTFIX_MIN_LINUX, SERIAL_POSTFIX_MAX_LINUX);
#endif
#if UNITY_STANDALONE_LINUX
        count = DiscoverDevices(SERIAL_POSTFIX_MIN_LINUX, SERIAL_POSTFIX_MAX_LINUX);
#endif

        serialPorts = new SerialPort[count];
        Configs = new string[count];
#if UNITY_EDITOR_WIN
        PopulateResources(SERIAL_POSTFIX_MIN_WINDOWS, SERIAL_POSTFIX_MAX_WINDOWS);
#endif
#if UNITY_STANDALONE_WIN
        PopulateResources(SERIAL_POSTFIX_MIN_WINDOWS, SERIAL_POSTFIX_MAX_WINDOWS);
#endif
#if UNITY_EDITOR_OSX
        PopulateResources(SERIAL_POSTFIX_MIN_MAC, SERIAL_POSTFIX_MAX_MAC);
#endif
#if UNITY_STANDALONE_OSX
        PopulateResources(SERIAL_POSTFIX_MIN_MAC, SERIAL_POSTFIX_MAX_MAC);
#endif
#if UNITY_EDITOR_LINUX
        PopulateResources(SERIAL_POSTFIX_MIN_LINUX, SERIAL_POSTFIX_MAX_LINUX);
#endif
#if UNITY_STANDALONE_LINUX
        PopulateResources(SERIAL_POSTFIX_MIN_LINUX, SERIAL_POSTFIX_MAX_LINUX);
#endif
        switch (incomingOption)
        {
            case IncomingOption.InvokedFunction:
                InvokedFunctionStart();
                break;
            case IncomingOption.CoroutineFunction:
                StartCoroutine(ReceiveDataCoroutine());
                break;
            default:
                break;
        }
    }

    /// <summary>
    /// A stub function to be replaced replaced by another class.
    /// </summary>
    private void DelegateFunction() {}

    /// <summary>
    /// Check all serial ports looking for any connection.
    /// </summary>
    /// <param name="min">The minimum possible port.</param>
    /// <param name="max">The maximum possible port.</param>
    /// <returns>The number of found serial ports.</returns>
    private int DiscoverDevices(int min, int max)
    {
        var count = 0;
        for (var i = min; i < max; i++)
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
        return count;
    }

    /// <summary>
    /// Start invoking the <see cref="InvokedFunction(void)">InvokedFunction()</see> function.
    /// </summary>
    private void InvokedFunctionStart()
    {
        InvokeRepeating(INVOKED_FUNCTION, 0f, 0.0f);
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
    /// Populate the <see cref="serialPorts">serialPorts</see> variable.
    /// </summary>
    private void PopulateResources(int min, int max)
    {
        var serialPortIndex = 0;
        for (var i = min; i < max; i++)
        {
            for (var j = 0; j < serialBaudRates.Length; j++)
            {
                try
                {
                    serialPorts[serialPortIndex] = ConnectSerialPort(i, serialBaudRates[j]);
                    serialPorts[serialPortIndex].ReadTimeout = SERIAL_TIMEOUT;
                    SendData(
                        serialPorts[serialPortIndex],
                        OutgoingMessageToString(OutgoingMessages.Start));
                    Configs[serialPortIndex] = new StringBuilder()
                        .Append("serialPortIndex:")
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
    }

    /// <summary>
    /// The Invoked function, but used by other receive options as well.
    /// Receive incoming data.
    /// </summary>
    /// <remarks>
    /// <listheader>RUSCAL</listheader>
    /// <list type="bullet">
    /// <item>...</item>
    /// <item>incomingMessage isoftype Pointer</item>
    /// </list>
    /// </remarks>
    /// <param name="serialPort">An element of <see cref="serialPorts">serialPorts</see>.</param>
    /// <param name="catenatedSerialPort">
    /// An element of <see cref="config">config</see> paired with an element of 
    /// <see cref="serialPorts">serialPorts</see>.
    /// </param>
    private void ReceiveDataUSB(SerialPort serialPort, string catenatedSerialPort, int configIndex)
    {
        if (isReadingDisabled)
        {
            return;
        }
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
                Configs[configIndex] = new StringBuilder()
                    .Append(catenatedSerialPort)
                    .Append(",")
                    .Append(incomingMessage)
                    .ToString();
            }
            IncomingData = incomingMessage;
            DelegateFunctionInstance();
            switch (incomingOption)
            {
                case IncomingOption.InvokedFunction:
                    InvokedFunctionStart();
                    break;
                default:
                    break;
            }
        }
        catch (System.Exception e)
        {
        }
    }

    /// <summary>
    /// The coroutine function.
    /// Receive incoming data.
    /// </summary>
    /// <returns>Ignore. Used by Unity.</returns>
    IEnumerator ReceiveDataCoroutine()
    {
        while(true)
        {
            for (var i = 0; i < serialPorts.Length; i++)
            {
                ReceiveHIDOrUSB(i);
            }
            yield return null;
        }
    }

    /// <summary>
    /// Receive incoming data from either a generic HID source, or a traditional Arduino serial source.
    /// </summary>
    /// <param name="index">
    /// The index of the <see cref="serialPorts">serialPorts</see>
    /// and <see cref="Config">Config</see> to be passed to 
    /// <see cref="ReceiveDataUSB(SerialPort, string, int)">ReceiveDataUSB(SerialPort, string, int)</see>
    /// </param>
    private void ReceiveHIDOrUSB(int index)
    {
        if (isIncomingDataHID)
        {
            ReceiveDataHID();
        }
        else
        {
            ReceiveDataUSB(serialPorts[index], Configs[index], index);
        }
    }

    /// <summary>
    /// The Rx HID function.
    /// Receive incoming data.
    /// </summary>
    private void ReceiveDataHID()
    {
        if (isReadingDisabled)
        {
            return;
        }
        if (Input.GetKeyDown(KeyCode.A)) incomingDataHIDCurrent.Append("a");
        else if (Input.GetKeyDown(KeyCode.B)) incomingDataHIDCurrent.Append("b");
        else if (Input.GetKeyDown(KeyCode.C)) incomingDataHIDCurrent.Append("c");
        else if (Input.GetKeyDown(KeyCode.D)) incomingDataHIDCurrent.Append("d");
        else if (Input.GetKeyDown(KeyCode.E)) incomingDataHIDCurrent.Append("e");
        else if (Input.GetKeyDown(KeyCode.F)) incomingDataHIDCurrent.Append("f");
        else if (Input.GetKeyDown(KeyCode.G)) incomingDataHIDCurrent.Append("g");
        else if (Input.GetKeyDown(KeyCode.H)) incomingDataHIDCurrent.Append("h");
        else if (Input.GetKeyDown(KeyCode.I)) incomingDataHIDCurrent.Append("i");
        else if (Input.GetKeyDown(KeyCode.J)) incomingDataHIDCurrent.Append("j");
        else if (Input.GetKeyDown(KeyCode.K)) incomingDataHIDCurrent.Append("k");
        else if (Input.GetKeyDown(KeyCode.L)) incomingDataHIDCurrent.Append("l");
        else if (Input.GetKeyDown(KeyCode.M)) incomingDataHIDCurrent.Append("m");
        else if (Input.GetKeyDown(KeyCode.N)) incomingDataHIDCurrent.Append("n");
        else if (Input.GetKeyDown(KeyCode.O)) incomingDataHIDCurrent.Append("o");
        else if (Input.GetKeyDown(KeyCode.P)) incomingDataHIDCurrent.Append("p");
        else if (Input.GetKeyDown(KeyCode.Q)) incomingDataHIDCurrent.Append("q");
        else if (Input.GetKeyDown(KeyCode.R)) incomingDataHIDCurrent.Append("r");
        else if (Input.GetKeyDown(KeyCode.S)) incomingDataHIDCurrent.Append("s");
        else if (Input.GetKeyDown(KeyCode.T)) incomingDataHIDCurrent.Append("t");
        else if (Input.GetKeyDown(KeyCode.U)) incomingDataHIDCurrent.Append("u");
        else if (Input.GetKeyDown(KeyCode.V)) incomingDataHIDCurrent.Append("v");
        else if (Input.GetKeyDown(KeyCode.W)) incomingDataHIDCurrent.Append("w");
        else if (Input.GetKeyDown(KeyCode.X)) incomingDataHIDCurrent.Append("x");
        else if (Input.GetKeyDown(KeyCode.Y)) incomingDataHIDCurrent.Append("y");
        else if (Input.GetKeyDown(KeyCode.Z)) incomingDataHIDCurrent.Append("z");
        else if (Input.GetKeyDown(KeyCode.Alpha0)) incomingDataHIDCurrent.Append("0");
        else if (Input.GetKeyDown(KeyCode.Alpha1)) incomingDataHIDCurrent.Append("1");
        else if (Input.GetKeyDown(KeyCode.Alpha2)) incomingDataHIDCurrent.Append("2");
        else if (Input.GetKeyDown(KeyCode.Alpha3)) incomingDataHIDCurrent.Append("3");
        else if (Input.GetKeyDown(KeyCode.Alpha4)) incomingDataHIDCurrent.Append("4");
        else if (Input.GetKeyDown(KeyCode.Alpha5)) incomingDataHIDCurrent.Append("5");
        else if (Input.GetKeyDown(KeyCode.Alpha6)) incomingDataHIDCurrent.Append("6");
        else if (Input.GetKeyDown(KeyCode.Alpha7)) incomingDataHIDCurrent.Append("7");
        else if (Input.GetKeyDown(KeyCode.Alpha8)) incomingDataHIDCurrent.Append("8");
        else if (Input.GetKeyDown(KeyCode.Alpha9)) incomingDataHIDCurrent.Append("9");
        else if (Input.GetKeyDown(KeyCode.Space)) incomingDataHIDCurrent.Append(" ");
        else if (Input.GetKeyDown(KeyCode.Comma)) incomingDataHIDCurrent.Append(",");
        else if (Input.GetKeyDown(KeyCode.Semicolon)) incomingDataHIDCurrent.Append(";");
        else if (Input.GetKeyDown(KeyCode.Colon)) incomingDataHIDCurrent.Append(":");
        else if (Input.GetKeyDown(KeyCode.Underscore)) incomingDataHIDCurrent.Append("_");
        else if (Input.anyKeyDown)
        {
            incomingDataHIDCurrent.Append("\n");
            IncomingData = incomingDataHIDCurrent.ToString();
            incomingDataHIDCurrent.Clear();
        }
    }

    /// <summary>
    /// The threaded function.
    /// Receive incoming data.
    /// </summary>
    private void ReceiveDataThreaded()
    {
        while (true)
        {
            mutex.WaitOne();
            try
            {
                for (var i = 0; i < serialPorts.Length; i++)
                {
                    ReceiveHIDOrUSB(i);
                }
            }
            catch (System.Exception e)
            {
            }
            mutex.ReleaseMutex();
        }
    }

    /// <summary>
    /// Starts one instance of 
    /// <see cref="InvokedFunction(SerialPort, string)">InvokedFunction(SerialPort, string)</see> per
    /// <see cref="serialPorts">serialPorts</see> member.
    /// </summary>
    private void ReceiveDatas()
    {
        if (isReadingDisabled)
        {
            return;
        }
        for (var i = 0; i < serialPorts.Length; i++)
        {
            ReceiveHIDOrUSB(i);
        }
    }

    /// <summary>
    /// Send outgoing data.
    /// </summary>
    /// <param name="serialPort">An element of <see cref="serialPorts">serialPorts</see>.</param>
    /// <param name="message">A string to send out to an Arduino.</param>
    private void SendData(SerialPort serialPort, string message)
    {
        if (isWritingDisabled)
        {
            return;
        }
        serialPort.Write(message);
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
    /// <listheader>Warnings:</listheader>
    /// <list type="bullet">
    /// <item>Cannot be named Reset.</item>
    /// </list>
    /// </remarks>
    private void ResetArduinos()
    {
        for (var i = 0; i < serialPorts.Length; i++)
        {
            if (debug)
            {
                print(Configs[i]);
            }
            if (Configs[i].Contains("type:config") && Configs[i].Contains("function:reset"))
            {
                SendData(serialPorts[i], OutgoingMessageToString(OutgoingMessages.Reset));
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
            case IncomingOption.InvokedFunction:
                InvokedFunctionStop();
                break;
            case IncomingOption.ThreadedFunction:
                threadedFunction.Abort();
                break;
            case IncomingOption.CoroutineFunction:
                StopCoroutine(ReceiveDataCoroutine());
                break;
            default:
                break;
        }
        ResetArduinos();
        CloseSerialPorts();
    }
    #endregion
}
