/*
 * Title: SwingDemo file.
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
import java.awt.Graphics;
import java.awt.Graphics2D;
import javax.swing.JPanel;

/**
 *
 * @author 
 */
public class SwingDemo extends JPanel {
    @Override
    public void paint(Graphics g) {
       Graphics2D graphic2d = (Graphics2D) g;
       graphic2d.setColor(Color.BLUE);
       graphic2d.fillRect(0, 0, 1000, 1000);
    }
}
