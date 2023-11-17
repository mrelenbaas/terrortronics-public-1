/*
 * Title: MainManager file.
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

public class MainManager : MonoBehaviour
{
    public const float SIZE = 0.1f;

    private bool isFirstFrame = true;

    public Squares squares;

    // TODO: Remember to access manager's through here. Like MaterialsManager.
    /// <summary>
    /// The main function.
    /// </summary>
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.P))
        {
            print(
                Player.i
                + ", "
                + Player.j
                + ": ("
                + LookupTables.LandName[Towns.town[0, Player.i, Player.j]]
                + ", "
                + LookupTables.LandModifierName[Towns.town[1, Player.i, Player.j]]
                + ", "
                + LookupTables.PeopleName[Towns.town[2, Player.i, Player.j]]
                + ", "
                + LookupTables.BuildingName[Towns.town[3, Player.i, Player.j]]
                + ", "
                + LookupTables.BuildingModifierName[Towns.town[4, Player.i, Player.j]]
                //+ ", "
                //+ LookupTables.EnemiesAndPlayerName[Towns.town[5, Player.i, Player.j]]
                //+ ", "
                //+ LookupTables.BuildingName[Towns.town[6, Player.j, Player.i]]
                + ")");
        }
        if (isFirstFrame)
        {
            squares.gameObject.SetActive(true);
            squares.StartSquares();
            isFirstFrame = false;
        }
    }
}
