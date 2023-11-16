/*
 * Title: Descriptions file.
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

public abstract class Descriptions : MonoBehaviour
{
    public static string messageMenuText = "";

    public static readonly string letUsListen = "Let us\n          Listen";

    public static readonly string[,] skyPalace = new string[,]
    {
        {
            "To Move",
            "Sky Palace Movement",
            "Observe the People"
        },
        {
            "Fight",
            "Fight Monsters",
            "Select Magic"
        },
        {
            "Status",
            "Status of Master",
            "Status of Cities"
        },
        {
            "Other",
            "Progress Log",
            "Message Speed"
        }
    };

    public static readonly string[,] townBuilder = new string[,] {
        {
            "To Move",
            "Return to Sky Palace",
            "Sky Palace Movement",
            "",
            "",
            ""
        },
        {
            "Direct the People",
            "Building Direction",
            "Let us Listen",
            "",
            "",
            ""
        },
        {
            "Miracles",
            "Lightning",
            "Rain",
            "Sun",
            "Wind",
            "Earthquake"
        },
        {
            "Offerings",
            "Take an Offering",
            "Use Offering",
            "",
            "",
            ""
        },
        {
            "Status",
            "Status of Master",
            "Status of Cities",
            "",
            "",
            ""
        },
        {
            "Other",
            "Progress Log",
            "Message Speed",
            "",
            "",
            ""
        }
    };
}
