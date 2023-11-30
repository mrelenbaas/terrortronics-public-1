/*
 * Title: AnimationFrame file.
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
import java.text.NumberFormat;

public class AnimationFrame extends ApplicationFrame {
    private Label mStatusLabel;
    private NumberFormat mFormat;
    
    public AnimationFrame(AnimationComponent ac) {
        super("AnimationFrame v1.0");
        setLayout(new BorderLayout());
        add(ac, BorderLayout.CENTER);
        add(mStatusLabel = new Label(), BorderLayout.SOUTH);
        
        mFormat = NumberFormat.getInstance();
        mFormat.setMaximumFractionDigits(1);
        
        ac.setRateListener(this);
        
        Thread t = new Thread(ac);
        t.start();
    }
    
    public void rateChanged(double frameRate) {}
}
