/*
 * Title: Player file.
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

public abstract class Player : MonoBehaviour
{
    public const int I_DEFAULT = 8;
    public const int J_DEFAULT = 6;

    public static bool isInvincible;
    public static bool isImmobilized;

    public static int healthPoints;
    public static int healthPointsMax;
    public static int level;
    public static int spellPoints;
    public static int spellPointsax;
    public static int i = I_DEFAULT;
    public static int j = J_DEFAULT;
    public static int previousI;
    public static int previousJ;

    public static int grayBoxI;
    public static int grayBoxJ;

    public static int yellowBoxI = 3;
    public static int yellowBoxJ = 3;
    public static string yellowBoxDirection = "";

    public static int offsetX;
    public static int offsetY;

    public static int tempJ = -1;
    public static int tempI = -1;

    public static bool isStrengthOfAngelActive;

    public static void ResetIJ()
    {
        tempJ = -1;
        tempI = -1;
        previousI = 0;
        previousJ = 0;
    }

    public static void HealthPointsIncrease()
    {
        healthPoints++;
        print(healthPoints);
        if (healthPoints > healthPointsMax)
        {
            healthPoints = healthPointsMax;
        }
    }
    public static void HealthPointsDecrease()
    {
        healthPoints--;
        if (healthPoints <= 0)
        {
            isImmobilized = true;
            healthPoints = 0;
        }
    }

    public static void PlayerSpellPointsIncrease()
    {
        Player.spellPoints++;
        if (Player.spellPoints > Player.spellPointsax)
        {
            Player.spellPoints = Player.spellPointsax;
        }

    }
    public static void PlayerSpellPointsDecrease()
    {
        Player.spellPoints--;
        if (Player.spellPoints < 0)
        {
            Player.spellPoints = 0;
        }
    }

    public const int SOURCE_OF_MAGIC_TOTAL = 8;
    public static int sourceOfMagicCount;
    public static void SourceOfMagicIncrease()
    {
        sourceOfMagicCount++;
    }
}
