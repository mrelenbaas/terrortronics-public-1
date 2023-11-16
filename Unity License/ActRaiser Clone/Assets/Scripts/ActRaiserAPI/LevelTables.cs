/*
 * Title: LevelTables file.
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

public abstract class LevelTables : MonoBehaviour
{
    public static readonly int[] healthPoints = new int[] {
        8,
        9,
        10,
        11,
        12,
        13,
        14,
        15,
        16,
        17,
        18,
        19,
        20,
        21,
        22,
        23,
        24};

    public static readonly int[] populations = new int[] {
        0,
        80,
        200,
        400,
        700,
        950,
        1200,
        1400,
        1700,
        1900,
        2200,
        2500,
        2900,
        3300,
        3700,
        4100,
        4600};

    public static readonly int[] spellPoints = new int[] {
        20,
        45,
        60,
        80,
        100,
        120,
        140,
        160,
        180,
        200,
        220,
        240,
        260,
        280,
        300,
        320,
        340};
}
