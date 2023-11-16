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

using System.Collections;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using Unity.Collections;
using Unity.Jobs;
using UnityEngine;

/// <summary>
/// The USB library.
/// </summary>
public class USB : MonoBehaviour
{
    // Create a native array of a single float to store the result. Using a 
    // NativeArray is the only way you can get the results of the job, whether
    // you're getting one value or an array of values.
    NativeArray<char> result;
    // Create a JobHandle for the job
    JobHandle handle;
    // Set up the job

    //[BurstCompile]
    public struct MyJob : IJob
    {
        public NativeArray<char> result;
        public NativeArray<char> serialPort;
        public int baudRate;
        public int timeout;


        public void Execute()
        {
            // Warning: The Burst compiler does not allow SerialPort and other non-atomics.
//#if UNITY_EDITOR_WIN
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
            print(incomingMessage);
            foreach (char c in incomingMessage)
            {
                result.Append(c);
            }
            result[0] = incomingMessage[0];
            result[1] = incomingMessage[1];
            result[2] = incomingMessage[2];
            result[3] = incomingMessage[3];
            result[4] = incomingMessage[4];
            result[5] = incomingMessage[5];
            result[6] = incomingMessage[6];
            result[7] = incomingMessage[7];
            result[8] = incomingMessage[8];
            result[9] = incomingMessage[9];
//#endif
        }
    }

    public static USB Instance { set; get; }
    private StringBuilder incomingDataHIDCurrent = new StringBuilder();
    //private string incomingDataHIDPrevious;
    [SerializeField]
    private bool isIncomingDataHID;
    [SerializeField]
    private bool isReadingDisabled;
    [SerializeField]
    private bool isWritingDisabled;

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
    private const int INCOMING_IN_COROUTINE_FUNCTION = 4;
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
    #endregion

    public delegate void delegateFunction();
    public event delegateFunction delegateFunctionInstance;

    //public delegate void gameEnd();
    //public event gameEnd OnGameEnd;

    #region Static Functions
    public static string ReceiveDataJobs()
    {
        SerialPort sp = new SerialPort("COM11", 9600);
        sp.ReadTimeout = 1000;
        sp.Open();
        var incomingMessage = sp.ReadLine();
        sp.Close();
        return incomingMessage;
    }
    #endregion

    #region Unity Event Functions
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
        USB.Instance.delegateFunctionInstance = DelegateFunction;
        //EditorApplication.quitting += CloseSerialPorts;
        Application.targetFrameRate = 100000000;
        /*
        switch (incomingOption)
        {
            case IncomingOption.UpdateFunction:
            case IncomingOption.InvokedFunction:
            case IncomingOption.ThreadedFunction:
            case IncomingOption.UserInterfaceFunction:
            case IncomingOption.CoroutineFunction:
                ConnectSerialPorts();
                break;
            case IncomingOption.JobSystemFunction:
                break;
        }
        */
        ConnectSerialPorts();
        switch (incomingOption)
        {
            case IncomingOption.UpdateFunction:
            case IncomingOption.InvokedFunction:
            case IncomingOption.ThreadedFunction:
            case IncomingOption.UserInterfaceFunction:
            case IncomingOption.CoroutineFunction:
                break;
            case IncomingOption.JobSystemFunction:
                CloseSerialPorts();
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
            case IncomingOption.CoroutineFunction:
                break;
            case IncomingOption.JobSystemFunction:
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
                    if (isIncomingDataHID)
                    {
                        ReceiveDataHID();
                    }
                    else
                    {
                        ReceiveData(serialPorts[i], Configs[i], i);
                    }
                }
                break;
            case IncomingOption.InvokedFunction:
                break;
            case IncomingOption.ThreadedFunction:
                break;
            case IncomingOption.UserInterfaceFunction:
                break;
            case IncomingOption.CoroutineFunction:
                break;
            case IncomingOption.JobSystemFunction:
                // Set up the job data
                result = new NativeArray<char>(10, Allocator.TempJob);
                NativeArray<char> tempSerialPort = new NativeArray<char>(serialPorts[0].PortName.Length, Allocator.TempJob);
                for (int i = 0; i < serialPorts[0].PortName.Length; i++)
                {
                    tempSerialPort[i] = serialPorts[0].PortName[i];
                }
                MyJob jobData = new MyJob
                {
                    result = result,
                    serialPort = tempSerialPort,
                    baudRate = serialPorts[0].BaudRate,
                    timeout = SERIAL_TIMEOUT
};
                // Schedule the job
                handle = jobData.Schedule();
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

