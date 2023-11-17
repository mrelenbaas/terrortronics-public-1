/*
 * Title: SketchShader file.
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

using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System;
using System.Text;
using UnityEngine.Rendering;

public class SketchShader : MonoBehaviour
{
    private const string FILENAME_EXTENSION = ".png";
    //private const string FILENAME_PATH = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
    private const string FILENAME = "image_to_process_";
    private int filenameCounter = 0;

    [SerializeField]
    private RawImage finalCutout;
    private Texture2D finalCutoutAtStart;

    private bool isBlocked;

    private Renderer myRenderer;

    private const string PIXEL_COROUTINE = "TakePictureCoroutine";
    private const int PIXEL_STEPS = 120;
    private int pixelCurrent;
    private int pixelTotal;
    private int pixelsPerFrame = WEBCAM_SIZE_WIDTH * (WEBCAM_SIZE_WIDTH / PIXEL_STEPS);
    private int pixelsProcessedThisFrame;

    [SerializeField]
    private GameObject references;
    [SerializeField]
    private RawImage[] referencesGrandchildren;
    private Color[] referenceColors;

    [SerializeField]
    private GameObject semiTransparency;
    [SerializeField]
    private GameObject semiTransparencyLeft;
    [SerializeField]
    private GameObject semiTransparencyRight;
    public int semiTransparencyIndex;

    [SerializeField]
    private GameObject timer;
    private int timerPercentage;

    private const int WEBCAM_FPS = 60;
    private const string WEBCAM_NAME_PRIMARY = "USB  Live camera";
    private const string WEBCAM_NAME_SECONDARY = "FaceTime HD Camera (Built-in)";
    private const int WEBCAM_SIZE_HEIGHT = 480;
    private const int WEBCAM_SIZE_WIDTH = 640;
    [SerializeField]
    private RawImage webcam;
    private WebCamTexture webcamTexture;
    private Texture2D webcamTextureCopy;


    private void Start()
    {
        myRenderer = GetComponent<Renderer>();
        finalCutoutAtStart = new Texture2D(finalCutout.mainTexture.width, finalCutout.mainTexture.height, TextureFormat.ARGB32, false);
        finalCutoutAtStart = CopyRawImageToTexture2D(finalCutout);
        referenceColors = new Color[referencesGrandchildren.Length];
        Color[] webcamColors = new Color[WEBCAM_SIZE_WIDTH * WEBCAM_SIZE_HEIGHT];
        for (var i = 0; i < webcamColors.Length; i++)
        {
            webcamColors[i] = Color.clear;
        }
        webcamTextureCopy = new Texture2D(WEBCAM_SIZE_WIDTH, WEBCAM_SIZE_HEIGHT);
        webcamTextureCopy.SetPixels(webcamColors);
        for (var i = 0; i < referencesGrandchildren.Length; i++)
        {
            referencesGrandchildren[i].enabled = false;
        }
        var webcamName = WEBCAM_NAME_SECONDARY;
        for (var i = 0; i < WebCamTexture.devices.Length; i++)
        {
            if (WebCamTexture.devices[i].name.Equals(WEBCAM_NAME_PRIMARY))
            {
                webcamName = WEBCAM_NAME_PRIMARY;
                break;
            }
        }
        webcamTexture = new WebCamTexture(webcamName);
        webcamTexture.requestedWidth = WEBCAM_SIZE_WIDTH;
        webcamTexture.requestedHeight = WEBCAM_SIZE_HEIGHT;
        webcamTexture.requestedFPS = WEBCAM_FPS;
        webcam.material.mainTexture = webcamTexture;
        webcamTexture.Play();
    }

    /// <summary>
    /// The main function.
    /// </summary>
    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space)
            && !isBlocked)
        {
            TakePicture();
        }
        //if (Input.GetKeyDown(KeyCode.P))
        //{
            //SavePicture();
        //}
    }

    private void ClearTextures()
    {
        var texture2D = new Texture2D(finalCutout.mainTexture.width, finalCutout.mainTexture.height, TextureFormat.ARGB32, false);
        for (var i = 0; i < finalCutout.texture.width; i++)
        {
            for (var j = 0; j < finalCutout.texture.height; j++)
            {
                texture2D.SetPixel(i, j, Color.clear);
                webcamTextureCopy.SetPixel(i, j, Color.clear);
            }
        }
        texture2D.Apply();
        finalCutout.texture = texture2D;
        webcamTextureCopy.Apply();
    }

    private Texture2D CopyRawImageToTexture2D(RawImage rawImage)
    {
        var texture2D = new Texture2D(rawImage.mainTexture.width, rawImage.mainTexture.height, TextureFormat.ARGB32, false);
        texture2D.SetPixels(((Texture2D)rawImage.texture).GetPixels());
        texture2D.Apply();
        return texture2D;
    }

    private void SavePicture(Texture2D texture2D)
    {
        //var texture2D = new Texture2D(webcamTexture.width, webcamTexture.height);
        //texture2D.SetPixels(webcamTexture.GetPixels());
        //texture2D.Apply();
        print('0');
        var filename = new StringBuilder()
            .Append(Environment.GetFolderPath(Environment.SpecialFolder.Desktop))
            .Append("/")
            .Append(FILENAME)
            .Append(semiTransparencyIndex)
            .Append(FILENAME_EXTENSION)
            .ToString();
        print(filename);
        print(semiTransparencyIndex);
        System.IO.File.WriteAllBytes(filename, texture2D.EncodeToPNG());
        System.IO.File.WriteAllBytes(new StringBuilder()
            .Append(Environment.GetFolderPath(Environment.SpecialFolder.Desktop))
            .Append("/")
            .Append(filenameCounter)
            .Append(" ")
            .Append(System.DateTime.Now.Year)
            .Append(" ")
            .Append(System.DateTime.Now.Month)
            .Append(" ")
            .Append(System.DateTime.Now.Day)
            .Append(" ")
            .Append(System.DateTime.Now.Hour)
            .Append(" ")
            .Append(System.DateTime.Now.Minute)
            .Append(" ")
            .Append(System.DateTime.Now.Second)
            .Append(".png")
            .ToString(), texture2D.EncodeToPNG());
        filenameCounter++;
    }

    public void TakePicture()
    {
        ClearTextures();
        var texture2Ds = new Texture2D[referencesGrandchildren.Length];
        for (var i = 0; i < texture2Ds.Length; i++)
        {
            texture2Ds[i] = new Texture2D(WEBCAM_SIZE_WIDTH, WEBCAM_SIZE_HEIGHT);
        }
        for (int y = 0; y < WEBCAM_SIZE_HEIGHT; y++)
        {
            for (int x = 0; x < WEBCAM_SIZE_WIDTH; x++)
            {
                for (var i = 0; i < texture2Ds.Length; i++)
                {
                    texture2Ds[i].SetPixel(x, y, webcamTexture.GetPixel(x, y));
                }
            }
        }
        for (var i = 0; i < texture2Ds.Length; i++)
        {
            texture2Ds[i].Apply();
        }
        pixelCurrent = 0;
        pixelsProcessedThisFrame = 0;
        pixelTotal = myRenderer.material.mainTexture.width * myRenderer.material.mainTexture.height;
        for (var i = 0; i < referencesGrandchildren.Length; i++)
        {
            referencesGrandchildren[i].enabled = true;
        }
        isBlocked = true;
        TakePictureStart();
    }

    private IEnumerator TakePictureCoroutine()
    {
        var count = 0;
        var texture2D = new Texture2D(webcamTextureCopy.width, webcamTextureCopy.height, TextureFormat.ARGB32, false);
        for (int y = 0; y < WEBCAM_SIZE_HEIGHT; y++)
        {
            for (int x = 0; x < WEBCAM_SIZE_WIDTH; x++)
            {
                for (var i = 0; i < referenceColors.Length; i++)
                {
                    referenceColors[i] = ((Texture2D)referencesGrandchildren[i].texture).GetPixel(x, y);
                }
                if (referenceColors[semiTransparencyIndex] == Color.white)
                {
                    webcamTextureCopy.SetPixel(x, y, webcamTexture.GetPixel(x, y));
                }
                pixelCurrent++;
                if (pixelCurrent >= WEBCAM_SIZE_WIDTH * WEBCAM_SIZE_HEIGHT)
                {
                    texture2D.SetPixels(webcamTextureCopy.GetPixels());
                    finalCutout.texture = texture2D;
                    timer.GetComponent<RectTransform>().sizeDelta = new Vector2(Screen.width, timer.GetComponent<RectTransform>().sizeDelta.y);
                    isBlocked = false;
                    SavePicture(texture2D);
                    TakePictureStop();
                }
                pixelsProcessedThisFrame++;
                timerPercentage = (int)(((float)pixelCurrent / pixelTotal) * 100.0f);
                if (pixelsProcessedThisFrame >= pixelsPerFrame)
                {
                    texture2D.Apply();
                    timer.GetComponent<RectTransform>().sizeDelta = new Vector2((Screen.width * (float)(timerPercentage / 100.0f)), timer.GetComponent<RectTransform>().sizeDelta.y);
                    pixelsProcessedThisFrame = 0;
                    //SavePicture(texture2D);
                    yield return null;
                }
                count++;
            }
        }
        //SavePicture(texture2D);
    }

    private void TakePictureStart()
    {
        StartCoroutine(PIXEL_COROUTINE);
    }

    private void TakePictureStop()
    {
        StopCoroutine(PIXEL_COROUTINE);
    }

    public void ScrollNext()
    {
        semiTransparencyIndex++;
        if (semiTransparencyIndex >= semiTransparency.transform.childCount)
        {
            semiTransparencyIndex = 0;
        }
        ScrollNextOrPrevious();
    }

    public void ScrollPrevious()
    {
        semiTransparencyIndex--;
        if (semiTransparencyIndex < 0)
        {
            semiTransparencyIndex = semiTransparency.transform.childCount - 1;
        }
        ScrollNextOrPrevious();
    }

    private void ScrollNextOrPrevious()
    {
        ClearTextures();
        for (var i = 0; i < semiTransparency.transform.childCount; i++)
        {
            semiTransparency.transform.GetChild(i).gameObject.SetActive(false);
            semiTransparencyLeft.transform.GetChild(i).gameObject.SetActive(false);
            semiTransparencyRight.transform.GetChild(i).gameObject.SetActive(false);
        }
        semiTransparency.transform.GetChild(semiTransparencyIndex).gameObject.SetActive(true);
        semiTransparencyLeft.transform.GetChild(semiTransparencyIndex).gameObject.SetActive(true);
        semiTransparencyRight.transform.GetChild(semiTransparencyIndex).gameObject.SetActive(true);
        for (var i = 0; i < references.transform.childCount; i++)
        {
            references.transform.GetChild(i).gameObject.SetActive(false);
        }
        references.transform.GetChild(semiTransparencyIndex).gameObject.SetActive(true);
    }
}
