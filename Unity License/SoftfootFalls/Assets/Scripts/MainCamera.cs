/*
 * Title: MainCamera file.
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

public class MainCamera : MonoBehaviour
{
    //private const float size = 0.1f;

    private const int HISTORY_SIZE = 50;
    private const float OFFSET_X = 7.0f;
    private const float OFFSET_Z = 15.0f;
    private const float Y = 0.7f;

    private Vector3 average;
    private Vector3[] history = new Vector3[HISTORY_SIZE];
    private int index;


    void Start()
    {
        for (var i = 0; i < HISTORY_SIZE; i++)
        {
            history[i] = transform.position;
        }
    }

    void Update()
    {
        history[index] = new Vector3(
            RevealedTerrain.cameraX * MainManager.SIZE + OFFSET_X * MainManager.SIZE,
            Y,
            -RevealedTerrain.cameraY * MainManager.SIZE - OFFSET_Z * MainManager.SIZE);
        index++;
        if (index >= HISTORY_SIZE)
        {
            index = 0;
        }
        average = Vector3.zero;
        for (var i = 0; i < HISTORY_SIZE; i++)
        {
            average += history[i];
        }
        average /= HISTORY_SIZE;
        transform.position = average;
    }
}
