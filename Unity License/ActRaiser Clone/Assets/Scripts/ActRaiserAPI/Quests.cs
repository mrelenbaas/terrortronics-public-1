/*
 * Title: Quests file.
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

public abstract class Quests : MonoBehaviour
{
    public static bool is1stTutorialCompleted;
    public static bool is2ndTutorialCompleted;
    public static bool is3rdTutorialCompleted;
    public static bool is4thTutorialCompleted;

    public static bool is4thTutorialReady;
}
