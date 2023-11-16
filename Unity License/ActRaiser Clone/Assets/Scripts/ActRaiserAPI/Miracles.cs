/*
 * Title: Miracles file.
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

public abstract class Miracles : MonoBehaviour
{
    public const int EARTHQUAKE_SP = 160;
    public const float EARTHQUAKE_TIME_PERIOD = 1f;
    public static bool isEarthquakeActive;
    public static bool isEarthquakePrimed;
    public static float earthquakeTimeSinceStartOfMiracle = -1.0f;
    public static void EarthquakeUpdatePeriod(
        int[,,] town,
        int grayBoxI,
        int grayBoxJ,
        int playerI,
        int playerJ,
        bool isInvincible,
        int townSize)
    {
        if (earthquakeTimeSinceStartOfMiracle == -1.0f)
        {
            return;
        }
        earthquakeTimeSinceStartOfMiracle += Timers.timeDelta;
        if (earthquakeTimeSinceStartOfMiracle >= EARTHQUAKE_TIME_PERIOD)
        {
            var result = false;
            for (var j = 0; j < townSize; j++)
            {
                for (var i = 0; i < townSize; i++)
                {
                    if (town[(int)Towns.Layers.EnemiesAndPlayer, i, j] >= 2
                        && town[(int)Towns.Layers.EnemiesAndPlayer, i, j] <= 5)
                    {
                        result = true;
                        earthquakeTimeSinceStartOfMiracle = -1.0f;
                        // TODO: Immobilize, not kill. Probably reset timer.
                        town[(int)Towns.Layers.EnemiesAndPlayer, i, j] = 0;
                    }
                    if (town[(int)Towns.Layers.Building, i, j] >= 1
                        && town[(int)Towns.Layers.Building, i, j] <= 9)
                    {
                        result = true;
                        town[(int)Towns.Layers.Building, i, j] = 0;
                    }
                }
            }
            if (result)
            {
                Player.isInvincible = false;
                //Menus.isEarthquakeSuccess = true;
                Timers.Reset();
            }
            else
            {
                Player.isInvincible = false;
                Menus.isEarthquakeFailure = true;
                Timers.Reset();
            }
        }
    }

    public const int WIND_SP = 80;
    public const float WIND_TIME_PERIOD = 1f;
    public static bool isWindActive;
    public static bool isWindPrimed;
    public static float windTimeSinceStartOfMiracle = -1.0f;
    public static void WindUpdatePeriod(
        int[,,] town,
        int grayBoxI,
        int grayBoxJ,
        int playerI,
        int playerJ,
        bool isInvincible,
        int townSize)
    {
        if (windTimeSinceStartOfMiracle == -1.0f)
        {
            return;
        }
        windTimeSinceStartOfMiracle += Timers.timeDelta;
        if (windTimeSinceStartOfMiracle >= WIND_TIME_PERIOD)
        {
            var result = false;
            for (var j = 0; j < townSize; j++)
            {
                for (var i = 0; i < townSize; i++)
                {
                    if (town[(int)Towns.Layers.EnemiesAndPlayer, i, j] >= 2
                        && town[(int)Towns.Layers.EnemiesAndPlayer, i, j] <= 5)
                    {
                        result = true;
                        windTimeSinceStartOfMiracle = -1.0f;
                        town[(int)Towns.Layers.EnemiesAndPlayer, i, j] = 0;
                    }
                }
            }
            if (result)
            {
                Player.isInvincible = false;
                //Menus.isWindSuccess = true;
                Timers.Reset();
            }
            else
            {
                Player.isInvincible = false;
                Menus.isWindFailure = true;
                Timers.Reset();
            }
        }
    }

    public const int SUNLIGHT_SP = 40;
    public const float SUNLIGHT_TIME_PERIOD = 1f;
    public static bool isSunlightActive;
    public static bool isSunlightPrimed;
    public static float sunlightTimeSinceStartOfMiracle = -1.0f;
    public static void SunlightUpdatePeriod(
        int[,,] town,
        int grayBoxI,
        int grayBoxJ,
        int playerI,
        int playerJ,
        bool isInvincible)
    {
        if (sunlightTimeSinceStartOfMiracle == -1.0f)
        {
            return;
        }
        sunlightTimeSinceStartOfMiracle += Timers.timeDelta;
        var k = 0;
        var result = false;
        for (var i = 0; i < 4; i++)
        {
            for (var j = 0; j < 4; j++)
            {
                if (sunlightTimeSinceStartOfMiracle >= SUNLIGHT_TIME_PERIOD)
                {
                    if (town[(int)Towns.Layers.LandModifier,
                        (grayBoxI * 4) + i,
                        (grayBoxJ * 4) + j] == 1
                        || town[(int)Towns.Layers.LandModifier,
                           (grayBoxI * 4) + i,
                           (grayBoxJ * 4) + j] == 2)
                    {
                        result = true;
                        town[(int)Towns.Layers.LandModifier,
                         (grayBoxI * 4) + i,
                         (grayBoxJ * 4) + j] = 0;
                    }
                }
                k++;
            }
        }
        if (result)
        {
            Player.isInvincible = false;
            //Menus.isSunSuccess = true;
            Timers.Reset();
        }
        else
        {
            Player.isInvincible = false;
            Menus.isSunFailure = true;
            Timers.Reset();
        }
    }

    public const int RAIN_SP = 20;
    public const float RAIN_TIME_PERIOD = 1f;
    public static bool isRainActive;
    public static bool isRainPrimed;
    public static float rainTimeSinceStartOfMiracle = -1.0f;
    public static void RainUpdatePeriod(
        int[,,] town,
        int grayBoxI,
        int grayBoxJ,
        int playerI,
        int playerJ,
        bool isInvincible)
    {
        if (rainTimeSinceStartOfMiracle == -1.0f)
        {
            return;
        }
        rainTimeSinceStartOfMiracle += Timers.timeDelta;
        var k = 0;
        var result = false;
        for (var i = 0; i < 4; i++)
        {
            for (var j = 0; j < 4; j++)
            {
                if (rainTimeSinceStartOfMiracle >= RAIN_TIME_PERIOD)
                {
                    town[(int)Towns.Layers.BuildingModifier,
                         (grayBoxI * 4) + i,
                         (grayBoxJ * 4) + j] = 0;
                    if (town[(int)Towns.Layers.LandModifier,
                        (grayBoxI * 4) + i,
                        (grayBoxJ * 4) + j] == 3)
                    {
                        result = true;
                        town[(int)Towns.Layers.LandModifier,
                         (grayBoxI * 4) + i,
                         (grayBoxJ * 4) + j] = 0;
                    }
                }
                k++;
            }
        }
        if (result)
        {
            Player.isInvincible = false;
            //Menus.isRainSuccess = true;
            Timers.Reset();
        }
        else
        {
            Player.isInvincible = false;
            Menus.isRainFailure = true;
            Timers.Reset();
        }
    }

    public const int LIGHTNING_SP = 10;
    public const int LIGHTNING_ACTIONS = 8;
    public static readonly float[] lightningTimePeriods = new float[]
    {
        3.0f,
        3.0f,
        3.0f,
        3.0f,
        3.0f,
        3.0f,
        3.0f,
        3.0f,
        3.0f,
        3.0f,
        3.0f,
        3.0f,
        3.0f,
        3.0f,
        3.0f,
        3.0f
    };
    public static readonly float[] lightningTimeStarts = new float[]
    {
        16.0f,
        12.0f,
        11.0f,
        10.0f,
        15.0f,
        3.0f,
        2.0f,
        4.0f,
        13.0f,
        7.0f,
        1.0f,
        5.0f,
        14.0f,
        8.0f,
        9.0f,
        6.0f
    };
    public static bool isLightningActive;
    public static bool isLightningPrimed;
    public static bool isLightningResult = false;
    public static float lightningTimesSinceStartOfMiracle = -1.0f;
    public static void LightningUpdatePeriod(
        int[,,] town,
        int grayBoxI,
        int grayBoxJ,
        int playerI,
        int playerJ,
        bool isInvincible)
    {
        if (lightningTimesSinceStartOfMiracle == -1.0f)
        {
            return;
        }
        lightningTimesSinceStartOfMiracle += Timers.timeDelta;
        var k = 0;
        var isComplete = false;
        for (var i = 0; i < 4; i++)
        {
            for (var j = 0; j < 4; j++)
            {
                if (lightningTimesSinceStartOfMiracle >= lightningTimeStarts[k])
                {
                    print(town[0, (grayBoxI * 4) + i, (grayBoxJ * 4) + j]);
                    if (town[0, (grayBoxI * 4) + i, (grayBoxJ * 4) + j] == 6
                        || town[0, (grayBoxI * 4) + i, (grayBoxJ * 4) + j] == 9)
                    {
                        // TODO: Move below code here.
                        // Update to include:
                        // ... houses
                        // ... fields
                        // ... rocks
                        // ... palm trees
                        // ... bushes
                        isLightningResult = true;
                        print("SUCESS");
                    }
                    // Move this up.
                    town[5,
                        (grayBoxI * 4) + i,
                        (grayBoxJ * 4) + j] = 10;
                }
                if (lightningTimesSinceStartOfMiracle >= (lightningTimeStarts[k] + lightningTimePeriods[k]))
                {
                    town[5,
                        (grayBoxI * 4) + i,
                        (grayBoxJ * 4) + j] = 0;
                    if (k == 0)
                    {
                        
                        lightningTimesSinceStartOfMiracle = -1.0f;
                    }
                    if ((grayBoxI * 4) + i == playerI
                        && (grayBoxJ * 4) + j == playerJ)
                    {
                        town[5,
                            (grayBoxI * 4) + i,
                            (grayBoxJ * 4) + j] = 1;
                    }
                }
                k++;
                if (k >= lightningTimeStarts.Length)
                {
                }
            }
        }
        if (lightningTimesSinceStartOfMiracle >= 18.5f)
        {
            Timers.isScrolling = false;
            Messages.IsMessageVisible = false;
            Player.isInvincible = false;
            if (isLightningResult)
            {
                print("MARK SUCCESS");
                //Menus.isLightningSuccess = true;
                Timers.Reset();
            }
            else
            {
                print("MARK FAILURE");
                Menus.isLightningFailure = true;
                Timers.Reset();
            }
        }
    }
}
