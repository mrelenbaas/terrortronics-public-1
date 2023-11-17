using System.Text;
using UnityEngine;

/**
 * 
**/

// TODO: The text that comes before the miracle is cast. It needs to be added.
public abstract class Route : MonoBehaviour
{
    public static bool IsBlocked
    {
        get
        {
            return Menus.isPaused;
        }
    }

    public static void Setup()
    {
        Menus.offeringsSize = (int)Menus.Offerings.Northwall5SourceOfLife;
        Menus.offeringIsFound = new bool[Menus.offeringsSize];
        Menus.offeringIsUsed = new bool[Menus.offeringsSize];
        SaveGame.SaveToFile(new int[] { 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
        SaveGameData.intArray = GameLoader.LoadFromFile();
        Towns.fillmore[5, Player.I_DEFAULT, Player.J_DEFAULT] = 1;
        Towns.town = Towns.deathHeim;
        for (var i = 0; i < Towns.TOWN_COUNT; i++)
        {
            for (var j = 0; j < DENS_PER_TOWN; j++)
            {
                enemyDenSouls[i, j] = enemyDenSoulsMaxes[i, j];
                enemyTimesSinceStartOfRound[i, j] = enemyTimesSinceStartOfRoundMaxes[i, j];
            }
        }
    }

    public static bool isHit;
    public static void EnemyAndPlayer()
    {
        if (Route.isHit)
        {
            var direction = UnityEngine.Random.Range(0.0f, 1.0f);
            for (var j = 0; j < 2; j++)
            {
                if (direction >= 0 && direction < 0.25f)
                {
                    Route.MoveUp(true);
                }
                else if (direction >= 0.25f && direction < 0.5f)
                {
                    Route.MoveDown(true);
                }
                else if (direction >= 0.5f && direction < 0.75f)
                {
                    Route.MoveLeft(true);
                }
                else
                {
                    Route.MoveRight(true);
                }
                direction = UnityEngine.Random.Range(0.0f, 1.0f);
            }
            Player.HealthPointsDecrease();
            Route.isHit = false;
        }
    }

    public static string messageText = "temp";
    public static void AllTimers()
    {
        if (Messages.IsMessageVisible)
        {
            Timers.ScrollStart(messageText.Length);
        }
        if (!Menus.isPaused
            && !Menus.isStart
            && !Menus.isSkyPalaceMenuVisible)
        {
            Timers.timeDelta = Time.deltaTime;
            Timers.Debounce();
            PopulationUpdatePeriod();
            ArrowUpdatePeriod();
            Miracles.LightningUpdatePeriod(
                Towns.town,
                Player.grayBoxI,
                Player.grayBoxJ);
            Miracles.RainUpdatePeriod(
                Towns.town,
                Player.grayBoxI,
                Player.grayBoxJ);
            Miracles.SunlightUpdatePeriod(
                Towns.town,
                Player.grayBoxI,
                Player.grayBoxJ);
            Miracles.WindUpdatePeriod(
                Towns.town,
                Player.grayBoxI,
                Player.grayBoxJ,
                Towns.SIZE);
            Miracles.EarthquakeUpdatePeriod(
                Towns.town,
                Player.grayBoxI,
                Player.grayBoxJ,
                Towns.SIZE);
            Timers.BoxYellow();
            if (isResettingToYellowBox)
            {
                ResetToYellowBoxUpdatePeriod();
            }
        }
        if (!Menus.isPaused
            && !Menus.isTakeAnOffering
            && !Menus.isTakeAnOfferingConfirmation
            && !Menus.isTakeAnOfferingDecline
            && !Menus.isUseAnOffering
            && !Menus.isUseAnOfferingDescription
            //&& !Miracles.IsAnyMiracleActive()
            && !Menus.isStart
            && !Menus.isPreEnterName
            && !Menus.isEnterPlayerNameMenuVisible
            && !Menus.isPostEnterName
            && !Menus.isSkyPalaceMenuVisible
            && !Menus.isTownBuilderMenuVisible
            && !Messages.IsMessageVisible)
        {
            EnemyUpdatePeriod();
            Timers.Angel();
            Timers.Grass();
            Timers.Fire();
            Timers.Water();
            Timers.HorsePasture();
        }
    }

    public const float RESET_TO_TOWN_YELLOW_BOX = 0.1f;
    public static float resetToYellowBoxTimeSinceStartOfPeriod = -1.0f;
    public static bool isResettingToYellowBox;
    public static void ResetToYellowBoxUpdatePeriod()
    {
        resetToYellowBoxTimeSinceStartOfPeriod += Timers.timeDelta;
        if (resetToYellowBoxTimeSinceStartOfPeriod > RESET_TO_TOWN_YELLOW_BOX)
        {
            resetToYellowBoxTimeSinceStartOfPeriod = 0.0f;
            if (Player.j < ((Player.yellowBoxI * 4) + 1))
            {
                Route.MoveRight();
            }
            else if (Player.j > ((Player.yellowBoxI * 4) + 1))
            {
                Route.MoveLeft();
            }
            else if (Player.i < ((Player.yellowBoxJ * 4) + 1))
            {
                Route.MoveDown();
            }
            else if (Player.i > ((Player.yellowBoxJ * 4) + 1))
            {
                Route.MoveUp();
            }
            else
            {
                resetToYellowBoxTimeSinceStartOfPeriod = -1.0f;
                isResettingToYellowBox = false;
                Route.isRecordingYellowBoxPath = true;
                Route.isGrayBoxVisible = true;
            }
        }
    }

    public static void SoulsCounterIncrease()
    {
        Towns.soulsCounters[Towns.townIndex]++;
    }
    public static void SoulsCounterDecrease()
    {
        Towns.soulsCounters[Towns.townIndex]--;
        if (Towns.soulsCounters[Towns.townIndex] < 0)
        {
            Towns.soulsCounters[Towns.townIndex] = 0;
        }
    }
    public static bool StructureIncrease()
    {
        if (Towns.populations[Towns.townIndex] == 0)
        {
            return false;
        }
        var roadCount = 0;
        for (var j = 0; j < Towns.SIZE; j++)
        {
            for (var k = 0; k < Towns.SIZE; k++)
            {
                if (Towns.town[(int)Towns.Layers.Building, k, j] == 24
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 25
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 26
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 27
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 28)
                {
                    roadCount++;
                }
            }
        }
        if (roadCount == 0)
        {
            return false;
        }
        var roads = new int[roadCount, 2];
        roadCount = 0;
        for (var j = 0; j < Towns.SIZE; j++)
        {
            for (var k = 0; k < Towns.SIZE; k++)
            {
                if (Towns.town[(int)Towns.Layers.Building, k, j] == 24
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 25
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 26
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 27
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 28)
                {
                    roads[roadCount, 0] = k;
                    roads[roadCount, 1] = j;
                    roadCount++;
                }
            }
        }
        var houseCount = 0;
        for (var i = 0; i < roadCount - 1; i++)
        {
            for (var j = roads[i, 1] - 1; j < roads[i, 1] + 1; j++)
            {
                for (var k = roads[i, 0] - 1; k < roads[i, 0] + 1; k++)
                {
                    if (Towns.town[(int)Towns.Layers.Building, k, j] == 0)
                    {
                        houseCount++;
                    }
                }
            }
        }
        var houses = new int[houseCount, 2];
        houseCount = 0;
        for (var i = 0; i < roadCount - 1; i++)
        {
            for (var j = roads[i, 1] - 1; j < roads[i, 1] + 1; j++)
            {
                for (var k = roads[i, 0] - 1; k < roads[i, 0] + 1; k++)
                {
                    if (Towns.town[(int)Towns.Layers.Building, k, j] == 110
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 210
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 310
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 410
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 114
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 214
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 314
                        || Towns.town[(int)Towns.Layers.Building, k, j] == 414)
                    {
                        print("SEAL DEN HERE: " + Towns.town[(int)Towns.Layers.Building, k, j]);
                        switch (Towns.town[(int)Towns.Layers.Building, k, j])
                        {
                            case 110:
                            case 114:
                                isEnemyDenSealed[Towns.townIndex, 0] = true;
                                break;
                            case 210:
                            case 214:
                                isEnemyDenSealed[Towns.townIndex, 1] = true;
                                break;
                            case 310:
                            case 314:
                                isEnemyDenSealed[Towns.townIndex, 2] = true;
                                break;
                            case 410:
                            case 414:
                                isEnemyDenSealed[Towns.townIndex, 3] = true;
                                break;
                        }
                        Towns.town[(int)Towns.Layers.Building, k, j] = 0;
                        Towns.soulsCounters[Towns.townIndex] += Towns.town[(int)Towns.Layers.Building, k, j + 1];
                        Towns.town[(int)Towns.Layers.Building, k, j + 1] = 0;
                    }
                    else if (Towns.town[(int)Towns.Layers.Building, k, j] == 0)
                    {
                        houses[houseCount, 0] = k;
                        houses[houseCount, 1] = j;
                        houseCount++;
                    }
                }
            }
        }
        if (houseCount == 0)
        {
            return false;
        }
        var houseIndex = UnityEngine.Random.Range(0, houses.Length - 1);
        if (Towns.civilizationLevels[Towns.townIndex] == 1)
        {
            // TODO: Why is there an 'out of bounds' exception here?
            try
            {
                Towns.town[
                (int)Towns.Layers.Building,
                houses[houseIndex, 0],
                houses[houseIndex, 1]] = 1;
            } catch (System.Exception e) { }
            return true;
        }
        else if (Towns.civilizationLevels[Towns.townIndex] == 2)
        {
            return true;
        }
        else if (Towns.civilizationLevels[Towns.townIndex] == 3)
        {
            return true;
        }
        return false;
    }
    public static bool StructureDecrease()
    {
        if (Towns.civilizationLevel1Buildings[Towns.townIndex] > 0)
        {
            Towns.civilizationLevel1Buildings[Towns.townIndex]--;
            return true;
        }
        else if (Towns.civilizationLevel2Buildings[Towns.townIndex] > 0)
        {
            Towns.civilizationLevel2Buildings[Towns.townIndex]--;
            return true;
        }
        else if (Towns.civilizationLevel3Buildings[Towns.townIndex] > 0)
        {
            Towns.civilizationLevel3Buildings[Towns.townIndex]--;
            return true;
        }
        else
        {
            return false;
        }
    }
    public static void CivilizationLevelIncrease()
    {
        Towns.civilizationLevels[Towns.townIndex]++;
        if (Towns.civilizationLevels[Towns.townIndex] > Towns.CIVILIZATION_LEVEL_MAX)
        {
            Towns.civilizationLevels[Towns.townIndex] = Towns.CIVILIZATION_LEVEL_MAX;
        }
    }

    public const int POPULATION_NEEDED_TO_SEAL_LAIR = 10;
    public static readonly float[,] enemyTimesSinceStartOfRoundMaxes = new float[,] {
        { 3.5f, 3.5f, 3.5f, 2.0f },
        { 3.0f, 3.0f, 3.0f, 3.0f },
        { 3.0f, 3.0f, 3.0f, 3.0f },
        { 3.0f, 3.0f, 3.0f, 3.0f },
        { 3.0f, 3.0f, 3.0f, 3.0f },
        { 3.0f, 3.0f, 3.0f, 3.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f }};
    public static readonly int[,] enemyDenSoulsMaxes = new int[,] {
        {500,500,500,500},
        {5,5,5,5},
        {5,5,5,5},
        {5,5,5,5},
        {5,5,5,5},
        {5,5,5,5},
        {0,0,0,0},
        {0,0,0,0}};
    public static int[,] monsterLocations = new int[,] {
        {-1, -1},
        {-1, -1},
        {-1, -1},
        {-1, -1}
    };
    public static bool[] isMonsterAlive = new bool[] {
        false,
        false,
        false,
        false
    };
    public static bool[] isMovingTowardPerson = new bool[] {
        false,
        false,
        false,
        false
    };
    public static bool[] isMovingTowardPlayer = new bool[] {
        false,
        false,
        false,
        false
    };
    public static int[,] targetLocations = new int[,] {
        { 0, 0 },
        { 0, 0 },
        { 0, 0 },
        { 0, 0 }
    };
    public static readonly bool[,] isEnemyDenSealed = new bool[,] {
        {false,false,false,false},
        {false,false,false,false},
        {false,false,false,false},
        {false,false,false,false},
        {false,false,false,false},
        {false,false,false,false},
        {false,false,false,false},
        {false,false,false,false}};
    public static int[] choosePersonIndexes = new int[]
    {
        0,
        0,
        0,
        0
    };
    public const int DENS_PER_TOWN = 4;
    public static int[,] enemyDenSouls = new int[Towns.TOWN_COUNT, 4];
    public static float[,] enemyTimesSinceStartOfRound = new float[Towns.TOWN_COUNT, DENS_PER_TOWN];
    public static void SealEnemyDen(int subgroupIndex)
    {
        do
        {
            EnemyDenSoulsDecrease(subgroupIndex);
            SoulsCounterIncrease();
        }
        while (enemyDenSouls[Towns.townIndex, subgroupIndex] > 0);
    }
    public static bool EnemyDenSoulsIncrease(int subgroupIndex)
    {
        if (Towns.populations[Towns.townIndex] == 0
            || enemyDenSouls[Towns.townIndex, subgroupIndex] == 0)
        {
            return false;
        }
        enemyDenSouls[Towns.townIndex, subgroupIndex]++;
        return true;
    }
    public static bool EnemyDenSoulsDecrease(int subgroupIndex)
    {
        enemyTimesSinceStartOfRound[Towns.townIndex, subgroupIndex] = 0.0f;
        enemyDenSouls[Towns.townIndex, subgroupIndex]--;
        if (enemyDenSouls[Towns.townIndex, subgroupIndex] == 0
            && isEnemyDenSealed[Towns.townIndex, subgroupIndex] == false)
        {
            isEnemyDenSealed[Towns.townIndex, subgroupIndex] = true;
            CivilizationLevelIncrease();
        }
        if (enemyDenSouls[Towns.townIndex, subgroupIndex] < 0)
        {
            enemyDenSouls[Towns.townIndex, subgroupIndex] = 0;
            return false;
        }
        return true;
    }
    public static void EnemyAction(int subgroupIndex)
    {
        if (isMonsterAlive[0] == false
            && isEnemyDenSealed[Towns.townIndex, 0] == false)
        {
            monsterLocations[0, 0] = Towns.denLocations[0, 0];
            monsterLocations[0, 1] = Towns.denLocations[0, 1];
            isMonsterAlive[0] = true;
        }
        else if (isMonsterAlive[1] == false
                 && isEnemyDenSealed[Towns.townIndex, 1] == false)
        {
            monsterLocations[0, 0] = Towns.denLocations[0, 0];
            monsterLocations[0, 1] = Towns.denLocations[0, 1];
            isMonsterAlive[1] = true;
        }
        else if (isMonsterAlive[2] == false
                 && isEnemyDenSealed[Towns.townIndex, 2] == false)
        {
            monsterLocations[0, 0] = Towns.denLocations[0, 0];
            monsterLocations[0, 1] = Towns.denLocations[0, 1];
            isMonsterAlive[2] = true;
        }
        else if (isMonsterAlive[3] == false
                 && isEnemyDenSealed[Towns.townIndex, 3] == false)
        {
            monsterLocations[0, 0] = Towns.denLocations[0, 0];
            monsterLocations[0, 1] = Towns.denLocations[0, 1];
            isMonsterAlive[3] = true;
        }
        else if (isMonsterAlive[subgroupIndex])
        {
            if (isMovingTowardPerson[subgroupIndex])
            {
                Route.MoveTowardPerson(subgroupIndex);
            }
            else if (isMovingTowardPlayer[subgroupIndex])
            {
                Route.MoveTowardPlayer(subgroupIndex);
            }
            else
            {
                var chooseAction = UnityEngine.Random.Range(0.0f, 1.0f);
                if (chooseAction < 0.5f)
                {
                    var peopleCounter = 0;
                    for (var j = 0; j < Towns.SIZE; j++)
                    {
                        for (var k = 0; k < Towns.SIZE; k++)
                        {
                            if (Towns.town[(int)Towns.Layers.People, j, k] > 0)
                            {
                                peopleCounter++;
                            }
                        }
                    }
                    if (peopleCounter == 0)
                    {
                        isMovingTowardPerson[subgroupIndex] = false;
                        isMovingTowardPlayer[subgroupIndex] = true;
                        Route.MoveTowardPerson(subgroupIndex);
                        return;
                    }
                    peopleLocations = new int[peopleCounter, 2];
                    var peopleIndex = 0;
                    for (var j = 0; j < Towns.SIZE; j++)
                    {
                        for (var k = 0; k < Towns.SIZE; k++)
                        {
                            if (Towns.town[(int)Towns.Layers.People, j, k] > 0)
                            {
                                peopleLocations[peopleIndex, 0] = k;
                                peopleLocations[peopleIndex, 1] = j;
                                peopleIndex++;
                            }
                        }
                    }
                    if (peopleCounter > 0)
                    {
                        var choosePerson = UnityEngine.Random.Range(0, peopleCounter - 1);
                        if (peopleLocations[choosePerson, 0] > 0
                            && peopleLocations[choosePerson, 1] > 0)
                        {
                            isMovingTowardPerson[subgroupIndex] = true;
                            targetLocations[subgroupIndex, 0] = peopleLocations[choosePerson, 0];
                            targetLocations[subgroupIndex, 1] = peopleLocations[choosePerson, 1];
                            choosePersonIndexes[subgroupIndex] = choosePerson;
                            choosePersonIndexes[subgroupIndex] = choosePerson;
                        }
                    }
                }
                else
                {
                    isMovingTowardPlayer[subgroupIndex] = true;
                }
            }
        }
    }
    public static void MoveTowardPerson(int subgroupIndex)
    {
        Towns.town[
            (int)Towns.Layers.EnemiesAndPlayer,
            monsterLocations[subgroupIndex, 1],
            monsterLocations[subgroupIndex, 0]] = 0;
        var previousX = monsterLocations[subgroupIndex, 0];
        var previousY = monsterLocations[subgroupIndex, 1];
        if (targetLocations[subgroupIndex, 0] == monsterLocations[subgroupIndex, 0]
            && targetLocations[subgroupIndex, 1] == monsterLocations[subgroupIndex, 1])
        {
            Towns.town[
                (int)Towns.Layers.People,
                targetLocations[subgroupIndex, 1],
                targetLocations[subgroupIndex, 0]] = 0;
            Timers.enemyTimesSinceStartOfRound[Towns.townIndex, subgroupIndex] = 0.0f;
            isMovingTowardPerson[subgroupIndex] = false;
        }
        else if (targetLocations[subgroupIndex, 0] == monsterLocations[subgroupIndex, 0])
        {
            if (targetLocations[subgroupIndex, 1] < monsterLocations[subgroupIndex, 1])
            {
                monsterLocations[subgroupIndex, 1]--;
                if (monsterLocations[subgroupIndex, 1] < 0)
                {
                    monsterLocations[subgroupIndex, 1] = 0;
                }
            }
            else if (targetLocations[subgroupIndex, 1] > monsterLocations[subgroupIndex, 1])
            {
                monsterLocations[subgroupIndex, 1]++;
                if (monsterLocations[subgroupIndex, 1] > 59)
                {
                    monsterLocations[subgroupIndex, 1] = 59;
                }
            }
        }
        else if (targetLocations[subgroupIndex, 0] < monsterLocations[subgroupIndex, 0])
        {
            monsterLocations[subgroupIndex, 0]--;
            if (monsterLocations[subgroupIndex, 0] < 0)
            {
                monsterLocations[subgroupIndex, 0] = 0;
            }
        }
        else if (targetLocations[subgroupIndex, 0] > monsterLocations[subgroupIndex, 0])
        {
            monsterLocations[subgroupIndex, 0]++;
            if (monsterLocations[subgroupIndex, 0] > 59)
            {
                monsterLocations[subgroupIndex, 0] = 59;
            }
        }
        for (var i = 0; i < 4; i++)
        {
            if (i == subgroupIndex)
            {
                continue;
            }
            if (monsterLocations[i, 0] == monsterLocations[subgroupIndex, 0]
                && monsterLocations[i, 1] == monsterLocations[subgroupIndex, 1])
            {
                monsterLocations[subgroupIndex, 0] = previousX;
                monsterLocations[subgroupIndex, 1] = previousY;
                Timers.enemyTimesSinceStartOfRound[Towns.townIndex, subgroupIndex] = 0.0f;
            }
        }
        if (subgroupIndex < 3)
        {
            Towns.town[
                (int)Towns.Layers.EnemiesAndPlayer,
                monsterLocations[subgroupIndex, 1],
                monsterLocations[subgroupIndex, 0]] = (subgroupIndex * 100) + 2;
        }
        else
        {
            Towns.town[
                (int)Towns.Layers.EnemiesAndPlayer,
                monsterLocations[subgroupIndex, 1],
                monsterLocations[subgroupIndex, 0]] = (subgroupIndex * 100) + 3;
        }
    }
    public static void MoveTowardPlayer(int subgroupIndex)
    {
        Towns.town[
            (int)Towns.Layers.EnemiesAndPlayer,
            monsterLocations[subgroupIndex, 1],
            monsterLocations[subgroupIndex, 0]] = 0;
        var previousX = monsterLocations[subgroupIndex, 0];
        var previousY = monsterLocations[subgroupIndex, 1];
        if (Player.j < monsterLocations[subgroupIndex, 0])
        {
            monsterLocations[subgroupIndex, 0]--;
        }
        else if (Player.j > monsterLocations[subgroupIndex, 0])
        {
            monsterLocations[subgroupIndex, 0]++;
        }
        else if (Player.i < monsterLocations[subgroupIndex, 1])
        {
            monsterLocations[subgroupIndex, 1]--;
        }
        else if (Player.i > monsterLocations[subgroupIndex, 1])
        {
            monsterLocations[subgroupIndex, 1]++;
        }
        if (Player.j == monsterLocations[subgroupIndex, 0]
            && Player.i == monsterLocations[subgroupIndex, 1])
        {
            monsterLocations[subgroupIndex, 0] = previousX;
            monsterLocations[subgroupIndex, 1] = previousY;
            Timers.enemyTimesSinceStartOfRound[Towns.townIndex, subgroupIndex] = 0.0f;
            isMovingTowardPlayer[subgroupIndex] = false;
            Route.isHit = true;
        }
        for (var i = 0; i < 4; i++)
        {
            if (i == subgroupIndex)
            {
                continue;
            }
            if (monsterLocations[i, 0] == monsterLocations[subgroupIndex, 0]
                && monsterLocations[i, 1] == monsterLocations[subgroupIndex, 1])
            {
                monsterLocations[subgroupIndex, 0] = previousX;
                monsterLocations[subgroupIndex, 1] = previousY;
                Timers.enemyTimesSinceStartOfRound[Towns.townIndex, subgroupIndex] = 0.0f;
            }
        }
        if (subgroupIndex < 3)
        {
            Towns.town[
                (int)Towns.Layers.EnemiesAndPlayer,
                monsterLocations[subgroupIndex, 1],
                monsterLocations[subgroupIndex, 0]] = (subgroupIndex * 100) + 2;
        }
        else
        {
            Towns.town[
                (int)Towns.Layers.EnemiesAndPlayer,
                monsterLocations[subgroupIndex, 1],
                monsterLocations[subgroupIndex, 0]] = (subgroupIndex * 100) + 3;
        }
    }
    public static void EnemyUpdatePeriod()
    {
        for (var i = 0; i < DENS_PER_TOWN; i++)
        {
            if (enemyDenSouls[Towns.townIndex, i] == 0)
            {
                continue;
            }
            enemyTimesSinceStartOfRound[Towns.townIndex, i] += Timers.timeDelta;
            if (enemyTimesSinceStartOfRound[Towns.townIndex, i] >= enemyTimesSinceStartOfRoundMaxes[Towns.townIndex, i])
            {
                enemyTimesSinceStartOfRound[Towns.townIndex, i] = 0f;
                EnemyAction(i);
            }
        }
    }

    public const int POPULATION_ACTIONS_PER_ROUND = 3;
    public static void PopulationIncrease()
    {
        if (Towns.soulsCounters[Towns.townIndex] <= 0)
        {
            return;
        }
        Towns.populations[Towns.townIndex]++;
        if (Towns.populations[Towns.townIndex] >= Towns.populationMaxes[Towns.townIndex])
        {
            Towns.populations[Towns.townIndex] = Towns.populationMaxes[Towns.townIndex];
        }
    }
    public static bool PopulationDecrease()
    {
        Towns.populations[Towns.townIndex]--;
        if (Towns.populations[Towns.townIndex] < 0)
        {
            Towns.populations[Towns.townIndex] = 0;
            return false;
        }
        return true;
    }
    public static void PopulationAction()
    {
        PopulationIncrease();
        if (StructureIncrease())
        {
        }
    }
    public static void PopulationRound()
    {
        Player.healthPoints += 2;
        if (Player.healthPoints > LevelTables.healthPoints[Player.level])
        {
            Player.healthPoints = LevelTables.healthPoints[Player.level];
        }
        for (var j = 0; j < POPULATION_ACTIONS_PER_ROUND; j++)
        {
            PopulationAction();
        }
        if (Route.isRecordingYellowBoxPath)
        {
        }
        else if (Route.yellowBoxPath[Route.yellowBoxPathI].x == -1
                 && Route.yellowBoxPath[Route.yellowBoxPathI].y == -1)
        {
        }
        else
        {
            if (Route.yellowBoxPathI < Route.YELLOW_BOX_PATH_MAX - 1
                && Route.yellowBoxPath[Route.yellowBoxPathI + 1].x == -1
                && Route.yellowBoxPath[Route.yellowBoxPathI + 1].y == -1)
            {
                return;
            }
            Route.yellowBoxPathI++;
            if (!Quests.is4thTutorialCompleted)
            {
                Quests.is4thTutorialReady = true;
            }
            if (Route.yellowBoxPathI >= Route.YELLOW_BOX_PATH_MAX - 1)
            {
                Route.yellowBoxDirections = new string[] {
                    "",
                    "",
                    "",
                    "",
                    "",
                    "",
                    "",
                    ""
                };
                if (yellowBoxPathI >= YELLOW_BOX_PATH_MAX - 1)
                {
                    Route.yellowBoxPath = new Vector2[] {
                        new Vector2(yellowBoxPath[YELLOW_BOX_PATH_MAX - 1].x, yellowBoxPath[YELLOW_BOX_PATH_MAX - 1].y),
                        new Vector2(-1, -1),
                        new Vector2(-1, -1),
                        new Vector2(-1, -1),
                        new Vector2(-1, -1),
                        new Vector2(-1, -1),
                        new Vector2(-1, -1),
                        new Vector2(-1, -1)
                    };
                }
                else
                {
                    Route.yellowBoxPath = new Vector2[] {
                        new Vector2(yellowBoxPath[yellowBoxPathI - 1].x, yellowBoxPath[yellowBoxPathI - 1].y),
                        new Vector2(-1, -1),
                        new Vector2(-1, -1),
                        new Vector2(-1, -1),
                        new Vector2(-1, -1),
                        new Vector2(-1, -1),
                        new Vector2(-1, -1),
                        new Vector2(-1, -1)
                    };
                }
                Route.yellowBoxPathI = 0;
                Route.isTownUnderConstruction = false;
            }
            else
            {
                Player.yellowBoxI = (int)Route.yellowBoxPath[Route.yellowBoxPathI].x;
                Player.yellowBoxJ = (int)Route.yellowBoxPath[Route.yellowBoxPathI].y;
                Player.yellowBoxDirection = Route.yellowBoxDirections[Route.yellowBoxPathI];
                while (true)
                {
                    var isComplete = false;
                    for (var i = 0; i < 4; i++)
                    {
                        for (var j = 0; j < 4; j++)
                        {
                            if (!isComplete)
                            {
                                if (Towns.town[(int)Towns.Layers.Building, (Player.yellowBoxJ * 4) + j, (Player.yellowBoxI * 4) + i] == 25)
                                {
                                    for (var k = j + 1; k > 0; k--)
                                    {
                                        if (Towns.town[(int)Towns.Layers.Land, (Player.yellowBoxJ * 4) + j - k, (Player.yellowBoxI * 4) + i] == 5)
                                        {
                                            continue;
                                        }
                                        Towns.town[(int)Towns.Layers.Building, (Player.yellowBoxJ * 4) + j - k, (Player.yellowBoxI * 4) + i] = 25;
                                    }
                                }
                                else if (Towns.town[(int)Towns.Layers.Building, (Player.yellowBoxJ * 4) + j, (Player.yellowBoxI * 4) + i] == 26)
                                {
                                    for (var k = 4 - (j + 1); k < 4; k++)
                                    {
                                        if (Towns.town[(int)Towns.Layers.Land, (Player.yellowBoxJ * 4) + j + k, (Player.yellowBoxI * 4) + i] == 5)
                                        {
                                            continue;
                                        }
                                        Towns.town[(int)Towns.Layers.Building, (Player.yellowBoxJ * 4) + j + k, (Player.yellowBoxI * 4) + i] = 26;
                                    }
                                }
                                else if (Towns.town[(int)Towns.Layers.Building, (Player.yellowBoxJ * 4) + j, (Player.yellowBoxI * 4) + i] == 27)
                                {
                                    for (var k = i + 1; k > 0; k--)
                                    {
                                        if (Towns.town[(int)Towns.Layers.Land, (Player.yellowBoxJ * 4) + j, (Player.yellowBoxI * 4) + i - k] == 5)
                                        {
                                            continue;
                                        }
                                        Towns.town[(int)Towns.Layers.Building, (Player.yellowBoxJ * 4) + j, (Player.yellowBoxI * 4) + i - k] = 27;
                                    }
                                }
                                else if (Towns.town[(int)Towns.Layers.Building, (Player.yellowBoxJ * 4) + j, (Player.yellowBoxI * 4) + i] == 28)
                                {
                                    for (var k = 0; k < 5; k++)
                                    {
                                        if (Towns.town[(int)Towns.Layers.Land, (Player.yellowBoxJ * 4) + j, (Player.yellowBoxI * 4) + i + k] == 5)
                                        {
                                        }
                                        Towns.town[(int)Towns.Layers.Building, (Player.yellowBoxJ * 4) + j, (Player.yellowBoxI * 4) + k] = 28;
                                    }
                                }
                            }
                        }
                    }
                    if (Route.yellowBoxPathI < 6
                        && (Route.yellowBoxDirections[Route.yellowBoxPathI + 1].Equals("<") || Route.yellowBoxDirections[Route.yellowBoxPathI + 1].Equals(">"))
                        && (Route.yellowBoxDirections[Route.yellowBoxPathI].Equals("^") || Route.yellowBoxDirections[Route.yellowBoxPathI].Equals("v")))
                    {
                        isComplete = false;
                        var row = 2;
                        for (var i = 0; i < 4; i++)
                        {
                            for (var j = 0; j < 4; j++)
                            {
                                if (Towns.town[(int)Towns.Layers.Building, ((int)Route.yellowBoxPath[Route.yellowBoxPathI].y * 4) + j, ((int)Route.yellowBoxPath[Route.yellowBoxPathI].x * 4) + i] == 25
                                    || Towns.town[(int)Towns.Layers.Building, ((int)Route.yellowBoxPath[Route.yellowBoxPathI].y * 4) + j, ((int)Route.yellowBoxPath[Route.yellowBoxPathI].x * 4) + i] == 26)
                                {
                                    if (!isComplete)
                                    {
                                        Towns.town[(int)Towns.Layers.Building, ((int)Route.yellowBoxPath[Route.yellowBoxPathI].y * 4) + row, ((int)Route.yellowBoxPath[Route.yellowBoxPathI].x * 4) + i] = 24;
                                        if (Route.yellowBoxDirections[Route.yellowBoxPathI + 1].Equals("<"))
                                        {
                                            for (var k = i + 1; k > 0; k--)
                                            {
                                                Towns.town[(int)Towns.Layers.Building, (Player.yellowBoxJ * 4) + row, (Player.yellowBoxI * 4) + i - k] = 27;
                                            }
                                        }
                                        else if (Route.yellowBoxDirections[Route.yellowBoxPathI + 1].Equals(">"))
                                        {
                                            for (var k = j; k < 3; k++)
                                            {
                                                Towns.town[(int)Towns.Layers.Building, (Player.yellowBoxJ * 4) + row, (Player.yellowBoxI * 4) + i + k] = 28;
                                            }
                                        }
                                        isComplete = true;
                                    }
                                }
                            }
                        }
                    }
                    else if (Route.yellowBoxPathI < 6
                             && (Route.yellowBoxDirections[Route.yellowBoxPathI + 1].Equals("^") || Route.yellowBoxDirections[Route.yellowBoxPathI + 1].Equals("v"))
                             && (Route.yellowBoxDirections[Route.yellowBoxPathI].Equals("<") || Route.yellowBoxDirections[Route.yellowBoxPathI].Equals(">")))
                    {
                        isComplete = false;
                        var column = 2;
                        var row = 1;
                        if (!isComplete)
                        {
                            Towns.town[(int)Towns.Layers.Building, ((int)Route.yellowBoxPath[Route.yellowBoxPathI].y * 4) + column, ((int)Route.yellowBoxPath[Route.yellowBoxPathI].x * 4) + row] = 24;
                            if (Route.yellowBoxDirections[Route.yellowBoxPathI + 1].Equals("^"))
                            {
                                for (var k = 4; k > 0; k--)
                                {
                                    Towns.town[(int)Towns.Layers.Building, (Player.yellowBoxJ * 4) + column - k, (Player.yellowBoxI * 4) + row] = 25;
                                }
                            }
                            else if (Route.yellowBoxDirections[Route.yellowBoxPathI + 1].Equals("v"))
                            {
                                for (var k = 0; k < 3; k++)
                                {
                                    Towns.town[(int)Towns.Layers.Building, (Player.yellowBoxJ * 4) + column + k, (Player.yellowBoxI * 4) + row] = 26;
                                }
                            }
                            isComplete = true;
                        }
                    }
                    break;
                }
            }
            var roadCounter = 0;
            for (var i = 0; i < Towns.SIZE; i++)
            {
                for (var j = 0; j < Towns.SIZE; j++)
                {
                    if (Towns.soulsCounters[Towns.townIndex] >= 4)
                    {
                        if (Towns.town[(int)Towns.Layers.Building, j, i] >= 24
                            && Towns.town[(int)Towns.Layers.Building, j, i] <= 34)
                        {
                            roadCounter++;
                        }
                        if ((Towns.town[(int)Towns.Layers.Building, j, i] == 25 || Towns.town[(int)Towns.Layers.Building, j, i] == 26)
                            && !((Towns.town[(int)Towns.Layers.Building, j, i] == 1) || (Towns.town[(int)Towns.Layers.Building, j, i] == 2 || (Towns.town[(int)Towns.Layers.Building, j, i] == 3))))
                        {
                            if (Towns.town[(int)Towns.Layers.Land, j, i - 1] == 2)
                            {
                                Towns.town[(int)Towns.Layers.Building, j, i - 1] = 1;
                            }
                            if (Towns.town[(int)Towns.Layers.Land, j, i + 1] == 2)
                            {
                                Towns.town[(int)Towns.Layers.Building, j, i + 1] = 1;
                            }
                            SoulsCounterDecrease();
                            SoulsCounterDecrease();
                            SoulsCounterDecrease();
                            SoulsCounterDecrease();
                            PopulationDecrease();
                            PopulationDecrease();
                            PopulationDecrease();
                            PopulationDecrease();
                        }
                        if ((Towns.town[(int)Towns.Layers.Building, j, i] == 27 || Towns.town[(int)Towns.Layers.Building, j, i] == 28)
                            && !((Towns.town[(int)Towns.Layers.Building, j, i] == 1) || (Towns.town[(int)Towns.Layers.Building, j, i] == 2 || (Towns.town[(int)Towns.Layers.Building, j, i] == 3))))
                        {
                            if (Towns.town[(int)Towns.Layers.Land, j - 1, i] == 2)
                            {
                                Towns.town[(int)Towns.Layers.Building, j - 1, i] = 1;
                            }
                            if (Towns.town[(int)Towns.Layers.Land, j + 1, i] == 2)
                            {
                                Towns.town[(int)Towns.Layers.Building, j + 1, i] = 1;
                            }
                            SoulsCounterDecrease();
                            SoulsCounterDecrease();
                            SoulsCounterDecrease();
                            SoulsCounterDecrease();
                            PopulationDecrease();
                            PopulationDecrease();
                            PopulationDecrease();
                            PopulationDecrease();
                        }
                    }
                }
            }
        }
    }
    public static void PopulationUpdatePeriod()
    {
        if (Towns.populations[Towns.townIndex] == 0)
        {
            Route.populationTimeSinceStartOfRound[Towns.townIndex] = 0f;
            return;
        }
        Route.populationTimeSinceStartOfRound[Towns.townIndex] += Timers.timeDelta;
        if (Route.populationTimeSinceStartOfRound[Towns.townIndex] >= Towns.periods[Towns.townIndex])
        {
            PopulationRound();
            Route.populationTimeSinceStartOfRound[Towns.townIndex] = 0f;
        }
    }

    public const float ARROW_TIME_PERIOD = 0.1f;
    public static float arrowTimeSinceStartOfPeriod;
    public static bool ArrowHit(int enemyAndPlayer)
    {
        var result = false;
        switch (enemyAndPlayer)
        {
            case 002:
            case 003:
                //Towns.town[(int)Towns.Layers.EnemiesAndPlayer,
                //           monsterLocations[0, 0],
                //           monsterLocations[0, 1]] = (int)LookupTables.EnemiesAndPlayer.None;
                monsterLocations[0, 0] = Towns.denLocations[0, 0];
                monsterLocations[0, 1] = Towns.denLocations[0, 1];
                isMonsterAlive[0] = false;
                EnemyDenSoulsDecrease(0);
                SoulsCounterIncrease();
                result = true;
                break;
            case 102:
            case 103:
                //Towns.town[(int)Towns.Layers.EnemiesAndPlayer,
                //           monsterLocations[1, 0],
                //           monsterLocations[1, 1]] = (int)LookupTables.EnemiesAndPlayer.None;
                monsterLocations[1, 0] = Towns.denLocations[1, 0];
                monsterLocations[1, 1] = Towns.denLocations[1, 1];
                isMonsterAlive[1] = false;
                EnemyDenSoulsDecrease(1);
                SoulsCounterIncrease();
                result = true;
                break;
            case 202:
            case 203:
                //Towns.town[(int)Towns.Layers.EnemiesAndPlayer,
                //           monsterLocations[2, 0],
                //           monsterLocations[2, 1]] = (int)LookupTables.EnemiesAndPlayer.None;
                monsterLocations[2, 0] = Towns.denLocations[2, 0];
                monsterLocations[2, 1] = Towns.denLocations[2, 1];
                isMonsterAlive[2] = false;
                EnemyDenSoulsDecrease(2);
                SoulsCounterIncrease();
                result = true;
                break;
            case 302:
            case 303:
                //Towns.town[(int)Towns.Layers.EnemiesAndPlayer,
                //           monsterLocations[3, 0],
                //           monsterLocations[3, 1]] = (int)LookupTables.EnemiesAndPlayer.None;
                monsterLocations[3, 0] = Towns.denLocations[3, 0];
                monsterLocations[3, 1] = Towns.denLocations[3, 1];
                isMonsterAlive[3] = false;
                EnemyDenSoulsDecrease(3);
                SoulsCounterIncrease();
                result = true;
                break;
        }
        return result;
    }
    public static void ArrowUpdatePeriod()
    {
        arrowTimeSinceStartOfPeriod += Timers.timeDelta;
        if (arrowTimeSinceStartOfPeriod >= ARROW_TIME_PERIOD)
        {
            for (var j = 0; j < Towns.SIZE; j++)
            {
                for (var k = 0; k < Towns.SIZE; k++)
                {
                    // Left.
                    if (Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k] == 6)
                    {
                        if (j - 1 >= 0)
                        {
                            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k] = 0;
                            if (!Route.ArrowHit(Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j - 1, k]))
                            {
                                Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j - 1, k] = 6;
                            }
                            else
                            {
                                //Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j - 1, k] = 0;
                            }
                            j--;
                        }
                        else
                        {
                            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k] = 0;
                        }
                        arrowTimeSinceStartOfPeriod = 0.0f;
                    }
                    // Right.
                    else if (Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k] == 7)
                    {
                        if (j + 1 < 60)
                        {
                            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k] = 0;
                            if (!Route.ArrowHit(Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j + 1, k]))
                            {
                                Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j + 1, k] = 7;
                            }
                            else
                            {
                                //Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j + 1, k] = 0;
                            }
                            j++;
                        }
                        else
                        {
                            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k] = 0;
                        }
                        arrowTimeSinceStartOfPeriod = 0.0f;
                    }
                    // Up.
                    else if (Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k] == 8)
                    {
                        if (k - 1 >= 0)
                        {
                            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k] = 0;
                            if (!Route.ArrowHit(Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k - 1]))
                            {
                                Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k - 1] = 8;
                            }
                            else
                            {
                                //Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k - 1] = 0;
                            }
                            k--;
                        }
                        else
                        {
                            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k] = 0;
                        }
                        arrowTimeSinceStartOfPeriod = 0.0f;
                    }
                    // Down.
                    else if (Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k] == 9)
                    {
                        if (k + 1 < 60)
                        {
                            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k] = 0;
                            if (!Route.ArrowHit(Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k + 1]))
                            {
                                Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k + 1] = 9;
                            }
                            else
                            {
                                //Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k + 1] = 0;
                            }
                            k++;
                        }
                        else
                        {
                            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k] = 0;
                        }
                        arrowTimeSinceStartOfPeriod = 0.0f;
                    }
                }
            }
        }
    }

    public static void Immobilize()
    {
        if (Player.isImmobilized)
        {
            if (Timers.Immobilize())
            {
            }
            else
            {
                Player.healthPoints = 2;
                Player.isImmobilized = false;
            }
        }
    }

    public static void ControlPadB()
    {
        if (Miracles.IsAnyMiracleActive())
        {
            return;
        }
        if (Menus.isStart)
        {
            Route.StartGame();
            return;
        }
        else if (Timers.isScrolling)
        {
            //print("IS SCROLLING");
            return;
        }
        else if (Timers.isScrollReblock)
        {
            Timers.ScrollUnblockReblock();
        }
        Timers.Reset();
        if (Menus.isPaused
            || Menus.isStart)
        {
            print("IS GENERALLY BLOCKED");
            Route.StartGame();
            return;
        }
        if (Towns.townIndex == 7)
        {
            print("IS TOWN 7");
            Towns.townIndex = 0;
            Menus.isSkyPalaceMenuVisible = true;
            return;
        }
        if (Route.isColumnZeroMessageVisible)
        {
            if (Messages.IncrementIndex(Messages.ColumnZero.Length))
            {
                Messages.IsMessageVisible = false;
                Route.isColumnZeroMessageVisible = false;
            }
        }
        else if (Route.isOhMessageVisible)
        {
            Route.isOhMessageVisible = false;
            Messages.IsMessageVisible = false;
        }
        else if (Menus.isEnterPlayerNameMenuVisible)
        {
            if (Menus.L == 4 && Menus.K == 12)
            {
                UpdatePlayerName();
                Route.EnterNameEnd();
            }
            else if (Menus.L == 4 && Menus.K == 11 && Route.nameIndex > 0)
            {
                UpdatePlayerName();
                Route.nameIndex--;
                if (Route.nameIndex < 0)
                {
                    Route.nameIndex = 0;
                }
            }
            else if (Menus.L == 4 && Menus.K == 11 && Route.nameIndex == 0)
            {
            }
            else
            {
                UpdatePlayerName();
                Route.nameIndex++;
                if (Route.nameIndex > 8)
                {
                    Route.nameIndex = 8;
                }
            }
        }
        else if (Route.isListeningToPeople)
        {
            Route.isListeningToPeople = false;
        }
        else if (Menus.isMessageSpeedMenuVisible)
        {
            Timers.scrollPeriodPrevious = Timers.scrollPeriod;
            SaveGameData.intArray[1] = Menus.L;
            Route.SetTextSpeedFromIntArray();
            Menus.isMessageSpeedMenuVisible = false;
            Menus.isMessageSpeedConfirmationVisible = true;
            Route.MessageTurnOn();
        }
        else if (Menus.isMessageSpeedConfirmationVisible)
        {
            Menus.isMessageSpeedConfirmationVisible = false;
            Messages.IsMessageVisible = false;
        }
        else if (Menus.isTakeAnOfferingConfirmation)
        {
            Route.TakeAnOfferingControlPadBAccept();
        }
        else if (Menus.isReturnToOfferingsDecline)
        {
            Messages.IsMessageVisible = false;
            //Timers.isScrolling = false;
            Menus.isReturnToOfferings = false;
            Menus.isReturnToOfferingsDecline = false;
            Menus.isTownBuilderMenuVisible = false;
        }
        else if (Menus.isReturnToOfferings)
        {
            var isFound = false;
            for (var i = 0; i < 2; i++)
            {
                for (var j = 0; j < 4; j++)
                {
                    if (i == 1 && j == 3)
                    {
                        Menus.offeringIconsInInventory[i, j] = Menus.offeringIcons[0];
                        Menus.offeringDescriptionsInInventory[i, j] = Menus.offeringDescriptions[0];
                    }
                    else if (i == Menus.K && j == Menus.L)
                    {
                        if (i == 0 && j == 3)
                        {
                            Menus.offeringIconsInInventory[i, j] = Menus.offeringIconsInInventory[1, 0];
                            Menus.offeringDescriptionsInInventory[i, j] = Menus.offeringDescriptionsInInventory[1, 0];
                        }
                        else
                        {
                            Menus.offeringIconsInInventory[i, j] = Menus.offeringIconsInInventory[i, j + 1];
                            Menus.offeringDescriptionsInInventory[i, j] = Menus.offeringDescriptionsInInventory[i, j + 1];
                        }
                        isFound = true;
                    }
                    else if (isFound)
                    {
                        if (i == 0 && j == 3)
                        {
                            Menus.offeringIconsInInventory[i, j] = Menus.offeringIconsInInventory[1, 0];
                            Menus.offeringDescriptionsInInventory[i, j] = Menus.offeringDescriptionsInInventory[1, 0];
                        }
                        else
                        {
                            Menus.offeringIconsInInventory[i, j] = Menus.offeringIconsInInventory[i, j + 1];
                            Menus.offeringDescriptionsInInventory[i, j] = Menus.offeringDescriptionsInInventory[i, j + 1];
                        }
                    }
                    else
                    {
                    }
                }
            }
            Menus.offeringIndex--;
            Menus.takenIndex++;
            if (Menus.K == 1)
            {
                Route.TakeAnOfferingControlPadBDecline();
            }
            else if (Menus.K == 0)
            {
                Menus.ResetKL();
                Route.TakeAnOffering();
                Menus.isReturnToOfferings = false;
            }
        }
        else if (Menus.isTakeAnOffering)
        {
            Menus.isTakeAnOfferingConfirmation = true;
            Menus.isTakeAnOffering = false;
        }
        else if (Menus.isUseAnOffering)
        {
            Route.UseAnOfferingControlPadBAccept();
        }
        else if (Route.isGoingToFight)
        {
            if (Messages.IncrementIndex(Messages.GoingToFight.Length))
            {
                //if (Towns.townIndex == 0)
                //{
                    //if (Menus.I == 1 && Menus.J == 1)
                    //{
                //Messages.IsMessageVisible = false;
                Menus.isSkyPalaceMenuVisible = false;
                if (Towns.isBossUnlocked[0, 0]
                    && !Towns.isBossDefeated[0, 0])
                {
                    Towns.populations[0] = 2;
                    Player.healthPoints = 8;
                    Player.spellPoints = 20;
                    Towns.isBossDefeated[0, 0] = true;
                    Status.scoreFillmoreActI = Status.scoreFillmoreActIMax;
                    Status.AddUpScore();
                }
                    //}
                //}
                Menus.ResetIJ();
                Menus.isSkyPalaceMenuVisible = false;
                Route.isGoingToFight = false;
                //Messages.IsMessageVisible = false;
            }
        }
        else if (Route.isQuittingGame)
        {
            if (Messages.IncrementIndex(Messages.Quitting.Length))
            {
                Menus.isReturnToWorldPromptVisible = false;
                Messages.IsMessageVisible = false;
                CrossPlatform.Quit();
            }
        }
        else if (Route.isMagicUnavailable)
        {
            Route.isMagicUnavailable = false;
            Messages.IsMessageVisible = false;
        }
        else if (isTownUninhabited)
        {
            isTownUninhabited = false;
            Messages.IsMessageVisible = false;
        }
        else if (Menus.isPreEnterName)
        {
            Route.PreEnterName();
        }
        else if (Menus.isPostEnterName)
        {
            Route.PostEnterName();
        }
        else if (Route.isRecordingYellowBoxPath)
        {
            Route.yellowBoxPathI = 0;
            Route.isGrayBoxVisible = false;
            Route.isRecordingYellowBoxPath = false;
        }
        else if (Route.isListeningToPeople)
        {
            Route.isListeningToPeople = false;
        }
        else if (!Quests.is1stTutorialCompleted
                    && !Menus.isSkyPalaceMenuVisible
                    && !Menus.isTownBuilderMenuVisible)
        {
            if (Messages.IncrementIndex(Messages.Quest1.Length))
            {
                print("1 complete");
                MessageTurnOn();
                Route.messageText = Messages.Quest2[Messages.Index];
                Quests.is1stTutorialCompleted = true;
            }
        }
        else if (!Quests.is2ndTutorialCompleted
                    && !Menus.isSkyPalaceMenuVisible
                    && !Menus.isTownBuilderMenuVisible)
        {
            if (Messages.IncrementIndex(Messages.Quest2.Length))
            {
                print("2 complete");
                //MessageTurnOn();
                Route.messageText = Messages.Quest3[Messages.Index];
                Quests.is2ndTutorialCompleted = true;
            }
        }
        else if (!Quests.is3rdTutorialCompleted
                    && !Menus.isSkyPalaceMenuVisible
                    && !Menus.isTownBuilderMenuVisible)
        {
            if (Messages.IncrementIndex(Messages.Quest3.Length))
            {
                print("3 complete");
                MessageTurnOn();
                Route.messageText = Messages.Quest4[Messages.Index];
                Quests.is3rdTutorialCompleted = true;
            }
        }
        else if (Quests.is4thTutorialReady
                    && !Quests.is4thTutorialCompleted
                    && !Menus.isSkyPalaceMenuVisible
                    && !Menus.isTownBuilderMenuVisible)
        {
            print("4 complete");
            if (Messages.IncrementIndex(Messages.Quest4.Length))
            {
                Quests.is4thTutorialReady = false;
                Quests.is4thTutorialCompleted = true;
            }
        }
        else if (Route.isProgressLogFinished)
        {
            if (Messages.IncrementIndex(Messages.ProgressLogContinue.Length))
            {
                Messages.IsMessageVisible = false;
                Route.isProgressLogFinished = false;
            }
        }
        else if (Menus.isProgressLogConfirmationVisible)
        {
            if (Menus.K == 0)
            {
                Menus.isProgressLogConfirmationVisible = false;
                Menus.isReturnToWorldPromptVisible = true;
                Menus.ResetKL();
            }
            else if (Menus.K == 1)
            {
                Menus.isProgressLogConfirmationVisible = false;
                Route.isOhMessageVisible = true;
                Menus.ResetKL();
            }
        }
        else if (Menus.isReturnToWorldPromptVisible)
        {
            if (Menus.K == 0)
            {
                SaveGame.SaveToFile(SaveGameData.intArray);
                Menus.isReturnToWorldPromptVisible = false;
                Route.isProgressLogFinished = true;
                Menus.ResetKL();
            }
            else if (Menus.K == 1)
            {
                Menus.isReturnToWorldPromptVisible = false;
                Route.isQuittingGame = true;
                Menus.ResetKL();
            }
        }
        else if (Route.isStatusOfMasterVisible)
        {
            Route.isStatusOfCitiesVisible = true;
            Route.isStatusOfMasterVisible = false;
        }
        else if (Route.isStatusOfCitiesVisible)
        {
            Menus.isSkyPalaceMenuVisible = true;
            Route.isStatusOfCitiesVisible = false;
        }
        else if (Menus.IsZeroColumn)
        {
            Route.isColumnZeroMessageVisible = true;
            Route.MessageTurnOn();
        }
        else if (Route.isMagicMenuVisible)
        {
            Route.isMagicMenuVisible = false;
        }
        else if (Menus.isLightningAvailable)
        {
            if (Messages.IncrementIndex(Messages.LightningAvailable.Length))
            {
                Menus.isLightningYesNo = true;
                Menus.isLightningAvailable = false;
            }
        }
        else if (Menus.isLightningUnavailable)
        {
            if (Messages.IncrementIndex(Messages.LightningUnavailable.Length))
            {
                Timers.ScrollStop();
                Menus.isLightningUnavailable = false;
            }
        }
        else if (Menus.isLightningYesNo)
        {
            if (Menus.K == 0)
            {
                Menus.isLightningShowMeWhere = true;
                Menus.isLightningYesNo = false;
            }
            else if (Menus.K == 1)
            {
                Menus.ResetIJ();
                Menus.ResetKL();
                Menus.ResetM();
                Menus.isTownBuilderMenuVisible = false;
                Messages.IsMessageVisible = false;
                Menus.isLightningYesNo = false;
            }
        }
        else if (Menus.isLightningShowMeWhere)
        {
            if (Messages.IncrementIndex(Messages.LightningShowMeWhere.Length))
            {
                Messages.IsMessageVisible = false;
                Menus.ResetIJ();
                Menus.ResetKL();
                Menus.ResetM();
                Route.isGrayBoxVisible = true;
                Miracles.isLightningPrimed = true;
                Menus.isTownBuilderMenuVisible = false;
                Menus.isLightningShowMeWhere = false;
            }
        }
        else if (Miracles.isLightningPrimed)
        {
            Miracles.lightningTimesSinceStartOfMiracle = 0.0f;
            Route.isGrayBoxVisible = false;
            Miracles.isLightningResult = false;
            Miracles.isLightningPrimed = false;
        }
        else if (Menus.isLightningSuccess)
        {
            // Empty.
        }
        else if (Menus.isLightningFailure)
        {
            //Timers.Reset();
            if (Messages.IncrementIndex(Messages.MiracleFailure.Length))
            {
                Menus.isLightningFailure = false;
                Messages.IsMessageVisible = false;
            }
        }
        else if (Menus.isRainAvailable)
        {
            if (Messages.IncrementIndex(Messages.RainAvailable.Length))
            {
                Menus.isRainYesNo = true;
                Menus.isRainAvailable = false;
            }
        }
        else if (Menus.isRainUnavailable)
        {
            if (Messages.IncrementIndex(Messages.RainUnavailable.Length))
            {
                Timers.ScrollStop();
                Menus.isRainUnavailable = false;
            }
        }
        else if (Menus.isRainYesNo)
        {
            if (Menus.K == 0)
            {
                Menus.isRainShowMeWhere = true;
                Menus.isRainYesNo = false;
            }
            else if (Menus.K == 1)
            {
                Menus.ResetIJ();
                Menus.ResetKL();
                Menus.ResetM();
                Menus.isTownBuilderMenuVisible = false;
                Messages.IsMessageVisible = false;
                Menus.isRainYesNo = false;
            }
        }
        else if (Menus.isRainShowMeWhere)
        {
            if (Messages.IncrementIndex(Messages.RainShowMeWhere.Length))
            {
                Menus.ResetIJ();
                Menus.ResetKL();
                Menus.ResetM();
                Route.isGrayBoxVisible = true;
                Miracles.isRainPrimed = true;
                Menus.isTownBuilderMenuVisible = false;
                Menus.isRainShowMeWhere = false;
            }
        }
        else if (Miracles.isRainPrimed)
        {
            Miracles.rainTimeSinceStartOfMiracle = 0.0f;
            Route.isGrayBoxVisible = false;
            Miracles.isRainPrimed = false;
        }
        else if (Menus.isRainSuccess)
        {
            // Empty.
        }
        else if (Menus.isRainFailure)
        {
            Timers.Reset();
            if (Messages.IncrementIndex(Messages.MiracleFailure.Length))
            {
                Menus.isRainFailure = false;
                Messages.IsMessageVisible = false;
            }
        }
        else if (Menus.isSunAvailable)
        {
            if (Messages.IncrementIndex(Messages.SunAvailable.Length))
            {
                Menus.isSunAvailable = false;
                Menus.isSunYesNo = true;
            }
        }
        else if (Menus.isSunUnavailable)
        {
            if (Messages.IncrementIndex(Messages.SunUnavailable.Length))
            {
                Timers.ScrollStop();
                Menus.isSunUnavailable = false;
            }
        }
        else if (Menus.isSunYesNo)
        {
            if (Menus.K == 0)
            {
                Menus.isSunShowMeWhere = true;
                Menus.isSunYesNo = false;
            }
            else if (Menus.K == 1)
            {
                Menus.ResetIJ();
                Menus.ResetKL();
                Menus.ResetM();
                Menus.isTownBuilderMenuVisible = false;
                Messages.IsMessageVisible = false;
                Menus.isSunYesNo = false;
            }
        }
        else if (Menus.isSunShowMeWhere)
        {
            if (Messages.IncrementIndex(Messages.SunShowMeWhere.Length))
            {
                Menus.ResetIJ();
                Menus.ResetKL();
                Menus.ResetM();
                Route.isGrayBoxVisible = true;
                Miracles.isSunlightPrimed = true;
                Menus.isTownBuilderMenuVisible = false;
                Menus.isSunShowMeWhere = false;
            }
        }
        else if (Miracles.isSunlightPrimed)
        {
            Miracles.sunlightTimeSinceStartOfMiracle = 0.0f;
            Route.isGrayBoxVisible = false;
            Miracles.isSunlightPrimed = false;
        }
        else if (Menus.isSunSuccess)
        {
            // Empty.
        }
        else if (Menus.isSunFailure)
        {
            Timers.Reset();
            if (Messages.IncrementIndex(Messages.MiracleFailure.Length))
            {
                Menus.isSunFailure = false;
                Messages.IsMessageVisible = false;
            }
        }
        else if (Menus.isWindAvailable)
        {
            if (Messages.IncrementIndex(Messages.WindAvailable.Length))
            {
                Menus.isWindAvailable = false;
                Menus.isWindYesNo = true;
                Miracles.windTimeSinceStartOfMiracle = 0.0f;
            }
        }
        else if (Menus.isWindUnavailable)
        {
            if (Messages.IncrementIndex(Messages.WindUnavailable.Length))
            {
                Timers.ScrollStop();
                Menus.isWindUnavailable = false;
            }
        }
        else if (Menus.isWindYesNo)
        {
            if (Menus.K == 0)
            {
                Menus.ResetIJ();
                Menus.ResetKL();
                Menus.ResetM();
                Menus.isTownBuilderMenuVisible = false;
                Messages.IsMessageVisible = false;
                Menus.isWindYesNo = false;
                Miracles.windTimeSinceStartOfMiracle = 0.0f;
            }
            else if (Menus.K == 1)
            {
                Menus.ResetIJ();
                Menus.ResetKL();
                Menus.ResetM();
                Menus.isTownBuilderMenuVisible = false;
                Messages.IsMessageVisible = false;
                Menus.isWindYesNo = false;
                Miracles.windTimeSinceStartOfMiracle = 0.0f;
            }
        }
        else if (Menus.isWindSuccess)
        {
            // Empty.
        }
        else if (Menus.isWindFailure)
        {
            Timers.Reset();
            if (Messages.IncrementIndex(Messages.MiracleFailure.Length))
            {
                Menus.isWindFailure = false;
                Messages.IsMessageVisible = false;
            }
        }
        else if (Menus.isEarthquakeAvailable)
        {
            if (Messages.IncrementIndex(Messages.EarthquakeAvailable.Length))
            {
                Menus.isEarthquakeAvailable = false;
                Menus.isEarthquakeYesNo = true;
            }
        }
        else if (Menus.isEarthquakeUnavailable)
        {
            if (Messages.IncrementIndex(Messages.EarthquakeUnavailable.Length))
            {
                Timers.ScrollStop();
                Menus.isEarthquakeUnavailable = false;
            }
        }
        else if (Menus.isEarthquakeYesNo)
        {
            if (Menus.K == 0)
            {
                Menus.ResetIJ();
                Menus.ResetKL();
                Menus.ResetM();
                Menus.isTownBuilderMenuVisible = false;
                Messages.IsMessageVisible = false;
                Menus.isEarthquakeYesNo = false;
                Miracles.earthquakeTimeSinceStartOfMiracle = 0.0f;
            }
            else if (Menus.K == 1)
            {
                Menus.ResetIJ();
                Menus.ResetKL();
                Menus.ResetM();
                Menus.isTownBuilderMenuVisible = false;
                Messages.IsMessageVisible = false;
                Menus.isEarthquakeYesNo = false;
                Miracles.earthquakeTimeSinceStartOfMiracle = 0.0f;
            }
        }
        else if (Menus.isEarthquakeSuccess)
        {
            // Empty.
        }
        else if (Menus.isEarthquakeFailure)
        {
            Timers.Reset();
            if (Messages.IncrementIndex(Messages.MiracleFailure.Length))
            {
                //Timers.isScrolling = false;
                Menus.isEarthquakeFailure = false;
                Messages.IsMessageVisible = false;
            }
        }
        else if (Menus.isTownBuilderMenuVisible)
        {
            if (Menus.I == 0 && Menus.J == 1)
            {
                Messages.IsMessageVisible = false;
                Menus.isSkyPalaceMenuVisible = true;
                Menus.isTownBuilderMenuVisible = false;
                Menus.ResetIJ();
                Towns.townIndex = 0;
            }
            else if (Menus.I == 0 && Menus.J == 2)
            {
                //Route.MessageTurnOn();
                //Towns.GoToWorldMap();
                Towns.GoToNextWorld();
                print("GO TO WORLD MAP");
                Menus.isTownBuilderMenuVisible = false;
                Menus.ResetIJ();
                Route.Setup();
                Route.SpecificTown();
            }
            else if (Menus.I == 1 && Menus.J == 1)
            {
                ResetToYellowBoxStart();
                Menus.isTownBuilderMenuVisible = false;
            }
            else if (Menus.I == 1 && Menus.J == 2)
            {
                Menus.isTownBuilderMenuVisible = false;
                Route.isListeningToPeople = true;
                Route.MessageTurnOn();
            }
            else if (Menus.I == 2 && Menus.J == 1)
            {
                if (Player.spellPoints >= Miracles.LIGHTNING_SP)
                {
                    Route.MessageTurnOn();
                    Menus.isLightningAvailable = true;
                }
                else
                {
                    Route.MessageTurnOn();
                    Menus.isLightningUnavailable = true;
                }
            }
            else if (Menus.I == 2 && Menus.J == 2)
            {
                if (Player.spellPoints >= Miracles.RAIN_SP)
                {
                    Route.MessageTurnOn();
                    Menus.isRainAvailable = true;
                }
                else
                {
                    Route.MessageTurnOn();
                    Menus.isRainUnavailable = true;
                }
            }
            else if (Menus.I == 2 && Menus.J == 3)
            {
                if (Player.spellPoints >= Miracles.SUNLIGHT_SP)
                {
                    Route.MessageTurnOn();
                    Menus.isSunAvailable = true;
                }
                else
                {
                    Route.MessageTurnOn();
                    Menus.isSunUnavailable = true;
                }
            }
            else if (Menus.I == 2 && Menus.J == 4)
            {
                if (Player.spellPoints >= Miracles.WIND_SP)
                {
                    Route.MessageTurnOn();
                    Menus.isWindAvailable = true;
                }
                else
                {
                    Route.MessageTurnOn();
                    Menus.isWindUnavailable = true;
                }
            }
            else if (Menus.I == 2 && Menus.J == 5)
            {
                if (Player.spellPoints >= Miracles.EARTHQUAKE_SP)
                {
                    Route.MessageTurnOn();
                    Menus.isEarthquakeAvailable = true;
                }
                else
                {
                    Route.MessageTurnOn();
                    Menus.isEarthquakeUnavailable = true;
                }
            }
            else if (Menus.I == 3 && Menus.J == 1)
            {
                Menus.isTownBuilderMenuVisible = false;
                Route.TakeAnOffering();
                Menus.ResetKL();
            }
            else if (Menus.I == 3 && Menus.J == 2)
            {
                Menus.ResetKL();
                Timers.Reset();
                Route.MessageDescription(Messages.UseOffering[Messages.Index]);
                Route.MessageTurnOn();
                Menus.isUseAnOffering = true;
            }
            else if (Menus.I == 4 && Menus.J == 1)
            {
                Route.isStatusOfMasterVisible = true;
            }
            else if (Menus.I == 4 && Menus.J == 2)
            {
                Route.isStatusOfCitiesVisible = true;
            }
            else if (Menus.I == 5 && Menus.J == 1)
            {
                Route.ProgressLog();
            }
            else if (Menus.I == 5 && Menus.J == 2)
            {
                Route.MessageSpeed();
            }
        }
        else if (Menus.isSkyPalaceMenuVisible)
        {
            if (Menus.I == 0 && Menus.J == 1)
            {
                //Towns.GoToWorldMap();
                Towns.GoToNextWorld();
                Messages.IsMessageVisible = false;
                Menus.isSkyPalaceMenuVisible = false;
                Menus.ResetIJ();
            }
            else if (Menus.I == 0 && Menus.J == 2)
            {
                if (Towns.townIndex == 0)
                {
                    if (Towns.isBossDefeated[0, 0])
                    {
                        Messages.IsMessageVisible = false;
                        Menus.isSkyPalaceMenuVisible = false;
                        Timers.Reset();
                    }
                    else
                    {
                        isTownUninhabited = true;
                        Route.MessageTurnOn();
                    }
                }
            }
            else if (Menus.I == 1 && Menus.J == 1)
            {
                Route.isGoingToFight = true;
                Route.MessageTurnOn();
            }
            else if (Menus.I == 1 && Menus.J == 2)
            {
                if (Magics.isMagicalFireUnlockled
                    || Magics.isMagicalStartdustUnlockled
                    || Magics.isMagicalLightUnlockled
                    || Magics.isMagicalAuraUnlockled)
                {
                    Route.isMagicMenuVisible = true;
                }
                else
                {
                    Route.isMagicUnavailable = true;
                }
                Route.MessageTurnOn();
            }
            else if (Menus.I == 2 && Menus.J == 1)
            {
                Route.isStatusOfMasterVisible = true;
            }
            else if (Menus.I == 2 && Menus.J == 2)
            {
                Route.isStatusOfCitiesVisible = true;
            }
            else if (Menus.I == 3 && Menus.J == 1)
            {
                Route.ProgressLog();
            }
            else if (Menus.I == 3 && Menus.J == 2)
            {
                Route.MessageSpeed();
            }
        }
        else if (!Menus.isSkyPalaceMenuVisible
                    && !Menus.isTownBuilderMenuVisible)
        {
            Messages.IsMessageVisible = false;
            Menus.isTownBuilderMenuVisible = true;
        }
        //print(Menus.isSkyPalaceMenuVisible + ", " + Menus.isTownBuilderMenuVisible);
    }

    public static int nameIndex;
    public static void ControlPadY()
    {
        /* TODO: This keeps being turned on, and I don't understand why.
        if (Timers.isScrolling)
        {
            print("HERE?");
            return;
        }
        else */
        if (Menus.isStart)
        {
            Route.StartGame();
            return;
        }
        else if (Timers.isScrolling)
        {
            print("IS SCROLLING");
            return;
        }
        else if (Menus.isTakeAnOffering)
        {
            Menus.isTakeAnOffering = false;
        }
        else if (Route.isMagicMenuVisible)
        {
            Route.isMagicMenuVisible = false;
        }
        else if (Menus.isLightningAvailable
                 || Menus.isRainAvailable
                 || Menus.isSunAvailable
                 || Menus.isWindAvailable
                 || Menus.isEarthquakeAvailable)
        {
            Messages.IsMessageVisible = false;
            Menus.ResetIJ();
            Menus.ResetKL();
            Menus.ResetM();
            Menus.isLightningAvailable = false;
            Menus.isRainAvailable = false;
            Menus.isSunAvailable = false;
            Menus.isWindAvailable = false;
            Menus.isEarthquakeAvailable = false;
        }
        else if (Menus.isLightningYesNo
                 || Menus.isRainYesNo
                 || Menus.isSunYesNo
                 || Menus.isWindYesNo
                 || Menus.isEarthquakeYesNo)
        {
            Messages.IsMessageVisible = false;
            Menus.ResetIJ();
            Menus.ResetKL();
            Menus.ResetM();
            Menus.isLightningYesNo = false;
            Menus.isRainYesNo = false;
            Menus.isSunYesNo = false;
            Menus.isRainYesNo = false;
            Menus.isEarthquakeYesNo = false;
        }
        else if (Menus.isLightningShowMeWhere)
        {
            if (Messages.IncrementIndex(Messages.LightningShowMeWhere.Length))
            {
                Messages.IsMessageVisible = false;
                //Timers.isScrolling = false;
                Menus.ResetIJ();
                Menus.ResetKL();
                Menus.ResetM();
                Route.isGrayBoxVisible = true;
                Miracles.isLightningPrimed = true;
                Menus.isTownBuilderMenuVisible = false;
                Menus.isLightningShowMeWhere = false;
            }
        }
        else if (Menus.isLightningFailure)
        {
            //Timers.Reset();
            if (Messages.IncrementIndex(Messages.MiracleFailure.Length))
            {
                Menus.isLightningFailure = false;
                Messages.IsMessageVisible = false;
            }
        }
        else if (Menus.isRainFailure)
        {
            //Timers.Reset();
            if (Messages.IncrementIndex(Messages.MiracleFailure.Length))
            {
                Menus.isRainFailure = false;
                Messages.IsMessageVisible = false;
            }
        }
        else if (Menus.isSunFailure)
        {
            //Timers.Reset();
            if (Messages.IncrementIndex(Messages.MiracleFailure.Length))
            {
                Menus.isSunFailure = false;
                Messages.IsMessageVisible = false;
            }
        }
        else if (Menus.isWindFailure)
        {
            //Timers.Reset();
            if (Messages.IncrementIndex(Messages.MiracleFailure.Length))
            {
                Menus.isWindFailure = false;
                Messages.IsMessageVisible = false;
            }
        }
        else if (Menus.isEarthquakeFailure)
        {
            //Timers.Reset();
            if (Messages.IncrementIndex(Messages.MiracleFailure.Length))
            {
                Menus.isEarthquakeFailure = false;
                Messages.IsMessageVisible = false;
            }
        }
        else if (Menus.isRainShowMeWhere)
        {
            if (Messages.IncrementIndex(Messages.RainShowMeWhere.Length))
            {
                Messages.IsMessageVisible = false;
                //Timers.isScrolling = false;
                Menus.ResetIJ();
                Menus.ResetKL();
                Menus.ResetM();
                Route.isGrayBoxVisible = true;
                Miracles.isRainPrimed = true;
                Menus.isTownBuilderMenuVisible = false;
                Menus.isRainShowMeWhere = false;
            }
        }
        else if (Menus.isSunShowMeWhere)
        {
            if (Messages.IncrementIndex(Messages.SunShowMeWhere.Length))
            {
                Messages.IsMessageVisible = false;
                //Timers.isScrolling = false;
                Menus.ResetIJ();
                Menus.ResetKL();
                Menus.ResetM();
                Route.isGrayBoxVisible = true;
                Miracles.isSunlightPrimed = true;
                Menus.isTownBuilderMenuVisible = false;
                Menus.isSunShowMeWhere = false;
            }
        }
        else if (Timers.isScrollReblock)
        {
            Timers.ScrollUnblockReblock();
        }
        else if (Menus.isPaused
                 || Towns.townIndex == 7
                 || Menus.isStart)
        {
            return;
        }
        else if (Menus.isTownBuilderMenuVisible)
        {
            Menus.isTownBuilderMenuVisible = false;
        }
        else if (Menus.isSkyPalaceMenuVisible)
        {
            //Towns.GoToWorldMap();
            Towns.GoToNextWorld();
            Menus.isSkyPalaceMenuVisible = false;
        }
        else if (Route.isOhMessageVisible)
        {
            Route.isOhMessageVisible = false;
            Messages.IsMessageVisible = false;
        }
        else if (Menus.isReturnToOfferingsDecline)
        {
            Messages.IsMessageVisible = false;
            //Timers.isScrolling = false;
            Menus.isReturnToOfferings = false;
            Menus.isReturnToOfferingsDecline = false;
            Menus.isTownBuilderMenuVisible = false;
        }
        else if (Menus.isReturnToOfferings)
        {
            var isFound = false;
            for (var i = 0; i < 2; i++)
            {
                for (var j = 0; j < 4; j++)
                {
                    if (i == 1 && j == 3)
                    {
                        Menus.offeringIconsInInventory[i, j] = Menus.offeringIcons[0];
                        Menus.offeringDescriptionsInInventory[i, j] = Menus.offeringDescriptions[0];
                    }
                    else if (i == Menus.K && j == Menus.L)
                    {
                        if (i == 0 && j == 3)
                        {
                            Menus.offeringIconsInInventory[i, j] = Menus.offeringIconsInInventory[1, 0];
                            Menus.offeringDescriptionsInInventory[i, j] = Menus.offeringDescriptionsInInventory[1, 0];
                        }
                        else
                        {
                            Menus.offeringIconsInInventory[i, j] = Menus.offeringIconsInInventory[i, j + 1];
                            Menus.offeringDescriptionsInInventory[i, j] = Menus.offeringDescriptionsInInventory[i, j + 1];
                        }
                        isFound = true;
                    }
                    else if (isFound)
                    {
                        if (i == 0 && j == 3)
                        {
                            Menus.offeringIconsInInventory[i, j] = Menus.offeringIconsInInventory[1, 0];
                            Menus.offeringDescriptionsInInventory[i, j] = Menus.offeringDescriptionsInInventory[1, 0];
                        }
                        else
                        {
                            Menus.offeringIconsInInventory[i, j] = Menus.offeringIconsInInventory[i, j + 1];
                            Menus.offeringDescriptionsInInventory[i, j] = Menus.offeringDescriptionsInInventory[i, j + 1];
                        }
                    }
                    else
                    {
                    }
                }
            }
            Menus.offeringIndex--;
            Menus.takenIndex++;
        }
        else if (Menus.isReturnToWorldPromptVisible)
        {
            Menus.isReturnToWorldPromptVisible = false;
            Messages.IsMessageVisible = false;
            Route.isProgressLogFinished = true;
            Menus.ResetKL();
        }
        else if (Menus.isEnterPlayerNameMenuVisible)
        {
            if (Route.nameIndex > 0)
            {
                UpdatePlayerName();
                Route.nameIndex--;
                if (Route.nameIndex < 0)
                {
                    Route.nameIndex = 0;
                }
            }
        }
        else if (Route.isStatusOfMasterVisible)
        {
            Route.isStatusOfCitiesVisible = true;
            Route.isStatusOfMasterVisible = false;
        }
        else if (Route.isStatusOfCitiesVisible)
        {
            Menus.isSkyPalaceMenuVisible = true;
            Route.isStatusOfCitiesVisible = false;
        }
        else if (Route.isListeningToPeople)
        {
            Route.isListeningToPeople = false;
        }
        else if (Menus.isMessageSpeedConfirmationVisible)
        {
            Timers.scrollPeriod = Timers.scrollPeriodPrevious;
            Menus.isMessageSpeedConfirmationVisible = false;
            Messages.IsMessageVisible = false;
        }
        else if (Menus.isMessageSpeedMenuVisible)
        {
            Menus.isMessageSpeedMenuVisible = false;
            Route.isOhMessageVisible = true;
            Route.MessageTurnOn();
        }
        else if (Route.isMagicUnavailable)
        {
            Route.isMagicUnavailable = false;
            Messages.IsMessageVisible = false;
        }
        else if (isTownUninhabited)
        {
            isTownUninhabited = false;
            Messages.IsMessageVisible = false;
        }
        else if (Menus.isPreEnterName)
        {
            Route.PreEnterName();
        }
        else if (Menus.isProgressLogConfirmationVisible)
        {
            Menus.isProgressLogConfirmationVisible = false;
            Route.isOhMessageVisible = true;
            Menus.ResetKL();
        }
        else if (Route.isProgressLogFinished)
        {
            Messages.IsMessageVisible = false;
        }
        else if (Miracles.isLightningPrimed)
        {
            Miracles.lightningTimesSinceStartOfMiracle = -1.0f;
            Route.isGrayBoxVisible = false;
            Miracles.isLightningPrimed = false;
            Menus.isTownBuilderMenuVisible = false;
        }
        else if (Miracles.isRainPrimed)
        {
            Miracles.rainTimeSinceStartOfMiracle = -1.0f;
            Route.isGrayBoxVisible = false;
            Miracles.isRainPrimed = false;
            Menus.isTownBuilderMenuVisible = false;
        }
        else if (Miracles.isSunlightPrimed)
        {
            Miracles.sunlightTimeSinceStartOfMiracle = -1.0f;
            Route.isGrayBoxVisible = false;
            Miracles.isSunlightPrimed = false;
            Menus.isTownBuilderMenuVisible = false;
        }
        else if (Route.isRecordingYellowBoxPath)
        {
            Route.isTownUnderConstruction = false;
            Route.isRecordingYellowBoxPath = false;
            Player.previousI = (int)Route.yellowBoxPath[0].x;
            Player.previousJ = (int)Route.yellowBoxPath[0].y;
            Player.yellowBoxI = (int)Route.yellowBoxPath[0].x;
            Player.yellowBoxJ = (int)Route.yellowBoxPath[0].y;
            Route.yellowBoxPath = new Vector2[] {
                    new Vector2(-1, -1),
                    new Vector2(-1, -1),
                    new Vector2(-1, -1),
                    new Vector2(-1, -1),
                    new Vector2(-1, -1),
                    new Vector2(-1, -1),
                    new Vector2(-1, -1),
                    new Vector2(-1, -1)
                };
            Route.yellowBoxPathI = 0;
            Route.isGrayBoxVisible = false;
        }
        else if (Menus.isLightningYesNo
            || Menus.isRainYesNo
            || Menus.isSunYesNo
            || Menus.isWindYesNo
            || Menus.isEarthquakeYesNo)
        {
            //Timers.isScrolling = false;
            Menus.ResetIJ();
            Menus.ResetKL();
            Menus.ResetM();
            //Timers.isScrolling = false;
            Menus.isTownBuilderMenuVisible = false;
            Menus.isLightningYesNo = false;
        }
        else
        {
            if (!Player.isImmobilized)
            {
                if (Towns.directionText.Equals("^"))
                {
                    Towns.town[(int)Towns.Layers.EnemiesAndPlayer, Player.i - 1, Player.j] = 6;
                }
                else if (Towns.directionText.Equals("v"))
                {
                    Towns.town[(int)Towns.Layers.EnemiesAndPlayer, Player.i + 1, Player.j] = 7;
                }
                else if (Towns.directionText.Equals("<"))
                {
                    Towns.town[(int)Towns.Layers.EnemiesAndPlayer, Player.i, Player.j - 1] = 8;
                }
                else if (Towns.directionText.Equals(">"))
                {
                    Towns.town[(int)Towns.Layers.EnemiesAndPlayer, Player.i, Player.j + 1] = 9;
                }
            }
        }
    }

    public static void ControlPadStart()
    {
        if (Menus.isStart)
        {
            Route.StartGame();
            return;
        }
        // TODO: Remember that this must come before IsMessageVisible check.
        else if (Menus.isEnterPlayerNameMenuVisible)
        {
            UpdatePlayerName();
            Route.EnterNameEnd();
        }
        else if (Messages.IsMessageVisible)
        {
            return;
        }
        else if (Menus.IsInMenu(Messages.IsMessageVisible))
        {
        }
        else if (Menus.isPaused)
        {
            Menus.isPaused = false;
        }
        else if (!Menus.isPaused)
        {
            Menus.isPaused = true;
        }
    }

    private static void StartGame()
    {
        Route.MessageTurnOn();
        switch (Menus.J)
        {
            case (int)Menus.Start.Continue:
                Quests.is1stTutorialCompleted = true;
                Quests.is2ndTutorialCompleted = true;
                Quests.is3rdTutorialCompleted = true;
                Messages.IsMessageVisible = false;
                Messages.Index = 0;
                Player.level = LevelTables.healthPoints.Length - 1;
                Player.healthPoints = LevelTables.healthPoints[Player.level];
                Player.spellPoints = LevelTables.spellPoints[Player.level];
                Towns.populations[0] = 2;
                Menus.isSkyPalaceMenuVisible = false;
                //SaveGameData.intArray = GameLoader.LoadFromFile();
                Towns.isBossDefeated[0, 0] = true;
                Timers.isScrolling = false;
                break;
            case (int)Menus.Start.NewGame:
                SaveGame.SaveToFileMin(SaveGameData.intArray);
                Menus.isPreEnterName = true;
                break;
            case (int)Menus.Start.ProfessionalMode:
                Menus.offeringIsFound[(int)Menus.Offerings.Fillmore2StrengthOfAngel] = true;
                Menus.offeringIsFound[(int)Menus.Offerings.Fillmore1Bomb] = true;
                Menus.offeringIsFound[(int)Menus.Offerings.Fillmore6Bridge] = true;
                Menus.offeringIsFound[(int)Menus.Offerings.Fillmore3SourceOfMagic] = true;
                Menus.offeringIsFound[(int)Menus.Offerings.Fillmore7MagicalFire] = true;
                Menus.offeringIconsInInventory[0, 0] = Menus.offeringIcons[(int)Menus.Offerings.Fillmore2StrengthOfAngel];
                Menus.offeringIconsInInventory[0, 1] = Menus.offeringIcons[(int)Menus.Offerings.Fillmore1Bomb];
                Menus.offeringIconsInInventory[0, 2] = Menus.offeringIcons[(int)Menus.Offerings.Fillmore6Bridge];
                Menus.offeringIconsInInventory[0, 3] = Menus.offeringIcons[(int)Menus.Offerings.Fillmore3SourceOfMagic];
                Menus.offeringIconsInInventory[1, 0] = Menus.offeringIcons[(int)Menus.Offerings.Fillmore7MagicalFire];
                Menus.offeringIconsInInventory[1, 1] = Menus.offeringIcons[(int)Menus.Offerings.None];
                Menus.offeringIconsInInventory[1, 2] = Menus.offeringIcons[(int)Menus.Offerings.None];
                Menus.offeringIconsInInventory[1, 3] = Menus.offeringIcons[(int)Menus.Offerings.None];
                Menus.offeringDescriptionsInInventory[0, 0] = Menus.offeringDescriptions[(int)Menus.Offerings.Fillmore2StrengthOfAngel];
                Menus.offeringDescriptionsInInventory[0, 1] = Menus.offeringDescriptions[(int)Menus.Offerings.Fillmore1Bomb];
                Menus.offeringDescriptionsInInventory[0, 2] = Menus.offeringDescriptions[(int)Menus.Offerings.Fillmore6Bridge];
                Menus.offeringDescriptionsInInventory[0, 3] = Menus.offeringDescriptions[(int)Menus.Offerings.Fillmore3SourceOfMagic];
                Menus.offeringDescriptionsInInventory[1, 0] = Menus.offeringDescriptions[(int)Menus.Offerings.Fillmore7MagicalFire];
                Menus.offeringDescriptionsInInventory[1, 1] = Menus.offeringDescriptions[(int)Menus.Offerings.None];
                Menus.offeringDescriptionsInInventory[1, 2] = Menus.offeringDescriptions[(int)Menus.Offerings.None];
                Menus.offeringDescriptionsInInventory[1, 3] = Menus.offeringDescriptions[(int)Menus.Offerings.None];
                Menus.offeringIndex = 5;
                Quests.is1stTutorialCompleted = true;
                Quests.is2ndTutorialCompleted = true;
                Quests.is3rdTutorialCompleted = true;
                Messages.IsMessageVisible = false;
                Messages.Index = 0;
                Player.level = LevelTables.healthPoints.Length - 1;
                Player.healthPoints = LevelTables.healthPoints[Player.level];
                Player.spellPoints = LevelTables.spellPoints[Player.level];
                Towns.populations[0] = 2;
                Menus.isSkyPalaceMenuVisible = false;
                Timers.isScrolling = false;
                break;
        }
        Menus.ResetIJ();
        Menus.isStart = false;
    }

    public static void SpecificTown()
    {
        switch (Towns.townIndex)
        {
            case 0:
                Towns.town = Towns.fillmore;
                break;
            case 1:
                Towns.town = Towns.bloodpool;
                break;
            case 2:
                Towns.town = Towns.kasandora;
                break;
            case 3:
                Towns.town = Towns.aitos;
                break;
            case 4:
                Towns.town = Towns.marahna;
                break;
            case 5:
                Towns.town = Towns.northwall;
                break;
            case 6:
                Towns.town = Towns.deathHeim;
                break;
            case 7:
                Towns.town = Towns.worldMap;
                break;
        };
        for (var i = 0; i < 4; i++)
        {
            isMonsterAlive[i] = true;
        }
        Route.rowIndex = 0;
        Route.columnIndex = 0;
        for (var j = 0; j < Towns.SIZE; j++)
        {
            for (var k = 0; k < Towns.SIZE; k++)
            {
                if (Towns.town[(int)Towns.Layers.Building, j, k] == 111)
                {
                    Towns.denLocations[0, 0] = k;
                    Towns.denLocations[0, 1] = j;
                    monsterLocations[0, 0] = k;
                    monsterLocations[0, 1] = j;
                }
                else if (Towns.town[(int)Towns.Layers.Building, j, k] == 210)
                {
                    Towns.denLocations[1, 0] = k;
                    Towns.denLocations[1, 1] = j;
                    monsterLocations[1, 0] = k;
                    monsterLocations[1, 1] = j;
                }
                else if (Towns.town[(int)Towns.Layers.Building, j, k] == 310)
                {
                    Towns.denLocations[2, 0] = k;
                    Towns.denLocations[2, 1] = j;
                    monsterLocations[2, 0] = k;
                    monsterLocations[2, 1] = j;
                }
                else if (Towns.town[(int)Towns.Layers.Building, j, k] == 410)
                {
                    Towns.denLocations[3, 0] = k;
                    Towns.denLocations[3, 1] = j;
                    monsterLocations[3, 0] = k;
                    monsterLocations[3, 1] = j;
                }
                else if (Towns.town[(int)Towns.Layers.Building, j, k] == 115)
                {
                    Towns.denLocations[0, 0] = k;
                    Towns.denLocations[0, 1] = j;
                    monsterLocations[0, 0] = k;
                    monsterLocations[0, 1] = j;
                }
                else if (Towns.town[(int)Towns.Layers.Building, j, k] == 215)
                {
                    Towns.denLocations[1, 0] = k;
                    Towns.denLocations[1, 1] = j;
                    monsterLocations[1, 0] = k;
                    monsterLocations[1, 1] = j;
                }
                else if (Towns.town[(int)Towns.Layers.Building, j, k] == 315)
                {
                    Towns.denLocations[2, 0] = k;
                    Towns.denLocations[2, 1] = j;
                    monsterLocations[2, 0] = k;
                    monsterLocations[2, 1] = j;
                }
                else if (Towns.town[(int)Towns.Layers.Building, j, k] == 415)
                {
                    Towns.denLocations[3, 0] = k;
                    Towns.denLocations[3, 1] = j;
                    monsterLocations[3, 0] = k;
                    monsterLocations[3, 1] = j;
                }
            }
        }
    }

    public static int[,] peopleLocations = new int[,] {
        { 0, 0 },
        { 0, 0 },
        { 0, 0 },
        { 0, 0 }
    };
    public static int denIndex;
    public static void AllTiles()
    {
        Route.rowIndex = 0;
        Route.columnIndex = 0;
        for (var j = 0; j < Towns.SIZE; j++)
        {
            for (var k = 0; k < Towns.SIZE; k++)
            {
                if (Towns.town[(int)Towns.Layers.People, j, k] > 0)
                {
                }
            }
        }
    }

    public static void CameraSquare()
    {
        for (var j = RevealedTerrain.y; j < RevealedTerrain.bottom; j++)
        {
            for (var k = RevealedTerrain.x; k < RevealedTerrain.right; k++)
            {
                switch (Towns.town[(int)Towns.Layers.BuildingModifier, j, k])
                {
                    case (int)Towns.BuildingModifiers.Nothing:
                        break;
                }
                switch (Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k])
                {
                    case (int)Towns.EnemiesAndPlayers.Nothing:
                        break;
                    case (int)Towns.EnemiesAndPlayers.Player:
                        if (Towns.previousDirection[0])
                        {
                            Towns.directionText = "^";
                        }
                        else if (Towns.previousDirection[1])
                        {
                            Towns.directionText = "v";
                        }
                        else if (Towns.previousDirection[2])
                        {
                            Towns.directionText = "<";
                        }
                        else if (Towns.previousDirection[3])
                        {
                            Towns.directionText = ">";
                        }
                        break;
                    /*
                    case (int)Towns.EnemiesAndPlayers.Lightning:
                        if (Towns.town[(int)Towns.Layers.Land, j, k] == 6
                            || Towns.town[(int)Towns.Layers.Land, j, k] == 9)
                        {
                            Towns.town[(int)Towns.Layers.Land, j, k] = 2;
                            Towns.town[(int)Towns.Layers.LandModifier, j, k] = 4;
                        }
                        if (Towns.town[(int)Towns.Layers.Land, j, k] != 1
                            && Towns.town[(int)Towns.Layers.Land, j, k] != 3
                            && Towns.town[(int)Towns.Layers.Land, j, k] != 4
                            && Towns.town[(int)Towns.Layers.Land, j, k] != 5
                            && Towns.town[(int)Towns.Layers.Land, j, k] != 8
                            && Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k] < 24)
                        {
                            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, j, k] = 0;
                            Towns.town[(int)Towns.Layers.People, j, k] = 0;
                        }
                        break;
                    */
                    case (int)Towns.EnemiesAndPlayers.Rain:
                        break;
                    case (int)Towns.EnemiesAndPlayers.Sunlight:
                        break;
                    case (int)Towns.EnemiesAndPlayers.Wind:
                        break;
                    case (int)Towns.EnemiesAndPlayers.Earthquake:
                        break;
                }
                Route.columnIndex++;
            }
            Route.columnIndex = 0;
            Route.rowIndex++;
        }
    }

    public static int columnIndex;
    public static int rowIndex;
    public static void FourByFour()
    {
        rowIndex = 0;
        columnIndex = 0;
        Player.ResetIJ();
        for (var j = 1; j < 9; j++)
        {
            for (var i = 1; i < 9; i++)
            {
                if (Player.j >= Player.previousJ * 4 && Player.j < j * 4)
                {
                    Player.tempJ = Player.previousJ;
                }
                if (Player.i >= Player.previousI * 4 && Player.i < i * 4)
                {
                    Player.tempI = Player.previousI;
                }
                Player.previousJ = j;
                Player.previousI = i;
            }
        }
    }

    public const int YELLOW_BOX_PATH_MAX = 8;
    public static string[] yellowBoxDirections = new string[] {
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        ""
    };
    public static Vector2[] yellowBoxPath = new Vector2[] {
            new Vector2(Player.yellowBoxI, Player.yellowBoxJ),
            new Vector2(-1, -1),
            new Vector2(-1, -1),
            new Vector2(-1, -1),
            new Vector2(-1, -1),
            new Vector2(-1, -1),
            new Vector2(-1, -1),
            new Vector2(-1, -1)
    };
    public static int yellowBoxPathI;
    public static bool isRecordingYellowBoxPath;
    public static void GrayBox()
    {
        if (Player.tempI == -1
            || Player.tempJ == -1)
        {
        }
        else
        {
            if (Route.isGrayBoxVisible)
            {
                Timers.Reset();
                //Timers.isScrolling = false;
                Messages.IsMessageVisible = false;
                if (isRecordingYellowBoxPath)
                {
                    if (yellowBoxPathI == 0)
                    {
                        yellowBoxPath[yellowBoxPathI] = new Vector2(Player.tempJ, Player.tempI);
                        yellowBoxDirections[yellowBoxPathI] = Towns.directionText;
                        yellowBoxPathI++;
                    }
                    else if (Player.tempJ != yellowBoxPath[yellowBoxPathI - 1].x
                             || Player.tempI != yellowBoxPath[yellowBoxPathI - 1].y)
                    {
                        for (var i = 0; i < 4; i++)
                        {
                            for (var j = 0; j < 4; j++)
                            {
                                if (Towns.town[(int)Towns.Layers.Land, (Player.tempI * 4) + i, (Player.tempJ * 4) + j] == 6)
                                {
                                    if (Towns.previousDirection[0])
                                    {
                                        Route.MoveDown();
                                    }
                                    else if (Towns.previousDirection[1])
                                    {
                                        Route.MoveUp();
                                    }
                                    else if (Towns.previousDirection[2])
                                    {
                                        Route.MoveRight();
                                    }
                                    else if (Towns.previousDirection[3])
                                    {
                                        Route.MoveLeft();
                                    }
                                    return;
                                }
                            }
                        }
                        yellowBoxPath[yellowBoxPathI] = new Vector2(Player.tempJ, Player.tempI);
                        yellowBoxDirections[yellowBoxPathI] = Towns.directionText;
                        yellowBoxPathI++;
                        if (yellowBoxPathI > YELLOW_BOX_PATH_MAX - 1)
                        {
                            yellowBoxPathI = 0;
                            isRecordingYellowBoxPath = false;
                            Route.isGrayBoxVisible = false;
                        }
                    }
                }
                Player.grayBoxI = Player.tempI;
                Player.grayBoxJ = Player.tempJ;
            }
        }
    }

    public static void ResetToYellowBoxStart()
    {
        resetToYellowBoxTimeSinceStartOfPeriod = 0.0f;
        isResettingToYellowBox = true;
    }
    public static float yellowBoxI;
    public static float yellowBoxJ;
    public static void YellowBox()
    {
        Player.tempI = (Player.yellowBoxI * 4) + Player.offsetX;
        Player.tempJ = (Player.yellowBoxJ * 4) + Player.offsetY;
        if (Timers.isBoxYellowVisible
            && Towns.townIndex != 7)
        {
        }
    }

    public static float[] populationTimeSinceStartOfRound = new float[Towns.TOWN_COUNT];
    public static bool isStatusOfCitiesVisible;
    public static bool isStatusOfMasterVisible;
    public static bool isGrayBoxVisible;
    public static bool isColumnZeroMessageVisible;
    public static bool isGoingToFight;
    public static bool isOhMessageVisible;
    public static bool isProgressLogFinished;
    public static bool isMagicUnavailable;
    public static bool isQuittingGame;
    public static bool isTownUninhabited;
    public static bool isListeningToPeople;
    public static bool isMagicMenuVisible;
    public static bool isTownUnderConstruction;
    public static void DrawButtonsBasedOnBools()
    {

        if (Menus.isStart
            || Menus.isSkyPalaceMenuVisible
            || Menus.isPreEnterName
            || Menus.isEnterPlayerNameMenuVisible
            || Menus.isPostEnterName)
        {
        }
        if (!Menus.isStart
            && !Menus.isSkyPalaceMenuVisible
            && Towns.townIndex != 7)
        {
        }
        if (isStatusOfMasterVisible)
        {
        }
        else if (isStatusOfCitiesVisible)
        {
        }
        else if (Menus.isTownBuilderMenuVisible)
        {
            if (isColumnZeroMessageVisible)
            {
                Route.MessageDescription(Messages.ColumnZero[Messages.Index]);
            }
            else if (isOhMessageVisible)
            {
                Route.MessageDescription(Messages.Oh[Messages.Index]);
            }
            else if (Menus.isUseAnOffering)
            {
                Route.MessageDescription(Messages.UseOffering[Messages.Index]);
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
                Route.MessageDescription(Messages.MessageSpeed[Messages.Index]);
            }
            else if (Menus.isMessageSpeedConfirmationVisible)
            {
                Route.MessageDescription(Messages.MessageSpeedLikeThis[Messages.Index]);
            }
            else if (Menus.isReturnToWorldPromptVisible)
            {
                Route.MessageDescription(Messages.ProgressLogComplete[Messages.Index]);
            }
            else if (isProgressLogFinished)
            {
                Route.MessageDescription(Messages.ProgressLogContinue[Messages.Index]);
            }
            else if (isQuittingGame)
            {
                Route.MessageDescription(Messages.Quitting[Messages.Index]);
            }
            else if (Menus.isLightningAvailable)
            {
                Route.MessageDescription(Messages.LightningAvailable[Messages.Index]);
            }
            else if (Menus.isLightningUnavailable)
            {
                Route.MessageDescription(Messages.LightningUnavailable[Messages.Index]);
            }
            else if (Menus.isLightningYesNo)
            {
                Route.MessageDescription(Messages.LightningYesNo[Messages.Index]);
            }
            else if (Menus.isLightningShowMeWhere)
            {
                Route.MessageDescription(Messages.LightningShowMeWhere[Messages.Index]);
            }
            else if (Menus.isRainAvailable)
            {
                Route.MessageDescription(Messages.RainAvailable[Messages.Index]);
            }
            else if (Menus.isRainUnavailable)
            {
                Route.MessageDescription(Messages.RainUnavailable[Messages.Index]);
            }
            else if (Menus.isRainYesNo)
            {
                Route.MessageDescription(Messages.RainYesNo[Messages.Index]);
            }
            else if (Menus.isRainShowMeWhere)
            {
                Route.MessageDescription(Messages.RainShowMeWhere[Messages.Index]);
            }
            else if (Menus.isSunAvailable)
            {
                Route.MessageDescription(Messages.SunAvailable[Messages.Index]);
            }
            else if (Menus.isSunUnavailable)
            {
                Route.MessageDescription(Messages.SunUnavailable[Messages.Index]);
            }
            else if (Menus.isSunYesNo)
            {
                Route.MessageDescription(Messages.SunYesNo[Messages.Index]);
            }
            else if (Menus.isSunShowMeWhere)
            {
                Route.MessageDescription(Messages.SunShowMeWhere[Messages.Index]);
            }
            else if (Menus.isWindAvailable)
            {
                Route.MessageDescription(Messages.WindAvailable[Messages.Index]);
            }
            else if (Menus.isWindUnavailable)
            {
                Route.MessageDescription(Messages.WindUnavailable[Messages.Index]);
            }
            else if (Menus.isWindYesNo)
            {
                Route.MessageDescription(Messages.WindYesNo[Messages.Index]);
            }
            //else if (Menus.isWindShowMeWhere)
            //{
            //    Route.MessageDescription(Messages.WindShowMeWhere[Messages.Index]);
            //}
            else if (Menus.isEarthquakeAvailable)
            {
                Route.MessageDescription(Messages.EarthquakeAvailable[Messages.Index]);
            }
            else if (Menus.isEarthquakeUnavailable)
            {
                Route.MessageDescription(Messages.EarthquakeUnavailable[Messages.Index]);
            }
            else if (Menus.isEarthquakeYesNo)
            {
                Route.MessageDescription(Messages.EarthquakeYesNo[Messages.Index]);
            }
            //else if (Menus.isEarthquakeShowMeWhere)
            //{
            //    Route.MessageDescription(Messages.EarthquakeShowMeWhere[Messages.Index]);
            //}
            else
            {
                Route.MessageDescription("");
            }
            if (Menus.isProgressLogConfirmationVisible)
            {
                Route.MessageDescription(Messages.ProgressLogConfirmation[Messages.Index]);
            }
            else if (Menus.isReturnToWorldPromptVisible)
            {
            }
        }
        else if (Towns.townIndex == 7)
        {
        }
        else if (Menus.isSkyPalaceMenuVisible)
        {
            for (var i = 0; i < 4; i++)
            {
                for (var j = 0; j < 3; j++)
                {
                    var result = false;
                    if (i == Menus.I)
                    {
                        result = true;
                    }
                    else if (i != Menus.I && j == 0)
                    {
                        result = true;
                    }
                    if (result)
                    {
                    }
                }
            }
            if (Menus.isProgressLogConfirmationVisible)
            {
                Route.MessageDescription(Messages.ProgressLogConfirmation[Messages.Index]);
            }
            else if (Menus.isReturnToWorldPromptVisible)
            {
                Route.MessageDescription(Messages.ProgressLogComplete[Messages.Index]);
            }
            else if (isColumnZeroMessageVisible)
            {
                Route.MessageDescription(Messages.ColumnZero[Messages.Index]);
            }
            else if (isGoingToFight)
            {
                Route.MessageDescription(Messages.GoingToFight[Messages.Index]);
            }
            else if (isOhMessageVisible)
            {
                Route.MessageDescription(Messages.Oh[Messages.Index]);
            }
            else if (Menus.isMessageSpeedMenuVisible)
            {
                Route.MessageDescription(Messages.MessageSpeed[Messages.Index]);
            }
            else if (Menus.isMessageSpeedConfirmationVisible)
            {
                Route.MessageDescription(Messages.MessageSpeedLikeThis[Messages.Index]);
            }
            else if (Menus.isReturnToWorldPromptVisible)
            {
                Route.MessageDescription(Messages.ProgressLogComplete[Messages.Index]);
            }
            else if (isProgressLogFinished)
            {
                Route.MessageDescription(Messages.ProgressLogContinue[Messages.Index]);
            }
            else if (isQuittingGame)
            {
                Route.MessageDescription(Messages.Quitting[Messages.Index]);
            }
            else
            {
                Route.MessageDescription("");
            }
        }
        else if (isListeningToPeople)
        {
            Route.MessageDescription(Messages.ListenToThePeople[Messages.Index]);
        }
        else if (Menus.isEnterPlayerNameMenuVisible)
        {
        }
        else if (Menus.isPreEnterName)
        {
            Route.MessageDescription(Messages.EnterPlayerNamePre[Messages.Index]);
        }
        else if (Menus.isPostEnterName)
        {
            Route.MessageDescription(Messages.EnterPlayerNamePost[Messages.Index]);
        }
        else if (isMagicUnavailable)
        {
            Route.MessageDescription(Messages.MagicUnavailable[Messages.Index]);
        }
        else if (isTownUninhabited)
        {
            Route.MessageDescription(Messages.TownIsUninhabitable[Messages.Index]);
        }
        else if (!Quests.is1stTutorialCompleted)
        {
            Route.MessageDescription(Messages.Quest1[Messages.Index]);
        }
        else if (!Quests.is2ndTutorialCompleted)
        {
            Route.MessageDescription(Messages.Quest2[Messages.Index]);
        }
        else if (!Quests.is3rdTutorialCompleted)
        {
            Route.MessageDescription(Messages.Quest3[Messages.Index]);
        }
        else if (Quests.is4thTutorialReady
                 && !Quests.is4thTutorialCompleted)
        {
            Route.MessageDescription(Messages.Quest4[Messages.Index]);
        }
        else if (Menus.isReturnToOfferingsDecline)
        {
            Route.TakeAnOfferingScrollDecline();
        }
        else if (Menus.isTakeAnOffering)
        {
            if (Menus.offeringIndex == 0)
            {
                Route.MessageDescription(Messages.TakeFailure[Messages.Index]);
            }
            else
            {
                Route.MessageDescription(Messages.TakeSuccess[Messages.Index]);
            }
        }
        else if (Menus.isTakeAnOfferingConfirmation)
        {
            Route.TakeAnOfferingScroll();
        }
        else if (Menus.isReturnToOfferings)
        {
            Route.MessageDescription(Messages.TakeConfirmation[Messages.Index]);
        }
        else if (Menus.isLightningSuccess)
        {
            // Empty.
        }
        else if (Menus.isLightningFailure)
        {
            Route.MessageDescription(Messages.MiracleFailure[Messages.Index]);
        }
        else if (Menus.isRainSuccess)
        {
            // Empty.
        }
        else if (Menus.isRainFailure)
        {
            Route.MessageDescription(Messages.MiracleFailure[Messages.Index]);
        }
        else if (Menus.isSunSuccess)
        {
            // Empty.
        }
        else if (Menus.isSunFailure)
        {
            Route.MessageDescription(Messages.MiracleFailure[Messages.Index]);
        }
        else if (Menus.isWindAvailable)
        {
            // Empty.
        }
        else if (Menus.isWindFailure)
        {
            Route.MessageDescription(Messages.MiracleFailure[Messages.Index]);
        }
        else if (Menus.isEarthquakeAvailable)
        {
            // Empty.
        }
        else if (Menus.isEarthquakeFailure)
        {
            Route.MessageDescription(Messages.MiracleFailure[Messages.Index]);
        }
        if (isMagicMenuVisible)
        {
        }
        if (Menus.isUseAnOffering)
        {
            Route.UseAnOfferingScroll();
        }
        if (isTownUnderConstruction)
        {
        }
    }

    // (Special Menu) Take An Offering
    public static void TakeAnOffering()
    {
        Menus.isTakeAnOffering = true;
        MessageTurnOn();
    }
    public static void TakeAnOfferingControlPadBAccept()
    {
        var k = 0;
        var l = Menus.takenIndex;
        var result = false;
        if (l > 3)
        {
            k = 1;
            l -= 4;
        }
        // Remember that these route to 3 possible places:
        //   1. Move to 'Taken Items' array.
        //   2. Unlock one of the four magics.
        //   3. Increase the 'Source of Magic' couonter.
        if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "bmb")
        {
            if (Messages.IncrementIndex(Messages.TakeBomb.Length))
            {
                result = true;
                Menus.takenIcons[k, l] = "bmb";
                Menus.takenDescriptions[k, l] = "Bomb!";
            }
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "soa")
        {
            if (Messages.IncrementIndex(Messages.TakeStrengthOfAngel.Length))
            {
                result = true;
                Menus.takenIcons[k, l] = "soa";
                Menus.takenDescriptions[k, l] = "Strength of Angel";
            }
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "som")
        {
            if (Messages.IncrementIndex(Messages.TakeSourceOfMagic.Length))
            {
                result = true;
                Player.SourceOfMagicIncrease();
            }
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "sol")
        {
            Menus.takenIcons[k, l] = "sol";
            Menus.takenDescriptions[k, l] = "Source of Life";
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "bdg")
        {
            if (Messages.IncrementIndex(Messages.TakeBridge.Length))
            {
                result = true;
                Menus.takenIcons[k, l] = "bdg";
                Menus.takenDescriptions[k, l] = "Bridge";
            }
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "fir")
        {
            if (Messages.IncrementIndex(Messages.TakeMagicalFire.Length))
            {
                result = true;
                Magics.isMagicalFireUnlockled = true;
            }
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "wht")
        {
            Menus.takenIcons[k, l] = "wht";
            Menus.takenDescriptions[k, l] = "Wheet";
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "brd")
        {
            Menus.takenIcons[k, l] = "brd";
            Menus.takenDescriptions[k, l] = "Loaf of Bread";
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "skl")
        {
            Menus.takenIcons[k, l] = "skl";
            Menus.takenDescriptions[k, l] = "Magic Skull";
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "cps")
        {
            Menus.takenIcons[k, l] = "cps";
            Menus.takenDescriptions[k, l] = "Compass";
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "dst")
        {
            Menus.takenIcons[k, l] = "Magical Stardust";
            Menus.takenDescriptions[k, l] = "dst";
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "tbt")
        {
            Menus.takenIcons[k, l] = "Ancient Tablet";
            Menus.takenDescriptions[k, l] = "tbt";
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "msc")
        {
            Menus.takenIcons[k, l] = "msc";
            Menus.takenDescriptions[k, l] = "Harmonious Music";
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "flc")
        {
            Menus.takenIcons[k, l] = "flc";
            Menus.takenDescriptions[k, l] = "Fleece";
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "hrb")
        {
            Menus.takenIcons[k, l] = "hrb";
            Menus.takenDescriptions[k, l] = "Herb";
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "aur")
        {
            Menus.takenIcons[k, l] = "aur";
            Menus.takenDescriptions[k, l] = "Magical Aura";
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "lgt")
        {
            Menus.takenIcons[k, l] = "lgt";
            Menus.takenDescriptions[k, l] = "Magical Light";
        }
        if (result)
        {
            Menus.isReturnToOfferings = true;
            Menus.isTakeAnOfferingConfirmation = false;
        }
    }
    public static void TakeAnOfferingControlPadBDecline()
    {
        if (Messages.IncrementIndex(Messages.TakeDecline.Length))
        {
            Menus.isTakeAnOfferingConfirmation = false;
            Menus.isReturnToOfferingsDecline = true;
        }
    }
    public static void TakeAnOfferingScroll()
    {
        var k = 0;
        var l = Menus.takenIndex;
        if (l > 3)
        {
            k = 1;
            l -= 4;
        }
        if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "bmb")
        {
            MessageDescription(Messages.TakeBomb[Messages.Index]);
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "soa")
        {
            MessageDescription(Messages.TakeStrengthOfAngel[Messages.Index]);
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "som")
        {
            MessageDescription(Messages.TakeSourceOfMagic[Messages.Index]);
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "sol")
        {
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "bdg")
        {
            MessageDescription(Messages.TakeBridge[Messages.Index]);
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "fir")
        {
            MessageDescription(Messages.TakeMagicalFire[Messages.Index]);
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "wht")
        {
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "brd")
        {
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "skl")
        {
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "cps")
        {
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "dst")
        {
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "tbt")
        {
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "msc")
        {
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "flc")
        {
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "hrb")
        {
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "aur")
        {
        }
        else if (Menus.offeringIconsInInventory[Menus.K, Menus.L] == "lgt")
        {
        }
    }
    public static void TakeAnOfferingScrollDecline()
    {
        MessageDescription(Messages.TakeDecline[Messages.Index]);
    }

    public static void UseAnOfferingControlPadBAccept()
    {
        var k = 0;
        var l = Menus.takenIndex;
        var result = false;
        if (l > 3)
        {
            k = 1;
            l -= 4;
        }
        // Remember that these route to 3 possible places:
        //   1. Move to 'Taken Items' array.
        //   2. Unlock one of the four magics.
        //   3. Increase the 'Source of Magic' couonter.
        if (Menus.takenIcons[Menus.K, Menus.L] == "bmb")
        {
            // Use Bomb
            result = true;
            for (var j = 0; j < Towns.SIZE; j++)
            {
                for (var i = 0; i < Towns.SIZE; i++)
                {
                    if (Towns.town[(int)Towns.Layers.EnemiesAndPlayer, i, j] >= 2
                        && Towns.town[(int)Towns.Layers.EnemiesAndPlayer, i, j] <= 5)
                    {
                        Towns.town[(int)Towns.Layers.EnemiesAndPlayer, i, j] = 0;
                    }
                    if (Towns.town[(int)Towns.Layers.Building, i, j] >= 1
                        && Towns.town[(int)Towns.Layers.Building, i, j] <= 9)
                    {
                        Towns.town[(int)Towns.Layers.Building, i, j] = 0;
                    }
                }
            }
            Menus.isTownBuilderMenuVisible = false;
            Menus.isUseAnOffering = false;
            Menus.isUseAnOfferingDescription = true;
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "soa")
        {
            if (Messages.IncrementIndex(Messages.UseStrengthOfAngel.Length))
            {
                Player.isStrengthOfAngelActive = true;
                result = true;
                Menus.isUseAnOffering = false;
                Menus.isUseAnOfferingDescription = true;
            }
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "som")
        {
            // Something.
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "sol")
        {
            // Not applicable.
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "bdg")
        {
            if (Messages.IncrementIndex(Messages.TakeBridge.Length))
            {
                result = true;
                Menus.isUseAnOffering = false;
                Menus.isUseAnOfferingDescription = true;
            }
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "fir")
        {
            // Not applicable.
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "wht")
        {
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "brd")
        {
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "skl")
        {
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "cps")
        {
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "dst")
        {
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "tbt")
        {
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "msc")
        {
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "flc")
        {
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "hrb")
        {
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "aur")
        {
        }
        else if (Menus.takenIcons[Menus.K, Menus.L] == "lgt")
        {
        }
        if (result)
        {
        }
    }
    public static void UseAnOfferingScroll()
    {
        MessageDescription(Messages.UseOffering[Messages.Index]);
    }

    // (Special Menu) Message Speed
    public static void MessageSpeed()
    {
        Menus.isMessageSpeedMenuVisible = true;
        MessageTurnOn();
    }
    public static void SetTextSpeedFromIntArray()
    {
        Timers.scrollPeriod = SaveGameData.intArray[1] * 0.1f;
    }

    // (Special Menu) Progress Log
    public static void ProgressLog()
    {
        Menus.isProgressLogConfirmationVisible = true;
        MessageTurnOn();
    }

    // Message At Bottom Of Screen
    public static void MessageDescription(string text)
    {
        messageText = text;
        Descriptions.messageMenuText = text;
    }
    public static void MessageTurnOn()
    {
        Timers.isScrolling = true;
        Messages.IsMessageVisible = true;
        Timers.Reset();
    }

    public static void MoveUp(bool forcePush = false)
    {
        if (Menus.isPaused
            || Menus.Up(IsBlocked)
            || (Timers.DebounceStart() && !forcePush))
        {
            return;
        }
        Towns.previousDirection = Towns.directionUp;
        var isEnemy = IsEnemy(Player.i - 1, Player.j);
        if (isEnemy)
        {
            Player.HealthPointsDecrease();
        }
        if (Towns.townIndex != 7 && Player.i > 27)
        {
            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, Player.i, Player.j] = 0;
            Player.i--;
            if (Player.i < 0)
            {
                Player.i = 0;
            }
            if (isEnemy)
            {
                Player.i -= FindFreeTileAbove();
            }
            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, Player.i, Player.j] = 1;
        }
        else
        {
            (Player.offsetY, Player.i, Player.j)
                = RevealedTerrain.DecrementY(
                    Player.offsetY,
                    Player.i,
                    Player.j,
                    isEnemy);
        }
    }
    public static void MoveDown(bool forcePush = false)
    {
        if (Menus.isPaused
            || Menus.Down(IsBlocked)
            || (Timers.DebounceStart() && !forcePush))
        {
            return;
        }
        Towns.previousDirection = Towns.directionDown;
        var isEnemy = IsEnemy(Player.i + 1, Player.j);
        if (isEnemy)
        {
            Player.HealthPointsDecrease();
        }
        if (Towns.townIndex != 7 && Player.i < Player.I_DEFAULT)
        {
            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, Player.i, Player.j] = 0;
            Player.i++;
            if (Player.i > 32)
            {
                Player.i = 32;
            }
            if (isEnemy)
            {
                Player.i -= FindFreeTileAbove();
            }
            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, Player.i, Player.j] = 1;
        }
        else
        {
            (Player.offsetY, Player.i, Player.j)
                = RevealedTerrain.IncrementY(
                    Player.offsetY,
                    Player.i,
                    Player.j,
                    isEnemy);
        }
    }
    public static void MoveLeft(bool forcePush = false)
    {
        if (Menus.isPaused
            || Menus.Left(IsBlocked)
            || (Timers.DebounceStart() && !forcePush))
        {
            return;
        }
        //print("HERE");
        Towns.previousDirection = Towns.directionLeft;
        var isEnemy = IsEnemy(Player.i, Player.j - 1);
        if (isEnemy)
        {
            Player.HealthPointsDecrease();
        }
        if (Towns.townIndex != 7 && Player.j > 23)
        {
            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, Player.i, Player.j] = 0;
            Player.j--;
            if (Player.j < 0)
            {
                Player.j = 0;
            }
            if (isEnemy)
            {
                Player.i -= FindFreeTileAbove();
            }
            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, Player.i, Player.j] = 1;
        }
        else
        {
            (Player.offsetX, Player.i, Player.j)
                = RevealedTerrain.DecrementX(
                    Player.offsetX,
                    Player.i,
                    Player.j,
                    isEnemy);
        }
    }
    public static void MoveRight(bool forcePush = false)
    {
        if (Menus.isPaused
            || Menus.Right(IsBlocked)
            || (Timers.DebounceStart() && !forcePush))
        {
            return;
        }
        Towns.previousDirection = Towns.directionRight;
        var isEnemy = IsEnemy(Player.i, Player.j + 1);
        if (isEnemy)
        {
            Player.HealthPointsDecrease();
        }
        if (Towns.townIndex != 7 && Player.j < 6)
        {
            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, Player.i, Player.j] = 0;
            Player.j++;
            if (Player.j >= 31)
            {
                Player.j = 31;
            }
            if (isEnemy)
            {
                Player.i -= FindFreeTileAbove();
            }
            Towns.town[(int)Towns.Layers.EnemiesAndPlayer, Player.i, Player.j] = 1;
        }
        else
        {
            (Player.offsetX, Player.i, Player.j)
                = RevealedTerrain.IncrementX(
                    Player.offsetX,
                    Player.i,
                    Player.j,
                    isEnemy);
        }
    }

    // Enter Name (Plus Pre & Post)
    public static void PreEnterName()
    {
        if (Messages.IncrementIndex(Messages.EnterPlayerNamePre.Length))
        {
            Timers.ScrollStop();
            Menus.isEnterPlayerNameMenuVisible = true;
            Menus.isPreEnterName = false;
            Menus.ResetKL();
        }
    }
    public static void EnterNameEnd()
    {
        Menus.isPostEnterName = true;
        Timers.Reset();
        Menus.isEnterPlayerNameMenuVisible = false;
        Menus.ResetKL();
    }
    public static void PostEnterName()
    {
        if (Messages.IncrementIndex(Messages.EnterPlayerNamePost.Length))
        {
            Messages.IsMessageVisible = false;
            Menus.isSkyPalaceMenuVisible = true;
            Menus.isPostEnterName = false;
        }
    }

    // Tile Utilities
    public static int FindFreeTileAbove()
    {
        var counter = 1;
        while (IsEnemy(Player.i - counter, Player.j))
        {
            counter++;
        }
        return counter;
    }
    public static bool IsEnemy(int i, int j)
    {
        try
        {
            var result = false;
            if (Towns.town[(int)Towns.Layers.EnemiesAndPlayer, i, j] == 111
                || Towns.town[(int)Towns.Layers.EnemiesAndPlayer, i, j] == 211
                || Towns.town[(int)Towns.Layers.EnemiesAndPlayer, i, j] == 311
                || Towns.town[(int)Towns.Layers.EnemiesAndPlayer, i, j] == 411
                || Towns.town[(int)Towns.Layers.EnemiesAndPlayer, i, j] == 115
                || Towns.town[(int)Towns.Layers.EnemiesAndPlayer, i, j] == 215
                || Towns.town[(int)Towns.Layers.EnemiesAndPlayer, i, j] == 315
                || Towns.town[(int)Towns.Layers.EnemiesAndPlayer, i, j] == 415)
            {
                result = true;
            }
            return result;
        }
        catch (System.Exception e)
        {
            return false;
        }
    }

    private static void UpdatePlayerName()
    {
        StringBuilder sb = new StringBuilder();
        for (var i = 0; i < 8; i++)
        {
            if (i < nameIndex)
            {
                sb.Append(Messages.PlayerName[i]);
            }
            else if (i == nameIndex)
            {
                sb.Append(Menus.enterPlayerName[Menus.L, Menus.K]);
            }
            else if (i > nameIndex)
            {
                sb.Append("");
            }
        }
        Messages.PlayerName = sb.ToString();
    }
}
