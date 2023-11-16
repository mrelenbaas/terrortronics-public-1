/*
 * Title: Buttons file.
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
using System.Text;
using UnityEngine;

public abstract class Buttons : MonoBehaviour
{
    public static readonly int BACKGROUND_COUNT = 3;
    public const string NAME_DEFAULT = "                           ";
    public static float SIZE = 50;

    public static readonly string[,] enterPlayerNameTexts = new string[,] {
        { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", },
        { "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", },
        { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", },
        { "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", },
        { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".","BS","ED", },
    };


    public static void BoxGray(int column, int row, int xOffset, int yOffset)
    {
        if (!MainLoop.IsShowingDebugGUI)
        { 
            return;
        }
        var size = 4;
        var rectangle = new Rect(
            SIZE * column * size + (xOffset * SIZE),
            SIZE * row * size + (yOffset * SIZE),
            SIZE * size,
            SIZE * size);
        GUI.backgroundColor = Color.gray;
        GUI.Button(rectangle, "");
    }

    public static void BoxYellow(
            int xOffset,
            int yOffset,
            string text,
            int yellowBoxI,
            int yellowBoxJ,
            int tempI,
            int tempJ)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var left = 0;
        var top = 0;
        var width = 4;
        var height = 4;
        var isYellowBoxOffscreen = false;
        if (tempI == -1)
        {
            left = 1;
            width = 3;
        }
        else if (tempI == -2)
        {
            left = 2;
            width = 2;
        }
        else if (tempI == -3)
        {
            left = 3;
            width = 1;
        }
        else if (tempI <= -4)
        {
            left = -tempI;
            width = 0;
            isYellowBoxOffscreen = true;
        }
        if (tempI == 13)
        {
            width = 3;
        }
        else if (tempI == 14)
        {
            width = 2;
        }
        else if (tempI == 15)
        {
            width = 1;
        }
        else if (tempI >= 16)
        {
            width = 0;
            isYellowBoxOffscreen = true;
        }
        if (tempJ == -1)
        {
            top = 1;
            height = 3;
        }
        else if (tempJ == -2)
        {
            top = 2;
            height = 2;
        }
        else if (tempJ == -3)
        {
            top = 3;
            height = 1;
        }
        else if (tempJ <= -4)
        {
            top = -tempI;
            height = 0;
            isYellowBoxOffscreen = true;
        }
        if (tempJ == 9)
        {
            height = 3;
        }
        else if (tempJ == 10)
        {
            height = 2;
        }
        else if (tempJ == 11)
        {
            height = 1;
        }
        else if (tempJ >= 12)
        {
            height = 0;
            isYellowBoxOffscreen = true;
        }
        var size = 4;
        Route.yellowBoxI = SIZE * yellowBoxI * size + (left * SIZE) + (xOffset * SIZE);
        Route.yellowBoxJ = SIZE * yellowBoxJ * size + (top * SIZE) + (yOffset * SIZE);
        var rectangle = new Rect(
            SIZE * yellowBoxI * size + (left * SIZE) + (xOffset * SIZE),
            SIZE * yellowBoxJ * size + (top * SIZE) + (yOffset * SIZE),
            SIZE * width,
            SIZE * height);
        GUI.backgroundColor = isYellowBoxOffscreen
            ? Color.clear
            : Color.yellow;
        GUI.Button(rectangle, text);
    }

    public static void ControlPadUnused()
    {
        Buttons.ControlPadA();
        Buttons.ControlPadX();
        Buttons.ControlPadL();
        Buttons.ControlPadR();
        Buttons.ControlPadSelect();
    }
    public static void ControlPadA()
    {
        var rectangle = new Rect(
            SIZE * 26,
            SIZE * 3,
            SIZE,
            SIZE);
        var text = "A";
        GUI.backgroundColor = Color.red;
        GUI.Button(rectangle, text);
    }
    public static bool ControlPadB(bool isRed)
    {
        var rectangle = new Rect(
                SIZE * 25,
                SIZE * 4,
                SIZE,
                SIZE);
        var text = "B";
        GUI.backgroundColor = isRed
            ? Color.red
            : Color.green;
        return GUI.Button(rectangle, text);
    }
    public static bool ControlPadUp(bool isRed, bool isInMenu)
    {
        var rectangle = new Rect(
            SIZE * 18,
            SIZE * 2,
            SIZE,
            SIZE);
        var text = "UP";
        GUI.backgroundColor = isRed
            ? Color.red
            : Color.green;
        return isInMenu
            ? GUI.Button(rectangle, text)
            : GUI.RepeatButton(rectangle, text);
    }
    public static bool ControlPadDown(bool isRed, bool isInMenu)
    {
        var rectangle = new Rect(
                SIZE * 18,
                SIZE * 4,
                SIZE,
                SIZE);
        var text = "DOWN";
        GUI.backgroundColor = isRed
            ? Color.red
            : Color.green;
        return isInMenu
            ? GUI.Button(rectangle, text)
            : GUI.RepeatButton(rectangle, text);
    }
    public static bool ControlPadLeft(bool isRed, bool isInMenu)
    {
        var rectangle = new Rect(
            SIZE * 17,
            SIZE * 3,
            SIZE,
            SIZE);
        var text = "LEFT";
        GUI.backgroundColor = isRed
            ? Color.red
            : Color.green;
        return isInMenu
            ? GUI.Button(rectangle, text)
            : GUI.RepeatButton(rectangle, text);
    }
    public static bool ControlPadRight(bool isRed, bool IsInMenu)
    {
        var rectangle = new Rect(
                SIZE * 19,
                SIZE * 3,
                SIZE,
                SIZE);
        var text = "RIGHT";
        GUI.backgroundColor = isRed
            ? Color.red
            : Color.green;
        return IsInMenu
            ? GUI.Button(rectangle, text)
            : GUI.RepeatButton(rectangle, text);
    }
    public static void ControlPadL()
    {
        var rectangle = new Rect(
            SIZE * 17,
            SIZE * 1,
            SIZE,
            SIZE * 0.5f);
        var text = "L";
        GUI.backgroundColor = Color.red;
        GUI.Button(rectangle, text);
    }
    public static void ControlPadR()
    {
        var rectangle = new Rect(
            SIZE * 26,
            SIZE * 1,
            SIZE * 1,
            SIZE * 0.5f);
        var text = "R";
        GUI.backgroundColor = Color.red;
        GUI.Button(rectangle, text);
    }
    public static void ControlPadSelect()
    {
        var rectangle = new Rect(
            SIZE * 21,
            SIZE * 3,
            SIZE,
            SIZE * 0.5f);
        var text = "SEL";
        GUI.backgroundColor = Color.red;
        GUI.Button(rectangle, text);
    }
    public static bool ControlPadStart(bool isRed)
    {
        var rectangle = new Rect(
            SIZE * 22,
            SIZE * 3,
            SIZE,
            SIZE * 0.5f);
        var text = "SRT";
        GUI.backgroundColor = isRed
            ? Color.red
            : Color.green;
        return GUI.Button(rectangle, text);
    }
    public static void ControlPadX()
    {
        var rectangle = new Rect(
            SIZE * 25,
            SIZE * 2,
            SIZE,
            SIZE);
        var text = "X";
        GUI.backgroundColor = Color.red;
        GUI.Button(rectangle, text);
    }
    public static bool ControlPadY(bool isRed)
    {
        var rectangle = new Rect(
            SIZE * 24,
            SIZE * 3,
            SIZE,
            SIZE);
        var text = "Y";
        GUI.backgroundColor = isRed
            ? Color.red
            : Color.green;
        return GUI.Button(rectangle, text);
    }

    public static void Continue(int row)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            SIZE * 4,
            SIZE * 5,
            SIZE * 8,
            SIZE * 1);
        var text = "Continue";
        GUI.backgroundColor = (row == 0)
            ? Color.blue
            : Color.black;
        GUI.Button(rectangle, text);
    }

    public static void Description(string description)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
                SIZE * 7,
                SIZE * 3,
                SIZE * 8,
                SIZE * 2);
        var text = new StringBuilder()
                .Append("[                                                                                            \n")
                .Append("                                                                                             \n")
                .Append(description)
                .Append("\n")
                .Append("                                                                                             \n")
                .Append("                                                                                            ]")
                .ToString();
        for (var k = 0; k < BACKGROUND_COUNT; k++)
        {
            GUI.backgroundColor = Color.white;
            GUI.Button(rectangle, "");
        }
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text);
    }

    public static void FullscreenBackground()
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            0,
            0,
            SIZE * 16,
            SIZE * 12);
        GUI.backgroundColor = Color.white;
        for (var i = 0; i < BACKGROUND_COUNT; i++)
        {
            GUI.Button(rectangle, "");
        }
    }

    public static void Grid(int column, int row, string text)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            SIZE * column,
            SIZE * row,
            SIZE,
            SIZE);
        GUI.Button(rectangle, text);
    }

    public static bool Menu(int i, int j, string text)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return false;
        }
        var rectangle = new Rect(
            (SIZE * 1) + (SIZE * j),
            (SIZE * 3) + (SIZE * i),
            SIZE,
            SIZE);
        for (var k = 0; k < 3; k++)
        {
            GUI.backgroundColor = Color.white;
            GUI.Button(rectangle, "");
        }
        GUI.backgroundColor =
            (i == Menus.I && j == Menus.J)
                ? Color.blue
                :
                    (i == Menus.I && j == 0)
                        ? Color.blue
                        : Color.black;
        return GUI.Button(rectangle, text);
    }

    public static void Message(string text, int substringIndex)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        if (text.Equals(""))
        {
            substringIndex = 0;
        }
        var rectangle = new Rect(
            SIZE * 1,
            SIZE * 9,
            SIZE * 14,
            SIZE * 3);
        GUI.backgroundColor = Color.white;
        for (var i = 0; i < BACKGROUND_COUNT; i++)
        {
            GUI.Button(rectangle, "");
        }
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text.Substring(0, substringIndex));
    }

    public static void MessageFromPeople(string text, int substringIndex)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        FullscreenBackground();
        Description("Let us\n            Listen");
        var rectangle = new Rect(
            SIZE * 1,
            SIZE * 9,
            SIZE * 14,
            SIZE * 3);
        GUI.backgroundColor = Color.white;
        for (var i = 0; i < BACKGROUND_COUNT; i++)
        {
            GUI.Button(rectangle, "");
        }
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text.Substring(0, substringIndex));
    }

    public static void TakeOffering(string text, int substringIndex)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        FullscreenBackground();
        Description("Take an\n            Offering");
        var rectangle = new Rect(
            SIZE * 1,
            SIZE * 9,
            SIZE * 14,
            SIZE * 3);
        GUI.backgroundColor = Color.white;
        for (var i = 0; i < BACKGROUND_COUNT; i++)
        {
            GUI.Button(rectangle, "");
        }
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text.Substring(0, substringIndex));
    }

    public static void SelectMagic()
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        for (var i = 0; i < 4; i++)
        {
            var rectangle = new Rect(
                (SIZE * 8.5f) + (SIZE * i),
                (SIZE * 5) + (SIZE * 0.5f),
                SIZE,
                SIZE);
            var text = "";
            if (i == 0 && Magics.isMagicalFireUnlockled)
            {
                text = "fir";
            }
            else if (i == 1 && Magics.isMagicalStartdustUnlockled)
            {
                text = "dst";
            }
            else if (i == 2 && Magics.isMagicalAuraUnlockled)
            {
                text = "aur";
            }
            else if (i == 3 && Magics.isMagicalLightUnlockled)
            {
                text = "lgt";
            }
            GUI.backgroundColor = Color.black;
            GUI.Button(rectangle, text);
        }
    }

    public static void MessageSpeed(int column)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(0, 0, 0, 0);
        var text = "";
        for (var i = 0; i < 10; i++)
        {
            rectangle = new Rect(
                (SIZE * 8.5f) + (SIZE * i * 0.5f),
                SIZE * 5,
                SIZE * 0.5f,
                SIZE * 1);
            text = new StringBuilder()
                .Append(i)
                .ToString();
            GUI.backgroundColor = (column == i)
                ? Color.blue
                : Color.black;
            GUI.Button(rectangle, text);
        }
        rectangle = new Rect(
            SIZE * 7,
            SIZE * 6,
            SIZE * 8,
            SIZE * 1);
        text = "FAST <--> SLOW";
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text);
    }

    public static void NewGame(int row)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            SIZE * 4,
            SIZE * 6,
            SIZE * 8,
            SIZE * 1);
        var text = "New Game";
        GUI.backgroundColor = (row == 1)
            ? Color.blue
            : Color.black;
        GUI.Button(rectangle, text);
    }

    public static void Paused()
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            SIZE * 5,
            SIZE * 5,
            SIZE * 6,
            SIZE * 2);
        var text = "Paused!";
        GUI.backgroundColor = Color.white;
        for (var i = 0; i < BACKGROUND_COUNT; i++)
        {
            GUI.Button(rectangle, "");
        }
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text);
    }

    public static void ProfessionalMode(int row)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            SIZE * 4,
            SIZE * 7,
            SIZE * 8,
            SIZE * 1);
        var text = "Professional Mode";
        GUI.backgroundColor = (row == 2)
            ? Color.blue
            : Color.black;
        GUI.Button(rectangle, text);
    }

    public static void EnterPlayerName(string name, int k, int l)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
                SIZE * 1,
                SIZE * 2,
                SIZE * 14,
                SIZE * 10);
        GUI.backgroundColor = Color.white;
        for (var i = 0; i < BACKGROUND_COUNT; i++)
        {
            GUI.Button(rectangle, "");
        }
        var text = new StringBuilder()
            .Append("Please enter Master's name.\n")
            .Append(name)
            .Append("\n---------------------------")
            .ToString();
        GUI.backgroundColor = Color.black;
        rectangle = new Rect(
            (SIZE * 2) - (SIZE * 0.5f),
            (SIZE * 2) + (SIZE * 0.5f),
            SIZE * 13,
            SIZE * 3);
        GUI.Button(rectangle, text);
        for (var i = 0; i < 13; i++)
        {
            for (var j = 0; j < 5; j++)
            {
                GUI.backgroundColor = (i == k && j == l)
                    ? Color.blue
                    : Color.black;
                rectangle = new Rect(
                    (SIZE * i) + (SIZE * 2) - (SIZE * 0.5f),
                    (SIZE * j) + (SIZE * 6) + (SIZE * 0.5f),
                    SIZE,
                    SIZE);
                GUI.Button(rectangle, enterPlayerNameTexts[j, i]);
            }
        }
    }

    public static void StatusOfCities(
        int score,
        int scoreFillmoreActI,
        int scoreFillmoreActII,
        int scoreBloodpoolActI,
        int scoreBloodpoolActII,
        int scoreKasandoraActI,
        int scoreKasandoraActII,
        int scoreAitosActI,
        int scoreAitosActII,
        int scoreMarahnaActI,
        int scoreMarahnaActII,
        int scoreNorthwallActI,
        int scoreNorthwallActII)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
                SIZE * 1,
                SIZE * 1,
                SIZE * 14,
                SIZE * 10);
        var text = new StringBuilder()
            .Append(score)
            .Append("\n")
            .Append("Area: Act I, Act II")
            .Append("\n")
            .Append("---------------------------------")
            .Append("\n")
            .Append("Fillmore: ")
            .Append(scoreFillmoreActI)
            .Append(", ")
            .Append(scoreFillmoreActII)
            .Append("\n")
            .Append("Bloodpool: ")
            .Append(scoreBloodpoolActI)
            .Append(", ")
            .Append(scoreBloodpoolActII)
            .Append("\n")
            .Append("Kanandora: ")
            .Append(scoreKasandoraActI)
            .Append(", ")
            .Append(scoreKasandoraActII)
            .Append("\n")
            .Append("Aitos: ")
            .Append(scoreAitosActI)
            .Append(", ")
            .Append(scoreAitosActII)
            .Append("\n")
            .Append("Marahna: ")
            .Append(scoreMarahnaActI)
            .Append(", ")
            .Append(scoreMarahnaActII)
            .Append("\n")
            .Append("Northwall: ")
            .Append(scoreNorthwallActI)
            .Append(", ")
            .Append(scoreNorthwallActII)
            .ToString();
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text);
    }

    public static void StatusOfMaster(
        string name,
        int lives,
        int level,
        int healthPoints,
        int spellPoints,
        int magicPoints,
        int experienceToNextLevel,
        int experienceTotal,
        string[] magics,
        string[] items)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
                SIZE * 3,
                SIZE * 1,
                SIZE * 10,
                SIZE * 10);
        var text = new StringBuilder()
            .Append(name)
            .Append("\n")
            .Append(lives)
            .Append("\n")
            .Append(level)
            .Append("\n")
            .Append(healthPoints)
            .Append("\n")
            .Append(spellPoints)
            .Append("\n")
            .Append(magicPoints)
            .Append("\n")
            .Append(experienceToNextLevel)
            .Append("\n")
            .Append(experienceTotal)
            .Append("\n")
            .Append("[")
            .Append(Magics.isMagicalFireUnlockled ? "fir" : "   ")
            .Append("] [")
            .Append(Magics.isMagicalStartdustUnlockled ? "dst" : "   ")
            .Append("] [")
            .Append(Magics.isMagicalAuraUnlockled ? "aur" : "   ")
            .Append("] [")
            .Append(Magics.isMagicalLightUnlockled ? "lgt" : "   ")
            .Append("]")
            .Append("\n")
            .Append("[")
            .Append(Menus.takenIndex > 0 ? Menus.takenIcons[0, 0] : "   ")
            .Append("] [")
            .Append(Menus.takenIndex > 1 ? Menus.takenIcons[0, 1] : "   ")
            .Append("] [")
            .Append(Menus.takenIndex > 2 ? Menus.takenIcons[0, 2] : "   ")
            .Append("] [")
            .Append(Menus.takenIndex > 3 ? Menus.takenIcons[0, 3] : "   ")
            .Append("]\n[")
            .Append(Menus.takenIndex > 4 ? Menus.takenIcons[1, 0] : "   ")
            .Append("] [")
            .Append(Menus.takenIndex > 5 ? Menus.takenIcons[1, 1] : "   ")
            .Append("] [")
            .Append(Menus.takenIndex > 6 ? Menus.takenIcons[1, 2] : "   ")
            .Append("] [")
            .Append(Menus.takenIndex > 7 ? Menus.takenIcons[1, 3] : "   ")
            .Append("]")
            .ToString();
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text);
    }

    public static void Title()
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            SIZE * 1,
            SIZE * 1,
            SIZE * 14,
            SIZE * 3);
        var text = "ActRaiser Clone";
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text);
    }

    public static void TopBackground()
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            0,
            0,
            SIZE * 16,
            SIZE * 2);
        for (var k = 0; k < BACKGROUND_COUNT; k++)
        {
            GUI.backgroundColor = Color.white;
            GUI.Button(rectangle, "");
        }
    }

    public static void TopHealthPoints(int healthPoints)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            SIZE * 0,
            SIZE * 1,
            SIZE * 8,
            SIZE * 1);
        var healthAsPipes = new StringBuilder();
        for (var i = 0; i < healthPoints; i++)
        {
            healthAsPipes.Append("|");
        }
        var text = new StringBuilder()
            .Append("Angel ")
            .Append(healthAsPipes.ToString())
            .ToString();
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text);
    }

    public static void TopHourglass(int timeRemaining)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            SIZE * 8,
            SIZE * 0,
            SIZE * 2,
            SIZE * 2);
        var text = new StringBuilder()
            .Append("Hourglass:\n")
            .Append(timeRemaining)
            .ToString();
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text);
    }

    public static void TopPopulation(int population, int populationMax)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
                    SIZE * 10,
                    SIZE * 0,
                    SIZE * 6,
                    SIZE * 1);
        var text = new StringBuilder()
                    .Append("Population: ")
                    .Append(population)
                    .Append("/")
                    .Append(populationMax)
                    .ToString();
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text);
    }

    public static void TopSpellPoints(int spellPoints, int spellPointsMax)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            SIZE * 10,
            SIZE * 1,
            SIZE * 6,
            SIZE * 1);
        var text = new StringBuilder()
            .Append("Spell Points: ")
            .Append(spellPoints)
            .Append("/")
            .Append(spellPointsMax)
            .ToString();
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text);
    }

    public static void TopTownName(string townName)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
                SIZE * 0,
                SIZE * 0,
                SIZE * 8,
                SIZE * 1);
        var text = new StringBuilder()
                .Append("[SIM] ")
                .Append(townName)
                .ToString();
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text);
    }

    public static void TownUnderConstruction()
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            SIZE * 5,
            SIZE * 5,
            SIZE * 6,
            SIZE * 2);
        var text = "Town Under Construction";
        GUI.Button(rectangle, text);
    }

    /*
    public static void TownHall(string text)
    {
        var rectangle = new Rect(
            SIZE * 2,
            SIZE * 2,
            SIZE * 10,
            SIZE * 10);
        GUI.backgroundColor = Color.white;
        for (var i = 0; i < BACKGROUND_COUNT; i++)
        {
            GUI.Button(rectangle, "");
        }
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text);
    }
    */

    public static void VariableMenuBackground()
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            SIZE * 7,
            SIZE * 5,
            SIZE * 8,
            SIZE * 2);
        GUI.backgroundColor = Color.white;
        for (var i = 0; i < BACKGROUND_COUNT; i++)
        {
            GUI.Button(rectangle, "");
        }
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, "");
    }

    public static void OfferingsGrid(
        int row,
        int column,
        string[,] offeringStrings)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        for (var i = 0; i < 2; i++)
        {
            for (var j = 0; j < 4; j++)
            {
                var rectangle = new Rect(
                    (SIZE * 9) + (SIZE * j),
                    (SIZE * 5) + (SIZE * i),
                    SIZE * 1,
                    SIZE * 1);
                var text = offeringStrings[i, j];
                GUI.backgroundColor = (i == row && j == column)
                    ? Color.blue
                    : Color.black;
                GUI.Button(rectangle, text);
            }
        }
    }

    public static void YesNo(int row)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        Buttons.O(row);
        Buttons.Yes();
        Buttons.X(row);
        Buttons.No();
    }
    public static void O(int row)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            SIZE * 8,
            SIZE * 5,
            SIZE * 1,
            SIZE * 1);
        var text = "O";
        GUI.backgroundColor = (row == 0)
            ? Color.blue
            : Color.black;
        GUI.Button(rectangle, text);
    }
    public static void Yes()
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            SIZE * 10,
            SIZE * 5,
            SIZE * 2,
            SIZE * 1);
        var text = "Yes";
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text);
    }
    public static void X(int row)
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
            SIZE * 8,
            SIZE * 6,
            SIZE * 1,
            SIZE * 1);
        var text = "X";
        GUI.backgroundColor = (row == 1)
            ? Color.blue
            : Color.black;
        GUI.Button(rectangle, text);
    }
    public static void No()
    {
        if (!MainLoop.IsShowingDebugGUI)
        {
            return;
        }
        var rectangle = new Rect(
                SIZE * 10,
                SIZE * 6,
                SIZE * 2,
                SIZE * 1);
        var text = "No";
        GUI.backgroundColor = Color.black;
        GUI.Button(rectangle, text);
    }
}
