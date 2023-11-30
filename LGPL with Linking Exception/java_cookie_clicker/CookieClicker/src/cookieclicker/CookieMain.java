/*
 * Title: CookieMain file.
 * Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * Version: 2
 * Date: September 15, 2023
 *
 * Intellectual Property:
 * Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 *
 * License:
 * This file is owned by Terrortronics / Bradley Elenbaas.
 * This file observes the LGPL with Linking Exception License.
 */

package cookieclicker;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.Timer;

/**
 * See <a href="https://www.youtube.com/watch?v=5AEIgLzueHk&list=PLejN69rU111NiOAX74MS7-nSAIY3uoXYo&index=1">Original Source</a>
 * @see <a href="https://www.youtube.com/watch?v=5AEIgLzueHk&list=PLejN69rU111NiOAX74MS7-nSAIY3uoXYo&index=1">Original Source</a>
 * @author 
 */
public class CookieMain {

    JLabel counterLabel, perSecLabel;
    JButton button1, button2, button3, button4;
    int cookieCounter, timerSpeed, cursorNumber, cursorPrice, grandpaNumber, grandpaPrice;
    double perSecond;
    boolean timerOn, grandpaUnlocked;
    Font font1, font2;
    CookieHandler cHandler = new CookieHandler();
    Timer timer;
    JTextArea messageText;
    MouseHandler mHandler = new MouseHandler();

    /**
     * The main function.
     * @param args
     */
    public static void main(String[] args) {

            new CookieMain();
            
            while(true){
                System.out.println("LOOP");
            }

    }

    /**
     *
     */
    public CookieMain() {

            timerOn = false;
            grandpaUnlocked = false;
            perSecond = 0;
            cookieCounter = 0;
            cursorNumber = 0;
            cursorPrice = 10;
            grandpaNumber = 0;
            grandpaPrice = 100;

            createFont();
            createUI();
    }

    /**
     *
     */
    public void createFont()
    {

            font1 = new Font("Comic Sans MS", Font.PLAIN, 32);
            font2 = new Font("Comic Sans MS", Font.PLAIN, 15);
    }

    /**
     *
     */
    public void createUI() {

            JFrame window = new JFrame();
            window.setSize(800, 600);
            window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            window.getContentPane().setBackground(Color.black);
            window.setLayout(null);
            
            JPanel cookiePanel = new JPanel();
            cookiePanel.setBounds(100, 220, 200, 200);
            cookiePanel.setBackground(Color.black);
            window.add(cookiePanel);

            ImageIcon cookie = new ImageIcon(getClass().getClassLoader().getResource("res/cookie200x200.png"));

            JButton cookieButton = new JButton();
            cookieButton.setBackground(Color.black);
            cookieButton.setFocusPainted(false);
            cookieButton.setBorder(null);
            cookieButton.setIcon(cookie);
            cookieButton.addActionListener(cHandler);
            cookieButton.setActionCommand("cookie");
            cookiePanel.add(cookieButton);

            JPanel counterPanel = new JPanel();
            counterPanel.setBounds(100, 100, 200, 100);
            counterPanel.setBackground(Color.black);
            counterPanel.setLayout(new GridLayout(2, 1));
            window.add(counterPanel);

            counterLabel = new JLabel(cookieCounter + " cookies");
            counterLabel.setForeground(Color.white);
            counterLabel.setFont(font1);
            counterPanel.add(counterLabel);

            perSecLabel = new JLabel();
            perSecLabel.setForeground(Color.white);
            perSecLabel.setFont(font2);
            counterPanel.add(perSecLabel);

            JPanel itemPanel = new JPanel();
            itemPanel.setBounds(500, 170, 250, 250);
            itemPanel.setBackground(Color.black);
            itemPanel.setLayout(new GridLayout(4, 1));
            window.add(itemPanel);

            button1 = new JButton("Cursor");
            button1.setFont(font1);
            button1.setFocusPainted(false);
            button1.addActionListener(cHandler);
            button1.setActionCommand("Cursor");
            button1.addMouseListener(mHandler);
            itemPanel.add(button1);

            button2 = new JButton("?");
            button2.setFont(font1);
            button2.setFocusPainted(false);
            button2.addActionListener(cHandler);
            button2.setActionCommand("Grandpa");
            button2.addMouseListener(mHandler);
            itemPanel.add(button2);

            button3 = new JButton("?");
            button3.setFont(font1);
            button3.setFocusPainted(false);
            button3.addActionListener(cHandler);
            button3.setActionCommand("");
            button3.addMouseListener(mHandler);
            itemPanel.add(button3);

            button4 = new JButton("?");
            button4.setFont(font1);
            button4.setFocusPainted(false);
            button4.addActionListener(cHandler);
            button4.setActionCommand("");
            button4.addMouseListener(mHandler);
            itemPanel.add(button4);

            JPanel messagePanel = new JPanel();
            messagePanel.setBounds(500, 70, 250, 150);
            messagePanel.setBackground(Color.black);
            window.add(messagePanel);

            messageText = new JTextArea();
            messageText.setBounds(500, 70, 250, 150);
            messageText.setForeground(Color.white);
            messageText.setBackground(Color.black);
            messageText.setFont(font2);
            messageText.setLineWrap(true);
            messageText.setWrapStyleWord(true);
            messageText.setEditable(false);
            messagePanel.add(messageText);
            
            //JFrame frame = new JFrame("Demo");
            //frame.add(new SwingDemo());
            //window.add(new SwingDemo());
            //window.setSize(550, 250);
            //frame.setVisible(true);
            //frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            //window.add(frame);
            
            //JPanel counterPanel = new JPanel();
            //counterPanel.setBounds(100, 100, 200, 100);
            //counterPanel.setBackground(Color.black);
            //counterPanel.setLayout(new GridLayout(2, 1));
            //window.add(counterPanel);
            
            SwingDemo swingDemo = new SwingDemo();
            swingDemo.setBounds(100, 0, 200, 100);
            //swingDemo.setBackgroundColor(Color.RED);
            //swingDemo.setLayout();
            window.add(swingDemo);

            window.setVisible(true);
    }

