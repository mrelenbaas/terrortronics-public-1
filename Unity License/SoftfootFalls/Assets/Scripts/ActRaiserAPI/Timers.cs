using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Timers : MonoBehaviour
{
    public static float timeDelta;

    public const float IMMOBILIZED_PERIOD = 10.0f;
    public static float immobilizedTime;

    public static bool Immobilize()
    {
        var result = true;
        immobilizedTime += timeDelta;
        if (immobilizedTime > IMMOBILIZED_PERIOD)
        {
            result = false;
            immobilizedTime = 0.0f;
        }
        return result;
    }

    public const float DEBOUND_PERIOD = 0.2f;
    public static float debounceTime;
    public static bool isDebouncing;

    // TODO: Remember this is trying a different timer reset setup.
    public static void Debounce()
    {
        var newTime = debounceTime += timeDelta;
        if (newTime > DEBOUND_PERIOD)
        {
            newTime = DEBOUND_PERIOD;
            isDebouncing = false;
        }
        debounceTime = newTime;
    }
    public static void DebounceReset()
    {
        Timers.debounceTime = 0.0f;
        Timers.isDebouncing = true;
    }
    public static bool DebounceStart()
    {
        var result = false;
        if (Timers.isDebouncing)
        {
            result = true;
        }
        else
        {
            Timers.DebounceReset();
        }
        return result;
    }

    public static readonly float angelPeriod = 0.6f;
    public static float angelTime;
    public static bool isAngelBobbedLeft;

    public static readonly float firePeriod = 0.1f;
    public static float fireTime;
    public static bool isFireBlocked;

    public static readonly float grassPeriod = 0.125f;
    public static readonly float grassThisPeriod = grassPeriod;
    public static float grassTime;
    public static bool isGrassBlocked;

    public static readonly float horsePasturePeriod = 1.2f;
    public static float horsePastureTime;
    public static bool isHorsePastureBlocked;

    public static readonly float waterPeriod = 0.2f;
    public static float waterTime;
    public static bool isWaterBlocked;

    public static readonly int DENS_PER_TOWN = 4;
    private const int ENEMY_ACTIONS_PER_ROUND = 1;
    public static readonly int TOWN_COUNT = 8;
    public static int[,] enemyDenSouls = new int[TOWN_COUNT, 4];
    public static float[,] enemyTimesSinceStartOfRound = new float[Timers.TOWN_COUNT, Timers.DENS_PER_TOWN];

    public static int scrollIndex;
    public static float scrollPeriod = 0.01f;
    public static float scrollPeriodPrevious = 0.01f;
    public static float scrollTime;
    public static bool isScrolling;
    public static bool isScrollReblock;

    public static readonly float boxYellowPeriod = 1.0f;
    public static float boxYellowTime;
    public static bool isBoxYellowVisible = true;


    public static void Angel()
    {
        angelTime += timeDelta;
        if (angelTime > angelPeriod)
        {
            isFireBlocked = false;
            angelTime = 0.0f;
            isAngelBobbedLeft = !isAngelBobbedLeft;
        }
    }

    public static void Grass()
    {
        grassTime += timeDelta;
        if (grassTime > grassPeriod)
        {
            isGrassBlocked = false;
            grassTime = 0.0f;
        }
    }

    public static void Fire()
    {
        fireTime += timeDelta;
        if (fireTime > firePeriod)
        {
            isFireBlocked = false;
            fireTime = 0.0f;
        }
    }

    public static void HorsePasture()
    {
        horsePastureTime += timeDelta;
        if (horsePastureTime > horsePasturePeriod)
        {
            //print("XXX");
            isHorsePastureBlocked = false;
            horsePastureTime = 0.0f;
        }
    }

    public static void Water()
    {
        waterTime += timeDelta;
        if (waterTime > waterPeriod)
        {
            isWaterBlocked = false;
            waterTime = 0.0f;
        }
    }

    public static void Reset()
    {
        if (isScrolling
            || isScrollReblock)
        {
            return;
        }
        scrollIndex = 0;
        scrollTime = 0.0f;
    }

    public static bool ScrollStart(int size)
    {
        var result = false;
        scrollTime += timeDelta;
        if (scrollTime > scrollPeriod)
        {
            //print(scrollIndex + "/" + size + ": " + Route.messageText);
            scrollTime = 0.0f;
            scrollIndex++;
            if (scrollIndex >= size)
            {
                result = true;
                isScrolling = false;
                scrollIndex = size;
            }
        }
        return result;
    }

    public static void ScrollStop()
    {
        scrollIndex = 0;
        isScrollReblock = false;
        //isScrolling = false;
    }

    public static void ScrollUnblockReblock()
    {
        isScrollReblock = false;
        isScrolling = true;
        Reset();
    }

    public static void BoxYellow()
    {
        boxYellowTime += timeDelta;
        if (boxYellowTime >= boxYellowPeriod)
        {
            boxYellowTime = 0.0f;
            isBoxYellowVisible = !isBoxYellowVisible;
        }
    }
}
