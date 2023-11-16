/*
 * Title: Quitter file.
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
using System.Diagnostics;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Quitter : MonoBehaviour
{
    private const float DELAY = 1.0f;

    [SerializeField]
    private USB arduinoIO;

    private void OnDisable()
    {
        //StartProcess("C:\\Users\\mrele\\Arcade Cabinet\\Assets\\~bat\\OBSSTOP.BAT");
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            QuitApplication(DELAY);
        }
        if (Input.GetKeyDown(KeyCode.F1))
        {
            Scene scene = SceneManager.GetActiveScene(); SceneManager.LoadScene(scene.name);
        }
    }

    private void QuitApplication()
    {
        Application.Quit();
        #if UNITY_EDITOR
            UnityEditor.EditorApplication.isPlaying = false;
        #endif
    }
    private void QuitApplication(float delay)
    {
        Invoke("QuitApplication", delay);
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
            //tempProcess.OutputDataReceived += new DataReceivedEventHandler(DataReceived);
            //tempProcess.ErrorDataReceived += new DataReceivedEventHandler(ErrorReceived);
            tempProcess.Start();
            tempProcess.BeginOutputReadLine();
            //messageStream = tempProcess.StandardInput;
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
}
