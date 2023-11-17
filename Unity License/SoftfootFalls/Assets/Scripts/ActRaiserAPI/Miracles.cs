using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Miracles : MonoBehaviour
{
    public const int CLUSTER_SIZE = 4;

    private static bool isAnimationBlocked;
    public static bool IsAnimationBlocked { get { return isAnimationBlocked; } set { isAnimationBlocked = value; } }


    public static bool IsAnyMiracleActive()
    {
        var result = false;
        if (lightningTimesSinceStartOfMiracle != -1.0f
            || rainTimeSinceStartOfMiracle != -1.0f
            || sunlightTimeSinceStartOfMiracle != -1.0f
            || windTimeSinceStartOfMiracle != -1.0f
            || earthquakeTimeSinceStartOfMiracle != -1.0f)
        {
            result = true;
        }
        return result;
    }

    public const int EARTHQUAKE_SP = 160;
    public const float EARTHQUAKE_TIME_PERIOD = 1f;
    public static bool isEarthquakeActive;
    public static float earthquakeTimeSinceStartOfMiracle = -1.0f;
    public static void EarthquakeUpdatePeriod(
        int[,,] town,
        int grayBoxI,
        int grayBoxJ,
        int townSize)
    {
        if (earthquakeTimeSinceStartOfMiracle == -1.0f)
        {
            return;
        }
        earthquakeTimeSinceStartOfMiracle += Timers.timeDelta;
        var result = false;
        if (earthquakeTimeSinceStartOfMiracle >= EARTHQUAKE_TIME_PERIOD)
        {
            for (var j = 0; j < townSize; j++)
            {
                for (var i = 0; i < townSize; i++)
                {
                    if (town[(int)Towns.Layers.Building,
                                  (grayBoxI * CLUSTER_SIZE) + i,
                                  (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.LevelOneHouse
                            || town[(int)Towns.Layers.Building,
                                    (grayBoxI * CLUSTER_SIZE) + i,
                                    (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.LevelTwoHouse
                            || town[(int)Towns.Layers.Building,
                                    (grayBoxI * CLUSTER_SIZE) + i,
                                    (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.CornField)
                    {
                        result = true;
                        town[(int)Towns.Layers.Building,
                             (grayBoxI * CLUSTER_SIZE) + i,
                             (grayBoxJ * CLUSTER_SIZE) + j] = (int)LookupTables.Building.None;
                        town[(int)Towns.Layers.LandModifier,
                             (grayBoxI * CLUSTER_SIZE) + i,
                             (grayBoxJ * CLUSTER_SIZE) + j] = (int)LookupTables.LandModifier.Burned;
                    }
                }
            }
            earthquakeTimeSinceStartOfMiracle = -1.0f;
        }
        if (earthquakeTimeSinceStartOfMiracle == -1.0f)
        {
            if (result)
            {
                Messages.IsMessageVisible = false;
                Menus.isEarthquakeFailure = false;
                Timers.Reset();
            }
            else
            {
                Messages.IsMessageVisible = true;
                Menus.isEarthquakeFailure = true;
                Timers.Reset();
            }
            isAnimationBlocked = false;
        }
    }

    public const int WIND_SP = 80;
    public const float WIND_TIME_PERIOD = 1f;
    public static bool isWindActive;
    //public static bool isWindPrimed;
    public static float windTimeSinceStartOfMiracle = -1.0f;
    public static void WindUpdatePeriod(
        int[,,] town,
        int grayBoxI,
        int grayBoxJ,
        int townSize)
    {
        if (windTimeSinceStartOfMiracle == -1.0f)
        {
            return;
        }
        windTimeSinceStartOfMiracle += Timers.timeDelta;
        var result = false;
        if (windTimeSinceStartOfMiracle >= WIND_TIME_PERIOD)
        {
            for (var j = 0; j < townSize; j++)
            {
                for (var i = 0; i < townSize; i++)
                {
                    if (town[(int)Towns.Layers.EnemiesAndPlayer, i, j] >= 2
                        && town[(int)Towns.Layers.EnemiesAndPlayer, i, j] <= 5)
                    {
                        result = true;
                        //windTimeSinceStartOfMiracle = -1.0f;
                        town[(int)Towns.Layers.EnemiesAndPlayer, i, j] = 0;
                    }
                }
            }
            windTimeSinceStartOfMiracle = -1.0f;
        }
        if (windTimeSinceStartOfMiracle == -1.0f)
        {
            if (result)
            {
                Messages.IsMessageVisible = false;
                Menus.isWindFailure = false;
                Timers.Reset();
            }
            else
            {
                Messages.IsMessageVisible = true;
                Menus.isWindFailure = true;
                Timers.Reset();
            }
            isAnimationBlocked = false;
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
        int grayBoxJ)
    {
        if (sunlightTimeSinceStartOfMiracle == -1.0f)
        {
            return;
        }
        sunlightTimeSinceStartOfMiracle += Timers.timeDelta;
        var k = 0;
        var result = false;
        if (sunlightTimeSinceStartOfMiracle >= SUNLIGHT_TIME_PERIOD)
        {
            for (var i = 0; i < 4; i++)
                {
                for (var j = 0; j < 4; j++)
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
                    sunlightTimeSinceStartOfMiracle = -1.0f;
                }
                k++;
            }
        }
        if (sunlightTimeSinceStartOfMiracle == -1.0f)
        {
            if (result)
            {
                Messages.IsMessageVisible = false;
                Menus.isSunFailure = false;
                Timers.Reset();
            }
            else
            {
                Messages.IsMessageVisible = true;
                Menus.isSunFailure = true;
                Timers.Reset();
            }
            isAnimationBlocked = false;
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
        int grayBoxJ)
    {
        if (rainTimeSinceStartOfMiracle == -1.0f)
        {
            return;
        }
        rainTimeSinceStartOfMiracle += Timers.timeDelta;
        var k = 0;
        var result = false;
        if (rainTimeSinceStartOfMiracle >= RAIN_TIME_PERIOD)
        {
            for (var i = 0; i < 4; i++)
            {
                for (var j = 0; j < 4; j++)
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
                    rainTimeSinceStartOfMiracle = -1.0f;
                    k++;
                }
            }
        }
        if (rainTimeSinceStartOfMiracle == -1.0f)
        {
            if (result)
            {
                Messages.IsMessageVisible = false;
                Menus.isRainFailure = false;
                Timers.Reset();
            }
            else
            {
                Messages.IsMessageVisible = true;
                Menus.isRainFailure = true;
                Timers.Reset();
            }
            isAnimationBlocked = false;
        }
    }

    public const int LIGHTNING_SP = 10;
    public const int LIGHTNING_ACTIONS = 8;
    private const float LIGHTNING_MOD_1 = 0.8f;
    private const float LIGHTNING_MOD_2 = 0.4f;
    public static readonly float[] lightningTimePeriods = new float[]
    {
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1,
        3.0f * LIGHTNING_MOD_1
    };
    public static readonly float[] lightningTimeStarts = new float[]
    {
        16.0f * LIGHTNING_MOD_2,
        12.0f * LIGHTNING_MOD_2,
        11.0f * LIGHTNING_MOD_2,
        10.0f * LIGHTNING_MOD_2,
        15.0f * LIGHTNING_MOD_2,
        3.0f * LIGHTNING_MOD_2,
        2.0f * LIGHTNING_MOD_2,
        4.0f * LIGHTNING_MOD_2,
        13.0f * LIGHTNING_MOD_2,
        7.0f * LIGHTNING_MOD_2,
        1.0f * LIGHTNING_MOD_2,
        5.0f * LIGHTNING_MOD_2,
        14.0f * LIGHTNING_MOD_2,
        8.0f * LIGHTNING_MOD_2,
        9.0f * LIGHTNING_MOD_2,
        6.0f * LIGHTNING_MOD_2
    };
    public static bool isLightningActive;
    public static bool isLightningPrimed;
    public static bool isLightningResult = false;
    public static float lightningTimesSinceStartOfMiracle = -1.0f;
    public static void LightningUpdatePeriod(
        int[,,] town,
        int grayBoxI,
        int grayBoxJ)
    {
        if (lightningTimesSinceStartOfMiracle == -1.0f)
        {
            return;
        }
        lightningTimesSinceStartOfMiracle += Timers.timeDelta;
        var k = 0;
        for (var i = 0; i < CLUSTER_SIZE; i++)
        {
            for (var j = 0; j < CLUSTER_SIZE; j++)
            {
                if (lightningTimesSinceStartOfMiracle >= lightningTimeStarts[k])
                {
                    if (town[(int)Towns.Layers.Land,
                             (grayBoxI * CLUSTER_SIZE) + i,
                             (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Land.Bush
                        || town[(int)Towns.Layers.Land,
                                (grayBoxI * CLUSTER_SIZE) + i,
                                (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Land.Rock
                        || town[(int)Towns.Layers.Land,
                                (grayBoxI * CLUSTER_SIZE) + i,
                                (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Land.PalmTree
                        || town[(int)Towns.Layers.Building,
                                (grayBoxI * CLUSTER_SIZE) + i,
                                (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.LevelOneHouse
                        || town[(int)Towns.Layers.Building,
                                (grayBoxI * CLUSTER_SIZE) + i,
                                (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.LevelTwoHouse
                        || town[(int)Towns.Layers.Building,
                                (grayBoxI * CLUSTER_SIZE) + i,
                                (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.LevelThreeHouse
                        || town[(int)Towns.Layers.Building,
                                (grayBoxI * CLUSTER_SIZE) + i,
                                (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.CornField
                        || town[(int)Towns.Layers.Building,
                                (grayBoxI * CLUSTER_SIZE) + i,
                                (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.WheatField
                        || town[(int)Towns.Layers.Building,
                                (grayBoxI * CLUSTER_SIZE) + i,
                                (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.Factory
                        || town[(int)Towns.Layers.Building,
                                (grayBoxI * CLUSTER_SIZE) + i,
                                (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.Windmill)
                    {
                        isLightningResult = true;
                    }
                    if (Route.ArrowHit(Towns.town[(int)Towns.Layers.EnemiesAndPlayer,
                                                  (grayBoxI * CLUSTER_SIZE) + i,
                                                  (grayBoxJ * CLUSTER_SIZE) + j]))
                    {
                        Towns.town[(int)Towns.Layers.EnemiesAndPlayer,
                                   (grayBoxI * CLUSTER_SIZE) + i,
                                   (grayBoxJ * CLUSTER_SIZE) + j] = (int)LookupTables.EnemiesAndPlayer.None;
                    }
                    town[(int)Towns.Layers.EnemiesAndPlayer,
                        (grayBoxI * CLUSTER_SIZE) + i,
                        (grayBoxJ * CLUSTER_SIZE) + j] = (int)LookupTables.EnemiesAndPlayer.MiracleLightning;
                }
                if (lightningTimesSinceStartOfMiracle >= (lightningTimeStarts[k] + lightningTimePeriods[k]))
                {
                    town[(int)Towns.Layers.EnemiesAndPlayer,
                        (grayBoxI * CLUSTER_SIZE) + i,
                        (grayBoxJ * CLUSTER_SIZE) + j] = (int)LookupTables.EnemiesAndPlayer.None;
                    if (k == 0)
                    {
                        lightningTimesSinceStartOfMiracle = -1.0f;
                    }
                }
                k++;
                if (k >= lightningTimeStarts.Length)
                {
                }
            }
        }
        if (lightningTimesSinceStartOfMiracle == -1.0f)
        {
            for (var i = 0; i < CLUSTER_SIZE; i++)
            {
                for (var j = 0; j < CLUSTER_SIZE; j++)
                {
                    if (town[(int)Towns.Layers.Land,
                                 (grayBoxI * CLUSTER_SIZE) + i,
                                 (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Land.Bush
                            || town[(int)Towns.Layers.Land,
                                    (grayBoxI * CLUSTER_SIZE) + i,
                                    (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Land.Rock
                            || town[(int)Towns.Layers.Land,
                                    (grayBoxI * CLUSTER_SIZE) + i,
                                    (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Land.PalmTree)
                    {
                        town[(int)Towns.Layers.Land,
                             (grayBoxI * CLUSTER_SIZE) + i,
                             (grayBoxJ * CLUSTER_SIZE) + j] = (int)LookupTables.Land.Grass;
                    }
                    else if (town[(int)Towns.Layers.Building,
                                  (grayBoxI * CLUSTER_SIZE) + i,
                                  (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.LevelOneHouse
                            || town[(int)Towns.Layers.Building,
                                    (grayBoxI * CLUSTER_SIZE) + i,
                                    (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.LevelTwoHouse
                            || town[(int)Towns.Layers.Building,
                                    (grayBoxI * CLUSTER_SIZE) + i,
                                    (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.LevelThreeHouse
                            || town[(int)Towns.Layers.Building,
                                    (grayBoxI * CLUSTER_SIZE) + i,
                                    (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.CornField
                            || town[(int)Towns.Layers.Building,
                                    (grayBoxI * CLUSTER_SIZE) + i,
                                    (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.WheatField
                            || town[(int)Towns.Layers.Building,
                                    (grayBoxI * CLUSTER_SIZE) + i,
                                    (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.Factory
                            || town[(int)Towns.Layers.Building,
                                    (grayBoxI * CLUSTER_SIZE) + i,
                                    (grayBoxJ * CLUSTER_SIZE) + j] == (int)LookupTables.Building.Windmill)
                    {
                        town[(int)Towns.Layers.Building,
                             (grayBoxI * CLUSTER_SIZE) + i,
                             (grayBoxJ * CLUSTER_SIZE) + j] = (int)LookupTables.Building.None;
                        town[(int)Towns.Layers.LandModifier,
                             (grayBoxI * CLUSTER_SIZE) + i,
                             (grayBoxJ * CLUSTER_SIZE) + j] = (int)LookupTables.LandModifier.Burned;
                    }
                }
            }
            if (isLightningResult)
            {
                Messages.IsMessageVisible = false;
                Menus.isLightningFailure = false;
                Timers.Reset();
            }
            else
            {
                Messages.IsMessageVisible = true;
                Menus.isLightningFailure = true;
                Timers.Reset();
            }
            isAnimationBlocked = false;
        }
    }
}
