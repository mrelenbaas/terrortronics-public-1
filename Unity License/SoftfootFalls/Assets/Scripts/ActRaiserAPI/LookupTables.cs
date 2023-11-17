using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class LookupTables : MonoBehaviour
{
    public enum Land
    {
        None,
        Tree,     // TODO: Add bottom art.
        Grass,    // TODO: Add bottom & front art.
        PalmTree, // TODO: Add bottom art.
        Water,
        Mountain, // TODO: Add bottom art.
        Bush,     // TODO: Add bottom & front art.
        Beach,    // TODO: Add bottom & front art.
        Cliff,    // TODO: Add bottom & front art.
        Rock      // TODO: bottom Add art.
    };

    public static string[] LandName = new string[]
    {
        "None",
        "Tree",
        "Grass",
        "PalmTree",
        "Water",
        "Mountain",
        "Bush",
        "Beach",
        "Cliff",
        "Rock"
    };

    public static Color[] LandColor = new Color[]
    {
        new Color(1.000f, 1.000f, 1.000f, 1.000f), // None.
        new Color(0.259f, 0.143f, 0.069f, 1.000f), // Tree.
        new Color(0.249f, 0.338f, 0.052f, 1.000f), // Grass.
        new Color(0.310f, 0.711f, 0.358f, 1.000f), // Palm Tree.
        new Color(0.212f, 0.326f, 0.831f, 1.000f), // Water.
        new Color(0.410f, 0.546f, 0.636f, 1.000f), // Mountain.
        new Color(0.223f, 0.627f, 0.210f, 1.000f), // Bush.
        new Color(0.925f, 0.813f, 0.422f, 1.000f), // Beach.
        new Color(0.434f, 0.552f, 0.543f, 1.000f), // Cliff.
        new Color(0.184f, 0.343f, 0.279f, 1.000f)  // Rock.
    };

    public enum LandModifier
    {
        None,
        Snow,
        Swamp,
        Dry,
        Burned
    }

    public static string[] LandModifierName = new string[]
    {
        "None",
        "Snow",
        "Swamp",
        "Dry",
        "Burned"
    };

    public static Color[] LandModifierColor = new Color[]
    {
        new Color(1.000f, 1.000f, 1.000f, 1.000f), // None.
        new Color(0.573f, 0.759f, 0.871f, 1.000f), // Snow.
        new Color(0.282f, 0.433f, 0.235f, 1.000f), // Swamp.
        new Color(0.876f, 0.702f, 0.370f, 1.000f), // Dry.
        new Color(0.905f, 0.231f, 0.231f, 1.000f)  // Burned.
    };

    public enum People
    {
        None,
        One,
        Three,
        Five,
        Seven,
        Ten
    }

    public static string[] PeopleName = new string[]
    {
        "None",
        "One",
        "Three",
        "Five",
        "Seven",
        "Ten"
    };

    public static Color[] PeopleColor = new Color[]
    {
        new Color(1.000f, 1.000f, 1.000f, 1.000f), // None.
        new Color(1.000f, 0.000f, 0.000f, 1.000f), // One.
        new Color(0.000f, 1.000f, 0.000f, 1.000f), // Three.
        new Color(0.000f, 1.000f, 0.000f, 1.000f), // Five.
        new Color(0.000f, 1.000f, 0.000f, 1.000f), // Seven.
        new Color(0.000f, 0.000f, 1.000f, 1.000f), // Ten.
    };

    public enum Building
    {
        None,
        LevelOneHouse,
        LevelTwoHouse,
        LevelThreeHouse,
        CornField,
        WheatField,
        Pony,
        Factory,
        Bridge,
        Windmill,
        DenNapperBatLeft,
        DenNapperBatRight,
        Road,
        TownHall,
        DenBlueDemonLeft,
        DenBlueDemonRight,
        DenRedDevilLeft,
        DenRedDevilRight,
        DenSkeletonHeadLeft,
        DenSkeletonHeadRight,
        TownHallUpperLeft,
        TownHallUpperRight,
        TownHallLowerLeft,
        TownHallLowerRight,
        ConnectorAllWay,
        ConnectorUp,
        ConnectorDown,
        ConnectorLeft,
        ConnectorRight,
        CornerUpperLeft,
        CornerUpperRight,
        CornerLowerLeft,
        CornerLowerRight,
        RoadHorizontal,
        RoadVertical,
        Corgi,
        Sheep
    }

    public static string[] BuildingName = new string[]
    {
        "None",
        "LevelOneHouse",
        "LevelTwoHouse",
        "LevelThreeHouse",
        "CornField",
        "WheatField",
        "HorsePasture",
        "Factory",
        "Bridge",
        "Windmill",
        "DenNapperBatLeft",
        "DenNapperBatRight",
        "Road",
        "TownHall",
        "DenBlueDemonLeft",
        "DenBlueDemonRight",
        "DenRedDevilLeft",
        "DenRedDevilRight",
        "DenSkeletonHeadLeft",
        "DenSkeletonHeadRight",
        "TownHallUpperLeft",
        "TownHallUpperRight",
        "TownHallLowerLeft",
        "TownHallLowerRight",
        "ConnectorAllWay",
        "ConnectorUp",
        "ConnectorDown",
        "ConnectorLeft",
        "ConnectorRight",
        "CornerUpperLeft",
        "CornerUpperRight",
        "CornerLowerLeft",
        "CornerLowerRight",
        "RoadHorizontal",
        "RoadVertical",
        "Corgi",
        "Sheep"
    };

    public static Color[] BuildingColor = new Color[]
    {
        new Color(1.000f, 1.000f, 1.000f, 1.000f), // None.
        new Color(1.000f, 0.000f, 0.000f, 1.000f), // LevelOneHouse.
        new Color(0.000f, 1.000f, 0.000f, 1.000f), // LevelTwoHouse.
        new Color(0.000f, 0.000f, 1.000f, 1.000f), // LevelThreeHouse.
        new Color(0.846f, 0.995f, 0.087f, 1.000f), // CornField.
        new Color(0.617f, 0.592f, 0.062f, 1.000f), // WheatField.
        new Color(0.443f, 0.235f, 0.199f, 1.000f), // HorsePasture.
        new Color(0.558f, 0.162f, 0.861f, 1.000f), // Factory.
        new Color(0.415f, 0.419f, 0.572f, 1.000f), // Bridge.
        new Color(0.950f, 0.510f, 0.510f, 1.000f), // Windmill.
        new Color(0.169f, 0.033f, 0.033f, 1.000f), // DenNapperBatLeft.
        new Color(0.169f, 0.033f, 0.033f, 1.000f), // DenNapperBatRight.
        new Color(0.415f, 0.419f, 0.572f, 1.000f), // Road.
        new Color(0.952f, 1.000f, 0.705f, 1.000f), // TownHall.
        new Color(0.207f, 0.223f, 0.751f, 1.000f), // DenBlueDemonLeft.
        new Color(0.207f, 0.223f, 0.751f, 1.000f), // DenBlueDemonRight.
        new Color(0.652f, 0.105f, 0.219f, 1.000f), // DenRedDevilLeft.
        new Color(0.652f, 0.105f, 0.219f, 1.000f), // DenRedDevilRight.
        new Color(0.731f, 0.722f, 0.137f, 1.000f), // DenSkeletonHeadLeft.
        new Color(0.731f, 0.722f, 0.137f, 1.000f), // DenSkeletonHeadRight.
        new Color(0.952f, 1.000f, 0.705f, 1.000f), // TownHallUpperLeft.
        new Color(0.952f, 1.000f, 0.705f, 1.000f), // TownHallUpperRight.
        new Color(0.952f, 1.000f, 0.705f, 1.000f), // TownHallLowerLeft.
        new Color(0.952f, 1.000f, 0.705f, 1.000f), // TownHallLowerRight.
        new Color(0.415f, 0.419f, 0.572f, 1.000f), // ConnectorAllWay.
        new Color(0.415f, 0.419f, 0.572f, 1.000f), // ConnectorUp.
        new Color(0.415f, 0.419f, 0.572f, 1.000f), // ConnectorDown.
        new Color(0.415f, 0.419f, 0.572f, 1.000f), // ConnectorLeft.
        new Color(0.415f, 0.419f, 0.572f, 1.000f), // ConnectorRight.
        new Color(0.415f, 0.419f, 0.572f, 1.000f), // CornerUpperLeft.
        new Color(0.415f, 0.419f, 0.572f, 1.000f), // CornerUpperRight.
        new Color(0.415f, 0.419f, 0.572f, 1.000f), // CornerLowerLeft.
        new Color(0.415f, 0.419f, 0.572f, 1.000f), // CornerLowerRight.
        new Color(0.415f, 0.419f, 0.572f, 1.000f), // RoadHorizontal.
        new Color(0.415f, 0.419f, 0.572f, 1.000f), // RoadVertical.
        new Color(0.415f, 0.419f, 0.572f, 1.000f), // Corgi.
        new Color(0.415f, 0.419f, 0.572f, 1.000f)  // Sheep.
    };

    public enum BuildingModifier
    {
        None,
        Fire,
        Fight,
        Sad
    }

    public static string[] BuildingModifierName = new string[]
    {
        "None",
        "Fire",
        "Fight",
        "Sad"
    };

    public static Color[] BuildingModifierColor = new Color[]
    {
        new Color(1.000f, 1.000f, 1.000f, 1.000f), // None.
        new Color(1.000f, 0.000f, 0.000f, 1.000f), // Fire.
        new Color(0.000f, 1.000f, 0.000f, 1.000f), // Fight.
        new Color(0.000f, 0.000f, 1.000f, 1.000f)  // Sad.
    };

    public enum EnemiesAndPlayer
    {
        None,
        Player,
        NapperBat,
        BlueDemon,
        RedDevil,
        SkeletonHead,
        ArrowUp,
        ArrowDown,
        ArrowLeft,
        ArrowRight,
        MiracleLightning,
        MiracleRain,
        MiracleSun,
        MiracleWind,
        MiracleEarthquake
    }

    public static string[] EnemiesAndPlayerName = new string[]
    {
        "None",
        "Player",
        "NapperBat",
        "BlueDemon",
        "RedDevil",
        "SkeletonHead",
        "ArrowUp",
        "ArrowDown",
        "ArrowLeft",
        "ArrowRight",
        "MiracleLightning",
        "MiracleRain",
        "MiracleSun",
        "MiracleWind",
        "MiracleEarthquake"
    };

    public static Color[] EnemiesAndPlayerColor = new Color[]
    {
        new Color(1.000f, 1.000f, 1.000f, 1.000f), // None.
        new Color(0.678f, 0.736f, 0.183f, 0.000f), // Player.
        new Color(0.169f, 0.033f, 0.033f, 1.000f), // Napper Bat.
        new Color(0.207f, 0.223f, 0.751f, 1.000f), // Blue Demon.
        new Color(0.652f, 0.105f, 0.219f, 1.000f), // Red Devil.
        new Color(0.731f, 0.722f, 0.137f, 1.000f), // Skeleton Head.
        new Color(1.000f, 1.000f, 1.000f, 1.000f), // Arrow Up.
        new Color(1.000f, 1.000f, 1.000f, 1.000f), // Arrow Down.
        new Color(1.000f, 1.000f, 1.000f, 1.000f), // Arrow Left.
        new Color(1.000f, 1.000f, 1.000f, 1.000f), // Arrow Right.
        new Color(1.000f, 1.000f, 1.000f, 1.000f), // Miracle Lightning.
        new Color(1.000f, 1.000f, 1.000f, 1.000f), // Miracle Rain.
        new Color(1.000f, 1.000f, 1.000f, 1.000f), // Miracle Sun.
        new Color(1.000f, 1.000f, 1.000f, 1.000f), // Miracle Wind.
        new Color(1.000f, 1.000f, 1.000f, 1.000f)  // Miracle Earthquake.
    };
}
