/*
 * Title: AnimationComponent file.
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

import java.awt.*;

public abstract class AnimationComponent extends Container implements Runnable {
    private boolean mTrucking = true;
    private long[] mPreviousTimes;
    private int mPreviousIndex;
    private boolean mPreviousFilled;
    private double mFrameRate;
    private Image mImage;
    
    public AnimationComponent() {
        mPreviousTimes = new long[128];
        mPreviousTimes[0] = System.currentTimeMillis();
        mPreviousIndex = 1;
        mPreviousFilled = false;
    }
    
    public abstract void timeStep();
    
    public void run() {
        while (mTrucking) {
            render();
            timeStep();
            calculateFrameRate();
        }
    }
    
    protected void render() {
        Graphics g = getGraphics();
        if (g != null) {
            Dimension d = getSize();
            if (checkImage(d)) {
                Graphics imageGraphics = mImage.getGraphics();
                
                imageGraphics.setColor(getBackground());
                imageGraphics.fillRect(0, 0, d.width, d.height);
                imageGraphics.setColor(getForeground());
                
                paint(imageGraphics);
                
                g.drawImage(mImage, 0, 0, null);
                
                imageGraphics.dispose();
            }
            g.dispose();
        }
    }
    
    protected boolean checkImage(Dimension d) {
        if (d.width == 0 || d.height == 0) return false;
        if (mImage == null || mImage.getWidth(null) != d.width || mImage.getHeight(null) != d.height) {
            mImage = createImage(d.width, d.height);
        }
        return true;
    }
    
    protected void calculateFrameRate() {
        long now = System.currentTimeMillis();
        int numberOfFrames = mPreviousTimes.length;
        double newRate;
        
        if (mPreviousFilled)
            newRate = (double)numberOfFrames / (double)(now - mPreviousTimes[mPreviousIndex]) * 1000.0;
        else
            newRate = 1000.0 / (double)(now - mPreviousTimes[numberOfFrames - 1]);
        //System.out.println(newRate);
        firePropertyChange("frameRate", mFrameRate, newRate);
        mFrameRate = newRate;
        
        mPreviousTimes[mPreviousIndex] = now;
        mPreviousIndex++;
        if (mPreviousIndex >= numberOfFrames) {
            mPreviousIndex = 0;
            mPreviousFilled = true;
        }
    }
    
    public double getFrameRate() { return mFrameRate; }
    
    private transient AnimationFrame mRateListener;
    
    public void setRateListener(AnimationFrame af) {
        mRateListener = af;
    }
    
    public void firePropertyChange(String name, double oldValue, double newValue) {
        mRateListener.rateChanged(newValue);
    }
}
