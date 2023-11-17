/*
 * Title: StandaloneCanvas file.
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
using TMPro;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class StandaloneCanvas : MonoBehaviour
{
    [SerializeField]
    private Squares squares;

    [SerializeField]
    private GameObject blackBackground;

    [SerializeField]
    private GameObject topTownName;

    [SerializeField]
    private TMP_Text topTownNameText;

    [SerializeField]
    private GameObject topHealthPoints;

    [SerializeField]
    private TMP_Text topHealthPointsText;

    [SerializeField]
    private GameObject topHourglass;

    [SerializeField]
    private TMP_Text topHourglassText;

    [SerializeField]
    private GameObject topPopulation;

    [SerializeField]
    private TMP_Text topPopulationText;

    [SerializeField]
    private GameObject topSpellPoints;

    [SerializeField]
    private TMP_Text topSpellPointsText;

    [SerializeField]
    private GameObject continueGame;

    [SerializeField]
    private GameObject newGame;

    [SerializeField]
    private GameObject professionalMode;

    [SerializeField]
    private GameObject title;

    [SerializeField]
    private GameObject pause;

    [SerializeField]
    private GameObject message;

    [SerializeField]
    private TMP_Text messageText;

    [SerializeField]
    private GameObject townBuilderBackground;

    [SerializeField]
    private GameObject townBuilder0x0;

    [SerializeField]
    private GameObject townBuilder0x1;

    [SerializeField]
    private GameObject townBuilder0x2;

    [SerializeField]
    private GameObject townBuilder1x0;

    [SerializeField]
    private GameObject townBuilder1x1;

    [SerializeField]
    private GameObject townBuilder1x2;

    [SerializeField]
    private GameObject townBuilder2x0;

    [SerializeField]
    private GameObject townBuilder2x1;

    [SerializeField]
    private GameObject townBuilder2x2;

    [SerializeField]
    private GameObject townBuilder2x3;

    [SerializeField]
    private GameObject townBuilder2x4;

    [SerializeField]
    private GameObject townBuilder2x5;

    [SerializeField]
    private GameObject townBuilder3x0;

    [SerializeField]
    private GameObject townBuilder3x1;

    [SerializeField]
    private GameObject townBuilder3x2;

    [SerializeField]
    private GameObject townBuilder4x0;

    [SerializeField]
    private GameObject townBuilder4x1;

    [SerializeField]
    private GameObject townBuilder4x2;

    [SerializeField]
    private GameObject townBuilder5x0;

    [SerializeField]
    private GameObject townBuilder5x1;

    [SerializeField]
    private GameObject townBuilder5x2;

    [SerializeField]
    private GameObject skyPalaceBackground;

    [SerializeField]
    private GameObject skyPalace0x0;

    [SerializeField]
    private GameObject skyPalace0x1;

    [SerializeField]
    private GameObject skyPalace0x2;

   [SerializeField]
    private GameObject skyPalace1x0;

    [SerializeField]
    private GameObject skyPalace1x1;

    [SerializeField]
    private GameObject skyPalace1x2;

   [SerializeField]
    private GameObject skyPalace2x0;

    [SerializeField]
    private GameObject skyPalace2x1;

    [SerializeField]
    private GameObject skyPalace2x2;

    [SerializeField]
    private GameObject skyPalace3x0;

    [SerializeField]
    private GameObject skyPalace3x1;

    [SerializeField]
    private GameObject skyPalace3x2;

    [SerializeField]
    private GameObject description;

    [SerializeField]
    private TMP_Text descriptionText;

    [SerializeField]
    private GameObject variableBackground;

    [SerializeField]
    private GameObject y;

    [SerializeField]
    private GameObject yes;

    [SerializeField]
    private GameObject x;

    [SerializeField]
    private GameObject no;

    [SerializeField]
    private GameObject itemName;

    [SerializeField]
    private GameObject item0x0;

    [SerializeField]
    private GameObject item0x1;

    [SerializeField]
    private GameObject item0x2;

    [SerializeField]
    private GameObject item0x3;

    [SerializeField]
    private GameObject item1x0;

    [SerializeField]
    private GameObject item1x1;

    [SerializeField]
    private GameObject item1x2;

    [SerializeField]
    private GameObject item1x3;

    [SerializeField]
    public GameObject[] statusOfPlayer;

    [SerializeField]
    public TMP_Text statusOfPlayerPlayerName;

    [SerializeField]
    public TMP_Text statusOfPlayerSourceOfLife;

    [SerializeField]
    public TMP_Text statusOfPlayerPlayerLevel;

    [SerializeField]
    public TMP_Text statusOfPlayerHealthPoints;

    [SerializeField]
    public TMP_Text statusOfPlayerSpellPoints;

    [SerializeField]
    public TMP_Text statusOfPlayerMagicPoints;

    [SerializeField]
    public TMP_Text statusOfPlayerExperienceToNextLevel;

    [SerializeField]
    public TMP_Text statusOfPlayerExperienceTotal;

    [SerializeField]
    public TMP_Text statusOfPlayerMagicalFire;

    [SerializeField]
    public TMP_Text statusOfPlayerMagicalStardust;

    [SerializeField]
    public TMP_Text statusOfPlayerMagicalAura;

    [SerializeField]
    public TMP_Text statusOfPlayerMagicalLight;

    [SerializeField]
    public TMP_Text statusOfPlayerItem0x0;

    [SerializeField]
    public TMP_Text statusOfPlayerItem0x1;

    [SerializeField]
    public TMP_Text statusOfPlayerItem0x2;

    [SerializeField]
    public TMP_Text statusOfPlayerItem0x3;

    [SerializeField]
    public TMP_Text statusOfPlayerItem1x0;

    [SerializeField]
    public TMP_Text statusOfPlayerItem1x1;

    [SerializeField]
    public TMP_Text statusOfPlayerItem1x2;

    [SerializeField]
    public TMP_Text statusOfPlayerItem1x3;

    [SerializeField]
    public GameObject[] statusOfCities;

    [SerializeField]
    private TMP_Text statusOfCitiesScore;

    [SerializeField]
    private TMP_Text statusOfCitiesFillmoreAct1;

    [SerializeField]
    private TMP_Text statusOfCitiesFillmoreAct2;

    [SerializeField]
    private TMP_Text statusOfCitiesBloodpoolAct1;

    [SerializeField]
    private TMP_Text statusOfCitiesBloodpoolAct2;

    [SerializeField]
    private TMP_Text statusOfCitiesKasandoraAct1;

    [SerializeField]
    private TMP_Text statusOfCitiesKasandoraAct2;

    [SerializeField]
    private TMP_Text statusOfCitiesAitosAct1;

    [SerializeField]
    private TMP_Text statusOfCitiesAitosAct2;

    [SerializeField]
    private TMP_Text statusOfCitiesMarahnaAct1;

    [SerializeField]
    private TMP_Text statusOfCitiesMarahnaAct2;

    [SerializeField]
    private TMP_Text statusOfCitiesNorthwallAct1;

    [SerializeField]
    private TMP_Text statusOfCitiesNorthwallAct2;

    [SerializeField]
    private GameObject enterPlayerNameBackground;

    [SerializeField]
    private GameObject enterPlayerNamePleaseEnterMastersName;

    [SerializeField]
    private GameObject enterPlayerNamePlayerName0;

    [SerializeField]
    private TMP_Text enterPlayerNamePlayerName0Text;

    [SerializeField]
    private GameObject enterPlayerNamePlayerName1;

    [SerializeField]
    private TMP_Text enterPlayerNamePlayerName1Text;

    [SerializeField]
    private GameObject enterPlayerNamePlayerName2;

    [SerializeField]
    private TMP_Text enterPlayerNamePlayerName2Text;

    [SerializeField]
    private GameObject enterPlayerNamePlayerName3;

    [SerializeField]
    private TMP_Text enterPlayerNamePlayerName3Text;

    [SerializeField]
    private GameObject enterPlayerNamePlayerName4;

    [SerializeField]
    private TMP_Text enterPlayerNamePlayerName4Text;

    [SerializeField]
    private GameObject enterPlayerNamePlayerName5;

    [SerializeField]
    private TMP_Text enterPlayerNamePlayerName5Text;

    [SerializeField]
    private GameObject enterPlayerNamePlayerName6;

    [SerializeField]
    private TMP_Text enterPlayerNamePlayerName6Text;

    [SerializeField]
    private GameObject enterPlayerNamePlayerName7;

    [SerializeField]
    private TMP_Text enterPlayerNamePlayerName7Text;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseA;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseB;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseC;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseD;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseE;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseF;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseG;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseH;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseI;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseJ;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseK;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseL;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseM;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseN;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseO;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseP;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseQ;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseR;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseS;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseT;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseU;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseV;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseW;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseX;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseY;

    [SerializeField]
    private GameObject enterPlayerNameUppercaseZ;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseA;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseB;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseC;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseD;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseE;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseF;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseG;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseH;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseI;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseJ;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseK;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseL;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseM;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseN;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseO;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseP;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseQ;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseR;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseS;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseT;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseU;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseV;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseW;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseX;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseY;

    [SerializeField]
    private GameObject enterPlayerNameLowercaseZ;

    [SerializeField]
    private GameObject enterPlayerName0;

    [SerializeField]
    private GameObject enterPlayerName1;

    [SerializeField]
    private GameObject enterPlayerName2;

    [SerializeField]
    private GameObject enterPlayerName3;

    [SerializeField]
    private GameObject enterPlayerName4;

    [SerializeField]
    private GameObject enterPlayerName5;

    [SerializeField]
    private GameObject enterPlayerName6;

    [SerializeField]
    private GameObject enterPlayerName7;

    [SerializeField]
    private GameObject enterPlayerName8;

    [SerializeField]
    private GameObject enterPlayerName9;

    [SerializeField]
    private GameObject enterPlayerNamePeriod;

    [SerializeField]
    private GameObject enterPlayerNameBackspace;

    [SerializeField]
    private GameObject enterPlayerNameEnd;

    private GameObject[,] items;

    private GameObject[,] enterPlayerName;

    private GameObject[] playerName;

    private TMP_Text[] playerNameText;


    void Start()
    {
        items = new GameObject[,]
        {
            { item0x0, item0x1, item0x2, item0x3 },
            { item1x0, item1x1, item1x2, item1x3 }
        };
        enterPlayerName = new GameObject[,]
        {
            {
                enterPlayerNameUppercaseA,
                enterPlayerNameUppercaseB,
                enterPlayerNameUppercaseC,
                enterPlayerNameUppercaseD,
                enterPlayerNameUppercaseE,
                enterPlayerNameUppercaseF,
                enterPlayerNameUppercaseG,
                enterPlayerNameUppercaseH,
                enterPlayerNameUppercaseI,
                enterPlayerNameUppercaseJ,
                enterPlayerNameUppercaseK,
                enterPlayerNameUppercaseL,
                enterPlayerNameUppercaseM
            },
            {
                enterPlayerNameUppercaseN,
                enterPlayerNameUppercaseO,
                enterPlayerNameUppercaseP,
                enterPlayerNameUppercaseQ,
                enterPlayerNameUppercaseR,
                enterPlayerNameUppercaseS,
                enterPlayerNameUppercaseT,
                enterPlayerNameUppercaseU,
                enterPlayerNameUppercaseV,
                enterPlayerNameUppercaseW,
                enterPlayerNameUppercaseX,
                enterPlayerNameUppercaseY,
                enterPlayerNameUppercaseZ
            },
            {
                enterPlayerNameLowercaseA,
                enterPlayerNameLowercaseB,
                enterPlayerNameLowercaseC,
                enterPlayerNameLowercaseD,
                enterPlayerNameLowercaseE,
                enterPlayerNameLowercaseF,
                enterPlayerNameLowercaseG,
                enterPlayerNameLowercaseH,
                enterPlayerNameLowercaseI,
                enterPlayerNameLowercaseJ,
                enterPlayerNameLowercaseK,
                enterPlayerNameLowercaseL,
                enterPlayerNameLowercaseM
            },
            {
                enterPlayerNameLowercaseN,
                enterPlayerNameLowercaseO,
                enterPlayerNameLowercaseP,
                enterPlayerNameLowercaseQ,
                enterPlayerNameLowercaseR,
                enterPlayerNameLowercaseS,
                enterPlayerNameLowercaseT,
                enterPlayerNameLowercaseU,
                enterPlayerNameLowercaseV,
                enterPlayerNameLowercaseW,
                enterPlayerNameLowercaseX,
                enterPlayerNameLowercaseY,
                enterPlayerNameLowercaseZ
            },
            {
                enterPlayerName0,
                enterPlayerName1,
                enterPlayerName2,
                enterPlayerName3,
                enterPlayerName4,
                enterPlayerName5,
                enterPlayerName6,
                enterPlayerName7,
                enterPlayerName8,
                enterPlayerName9,
                enterPlayerNamePeriod,
                enterPlayerNameBackspace,
                enterPlayerNameEnd
            }
        };
        playerName = new GameObject[]
        {
            enterPlayerNamePlayerName0,
            enterPlayerNamePlayerName1,
            enterPlayerNamePlayerName2,
            enterPlayerNamePlayerName3,
            enterPlayerNamePlayerName4,
            enterPlayerNamePlayerName5,
            enterPlayerNamePlayerName6,
            enterPlayerNamePlayerName7
        };
        playerNameText = new TMP_Text[]
        {
            enterPlayerNamePlayerName0Text,
            enterPlayerNamePlayerName1Text,
            enterPlayerNamePlayerName2Text,
            enterPlayerNamePlayerName3Text,
            enterPlayerNamePlayerName4Text,
            enterPlayerNamePlayerName5Text,
            enterPlayerNamePlayerName6Text,
            enterPlayerNamePlayerName7Text
        };
        newGame.SetActive(true);
        title.SetActive(true);
        blackBackground.SetActive(true);
        switch (SaveGameData.intArray[(int)SaveGameData.IntArray.SaveGame])
        {
            case (int)SaveGameData.SaveGame.None:
                break;
            case (int)SaveGameData.SaveGame.SavedGame:
                continueGame.SetActive(true);
                break;
            case (int)SaveGameData.SaveGame.BeatenGame:
                continueGame.SetActive(true);
                professionalMode.SetActive(true);
                break;
        }
        Route.MessageTurnOn();
    }

    private void Update()
    {
        if (Menus.isStart)
        {
            switch (Menus.J)
            {
                case 0:
                    EventSystem.current.SetSelectedGameObject(continueGame);
                    break;
                case 1:
                    EventSystem.current.SetSelectedGameObject(newGame);
                    break;
                case 2:
                    EventSystem.current.SetSelectedGameObject(professionalMode);
                    break;
            }
        }
        else if (!Menus.isStart
                 && continueGame.activeSelf
                 && newGame.activeSelf
                 && professionalMode.activeSelf
                 && title.activeSelf)
        {
            continueGame.SetActive(false);
            newGame.SetActive(false);
            professionalMode.SetActive(false);
            title.SetActive(false);
            message.SetActive(false);
            blackBackground.SetActive(false);
            topHealthPoints.SetActive(true);
            topHourglass.SetActive(true);
            topPopulation.SetActive(true);
            topSpellPoints.SetActive(true);
            topTownName.SetActive(true);
        }
        if (Menus.isEnterPlayerNameMenuVisible)
        {
            EnterPlayerNameOn();
            EventSystem.current
                .SetSelectedGameObject(enterPlayerName[Menus.L, Menus.K]);
            for (var i = 0; i < 8; i++)
            {
                if (i < Route.nameIndex)
                {
                    playerNameText[i].text = Messages.PlayerName[i].ToString();
                }
                else
                {
                    playerNameText[i].text = "_";
                }
            }
        }
        else if (!Menus.isEnterPlayerNameMenuVisible)
        {
            EnterPlayerNameOff();
        }
        if (Menus.isTownBuilderMenuVisible)
        {
            TownBuilderActivateRow();
            switch (Menus.I)
            {
                case 0:
                    switch (Menus.J)
                    {
                        case 0:
                            EventSystem.current.SetSelectedGameObject(townBuilder0x0);
                            break;
                        case 1:
                            EventSystem.current.SetSelectedGameObject(townBuilder0x1);
                            break;
                        case 2:
                            EventSystem.current.SetSelectedGameObject(townBuilder0x2);
                            break;
                    }
                    break;
                case 1:
                    switch (Menus.J)
                    {
                        case 0:
                            EventSystem.current.SetSelectedGameObject(townBuilder1x0);
                            break;
                        case 1:
                            EventSystem.current.SetSelectedGameObject(townBuilder1x1);
                            break;
                        case 2:
                            EventSystem.current.SetSelectedGameObject(townBuilder1x2);
                            break;
                    }
                    break;
                case 2:
                    if (Menus.isLightningYesNo
                        || Menus.isRainYesNo
                        || Menus.isSunYesNo
                        || Menus.isWindYesNo
                        || Menus.isEarthquakeYesNo)
                    {
                        switch (Menus.K)
                        {
                            case 0:
                                EventSystem.current.SetSelectedGameObject(y);
                                break;
                            case 1:
                                EventSystem.current.SetSelectedGameObject(x);
                                break;
                        }
                    }
                    else
                    {
                        switch (Menus.J)
                        {
                            case 0:
                                EventSystem.current.SetSelectedGameObject(townBuilder2x0);
                                break;
                            case 1:
                                EventSystem.current.SetSelectedGameObject(townBuilder2x1);
                                break;
                            case 2:
                                EventSystem.current.SetSelectedGameObject(townBuilder2x2);
                                break;
                            case 3:
                                EventSystem.current.SetSelectedGameObject(townBuilder2x3);
                                break;
                            case 4:
                                EventSystem.current.SetSelectedGameObject(townBuilder2x4);
                                break;
                            case 5:
                                EventSystem.current.SetSelectedGameObject(townBuilder2x5);
                                break;
                        }
                    }
                    break;
                case 3:
                    switch (Menus.J)
                    {
                        case 0:
                            EventSystem.current.SetSelectedGameObject(townBuilder3x0);
                            break;
                        case 1:
                            EventSystem.current.SetSelectedGameObject(townBuilder3x1);
                            break;
                        case 2:
                            EventSystem.current.SetSelectedGameObject(townBuilder3x2);
                            break;
                    }
                    break;
                case 4:
                    switch (Menus.J)
                    {
                        case 0:
                            EventSystem.current.SetSelectedGameObject(townBuilder4x0);
                            break;
                        case 1:
                            EventSystem.current.SetSelectedGameObject(townBuilder4x1);
                            break;
                        case 2:
                            EventSystem.current.SetSelectedGameObject(townBuilder4x2);
                            break;
                    }
                    break;
                case 5:
                    if (Menus.isProgressLogConfirmationVisible
                        || Menus.isReturnToWorldPromptVisible)
                    {
                        switch (Menus.K)
                        {
                            case 0:
                                EventSystem.current.SetSelectedGameObject(y);
                                break;
                            case 1:
                                EventSystem.current.SetSelectedGameObject(x);
                                break;
                        }
                    }
                    else
                    {
                        switch (Menus.J)
                        {
                            case 0:
                                EventSystem.current.SetSelectedGameObject(townBuilder5x0);
                                break;
                            case 1:
                                EventSystem.current.SetSelectedGameObject(townBuilder5x1);
                                break;
                            case 2:
                                EventSystem.current.SetSelectedGameObject(townBuilder5x2);
                                break;
                        }
                    }
                    break;
            }
        }
        else if (!Menus.isTownBuilderMenuVisible
                 && townBuilder0x0.activeSelf)
        {
            TownBuilderDeactivate();
        }

        if (Menus.isSkyPalaceMenuVisible)
        {
            SkyPalaceActivateRow();
            switch (Menus.I)
            {
                case 0:
                    switch (Menus.J)
                    {
                        case 0:
                            EventSystem.current.SetSelectedGameObject(skyPalace0x0);
                            break;
                        case 1:
                            EventSystem.current.SetSelectedGameObject(skyPalace0x1);
                            break;
                        case 2:
                            EventSystem.current.SetSelectedGameObject(skyPalace0x2);
                            break;
                    }
                    break;
                case 1:
                    switch (Menus.J)
                    {
                        case 0:
                            EventSystem.current.SetSelectedGameObject(skyPalace1x0);
                            break;
                        case 1:
                            EventSystem.current.SetSelectedGameObject(skyPalace1x1);
                            break;
                        case 2:
                            EventSystem.current.SetSelectedGameObject(skyPalace1x2);
                            break;
                    }
                    break;
                case 2:
                    switch (Menus.J)
                    {
                        case 0:
                            EventSystem.current.SetSelectedGameObject(skyPalace2x0);
                            break;
                        case 1:
                            EventSystem.current.SetSelectedGameObject(skyPalace2x1);
                            break;
                        case 2:
                            EventSystem.current.SetSelectedGameObject(skyPalace2x2);
                            break;
                    }
                    break;
                case 3:
                    switch (Menus.J)
                    {
                        case 0:
                            EventSystem.current.SetSelectedGameObject(skyPalace3x0);
                            break;
                        case 1:
                            EventSystem.current.SetSelectedGameObject(skyPalace3x1);
                            break;
                        case 2:
                            EventSystem.current.SetSelectedGameObject(skyPalace3x2);
                            break;
                    }
                    break;
            }
            if (!skyPalaceBackground.activeSelf)
            {
                SkyPalaceOn();
            }
            variableBackground.SetActive(true);
            if (Menus.isProgressLogConfirmationVisible)
            {
                VariableYesNoOn();
            }
            else if (Menus.isReturnToWorldPromptVisible)
            {
                VariableYesNoOn();
            }
            else if (Route.isColumnZeroMessageVisible)
            {
            }
            else if (Route.isGoingToFight)
            {
            }
            else if (Route.isOhMessageVisible)
            {
            }
            else if (Menus.isMessageSpeedMenuVisible)
            {
            }
            else if (Menus.isMessageSpeedConfirmationVisible)
            {
            }
            else if (Menus.isReturnToWorldPromptVisible)
            {
            }
            else if (Route.isProgressLogFinished)
            {
            }
            else if (Route.isQuittingGame)
            {
            }
            else
            {
            }
        }
        else if (!Menus.isSkyPalaceMenuVisible)
        {
            if (skyPalaceBackground.activeSelf)
            {
                SkyPalaceOff();
            }
        }

        if (Menus.isTakeAnOffering
            || Menus.isTakeAnOfferingConfirmation
            || Menus.isTakeAnOfferingDecline
            || Menus.isUseAnOffering
            || Menus.isUseAnOfferingDescription)
        {
            OfferingsGridUpdate();
        }

        /*if (Menus.isStart)
        {
        }
        else */if (Messages.IsMessageVisible)
        {
            if (!message.activeSelf)
            {
                message.SetActive(true);
            }
            if (Route.messageText.Equals(""))
            {
                messageText.text = "";
            }
            else
            {
                messageText.text = Route.messageText.Substring(0, Timers.scrollIndex);
            }
        }
        else
        {
            if (message.activeSelf)
            {
                message.SetActive(false);
            }
        }

        if (!Menus.isStart
            && !Menus.isSkyPalaceMenuVisible
            && Towns.townIndex != 7)
        {
            topTownNameText.text = new StringBuilder()
                .Append(Towns.names[Towns.townIndex])
                .ToString();
            topHealthPointsText.text = new StringBuilder()
                .Append(Player.healthPoints)
                .ToString();
            topHourglassText.text = new StringBuilder()
                .Append((int)(Towns.periods[Towns.townIndex] - Route.populationTimeSinceStartOfRound[Towns.townIndex]))
                .ToString();
            topPopulationText.text = new StringBuilder()
                .Append(Towns.populations[Towns.townIndex])
                .Append(" / ")
                .Append(Towns.populationMaxes[Towns.townIndex])
                .ToString();
            topSpellPointsText.text = new StringBuilder()
                .Append(Player.spellPoints)
                .Append(" / ")
                .Append(LevelTables.spellPoints[Player.level])
                .ToString();
        }
        if (Route.isStatusOfMasterVisible)
        {
            if (!statusOfPlayer[0].activeSelf)
            {
                for (var i = 0; i < statusOfPlayer.Length; i++)
                {
                    statusOfPlayer[i].SetActive(true);
                }
            }
            statusOfPlayerPlayerName.text = Messages.PlayerName;
            statusOfPlayerSourceOfLife.text = Player.sourceOfLifeCount.ToString();
            statusOfPlayerPlayerLevel.text = Player.level.ToString();
            statusOfPlayerHealthPoints.text = Player.healthPoints.ToString();
            statusOfPlayerSpellPoints.text = Player.spellPoints.ToString();
            statusOfPlayerMagicPoints.text = Player.sourceOfMagicCount.ToString();
            statusOfPlayerExperienceToNextLevel.text = 
                Player.level == Player.LEVEL_MAX 
                    ? "Max" 
                    : (LevelTables.populations[Player.level + 1] - LevelTables.populations[Player.level]).ToString();
            var populationTotal = 0;
            for (var i = 0; i < Towns.populations.Length; i++)
            {
                populationTotal += Towns.populations[i];
            }
            statusOfPlayerExperienceTotal.text = populationTotal.ToString();
            statusOfPlayerMagicalFire.text =
                Magics.isMagicalFireUnlockled
                    ? ""
                    : "Magical\nFire";
            statusOfPlayerMagicalStardust.text =
                Magics.isMagicalStartdustUnlockled
                    ? ""
                    : "Magical\nStardust";
            statusOfPlayerMagicalAura.text =
                Magics.isMagicalAuraUnlockled
                    ? ""
                    : "Magical\nAura";
            statusOfPlayerMagicalLight.text =
                Magics.isMagicalLightUnlockled
                    ? ""
                    : "Magical\nLight";
            statusOfPlayerItem0x0.text =
                Menus.takenIndex > 0
                    ? Menus.takenIcons[0, 0]
                    : "";
            statusOfPlayerItem0x1.text =
                Menus.takenIndex > 1
                    ? Menus.takenIcons[0, 1]
                    : "";
            statusOfPlayerItem0x2.text =
                Menus.takenIndex > 2
                    ? Menus.takenIcons[0, 2]
                    : "";
            statusOfPlayerItem0x3.text =
                Menus.takenIndex > 3
                    ? Menus.takenIcons[0, 3]
                    : "";
            statusOfPlayerItem1x0.text =
                Menus.takenIndex > 4
                    ? Menus.takenIcons[1, 0]
                    : "";
            statusOfPlayerItem1x1.text =
                Menus.takenIndex > 5
                    ? Menus.takenIcons[1, 1]
                    : "";
            statusOfPlayerItem1x2.text =
                Menus.takenIndex > 6
                    ? Menus.takenIcons[1, 2]
                    : "";
            statusOfPlayerItem1x3.text =
                Menus.takenIndex > 7
                    ? Menus.takenIcons[1, 3]
                    : "";
        }
        else if (!Route.isStatusOfMasterVisible
                 && statusOfPlayer[0].activeSelf)
        {
            for (var i = 0; i < statusOfPlayer.Length; i++)
            {
                statusOfPlayer[i].SetActive(false);
            }
        }
        else if (Route.isStatusOfCitiesVisible)
        {
            if (!statusOfCities[0].activeSelf)
            {
                for (var i = 0; i < statusOfCities.Length; i++)
                {
                    statusOfCities[i].SetActive(true);
                }
            }
            statusOfCitiesScore.text = Status.score.ToString();
            statusOfCitiesFillmoreAct1.text = Status.scoreFillmoreActI.ToString();
            statusOfCitiesFillmoreAct2.text = Status.scoreFillmoreActII.ToString();
            statusOfCitiesBloodpoolAct1.text = Status.scoreBloodpoolActI.ToString();
            statusOfCitiesBloodpoolAct2.text = Status.scoreBloodpoolActII.ToString();
            statusOfCitiesKasandoraAct1.text = Status.scoreKasandoraActI.ToString();
            statusOfCitiesKasandoraAct2.text = Status.scoreKasandoraActII.ToString();
            statusOfCitiesAitosAct1.text = Status.scoreAitosActI.ToString();
            statusOfCitiesAitosAct2.text = Status.scoreAitosActII.ToString();
            statusOfCitiesMarahnaAct1.text = Status.scoreMarahnaActI.ToString();
            statusOfCitiesMarahnaAct2.text = Status.scoreMarahnaActII.ToString();
            statusOfCitiesNorthwallAct1.text = Status.scoreNorthwallActI.ToString();
            statusOfCitiesNorthwallAct2.text = Status.scoreNorthwallActII.ToString();
        }
        else if (!Route.isStatusOfCitiesVisible
                 && statusOfCities[0].activeSelf)
        {
            for (var i = 0; i < statusOfCities.Length; i++)
            {
                statusOfCities[i].SetActive(false);
            }
        }
        else if (Menus.isTownBuilderMenuVisible)
        {
            descriptionText.text = Descriptions.townBuilder[Menus.I, Menus.J];
            if (Route.isColumnZeroMessageVisible)
            {
            }
            else if (Route.isOhMessageVisible)
            {
            }
            else if (Menus.isUseAnOffering)
            {
            }
            else if (Menus.isTakeAnOffering)
            {
                Menus.isTakeAnOfferingConfirmation = true;
                Menus.ResetKL();
            }
            else if (Menus.isTakeAnOfferingConfirmation)
            {
                Menus.isReturnToOfferings = true;
            }
            else if (Menus.isReturnToOfferings)
            {
                Route.TakeAnOffering();
                Menus.ResetM();
            }
            else if (Menus.isMessageSpeedMenuVisible)
            {
            }
            else if (Menus.isMessageSpeedConfirmationVisible)
            {
            }
            else if (Menus.isReturnToWorldPromptVisible)
            {
            }
            else if (Route.isProgressLogFinished)
            {
            }
            else if (Route.isQuittingGame)
            {
            }
            else if (Menus.isLightningAvailable)
            {
            }
            else if (Menus.isLightningUnavailable)
            {
            }
            else if (Menus.isLightningYesNo)
            {
                VariableYesNoOn();
                descriptionText.text = "Lightning";
            }
            else if (Menus.isLightningShowMeWhere)
            {
                descriptionText.text = "Lightning";
            }
            else if (Menus.isRainAvailable)
            {
            }
            else if (Menus.isRainUnavailable)
            {
            }
            else if (Menus.isRainYesNo)
            {
                VariableYesNoOn();
                descriptionText.text = "Rain";
            }
            else if (Menus.isRainShowMeWhere)
            {
                descriptionText.text = "Rain";
            }
            else if (Menus.isSunAvailable)
            {
            }
            else if (Menus.isSunUnavailable)
            {
            }
            else if (Menus.isSunYesNo)
            {
                VariableYesNoOn();
                descriptionText.text = "Sun";
            }
            else if (Menus.isSunShowMeWhere)
            {
                descriptionText.text = "Sun";
            }
            else if (Menus.isWindAvailable)
            {
            }
            else if (Menus.isWindUnavailable)
            {
            }
            else if (Menus.isWindYesNo)
            {
                VariableYesNoOn();
                descriptionText.text = "Wind";
            }
            else if (Menus.isEarthquakeAvailable)
            {
            }
            else if (Menus.isEarthquakeUnavailable)
            {
            }
            else if (Menus.isEarthquakeYesNo)
            {
                VariableYesNoOn();
                descriptionText.text = "Earthquake";
            }
            else
            {
            }
            if (Menus.isProgressLogConfirmationVisible)
            {
                VariableYesNoOn();
            }
            else if (Menus.isReturnToWorldPromptVisible)
            {
                VariableYesNoOn();
            }
        }
        else if (Towns.townIndex == 7)
        {
            descriptionText.text = Towns.names[Towns.townIndex];
        }
        else if (Route.isListeningToPeople)
        {
            descriptionText.text = Descriptions.letUsListen;
        }
        else if (Menus.isEnterPlayerNameMenuVisible)
        {
        }
        else if (Menus.isPreEnterName)
        {
        }
        else if (Menus.isPostEnterName)
        {
        }
        else if (Route.isMagicUnavailable)
        {
        }
        else if (Route.isTownUninhabited)
        {
        }
        else if (!Quests.is1stTutorialCompleted)
        {
        }
        else if (!Quests.is2ndTutorialCompleted)
        {
        }
        else if (!Quests.is3rdTutorialCompleted)
        {
            Descriptions.messageMenuText = Messages.Quest3[Messages.Index];
        }
        else if (Quests.is4thTutorialReady
                 && !Quests.is4thTutorialCompleted)
        {
        }
        else if (Menus.isReturnToOfferingsDecline)
        {
            descriptionText.text = "Let us\n            Listen";
            Route.TakeAnOfferingScrollDecline();
        }
        else if (Menus.isTakeAnOffering)
        {
            if (Menus.offeringIndex == 0)
            {
                descriptionText.text = "";
                variableBackground.SetActive(true);
                OfferingsGridUpdate();
            }
            else
            {
                descriptionText.text = Menus.offeringDescriptionsInInventory[Menus.K, Menus.L];
                variableBackground.SetActive(true);
                OfferingsGridUpdate();
            }
        }
        else if (Menus.isTakeAnOfferingConfirmation)
        {
            descriptionText.text = "Let us\n            Listen";
            Route.TakeAnOfferingScroll();
            variableBackground.SetActive(true);
            OfferingsGridUpdate();
        }
        else if (Menus.isReturnToOfferings)
        {
            variableBackground.SetActive(true);
            VariableYesNoOn();
            descriptionText.text = "Let us\n            Listen";
        }
        else if (Menus.isLightningSuccess)
        {
        }
        else if (Menus.isLightningFailure)
        {
        }
        else if (Menus.isRainSuccess)
        {
        }
        else if (Menus.isRainFailure)
        {
        }
        else if (Menus.isSunSuccess)
        {
        }
        else if (Menus.isSunFailure)
        {
        }
        else if (Menus.isWindAvailable)
        {
        }
        else if (Menus.isWindFailure)
        {
        }
        else if (Menus.isEarthquakeAvailable)
        {
        }
        else if (Menus.isEarthquakeFailure)
        {
            descriptionText.text = Messages.MiracleFailure[Messages.Index];
        }
        if (Route.isMagicMenuVisible)
        {
            variableBackground.SetActive(true);
        }
        if (Menus.isUseAnOffering)
        {
            descriptionText.text = "Use\n            Offering";
            messageText.text = Messages.UseOffering[Messages.Index].Substring(0, Timers.scrollIndex);
            Route.UseAnOfferingScroll();
            variableBackground.SetActive(true);
            OfferingsGridUpdate();
        }
        if (Route.isTownUnderConstruction)
        {
        }
        if (Menus.isPaused)
        {
            if (!pause.activeSelf)
            {
                pause.SetActive(true);
            }
        }
        else if (!Menus.isPaused)
        {
            if (pause.activeSelf)
            {
                pause.SetActive(false);
            }
        }
    }

    private void OfferingsGridUpdate()
    {
        switch (Menus.K)
        {
            case 0:
                switch (Menus.L)
                {
                    case 0:
                        EventSystem.current.SetSelectedGameObject(item0x0);
                        break;
                    case 1:
                        EventSystem.current.SetSelectedGameObject(item0x1);
                        break;
                    case 2:
                        EventSystem.current.SetSelectedGameObject(item0x2);
                        break;
                    case 3:
                        EventSystem.current.SetSelectedGameObject(item0x3);
                        break;
                }
                break;
            case 1:
                switch (Menus.L)
                {
                    case 0:
                        EventSystem.current.SetSelectedGameObject(item1x0);
                        break;
                    case 1:
                        EventSystem.current.SetSelectedGameObject(item1x1);
                        break;
                    case 2:
                        EventSystem.current.SetSelectedGameObject(item1x2);
                        break;
                    case 3:
                        EventSystem.current.SetSelectedGameObject(item1x3);
                        break;
                }
                break;
        }
    }

    public void ControlPadStart()
    {
        Route.ControlPadStart();
        if (Menus.isStart)
        {
            topTownName.SetActive(true);
            topHealthPoints.SetActive(true);
            topHourglass.SetActive(true);
            topPopulation.SetActive(true);
            topSpellPoints.SetActive(true);
        }
        else if (Messages.IsMessageVisible)
        {
        }
        //Route.ControlPadStart();
    }

    public void ControlPadSelect()
    {
    }

    public void ControlPadB()
    {
        Route.ControlPadB();
        if (Menus.isTownBuilderMenuVisible)
        {
            switch (Menus.I)
            {
                case 0:
                    switch (Menus.J)
                    {
                        case 0:
                            break;
                        case 1:
                            break;
                    }
                    break;
                case 1:
                    switch (Menus.J)
                    {
                        case 0:
                            break;
                        case 1:
                            break;
                    }
                    break;
                case 2:
                    switch (Menus.J)
                    {
                        case 0:
                            break;
                        case 1:
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                    }
                    break;
                case 3:
                    switch (Menus.J)
                    {
                        case 0:
                            break;
                        case 1:
                            break;
                    }
                    break;
                case 4:
                    switch (Menus.J)
                    {
                        case 0:
                            break;
                        case 1:
                            break;
                    }
                    break;
                case 5:
                    switch (Menus.J)
                    {
                        case 0:
                            break;
                        case 1:
                            break;
                    }
                    break;
            }
        }
        if (Menus.isLightningShowMeWhere
            || Menus.isRainShowMeWhere
            || Menus.isSunShowMeWhere)
        {
            VariableYesNoOff();
        }
        else if (Towns.isGraphicsRestartNeeded)
        {
            squares.StartSquares();
            Towns.isGraphicsRestartNeeded = false;
        }
    }

    public void ControlPadY()
    {
        Route.ControlPadY();
    }

    public void ControlPadUp()
    {
        Route.MoveUp();
    }

    public void ControlPadDown()
    {
        Route.MoveDown();
    }

    public void ControlPadLeft()
    {
        Route.MoveLeft();
    }

    public void ControlPadRight()
    {
        Route.MoveRight();
    }

    private void ItemMenuActivate()
    {
        itemName.SetActive(true);
        item0x0.SetActive(true);
        item0x1.SetActive(true);
        item0x2.SetActive(true);
        item0x3.SetActive(true);
        item1x0.SetActive(true);
        item1x1.SetActive(true);
        item1x2.SetActive(true);
        item1x3.SetActive(true);
    }

    private void ItemMenuDeactivate()
    {
        itemName.SetActive(false);
        item0x0.SetActive(false);
        item0x1.SetActive(false);
        item0x2.SetActive(false);
        item0x3.SetActive(false);
        item1x0.SetActive(false);
        item1x1.SetActive(false);
        item1x2.SetActive(false);
        item1x3.SetActive(false);
        Menus.isTakeAnOffering = false;
        Menus.isTakeAnOfferingConfirmation = false;
        Menus.isTakeAnOfferingDecline = false;
        Menus.isUseAnOffering = false;
        Menus.isUseAnOfferingDescription = false;
    }

    private void ItemMenuUpDownLeftRight()
    {
        if (Menus.isTakeAnOffering
            || Menus.isTakeAnOfferingConfirmation
            || Menus.isTakeAnOfferingDecline)
        {
            // TODO: Remember. This is working, but also a bit broken.
            itemName.GetComponentInChildren<TMP_Text>().text = Menus.offeringIconsInInventory[Menus.K, Menus.I];
        }
        if (Menus.isUseAnOffering
            || Menus.isUseAnOfferingDescription)
        {
            itemName.GetComponentInChildren<TMP_Text>().text = Menus.takenDescriptions[Menus.K, Menus.I];
        }
    }

    private void TownBuilderDeactivate()
    {
        townBuilderBackground.SetActive(false);
        townBuilder0x0.SetActive(false);
        townBuilder0x1.SetActive(false);
        townBuilder0x2.SetActive(false);
        townBuilder1x0.SetActive(false);
        townBuilder1x1.SetActive(false);
        townBuilder1x2.SetActive(false);
        townBuilder2x0.SetActive(false);
        townBuilder2x1.SetActive(false);
        townBuilder2x2.SetActive(false);
        townBuilder2x3.SetActive(false);
        townBuilder2x4.SetActive(false);
        townBuilder2x5.SetActive(false);
        townBuilder3x0.SetActive(false);
        townBuilder3x1.SetActive(false);
        townBuilder3x2.SetActive(false);
        townBuilder4x0.SetActive(false);
        townBuilder4x1.SetActive(false);
        townBuilder4x2.SetActive(false);
        townBuilder5x0.SetActive(false);
        townBuilder5x1.SetActive(false);
        townBuilder5x2.SetActive(false);
        VariableYesNoOff();
        ItemMenuDeactivate();
    }
    private void TownBuilderActivateRow()
    {
        switch (Menus.I)
        {
            case 0:
                townBuilderBackground.SetActive(true);
                townBuilder0x0.SetActive(true);
                townBuilder0x1.SetActive(true);
                townBuilder0x2.SetActive(true);
                townBuilder1x0.SetActive(true);
                townBuilder1x1.SetActive(false);
                townBuilder1x2.SetActive(false);
                townBuilder2x0.SetActive(true);
                townBuilder2x1.SetActive(false);
                townBuilder2x2.SetActive(false);
                townBuilder2x3.SetActive(false);
                townBuilder2x4.SetActive(false);
                townBuilder2x5.SetActive(false);
                townBuilder3x0.SetActive(true);
                townBuilder3x1.SetActive(false);
                townBuilder3x2.SetActive(false);
                townBuilder4x0.SetActive(true);
                townBuilder4x1.SetActive(false);
                townBuilder4x2.SetActive(false);
                townBuilder5x0.SetActive(true);
                townBuilder5x1.SetActive(false);
                townBuilder5x2.SetActive(false);
                break;
            case 1:
                townBuilderBackground.SetActive(true);
                townBuilder0x0.SetActive(true);
                townBuilder0x1.SetActive(false);
                townBuilder0x2.SetActive(false);
                townBuilder1x0.SetActive(true);
                townBuilder1x1.SetActive(true);
                townBuilder1x2.SetActive(true);
                townBuilder2x0.SetActive(true);
                townBuilder2x1.SetActive(false);
                townBuilder2x2.SetActive(false);
                townBuilder2x3.SetActive(false);
                townBuilder2x4.SetActive(false);
                townBuilder2x5.SetActive(false);
                townBuilder3x0.SetActive(true);
                townBuilder3x1.SetActive(false);
                townBuilder3x2.SetActive(false);
                townBuilder4x0.SetActive(true);
                townBuilder4x1.SetActive(false);
                townBuilder4x2.SetActive(false);
                townBuilder5x0.SetActive(true);
                townBuilder5x1.SetActive(false);
                townBuilder5x2.SetActive(false);
                break;
            case 2:
                townBuilderBackground.SetActive(true);
                townBuilder0x0.SetActive(true);
                townBuilder0x1.SetActive(false);
                townBuilder0x2.SetActive(false);
                townBuilder1x0.SetActive(true);
                townBuilder1x1.SetActive(false);
                townBuilder1x2.SetActive(false);
                townBuilder2x0.SetActive(true);
                townBuilder2x1.SetActive(true);
                townBuilder2x2.SetActive(true);
                townBuilder2x3.SetActive(true);
                townBuilder2x4.SetActive(true);
                townBuilder2x5.SetActive(true);
                townBuilder3x0.SetActive(true);
                townBuilder3x1.SetActive(false);
                townBuilder3x2.SetActive(false);
                townBuilder4x0.SetActive(true);
                townBuilder4x1.SetActive(false);
                townBuilder4x2.SetActive(false);
                townBuilder5x0.SetActive(true);
                townBuilder5x1.SetActive(false);
                townBuilder5x2.SetActive(false);
                break;
            case 3:
                townBuilderBackground.SetActive(true);
                townBuilder0x0.SetActive(true);
                townBuilder0x1.SetActive(false);
                townBuilder0x2.SetActive(false);
                townBuilder1x0.SetActive(true);
                townBuilder1x1.SetActive(false);
                townBuilder1x2.SetActive(false);
                townBuilder2x0.SetActive(true);
                townBuilder2x1.SetActive(false);
                townBuilder2x2.SetActive(false);
                townBuilder2x3.SetActive(false);
                townBuilder2x4.SetActive(false);
                townBuilder2x5.SetActive(false);
                townBuilder3x0.SetActive(true);
                townBuilder3x1.SetActive(true);
                townBuilder3x2.SetActive(true);
                townBuilder4x0.SetActive(true);
                townBuilder4x1.SetActive(false);
                townBuilder4x2.SetActive(false);
                townBuilder5x0.SetActive(true);
                townBuilder5x1.SetActive(false);
                townBuilder5x2.SetActive(false);
                break;
            case 4:
                townBuilderBackground.SetActive(true);
                townBuilder0x0.SetActive(true);
                townBuilder0x1.SetActive(false);
                townBuilder0x2.SetActive(false);
                townBuilder1x0.SetActive(true);
                townBuilder1x1.SetActive(false);
                townBuilder1x2.SetActive(false);
                townBuilder2x0.SetActive(true);
                townBuilder2x1.SetActive(false);
                townBuilder2x2.SetActive(false);
                townBuilder2x3.SetActive(false);
                townBuilder2x4.SetActive(false);
                townBuilder2x5.SetActive(false);
                townBuilder3x0.SetActive(true);
                townBuilder3x1.SetActive(false);
                townBuilder3x2.SetActive(false);
                townBuilder4x0.SetActive(true);
                townBuilder4x1.SetActive(true);
                townBuilder4x2.SetActive(true);
                townBuilder5x0.SetActive(true);
                townBuilder5x1.SetActive(false);
                townBuilder5x2.SetActive(false);
                break;
            case 5:
                townBuilderBackground.SetActive(true);
                townBuilder0x0.SetActive(true);
                townBuilder0x1.SetActive(false);
                townBuilder0x2.SetActive(false);
                townBuilder1x0.SetActive(true);
                townBuilder1x1.SetActive(false);
                townBuilder1x2.SetActive(false);
                townBuilder2x0.SetActive(true);
                townBuilder2x1.SetActive(false);
                townBuilder2x2.SetActive(false);
                townBuilder2x3.SetActive(false);
                townBuilder2x4.SetActive(false);
                townBuilder2x5.SetActive(false);
                townBuilder3x0.SetActive(true);
                townBuilder3x1.SetActive(false);
                townBuilder3x2.SetActive(false);
                townBuilder4x0.SetActive(true);
                townBuilder4x1.SetActive(false);
                townBuilder4x2.SetActive(false);
                townBuilder5x0.SetActive(true);
                townBuilder5x1.SetActive(true);
                townBuilder5x2.SetActive(true);
                break;
        }
    }

    private void VariableYesNoOff()
    {
        variableBackground.SetActive(false);
        y.SetActive(false);
        yes.SetActive(false);
        x.SetActive(false);
        no.SetActive(false);
    }

    private void VariableYesNoOn()
    {
        variableBackground.SetActive(true);
        y.SetActive(true);
        yes.SetActive(true);
        x.SetActive(true);
        no.SetActive(true);
    }

    private void EnterPlayerNameOn()
    {
        if (!enterPlayerNameBackground.activeSelf)
        {
            enterPlayerNameBackground.SetActive(true);
            enterPlayerNamePleaseEnterMastersName.SetActive(true);
            for (var i = 0; i < playerName.Length; i++)
            {
                playerName[i].SetActive(true);
            }
            for (var i = 0; i < 5; i++)
            {
                for (var j = 0; j < 13; j++)
                {
                    enterPlayerName[i, j].SetActive(true);
                }
            }
        }
    }

    private void EnterPlayerNameOff()
    {
        if (enterPlayerNameBackground.activeSelf)
        {
            enterPlayerNameBackground.SetActive(false);
            enterPlayerNamePleaseEnterMastersName.SetActive(false);
            for (var i = 0; i < playerName.Length; i++)
            {
                playerName[i].SetActive(false);
            }
            for (var i = 0; i < 5; i++)
            {
                for (var j = 0; j < 13; j++)
                {
                    enterPlayerName[i, j].SetActive(false);
                }
            }
        }
    }

    private void SkyPalaceOn()
    {
        skyPalaceBackground.SetActive(true);
        skyPalace0x0.SetActive(true);
        skyPalace0x1.SetActive(true);
        skyPalace0x2.SetActive(true);
        skyPalace1x0.SetActive(true);
        skyPalace1x1.SetActive(true);
        skyPalace1x2.SetActive(true);
        skyPalace2x0.SetActive(true);
        skyPalace2x1.SetActive(true);
        skyPalace2x2.SetActive(true);
        skyPalace3x0.SetActive(true);
        skyPalace3x1.SetActive(true);
        skyPalace3x2.SetActive(true);
    }
    private void SkyPalaceOff()
    {
        variableBackground.SetActive(false);
        skyPalaceBackground.SetActive(false);
        skyPalace0x0.SetActive(false);
        skyPalace0x1.SetActive(false);
        skyPalace0x2.SetActive(false);
        skyPalace1x0.SetActive(false);
        skyPalace1x1.SetActive(false);
        skyPalace1x2.SetActive(false);
        skyPalace2x0.SetActive(false);
        skyPalace2x1.SetActive(false);
        skyPalace2x2.SetActive(false);
        skyPalace3x0.SetActive(false);
        skyPalace3x1.SetActive(false);
        skyPalace3x2.SetActive(false);
    }
    private void SkyPalaceActivateRow()
    {
        switch (Menus.I)
        {
            case 0:
                skyPalaceBackground.SetActive(true);
                skyPalace0x0.SetActive(true);
                skyPalace0x1.SetActive(true);
                skyPalace0x2.SetActive(true);
                skyPalace1x0.SetActive(true);
                skyPalace1x1.SetActive(false);
                skyPalace1x2.SetActive(false);
                skyPalace2x0.SetActive(true);
                skyPalace2x1.SetActive(false);
                skyPalace2x2.SetActive(false);
                skyPalace3x0.SetActive(true);
                skyPalace3x1.SetActive(false);
                skyPalace3x2.SetActive(false);
                break;
            case 1:
                skyPalaceBackground.SetActive(true);
                skyPalace0x0.SetActive(true);
                skyPalace0x1.SetActive(false);
                skyPalace0x2.SetActive(false);
                skyPalace1x0.SetActive(true);
                skyPalace1x1.SetActive(true);
                skyPalace1x2.SetActive(true);
                skyPalace2x0.SetActive(true);
                skyPalace2x1.SetActive(false);
                skyPalace2x2.SetActive(false);
                skyPalace3x0.SetActive(true);
                skyPalace3x1.SetActive(false);
                skyPalace3x2.SetActive(false);
                break;
            case 2:
                skyPalaceBackground.SetActive(true);
                skyPalace0x0.SetActive(true);
                skyPalace0x1.SetActive(false);
                skyPalace0x2.SetActive(false);
                skyPalace1x0.SetActive(true);
                skyPalace1x1.SetActive(false);
                skyPalace1x2.SetActive(false);
                skyPalace2x0.SetActive(true);
                skyPalace2x1.SetActive(true);
                skyPalace2x2.SetActive(true);
                skyPalace3x0.SetActive(true);
                skyPalace3x1.SetActive(false);
                skyPalace3x2.SetActive(false);
                break;
            case 3:
                skyPalaceBackground.SetActive(true);
                skyPalace0x0.SetActive(true);
                skyPalace0x1.SetActive(false);
                skyPalace0x2.SetActive(false);
                skyPalace1x0.SetActive(true);
                skyPalace1x1.SetActive(false);
                skyPalace1x2.SetActive(false);
                skyPalace2x0.SetActive(true);
                skyPalace2x1.SetActive(false);
                skyPalace2x2.SetActive(false);
                skyPalace3x0.SetActive(true);
                skyPalace3x1.SetActive(true);
                skyPalace3x2.SetActive(true);
                break;
        }
    }
}
