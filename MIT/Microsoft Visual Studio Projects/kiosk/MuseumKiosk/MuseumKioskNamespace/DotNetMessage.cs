/*
 * Title: DotNetMessage file.
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
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using MuseumKioskNamespace;

namespace MuseumKioskNamespace
{

    // TODO: Rename this class to something less confusing.
    // TODO: Replace the "last" naming convention with the "previous" naming convention.
    // TODO: Replace the "lat" & "lng" naming conventions with the "latitude" & "longitude" naming conventions.
    public class DotNetMessage
    {
        private static List<string> firstNames = new List<string>();
        private static List<string> lastNames = new List<string>();
        private static List<string> cityTowns = new List<string>();
        private static List<string> stateProvinces = new List<string>();
        private static List<string> countries = new List<string>();
        private static List<string> lats = new List<string>();
        private static List<string> lngs = new List<string>();

        private static string lastFirstName = "";
        private static string lastLastName = "";
        private static string lastCity = "";
        private static string lastState = "";
        private static string lastCountry = "";
        private static string lastLat = "";
        private static string lastLng = "";

        public static void SetLastFirstName(string firstName)
        {
            lastFirstName = firstName;
        }

        public static void SetLastLastName(string lastName)
        {
            lastLastName = lastName;
        }

        public static void SetLastCity(string city)
        {
            lastCity = city;
        }

        public static void SetLastState(string state)
        {
            lastState = state;
        }

        public static void SetLastCountry(string country)
        {
            lastCountry = country;
        }

        // TODO: Rename this something more helpful.
        public void Hello(string message)
        {
            String[] results = message.Split(',');
            String lat = results[0];
            String lng = results[1];
            StringBuilder sb = new StringBuilder();
            sb.Append(lastFirstName);
            sb.Append(@",");
            sb.Append(lastLastName);
            sb.Append(@",");
            sb.Append(lastCity);
            sb.Append(@",");
            sb.Append(lastState);
            sb.Append(@",");
            sb.Append(lastCountry);
            sb.Append(@",");
            sb.Append(lat);
            sb.Append(@",");
            sb.Append(lng);
            sb.Append(@",");
            if (lat == lastLat && lng == lastLng)
            {
                lastLat = "";
                lastLng = "";
            }
            else
            {
                lastLat = lat;
                lastLng = lng;
                Write(sb.ToString());
                Read();
            }
        }

        public static void Write(string message)
        {
            System.Console.WriteLine("Write: " + message);
            string newFileName = Constants.Filename.newFileName;
            string clientDetails = message + "\r\n";
            clientDetails = clientDetails.Replace(";", "");
            if (!File.Exists(newFileName))
            {
                string clientHeader = "Client Name(ie. Billto_desc)" + "," + "Mid_id,billing number(ie billto_id)" + "," + "business unit id" + Environment.NewLine;
                File.WriteAllText(newFileName, clientHeader);
            }
            File.AppendAllText(newFileName, clientDetails);
        }

        public static void Read()
        {
            firstNames.Clear();
            lastNames.Clear();
            cityTowns.Clear();
            stateProvinces.Clear();
            countries.Clear();
            lats.Clear();
            lngs.Clear();
            var reader = new StreamReader(Constants.Filename.newFileName);
            try
            {
                int i = 0;
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var values = line.Split(',');
                    firstNames.Add(values[0]);
                    lastNames.Add(values[1]);
                    cityTowns.Add(values[2]);
                    stateProvinces.Add(values[3]);
                    countries.Add(values[4]);
                    lats.Add(values[5]);
                    lngs.Add(values[6]);
                    ++i;
                }
            }
            catch (Exception e)
            {
                reader.Close();
                throw e;
            }
            reader.Close();
        }

        public static void DeleteLastLine(string filepath)
        {
            List<string> lines = File.ReadAllLines(filepath).ToList();
            lines.RemoveAt(lines.Count - 1);
            File.WriteAllLines(filepath, lines.GetRange(0, lines.Count).ToArray());
            
        }

        public static List<string> GetFirstNames()
        {
            return firstNames;
        }

        public static List<string> GetLastNames()
        {
            return lastNames;
        }

        public static List<string> GetCityTowns()
        {
            return cityTowns;
        }

        public static List<string> GetStateProvinces()
        {
            return stateProvinces;
        }

        public static List<string> GetCountries()
        {
            return countries;
        }

        public static List<string> GetLats()
        {
            return lats;
        }

        public static List<string> GetLngs()
        {
            return lngs;
        }
    }
}
