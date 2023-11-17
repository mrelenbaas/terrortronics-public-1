using System.Collections;
using System.Collections.Generic;
//using System.IO;
//using System.Runtime.Serialization.Formatters.Binary;
using UnityEngine;

public class GameLoader : MonoBehaviour
{
    public static string saveDirectory = "Saves";
    public static string saveName = "saveGame";


    public void LoadFromFile2()
    {
        //int[] intArray = LoadFromFile();
        // TODO: Route this int array.
    }
    public static int[] LoadFromFile()
    {
        return new int[] {
            PlayerPrefs.GetInt(
                SaveGameData.stringArray[(int)SaveGameData.IntArray.SaveGame],
                (int)SaveGameData.SaveGame.BeatenGame),  // 0: 0 = No save game, 1 = saved game, 2 = beaten game.
            PlayerPrefs.GetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.MessageSpeed], 4),  // 1:  Message speed (0 - 9).
            PlayerPrefs.GetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.ScoreTotal], 0), // 2:  Score total.
            PlayerPrefs.GetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score1x1], 0), // 3:  1.1 score.
            PlayerPrefs.GetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score1x2], 0), // 4:  1.2 score.
            PlayerPrefs.GetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score2x1], 0), // 5:  2.1 score.
            PlayerPrefs.GetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score2x2], 0), // 6:  2.2 score.
            PlayerPrefs.GetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score3x1], 0), // 7:  3.1 score.
            PlayerPrefs.GetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score3x2], 0), // 8:  3.2 score.
            PlayerPrefs.GetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score4x1], 0), // 9:  4.1 score.
            PlayerPrefs.GetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score4x2], 0), // 10: 4.2 score.
            PlayerPrefs.GetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score5x1], 0), // 11: 5.1 score.
            PlayerPrefs.GetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score5x2], 0), // 12: 5.2 score.
            PlayerPrefs.GetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score6x1], 0), // 13: 6.1 score.
            PlayerPrefs.GetInt(SaveGameData.stringArray[(int)SaveGameData.IntArray.Score6x2], 0), // 14: 6.2 score.
        };
    }
}
