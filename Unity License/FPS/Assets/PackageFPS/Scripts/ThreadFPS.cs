/*
 * Title: ThreadFPS file.
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

using UnityEngine;
using System.Collections;
using System.Threading;
using System;
using System.Text;
using System.Runtime.CompilerServices;

public class ThreadFPS : MonoBehaviour
{
    #region Region example
    #endregion

    private Thread _t1;
    private Mutex _mutex = new Mutex();

    private const long PERIOD = 1000;
    private int fpsCurrent;
    private int fpsPrevious;
    private long timeCurrent;
    private long timePrevious;
    private long timeDelta;
    private long timeAtStart;
    private long timeThisSecond;

    void Start()
    {
        Application.targetFrameRate = 100000000;
        timeAtStart = DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond;
        timePrevious = timeAtStart;
        timeAtStart = DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond;
        timeDelta = timeCurrent - timePrevious;
        timeThisSecond = timeDelta;
        _t1 = new Thread(_func1);
        _t1.Start();
    }

    private void OnApplicationQuit()
    {
        _t1.Abort();
    }

    private void _func1()
    {
        while (true)
        {
            _mutex.WaitOne();
            timePrevious = timeCurrent;
            timeCurrent = DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond;
            timeDelta = timeCurrent - timePrevious;
            timeThisSecond += timeDelta;
            if (timeThisSecond > PERIOD)
            {
                fpsPrevious = fpsCurrent;
                fpsCurrent = 0;
                timeThisSecond -= PERIOD;
                UpdateFPS.fpsPreviousThread = fpsPrevious;
            }
            else
            {
                fpsCurrent++;
            }
            _mutex.ReleaseMutex();
        }
    }
}