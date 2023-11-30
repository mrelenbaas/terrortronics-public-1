/*
 * Title: Timer file.
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

import java.awt.Frame;
import java.util.Date;

/**
 * Counts FPS.
 */
public class Timer {
    
    /**
     * 1 second.
     */
    public final int PERIOD = 1000;
    /**
     * Frames counted during previous second.
     */
    private long mFPS = 0L;
    /**
     * Frames counted during current second.
     */
    private long mCount = 0L;
    /**
     * Time (milliseconds) since start of second.
     */
    private long mCurrent = 0L;
    /**
     * Time (milliseconds) since January 1, 1970, 00:00:00 GMT.
     */
    private long mNow = 0L;
    /**
     * Time (milliseconds) at previous update.
     */
    private long mPrevious = 0L;
    
    /**
     * Counts frames for 1 second, then resets.
     * 
     * @param frame  Frame for FPS display.
     */
    public void updater(Frame frame) {
        mNow = new Date().getTime();
        mCurrent += mNow - mPrevious;
        mPrevious = mNow;
        mCount++;
        if (mCurrent > PERIOD) {
            mFPS = mCount;
            mCount = 0L;
            mCurrent = 0L;
            frame.setTitle("" + mFPS);
        }
    }
}
