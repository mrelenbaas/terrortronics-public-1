/*
 * Title: Games file.
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
using System.IO;
using Unity.VisualScripting;
using UnityEngine;

public class Games : MonoBehaviour
{
    [SerializeField]
    private GameObject gamePrefab;

    [SerializeField]
    private GameObject videoBackgroundGames;

    private const float X_START = -17.6f;
    private const float Z_STEP = 20;
    private float xStart = X_START;
    private float zStart = 5;
    private float xStep = 7;
    private float xIndex;


    void Start()
    {
        string path = Environment.GetFolderPath(Environment.SpecialFolder.Desktop) + "\\TCTA\\";
        string[] directories = Directory.GetDirectories(path);
        for (var i = 0; i < directories.Length; i++)
        {
            string[] files = Directory.GetFiles(directories[i]);
            if (Directory.Exists(directories[i]))
            {
            }
            var isSingleGameDirectoryFound = false;
            string[] subdirectories = Directory.GetDirectories(directories[i]);
            string[] subfiles;
            var isTextFileFound = false;
            var isVideoFileFound = false;
            var isThumbnailFound = false;
            string textFile = "";
            string videoFile = "";
            string thumbnailFile = "";
            var count = 0;
            if (subdirectories.Length == 1)
            {
                isSingleGameDirectoryFound = true;
                subfiles = Directory.GetFiles(directories[i]);
                for (var j = 0; j < subfiles.Length; j++)
                {
                    if (subfiles[j].Split(".")[1].ToLower().Contains("txt"))
                    {
                        textFile = subfiles[j];
                        isTextFileFound = true;
                    }
                    if (subfiles[j].Split(".")[1].ToLower().Contains("mp4"))
                    {
                        videoFile = subfiles[j];
                        isVideoFileFound = true;
                    }
                }
            }
            if (isSingleGameDirectoryFound
                && isTextFileFound
                && isVideoFileFound)
            {
                count++;
            }
            isSingleGameDirectoryFound = false;
            isTextFileFound = false;
            isVideoFileFound = false;
            GameObject[] games = new GameObject[count];
            count = 0;
            string gameFilename = "";
            if (subdirectories.Length == 1)
            {
                string[] subsubfiles = Directory.GetFiles(subdirectories[0]);
                for (var k = 0; k < subsubfiles.Length; k++)
                {
                    try
                    {
                        //print("subsubfiles[k]: " + subsubfiles[k]);
                        if (subsubfiles[k].Split(".")[1].ToLower().Contains("exe")
                            && !subsubfiles[k].Split(".")[0].Contains("CrashHandler"))
                        {
                            gameFilename = subsubfiles[k];
                            //print("gameFilename: " + gameFilename);
                            break;
                        }
                    }
                    catch (System.Exception e)
                    {
                        print("ERROR: " + subsubfiles[k] + " is an unexpected format.");
                    }
                }
                isSingleGameDirectoryFound = true;
                subfiles = Directory.GetFiles(directories[i]);
                for (var j = 0; j < subfiles.Length; j++)
                {
                    if (subfiles[j].Split(".")[1].ToLower().Contains("txt"))
                    {
                        textFile = subfiles[j];
                        isTextFileFound = true;
                    }
                    if (subfiles[j].Split(".")[1].ToLower().Contains("mp4"))
                    {
                        videoFile = subfiles[j];
                        isVideoFileFound = true;
                    }
                    if (subfiles[j].Split(".")[1].ToLower().Contains("png"))
                    {
                        thumbnailFile = subfiles[j];
                        isThumbnailFound = true;
                    }
                }
            }
            if (isSingleGameDirectoryFound
                && isTextFileFound
                && isVideoFileFound
                /*&& isThumbnailFound*/)
            {
                GameObject game = Instantiate(gamePrefab);
                game.transform.parent = transform;
                game.transform.position = new Vector3(
                    xStart,
                    game.transform.position.y,
                    zStart);
                xStart += xStep;
                xIndex++;
                if (xIndex > 5)
                {
                    xStart = X_START;
                    zStart += Z_STEP;
                    xIndex = 0;
                }
                game.name = directories[i].Split("\\")[directories[i].Split("\\").Length - 1];
                NewGame newGame = game.GetComponent<NewGame>();
                newGame.Title = game.name;
                newGame.Description = System.IO.File.ReadAllText(textFile);
                newGame.GameFilename = gameFilename;
                newGame.VideoFilename = videoFile;
                newGame.ThumbnailFilename = thumbnailFile;
                newGame.VideoBackgroundGames = videoBackgroundGames;
                //print("Arcade Cabinet directory found.");
                //print(newGame.Title);
                //print(newGame.Description);
                //print(newGame.GameFilename);
                //print(newGame.VideoFilename);
                games[count] = game;
                count++;
            }
        }
    }

    void Update()
    {
        
    }
}
