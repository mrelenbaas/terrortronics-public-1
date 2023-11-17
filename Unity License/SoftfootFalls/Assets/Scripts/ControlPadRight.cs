/*
 * Title: ControlPadRight file.
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
using UnityEngine.EventSystems;

public class ControlPadRight : MonoBehaviour
{
    private bool isPressed;

    public void UpdateSelected()
    {
        if (isPressed)
        {
            Route.MoveRight();
        }
    }

    public void PointerDown()
    {
        isPressed = true;
    }

    public void PointerUp()
    {
        isPressed = false;
    }
}
