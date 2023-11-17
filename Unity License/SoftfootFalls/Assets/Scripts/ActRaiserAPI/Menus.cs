using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Menus : MonoBehaviour
{
    public enum Start
    {
        Continue,
        NewGame,
        ProfessionalMode
    }
    public static bool isStart = true;

    public static bool isPreEnterName;
    public static bool isEnterPlayerNameMenuVisible;
    public static bool isPostEnterName;

    public static bool isMessageSpeedConfirmationVisible;
    public static bool isMessageSpeedMenuVisible;
    public static bool isPaused;
    public static bool isProgressLogConfirmationVisible;
    public static bool isReturnToWorldPromptVisible;
    public static bool isSkyPalaceMenuVisible;
    public static bool isTownBuilderMenuVisible;

    public static bool isTakeAnOffering;
    public static bool isTakeAnOfferingConfirmation;
    public static bool isTakeAnOfferingDecline;
    public static bool isReturnToOfferings;
    public static bool isReturnToOfferingsDecline;
    public static bool isUseAnOffering;
    public static bool isUseAnOfferingDescription;
    public static bool isLightningAvailable;
    public static bool isLightningUnavailable;
    public static bool isLightningYesNo;
    public static bool isLightningSuccess;
    public static bool isLightningFailure;
    public static bool isLightningShowMeWhere;
    public static bool isRainAvailable;
    public static bool isRainUnavailable;
    public static bool isRainYesNo;
    public static bool isRainSuccess;
    public static bool isRainFailure;
    public static bool isRainShowMeWhere;
    public static bool isSunAvailable;
    public static bool isSunUnavailable;
    public static bool isSunYesNo;
    public static bool isSunSuccess;
    public static bool isSunFailure;
    public static bool isSunShowMeWhere;
    public static bool isWindAvailable;
    public static bool isWindUnavailable;
    public static bool isWindYesNo;
    public static bool isWindSuccess;
    public static bool isWindFailure;
    public static bool isEarthquakeAvailable;
    public static bool isEarthquakeUnavailable;
    public static bool isEarthquakeYesNo;
    public static bool isEarthquakeSuccess;
    public static bool isEarthquakeFailure;

    public static string[,] skyPalaceIcons = new string[,] {
        { "\n<=>", "||||\n",      "v\n" },
        { "\n/*/", "\n(       )", "\n|~~|" },
        { "<B",    "/-)",         "[^^]" },
        { "I/O",   "//",          "=>" }
    };

    public const int MENU_GRID_SIZE = 6;
    public static string[,] townBuilderIcons = new string[,]{
        { "\n<=>",  "\n|__|",  "||||\n", "",      "",      ""      },
        { "1\n***", "\n===",   "2\n***", "",      "",      ""      },
        { "/./",    "! ! !\n", "@ @\n",  "# #\n", "$ $\n", "% %\n" },
        { "oOo",    "/ \\",    "\\ /",   "",      "",      ""      },
        { "<B",     "/-)",     "[^^]",   "",      "",      ""      },
        { "I/O",    "//",      "=>",     "",      "",      ""      }
    };
    public static readonly int[] menuGridWidths = new int[] {
        3,
        3,
        6,
        3,
        3,
        3
    };

    private static int i;
    private static int j = 1;
    private static int k;
    private static int l = 2;
    private static int m;
    //private static int n;
    public static int I { get { return i; } set { i = value; } }
    public static int J { get { return j; } set { j = value; } }
    public static int K { get { return k; } set { k = value; } }
    public static int L { get { return l; } set { l = value; } }
    public static int M { get { return m; } set { m = value; } }
    //public static int N { get { return n; } set { n = value; } }
    public static void ResetIJ()
    {
        I = 0;
        J = 0;
    }
    public static void ResetKL()
    {
        K = 0;
        L = 0;
    }
    public static void ResetM()
    {
        M = 0;
        //N = 0;
    }

    public enum Offerings
    {
        None,
        Fillmore1Bomb,
        Fillmore2StrengthOfAngel,
        Fillmore3SourceOfMagic,
        Fillmore4SourceOfMagic,
        Fillmore5SourceOfLife,
        Fillmore6Bridge,
        Fillmore7MagicalFire,
        Bloodpool1Bomb,
        Bloodpool2Wheat,
        Bloodpool3LoafOfBread,
        Bloodpool4MagicSkull,
        Bloodpool5Compass,
        Bloodpool6SourceOfMagic,
        Bloodpool7SourceOfLife,
        Bloodpool8MagicStardust,
        Kasandora1Bomb,
        Kasandora2StrengthOfAngel,
        Kasandora3SourceOfMagic,
        Kasandora4SourceOfMagic,
        Kasandora5SourceOfLife,
        Kasandora6AncientTablet,
        Kasandora7HarmoniousMusic,
        Aitos1Bomb,
        Aitos2StrengthOfAngel,
        Aitos3SourceOfMagic,
        Aitos4SheepFleece,
        Marahna1Bomb,
        Marahna2StrengthOfAngel,
        Marahna3SourceOfMagic,
        Marahna4Herb,
        Marahna5MagicalAura,
        Northwall1StrengthOfAngel,
        Northwall2Bomb,
        Northwall3SourceOfMagic,
        Northwall4MagicalLight,
        Northwall5SourceOfLife
    }
    public static string[] offeringDescriptions = new string[]
    {
        "",
        "Bomb!",
        "Strength of Angel",
        "Source of Magic",
        "Source of Magic",
        "Source of Life",
        "Bridge",
        "Magical Fire",
        "Bomb!",
        "Wheat",
        "Loaf of Bread",
        "Magic Skull",
        "Compass",
        "Source of Magic",
        "Source of Magic",
        "Magical Stardust",
        "Bomb!",
        "Strength of Angel",
        "Source of Magic",
        "Source of Magic",
        "Source of Magic",
        "Ancient Tablet",
        "Harmonious Music",
        "Bomb!",
        "Strength of Angel",
        "Source of Magic",
        "Fleece",
        "Bomb!",
        "Strength of Angel",
        "Source of Magic",
        "Herb",
        "Magical Aura",
        "Strength of Angel",
        "Bomb!",
        "Source of Magic",
        "Magical Light",
        "Source of Magic"
    };
    public static string[] offeringIcons = new string[]
    {
        "",
        "bmb",
        "soa",
        "som",
        "som",
        "sol",
        "bdg",
        "fir",
        "bmb",
        "wht",
        "brd",
        "skl",
        "cps",
        "som",
        "sol",
        "dst",
        "bmb",
        "soa",
        "som",
        "som",
        "sol",
        "tbt",
        "msc",
        "bmb",
        "soa",
        "som",
        "flc",
        "bmb",
        "soa",
        "som",
        "hrb",
        "aur",
        "soa",
        "bmb",
        "som",
        "lgt",
        "sol"
    };
    public static int offeringsSize;
    public static bool[] offeringIsFound;
    public static bool[] offeringIsUsed;
    public const int OFFERING_INDEX_MAX = 8;
    public static int offeringIndex;
    //public static Offerings[,] offerings = new Offerings[,] {
    //    { Offerings.None, Offerings.None, Offerings.None, Offerings.None },
    //    { Offerings.None, Offerings.None, Offerings.None, Offerings.None }
    //};
    public static string[,] offeringIconsInInventory = new string[,]
    {
        { "", "", "", "" },
        { "", "", "", "" }
    };
    public static string[,] offeringDescriptionsInInventory = new string[,]
    {
        { "", "", "", "" },
        { "", "", "", "" }
    };

    public static int takenIndex;
    public static string[,] takenIcons = new string[,]
    {
        { "", "", "", "" },
        { "", "", "", "" }
    };
    public static string[,] takenDescriptions = new string[,]
    {
        { "", "", "", "" },
        { "", "", "", "" }
    };

    public static string[,] enterPlayerName = new string[,]
    {
        { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",},
        { "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",},
        { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",},
        { "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",},
        { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "BS", "ED",}
    };


    public static bool IsInMenu(bool isMessageVisible)
    {
        return isTownBuilderMenuVisible
               || isSkyPalaceMenuVisible
               || isStart
               || isEnterPlayerNameMenuVisible
               || isMessageVisible;
    }

    public static bool IsZeroColumn { get {
        return (isTownBuilderMenuVisible || isSkyPalaceMenuVisible)
                     && J == 0;
    } }

    public static bool Up(bool isBlocked)
    {
        if (ShowMeWhereBlock())
        {
            return true;
        }
        var result = false;
        if (isBlocked
            || isPaused
            || isProgressLogConfirmationVisible
            || isReturnToWorldPromptVisible)
        {
            result = true;
            K--;
            if (K < 0)
            {
                K = 0;
            }
        }
        else if (isReturnToOfferings
                 || isLightningYesNo
                 || isRainYesNo
                 || isSunYesNo
                 || isWindYesNo
                 || isEarthquakeYesNo)
        {
            result = true;
            if (K == 1)
            {
                K = 0;
            }
        }
        else if (isTakeAnOffering
                 || isUseAnOffering)
        {
            result = true;
            K--;
            if (K < 0)
            {
                K = 0;
            }
        }
        else if (isEnterPlayerNameMenuVisible)
        {
            result = true;
            L--;
            if (L < 0)
            {
                L = 4;
            }
        }
        else if (isTownBuilderMenuVisible
                 || isSkyPalaceMenuVisible
                 || isEnterPlayerNameMenuVisible)
        {
            result = true;
            J = 0;
            I--;
            if (I < 0)
            {
                I = 0;
            }
        }
        else if (isStart)
        {
            result = true;
            J--;
            if (SaveGameData.intArray[0] == 0 && J < 1)
            {
                J = 1;
            }
            else if (J < 0)
            {
                J = 0;
            }
        }
        else if (Messages.IsMessageVisible)
        {
            result = true;
        }
        return result;
    }

    public static bool Down(bool isBlocked)
    {
        if (ShowMeWhereBlock())
        {
            return true;
        }
        var result = false;
        if (isPaused
            || isProgressLogConfirmationVisible
            || isReturnToWorldPromptVisible)
        {
            result = true;
        }
        else if (isReturnToOfferings
                 || isLightningYesNo
                 || isRainYesNo
                 || isSunYesNo
                 || isWindYesNo
                 || isEarthquakeYesNo)
        {
            result = true;
            if (K == 0)
            {
                K = 1;
            }
        }
        else if (isTakeAnOffering
                 || isUseAnOffering)
        {
            result = true;
            if (L + 4 >= offeringIndex)
            {
            }
            else
            {
                K++;
                if (K > 1)
                {
                    K = 1;
                }
            }
        }
        else if (isEnterPlayerNameMenuVisible)
        {
            result = true;
            L++;
            if (L > 5 - 1)
            {
                L = 0;
            }
        }
        else if (isTownBuilderMenuVisible)
        {
            result = true;
            I++;
            if (I > MENU_GRID_SIZE - 1)
            {
                I = MENU_GRID_SIZE - 1;
            }
            else
            {
                J = 0;
            }
        }
        else if (isSkyPalaceMenuVisible)
        {
            result = true;
            var size = 4;
            I++;
            if (I > size - 1)
            {
                I = size - 1;
            }
            else
            {
                J = 0;
            }
        }
        else if (isStart)
        {
            result = true;
            J++;
            if (SaveGameData.intArray[0] != 2
                && J > 1)
            {
                J = 1;
            }
            else if (J >= 2)
            {
                J = 2;
            }
        }
        else if (Messages.IsMessageVisible)
        {
            result = true;
        }
        return result;
    }

    public static bool Left(bool isBlocked)
    {
        if (ShowMeWhereBlock())
        {
            return true;
        }
        var result = false;
        if (isBlocked
            || isPaused
            || isProgressLogConfirmationVisible
            || isReturnToWorldPromptVisible
            || isStart)
        {
            result = true;
        }
        else if (isTakeAnOffering
                 || isUseAnOffering)
        {
            result = true;
            if (L == 0 && K == 1)
            {
                L = 3;
                K = 0;
            }
            else
            {
                L--;
                if (L < 0 && K == 0)
                {
                    L = 0;
                }
            }
        }
        else if (isEnterPlayerNameMenuVisible)
        {
            result = true;
            K--;
            if (K < 0)
            {
                K = 12;
            }
        }
        else if (isMessageSpeedMenuVisible
                 && !isMessageSpeedConfirmationVisible)
        {
            result = true;
            L--;
            if (L < 0)
            {
                L = 0;
            }
        }
        else if (isTownBuilderMenuVisible
                 || isSkyPalaceMenuVisible)
        {
            result = true;
            J--;
            if (J < 0)
            {
                J = 0;
            }
        }
        else if (Messages.IsMessageVisible)
        {
            result = true;
        }
        return result;
    }

    public static bool Right(bool isBlocked)
    {
        if (ShowMeWhereBlock())
        {
            return true;
        }
        var result = false;
        if (isBlocked
            || isPaused
            || isProgressLogConfirmationVisible
            || isReturnToWorldPromptVisible
            || isStart)
        {
            result = true;
        }
        else if (isTakeAnOffering
                 || isUseAnOffering)
        {
            result = true;
            if (L == 3 && K == 0
                && offeringIndex - 1 > 3)
            {
                L = 0;
                K = 1;
            }
            else
            {
                L++;
                if (L > 3 && K == 1)
                {
                    L = 3;
                }
                else if (L >= offeringIndex && K == 0)
                {
                    L = offeringIndex - 1;
                }
                else if (L >= (offeringIndex - 4) && K == 1)
                {
                    L = (offeringIndex - 1 - 4);
                }
            }
        }
        else if (isEnterPlayerNameMenuVisible)
        {
            result = true;
            K++;
            if (K > 12)
            {
                K = 0;
            }
        }
        else if (isMessageSpeedMenuVisible
                 && !isMessageSpeedConfirmationVisible)
        {
            result = true;
            var size = 9;
            L++;
            if (L > size)
            {
                L = size;
            }
        }
        else if (isTownBuilderMenuVisible)
        {
            result = true;
            J++;
            if (J > menuGridWidths[I] - 1)
            {
                J = menuGridWidths[I] - 1;
            }
        }
        else if (isSkyPalaceMenuVisible)
        {
            result = true;
            var size = 2;
            J++;
            if (J > size)
            {
                J = size;
            }
        }
        else if (Messages.IsMessageVisible)
        {
            result = true;
        }
        return result;
    }

    public static bool ShowMeWhereBlock()
    {
        var isBlocked = false;
        if (isLightningShowMeWhere
            || isRainShowMeWhere
            || isSunShowMeWhere)
        {
            isBlocked = true;
        }
        return isBlocked;
    }
}