    private void LateUpdate()
    {
        switch (incomingOption)
        {
            case IncomingOption.UpdateFunction:
                break;
            case IncomingOption.InvokedFunction:
                break;
            case IncomingOption.ThreadedFunction:
                break;
            case IncomingOption.UserInterfaceFunction:
                break;
            case IncomingOption.CoroutineFunction:
                break;
            case IncomingOption.JobSystemFunction:
                // Sometime later in the frame, wait for the job to complete before accessing the results.
                handle.Complete();
                // All copies of the NativeArray point to the same memory, you can access the result in "your" copy of the NativeArray
                //float aPlusB = result[0];
                StringBuilder sb = new StringBuilder();
                var counter = 0;
                char aPlusB = result[0];
                //print("size of decoded result: " + result.Length);
                //print("decoded result: " + aPlusB);
                foreach (char c in result)
                {
                    //print("decode: " + counter + ": " + c);
                    sb.Append(c);
                    counter++;
                }
                IncomingData = sb.ToString();
                if (debug)
                {
                    print("FROM JOB SYSTEM: " + IncomingData);
                }
                USB.Instance.delegateFunctionInstance();
                // Free the memory allocated by the result array
                result.Dispose();
                break;
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
                    SendData(serialPorts[serialPortIndex], OutgoingMessageToString(OutgoingMessages.Start));
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
                    //serialPorts[serialPortIndex].Close();
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
            case IncomingOption.CoroutineFunction:
                StartCoroutine(ReceiveDataCoroutine());
                break;
            case IncomingOption.JobSystemFunction:
                break;
        }
    }

    private void DelegateFunction()
    {
        if (debug)
        {
            print("DEFAULT DELEGATE FUNCTION");
        }
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
    /// The Invoked function.
    /// Receive incoming data.
    /// </summary>
    /// <param name="serialPort">An element of <see cref="serialPorts">serialPorts</see>.</param>
    /// <param name="catenatedSerialPort">
    /// An element of <see cref="config">config</see> paired with an element of 
    /// <see cref="serialPorts">serialPorts</see>.
    /// </param>
    private void ReceiveData(SerialPort serialPort, string catenatedSerialPort, int configIndex)
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
            if (incomingMessage.Contains(","))
            {
                //serialPort.Close();
            }
            IncomingData = incomingMessage;
            delegateFunctionInstance();
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
                case IncomingOption.CoroutineFunction:
                    break;
                case IncomingOption.JobSystemFunction:
                    break;
            }
        }
        catch (System.Exception e)
        {
        }
    }

    IEnumerator ReceiveDataCoroutine()
    {
        while(true)
        {
            ReceiveDatas();
            yield return null;
        }
    }

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
            if (isIncomingDataHID)
            {
                ReceiveDataHID();
            }
            else
            {
                ReceiveData(serialPorts[i], Configs[i], i);
            }
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
    /// Cannot be named Reset.
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
            case IncomingOption.UpdateFunction:
                break;
            case IncomingOption.InvokedFunction:
                InvokedFunctionStop();
                break;
            case IncomingOption.ThreadedFunction:
                threadedFunction.Abort();
                break;
            case IncomingOption.UserInterfaceFunction:
                break;
            case IncomingOption.CoroutineFunction:
                StopCoroutine(ReceiveDataCoroutine());
                break;
            case IncomingOption.JobSystemFunction:
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
                    if (isIncomingDataHID)
                    {
                        ReceiveDataHID();
                    }
                    else
                    {
                        ReceiveData(serialPorts[i], Configs[i], i);
                    }
                }
            }
            catch (System.Exception e)
            {
            }
            mutex.ReleaseMutex();
        }
    }
    #endregion
}
