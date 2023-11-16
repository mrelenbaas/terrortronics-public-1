/*
 * Title: NewGame file.
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
using TMPro;

public class NewGame : MonoBehaviour
{
    [SerializeField]
    private GameObject cubeTriggered;

    [SerializeField]
    private GameObject cubeNotTriggered;

    //[SerializeField]
    //JoystickDiscovery joystickDiscovery;

    //[SerializeField]
    //private string filename;

    [SerializeField]
    private TMP_Text titleTMP;

    [SerializeField]
    private TMP_Text descriptionTMP;

    [SerializeField]
    private GameObject quad;

    [SerializeField]
    private GameObject quad1;


    public string Title { get { return titleTMP.text; } set { titleTMP.text = value; } }
    public string Description { get { return descriptionTMP.text; } set { descriptionTMP.text = value; } }
    public string GameFilename { get; set; }
    public GameObject VideoBackgroundGames { private get; set; }
    public string VideoFilename { get; set; }
    //public GameObject Quad { get; set; }
    public string ThumbnailFilename { get; set; }


    void Start()
    {
        TurnOff();
    }

    private void Update()
    {
        if (Input.GetButton("Fire1")
            && cubeTriggered.activeSelf)
        {
            //print("Now");
            //print(GameFilename);
            GameObject.Find("Joystick Discovery").GetComponent<JoystickDiscovery>().StartProcessWrapper(GameFilename);
        }
    }



    void OnTriggerEnter(Collider other)
    {
        if (other.tag.Contains("Player"))
        {
            other.GetComponent<JoystickPlayerChild>().EnableAndSetText(descriptionTMP.text);
            TurnOn();
        }
    }

    void OnTriggerExit(Collider other)
    {
        if (other.tag.Contains("Player"))
        {
            other.GetComponent<JoystickPlayerChild>().DisableText();
            TurnOff();
        }
    }

    private void TurnOn()
    {
        if (cubeTriggered.activeSelf)
        {
            return;
        }
        cubeTriggered.SetActive(true);
        cubeNotTriggered.SetActive(false);
        VideoBackgroundGames.GetComponent<MeshRenderer>().enabled = true;
        VideoBackgroundGames.GetComponent<VideoPlayer>().url = VideoFilename;
        VideoBackgroundGames.GetComponent<VideoBackground>().RestartPlaying();
        VideoBackgroundGames.transform.position = quad.transform.position;
        VideoBackgroundGames.transform.rotation = quad.transform.rotation;
        VideoBackgroundGames.transform.localScale = quad.transform.localScale;
        print(ThumbnailFilename);
        quad1.GetComponent<MeshRenderer>().materials[0] = Resources.Load(ThumbnailFilename) as Material;
        quad.SetActive(false);
        quad1.SetActive(false);
        //GameObject.Find("Video Background (Super Future Template)").GetComponent<MeshRenderer>().enabled = false;
    }

    private void TurnOff()
    {
        if (cubeNotTriggered.activeSelf)
        {
            return;
        }
        cubeTriggered.SetActive(false);
        cubeNotTriggered.SetActive(true);
        VideoBackgroundGames.GetComponent<MeshRenderer>().enabled = false;
        quad.SetActive(true);
        quad1.SetActive(true);
        //GameObject.Find("Video Background (Super Future Template)").GetComponent<MeshRenderer>().enabled = true;
        //GameObject.Find("Video Background (Super Future Template)").GetComponent<VideoBackground>().RestartPlaying();
    }
}
