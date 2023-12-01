/*
 * Title: Form1.Designer file.
 * Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * Version: 2
 * Date: September 15, 2023
 *
 * Intellectual Property:
 * Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 *
 * License:
 * This file is owned by Terrortronics / Bradley Elenbaas.
 * This file observes the MIT License.
 */

using System;
using System.Windows.Forms;
using System.IO.Ports;
using System.Text;

namespace usb
{
    partial class Form1
    {
        SerialPort port;

        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        /// <summary>
        ///  Pseudo-Constructor.
        ///  Performs try/catch discovery.
        /// </summary>
        public void Setup()
        {
            Console.WriteLine("START");
            InitializeComponent();
            this.FormClosed += new FormClosedEventHandler(Form1_FormClosed);
            button1.Click += new EventHandler(button1_Click);
            button2.Click += new EventHandler(button2_Click);
            if (port == null)
            {
                for (int i = 0; i < 256; i++)
                {
                    //port = new SerialPort("COM25", 9600);//Set your board COM
                    try
                    {
                        port = new SerialPort(new StringBuilder().Append("COM").Append(i).ToString(), 9600);//Set your board COM
                        port.Open();
                        break;
                    }
                    catch (System.Exception e)
                    {

                    }
                }
                //port = new SerialPort("COM25", 9600);//Set your board COM
                //port.Open();
                PortWrite("1");
                //byte[] buffer = new byte[2];
                //port.Read(buffer, 0, 2);
                //Console.WriteLine(buffer[0]);
                //port.Close();
            }
        }

        void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (port != null && port.IsOpen)
            {
                port.Close();
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            Console.WriteLine("one");
            PortWrite("1");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Console.WriteLine("two");
            PortWrite("0");
        }
        private void PortWrite(string message)
        {
            port.Write(message);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            button1 = new Button();
            button2 = new Button();
            SuspendLayout();
            // 
            // button1
            // 
            button1.Location = new Point(324, 104);
            button1.Name = "button1";
            button1.Size = new Size(75, 23);
            button1.TabIndex = 0;
            button1.Text = "button1";
            button1.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            button2.Location = new Point(365, 180);
            button2.Name = "button2";
            button2.Size = new Size(75, 23);
            button2.TabIndex = 1;
            button2.Text = "button2";
            button2.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(button2);
            Controls.Add(button1);
            Name = "Form1";
            Text = "Form1";
            ResumeLayout(false);
        }

        #endregion

        private Button button1;
        private Button button2;
    }
}