/*
 * Title: VideoBackground file.
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
using UnityEngine.Video;

public class VideoBackground : MonoBehaviour
{
    [SerializeField]
    private VideoPlayer videoPlayer;

    [SerializeField]
    private VideoClip[] videoClips;

    /*
    private VideoClip gameVideoClip = null;
    public VideoClip VideoClips
    {
        set
        {
            gameVideoClip = value;
            if (gameVideoClip == null)
            {
                videoPlayer.clip = videoClips[Random.Range(0, videoClips.Length)];
            }
            else
            {
                videoPlayer.Stop();
                videoPlayer.clip = gameVideoClip;
                videoPlayer.Play();
            }
        }
    }
    */


    public void RestartPlaying()
    {
        videoPlayer.Stop();
        videoPlayer.clip = videoClips[Random.Range(0, videoClips.Length)];
        videoPlayer.Play();
    }

    void Start()
    {
        videoPlayer.clip = videoClips[Random.Range(0, videoClips.Length)];
        videoPlayer.loopPointReached += EndReached;
    }

    void EndReached(UnityEngine.Video.VideoPlayer vp)
    {
        //vp.playbackSpeed = vp.playbackSpeed / 10.0F;
        vp.clip = videoClips[Random.Range(0, videoClips.Length)];
    }
}
