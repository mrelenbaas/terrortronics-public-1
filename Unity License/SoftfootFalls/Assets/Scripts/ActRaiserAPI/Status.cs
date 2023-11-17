using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Status : MonoBehaviour
{
    public static readonly int scoreFillmoreActIMax = 20200;
    // TODO: Remember to fill this in at the end.
    public static readonly int scoreFillmoreActIIMax;
    public static readonly int scoreBloodpoolActIMax;
    public static readonly int scoreBloodpoolActIIMax;
    public static readonly int scoreKasandoraActIMax;
    public static readonly int scoreKasandoraActIIMax;
    public static readonly int scoreAitosActIMax;
    public static readonly int scoreAitosActIIMax;
    public static readonly int scoreMarahnaActIMax;
    public static readonly int scoreMarahnaActIIMax;
    public static readonly int scoreNorthwallActIMax;
    public static readonly int scoreNorthwallActIIMax;

    public static int score;
    public static int scoreFillmoreActI;
    public static int scoreFillmoreActII;
    public static int scoreBloodpoolActI;
    public static int scoreBloodpoolActII;
    public static int scoreKasandoraActI;
    public static int scoreKasandoraActII;
    public static int scoreAitosActI;
    public static int scoreAitosActII;
    public static int scoreMarahnaActI;
    public static int scoreMarahnaActII;
    public static int scoreNorthwallActI;
    public static int scoreNorthwallActII;

    public static void AddUpScore()
    {
        score =
            scoreAitosActI
            + scoreAitosActII
            + scoreBloodpoolActI
            + scoreBloodpoolActII
            + scoreFillmoreActI
            + scoreFillmoreActII
            + scoreKasandoraActI
            + scoreKasandoraActII
            + scoreMarahnaActI
            + scoreMarahnaActII
            + scoreNorthwallActI
            + scoreNorthwallActII;
        SaveGameData.intArray[2] = score;
        SaveGameData.intArray[3] = scoreFillmoreActI;
        SaveGameData.intArray[4] = scoreFillmoreActII;
        SaveGameData.intArray[5] = scoreBloodpoolActI;
        SaveGameData.intArray[6] = scoreBloodpoolActII;
        SaveGameData.intArray[7] = scoreKasandoraActI;
        SaveGameData.intArray[8] = scoreKasandoraActII;
        SaveGameData.intArray[9] = scoreAitosActI;
        SaveGameData.intArray[10] = scoreAitosActII;
        SaveGameData.intArray[11] = scoreMarahnaActI;
        SaveGameData.intArray[12] = scoreMarahnaActII;
        SaveGameData.intArray[13] = scoreNorthwallActI;
        SaveGameData.intArray[14] = scoreNorthwallActII;
    }

    public static int bombsItemCount = 1;
    public static int ancientTabletItemCount;
    public static int bridgeItemCount;
    public static int compassItemCount;
    public static int harmoniousMusicItemCount;
    public static int herbItemCount;
    public static int loafOfBreadItemCount;
    public static int magicSkullItemCount;
    public static int sheepsFleeceItemCount;
    public static int sourceOfLifeItemCount;
    public static int sourceOfMagicItemCount;
    public static int strengthOfAngelItemCount;
    public static int wheatItemCount;
}
