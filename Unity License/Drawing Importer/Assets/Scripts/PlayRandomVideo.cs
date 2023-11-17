/*
 * Title: PlayRandomVideo file.
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
using System.Drawing;
using System.IO;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Video;

public class PlayRandomVideo : MonoBehaviour
{
    public enum CubePosition { Top, Middle, Bottom }

    [SerializeField]
    private CubePosition cubePosition;

    [SerializeField]
    private VideoPlayer videoPlayer;

    [SerializeField]
    private VideoClip[] videoClips;

    [SerializeField]
    private RawImage rawImage;

    [SerializeField]
    private RawImage topRawImage;

    [SerializeField]
    private RawImage middleRawImage;

    [SerializeField]
    private RawImage bottomRawImage;

    private Texture2D videoFrame;
    private UnityEngine.Color[] transparentPixels;

    void OnEnable()
    {
        PlayRandom();
    }

    void Start()
    {
        transparentPixels = new UnityEngine.Color[640 * 480];
        for (var i = 0; i < transparentPixels.Length; i++)
        {
            transparentPixels[i] = new UnityEngine.Color(1.0f, 0.0f, 0.0f, 0.0f);
        }
        videoFrame = new Texture2D(640, 480);
        videoPlayer.sendFrameReadyEvents = true;
        videoPlayer.frameReady += OnNewFrame;
        videoPlayer.loopPointReached += EndReached;
        videoPlayer.Play();
    }

    void EndReached(UnityEngine.Video.VideoPlayer vp)
    {
        PlayRandom();
    }

    void OnNewFrame(VideoPlayer source, long frameIdx)
    {
        RenderTexture renderTexture = source.texture as RenderTexture;


        if (videoFrame.width != renderTexture.width || videoFrame.height != renderTexture.height)
        {
            videoFrame.Reinitialize(renderTexture.width, renderTexture.height);
        }
        RenderTexture.active = renderTexture;
        videoFrame.ReadPixels(new Rect(0, 0, renderTexture.width, renderTexture.height), 0, 0);
        videoFrame.Apply();
        RenderTexture.active = null;

        //((Texture2D)rawImage.texture).SetPixels(transparentPixels);
        UnityEngine.Color[] finalPixels = new UnityEngine.Color[transparentPixels.Length];
        UnityEngine.Color[] currentPixels = videoFrame.GetPixels();
        for (var i = 0; i < finalPixels.Length; i++)
        {
            switch (cubePosition)
            {
                case CubePosition.Top:
                    if (i > 204800 && i <= 307200)
                    {
                        finalPixels[i] = currentPixels[i];
                    }
                    else
                    {
                        finalPixels[i] = transparentPixels[i];
                    }
                    break;
                case CubePosition.Middle:
                    if (i > 102400 && i <= 204800)
                    {
                        finalPixels[i] = currentPixels[i];
                    }
                    else
                    {
                        finalPixels[i] = transparentPixels[i];
                    }
                    break;
                case CubePosition.Bottom:
                    if (i > 0 && i <= 102400)
                    {
                        finalPixels[i] = currentPixels[i];
                    }
                    else
                    {
                        finalPixels[i] = transparentPixels[i];
                    }
                    break;
            }
        }
        Texture2D texture = new Texture2D(640, 480);
        texture.SetPixels(finalPixels);
        texture.Apply();
        rawImage.texture = texture;

        switch (cubePosition)
        {
            case CubePosition.Top:
                Texture2D topTexure = new Texture2D(640, 480);
                topTexure.SetPixels(finalPixels);
                topTexure.Apply();
                topRawImage.texture = topTexure;
                break;
            case CubePosition.Middle:
                Texture2D middleTexure = new Texture2D(640, 480);
                middleTexure.SetPixels(finalPixels);
                middleTexure.Apply();
                middleRawImage.texture = middleTexure;
                break;
            case CubePosition.Bottom:
                Texture2D bottomTexure = new Texture2D(640, 480);
                bottomTexure.SetPixels(finalPixels);
                bottomTexure.Apply();
                bottomRawImage.texture = bottomTexure;
                break;
        }

        //targetColor = CalculateAverageColorFromTexture(videoFrame);
        //lSource.color = targetColor;
    }

    void PlayRandom()
    {
        var count = 0;
        string[] desktopFiles = Directory.GetFiles("C:\\Users\\" + Environment.UserName + "\\Desktop\\");
        for (var i = 0; i < desktopFiles.Length; i++)
        {
            if (desktopFiles[i].Contains(".mp4"))
            {
                count++;
            }
        }
        string[] desktopVideos = new string[count];
        count = 0;
        for (var i = 0; i < desktopFiles.Length; i++)
        {
            if (desktopFiles[i].Contains(".mp4"))
            {
                desktopVideos[count] = desktopFiles[i];
                count++;
            }
        }
        if (desktopVideos.Length != 0)
        {
            videoPlayer.url = desktopVideos[UnityEngine.Random.Range(0, desktopVideos.Length)];
        }
        else
        {
            PlayRandom();
        }
    }
}
