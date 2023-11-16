/*
 * Title: GameLoader file.
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
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using UnityEngine;

public class GameLoader : MonoBehaviour
{
    public static string saveDirectory = "Saves";
    public static string saveName = "saveGame";


    public void LoadFromFile2()
    {
        int[] intArray = LoadFromFile();
        // TODO: Route this int array.
    }
    public static int[] LoadFromFile()
    {
        BinaryFormatter formatter = new BinaryFormatter();

        FileStream saveFile = File.Open(saveDirectory + "/" + saveName + ".bin", FileMode.Open);

        SaveGameData loadData = (SaveGameData)formatter.Deserialize(saveFile);

        print("Loaded: " + loadData.playerName);
        // TODO: Route loaded data here.

        var intArray = new int[] {
            2,  // 0: 0 = No save game, 1 = saved game, 2 = beaten game.
            4,  // 1:  Message speed (0 - 9).
            -1, // 2:  Score total.
            -1, // 3:  1.1 score.
            -1, // 4:  1.2 score.
            -1, // 5:  2.1 score.
            -1, // 6:  2.2 score.
            -1, // 7:  3.1 score.
            -1, // 8:  3.2 score.
            -1, // 9:  4.1 score.
            -1, // 10: 4.2 score.
            -1, // 11: 5.1 score.
            -1, // 12: 5.2 score.
            -1, // 13: 6.1 score.
            -1, // 14: 6.2 score.
        };

        saveFile.Close();

        return intArray;
    }
}
