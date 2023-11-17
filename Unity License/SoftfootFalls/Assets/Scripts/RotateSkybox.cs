/*
 * Title: RotateSkybox file.
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

public class RotateSkybox : MonoBehaviour
{
    [SerializeField]
    private Animator animator;


    void Update()
    {
        //if (Menus.isPaused
        //    || Menus.isStart
        //    || Menus.isTownBuilderMenuVisible
        //    || Menus.isSkyPalaceMenuVisible)
        //{
        //    if (animator.enabled)
        //    {
        //        animator.enabled = false;
        //    }
        //    return;
        //}
        //if (!animator.enabled)
        //{
            //animator.enabled = true;
        //}
        //RenderSettings.skybox.SetFloat("_Rotation", Time.time * 0.4f);
    }
}
