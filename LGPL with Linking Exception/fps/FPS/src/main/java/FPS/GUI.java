/*
 * Title: GUI file.
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

package FPS;

import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;

public class GUI extends Frame {
    
    Timer mTimer;
    
    public GUI() {
        mTimer = new Timer();
        setFont(new Font("Serif", Font.PLAIN, 12));
        setLayout(new BorderLayout());
        
        setSize(200, 350);
        
        setVisible(true);
    }
    
    public void paint(Graphics g) {
        mTimer.updater(this);
        repaint();
    }
}
