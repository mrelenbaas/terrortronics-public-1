/*
 * Title: PlayerFollower file.
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

public class PlayerFollower : MonoBehaviour
{
    [SerializeField]
    private GameObject mainCamera;

    [SerializeField]
    private GameObject player;

    [SerializeField]
    private GameObject cameraHook;

    private bool isPlayerStationary = true;
    private Vector3 originalPosition;
    private Vector3[] rawPositions = new Vector3[60];
    private Vector3 smoothedPosition;
    private int positionIndex;

    void Start()
    {
        originalPosition = new Vector3(
            player.transform.position.x,
            player.transform.position.y,
            player.transform.position.z);
        for (var i = 0; i < rawPositions.Length; i++)
        {
            rawPositions[i] = new Vector3(
                transform.position.x,
                transform.position.y,
                transform.position.z);
        }
    }

    void Update()
    {
        //print(player.transform.position + " != " + originalPosition);
        if (isPlayerStationary &&
            player.transform.position != originalPosition)
        {
            isPlayerStationary = false;
        }
        else if (!isPlayerStationary)
        {
            rawPositions[positionIndex] = new Vector3(
                cameraHook.transform.position.x,
                cameraHook.transform.position.y,
                cameraHook.transform.position.z);
            smoothedPosition = Vector3.zero;
            for (var i = 0; i < rawPositions.Length; i++)
            {
                smoothedPosition += rawPositions[i];
            }
            smoothedPosition /= rawPositions.Length;
            positionIndex++;
            if (positionIndex >= rawPositions.Length)
            {
                positionIndex = 0;
            }
            transform.position = smoothedPosition;
            //transform.position = cameraHook.transform.position;
        }
    }
}
