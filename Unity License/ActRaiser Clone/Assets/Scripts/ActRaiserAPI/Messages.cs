/*
 * Title: Messages file.
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

public abstract class Messages : MonoBehaviour
{
    // TODO: Magics.
    // TODO: Miracles (Wind and Earthquake ShowMeWhere)
    // TODO: Quests.

    // 1. Miracles have x4 sub-messages.
    // 1a. miracle *** available
    // 1b. miracle *** unavailable
    // 1c. miracle *** yes no
    // 1d. miracle *** show me where
    // 2. Menus.
    // 2a. Start Menu
    // 2b. Enter Player Name Menu
    // 2c. Sky Palace Menu
    // 2d. Town Builder Menu

    // Add a message.
    // 1. Add an array of strings (an array of string builders)
    // 1a. Array of strings is readonly, if it doesn't include the PlayerName.
    // 1b. Otheriwise, it's not readonly.
    // 2. Add property to get array of strings.

    // Miracle readonlys.
    private static readonly string[] earthquakeAvailable = new string[]
    {
        new StringBuilder()
            .Append("Some change may take\n")
            .Append("place to the continent,\n")
            .Append("if you cause\n")
            .Append("an earthquake.")
            .ToString()
    };
    private static readonly string[] earthquakeUnavailable = new string[]
    {
        new StringBuilder()
            .Append("Some change may take\n")
            .Append("place to the continent,\n")
            .Append("if you cause\n")
            .Append("an earthquake.")
            .ToString(),
        new StringBuilder()
            .Append("However, my Master,\n")
            .Append("we need 160 SP in order\n")
            .Append("to create an  earthquake.")
            .ToString()
    };
    private static readonly string[] earthquakeYesNo = new string[]
    {
        new StringBuilder()
            .Append("EATHQUAKE YES NO")
            .ToString()
    };
    private static readonly string[] earthquakeShowMeWhere = new string[]
    {
        new StringBuilder()
            .Append("EARTHQUAKE SHOW ME WHERE")
            .ToString()
    };
    private static readonly string[] lightningAvailable = new string[]
    {
        new StringBuilder()
            .Append("Your lightning can\n")
            .Append("destroy houses\n")
            .Append("fields, rocks,\n")
            .Append("palm trees and bushes.")
            .ToString()
    };
    private static readonly string[] lightningUnavailable = new string[]
    {
        new StringBuilder()
            .Append("Your lightning can\n")
            .Append("destroy houses\n")
            .Append("fields, rocks,\n")
            .Append("palm trees and bushes.")
            .ToString(),
        new StringBuilder()
            .Append("However, my Master,\n")
            .Append("we need 10 SP\n")
            .Append("in order to\n")
            .Append("create a lightning bolt.")
            .ToString()
    };
    private static readonly string[] lightningYesNo = new string[]
    {
        new StringBuilder()
            .Append("Will you use lightning?")
            .ToString()
    };
    private static readonly string[] lightningShowMeWhere = new string[]
    {
        new StringBuilder()
            .Append("All right, please show\n")
            .Append("me where to use\n")
            .Append("the lightning bolt.")
            .ToString()
    };
    private static readonly string[] rainAvailable = new string[]
    {
        new StringBuilder()
            .Append("If you send rain,\n")
            .Append("the crops will grow\n")
            .Append("and any dried-up fields\n")
            .Append("will be nurtured back\n")
            .Append("to full productivity.")
            .ToString()
    };
    private static readonly string[] rainUnavailable = new string[]
    {
        new StringBuilder()
            .Append("If you send rain,\n")
            .Append("the crops will grow\n")
            .Append("and any dried-up fields\n")
            .Append("will be nurtured back\n")
            .Append("to full productivity.")
            .ToString(),
        new StringBuilder()
            .Append("However, my Master,\n")
            .Append("we need 20 SP,\n")
            .Append("in order to create\n")
            .Append("a rain cloud.")
            .ToString()
    };
    private static readonly string[] rainYesNo = new string[]
    {
        new StringBuilder()
            .Append("Will you use rain?")
            .ToString()
    };
    private static readonly string[] rainShowMeWhere = new string[]
    {
        new StringBuilder()
            .Append("Well, then please\n")
            .Append("show me where to send\n")
            .Append("the rain.")
            .ToString()
    };
    private static readonly string[] sunAvailable = new string[]
    {
        new StringBuilder()
            .Append("The sunlight will\n")
            .Append("dry up marsh lands and\n")
            .Append("melt snow.")
            .ToString()
    };
    private static readonly string[] sunUnavailable = new string[]
    {
        new StringBuilder()
            .Append("The sunlight will\n")
            .Append("dry up marsh lands and\n")
            .Append("melt snow.")
            .ToString(),
        new StringBuilder()
            .Append("However, my Master,\n")
            .Append("we need 30 SP in order,\n")
            .Append("to create sunlight.")
            .ToString()
    };
    private static readonly string[] sunYesNo = new string[]
    {
        new StringBuilder()
            .Append("Do you want to\n")
            .Append("send the sun?")
            .ToString()
    };
    private static readonly string[] sunShowMeWhere = new string[]
    {
        new StringBuilder()
            .Append("Now, please show me\n")
            .Append("where to send the\n")
            .Append("sunlight.")
            .ToString()
    };
    private static readonly string[] windAvailable = new string[]
    {
        new StringBuilder()
            .Append("Your powerful wind will\n")
            .Append("blow all flying\n")
            .Append("creatures away.")
            .ToString()
    };
    private static readonly string[] windUnavailable = new string[]
    {
        new StringBuilder()
            .Append("Your powerful wind will\n")
            .Append("blow all flying\n")
            .Append("creatures away.")
            .ToString(),
        new StringBuilder()
            .Append("However, my Master,")
            .Append("we need 80 SP in order\n")
            .Append("to create wind.")
            .ToString()
    };
    private static readonly string[] windYesNo = new string[]
    {
        new StringBuilder()
            .Append("WIND YES NO")
            .ToString()
    };
    private static readonly string[] windShowMeWhere = new string[]
    {
        new StringBuilder()
            .Append("WIND SHOW ME WHERE")
            .ToString()
    };
    // Start Menu readonlys.
    private static readonly string[] licensing = new string[]
    {
        new StringBuilder()
            .Append("All Rights Reserved\n")
            .Append("Copyright 2018-2022 Bradley Elenbaas\n")
            .Append("Licensed by Terrortronics")
            .ToString()
    };
    // Enter Player Name Menu readonlys.
    private static readonly string[] enterPlayerNamePre = new string[]
    {
        new StringBuilder()
            .Append("Please create a name\n")
            .Append("for yourself.")
            .ToString(),
        new StringBuilder()
            .Append("Press B Button\n")
            .Append("to enter any letter\n")
            .Append("you select.\n")
            .Append("Press Y Button\n")
            .Append("to cancel any letter\n")
            .Append("entry.")
            .ToString(),
        new StringBuilder()
            .Append("Press START Button\n")
            .Append("once you have created\n")
            .Append("your name.")
            .ToString()
    };
    // Town Builder Menu and Sky Palace Menu readonlys.
    private static readonly string[] columnZero = new string[]
    {
        new StringBuilder()
            .Append("Please select\n")
            .Append("the desired command\n")
            .Append("from menu at the right.")
            .ToString()
    };
    private static readonly string[] messageSpeedLikeThis = new string[]
    {
        new StringBuilder()
            .Append("Like this?")
            .ToString()
    };
    private static readonly string[] oh = new string[]
    {
        new StringBuilder()
            .Append("Oh!\n")
            .Append("You have changed your\n")
            .Append("mind?")
            .ToString()
    };
    private static readonly string[] progressLogComplete = new string[]
    {
        new StringBuilder()
            .Append("Finished recording.\n")
            .Append("Do you want to continue\n")
            .Append("building your world?")
            .ToString()
    };
    private static readonly string[] quitting = new string[]
    {
        new StringBuilder()
            .Append("You've worked so hard\n")
            .Append("today.\n")
            .Append("Let us rest now.\n")
            .Append("It's been an exhausting\n")
            .Append("day.")
            .ToString(),
        new StringBuilder()
            .Append("A short rest now will\n")
            .Append("result in a splendid\n")
            .Append("world tomorrow.")
            .ToString()
    };
    // Town Builder strings.
    private static readonly string[] listenToThePeople = new string[]
    {
        new StringBuilder()
            .Append("My master,\n")
            .Append("thank you very much for\n")
            .Append("giviing us such a\n")
            .Append("beautiful land.\n")
            .Append("Because of this, we can\n")
            .Append("work and be happy.")
            .ToString()
    };
    private static readonly string[] takeConfirmation = new string[]
    {
        new StringBuilder()
            .Append("Do you have anything\n")
            .Append("else to offer?")
            .ToString()
    };
    private static readonly string[] takeDecline = new string[]
    {
        new StringBuilder()
            .Append("Oh!\n")
            .Append("So you don't want it.")
            .ToString()
    };
    private static readonly string[] takeSuccess = new string[]
    {
        new StringBuilder()
            .Append("We have the following\n")
            .Append("to offer this year,\n")
            .Append("my Master.\n")
            .Append("Which one of our offerings\n")
            .Append("will you accept?")
            .ToString()
    };
    private static readonly string[] takeFailure = new string[]
    {
        new StringBuilder()
            .Append("We have nothing to\n")
            .Append("offer this year,\n")
            .Append("my Master.")
            .ToString()
    };
    private static readonly string[] takeAncientTablet = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] takeBomb = new string[]
    {
        new StringBuilder()
            .Append("If you hold this aloft,\n")
            .Append("all flying monsters\n")
            .Append("will be destroyed.")
            .ToString()
    };
    private static readonly string[] takeCompass = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] takeBridge = new string[]
    {
        new StringBuilder()
            .Append("My Master, this is the\n")
            .Append("bridge-building\n")
            .Append("technique that FILLMORE\n")
            .Append("is so proud of.")
            .ToString(),
        new StringBuilder()
            .Append("With this new skill,\n")
            .Append("people will be able to\n")
            .Append("build there homes on the\n")
            .Append("other side of the river.")
            .ToString()
    };
    private static readonly string[] takeHarmoniousMusic = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] takeHerb = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] takeLoafOfBread = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] takeMagicSkull = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] takeMagicalAura = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] takeMagicalFire = new string[]
    {
        new StringBuilder()
            .Append("The lightning bolt you\n")
            .Append("sent just smashed\n")
            .Append("a huge rock.\n")
            .Append("We found a Magical Fire\n")
            .Append("spell underneath the\n")
            .Append("rock.")
            .ToString(),
        new StringBuilder()
            .Append("The spell must belong\n")
            .Append("to you, my Master.\n")
            .Append("Please accept it as an\n")
            .Append("offering.")
            .ToString()
    };
    private static readonly string[] takeMagicalLight = new string[]
    {
        new StringBuilder()
            .Append("EMPTYs\n")
            .ToString()
    };
    private static readonly string[] takeMagicalStardust = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] takeSheepsFleece = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] takeSourceOfLife = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] takeStrengthOfAngel = new string[]
    {
        new StringBuilder()
            .Append("This appears to be\n")
            .Append("an Angel's arrow.")
            .ToString()
    };
    private static readonly string[] takeWheat = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useAncientTablet = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useBomb = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useCompass = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useHarmoniousMusic = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useHerb = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useLoafOfBread = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useMagicSkull = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useMagicalAura = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useMagicalFire = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useMagicalLight = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useMagicalStardust = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useSheepsFleece = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useSourceOfLife = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useSourceOfMagic = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    private static readonly string[] useStrengthOfAngel = new string[]
    {
        new StringBuilder()
            .Append("The power of the\n")
            .Append("Angel's arrow seems to\n")
            .Append("have increased.")
            .ToString()
    };
    private static readonly string[] useWheat = new string[]
    {
        new StringBuilder()
            .Append("EMPTY\n")
            .ToString()
    };
    // Quests readonlys.
    private static readonly string[] quest2 = new string[]
    {
        new StringBuilder()
            .Append("My master, we are\n")
            .Append("having a difficult time\n")
            .Append("building homes\n")
            .Append("because of many bushes")
            .ToString(),
        new StringBuilder()
            .Append("Please burn the bushes\n")
            .Append("and guide us as we\n")
            .Append("begin to build our\n")
            .Append("roads.")
            .ToString()
    };
    private static readonly string[] quest3 = new string[]
    {
        new StringBuilder()
            .Append("REPLACE THIS LATER")
            .ToString()
    };

    // Magic strings.
    private static string[] magicUnavailable = new string[]
    {
        new StringBuilder()
            .Append("Sir ")
            .Append(PlayerName)
            .Append("You have no magic!")
            .ToString()
    };
    // Miracle strings.
    private static string[] miracleFailure = new string[] 
    {
        new StringBuilder()
            .Append("Sir ")
            .Append(PlayerName)
            .Append("\n")
            .Append("unfortunately,\n")
            .Append("nothing happened.")
            .ToString()
    };
    // Enter Player Name Menu strings.
    private static string[] enterPlayerNamePost = new string[] 
    {
        new StringBuilder()
            .Append("Are you awake?\n")
            .Append("Sir ")
            .Append(PlayerName)
            .Append("\n")
            .Append("I am the Angel sent to\n")
            .Append("help you recover your\n")
            .Append("lost strength.")
            .ToString(),
        new StringBuilder()
            .Append("Now, all types of\n")
            .Append("monsters are in total\n")
            .Append("control of the earth.")
            .ToString(),
        new StringBuilder()
            .Append("This all came about\n")
            .Append("because of a demon they\n")
            .Append("call Tanzra,\n")
            .Append("the one who sealed your\n")
            .Append("power.")
            .ToString(),
        new StringBuilder()
            .Append("In order to restore\n")
            .Append("your power, you will\n")
            .Append("need to rekindle the\n")
            .Append("people's faith in you.")
            .ToString(),
        new StringBuilder()
            .Append("But first, let us go\n")
            .Append("down to the earth and\n")
            .Append("destroy all monsters,\n")
            .Append("that we may establish\n")
            .Append("a peaceful land for\n")
            .Append("our people to dwell in")
            .ToString()
    };
    // Town Builder Menu and Sky Palace Menu strings.
    private static string[] messageSpeed = new string[]
    {
        new StringBuilder()
            .Append("Sir ")
            .Append(PlayerName)
            .Append("\n")
            .Append("What shall I do for\n")
            .Append("the Message Speed?\n")
            .ToString()
    };
    private static string[] progressLogConfirmation = new string[] 
    {
        new StringBuilder()
            .Append("Sir ")
            .Append(PlayerName)
            .Append("\n")
            .Append("do you want to\n")
            .Append("record the progress\n")
            .Append("your world has made?")
            .ToString()
    };
    private static string[] progressLogContinue = new string[] 
    {
        new StringBuilder()
            .Append("Sir ")
            .Append(PlayerName)
            .Append("\n")
            .Append("you are so diligent\n")
            .Append("and hard working\n")
            .Append("If you must,\n")
            .Append("Please continue.")
            .ToString()
    };
    // Sky Palace Menu strings.
    private static string[] goingToFight = new string[] 
    {
        new StringBuilder()
            .Append("Sir ")
            .Append(PlayerName)
            .Append(" if we\n")
            .Append("destroy all monsters\n")
            .Append("in this land,\n")
            .Append("people will be able to\n")
            .Append("live here again.")
            .ToString()
    };
    private static string[] townIsUninhabitable = new string[] 
    {
        new StringBuilder()
            .Append("Sir ")
            .Append(PlayerName)
            .Append("\n")
            .Append("no one yet inhabits\n")
            .Append("this area.")
            .ToString()
    };
    // Town Builder strings.
    private static string[] takeSourceOfMagic = new string[] 
    {
        new StringBuilder()
            .Append("Sir ")
            .Append(PlayerName)
            .Append("we have received\n")
            .Append("another MP!!")
            .ToString()
    };
    private static string[] useOffering = new string[] 
    {
        new StringBuilder()
            .Append("Sir ")
            .Append(PlayerName)
            .Append("\n")
            .Append("which item will you\n")
            .Append("select?")
            .ToString()
    };
    private static string[] useBridge = new string[] 
    {
        new StringBuilder()
            .Append("Sir ")
            .Append(PlayerName)
            .Append("\n")
            .Append("the people of this\n")
            .Append("region already\n")
            .Append("understand the\n")
            .Append("the technology of building\n")
            .Append("bridges.")
            .ToString()
    };
    // Quest strings.
    private static string[] quest0 = new string[]
    {
        new StringBuilder()
            .Append("Sir ")
            .Append(PlayerName)
            .Append("\n")
            .Append("FILLMORE may became\n")
            .Append("a land where people can\n")
            .Append("live in peace.")
            .ToString(),
        new StringBuilder()
            .Append("Our first duty is to\n")
            .Append("protect our people from\n")
            .Append("any monsters.")
            .ToString(),
        new StringBuilder()
            .Append("I will do as you\n")
            .Append("instruct.\n")
            .Append("Please rid the land of\n")
            .Append("these monsters with my\n")
            .Append("arrows.")
            .ToString(),
        new StringBuilder()
            .Append("There are several\n")
            .Append("mysterious circles\n")
            .Append("on the ground which\n")
            .Append("represent monsters'")
            .Append("Lairs.")
            .ToString(),
        new StringBuilder()
            .Append("If you direct\n")
            .Append("the people correctly,\n")
            .Append("they will be able to\n")
            .Append("seal the lairs.")
            .ToString(),
        new StringBuilder()
            .Append("You will discover the\n")
            .Append("monster that controls\n")
            .Append("this land.")
            .ToString(),
        new StringBuilder()
            .Append("If destroyed, control\n")
            .Append("of this land's destiny\n")
            .Append("will return to her\n")
            .Append("people.")
            .ToString(),
        new StringBuilder()
            .Append("All right, my Master,\n")
            .Append("let us work towards\n")
            .Append("peace.\n")
            .ToString()
    };
    private static string[] quest1 = new string[] 
    {
        new StringBuilder()
            .Append("Sir ")
            .Append(PlayerName)
            .Append("\n")
            .Append("I know it's unexpected,\n")
            .Append("but out people in\n")
            .Append("FILLMORE have\n")
            .Append("something to tell you")
            .ToString()
    };

    // Magic properties.
    public static string[] MagicUnavailable { get { return magicUnavailable; } }
    // Miracle properties.
    public static string[] MiracleFailure { get { return miracleFailure; } }
    public static string[] LightningAvailable { get { return lightningAvailable; } }
    public static string[] LightningUnavailable { get { return lightningUnavailable; } }
    public static string[] LightningYesNo { get { return lightningYesNo;  } }
    public static string[] LightningShowMeWhere { get { return lightningShowMeWhere; } }
    public static string[] RainAvailable { get { return rainAvailable; } }
    public static string[] RainUnavailable { get { return rainUnavailable; } }
    public static string[] RainYesNo { get { return rainYesNo;  } }
    public static string[] RainShowMeWhere { get { return rainShowMeWhere ; } }
    public static string[] SunAvailable { get { return sunAvailable; } }
    public static string[] SunUnavailable { get { return sunUnavailable; } }
    public static string[] SunYesNo { get { return sunYesNo; } }
    public static string[] SunShowMeWhere { get { return sunShowMeWhere; } }
    public static string[] WindAvailable { get { return windAvailable; } }
    public static string[] WindUnavailable { get { return windUnavailable; } }
    public static string[] WindYesNo { get { return windYesNo; } }
    public static string[] WindShowMeWhere { get { return windShowMeWhere; } }
    public static string[] EarthquakeAvailable { get { return earthquakeAvailable; } }
    public static string[] EarthquakeUnavailable { get { return earthquakeUnavailable; } }
    public static string[] EarthquakeYesNo { get { return earthquakeYesNo; } }
    public static string[] EarthquakeShowMeWhere { get { return earthquakeShowMeWhere; } }
    // Start Menu properties.
    public static string[] Licensing { get { return licensing; } }
    // Enter Player Name Menu properties.
    public static string[] EnterPlayerNamePre { get { return enterPlayerNamePre; } }
    public static string[] EnterPlayerNamePost { get { return enterPlayerNamePost; } }
    // Town Builder Menu and Sky Palace Menu properties.
    public static string[] ColumnZero { get { return columnZero; } }
    public static string[] MessageSpeed { get { return messageSpeed; } }
    public static string[] MessageSpeedLikeThis { get { return messageSpeedLikeThis; } }
    public static string[] Oh { get { return oh; } }
    public static string[] ProgressLogComplete { get { return progressLogComplete; } }
    public static string[] ProgressLogConfirmation { get { return progressLogConfirmation; } }
    public static string[] ProgressLogContinue { get { return progressLogContinue; } }
    public static string[] Quitting { get { return quitting; } }
    // Sky Palace properties.
    public static string[] GoingToFight { get { return goingToFight; } }
    public static string[] TownIsUninhabitable { get { return townIsUninhabitable; } }
    // Town Builder properties.
    public static string[] ListenToThePeople { get { return listenToThePeople; } }
    public static string[] TakeConfirmation { get { return takeConfirmation; } }
    public static string[] TakeDecline { get { return takeDecline; } }
    public static string[] TakeSuccess { get { return takeSuccess; } }
    public static string[] TakeFailure { get { return takeFailure; } }
    public static string[] TakeAncientTablet { get { return takeAncientTablet; } }
    public static string[] TakeBomb { get { return takeBomb; } }
    public static string[] TakeCompass { get { return takeCompass; } }
    public static string[] TakeBridge { get { return takeBridge; } }
    public static string[] TakeHarmoniousMusic { get { return takeHarmoniousMusic; } }
    public static string[] TakeHerb { get { return takeHerb; } }
    public static string[] TakeLoafOfBread { get { return takeLoafOfBread; } }
    public static string[] TakeMagicSkull { get { return takeMagicSkull; } }
    public static string[] TakeMagicalAura { get { return takeMagicalAura; } }
    public static string[] TakeMagicalFire { get { return takeMagicalFire; } }
    public static string[] TakeMagicalLight { get { return takeMagicalLight; } }
    public static string[] TakeMagicalStardust { get { return takeMagicalStardust; } }
    public static string[] TakeSheepsFleece { get { return takeSheepsFleece; } }
    public static string[] TakeSourceOfLife { get { return takeSourceOfLife; } }
    public static string[] TakeSourceOfMagic { get { return takeSourceOfMagic; } }
    public static string[] TakeStrengthOfAngel { get { return takeStrengthOfAngel; } }
    public static string[] TakeWheat { get { return takeWheat; } }
    public static string[] UseOffering { get { return useOffering; } }
    public static string[] UseAncientTablet { get { return useAncientTablet; } }
    public static string[] UseBomb { get { return useBomb; } }
    public static string[] UseCompass { get { return useCompass; } }
    public static string[] UseBridge { get { return useBridge; } }
    public static string[] UseHarmoniousMusic { get { return useHarmoniousMusic; } }
    public static string[] UseHerb { get { return useHerb; } }
    public static string[] UseLoafOfBread { get { return useLoafOfBread; } }
    public static string[] UseMagicSkull { get { return useMagicSkull; } }
    public static string[] UseMagicalAura { get { return useMagicalAura; } }
    public static string[] UseMagicalFire { get { return useMagicalFire; } }
    public static string[] UseMagicalLight { get { return useMagicalLight; } }
    public static string[] UseMagicalStardust { get { return useMagicalStardust; } }
    public static string[] UseSheepsFleece { get { return useSheepsFleece; } }
    public static string[] UseSourceOfLife { get { return useSourceOfLife; } }
    public static string[] UseSourceOfMagic { get { return useSourceOfMagic; } }
    public static string[] UseStrengthOfAngel { get { return useStrengthOfAngel; } }
    public static string[] UseWheat { get { return useWheat; } }
    // Quest properties.
    public static string[] Quest0 { get { return quest0; } }
    public static string[] Quest1 { get { return quest1; } }
    public static string[] Quest2 { get { return quest2; } }
    public static string[] Quest3 { get { return quest3; } }

    // The current string in an array of strings. 
    public static int Index { get; set; }

    // Is the message currently visible.
    public static bool IsMessageVisible { get; set; }

    // The name entered during the 'Enter Player Name' section.
    public static string PlayerName { get; set; }


    // Increments index. Returns true is complete, otherwise returns false.
    public static bool IncrementIndex(int length)
    {
        var result = false;
        Index++;
        if (Index >= length)
        {
            Index = 0;
            result = true;
        }
        return result;
    }
}
