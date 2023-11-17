/*
 * Title: Squares file.
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

public class Squares : MonoBehaviour
{
    //private float size = 0.1f;

    private Square[,,] allSquares = new Square[7, Towns.SIZE, Towns.SIZE];
    private bool isSquaresStarted;

    private GameObject player;
    private GameObject enemy0;
    private GameObject enemy1;
    private GameObject enemy2;
    private GameObject enemy3;

    private Square playerSquare;
    private Square enemySquare0;
    private Square enemySquare1;
    private Square enemySquare2;
    private Square enemySquare3;

    private string playerDirection;

    //private GameObject arrow;

    private GameObject referenceSquare;

    [SerializeField]
    private MainManager mainManager;

    public GameObject SquarePrefab;

    public Transform yellowBox;
    public Transform grayBox;

    // Squigglevision Blocks.
    private bool isGrassBlocked2;
    private bool isFireBlocked2;
    private bool isWaterBlocked2;
    private bool isHorsePastureBlocked2;

    //public float Size { get { return size; } set { size = value; } }

    [SerializeField]
    private Transform lightning;

    [SerializeField]
    private Animator lightningAnimator;

    [SerializeField]
    private Transform rain;

    [SerializeField]
    private Animator rainAnimator;

    [SerializeField]
    private Transform sun;

    [SerializeField]
    private Animator sunAnimator;

    [SerializeField]
    private Transform wind;

    [SerializeField]
    private Animator windAnimator;

    [SerializeField]
    private Transform earthquake;

    [SerializeField]
    private Animator earthquakeAnimator;


    public void StartSquares()
    {
        player = Instantiate(SquarePrefab);
        player.AddComponent<PoorManAnimation>();
        player.GetComponent<PoorManAnimation>().StartPlayer();
        player.name = "Player";
        player.transform.localScale = new Vector3(
            MainManager.SIZE,
            MainManager.SIZE,
            MainManager.SIZE);
        playerSquare = player.GetComponent<Square>();
        playerSquare.SetRenderersColor(LookupTables.EnemiesAndPlayerColor[(int)LookupTables.EnemiesAndPlayer.Player]);
        //playerSquare.TurnRenderersOff();
        playerSquare.TopBottom.SetActive(true);
        playerSquare.TopFrontMiddle.SetActive(true);
        GeneralResize(playerSquare);
        playerSquare.ApplyBird();
        playerSquare.TurnHorsesOn();
        enemy0 = Instantiate(SquarePrefab);
        enemy0.AddComponent<PoorManAnimation>();
        enemy0.GetComponent<PoorManAnimation>().StartMonster(0);
        enemy0.name = "Enemy 0";
        enemy0.transform.localScale = new Vector3(
            MainManager.SIZE,
            MainManager.SIZE,
            MainManager.SIZE);
        enemySquare0 = enemy0.GetComponent<Square>();
        //enemySquare0.TurnRenderersOff();
        enemySquare0.FrontMiddle.SetActive(true);
        //GeneralResize(enemySquare0);
        enemySquare0.ApplyNapperBat();
        enemy1 = Instantiate(SquarePrefab);
        enemy1.AddComponent<PoorManAnimation>();
        enemy1.GetComponent<PoorManAnimation>().StartMonster(1);
        enemy1.name = "Enemy 1";
        enemy1.transform.localScale = new Vector3(
            MainManager.SIZE,
            MainManager.SIZE,
            MainManager.SIZE);
        enemySquare1 = enemy1.GetComponent<Square>();
        //enemySquare1.TurnRenderersOff();
        enemySquare1.FrontMiddle.SetActive(true);
        //GeneralResize(enemySquare1);
        enemySquare1.ApplyNapperBat();
        enemy2 = Instantiate(SquarePrefab);
        enemy2.AddComponent<PoorManAnimation>();
        enemy2.GetComponent<PoorManAnimation>().StartMonster(2);
        enemy2.name = "Enemy 2";
        enemy2.transform.localScale = new Vector3(
            MainManager.SIZE,
            MainManager.SIZE,
            MainManager.SIZE);
        enemySquare2 = enemy2.GetComponent<Square>();
        //enemySquare2.TurnRenderersOff();
        enemySquare2.FrontMiddle.SetActive(true);
        //GeneralResize(enemySquare2);
        enemySquare2.ApplyNapperBat();
        enemy3 = Instantiate(SquarePrefab);
        enemy3.AddComponent<PoorManAnimation>();
        enemy3.GetComponent<PoorManAnimation>().StartMonster(3);
        enemy3.name = "Enemy 3";
        enemy3.transform.localScale = new Vector3(
            MainManager.SIZE,
            MainManager.SIZE,
            MainManager.SIZE);
        enemySquare3 = enemy3.GetComponent<Square>();
        //enemySquare3.TurnRenderersOff();
        enemySquare3.FrontMiddle.SetActive(true);
        //GeneralResize(enemySquare3);
        enemySquare3.ApplyBlueDemon();
        referenceSquare = Instantiate(SquarePrefab);
        referenceSquare.name = "Reference Square";
        referenceSquare.transform.parent = transform.parent;
        referenceSquare.SetActive(false);
        for (var layer = 0; layer < Towns.LayersName.Length; layer++)
        {
            for (var column = 0; column < Towns.SIZE; column++)
            {
                for (var row = 0; row < Towns.SIZE; row++)
                {
                    var index = Towns.town[layer, row, column];
                    GameObject squareGameObject = Instantiate(SquarePrefab);
                    Square squareScript = squareGameObject.GetComponent<Square>();
                    squareGameObject.name = new StringBuilder()
                        .Append("Default Square (")
                        .Append(Towns.LayersName[layer])
                        .Append(", ")
                        .Append(column)
                        .Append(", ")
                        .Append(row)
                        .Append(")")
                        .ToString();
                    squareGameObject.transform.parent = transform.parent;
                    squareGameObject.transform.position = new Vector3(
                        MainManager.SIZE * (referenceSquare.transform.position.x + column),
                        MainManager.SIZE * (referenceSquare.transform.position.y + layer - MainManager.SIZE),
                        MainManager.SIZE * (referenceSquare.transform.position.z - row));
                    squareGameObject.transform.localScale = new Vector3(
                        MainManager.SIZE * referenceSquare.transform.localScale.x,
                        MainManager.SIZE * referenceSquare.transform.localScale.y,
                        MainManager.SIZE * referenceSquare.transform.localScale.z);
                    switch (layer)
                    {
                        case (int)Towns.Layers.Land:
                            //squareScript.TurnRenderersOff();
                            switch (index)
                            {
                                //case (int)LookupTables.Land.Grass:
                                    //squareScript.Filler.enabled = true;
                                    //squareScript.TopFrontMiddle.enabled = true;
                                    //squareScript.SetRenderersColor(LookupTables.LandColor[(int)LookupTables.Land.Grass]);
                                    //break;
                                case (int)LookupTables.Land.Water:
                                    squareScript.TopTop.SetActive(true);
                                    squareScript.Filler.enabled = true;
                                    squareScript.RandomWater();
                                    //squareScript.TopTop.material.color = LookupTables.LandColor[(int)LookupTables.Land.Water];
                                    break;
                                case (int)LookupTables.Land.Beach:
                                    squareScript.TopTop.SetActive(true);
                                    squareScript.Filler.enabled = true;
                                    squareScript.RandomBeach();
                                    break;
                                case (int)LookupTables.Land.Cliff:
                                    squareScript.Filler.enabled = true;
                                    break;
                                case (int)LookupTables.Land.PalmTree:
                                    squareScript.FrontMiddle.SetActive(true);
                                    squareScript.Filler.enabled = true;
                                    GeneralResize(squareScript);
                                    squareScript.ApplyPalmTree();
                                    break;
                                //case (int)LookupTables.Land.Bush:
                                    //squareScript.FrontMiddle.enabled = true;
                                    //squareScript.Filler.enabled = true;
                                    //GeneralResize(squareScript);
                                    //break;
                                case (int)LookupTables.Land.Rock:
                                    squareScript.FrontMiddle.SetActive(true);
                                    squareScript.Filler.enabled = true;
                                    GeneralResize(squareScript);
                                    squareScript.ApplyRock();
                                    break;
                                case (int)LookupTables.Land.Mountain:
                                    squareScript.TopFrontMiddle.SetActive(true);
                                    squareScript.Filler.enabled = true;
                                    GeneralResize(squareScript);
                                    squareScript.RandomMountain();
                                    break;
                                case (int)LookupTables.Land.Tree:
                                    squareScript.TopFrontMiddle.SetActive(true);
                                    squareScript.Filler.enabled = true;
                                    squareScript.TopTop.SetActive(true);
                                    //squareScript.TopFrontMiddle.transform.localPosition = new Vector3(0.5f, 2.0f, 0.0f);
                                    //squareScript.TopFrontMiddle.transform.localScale = new Vector3(2.0f, 2.0f, 1.0f);
                                    //GeneralResize(squareScript);
                                    squareScript.ApplyTree();
                                    squareScript.RandomTreeBed();
                                    break;
                            }
                            break;
                        case (int)Towns.Layers.LandModifier:
                            switch (index)
                            {
                                case (int)LookupTables.LandModifier.None:
                                    break;
                                case (int)LookupTables.LandModifier.Burned:
                                    break;
                                case (int)LookupTables.LandModifier.Dry:
                                    break;
                                case (int)LookupTables.LandModifier.Snow:
                                    break;
                                case (int)LookupTables.LandModifier.Swamp:
                                    break;
                            }
                            break;
                        case (int)Towns.Layers.Building:
                            //squareScript.TurnRenderersOff();
                            //squareScript.TopFrontMiddle.SetActive(true);
                            break;
                    }
                    allSquares[layer, column, row] = squareScript;
                }
            }
        }
        for (var layer = 0; layer < Towns.LayersName.Length; layer++)
        {
            for (var column = 0; column < Towns.SIZE; column++)
            {
                for (var row = 0; row < Towns.SIZE; row++)
                {
                    var index = Towns.town[layer, row, column];
                    var color = Color.white;
                    var position = new Vector3(
                       referenceSquare.transform.position.x + (MainManager.SIZE * column),
                       -MainManager.SIZE,
                       referenceSquare.transform.position.z - (MainManager.SIZE * row));
                    var scale = Vector3.one;
                    switch (layer)
                    {
                        case (int)Towns.Layers.Land:
                            color = LookupTables.LandColor[index];
                            switch (index)
                            {
                                case (int)LookupTables.Land.Water:
                                    position.y = -0.5f * MainManager.SIZE;
                                    break;
                                case (int)LookupTables.Land.Beach:
                                    position.y = -0.25f * MainManager.SIZE;
                                    break;
                                //case (int)LookupTables.Land.Grass:
                                    //position.y = 0.0f * MainManager.SIZE;
                                    //break;
                                case (int)LookupTables.Land.Cliff:
                                    scale.y = 2.0f;
                                    position.y = 0.75f * MainManager.SIZE;
                                    break;
                                case (int)LookupTables.Land.Tree:
                                    scale.y = 1.0f;
                                    position.y = 0.1f * MainManager.SIZE;
                                    break;
                                case (int)LookupTables.Land.PalmTree:
                                    position.y = 0.0f * MainManager.SIZE;
                                    break;
                                case (int)LookupTables.Land.Mountain:
                                    position.y = 0.5f * MainManager.SIZE;
                                    break;
                                case (int)LookupTables.Land.Bush:
                                case (int)LookupTables.Land.Rock:
                                    position.y = 0.0f * MainManager.SIZE;
                                    break;
                            }
                            break;
                        case (int)Towns.Layers.LandModifier:
                            color = LookupTables.LandModifierColor[index];
                            position.y = 2.0f * MainManager.SIZE;
                            break;
                        case (int)Towns.Layers.People:
                            color = LookupTables.PeopleColor[index];
                            position.y = 1.0f * MainManager.SIZE;
                            break;
                        case (int)Towns.Layers.Building:
                            color = Color.gray;
                            position.y = 0.0f * MainManager.SIZE;
                            break;
                        case (int)Towns.Layers.BuildingModifier:
                            color = LookupTables.BuildingModifierColor[index];
                            switch (index)
                            {
                                case (int)LookupTables.BuildingModifier.None:
                                case (int)LookupTables.BuildingModifier.Fire:
                                case (int)LookupTables.BuildingModifier.Fight:
                                case (int)LookupTables.BuildingModifier.Sad:
                                    break;
                            }
                            break;
                        case (int)Towns.Layers.EnemiesAndPlayer:
                            color = Color.green;
                            position.y = 3.0f;
                            break;
                    }
                    allSquares[layer, column, row].Filler.material.color = color;
                    //allSquares[layer, column, row].TopTop.material.color = color;
                    //allSquares[layer, column, row].TopMiddle.material.color = color;
                    //allSquares[layer, column, row].TopBottom.material.color = color;
                    //allSquares[layer, column, row].Bottom.material.color = color;
                    //allSquares[layer, column, row].Left.material.color = color;
                    //allSquares[layer, column, row].Right.material.color = color;
                    allSquares[layer, column, row].FrontFront.material.color = color;
                    //allSquares[layer, column, row].FrontMiddle.material.color = color;
                    allSquares[layer, column, row].FrontBack.material.color = color;
                    //allSquares[layer, column, row].Back.material.color = color;
                    //allSquares[layer, column, row].TopFrontMiddle.material.color = color;
                    allSquares[layer, column, row].transform.position = position;
                    allSquares[layer, column, row].transform.localScale = scale;
                    if (Towns.town[layer, row, column] != 0)
                    {
                    }
                    else
                    {
                        allSquares[layer, column, row].gameObject.SetActive(false);
                    }
                }
            }
        }
        isSquaresStarted = true;
    }

    private void Update()
    {
        if (!isSquaresStarted)
        {
            return;
        }
        playerSquare.TopFrontMiddle.transform.rotation = Quaternion.identity;
        AllTiles();
        if (Timers.isBoxYellowVisible)
        {
            if (!yellowBox.gameObject.activeSelf)
            {
                yellowBox.gameObject.SetActive(true);
            }
            if (Route.isRecordingYellowBoxPath)
            {
                yellowBox.position = new Vector3(
                    (1.5f + (Player.yellowBoxI * 4.0f)) * MainManager.SIZE,
                    1.0f * MainManager.SIZE,
                    (-(1.5f + (Player.yellowBoxJ * 4.0f))) * MainManager.SIZE);
            }
            else
            {
                yellowBox.position = new Vector3(
                    (1.5f + (Route.yellowBoxPath[Route.yellowBoxPathI].x * 4.0f)) * MainManager.SIZE,
                    1.0f * MainManager.SIZE,
                    (-(1.5f + (Route.yellowBoxPath[Route.yellowBoxPathI].y * 4.0f))) * MainManager.SIZE);
            }
        }
        else
        {
            if (yellowBox.gameObject.activeSelf)
            {
                yellowBox.gameObject.SetActive(false);
            }
        }
        if (Route.isGrayBoxVisible)
        {
            if (!grayBox.gameObject.activeSelf)
            {
                grayBox.gameObject.SetActive(true);
            }
            grayBox.position = new Vector3(
                (1.5f + (Player.grayBoxJ * 4.0f)) * MainManager.SIZE,
                1.0f * MainManager.SIZE,
                (-(1.5f + (Player.grayBoxI * 4.0f))) * MainManager.SIZE);
        }
        else
        {
            if (grayBox.gameObject.activeSelf)
            {
                grayBox.gameObject.SetActive(false);
            }
        }
        if (Timers.isAngelBobbedLeft)
        {
            playerSquare.TopFrontMiddle.transform.localPosition = 
                new Vector3(0.00f, 0.50f, 0.02f);
        }
        else
        {
            playerSquare.TopFrontMiddle.transform.localPosition = 
                new Vector3(0.00f, 0.50f, -0.02f);
        }
        // TODO: Remember that this is marked during AllTiles, but not actually blocked until the end.
        if (isGrassBlocked2)
        {
            Timers.isGrassBlocked = true;
        }
        if (isFireBlocked2)
        {
            Timers.isFireBlocked = true;
        }
        if (isWaterBlocked2)
        {
            Timers.isWaterBlocked = true;
        }
        if (isHorsePastureBlocked2)
        {
            Timers.isHorsePastureBlocked = true;
        }
        if (Miracles.lightningTimesSinceStartOfMiracle != -1.0f)
        {
            if (!Miracles.IsAnimationBlocked)
            {
                lightning.transform.position = new Vector3(
                    Player.grayBoxJ * Miracles.CLUSTER_SIZE * MainManager.SIZE
                    + (MainManager.SIZE * 1.5f),
                    0.4f,
                    -Player.grayBoxI * Miracles.CLUSTER_SIZE * MainManager.SIZE
                    - (MainManager.SIZE * 1.5f));
                lightningAnimator.Play("Base Layer.Lightning Animation", 0, 0.0f);
                Miracles.IsAnimationBlocked = true;
            }
        }
        else if (Miracles.rainTimeSinceStartOfMiracle != -1.0f)
        {
            if (!Miracles.IsAnimationBlocked)
            {
                rain.transform.position = new Vector3(
                    Player.grayBoxJ * Miracles.CLUSTER_SIZE * MainManager.SIZE
                    + (MainManager.SIZE * 1.5f),
                    0.3f,
                    -Player.grayBoxI * Miracles.CLUSTER_SIZE * MainManager.SIZE
                    - (MainManager.SIZE * 1.5f));
                rainAnimator.Play("Base Layer.Rain Animation", 0, 0.0f);
                Miracles.IsAnimationBlocked = true;
            }
        }
        else if (Miracles.sunlightTimeSinceStartOfMiracle != -1.0f)
        {
            if (!Miracles.IsAnimationBlocked)
            {
                sunAnimator.Play("Base Layer.Sun Animation", 0, 0.0f);
                Miracles.IsAnimationBlocked = true;
            }
        }
        else if (Miracles.windTimeSinceStartOfMiracle != -1.0f)
        {
            if (!Miracles.IsAnimationBlocked)
            {
                windAnimator.Play("Base Layer.Wind Animation", 0, 0.0f);
                Miracles.IsAnimationBlocked = true;
            }
        }
        else if (Miracles.earthquakeTimeSinceStartOfMiracle != -1.0f)
        {
            if (!Miracles.IsAnimationBlocked)
            {
                earthquakeAnimator.Play("Base Layer.Earthquake Animation", 0, 0.0f);
                Miracles.IsAnimationBlocked = true;
            }
        }
        else
        {
        }
    }

    private void GeneralResize(Square square)
    {
        square.TopFrontMiddle.transform.localPosition = new Vector3(0.0f, 1.5f, 0.0f);
        square.TopFrontMiddle.transform.localScale = new Vector3(2.0f, 2.0f, 1.0f);
    }

    private void AllTiles()
    {
        for (var column = 0; column < Towns.SIZE; column++)
        {
            for (var row = 0; row < Towns.SIZE; row++)
            {
                for (var layer = 0; layer < Towns.LayersName.Length; layer++)
                {
                    var index = Towns.town[layer, row, column];
                    var square = allSquares[layer, column, row];
                    if (layer == (int)Towns.Layers.Land)
                    {
                        switch (index)
                        {
                            case (int)LookupTables.Land.None:
                                if (!square.Filler.material.color.Equals(
                                        LookupTables.LandColor[(int)LookupTables.Land.None]))
                                {
                                    //square.TurnRenderersOff();
                                    square.Filler.enabled = true;
                                }
                                break;
                            case (int)LookupTables.Land.Grass:
                                if (Timers.isGrassBlocked)
                                {
                                }
                                else
                                {
                                    //square.TurnRenderersOff();
                                    square.Filler.enabled = true;
                                    square.TopFrontMiddle.SetActive(true);
                                    allSquares[layer, column, row].transform.position = new Vector3(
                                        referenceSquare.transform.position.x + (MainManager.SIZE * column),
                                        0.0f * MainManager.SIZE,
                                        referenceSquare.transform.position.z - (MainManager.SIZE * row));
                                    square.TopFrontMiddle.transform.localPosition = new Vector3(
                                        0.0f,
                                        1.0f,
                                        0.0f);
                                    square.TopFrontMiddle.transform.localScale = new Vector3(0.95f, 0.95f, 0.95f);
                                    square.SetRenderersColor(LookupTables.LandColor[(int)LookupTables.Land.Grass]);
                                    square.RandomGrass();
                                    isGrassBlocked2 = true;
                                }
                                break;
                            case (int)LookupTables.Land.PalmTree:
                                square.Filler.enabled = true;
                                square.TopFrontMiddle.SetActive(true);
                                square.SetRenderersColor(LookupTables.LandColor[(int)LookupTables.Land.PalmTree]);
                                square.ApplyPalmTree();
                                break;
                            case (int)LookupTables.Land.Beach:
                                if (Timers.isWaterBlocked)
                                {
                                }
                                else
                                {
                                    square.gameObject.transform.localPosition = new Vector3(
                                        square.gameObject.transform.localPosition.x,
                                        Random.Range(-0.5f, -0.45f),
                                        square.gameObject.transform.localPosition.z);
                                    square.RandomBeach();
                                    //isWaterBlocked2 = true;
                                }
                                break;
                            case (int)LookupTables.Land.Water:
                                if (Timers.isWaterBlocked)
                                {
                                }
                                else
                                {
                                    square.gameObject.transform.localPosition = new Vector3(
                                        square.gameObject.transform.localPosition.x, 
                                        Random.Range(-0.5f, -0.45f),
                                        square.gameObject.transform.localPosition.z);
                                    square.RandomWater();
                                    isWaterBlocked2 = true;
                                }
                                break;
                            case (int)LookupTables.Land.Bush:
                                // TODO: Remember that this is a copy of the grass block.
                                if (Timers.isGrassBlocked)
                                {
                                }
                                else
                                {
                                    //square.TurnRenderersOff();
                                    square.Filler.enabled = true;
                                    square.TopFrontMiddle.SetActive(true);
                                    square.TopFrontMiddle.transform.localPosition = new Vector3(0.0f, 1.0f, 0.0f);
                                    square.TopFrontMiddle.transform.localScale = new Vector3(0.95f, 0.95f, 0.95f);
                                    //square.SetRenderersColor(LookupTables.LandColor[(int)LookupTables.Land.Grass]);
                                    square.RandomGrass();
                                    isGrassBlocked2 = true;
                                }
                                square.Filler.enabled = true;
                                square.FrontMiddle.SetActive(true);
                                square.FrontMiddle.transform.localPosition = new Vector3(0.0f, 1.5f, 0.1f);
                                square.FrontMiddle.transform.localScale = new Vector3(1.95f, 1.95f, 0.95f);
                                square.SetRenderersColor(LookupTables.LandColor[(int)LookupTables.Land.Bush]);
                                square.ApplyBush();
                                break;
                        }
                    }
                    if (layer == (int)Towns.Layers.LandModifier)
                    {
                        switch (index)
                        {
                            case (int)LookupTables.LandModifier.None:
                                //square.TurnRenderersOff();
                                break;
                            case (int)LookupTables.LandModifier.Burned:
                                square.gameObject.SetActive(true);
                                square.TopBottom.SetActive(true);
                                square.TopBottom.transform.localPosition = new Vector3(
                                    0.0f,
                                    -1.4f,
                                    0.0f);
                                square.ApplyBurned();
                                break;
                            case (int)LookupTables.LandModifier.Dry:
                                //square.TurnRenderersOff();
                                square.TopMiddle.SetActive(true);
                                square.TopMiddle.transform.localPosition = new Vector3(
                                    0.0f,
                                    -1.4f,
                                    0.0f);
                                square.TopMiddle.transform.localScale = new Vector3(
                                    1.05f,
                                    1.05f,
                                    1.0f);
                                // TODO: Set material here when art is ready.
                                break;
                            case (int)LookupTables.LandModifier.Snow:
                                //square.TurnRenderersOff();
                                square.TopMiddle.SetActive(true);
                                square.TopMiddle.transform.localPosition = new Vector3(
                                    0.0f,
                                    -1.4f,
                                    0.0f);
                                square.TopMiddle.transform.localScale = new Vector3(
                                    1.05f,
                                    1.05f,
                                    1.0f);
                                // TODO: Set material here when art is ready.
                                break;
                            case (int)LookupTables.LandModifier.Swamp:
                                //square.TurnRenderersOff();
                                square.TopMiddle.SetActive(true);
                                square.TopMiddle.transform.localPosition = new Vector3(
                                    0.0f,
                                    -1.4f,
                                    0.0f);
                                square.TopMiddle.transform.localScale = new Vector3(
                                    1.05f,
                                    1.05f,
                                    1.0f);
                                square.ApplySwamp();
                                break;
                        }
                    }
                    if (layer == (int)Towns.Layers.People)
                    {
                        switch (index)
                        {
                            case (int)LookupTables.People.None:
                                if (square.gameObject.activeSelf)
                                {
                                }
                                break;
                            case (int)LookupTables.People.One:
                                //square.TurnRenderersOff();
                                square.FrontMiddle.SetActive(true);
                                break;
                            case (int)LookupTables.People.Three:
                                //square.TurnRenderersOff();
                                square.FrontMiddle.SetActive(true);
                                break;
                            case (int)LookupTables.People.Five:
                                //square.TurnRenderersOff();
                                square.FrontFront.enabled = true;
                                square.FrontMiddle.SetActive(true);
                                break;
                            case (int)LookupTables.People.Seven:
                                //square.TurnRenderersOff();
                                square.FrontFront.enabled = true;
                                square.FrontMiddle.SetActive(true);
                                square.FrontBack.enabled = true;
                                break;
                            case (int)LookupTables.People.Ten:
                                //square.TurnRenderersOff();
                                square.FrontMiddle.SetActive(true);
                                break;
                        }
                    }
                    if (layer == (int)Towns.Layers.Building)
                    {
                        //square.TurnRenderersOff();
                        switch (index)
                        {

                            case (int)LookupTables.Building.None:
                                break;
                            case (int)LookupTables.Building.LevelOneHouse:
                                break;
                            case (int)LookupTables.Building.LevelTwoHouse:
                                break;
                            case (int)LookupTables.Building.LevelThreeHouse:
                                break;
                            case (int)LookupTables.Building.CornField:
                                break;
                            case (int)LookupTables.Building.WheatField:
                                break;
                            case (int)LookupTables.Building.Pony:
                                square.TopFrontMiddle.SetActive(true);
                                if (Timers.isHorsePastureBlocked)
                                {
                                }
                                else
                                {
                                    GeneralResize(square);
                                    square.RandomPony();
                                    isHorsePastureBlocked2 = true;
                                }
                                break;
                            case (int)LookupTables.Building.Corgi:
                                square.TopFrontMiddle.SetActive(true);
                                if (Timers.isHorsePastureBlocked)
                                {
                                }
                                else
                                {
                                    GeneralResize(square);
                                    square.RandomCorgi();
                                    //isHorsePastureBlocked2 = true;
                                }
                                break;
                            case (int)LookupTables.Building.Sheep:
                                square.TopFrontMiddle.SetActive(true);
                                if (Timers.isHorsePastureBlocked)
                                {
                                }
                                else
                                {
                                    GeneralResize(square);
                                    square.RandomSheep();
                                    //isHorsePastureBlocked2 = true;
                                }
                                break;
                            case (int)LookupTables.Building.Factory:
                                break;
                            case (int)LookupTables.Building.Bridge:
                                break;
                            case (int)LookupTables.Building.Windmill:
                                break;
                            case (int)LookupTables.Building.DenNapperBatLeft:
                                break;
                            case (int)LookupTables.Building.DenNapperBatRight:
                                break;
                            case (int)LookupTables.Building.TownHall:
                                break;
                            case (int)LookupTables.Building.DenBlueDemonLeft:
                                break;
                            case (int)LookupTables.Building.DenBlueDemonRight:
                                break;
                            case (int)LookupTables.Building.DenRedDevilLeft:
                                break;
                            case (int)LookupTables.Building.DenRedDevilRight:
                                break;
                            case (int)LookupTables.Building.DenSkeletonHeadLeft:
                                break;
                            case (int)LookupTables.Building.DenSkeletonHeadRight:
                                break;
                            case (int)LookupTables.Building.TownHallUpperLeft:
                                break;
                            case (int)LookupTables.Building.TownHallUpperRight:
                                break;
                            case (int)LookupTables.Building.TownHallLowerLeft:
                                break;
                            case (int)LookupTables.Building.TownHallLowerRight:
                                break;
                            case (int)LookupTables.Building.Road:
                            case (int)LookupTables.Building.ConnectorAllWay:
                            case (int)LookupTables.Building.ConnectorUp:
                            case (int)LookupTables.Building.ConnectorDown:
                            case (int)LookupTables.Building.ConnectorLeft:
                            case (int)LookupTables.Building.ConnectorRight:
                            case (int)LookupTables.Building.CornerUpperLeft:
                            case (int)LookupTables.Building.CornerUpperRight:
                            case (int)LookupTables.Building.CornerLowerLeft:
                            case (int)LookupTables.Building.CornerLowerRight:
                            case (int)LookupTables.Building.RoadHorizontal:
                            case (int)LookupTables.Building.RoadVertical:
                                square.Filler.enabled = true;
                                break;
                        }
                    }
                    if (layer == (int)Towns.Layers.BuildingModifier)
                    {
                        switch (index)
                        {
                            case (int)LookupTables.BuildingModifier.None:
                                break;
                            case (int)LookupTables.BuildingModifier.Fire:
                                if (Miracles.lightningTimesSinceStartOfMiracle != 1.0f)
                                {
                                    square.Filler.enabled = true;
                                    square.TopFrontMiddle.SetActive(true);
                                    square.TopFrontMiddle.transform.position = new Vector3(
                                        square.transform.position.x - 0.01f,
                                        allSquares[(int)Towns.Layers.Land, column, row].transform.position.y
                                        + allSquares[(int)Towns.Layers.Land, column, row].transform.localScale.y * 0.2f,
                                        allSquares[(int)Towns.Layers.Land, column, row].transform.position.z);
                                    square.SetRenderersColor(LookupTables.BuildingModifierColor[(int)LookupTables.BuildingModifier.Fire]);
                                    //square.TopFrontMiddle.material = square.TopFrontMiddle.material;
                                    if (Timers.isFireBlocked)
                                    {
                                    }
                                    else
                                    {
                                        square.GetComponent<Square>().RandomFire();
                                        isFireBlocked2 = true;
                                    }
                                }
                                else
                                {
                                }
                                break;
                            case (int)LookupTables.BuildingModifier.Sad:
                                break;
                            case (int)LookupTables.BuildingModifier.Fight:
                                break;
                        }
                    }
                    if (layer == (int)Towns.Layers.EnemiesAndPlayer)
                    {
                        if (Towns.town[layer, row, column] == 0
                            && square.gameObject.activeSelf)
                        {
                            square.gameObject.SetActive(false);
                            continue;
                        }
                        // TODO: Fill this out for each case, then remove.
                        //square.TurnRenderersOff();
                        //square.Filler.enabled = true;
                        
                        //square.gameObject.SetActive(true);
                        switch (index)
                        {
                            case (int)LookupTables.EnemiesAndPlayer.Player:
                                playerDirection = Towns.directionText;
                                switch (playerDirection)
                                {
                                    case "^": // Up.
                                        player.transform.eulerAngles = new Vector3(0.0f, 90.0f, 0.0f);
                                        break;
                                    case "v": // Down.
                                        player.transform.eulerAngles = new Vector3(0.0f, 270.0f, 0.0f);
                                        break;
                                    case "<": // Left.
                                        player.transform.eulerAngles = new Vector3(0.0f, 0.0f, 0.0f);
                                        break;
                                    case ">": // Right.
                                        player.transform.eulerAngles = new Vector3(0.0f, 180.0f, 0.0f);
                                        break;
                                }
                                break;
                            case (int)LookupTables.EnemiesAndPlayer.NapperBat:
                                //square.gameObject.SetActive(true);
                                //square.Filler.enabled = true;
                                break;
                            case (int)LookupTables.EnemiesAndPlayer.BlueDemon:
                                //square.gameObject.SetActive(true);
                                //square.Filler.enabled = true;
                                break;
                            case (int)LookupTables.EnemiesAndPlayer.RedDevil:
                                //square.gameObject.SetActive(true);
                                //square.Filler.enabled = true;
                                break;
                            case (int)LookupTables.EnemiesAndPlayer.SkeletonHead:
                                //square.gameObject.SetActive(true);
                                //square.Filler.enabled = true;
                                break;
                            case (int)LookupTables.EnemiesAndPlayer.ArrowUp:
                                square.Filler.enabled = false;
                                square.FrontMiddle.SetActive(true);
                                square.ApplyArrowUp();
                                square.gameObject.SetActive(true);
                                square.transform.position = new Vector3(
                                    column * MainManager.SIZE,
                                    3.0f * MainManager.SIZE,
                                    -row * MainManager.SIZE);
                                square.SetRenderersColor(LookupTables.EnemiesAndPlayerColor[index]);
                                break;
                            case (int)LookupTables.EnemiesAndPlayer.ArrowDown:
                                square.Filler.enabled = false;
                                square.FrontMiddle.SetActive(true);
                                square.ApplyArrowDown();
                                square.gameObject.SetActive(true);
                                square.transform.position = new Vector3(
                                    column * MainManager.SIZE,
                                    3.0f * MainManager.SIZE,
                                    -row * MainManager.SIZE);
                                square.SetRenderersColor(LookupTables.EnemiesAndPlayerColor[index]);
                                break;
                            case (int)LookupTables.EnemiesAndPlayer.ArrowLeft:
                                square.Filler.enabled = false;
                                square.FrontMiddle.SetActive(true);
                                square.ApplyArrowLeft();
                                square.gameObject.SetActive(true);
                                square.transform.position = new Vector3(
                                    column * MainManager.SIZE,
                                    3.0f * MainManager.SIZE,
                                    -row * MainManager.SIZE);
                                square.SetRenderersColor(LookupTables.EnemiesAndPlayerColor[index]);
                                break;
                            case (int)LookupTables.EnemiesAndPlayer.ArrowRight:
                                square.Filler.enabled = false;
                                square.FrontMiddle.SetActive(true);
                                square.ApplyArrowRight();
                                square.gameObject.SetActive(true);
                                square.transform.position = new Vector3(
                                    column * MainManager.SIZE, 
                                    3.0f * MainManager.SIZE, 
                                    -row * MainManager.SIZE);
                                square.SetRenderersColor(LookupTables.EnemiesAndPlayerColor[index]);
                                break;
                            case (int)LookupTables.EnemiesAndPlayer.MiracleLightning:
                                square.FrontBack.enabled = true;
                                square.transform.position = new Vector3(
                                    column * MainManager.SIZE,
                                    1.25f * MainManager.SIZE,
                                    -row * MainManager.SIZE);
                                square.FrontBack.material = square.FrontBack.material;
                                if (!Timers.isFireBlocked)
                                {
                                    square.GetComponent<Square>().RandomMiracleLightningFire();

                                }
                                square.gameObject.SetActive(true);
                                break;
                            case (int)LookupTables.EnemiesAndPlayer.MiracleRain:
                                break;
                            case (int)LookupTables.EnemiesAndPlayer.MiracleSun:
                                //square.gameObject.SetActive(true);
                                //square.transform.position = new Vector3(column * MainManager.SIZE, 1.0f * MainManager.SIZE, -row * MainManager.SIZE);
                                //square.SetRenderersColor(LookupTables.EnemiesAndPlayerColor[index]);
                                break;
                            case (int)LookupTables.EnemiesAndPlayer.MiracleWind:
                                //square.gameObject.SetActive(true);
                                //square.transform.position = new Vector3(column * MainManager.SIZE, 1.0f * MainManager.SIZE, -row * MainManager.SIZE);
                                //square.SetRenderersColor(LookupTables.EnemiesAndPlayerColor[index]);
                                break;
                            case (int)LookupTables.EnemiesAndPlayer.MiracleEarthquake:
                                //square.gameObject.SetActive(true);
                                //square.transform.position = new Vector3(column * MainManager.SIZE, 1.0f * MainManager.SIZE, -row * MainManager.SIZE);
                                //square.SetRenderersColor(LookupTables.EnemiesAndPlayerColor[index]);
                                break;
                        }
                    }
                }
            }
        }
    }
}