    /**
     *
     */
    public void setTimer() {

            timer = new Timer(timerSpeed, new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {

                            cookieCounter++;
                            counterLabel.setText(cookieCounter + " cookies");

                            if(grandpaUnlocked == false) {
                                    if(cookieCounter >= 100) {
                                            grandpaUnlocked = true;
                                            button2.setText("Grandpa " + "(" + grandpaNumber + ")");
                                    }
                            }
                    }
            });
    }

    /**
     *
     */
    public void timerUpdate() {

            if(timerOn == false) {
                    timerOn = true;
            }
            else if(timerOn == true) {
                    timer.stop();
            }

            double speed = 1/perSecond*1000;
            timerSpeed = (int)Math.round(speed);

            String s = String.format("%.1f", perSecond);
            perSecLabel.setText("per second: " + s);

            setTimer();
            timer.start();
    }

    /**
     *
     */
    public class CookieHandler implements ActionListener {

            @Override
            public void actionPerformed(ActionEvent e) {

                    String action = e.getActionCommand();

                    switch(action)
                    {
                    case "cookie":
                            cookieCounter++;
                            counterLabel.setText(cookieCounter + " cookie");
                            break;
                    case "Cursor":
                            if(cookieCounter >= cursorPrice) {
                                    cookieCounter = cookieCounter - cursorPrice;
                                    cursorPrice = cursorPrice + 5;
                                    counterLabel.setText(cookieCounter + " cookies");

                                    cursorNumber++;
                                    button1.setText("Cursor" + "(" + cursorNumber + ")");
                                    messageText.setText("Cursor\n[price: " + cursorPrice + "]\nAutoclicks once every 10 seconds.");
                                    perSecond = perSecond + 0.1;
                                    timerUpdate();
                            }
                            else {
                                    messageText.setText("You need more cookies!");
                            }
                            break;
                    case "Grandpa":
                            if(cookieCounter >= grandpaPrice) {
                                    cookieCounter = cookieCounter - grandpaPrice;
                                    grandpaPrice = grandpaPrice + 50;
                                    counterLabel.setText(cookieCounter + " cookies");

                                    grandpaNumber++;
                                    button2.setText("Grandpa " + "(" + grandpaNumber + ")");
                                    messageText.setText("Grandpa\n[price: " + grandpaPrice + "]\nEach grandpa produces 1 cookie per second.");
                                    perSecond = perSecond + 1;
                                    timerUpdate();
                            }
                            else {
                                    messageText.setText("You need more cookies!");
                            }
                            break;
                    }

                    //cookieCounter++;
                    counterLabel.setText(cookieCounter + " cookies");
            }
    }

    /**
     *
     */
    public class MouseHandler implements MouseListener{

            @Override
            public void mouseClicked(MouseEvent e) {
                    // TODO Auto-generated method stub

            }

            @Override
            public void mousePressed(MouseEvent e) {
                    // TODO Auto-generated method stub

            }

            @Override
            public void mouseReleased(MouseEvent e) {
                    // TODO Auto-generated method stub

            }

            @Override
            public void mouseEntered(MouseEvent e) {

                    JButton button = (JButton)e.getSource();

                    if(button == button1) {
                            messageText.setText("Cursor\n[price: " + cursorPrice + "]\nAutoclicks once every 10 seconds.");
                    }
                    else if(button == button2) {
                            if(grandpaUnlocked == false) {
                                    messageText.setText("This item is currently locked!");
                            }
                            else {
                                    messageText.setText("Grandpa\n[price: " + grandpaPrice + "]\nEach grandpa produces 1 cookie per second.");
                            }

                    }
                    else if(button == button3) {
                            messageText.setText("This item is currently locked!");
                    }
                    else if(button == button4) {
                            messageText.setText("This item is currently locked!");
                    }
            }

            @Override
            public void mouseExited(MouseEvent e) {

                    JButton button = (JButton)e.getSource();

                    if(button == button1) {
                            messageText.setText(null);
                    }
                    else if(button == button2) {
                            messageText.setText(null);
                    }
                    else if(button == button3) {
                            messageText.setText(null);
                    }
                    else if(button == button4) {
                            messageText.setText(null);
                    }
            }

    }
}
