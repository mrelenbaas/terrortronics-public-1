/*
 * Title: Handlers file.
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
// Override inherited handlers.

// Command-Line Arguments and Error Levels
//---------------------------
// No Command-Line Arguments of Error Levels.

// Unit Tests
//----------
// No unit tests.

using CefSharp;
using CefSharp.Enums;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MuseumKioskNamespace
{
    abstract class Handlers
    {
        /*
        // Disables middle click dragging.
        public class Drag : IDragHandler
        {
            public bool OnDragEnter(IWebBrowser chromiumWebBrowser, IBrowser browser, IDragData dragData, DragOperationsMask mask)
            {
                return false;
            }

            public void OnDraggableRegionsChanged(IWebBrowser chromiumWebBrowser, IBrowser browser, IFrame frame, IList<DraggableRegion> regions)
            {
                return;
            }
        }
        */

        // Disables pop-up windows.
        public class LifeSpan_LeftBrowser : ILifeSpanHandler
        {
            public bool OnBeforePopup(IWebBrowser browserControl, IBrowser browser, IFrame frame, string targetUrl, string targetFrameName, WindowOpenDisposition targetDisposition, bool userGesture, IPopupFeatures popupFeatures, IWindowInfo windowInfo, IBrowserSettings browserSettings, ref bool noJavascriptAccess, out IWebBrowser newBrowser)
            {
                newBrowser = null;
                return true;
            }

            public void OnAfterCreated(IWebBrowser browserControl, IBrowser browser) {}

            public bool DoClose(IWebBrowser browserControl, IBrowser browser)
            {
                return false;
            }

            public void OnBeforeClose(IWebBrowser browserControl, IBrowser browser) {}
        }

        // Disables right click from opening a menu.
        public class Menu : IContextMenuHandler
        {
            public void OnBeforeContextMenu(IWebBrowser browserControl, IBrowser browser, IFrame frame, IContextMenuParams parameters, IMenuModel model)
            {
                model.Clear();
            }

            public bool OnContextMenuCommand(IWebBrowser browserControl, IBrowser browser, IFrame frame, IContextMenuParams parameters, CefMenuCommand commandId, CefEventFlags eventFlags)
            {
                return false;
            }

            public void OnContextMenuDismissed(IWebBrowser browserControl, IBrowser browser, IFrame frame) { }

            public bool RunContextMenu(IWebBrowser browserControl, IBrowser browser, IFrame frame, IContextMenuParams parameters, IMenuModel model, IRunContextMenuCallback callback)
            {
                return false;
            }
        }
    }
}
