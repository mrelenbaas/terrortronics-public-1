/*
 * Title: Game file.
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

package softfootfalls;

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

public class Game {
    
    private Inputer inputer;
    private Outputer outputer;
    private GUI mGUI;
    
    public Game() {
        //super("SmoothMove v1.0");
        super();
        
        outputer = new Outputer(inputer);
        inputer = new Inputer(outputer);
    }
    
    /*
    public void updater() {
        outputer.updater();
    }
    */
}
