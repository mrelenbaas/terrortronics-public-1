using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class RevealedTerrain : MonoBehaviour
{
    public const int CAMERA_HEIGHT = 12;
    public const int CAMERA_WIDTH = 16;

    public static int cameraX;
    public static int cameraY;

    public static int x;
    public static int y;
    public static int right;
    public static int bottom;

    public static void Boundary()
    {
        x = cameraX;
        y = cameraY;
        right = cameraX + CAMERA_WIDTH;
        bottom = cameraY + CAMERA_HEIGHT;
    }

    public static (int, int, int) IncrementX(
        int boxOffsetX,
        int playerI,
        int playerJ,
        bool isEnemy)
    {
        cameraX++;
        boxOffsetX--;
        if (cameraX > 16)
        {
            cameraX = 16;
            boxOffsetX++;
            Towns.town[5, playerI, playerJ] = 0;
            playerJ++;
            if (playerJ > 31)
            {
                playerJ = 31;
            }
            if (isEnemy)
            {
                playerI -= Route.FindFreeTileAbove();
            }
            Towns.town[5, playerI, playerJ] = 1;
        }
        else
        {
            Towns.town[5, playerI, playerJ] = 0;
            playerJ++;
            if (isEnemy)
            {
                cameraX--;
                playerI -= Route.FindFreeTileAbove();
            }
            Towns.town[5, playerI, playerJ] = 1;
        }
        return (boxOffsetX, playerI, playerJ);
    }
    public static (int, int, int) DecrementX(
        int boxOffsetX,
        int playerI,
        int playerJ,
        bool isEnemy)
    {
        cameraX--;
        boxOffsetX++;
        if (cameraX < 0)
        {
            cameraX = 0;
            boxOffsetX--;
            Towns.town[5, playerI, playerJ] = 0;
            playerJ--;
            if (playerJ < 0)
            {
                playerJ = 0;
            }
            if (isEnemy)
            {
                playerI -= Route.FindFreeTileAbove();
            }
            Towns.town[5, playerI, playerJ] = 1;
        }
        else
        {
            Towns.town[5, playerI, playerJ] = 0;
            playerJ--;
            if (isEnemy)
            {
                cameraX++;
                playerI -= Route.FindFreeTileAbove();
            }
            Towns.town[5, playerI, playerJ] = 1;
        }
        return (boxOffsetX, playerI, playerJ);
    }

    public static (int, int, int) IncrementY(
        int boxOffsetY,
        int playerI,
        int playerJ,
        bool isEnemy)
    {
        cameraY++;
        boxOffsetY--;
        if (cameraY + CAMERA_HEIGHT > 32)
        {
            cameraY = 32 - CAMERA_HEIGHT;
            boxOffsetY++;
            Towns.town[5, playerI, playerJ] = 0;
            playerI++;
            if (playerI > 31)
            {
                playerI = 31;
            }
            if (isEnemy)
            {
                playerI -= Route.FindFreeTileAbove();
            }
            Towns.town[5, playerI, playerJ] = 1;
        }
        else
        {
            Towns.town[5, playerI, playerJ] = 0;
            playerI++;
            if (isEnemy)
            {
                cameraY--;
                playerI -= Route.FindFreeTileAbove();
            }
            Towns.town[5, playerI, playerJ] = 1;
        }
        return (boxOffsetY, playerI, playerJ);
    }
    public static (int, int, int) DecrementY(
        int boxOffsetY,
        int playerI,
        int playerJ,
        bool isEnemy)
    {
        if (playerI > 27)
        {
            Towns.town[5, playerI, playerJ] = 0;
            playerI--;
            Towns.town[5, playerI, playerJ] = 1;
        }
        else
        {
            cameraY--;
            boxOffsetY++;
            if (cameraY < 0)
            {
                cameraY = 0;
                boxOffsetY--;
                Towns.town[5, playerI, playerJ] = 0;
                playerI--;
                if (playerI < 0)
                {
                    playerI = 0;
                }
                if (isEnemy)
                {
                    playerI -= Route.FindFreeTileAbove();
                }
                Towns.town[5, playerI, playerJ] = 1;
            }
            else
            {
                Towns.town[5, playerI, playerJ] = 0;
                playerI--;
                if (isEnemy)
                {
                    cameraY++;
                    playerI -= Route.FindFreeTileAbove();
                }
                Towns.town[5, playerI, playerJ] = 1;
            }
        }
        return (boxOffsetY, playerI, playerJ);
    }
}
