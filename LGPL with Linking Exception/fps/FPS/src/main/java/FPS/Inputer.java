/*
 * Title: Inputer file.
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

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;

// Just uses Frame for addMouseMotionListener() call.
public class Inputer implements MouseMotionListener {
    
    public static int sX = 0;
    public static int sY = 0;
    
    private int mX, mY;
    Frame mFrame;
    
    public Inputer(Frame frame) {
        mFrame = frame;
        mFrame.addMouseMotionListener(this);
    }
    
    public static int getX() {
        return sX;
    }
    
    public static int getY() {
        return sY;
    }
    
    public void mouseMoved(MouseEvent me) {
        mX = (int)me.getPoint().getX();
        mY = (int)me.getPoint().getY();
        sX = mX;
        sY = mY;
        mFrame.repaint();
    }
    
    public void mouseDragged(MouseEvent me) { mouseMoved(me); }
}
