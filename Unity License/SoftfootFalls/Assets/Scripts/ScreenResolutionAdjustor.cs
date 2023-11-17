/*
 * Title: ScreenResolutionAdjustor file.
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
using UnityEngine.UI;

public class ScreenResolutionAdjustor : MonoBehaviour
{
    [SerializeField]
    private GameObject standaloneCanvas;

    [SerializeField]
    private CanvasScaler canvasScaler;


    void Start()
    {
        switch (Screen.width)
        {
            case 800:
                switch (Screen.height)
                {
                    case 600:
                        canvasScaler.scaleFactor = 0.5f;
                        break;
                }
                break;
        }
    }
}
