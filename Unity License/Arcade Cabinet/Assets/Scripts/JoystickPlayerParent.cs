/*
 * Title: JoystickPlayerParent file.
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

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UIElements;

public class JoystickPlayerParent : MonoBehaviour
{
    private const float SPEED = 0.1f;
    private const float MAX_X_OFFSET = 24.0f;
    private const float MAX_Z = 85.0f;
    private const float MIN_Z = -5.0f;
    private const float DEADZONE_X = 0.9f;
    private const float DEADZONE_Z = 0.9f;

    private float maxX;
    private float minX;

    private const float TIME_TIMEOUT = 50.0f;
    private float timeCurrent;
    private bool isTimeBeforeFirstMovement = true;

    [SerializeField]
    private Transform[] joystickPlayers;


    private void Start()
    {
        minX = transform.position.x - MAX_X_OFFSET;
        maxX = transform.position.x + MAX_X_OFFSET;
        for (var i = 0; i < joystickPlayers.Length; i++)
        {
            //transform.GetChild(i).GetChild(0).GetComponent<TMP_Text>().text = new StringBuilder().Append(i + 1).ToString();
        }
    }

    private void Update()
    {
        if (Input.GetKey(KeyCode.W))
        {
            joystickPlayers[0].position = new Vector3(
                joystickPlayers[0].position.x,
                0,
                joystickPlayers[0].position.z + SPEED);
            ResetTime();
        }
        else if (Input.GetKey(KeyCode.S))
        {
            joystickPlayers[0].position = new Vector3(
                joystickPlayers[0].position.x,
                0,
                joystickPlayers[0].position.z - SPEED);
            ResetTime();
        }
        else if (Input.GetKey(KeyCode.A))
        {
            joystickPlayers[0].position = new Vector3(
                joystickPlayers[0].position.x - SPEED,
                0,
                joystickPlayers[0].position.z);
            ResetTime();
        }
        else if (Input.GetKey(KeyCode.D))
        {
            joystickPlayers[0].position = new Vector3(
                joystickPlayers[0].position.x + SPEED,
                0,
                joystickPlayers[0].position.z);
            ResetTime();
        }
        else
        {
            for (var i = 0; i < joystickPlayers.Length; i++)
            {
                MoveJoystickPlayer(i, JoystickDiscovery.GetJoystick(i));
            }
        }
    }

    private void MoveJoystickPlayer(int index, Vector3 position)
    {
        var x = joystickPlayers[index].position.x + (position.x * SPEED);
        var z = joystickPlayers[index].position.z + (position.z * SPEED);
        //print(position.x);
        if ((position.x > 0 && position.x < DEADZONE_X) ||
            (position.x < 0 && position.x > -DEADZONE_X))
        {
            if (index == 0)
            {
                ContinueTime();
            }
        }
        else
        {
            if (x < minX)
            {
                x = minX;
            }
            else if (x > maxX)
            {
                x = maxX;
            }
            else
            {
                if (index == 0)
                {
                    ResetTime();
                }
            }
            joystickPlayers[index].position = new Vector3(
                x,
                joystickPlayers[index].position.y,
                joystickPlayers[index].position.z);
        }
        if ((position.z > 0 && position.z < DEADZONE_Z) ||
            (position.z < 0 && position.z > -DEADZONE_Z))
        {
            if (index == 0)
            {
                ContinueTime();
            }
        }
        else
        {
            if (z < MIN_Z)
            {
                z = MIN_Z;
            }
            else if (z > MAX_Z)
            {
                z = MAX_Z;
            }
            else
            {
                if (index == 0)
                {
                    ResetTime();
                }
            }
            joystickPlayers[index].position = new Vector3(
                joystickPlayers[index].position.x,
                joystickPlayers[index].position.y,
                z);
        }
        //print(timeCurrent);
        if (timeCurrent > TIME_TIMEOUT)
        {
            Scene scene = SceneManager.GetActiveScene(); SceneManager.LoadScene(scene.name);
            //ResetTime();
        }
        /*
        if (position.x < THRESHOLD_X && position.x > -THRESHOLD_X)
        {
            return;
        }
        if (position.z < THRESHOLD_Z && position.z > -THRESHOLD_Z)
        {
            return;
        }
        */
    }

    private void ResetTime()
    {
        timeCurrent = 0;
        //isTimeBeforeFirstMovement = true;
    }

    private void ContinueTime()
    {
        timeCurrent += Time.deltaTime;
        print(timeCurrent);
        isTimeBeforeFirstMovement = false;
    }
}
