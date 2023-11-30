/*
 * Title: SoftfootFalls file.
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

// NOTE: the profiler is built into NetBeans.

import java.util.Date;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import static java.util.concurrent.TimeUnit.*;

public class SoftfootFalls implements Runnable {

    private Game mGame;
    private GUI mGUI;
    //private Timer mTimer;
    
    private Date mDate;
    private final ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);
        
    public static void main(String[] args) {
        SoftfootFalls softfootFalls = new SoftfootFalls();
        //softfootFalls.someFunctionWrapper();
    }
    
    public SoftfootFalls() {
        mGame = new Game();
        mGUI = new GUI();
        //mTimer = new Timer();
        
        mDate = new Date();
    }
    
    public void someFunctionWrapper() {
        final Runnable someRunnable = new Runnable() {
                public void run() {
                    //System.out.println("Run");
                    someFunction();
                }
            };
        final ScheduledFuture<?> someHandle = scheduler.scheduleAtFixedRate(someRunnable, 1000, 1, NANOSECONDS);
        scheduler.schedule(new Runnable() {
                public void run() {
                    someHandle.cancel(true);
                }
            }, 60 * 60, SECONDS);
    }
    
    public void someFunction() {
        //boolean result = mTimer.updater();
        //long fps = mTimer.getFPS();
        //if (result) {
            //mTimer.output();
        //}
    }

    public void run() {
        /*
        boolean result = mTimer.updater();
        long fps = mTimer.getFPS();
        if (result) {
            mTimer.output();
        }
*/
        //mGame.updater();
    }
}
