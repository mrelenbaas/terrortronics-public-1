/*
 * Title: MainLoop file.
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


/// <summary>
/// TEXT HERE.
/// </summary>
public class MainLoop : MonoBehaviour
{
    private static bool isShowingDebugGUI = true;

    public static bool IsShowingDebugGUI
    { 
        get 
        { 
            return isShowingDebugGUI;
        } 
        set 
        { 
            isShowingDebugGUI = value; 
        } 
    }


    void Start()
    {
        Route.Setup();
        Route.SpecificTown();
    }

    private void Update()
    {
        Route.AllTimers();
    }

    /// <summary>
    /// The main loop.
    /// </summary>
    /// <remarks>
    /// ## Remarks
    /// None.
    /// </remarks>
    void OnGUI()
    {
        //SaveGame.SaveToFile(new int[] { 2, 1 });
        Route.Immobilize();
        Route.ControlPadDPad();
        Route.ControlPadB();
        Route.ControlPadY();
        Route.ControlPadStart();
        Buttons.ControlPadUnused();
        //Route.SpecificTown();
        RevealedTerrain.Boundary();
        Route.EnemyAndPlayer();
        Route.AllTiles();
        Route.CameraSquare();
        Route.FourByFour();
        Route.GrayBox();
        Route.YellowBox();
        Route.DrawButtonsBasedOnBools();
        //if (IsShowingDebugGUI)
        //{
        //    Route.DrawButtonsBasedOnBools();
        //}
    }
}
