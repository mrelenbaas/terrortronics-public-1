using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class MainLoop : MonoBehaviour
{
    void Start()
    {
        Route.Setup();
        Route.SpecificTown();
    }

    private void Update()
    {
        Route.AllTimers();

        Route.Immobilize();
        RevealedTerrain.Boundary();
        Route.EnemyAndPlayer();
        Route.AllTiles();
        Route.CameraSquare();
        Route.FourByFour();
        Route.GrayBox();
        Route.YellowBox();
        Route.DrawButtonsBasedOnBools();
    }
}
