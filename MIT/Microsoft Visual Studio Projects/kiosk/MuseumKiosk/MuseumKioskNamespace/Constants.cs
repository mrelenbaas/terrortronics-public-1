/*
 * Title: Constants file.
 * Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * Version: 2
 * Date: September 15, 2023
 *
 * Intellectual Property:
 * Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 *
 * License:
 * This file is owned by Terrortronics / Bradley Elenbaas.
 * This file observes the no License.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MuseumKioskNamespace
{
    abstract class Constants
    {
        public struct Callbacks
        {
            public readonly static string CALLBACK_001 = "boundAsync";
            public readonly static string CALLBACK_002 = "boundAsync2";
            public readonly static string CALLBACK_003 = "boundAsync3";
        }

        public struct Color
        {
            public readonly static string RED = "#811919";
            public readonly static string LIGHT_GRAY = "#f7f7f7";
        }

        public struct CSV
        {
            public readonly static string DELIMITER = @",";
        }

        public struct Donate
        {
            public readonly static double TOP = -26;
        }

        public struct Error
        {
            public readonly static string JAVASCRIPT_INJECTION_ERROR = "error";
        }

        public struct Filename
        {
            //public readonly static string HOME = Environment.GetEnvironmentVariable("USERPROFILE") + "\\Documents\\terrortronics-private\\Microsoft Visual Studio Projects\\museum_kiosk\\MuseumKiosk\\MuseumKioskNamespace\\HomePage.html";
            //public readonly static string GUEST_BOOK = Environment.GetEnvironmentVariable("USERPROFILE") + "\\Documents\\terrortronics-private\\Microsoft Visual Studio Projects\\museum_kiosk\\MuseumKiosk\\MuseumKioskNamespace\\GuestPage.html";
            //public readonly static string newFileName = Environment.GetEnvironmentVariable("USERPROFILE") + "\\Documents\\terrortronics-private\\Microsoft Visual Studio Projects\\museum_kiosk\\MuseumKiosk\\MuseumKioskNamespace\\pins.csv";
            public readonly static string HOME = Environment.GetEnvironmentVariable("USERPROFILE") + "\\Documents\\museum_kiosk\\MuseumKiosk\\MuseumKioskNamespace\\HomePage.html";
            public readonly static string GUEST_BOOK = Environment.GetEnvironmentVariable("USERPROFILE") + "\\Documents\\museum_kiosk\\MuseumKiosk\\MuseumKioskNamespace\\GuestPage.html";
            public readonly static string newFileName = Environment.GetEnvironmentVariable("USERPROFILE") + "\\Documents\\museum_kiosk\\MuseumKiosk\\MuseumKioskNamespace\\pins.csv";
        }

        public struct Form
        {
            public readonly static string FIRST_NAME = "First Name";
            public readonly static string LAST_NAME = "Last Name";
            public readonly static string CITY = "City / Town";
            public readonly static string STATE = "State / Province";
            public readonly static string COUNTRY = "Country";
            public readonly static string SUBMIT = "Submit";
            public readonly static string TITLE = "Submit Form to Perform Geolocation";
            public readonly static double WIDTH_PERCENTAGE = 0.8;
            public readonly static double LEFT_PERCENTAGE = 0.1;
            public readonly static double TOP_PERCENTAGE = 0.1;
            public readonly static double HEIGHT = 390;
            public readonly static double TITLE_HEIGHT = 50;
            public readonly static double LEFT_OFFSET = 150;
            public readonly static double TOP_OFFSET = 7;
            public readonly static float TEXT_BOX_LEFT_PERCENTAGE = 0.11f;
            public readonly static float TEXT_BOX_WIDTH_PERCENTAGE = 0.78f;
            public readonly static int SUBMIT_HEIGHT = 60;
            public readonly static int SUBMIT_TOP_OFFSET = 6;
            public readonly static int SUBMIT_TOP = 300;
        }

        public struct GUEST_BOOK
        {
            public readonly static double TOP = 90;
            public readonly static double LEFT = 694;
            public readonly static double WIDTH = 1226;
        }

        public struct Home
        {
            public readonly static double BUTTON_WIDTH = 500;
            public readonly static double LEFT = 200;
            public readonly static double TOP = 200;
            public readonly static double MARGIN = 70;
            public readonly static double HEIGHT = 120;
            public readonly static double FONT_SIZE = 40;
            public readonly static double TOP_PADDING = 30;
            public readonly static double BORDER_THICKNESS = 2;
            public readonly static double CORNER_RADIUS = 6;
        }

        public struct Keyboard
        {
            public readonly static double WIDTH = 380;
            public readonly static double LEFT = 1450;
            public readonly static double TOP = 900;
            public readonly static double HEIGHT = 120;
            public readonly static double FONT_SIZE = 40;
            public readonly static double TOP_THICKNESS = 30;
            public readonly static double THICKNESS = 2;
            public readonly static double CORNER_RADIUS = 6;
            public readonly static double TOP_PADDING = 30;
        }

        public struct OS
        {
            public readonly static string VIRTUAL_KEYBOARD = "osk.exe";
        }

        public struct Pin
        {
            public readonly static double BUTTON_WIDTH = 380;
            public readonly static double LEFT = 740;
            public readonly static double TOP = 900;
            public readonly static double HEIGHT = 120;
            public readonly static double FONT_SIZE = 40;
            public readonly static double TOP_PADDING = 30;
            public readonly static double BORDER_THICKNESS = 2;
            public readonly static double CORNER_RADIUS = 6;
        }

        public struct Prompt
        {
            public readonly static string TEXT = "Click the Pin button to fill out geolocation form.";
            public readonly static double HEIGHT = 100;
            public readonly static double WIDTH = 1230;
            public readonly static double LEFT = 705;
            public readonly static double TOP = 100;
            public readonly static double TOP_PADDING = 30;
            public readonly static double FONT_SIZE = 40;
        }

        public struct Survey
        {
            public readonly static double TOP = -26;
        }

        public struct Tab
        {
            public readonly static double HEIGHT = 50;
            public readonly static double TOP = 50;
            public readonly static double FONT_SIZE = 30;
            public readonly static double TOP_PADDING = 3;
            public readonly static double OFFSET = 1;
        }

        public struct Time
        {
            public readonly static int INTERVAL = 1000;
            public readonly static int SHORT_DELAY = 100;
            public readonly static int MEDIUM_DELAY = 2000;
            public readonly static int LONG_DELAY = 10000;
        }

        public struct Volunteer
        {
            public readonly static double TOP = -26;
        }

        public struct Websites
        {
            public readonly static string EVENTS = "https://igdatc.org/";
            public readonly static string SURVEY = "https://docs.google.com/forms/d/e/1FAIpQLSfR0QzF4zZaqwqJbhXObQc-sGtyV20eHDhmr1fuPNeCTGqbqA/viewform";
            public readonly static string DONATE = "https://members.igda.org/donations/donate.asp?id=22622";
            //public readonly static string DONATE = "https://www.paypal.com/donate/?token=8pPRH3Ws9L2LBEPCmKHnhn13EC8OSZoJiMcuU4dCOwK8pyeuD45vZ0nX6V33YC7Wsapxe8swMcYWTm09&locale.x=EN_US";
            public readonly static string VOLUNTEER = "https://igdatc.org/governance";
            public readonly static string PAYPAL_CHECK = "www.paypal.com";
        }
    }
}
