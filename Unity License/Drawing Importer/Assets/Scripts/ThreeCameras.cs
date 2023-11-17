/*
 * Title: ThreeCameras file.
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
using UnityEngine;
using UnityEngine.UI;

public class ThreeCameras : MonoBehaviour
{
    [SerializeField]
    private RawImage rawImageTop;

    //[SerializeField]
    //private RawImage rawImageMiddle;

    //[SerializeField]
    //private RawImage rawImageBottom;

    //private WebCamTexture webCamTextureTop;
    //private WebCamTexture webCamTextureMiddle;
    //private WebCamTexture webCamTextureBottom;

    //private const int SIZE = 100;
    //private int counter;
    //private int filenameCounter = 1;
    //public static bool block;
    //Texture2D[] savedTextures = new Texture2D[SIZE];


    void Start()
    {
        /*
        for (var i = 0; i < SIZE; i++)
        {
            savedTextures[i] = new Texture2D(640, 480);
        }
        */
        //webCamTextureTop = new WebCamTexture();
        //webCamTextureMiddle = new WebCamTexture();
        //webCamTextureBottom = new WebCamTexture();
        //webCamTextureTop.deviceName = WebCamTexture.devices[0].name;
        //webCamTextureMiddle.deviceName = WebCamTexture.devices[1].name;
        //webCamTextureBottom.deviceName = WebCamTexture.devices[2].name;
        //rawImageTop.texture = webCamTextureTop;
        //rawImageMiddle.texture = webCamTextureMiddle;
        //rawImageBottom.texture = webCamTextureBottom;
        //webCamTextureTop.Play();
        //webCamTextureMiddle.Play();
        //webCamTextureBottom.Play();
    }

    void Update()
    {
    }
}
