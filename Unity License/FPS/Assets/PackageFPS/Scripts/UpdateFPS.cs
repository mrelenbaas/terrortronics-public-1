/*
 * Title: UpdateFPS file.
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
using Unity.VisualScripting;
using UnityEngine;
using TMPro;
using System.Text;

public class UpdateFPS : MonoBehaviour
{
    public static long fpsPreviousThread;

    private int fpsCurrent;
    private int fpsPrevious;
    private float timeThisSecond;

    private float PERIOD = 1.0f;

    [SerializeField]
    private TMP_Text fpsPreviousText;

    [SerializeField]
    private TMP_Text fpsPreviousThreadText;

    void Update()
    {
        timeThisSecond += Time.deltaTime;
        if (timeThisSecond > PERIOD)
        {
            fpsPrevious = fpsCurrent;
            fpsCurrent = 0;
            timeThisSecond -= PERIOD;
            fpsPreviousText.text = "FPS (from Update function): " + new StringBuilder().Append(fpsPrevious).ToString();
        }
        else
        {
            fpsCurrent++;
        }
        fpsPreviousThreadText.text = "FPS (from Thread function): " + new StringBuilder().Append(fpsPreviousThread).ToString();
    }
}
