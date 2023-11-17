/*
 * Title: PoorManAnimation file.
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

public class PoorManAnimation : MonoBehaviour
{
    // TODO: Remember that this is a seperate copy of the same value in Squares.
    //private float size = 0.1f;

    private const int HISTORY_SIZE = 20;

    private Vector3 average;
    private Vector3[] positionHistory = new Vector3[HISTORY_SIZE];
    private Vector3[] rotationHistory = new Vector3[HISTORY_SIZE];
    private int index;

    private bool isPlayer;
    private bool isMonster;
    private int denIndex;


    void Start()
    {

        for (var i = 0; i < HISTORY_SIZE; i++)
        {
            positionHistory[i] = transform.position;
            rotationHistory[i] = transform.eulerAngles;
        }
    }

    void Update()
    {
        var y = 3.0f * MainManager.SIZE;
        var ratio = Timers.debounceTime / Timers.DEBOUND_PERIOD * 0.95f;
        if (isPlayer)
        {
            positionHistory[index] = new Vector3(
                Player.j * MainManager.SIZE,
                y,
                -Player.i * MainManager.SIZE);
            rotationHistory[index] = new Vector3(
                transform.eulerAngles.x,
                transform.eulerAngles.y,
                transform.eulerAngles.z);
        }
        else if (isMonster)
        {
            positionHistory[index] = new Vector3(
                Route.monsterLocations[denIndex, 0] * MainManager.SIZE,
                y,
                -Route.monsterLocations[denIndex, 1] * MainManager.SIZE);
        }
        index++;
        if (index >= HISTORY_SIZE)
        {
            index = 0;
        }
        average = Vector3.zero;
        for (var i = 0; i < HISTORY_SIZE; i++)
        {
            average += positionHistory[i];
        }
        average /= HISTORY_SIZE;
        transform.position = average;
        average = Vector3.zero;
        for (var i = 0; i < HISTORY_SIZE; i++)
        {
            average += rotationHistory[i];
        }
        average /= HISTORY_SIZE;
        transform.eulerAngles = average;
    }

    public void StartPlayer()
    {
        isPlayer = true;
    }

    public void StartMonster(int denIndex)
    {
        isMonster = true;
        this.denIndex = denIndex;
    }
}
