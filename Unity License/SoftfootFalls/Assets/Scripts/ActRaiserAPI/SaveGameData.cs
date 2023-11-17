using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[Serializable]
public struct SaveGameData
{
    public enum SaveGame
    {
        None,
        SavedGame,
        BeatenGame
    }

    public enum IntArray
    {
        SaveGame,
        MessageSpeed,
        ScoreTotal,
        Score1x1,
        Score1x2,
        Score2x1,
        Score2x2,
        Score3x1,
        Score3x2,
        Score4x1,
        Score4x2,
        Score5x1,
        Score5x2,
        Score6x1,
        Score6x2
    }
    public static string[] stringArray = new string[] {
        "Save Game",  // 0: 0 = No save game, 1 = saved game, 2 = beaten game.
        "Message Speed",  // 1:  Message speed (0 - 9).
        "Score Total", // 2:  Score total.
        "Score 1x1", // 3:  1.1 score.
        "Score 1x2", // 4:  1.2 score.
        "Score 2x1", // 5:  2.1 score.
        "Score 2x2", // 6:  2.2 score.
        "Score 3x1", // 7:  3.1 score.
        "Score 3x2", // 8:  3.2 score.
        "Score 4x1", // 9:  4.1 score.
        "Score 4x2", // 10: 4.2 score.
        "Score 5x1", // 11: 5.1 score.
        "Score 5x2", // 12: 5.2 score.
        "Score 6x1", // 13: 6.1 score.
        "Score 6x2", // 14: 6.2 score.
    };
    public static int[] intArray = new int[] {
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

    public int health;
    public int money;
    public string playerName;
}
