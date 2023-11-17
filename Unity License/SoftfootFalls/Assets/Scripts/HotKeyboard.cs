/*
 * Title: HotKeyboard file.
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

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HotKeyboard : MonoBehaviour
{
    // TODO: Remember to split this into two classes. They don't work
    //       well together.

    //private bool upBlock;
    //private bool downBlock;
    //private bool leftBlock;
    //private bool rightBlock;

    //private bool startBlock;
    //private bool bBlock;
    //private bool yBlock;

    [SerializeField]
    private StandaloneCanvas standaloneCanvas;


    void Update()
    {
        if (Input.GetAxis("Vertical") == 1.0f
            || Input.GetAxis("Vertical2") == 1.0f
            || Input.GetKeyDown(KeyCode.UpArrow))
        {
            //if (!upBlock)
            //{
                standaloneCanvas.ControlPadUp();
                //upBlock = true;
            //}
        }
        else if (Input.GetAxis("Vertical") != 1.0f
                 && Input.GetAxis("Vertical2") != 1.0f
                 && Input.GetKeyUp(KeyCode.UpArrow))
        {
            //if (upBlock)
            //{
                //upBlock = false;
            //}
        }
        if (Input.GetAxis("Vertical") == -1.0f
            || Input.GetAxis("Vertical2") == -1.0f
            || Input.GetKeyDown(KeyCode.DownArrow))
        {
            //if (!downBlock)
            //{
                standaloneCanvas.ControlPadDown();
                //downBlock = true;
            //}
        }
        else if (Input.GetAxis("Vertical") != -1.0f
                 && Input.GetAxis("Vertical2") != -1.0f
                 && Input.GetKeyUp(KeyCode.DownArrow))
        {
            //if (downBlock)
            //{
                //downBlock = false;
            //}
        }
        if (Input.GetAxis("Horizontal") == -1.0f
            || Input.GetAxis("Horizontal2") == -1.0f
            || Input.GetKeyDown(KeyCode.LeftArrow))
        {
            //if (!leftBlock)
            //{
                standaloneCanvas.ControlPadLeft();
                //leftBlock = true;
            //}
        }
        else if (Input.GetAxis("Horizontal") != -1.0f
                 && Input.GetAxis("Horizontal2") != -1.0f
                 && Input.GetKeyUp(KeyCode.LeftArrow))
        {
            //if (leftBlock)
            //{
                //leftBlock = false;
            //}
        }
        if (Input.GetAxis("Horizontal") == 1.0f
            || Input.GetAxis("Horizontal2") == 1.0f
            || Input.GetKeyDown(KeyCode.RightArrow))
        {
            //if (!rightBlock)
            //{
                standaloneCanvas.ControlPadRight();
                //rightBlock = true;
            //}
        }
        else if (Input.GetAxis("Horizontal") != 1.0f
                 && Input.GetAxis("Horizontal2") != 1.0f
                 && Input.GetKeyUp(KeyCode.RightArrow))
        {
            //if (rightBlock)
            //{
                //rightBlock = false;
            //}
        }
        if (Input.GetKeyDown(KeyCode.Joystick1Button9)
            || Input.GetKeyDown(KeyCode.Return))
        {
            //if (!startBlock)
            //{
                standaloneCanvas.ControlPadStart();
                //startBlock = true;
            //}
        }
        else if (Input.GetKeyUp(KeyCode.Joystick1Button9)
                 || Input.GetKeyUp(KeyCode.Return))
        {
            //if (startBlock)
            //{
                //if (!bBlock)
                //{
                    standaloneCanvas.ControlPadB();
                    //bBlock = true;
                //}
                //startBlock = false;
            //}
        }
        if (Input.GetKeyDown(KeyCode.Joystick1Button1)
            || Input.GetKeyDown(KeyCode.Z))
        {
            //if (!bBlock)
            //{
                standaloneCanvas.ControlPadB();
                //bBlock = true;
            //}
        }
        else if (Input.GetKeyUp(KeyCode.Joystick1Button1)
                 || Input.GetKeyUp(KeyCode.Z))
        {
            //if (bBlock)
            //{
                //bBlock = false;
            //}
        }
        if (Input.GetKeyDown(KeyCode.Joystick1Button0)
            || Input.GetKeyDown(KeyCode.X))
        {
            //if (!yBlock)
            //{
                standaloneCanvas.ControlPadY();
                //yBlock = true;
            //}
        }
        else if (Input.GetKeyUp(KeyCode.Joystick1Button0)
                 || Input.GetKeyUp(KeyCode.X))
        {
            //if (yBlock)
            //{
                //yBlock = false;
            //}
        }
    }
}
