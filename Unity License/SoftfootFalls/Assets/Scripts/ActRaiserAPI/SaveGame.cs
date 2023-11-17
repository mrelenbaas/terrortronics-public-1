using System.Collections;
using System.Collections.Generic;
//using System.IO;
//using System.Runtime.Serialization.Formatters.Binary;
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
        PlayerPrefs.SetInt(
            SaveGameData.stringArray[(int)SaveGameData.IntArray.SaveGame],
            intArray[0]);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.MessageSpeed], intArray[1]);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.ScoreTotal], intArray[2]);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score1x1], intArray[3]);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score1x2], intArray[4]);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score2x1], intArray[5]);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score2x2], intArray[6]);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score3x1], intArray[7]);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score3x2], intArray[8]);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score4x1], intArray[9]);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score4x2], intArray[10]);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score5x1], intArray[11]);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score5x2], intArray[12]);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score6x1], intArray[13]);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score6x2], intArray[14]);
    }

    // TODO: Update this. This is currently a clone of SaveToFile().
    public static void SaveToFileMin(int[] intArray)
    {
        PlayerPrefs.SetInt(
            SaveGameData.stringArray[(int)SaveGameData.IntArray.SaveGame], 
            (int)SaveGameData.SaveGame.BeatenGame);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.MessageSpeed], 4);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.ScoreTotal], 0);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score1x1], 0);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score1x2], 0);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score2x1], 0);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score2x2], 0);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score3x1], 0);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score3x2], 0);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score4x1], 0);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score4x2], 0);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score5x1], 0);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score5x2], 0);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score6x1], 0);
        PlayerPrefs.SetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score6x2], 0);
    }
}
