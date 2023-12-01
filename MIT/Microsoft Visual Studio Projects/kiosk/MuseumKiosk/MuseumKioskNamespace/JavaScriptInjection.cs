/*
 * Title: JavaScriptInjection file.
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
    class JavaScriptInjection
    {
        public static string ClearCache()
        {
            return @"localStorage.clear();sessionStorage.clear();";
        }
    }
}
