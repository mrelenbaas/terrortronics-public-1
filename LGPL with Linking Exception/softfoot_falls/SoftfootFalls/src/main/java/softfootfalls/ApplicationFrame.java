/*
 * Title: ApplicationFrame file.
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
import java.awt.event.*;

/**
 * This came from the Java2D book.
 * @author mrele
 */
public class ApplicationFrame extends Frame{
    
    public ApplicationFrame() { this("Application Frame v1.0"); }
    
    public ApplicationFrame(String title) {
        super(title);
        createUI();
        System.out.println("Constructor complete.");
        repaint();
    }
    
    protected void createUI() {
        setSize(1280 + 16, 720 + 62);
        center();
        
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                dispose();
                System.exit(0);
            }
        });
    }
    
    public void center() {
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        Dimension frameSize = getSize();
        int x = (screenSize.width - frameSize.width) / 2;
        int y = (screenSize.height - frameSize.height) / 2;
        setLocation(x, y);
    }
}
