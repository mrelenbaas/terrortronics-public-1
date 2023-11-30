/*
 * Title: Outputer file.
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
import java.awt.Graphics;
import java.awt.Image;

public class Outputer extends ApplicationFrame {
    
    private boolean mBlock = false;
    private Image mBackground;
    private Image mBackground2;
    private Image mMonitor;
    private Image mMonitor2;
    private boolean mMonitorBlock = false;
    private Image mCat;
    private Image mNumber0;
    private Image mNumber1;
    private Image mNumber2;
    private Image mNumber3;
    private Image mNumber4;
    private Image mNumber5;
    private Image mNumber6;
    private Image mNumber7;
    private Image mNumber8;
    private Image mNumber9;
    
    private Image mImage;
    
    private int mX = 0;
    private int mY = 0;
    
    private Inputer mInputer;
    private Timer mTimer;
    
    //private Timer mTimer;
    
    public Outputer (Inputer inputer) {
        // todo: art should all get read in together, and stuck into a map where the key is the filename. Or, something.
        mInputer = inputer;
        mTimer = new Timer();
        System.out.println(System.getProperty("user.dir"));
        Image background = Utilities.blockingLoad(System.getProperty("user.dir") + "\\src\\art\\background.jpg");
        /*
        Image mBackground2 = Utilities.blockingLoad("");
        Image mMonitor = Utilities.blockingLoad("");
        Image mMonitor2 = Utilities.blockingLoad("");
        Image mCat = Utilities.blockingLoad("");
        Image mNumber0 = Utilities.blockingLoad("");
        Image mNumber1 = Utilities.blockingLoad("");
        Image mNumber2 = Utilities.blockingLoad("");
        Image mNumber3 = Utilities.blockingLoad("");
        Image mNumber4 = Utilities.blockingLoad("");
        Image mNumber5 = Utilities.blockingLoad("");
        Image mNumber6 = Utilities.blockingLoad("");
        Image mNumber7 = Utilities.blockingLoad("");
        Image mNumber8 = Utilities.blockingLoad("");
        Image mNumber9 = Utilities.blockingLoad("");
        */
        //mTimer = new Timer();
        
        //mBackground = Utilities.makeBufferedImage(background);
        setVisible(true);
        repaint();
    }
    
    public void setX(int x) {
        mX = x;
    }
    
    public void setY(int y) {
        mY = y;
    }
    
    public void update(Graphics g) {
        paint(g);
    }
    
    public void paint(Graphics g) {
        
        Dimension d = getSize();
        checkOffscreenImage();
        Graphics offG = mImage.getGraphics();
        offG.setColor(getBackground());
        offG.fillRect(0, 0, d.width, d.height);
        
        paintOffscreen(mImage.getGraphics());
        
        g.drawImage(mImage, 0, 0, null);
        
        mTimer.updater(this);
    }
    
    public void checkOffscreenImage() {
        Dimension d = getSize();
        if (mImage == null || mImage.getWidth(null) != d.width || mImage.getHeight(null) != d.height) {
            mImage = createImage(d.width, d.height);
        }
    }
    
    public void paintOffscreen(Graphics g) {
        mX = Inputer.getX();
        mY = Inputer.getY();
        int s = 100;
        g.drawImage(mBackground, 0, 0, this);
        g.setColor(Color.blue);
        g.fillRect(mX - s / 2, mY - s / 2, s, s);
    }
}
