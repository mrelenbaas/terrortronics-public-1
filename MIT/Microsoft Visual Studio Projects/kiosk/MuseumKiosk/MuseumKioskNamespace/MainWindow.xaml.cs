/*
 * Title: MainWindow file.
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

// Contact
// -------
// Title: Museum Kiosk - 
// Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
// Version: 1.0.0
// Date: June 26, 2023

// Description
//-----------
// The main manager file.
// The file is a bit of a "god component", as much as I wish it weren't.

// Command-Line Arguments and Error Levels
//---------------------------
// No Command-Line Arguments of Error Levels.

// Unit Tests
//----------
// No unit tests.

using CefSharp;
using CefSharp.Wpf;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using System.Windows.Controls;

namespace MuseumKioskNamespace
{
    /// <summary>
    /// The main function.
    /// </summary>
    public partial class MainWindow : Window
    {
        // Blocks.
        public static bool isBlocked = true;
        public static bool isDeleteBlocked = false;
        public static bool isReloadBlocked = true;
        public static bool isClearCacheBlocked = true;

        public static string location = "";

        // Styles.
        private readonly Style defaultStyle;
        private readonly Style underlinedStyle;

        private bool isLoading;

        private Process keyboardProcess;

        public class LifeSpan_RightBrowser : ILifeSpanHandler
        {
            public static IBrowser someBrowser = null;
            public static IWebBrowser anotherBrowser = null;

            public static Border someBorder;
            public static Button someButton;
            public static double someHeight;
            public static double someWidth;

            public bool OnBeforePopup(IWebBrowser browserControl, IBrowser browser, IFrame frame, string targetUrl, string targetFrameName, WindowOpenDisposition targetDisposition, bool userGesture, IPopupFeatures popupFeatures, IWindowInfo windowInfo, IBrowserSettings browserSettings, ref bool noJavascriptAccess, out IWebBrowser newBrowser)
            {
                if (targetUrl.Contains(Constants.Websites.PAYPAL_CHECK))
                {
                    MainWindow.isClearCacheBlocked = false;

                    if (anotherBrowser != null)
                    {
                        if (anotherBrowser.IsBrowserInitialized)
                        {
                            //anotherBrowser.Delete();
                        }
                        //anotherBrowser.Dispose();
                        //anotherBrowser.Delete();
                    }
                    if (someBrowser != null)
                    {
                        //someBrowser.CloseBrowser(true);
                    }

                    /*
                    someBorder.Height = someHeight;
                    someBorder.Width = someWidth;
                    Canvas.SetLeft(someBorder, 0);
                    Canvas.SetTop(someBorder, 0);
                    someButton.Height = someHeight;
                    someButton.Width = someWidth;
                    Canvas.SetLeft(someButton, 0);
                    Canvas.SetTop(someButton, 0);
                    */

                    //if (someBrowser != null)
                    //{
                    //someBrowser.CloseBrowser(true);
                    newBrowser = new ChromiumWebBrowser();
                        //someBrowser = newBrowser.GetBrowser();
                        //anotherBrowser = newBrowser.get;
                    //}
                    //else
                    //{
                    //    someBrowser = null;
                    //}

                    newBrowser = null;
                    return false;
                }
                else
                {
                    browserControl.Load(targetUrl);
                    newBrowser = null;
                    //someBrowser = newBrowser.GetBrowser();
                    return true;
                }
            }

            public void OnAfterCreated(IWebBrowser browserControl, IBrowser browser) 
            {
                someBrowser = browser;
            }

            public bool DoClose(IWebBrowser browserControl, IBrowser browser)
            {
                //TeardownForm();
                //if (browser != null)
                //{
                    //if (!browser.IsDisposed)
                    //{
                        //browser.CloseBrowser(true);
                    //}
                    //LifeSpan_RightBrowser.someBrowser.CloseBrowser(true);
                //}
                //ClickFormBackground(null, null);
                //Debug.Print("CLOSING");
                return false;
            }

            public void OnBeforeClose(IWebBrowser browserControl, IBrowser browser) { }
        }

        // Constructor.
        public MainWindow()
        {
            InitializeComponent();
            defaultStyle = (Style)Resources["defaultFont"];
            underlinedStyle = (Style)Resources["underlinedFont"];
            TeardownForm();
            SetupWorkers();
            SetupStyles();
            SetupJavaScriptCallbacks();
        }

        // Pseudo-constructor.
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            LifeSpan_RightBrowser.someBorder = Border_FormBackground;
            LifeSpan_RightBrowser.someButton = Button_FormBackground;
            LifeSpan_RightBrowser.someHeight = TopParent.Height;
            LifeSpan_RightBrowser.someWidth = TopParent.Width;

            SetupBrowsers();
            ClickHome(null, null);
        }

        // Load donate page.
        private void ClickDonate(object sender, RoutedEventArgs e)
        {
            if (LifeSpan_RightBrowser.someBrowser != null)
            {
                if (!LifeSpan_RightBrowser.someBrowser.IsDisposed)
                {
                    LifeSpan_RightBrowser.someBrowser.CloseBrowser(true);
                }
                //LifeSpan_RightBrowser.someBrowser.CloseBrowser(true);
            }
            //LifeSpan_RightBrowser.someBrowser.CloseBrowser(true);
            //LifeSpan_RightBrowser.someBrowser = null;
            SetupKeyboardButton();
            ClearCache();
            Button[] buttons = new Button[] {
                Home_Button,
                Survey_Button,
                Volunteer_Button,
                GuestBook_Button
            };
            TextBlock[] textBlocks = new TextBlock[] {
                Home_TextBlock,
                Survey_TextBlock,
                Volunteer_TextBlock,
                GuestBook_TextBlock
            };
            Border[] borders = new Border[] {
                Home_TextBlockBorder,
                Survey_TextBlockBorder,
                Volunteer_TextBlockBorder,
                GuestBook_TextBlockBorder
            };
            TeardownHome();
            SetupTabButtons(buttons, textBlocks, borders);
            Canvas.SetTop(rightBrowser, Constants.Donate.TOP);
            backgroundBrowser.Opacity = 0;
            TeardownPrompt();
            TeardownForm();
            rightBrowser.Address = Constants.Websites.DONATE;
            if (leftBrowser.Address != Constants.Websites.EVENTS)
            {
                leftBrowser.Address = Constants.Websites.EVENTS;
            }
        }

        // Teardown form.
        private void ClickFormBackground(object sender, RoutedEventArgs e)
        {
            TeardownForm();
            if (LifeSpan_RightBrowser.someBrowser != null)
            {
                if (!LifeSpan_RightBrowser.someBrowser.IsDisposed)
                {
                    LifeSpan_RightBrowser.someBrowser.CloseBrowser(true);
                }
                //LifeSpan_RightBrowser.someBrowser.CloseBrowser(true);
            }
        }

        // Load guest book page.
        private async void ClickGuestBook(object sender, RoutedEventArgs e)
        {
            SetupKeyboardButton();
            Button[] buttons = new Button[] {
                Home_Button,
                Survey_Button,
                Donate_Button,
                Volunteer_Button
            };
            TextBlock[] textBlocks = new TextBlock[] {
                Home_TextBlock,
                Survey_TextBlock,
                Donate_TextBlock,
                Volunteer_TextBlock
            };
            Border[] borders = new Border[] {
                Home_TextBlockBorder,
                Survey_TextBlockBorder,
                Donate_TextBlockBorder,
                Volunteer_TextBlockBorder
            };
            isDeleteBlocked = false;
            TeardownHome();
            SetupTabButtons(buttons, textBlocks, borders);
            Canvas.SetTop(rightBrowser, Constants.GUEST_BOOK.TOP);
            Canvas.SetLeft(rightBrowser, Constants.GUEST_BOOK.LEFT);
            rightBrowser.Width = Constants.GUEST_BOOK.WIDTH;
            backgroundBrowser.Opacity = 0;
            rightBrowser.Address = Constants.Filename.GUEST_BOOK;
            SetupPinButton();
            TeardownForm();
            if (leftBrowser.Address != Constants.Websites.EVENTS)
            {
                leftBrowser.Address = Constants.Websites.EVENTS;
            }
            SetupPrompt();
            await Task.Delay(200);
            LoadPins(0);
        }
        private async void ClickGuestBook2(object sender, RoutedEventArgs e)
        {
            SetupKeyboardButton();
            Button[] buttons = new Button[] {
                Home_Button,
                Survey_Button,
                Donate_Button,
                Volunteer_Button
            };
            TextBlock[] textBlocks = new TextBlock[] {
                Home_TextBlock,
                Survey_TextBlock,
                Donate_TextBlock,
                Volunteer_TextBlock
            };
            Border[] borders = new Border[] {
                Home_TextBlockBorder,
                Survey_TextBlockBorder,
                Donate_TextBlockBorder,
                Volunteer_TextBlockBorder
            };
            isDeleteBlocked = false;
            TeardownHome();
            SetupTabButtons(buttons, textBlocks, borders);
            Canvas.SetTop(rightBrowser, Constants.GUEST_BOOK.TOP);
            Canvas.SetLeft(rightBrowser, Constants.GUEST_BOOK.LEFT);
            rightBrowser.Width = Constants.GUEST_BOOK.WIDTH;
            backgroundBrowser.Opacity = 0;
            rightBrowser.Address = Constants.Filename.GUEST_BOOK;
            SetupPinButton();
            TeardownForm();
            if (leftBrowser.Address != Constants.Websites.EVENTS)
            {
                leftBrowser.Address = Constants.Websites.EVENTS;
            }
            SetupPrompt();
            await Task.Delay(200);
            LoadPins(1000);
        }

        // Load home page.
        private void ClickHome(object sender, RoutedEventArgs e)
        {
            TeardownKeyboardButton();
            SetupHome();
            SetupHomeButtons();
            TeardownPrompt();
            TeardownForm();
            backgroundBrowser.Opacity = 1;
            rightBrowser.Address = Constants.Filename.HOME;
        }

        // TODO: Remove old function.
        // Launch virtual keyboard.
        private void ClickKeyboard(object sender, RoutedEventArgs e)
        {
            Process.Start(Constants.OS.VIRTUAL_KEYBOARD);
        }

        // Setup form.
        private void ClickPin(object sender, RoutedEventArgs e)
        {
            keyboardProcess = Process.Start(Constants.OS.VIRTUAL_KEYBOARD);
            SetupForms();
        }

        // Submit form to update GoogleMaps.
        private async void ClickSubmit(object sender, RoutedEventArgs e)
        {
            StringBuilder sb = new StringBuilder();
            string firstName = "";
            string lastName = "";
            string city = "";
            string state = "";
            string country = "";
            StringBuilder message = new StringBuilder();
            if (TextBox_FirstName.Text != Constants.Form.FIRST_NAME)
            {
                if (rightBrowser.CanExecuteJavascriptInMainFrame)
                {
                    message.Clear();
                    message.Append(@"window.lastFirstName = """);
                    message.Append(TextBox_FirstName.Text);
                    message.Append(@""";");
                    await rightBrowser.EvaluateScriptAsync(message.ToString(), 10000);
                    await Task.Delay(100);
                }
                sb.Append(TextBox_FirstName.Text);
                firstName = TextBox_FirstName.Text + Constants.CSV.DELIMITER;
                DotNetMessage.SetLastFirstName(TextBox_FirstName.Text);
            }
            else
            {
                message.Clear();
                message.Append(@"window.lastFirstName = """);
                message.Append(@" ");
                message.Append(@""";");
                await rightBrowser.EvaluateScriptAsync(message.ToString(), 10000);
                await Task.Delay(100);
                sb.Append("");
            }
            sb.Append(Constants.CSV.DELIMITER);
            if (TextBox_LastName.Text != Constants.Form.LAST_NAME)
            {
                if (rightBrowser.CanExecuteJavascriptInMainFrame)
                {
                    message.Clear();
                    message.Append(@"window.lastLastName = """);
                    message.Append(TextBox_LastName.Text);
                    message.Append(@""";");
                    await rightBrowser.EvaluateScriptAsync(message.ToString(), 10000);
                    await Task.Delay(100);
                }
                sb.Append(TextBox_LastName.Text);
                lastName = TextBox_LastName.Text + Constants.CSV.DELIMITER;
                DotNetMessage.SetLastLastName(TextBox_LastName.Text);
            }
            else
            {
                message.Clear();
                message.Append(@"window.lastLastName = """);
                message.Append(@" ");
                message.Append(@""";");
                await rightBrowser.EvaluateScriptAsync(message.ToString(), 10000);
                await Task.Delay(100);
                sb.Append("");
            }
            sb.Append(Constants.CSV.DELIMITER);
            bool isFirst = true;
            StringBuilder tempString = new StringBuilder();
            if (TextBox_City.Text != Constants.Form.CITY)
            {
                if (rightBrowser.CanExecuteJavascriptInMainFrame)
                {
                    message.Clear();
                    message.Append(@"window.lastCity = """);
                    message.Append(TextBox_City.Text);
                    message.Append(@""";");
                    await rightBrowser.EvaluateScriptAsync(message.ToString(), 10000);
                    await Task.Delay(100);
                }
                sb.Append(TextBox_City.Text);
                city = TextBox_City.Text + Constants.CSV.DELIMITER;
                DotNetMessage.SetLastCity(TextBox_City.Text);
                if (isFirst)
                {
                    isFirst = false;
                }
                else
                {
                    tempString.Append(@", ");
                }
                tempString.Append(TextBox_City.Text);
            }
            else
            {
                message.Clear();
                message.Append(@"window.lastCity = """);
                message.Append(@" ");
                message.Append(@""";");
                await rightBrowser.EvaluateScriptAsync(message.ToString(), 10000);
                await Task.Delay(100);
                sb.Append("");
            }
            sb.Append(Constants.CSV.DELIMITER);
            if (TextBox_State.Text != Constants.Form.STATE)
            {
                if (rightBrowser.CanExecuteJavascriptInMainFrame)
                {
                    message.Clear();
                    message.Append(@"window.lastState = """);
                    message.Append(TextBox_State.Text);
                    message.Append(@""";");
                    await rightBrowser.EvaluateScriptAsync(message.ToString(), 10000);
                    await Task.Delay(100);
                }
                sb.Append(TextBox_State.Text);
                state = TextBox_State.Text + Constants.CSV.DELIMITER;
                DotNetMessage.SetLastState(TextBox_State.Text);
                if (isFirst)
                {
                    isFirst = false;
                }
                else
                {
                    tempString.Append(@", ");
                }
                tempString.Append(TextBox_State.Text);
            }
            else
            {
                sb.Append("");
            }
            sb.Append(Constants.CSV.DELIMITER);
            if (TextBox_Country.Text != Constants.Form.COUNTRY)
            {
                if (rightBrowser.CanExecuteJavascriptInMainFrame)
                {
                    message.Clear();
                    message.Append(@"window.lastCountry = """);
                    message.Append(TextBox_Country.Text);
                    message.Append(@""";");
                    await rightBrowser.EvaluateScriptAsync(message.ToString(), 10000);
                    await Task.Delay(100);
                }
                sb.Append(TextBox_Country.Text);
                country = TextBox_Country.Text + Constants.CSV.DELIMITER;
                DotNetMessage.SetLastCountry(TextBox_Country.Text);
                if (isFirst)
                {
                    isFirst = false;
                }
                else
                {
                    tempString.Append(@", ");
                }
                tempString.Append(TextBox_Country.Text);
            }
            else
            {
                sb.Append("");
            }
            sb.Append(Constants.CSV.DELIMITER);
            location = tempString.ToString();
            if (firstName != "" && lastName != "")
            {
            }
            else
            {
                var c = new System.Windows.Media.BrushConverter();
                var b = (System.Windows.Media.Brush)c.ConvertFromString(Constants.Color.RED);

                if (TextBox_FirstName.Text == "" || TextBox_FirstName.Text == Constants.Form.FIRST_NAME)
                {
                    Border_FirstNameBackground.Background = b;
                }
                if (TextBox_LastName.Text == "" || TextBox_LastName.Text == Constants.Form.LAST_NAME)
                {
                    Border_LastNameBackground.Background = b;
                }
                backgroundBrowser.Reload();
                return;
            }
            TeardownForm();
            var converter = new System.Windows.Media.BrushConverter();
            var brush = (System.Windows.Media.Brush)converter.ConvertFromString(Constants.Color.LIGHT_GRAY);
            Border_FirstNameBackground.Background = brush;
            Border_LastNameBackground.Background = brush;
            Border_CityBackground.Background = brush;
            Border_StateBackground.Background = brush;
            Border_CountryBackground.Background = brush;
            isBlocked = false;
            //LoadPins2();
            isLoading = false;
            ClickGuestBook(null, null);
            //Process.Start("taskkill osk.exe");
            //keyboardProcess.Kill();
        }

        // Load volunteer page.
        private void ClickVolunteer(object sender, RoutedEventArgs e)
        {
            SetupKeyboardButton();
            Button[] buttons = new Button[] {
                Home_Button,
                Survey_Button,
                Donate_Button,
                GuestBook_Button
            };
            TextBlock[] textBlocks = new TextBlock[] {
                Home_TextBlock,
                Survey_TextBlock,
                Donate_TextBlock,
                GuestBook_TextBlock
            };
            Border[] borders = new Border[] {
                Home_TextBlockBorder,
                Survey_TextBlockBorder,
                Donate_TextBlockBorder,
                GuestBook_TextBlockBorder
            };
            TeardownHome();
            SetupTabButtons(buttons, textBlocks, borders);
            Canvas.SetTop(rightBrowser, Constants.Volunteer.TOP);
            backgroundBrowser.Opacity = 0;
            TeardownPrompt();
            TeardownForm();
            rightBrowser.Address = Constants.Websites.VOLUNTEER;
            if (leftBrowser.Address != Constants.Websites.EVENTS)
            {
                leftBrowser.Address = Constants.Websites.EVENTS;
            }
        }

        private async void LoadPins(int delayTime)
        {
            if (isLoading)
            {
                return;
            }
            else
            {
                isLoading = true;
            }
            await Task.Delay(delayTime);
            DotNetMessage.Read();
            List<string> firstNames = DotNetMessage.GetFirstNames();
            List<string> lastNames = DotNetMessage.GetLastNames();
            List<string> cities = DotNetMessage.GetCityTowns();
            List<string> states = DotNetMessage.GetStateProvinces();
            List<string> countries = DotNetMessage.GetCountries();
            List<string> lats = DotNetMessage.GetLats();
            List<string> lngs = DotNetMessage.GetLngs();
            String localAddress = "";
            float perc = 0.0f;
            var rand = new Random();
            double isNegative = 1.0;
            System.Console.WriteLine("lats.Count: " + lats.Count);
            for (int i = 0; i < lats.Count; ++i)
            {
                StringBuilder tempLocation = new StringBuilder();
                tempLocation.Append(cities[i]);
                tempLocation.Append(@", ");
                tempLocation.Append(states[i]);
                tempLocation.Append(@", ");
                tempLocation.Append(countries[i]);
                localAddress = tempLocation.ToString();
                StringBuilder tempSB = new StringBuilder();
                if (rand.NextDouble() > 0.5)
                {
                    isNegative = 1.0;
                }
                else
                {
                    isNegative = -1.0;
                }
                tempSB.Append(@"window.locations.push(");
                tempSB.Append(@"{ ");
                tempSB.Append(@"firstName: """);
                tempSB.Append(firstNames[i]);
                tempSB.Append(@"""");
                tempSB.Append(@", lastName: """);
                tempSB.Append(lastNames[i]);
                tempSB.Append(@"""");
                tempSB.Append(@", city: """);
                tempSB.Append(cities[i]);
                tempSB.Append(@"""");
                tempSB.Append(@", lat: ");
                tempSB.Append(float.Parse(lats[i]) + (isNegative * (rand.NextDouble() * 0.0005f)));
                tempSB.Append(@", lng: ");
                tempSB.Append(float.Parse(lngs[i]) + (isNegative * (rand.NextDouble() * 0.0005f)));
                tempSB.Append(@", get getCity() {");
                tempSB.Append(@"return this.city;");
                tempSB.Append(@"}");
                tempSB.Append(@", get getFirstName() {");
                tempSB.Append(@"return this.firstName;");
                tempSB.Append(@"}");
                tempSB.Append(@", get getLastName() {");
                tempSB.Append(@"return this.lastName;");
                tempSB.Append(@"}");
                tempSB.Append(@" }");
                tempSB.Append(@");");
                tempSB.Append(@"");
                perc = i / lats.Count;
                Volunteer_TextBlock.Text = "" + (int)(((float)i / (float)lats.Count) * 100f) + "%";
                if (rightBrowser.CanExecuteJavascriptInMainFrame)
                {
                    JavascriptResponse response = await rightBrowser.EvaluateScriptAsync(tempSB.ToString(), 0);
                    //await Task.Delay(10);
                    if (response.Result == null)
                    {
                    }
                }
                //await Task.Delay(10);
            }
            StringBuilder sb = new StringBuilder();
            Volunteer_TextBlock.Text = "VOLUNTEER";
            sb.Append(@"initMap();");
            if (rightBrowser.CanExecuteJavascriptInMainFrame)
            {
                JavascriptResponse response = await rightBrowser.EvaluateScriptAsync(sb.ToString(), 10000);
                await Task.Delay(400);
                if (response.Result == null)
                {
                }
            }
            isLoading = false;
        }

        // Load survey page.
        private void ClickSurvey(object sender, RoutedEventArgs e)
        {
            SetupKeyboardButton();
            Button[] buttons = new Button[] {
                Home_Button,
                Donate_Button,
                Volunteer_Button,
                GuestBook_Button
            };
            TextBlock[] textBlocks = new TextBlock[] {
                Home_TextBlock,
                Donate_TextBlock,
                Volunteer_TextBlock,
                GuestBook_TextBlock
            };
            Border[] borders = new Border[] {
                Home_TextBlockBorder,
                Donate_TextBlockBorder,
                Volunteer_TextBlockBorder,
                GuestBook_TextBlockBorder
            };
            TeardownHome();
            SetupTabButtons(buttons, textBlocks, borders);
            Canvas.SetTop(rightBrowser, Constants.Survey.TOP);
            backgroundBrowser.Opacity = 0;
            TeardownPrompt();
            TeardownForm();
            rightBrowser.Address = Constants.Websites.SURVEY;
            if (leftBrowser.Address != Constants.Websites.EVENTS)
            {
                leftBrowser.Address = Constants.Websites.EVENTS;
            }
        }

        // Delete cookies, flush, then clear cache.
        private void ClearCache()
        {
            Cef.GetGlobalCookieManager().DeleteCookies("", "");
            Cef.GetGlobalCookieManager().FlushStore(null);
            rightBrowser.GetMainFrame().ExecuteJavaScriptAsync(JavaScriptInjection.ClearCache());
        }

        // Clear city text box, and reset other text boxes if needed.
        private void MouseDownCity(object sender, RoutedEventArgs e)
        {
            TextBox_City.Text = "";
            ResetFormTextIfNeeded(TextBox_City);
        }

        // Clear country text box, and reset other text boxes if needed.
        private void MouseDownCountry(object sender, RoutedEventArgs e)
        {
            TextBox_Country.Text = "";
            ResetFormTextIfNeeded(TextBox_Country);
        }

        // Clear first name text box, and reset other text boxes if needed.
        private void MouseDownFirstName(object sender, RoutedEventArgs e)
        {
            TextBox_FirstName.Text = "";
            ResetFormTextIfNeeded(TextBox_FirstName);
        }

        // Clear last name text box, and reset other text boxes if needed.
        private void MouseDownLastName(object sender, RoutedEventArgs e)
        {
            TextBox_LastName.Text = "";
            ResetFormTextIfNeeded(TextBox_LastName);
        }

        // Clear state text box, and reset other text boxes if needed.
        private void MouseDownState(object sender, RoutedEventArgs e)
        {
            TextBox_State.Text = "";
            ResetFormTextIfNeeded(TextBox_State);
        }

        // Underline donate text block.
        private void MouseEnterDonate(object sender, RoutedEventArgs e)
        {
            Donate_TextBlock.Style = underlinedStyle;
        }

        // Underline guest book text block.
        private void MouseEnterGuestBook(object sender, RoutedEventArgs e)
        {
            GuestBook_TextBlock.Style = underlinedStyle;
        }

        // Underline home text block.
        private void MouseEnterHome(object sender, RoutedEventArgs e)
        {
            Home_TextBlock.Style = underlinedStyle;
        }

        // Underline keyboard text block.
        private void MouseEnterKeyboard(object sender, RoutedEventArgs e)
        {
            Keyboard_TextBlock.Style = underlinedStyle;
        }

        // Underline pin tex block.
        private void MouseEnterPin(object sender, RoutedEventArgs e)
        {
            Pin_TextBlock.Style = underlinedStyle;
        }

        // Underline submit text block.
        private void MouseEnterSubmit(object sender, RoutedEventArgs e)
        {
            TextBlock_Submit.Style = underlinedStyle;
        }

        // Underline survey text block.
        private void MouseEnterSurvey(object sender, RoutedEventArgs e)
        {
            Survey_TextBlock.Style = underlinedStyle;
        }

        // Underline volunteer text block.
        private void MouseEnterVolunteer(object sender, RoutedEventArgs e)
        {
            Volunteer_TextBlock.Style = underlinedStyle;
        }

        // Reset donate text block.
        private void MouseLeaveDonate(object sender, RoutedEventArgs e)
        {
            Donate_TextBlock.Style = defaultStyle;
        }

        // Reset guest book text block.
        private void MouseLeaveGuestBook(object sender, RoutedEventArgs e)
        {
            GuestBook_TextBlock.Style = defaultStyle;
        }

        // Reset home text block.
        private void MouseLeaveHome(object sender, RoutedEventArgs e)
        {
            Home_TextBlock.Style = defaultStyle;
        }

        // Reset keyboard text block.
        private void MouseLeaveKeyboard(object sender, RoutedEventArgs e)
        {
            Keyboard_TextBlock.Style = defaultStyle;
        }

        // Reset pin text block.
        private void MouseLeavePin(object sender, RoutedEventArgs e)
        {
            Pin_TextBlock.Style = defaultStyle;
        }

        // Reset submit text block.
        private void MouseLeaveSubmit(object sender, RoutedEventArgs e)
        {
            TextBlock_Submit.Style = defaultStyle;
        }

        // Reset survey text block.
        private void MouseLeaveSurvey(object sender, RoutedEventArgs e)
        {
            Survey_TextBlock.Style = defaultStyle;
        }

        // Reset volunteer text block.
        private void MouseLeaveVolunteer(object sender, RoutedEventArgs e)
        {
            Volunteer_TextBlock.Style = defaultStyle;
        }

        // Reset form text boxes if they have been left blank.
        private void ResetFormTextIfNeeded(TextBox caller)
        {
            if (TextBox_FirstName.Text == "" && TextBox_FirstName != caller)
            {
                TextBox_FirstName.Text = Constants.Form.FIRST_NAME;
            }
            if (TextBox_LastName.Text == "" && TextBox_LastName != caller)
            {
                TextBox_LastName.Text = Constants.Form.LAST_NAME;
            }
            if (TextBox_City.Text == "" && TextBox_City != caller)
            {
                TextBox_City.Text = Constants.Form.CITY;
            }
            if (TextBox_State.Text == "" && TextBox_State != caller)
            {
                TextBox_State.Text = Constants.Form.STATE;
            }
            if (TextBox_Country.Text == "" && TextBox_Country != caller)
            {
                TextBox_Country.Text = Constants.Form.COUNTRY;
            }
        }

        // Setup browsers.
        private void SetupBrowsers()
        {
            ChromiumWebBrowser[] browsers = new ChromiumWebBrowser[]
            {
                leftBrowser,
                rightBrowser,
                backgroundBrowser,
            };
            leftBrowser.Address = Constants.Websites.EVENTS;
            rightBrowser.Address = Constants.Filename.GUEST_BOOK;
            backgroundBrowser.Address = Constants.Filename.HOME;
            leftBrowser.LifeSpanHandler = new Handlers.LifeSpan_LeftBrowser();
            rightBrowser.LifeSpanHandler = new LifeSpan_RightBrowser();
            foreach (ChromiumWebBrowser browser in browsers)
            {
                browser.MenuHandler = new Handlers.Menu();
                //browser.DragHandler = new Handlers.Drag();
            }
        }

        // Setup GoogleMaps form.
        private void SetupForms()
        {
            double width = TopParent.Width * Constants.Form.WIDTH_PERCENTAGE;
            double left = TopParent.Width * Constants.Form.LEFT_PERCENTAGE;
            double top = TopParent.Height * Constants.Form.TOP_PERCENTAGE;
            double height = Constants.Form.HEIGHT;

            Border_FormBackground.Height = TopParent.Height;
            Border_FormBackground.Width = TopParent.Width;
            Canvas.SetLeft(Border_FormBackground, 0);
            Canvas.SetTop(Border_FormBackground, 0);
            Button_FormBackground.Height = TopParent.Height;
            Button_FormBackground.Width = TopParent.Width;
            Canvas.SetLeft(Button_FormBackground, 0);
            Canvas.SetTop(Button_FormBackground, 0);

            Border_Form.Height = height;
            Border_Form.Width = width;
            Canvas.SetLeft(Border_Form, left);
            Canvas.SetTop(Border_Form, top);
            Border_FormTitle.Height = Constants.Form.TITLE_HEIGHT;
            Border_FormTitle.Width = width;
            Canvas.SetLeft(Border_FormTitle, left);
            Canvas.SetTop(Border_FormTitle, top);
            TextBlock_FormTitle.Text = Constants.Form.TITLE;
            TextBlock_FormTitle.Width = width;
            Canvas.SetLeft(TextBlock_FormTitle, (TopParent.Width * 0.5) - Constants.Form.LEFT_OFFSET);
            Canvas.SetTop(TextBlock_FormTitle, top + Constants.Form.TOP_OFFSET);
            float textBoxLeft = Constants.Form.TEXT_BOX_LEFT_PERCENTAGE;
            float textBoxWidth = Constants.Form.TEXT_BOX_WIDTH_PERCENTAGE;
            double tempHeight = Constants.Form.TITLE_HEIGHT;
            Border_FirstNameBackground.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(Border_FirstNameBackground, TopParent.Width * textBoxLeft);
            Canvas.SetTop(Border_FirstNameBackground, top + tempHeight + Constants.Form.TOP_OFFSET);
            TextBox_FirstName.Text = Constants.Form.FIRST_NAME;
            TextBox_FirstName.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(TextBox_FirstName, TopParent.Width * textBoxLeft);
            Canvas.SetTop(TextBox_FirstName, top + tempHeight + Constants.Form.TOP_OFFSET);
            Border_FirstNameForeground.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(Border_FirstNameForeground, TopParent.Width * textBoxLeft);
            Canvas.SetTop(Border_FirstNameForeground, top + tempHeight + Constants.Form.TOP_OFFSET);
            tempHeight += Constants.Form.TITLE_HEIGHT;
            Border_LastNameBackground.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(Border_LastNameBackground, TopParent.Width * textBoxLeft);
            Canvas.SetTop(Border_LastNameBackground, top + tempHeight + Constants.Form.TOP_OFFSET);
            TextBox_LastName.Text = Constants.Form.LAST_NAME;
            TextBox_LastName.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(TextBox_LastName, TopParent.Width * textBoxLeft);
            Canvas.SetTop(TextBox_LastName, top + tempHeight + Constants.Form.TOP_OFFSET);
            Border_LastNameForeground.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(Border_LastNameForeground, TopParent.Width * textBoxLeft);
            Canvas.SetTop(Border_LastNameForeground, top + tempHeight + Constants.Form.TOP_OFFSET);
            tempHeight += Constants.Form.TITLE_HEIGHT;
            Border_CityBackground.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(Border_CityBackground, TopParent.Width * textBoxLeft);
            Canvas.SetTop(Border_CityBackground, top + tempHeight + Constants.Form.TOP_OFFSET);
            TextBox_City.Text = Constants.Form.CITY;
            TextBox_City.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(TextBox_City, TopParent.Width * textBoxLeft);
            Canvas.SetTop(TextBox_City, top + tempHeight + Constants.Form.TOP_OFFSET);
            Border_CityForeground.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(Border_CityForeground, TopParent.Width * textBoxLeft);
            Canvas.SetTop(Border_CityForeground, top + tempHeight + Constants.Form.TOP_OFFSET);
            tempHeight += Constants.Form.TITLE_HEIGHT;
            Border_StateBackground.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(Border_StateBackground, TopParent.Width * textBoxLeft);
            Canvas.SetTop(Border_StateBackground, top + tempHeight + Constants.Form.TOP_OFFSET);
            TextBox_State.Text = Constants.Form.STATE;
            TextBox_State.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(TextBox_State, TopParent.Width * textBoxLeft);
            Canvas.SetTop(TextBox_State, top + tempHeight + Constants.Form.TOP_OFFSET);
            Border_StateForeground.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(Border_StateForeground, TopParent.Width * textBoxLeft);
            Canvas.SetTop(Border_StateForeground, top + tempHeight + Constants.Form.TOP_OFFSET);
            tempHeight += Constants.Form.TITLE_HEIGHT;
            Border_CountryBackground.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(Border_CountryBackground, TopParent.Width * textBoxLeft);
            Canvas.SetTop(Border_CountryBackground, top + tempHeight + Constants.Form.TOP_OFFSET);
            TextBox_Country.Text = Constants.Form.COUNTRY;
            TextBox_Country.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(TextBox_Country, TopParent.Width * textBoxLeft);
            Canvas.SetTop(TextBox_Country, top + tempHeight + Constants.Form.TOP_OFFSET);
            Border_CountryForeground.Width = TopParent.Width * textBoxWidth;
            Canvas.SetLeft(Border_CountryForeground, TopParent.Width * textBoxLeft);
            Canvas.SetTop(Border_CountryForeground, top + tempHeight + Constants.Form.TOP_OFFSET);
            int submitHeight = Constants.Form.SUBMIT_HEIGHT;
            Button_Submit.Height = submitHeight;
            Button_Submit.Width = width / 2;
            Canvas.SetLeft(Button_Submit, ((TopParent.Width * 0.5) - (Button_Submit.Width * 0.5)));
            Canvas.SetTop(Button_Submit, top + Constants.Form.SUBMIT_TOP + Constants.Form.SUBMIT_TOP_OFFSET);
            TextBlock_Submit.Text = Constants.Form.SUBMIT;
            TextBlock_Submit.Height = submitHeight;
            TextBlock_Submit.Width = width / 2;
            Canvas.SetLeft(TextBlock_Submit, ((TopParent.Width * 0.5) - (Button_Submit.Width * 0.5)));
            Canvas.SetTop(TextBlock_Submit, top + Constants.Form.SUBMIT_TOP + Constants.Form.SUBMIT_TOP_OFFSET);
            Border_Submit.Height = submitHeight;
            Border_Submit.Width = width / 2;
            Canvas.SetLeft(Border_Submit, ((TopParent.Width * 0.5) - (Button_Submit.Width * 0.5)));
            Canvas.SetTop(Border_Submit, top + Constants.Form.SUBMIT_TOP + Constants.Form.SUBMIT_TOP_OFFSET);
        }

        // Setup home.
        private void SetupHome()
        {
            leftBrowser.Opacity = 0;
            rightBrowser.Opacity = 0;
            TopRectangle.Opacity = 0;
            TopRectangleBackground.Opacity = 0;
        }

        // Setup home buttons.
        private void SetupHomeButtons()
        {
            Button[] buttons = new Button[] {
                Survey_Button,
                Donate_Button,
                Volunteer_Button,
                GuestBook_Button
            };
            TextBlock[] textBlocks = new TextBlock[] {
                Survey_TextBlock,
                Donate_TextBlock,
                Volunteer_TextBlock,
                GuestBook_TextBlock
            };
            Border[] borders = new Border[] {
                Survey_TextBlockBorder,
                Donate_TextBlockBorder,
                Volunteer_TextBlockBorder,
                GuestBook_TextBlockBorder
            };
            TeardownButtons();
            for (int i = 0; i < buttons.Length; ++i)
            {
                buttons[i].Width = Constants.Home.BUTTON_WIDTH;
                buttons[i].Height = Constants.Home.HEIGHT;
                Canvas.SetLeft(buttons[i], Constants.Home.LEFT);
                Canvas.SetTop(buttons[i], Constants.Home.TOP + ((Constants.Home.MARGIN + Constants.Home.HEIGHT) * i));
                textBlocks[i].Width = Constants.Home.BUTTON_WIDTH;
                textBlocks[i].Height = Constants.Home.HEIGHT;
                textBlocks[i].Style = defaultStyle;
                textBlocks[i].FontSize = Constants.Home.FONT_SIZE;
                textBlocks[i].Padding = new Thickness(0, Constants.Home.TOP_PADDING, 0, 0);
                Canvas.SetLeft(textBlocks[i], Constants.Home.LEFT);
                Canvas.SetTop(textBlocks[i], Constants.Home.TOP + ((Constants.Home.MARGIN + Constants.Home.HEIGHT) * i));
                borders[i].Width = Constants.Home.BUTTON_WIDTH;
                borders[i].BorderThickness = new Thickness(Constants.Home.BORDER_THICKNESS, Constants.Home.BORDER_THICKNESS, Constants.Home.BORDER_THICKNESS, Constants.Home.BORDER_THICKNESS);
                borders[i].CornerRadius = new CornerRadius(Constants.Home.CORNER_RADIUS);
                Canvas.SetLeft(borders[i], Constants.Home.LEFT);
                Canvas.SetTop(borders[i], Constants.Home.TOP + ((Constants.Home.MARGIN + Constants.Home.HEIGHT) * i));
            }
            Survey_DropShadow.Opacity = 1;
            Donate_DropShadow.Opacity = 1;
            Volunteer_DropShadow.Opacity = 1;
            GuestBook_DropShadow.Opacity = 1;
        }

        // Setup JavaScript callbacks.
        private void SetupJavaScriptCallbacks()
        {
            rightBrowser.JavascriptObjectRepository.ResolveObject += (sender, e) =>
            {
                var repo = e.ObjectRepository;
                if (e.ObjectName == Constants.Callbacks.CALLBACK_001)
                {
                    repo.Register(
                        Constants.Callbacks.CALLBACK_001,
                        new DotNetMessage(),
                        isAsync: true,
                        options: BindingOptions.DefaultBinder
                    );
                }
            };
            rightBrowser.JavascriptObjectRepository.ResolveObject += (sender, e) =>
            {
                var repo = e.ObjectRepository;
                if (e.ObjectName == Constants.Callbacks.CALLBACK_002)
                {
                    repo.Register(
                        Constants.Callbacks.CALLBACK_002,
                        new DotNetMessage(),
                        isAsync: true,
                        options: BindingOptions.DefaultBinder
                    );
                }
            };
            rightBrowser.JavascriptObjectRepository.ResolveObject += (sender, e) =>
            {
                var repo = e.ObjectRepository;
                if (e.ObjectName == Constants.Callbacks.CALLBACK_003)
                {
                    repo.Register(
                        Constants.Callbacks.CALLBACK_003,
                        new DotNetMessage(),
                        isAsync: true,
                        options: BindingOptions.DefaultBinder
                    );
                }
            };
        }

        // Setup keyboard button.
        private void SetupKeyboardButton()
        {
            Keyboard_Button.Width = Constants.Keyboard.WIDTH;
            Keyboard_Button.Height = Constants.Keyboard.HEIGHT;
            Canvas.SetLeft(Keyboard_Button, Constants.Keyboard.LEFT);
            Canvas.SetTop(Keyboard_Button, Constants.Keyboard.TOP);
            Keyboard_TextBlock.Width = Constants.Keyboard.WIDTH;
            Keyboard_TextBlock.Height = Constants.Keyboard.HEIGHT;
            Keyboard_TextBlock.Style = defaultStyle;
            Keyboard_TextBlock.FontSize = Constants.Keyboard.FONT_SIZE;
            Keyboard_TextBlock.Padding = new Thickness(0, Constants.Keyboard.TOP_THICKNESS, 0, 0);
            Keyboard_TextBlockBorder.Width = Constants.Keyboard.WIDTH;
            Keyboard_TextBlockBorder.BorderThickness = new Thickness(Constants.Keyboard.THICKNESS, Constants.Keyboard.THICKNESS, Constants.Keyboard.THICKNESS, Constants.Keyboard.THICKNESS);
            Keyboard_TextBlockBorder.CornerRadius = new CornerRadius(Constants.Keyboard.CORNER_RADIUS);
            Canvas.SetLeft(Keyboard_TextBlockBorder, Constants.Keyboard.LEFT);
            Canvas.SetTop(Keyboard_TextBlockBorder, Constants.Keyboard.TOP);
        }

        // Setup pin button.
        private void SetupPinButton()
        {
            Pin_Button.Width = Constants.Pin.BUTTON_WIDTH;
            Pin_Button.Height = Constants.Pin.HEIGHT;
            Canvas.SetLeft(Pin_Button, Constants.Pin.LEFT);
            Canvas.SetTop(Pin_Button, Constants.Pin.TOP);
            Pin_TextBlock.Width = Constants.Pin.BUTTON_WIDTH;
            Pin_TextBlock.Height = Constants.Pin.HEIGHT;
            Pin_TextBlock.Style = defaultStyle;
            Pin_TextBlock.FontSize = Constants.Pin.FONT_SIZE;
            Pin_TextBlock.Padding = new Thickness(0, Constants.Pin.TOP_PADDING, 0, 0);
            Canvas.SetLeft(Pin_TextBlock, Constants.Pin.LEFT);
            Canvas.SetTop(Pin_TextBlock, Constants.Pin.TOP);
            Pin_TextBlockBorder.Width = Constants.Pin.BUTTON_WIDTH;
            Pin_TextBlockBorder.BorderThickness = new Thickness(Constants.Pin.BORDER_THICKNESS, Constants.Pin.BORDER_THICKNESS, Constants.Pin.BORDER_THICKNESS, Constants.Pin.BORDER_THICKNESS);
            Pin_TextBlockBorder.CornerRadius = new CornerRadius(Constants.Pin.CORNER_RADIUS);
            Canvas.SetLeft(Pin_TextBlockBorder, Constants.Pin.LEFT);
            Canvas.SetTop(Pin_TextBlockBorder, Constants.Pin.TOP);
        }


        // Setup prompt.
        public void SetupPrompt()
        {
            Prompt_TextBlock.Text = Constants.Prompt.TEXT;
            Prompt_TextBlock.Padding = new Thickness(0, Constants.Prompt.TOP_PADDING, 0, 0);
            Prompt_TextBlock.FontSize = Constants.Prompt.FONT_SIZE;
            Prompt_TextBlock.Style = defaultStyle;
            Prompt_TextBlock.Foreground = System.Windows.Media.Brushes.Black;
            Prompt_TextBlockBorder.Height = Constants.Prompt.HEIGHT;
            Prompt_TextBlockBorder.Width = Constants.Prompt.WIDTH;
            Canvas.SetLeft(Prompt_TextBlockBorder, Constants.Prompt.LEFT);
            Canvas.SetTop(Prompt_TextBlockBorder, Constants.Prompt.TOP);
        }

        // Setup styles not-setup by other functions.
        private void SetupStyles()
        {
            TextBlock_Submit.Style = defaultStyle;
        }

        // Setup tab buttons.
        private void SetupTabButtons(Button[] buttons, TextBlock[] textBlocks, Border[] borders)
        {
            TeardownButtons();
            TeardownForm();
            double buttonWidth = TopParent.Width / buttons.Length;
            for (int i = 0; i < buttons.Length; ++i)
            {
                buttons[i].Width = buttonWidth;
                buttons[i].Height = Constants.Tab.HEIGHT;
                Canvas.SetLeft(buttons[i], (buttonWidth * i));
                Canvas.SetTop(buttons[i], Constants.Tab.TOP);
            }
            for (int i = 0; i < textBlocks.Length; ++i)
            {
                textBlocks[i].Width = buttonWidth;
                textBlocks[i].Height = Constants.Tab.HEIGHT;
                textBlocks[i].Style = defaultStyle;
                textBlocks[i].FontSize = Constants.Tab.FONT_SIZE;
                textBlocks[i].Padding = new Thickness(0, Constants.Tab.TOP_PADDING, 0, 0);
                Canvas.SetLeft(textBlocks[i], (buttonWidth * i));
            }
            for (int i = 0; i < borders.Length; ++i)
            {
                borders[i].Width = buttonWidth;
                borders[i].BorderThickness = new Thickness(0, 0, 0, 0);
                borders[i].CornerRadius = new CornerRadius(0);
                Canvas.SetLeft(borders[i], (buttonWidth * i));
                Canvas.SetTop(borders[i], Constants.Tab.TOP);
            }
            Canvas.SetLeft(textBlocks[0], Constants.Tab.OFFSET);
            Canvas.SetLeft(borders[0], Constants.Tab.OFFSET);
            Canvas.SetLeft(textBlocks[textBlocks.Length - 1], TopParent.Width - buttonWidth - Constants.Tab.OFFSET);
            Canvas.SetLeft(borders[borders.Length - 1], TopParent.Width - buttonWidth - Constants.Tab.OFFSET);
            Survey_DropShadow.Opacity = 0;
            Donate_DropShadow.Opacity = 0;
            Volunteer_DropShadow.Opacity = 0;
            GuestBook_DropShadow.Opacity = 0;
        }

        // Setup worker threads.
        private void SetupWorkers()
        {
            System.Timers.Timer timer = new System.Timers.Timer();
            timer.Elapsed += new ElapsedEventHandler(WorkerJavaScriptInjection);
            timer.Elapsed += new ElapsedEventHandler(WorkerForceReload);
            timer.Elapsed += new ElapsedEventHandler(WorkerClearCache);
            timer.Interval = Constants.Time.INTERVAL;
            timer.Enabled = true;
        }

        // Teardown buttons.
        private void TeardownButtons()
        {
            Button[] buttons = new Button[] {
                Survey_Button,
                Donate_Button,
                Volunteer_Button,
                GuestBook_Button,
                Home_Button,
                Pin_Button,
            };
            TextBlock[] textBlocks = new TextBlock[] {
                Survey_TextBlock,
                Donate_TextBlock,
                Volunteer_TextBlock,
                GuestBook_TextBlock,
                Home_TextBlock,
                Pin_TextBlock,
            };
            Border[] borders = new Border[] {
                Survey_TextBlockBorder,
                Donate_TextBlockBorder,
                Volunteer_TextBlockBorder,
                GuestBook_TextBlockBorder,
                Home_TextBlockBorder,
                Pin_TextBlockBorder,
            };
            foreach (Button button in buttons)
            {
                button.Width = 0;
            }
            foreach (TextBlock textBlock in textBlocks)
            {
                textBlock.Width = 0;
            }
            foreach (Border border in borders)
            {
                border.Width = 0;
            }
        }

        // Teardown GoogleMaps input form.
        private void TeardownForm()
        {
            Border[] borders = new Border[]
            {
                Border_Form,
                Border_FormBackground,
                Border_FormTitle,
                Border_FirstNameBackground,
                Border_FirstNameForeground,
                Border_LastNameBackground,
                Border_LastNameForeground,
                Border_CityBackground,
                Border_CityForeground,
                Border_StateBackground,
                Border_StateForeground,
                Border_CountryBackground,
                Border_CountryForeground,
                Border_Submit
            };
            Button[] buttons = new Button[]
            {
                Button_FormBackground,
                Button_Submit,
            };
            TextBlock[] textBlocks = new TextBlock[]
            {
                TextBlock_FormTitle,
                TextBlock_Submit,
            };
            TextBox[] textBoxes = new TextBox[]
            {
                TextBox_FirstName,
                TextBox_LastName,
                TextBox_City,
                TextBox_State,
                TextBox_Country,
            };
            foreach (Border border in borders)
            {
                Canvas.SetLeft(border, 0);
                Canvas.SetTop(border, 0);
                border.Width = 0;
            }
            foreach (Button button in buttons)
            {
                Canvas.SetLeft(button, 0);
                Canvas.SetTop(button, 0);
                button.Width = 0;
            }
            foreach (TextBlock textBlock in textBlocks)
            {
                Canvas.SetLeft(textBlock, 0);
                Canvas.SetTop(textBlock, 0);
                textBlock.Width = 0;
                textBlock.Text = "";
            }
            foreach (TextBox textBox in textBoxes)
            {
                Canvas.SetLeft(textBox, 0);
                Canvas.SetTop(textBox, 0);
                textBox.Width = 0;
            }
            if (keyboardProcess != null)
            {
                try
                {
                    keyboardProcess.Kill();
                } catch (System.Exception e) { }
                keyboardProcess = null;
            }
        }

        // Teardown home page.
        private void TeardownHome()
        {
            leftBrowser.Opacity = 1;
            rightBrowser.Opacity = 1;
            TopRectangle.Opacity = 1;
            TopRectangleBackground.Opacity = 1;
        }

        // Teardown keyboard button.
        private void TeardownKeyboardButton()
        {
            Keyboard_Button.Width = 0;
            Keyboard_Button.Height = 0;
            Canvas.SetLeft(Keyboard_Button, 0);
            Canvas.SetTop(Keyboard_Button, 0);
            Keyboard_TextBlock.Width = 0;
            Keyboard_TextBlock.Height = 0;
            Keyboard_TextBlock.Style = defaultStyle;
            Keyboard_TextBlock.FontSize = Constants.Keyboard.FONT_SIZE;
            Keyboard_TextBlock.Padding = new Thickness(0, Constants.Keyboard.TOP_PADDING, 0, 0);
            Keyboard_TextBlockBorder.Width = 0;
            Keyboard_TextBlockBorder.BorderThickness = new Thickness(Constants.Keyboard.THICKNESS, Constants.Keyboard.THICKNESS, Constants.Keyboard.THICKNESS, Constants.Keyboard.THICKNESS);
            Keyboard_TextBlockBorder.CornerRadius = new CornerRadius(Constants.Keyboard.CORNER_RADIUS);
            Canvas.SetLeft(Keyboard_TextBlockBorder, 0);
            Canvas.SetTop(Keyboard_TextBlockBorder, 0);
        }

        // Teardown form guest page prompt.
        private void TeardownPrompt()
        {
            Prompt_TextBlockBorder.Width = 0;
            Prompt_TextBlockBorder.Height = 0;
        }

        // Clear cache when needed.
        private void WorkerClearCache(object source, ElapsedEventArgs notUsed)
        {
            if (MainWindow.isClearCacheBlocked)
            {
                return;
            }
            MainWindow.isClearCacheBlocked = true;
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(delegate ()
            {
                ClickVolunteer(null, null);
                // HERE

                Border_FormBackground.Height = TopParent.Height;
                Border_FormBackground.Width = TopParent.Width;
                Canvas.SetLeft(Border_FormBackground, 0);
                Canvas.SetTop(Border_FormBackground, 0);
                Button_FormBackground.Height = TopParent.Height;
                Button_FormBackground.Width = TopParent.Width;
                Canvas.SetLeft(Button_FormBackground, 0);
                Canvas.SetTop(Button_FormBackground, 0);
            }));
        }

        // Force reloaded when needed.
        private async void WorkerForceReload(object source, ElapsedEventArgs notUsed)
        {
            if (isReloadBlocked)
            {
                return;
            }
            rightBrowser.Reload();
            await Task.Delay(Constants.Time.SHORT_DELAY);
            isReloadBlocked = true;
        }

        // Inject map into guest page.
        private async void WorkerJavaScriptInjection(object source, ElapsedEventArgs notUsed)
        {
            if (isBlocked)
            {
                return;
            }
            isBlocked = true;
            StringBuilder sb = new StringBuilder();
            sb.Append(@"document.getElementById(""address"").value = """);
            sb.Append(MainWindow.location);
            sb.Append(@""";");
            await rightBrowser.EvaluateScriptAsync(sb.ToString(), Constants.Time.LONG_DELAY);
            await rightBrowser.EvaluateScriptAsync(@"document.getElementById(""submit"").click();", Constants.Time.LONG_DELAY);
        }
    }
}
