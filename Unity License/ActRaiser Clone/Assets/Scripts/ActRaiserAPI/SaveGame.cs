/*
 * Title: SaveGame file.
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

public class SaveGame : MonoBehaviour
{
    public static string saveName = "saveGame";
    public static string directoryName = "Saves";
    public static SaveGameData saveGameData;

    public void SaveToFile2()
    {
        // TODO: Remember that this is just a dummy setup.
        SaveToFile(new int[] { 2, 4 });
    }
    public static void SaveToFile(int[] intArray)
    {
        if (!Directory.Exists(directoryName))
            Directory.CreateDirectory(directoryName);

        BinaryFormatter formatter = new BinaryFormatter();

        FileStream saveFile = File.Create(directoryName + "/" + saveName + ".bin");

        formatter.Serialize(saveFile, saveGameData);

        saveFile.Close();

        print("Game saved to: " + Directory.GetCurrentDirectory().ToString() + "/Saves/" + saveName + ".bin");
    }

    // TODO: Update this. This is currently a clone of SaveToFile().
    public static void SaveToFileMin(int[] intArray)
    {
        if (!Directory.Exists(directoryName))
            Directory.CreateDirectory(directoryName);

        BinaryFormatter formatter = new BinaryFormatter();

        FileStream saveFile = File.Create(directoryName + "/" + saveName + ".bin");

        formatter.Serialize(saveFile, saveGameData);

        saveFile.Close();

        print("Game saved to: " + Directory.GetCurrentDirectory().ToString() + "/Saves/" + saveName + ".bin");
    }
}
