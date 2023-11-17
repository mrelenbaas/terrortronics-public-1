/*
 * Title: Square file.
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

// TODO: Remember to re-implement the materials batching from the Vertical Slice build.

public class Square : MonoBehaviour
{
    [SerializeField]
    private Renderer filler;

    [SerializeField]
    private GameObject topTop;

    [SerializeField]
    private GameObject topMiddle;

    [SerializeField]
    private GameObject topBottom;

    [SerializeField]
    private Renderer frontFront;

    [SerializeField]
    private GameObject frontMiddle;

    [SerializeField]
    private Renderer frontBack;

    [SerializeField]
    private GameObject topFrontMiddle;

    [SerializeField]
    private GameObject horseLeft;

    [SerializeField]
    private GameObject horseRight;

    [SerializeField]
    private GameObject[] beaches;

    [SerializeField]
    private GameObject[] fire;

    [SerializeField]
    private GameObject[] grass;

    [SerializeField]
    private GameObject[] ponies;

    [SerializeField]
    private GameObject[] corgies;

    [SerializeField]
    private GameObject[] sheep;

    [SerializeField]
    private GameObject[] miracleLightningFires;

    [SerializeField]
    private GameObject[] mountains;

    [SerializeField]
    private GameObject[] treeBeds;

    [SerializeField]
    private GameObject[] water;

    [SerializeField]
    private GameObject arrowUp;

    [SerializeField]
    private GameObject arrowDown;

    [SerializeField]
    private GameObject arrowLeft;

    [SerializeField]
    private GameObject arrowRight;

    [SerializeField]
    private GameObject swamp;

    [SerializeField]
    private GameObject burned;

    [SerializeField]
    private GameObject bush;

    [SerializeField]
    private GameObject palmTree;

    [SerializeField]
    private GameObject bird;

    [SerializeField]
    private GameObject napperBat;

    [SerializeField]
    private GameObject blueDemon;

    [SerializeField]
    private GameObject tree;

    [SerializeField]
    private GameObject rock;

    public Renderer Filler { get { return filler; } set { filler = value; } }
    public GameObject TopTop { get { return topTop; } set { topTop = value; } }
    public GameObject TopMiddle { get { return topMiddle; } set { topMiddle = value; } }
    public GameObject TopBottom { get { return topBottom; } set { topBottom = value; } }
    public Renderer FrontFront { get { return frontFront; } set { frontFront = value; } }
    public GameObject FrontMiddle { get { return frontMiddle; } set { frontMiddle = value; } }
    public Renderer FrontBack { get { return frontBack; } set { frontBack = value; } }
    public GameObject TopFrontMiddle { get { return topFrontMiddle; } }

    public bool HorseLeft { get { return horseLeft.activeSelf; } set { horseLeft.SetActive(value); } }
    public bool HorseRight { get { return horseRight.activeSelf; } set { horseRight.SetActive(value); } }


    public void ApplyArrowUp()
    {
        //frontMiddle.material = arrow;
        arrowUp.SetActive(true);
    }

    public void ApplyArrowDown()
    {
        //frontMiddle.material = arrow;
        arrowDown.SetActive(true);
    }

    public void ApplyArrowLeft()
    {
        //frontMiddle.material = arrow;
        arrowLeft.SetActive(true);
    }

    public void ApplyArrowRight()
    {
        //frontMiddle.material = arrow;
        arrowRight.SetActive(true);
    }

    public void ApplyBird()
    {
        bird.SetActive(true);
    }

    public void ApplyBlueDemon()
    {
        blueDemon.SetActive(true);
    }

    public void ApplyBurned()
    {
        //topBottom.material = burned;
        burned.SetActive(true);
    }

    public void ApplyBush()
    {
        //frontMiddle.material = bush;
        bush.SetActive(true);
    }

    public void ApplyNapperBat()
    {
        napperBat.SetActive(true);
    }

    public void ApplyPalmTree()
    {
        palmTree.SetActive(true);
    }

    public void ApplyRock()
    {
        rock.SetActive(true);
    }

    public void ApplySwamp()
    {
        swamp.SetActive(true);
    }

    public void ApplyTree()
    {
        tree.SetActive(true);
    }

    public void RandomBeach()
    {
        for (var i = 0; i < beaches.Length; i++)
        {
            beaches[i].SetActive(false);
        }
        beaches[Random.Range(0, beaches.Length)].SetActive(true);
    }

    public void RandomFire()
    {
        for (var i = 0; i < fire.Length; i++)
        {
            fire[i].SetActive(false);
        }
        fire[Random.Range(0, fire.Length)].SetActive(true);
    }

    public void RandomGrass()
    {
        for (var i = 0; i < grass.Length; i++)
        {
            grass[i].SetActive(false);
        }
        grass[Random.Range(0, grass.Length)].SetActive(true);
    }

    public void RandomPony()
    {
        for (var i = 0; i < ponies.Length; i++)
        {
            ponies[i].SetActive(false);
        }
        ponies[Random.Range(0, ponies.Length)].SetActive(true);
    }

    public void RandomCorgi()
    {
        for (var i = 0; i < corgies.Length; i++)
        {
            corgies[i].SetActive(false);
        }
        corgies[Random.Range(0, corgies.Length)].SetActive(true);
    }

    public void RandomSheep()
    {
        for (var i = 0; i < sheep.Length; i++)
        {
            sheep[i].SetActive(false);
        }
        sheep[Random.Range(0, sheep.Length)].SetActive(true);
    }

    public void RandomMiracleLightningFire()
    {
        for (var i = 0; i < miracleLightningFires.Length; i++)
        {
            miracleLightningFires[i].SetActive(false);
        }
        miracleLightningFires[Random.Range(0, miracleLightningFires.Length)].SetActive(true);
    }

    public void RandomMountain()
    {
        for (var i = 0; i < mountains.Length; i++)
        {
            mountains[i].SetActive(false);
        }
        mountains[Random.Range(0, mountains.Length)].SetActive(true);
    }

    public void RandomTreeBed()
    {
        for (var i = 0; i < treeBeds.Length; i++)
        {
            treeBeds[i].SetActive(false);
        }
        treeBeds[Random.Range(0, treeBeds.Length)].SetActive(true);
    }

    public void RandomWater()
    {
        for (var i = 0; i < water.Length; i++)
        {
            water[i].SetActive(false);
        }
        water[Random.Range(0, water.Length)].SetActive(true);
    }

    public void SetRenderersColor(Color color)
    {
        filler.material.color = color;
        //topTop.material.color = color;
        //topMiddle.material.color = color;
        frontFront.material.color = color;
        //frontMiddle.material.color = color;
        frontBack.material.color = color;
    }

    public void TurnHorsesOn()
    {
        horseLeft.SetActive(true);
        horseRight.SetActive(true);
    }

    public void TurnHorsesOff()
    {
        horseLeft.SetActive(false);
        horseRight.SetActive(false);
    }
}
