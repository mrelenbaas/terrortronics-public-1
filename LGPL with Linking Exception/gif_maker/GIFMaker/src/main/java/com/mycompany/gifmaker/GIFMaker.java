/*
 * Title: GIFMaker file.
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

// TODO: Reverse the parameter order such that the output file comes first 
// instead of last.

package com.mycompany.gifmaker;

import javax.imageio.*;
import javax.imageio.metadata.*;
import javax.imageio.stream.*;
import java.awt.image.*;
import java.io.*;
import java.util.Iterator;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author 
 */
public class GIFMaker {

    /**
     * The main function.
     * 
     * @param args 
     */
    public static void main(String[] args) {
        System.out.println("-1");
        if (args.length > 1) {
            try {
                System.out.println(args[0]);
                System.out.println("0");
                // grab the output image type from the first image in the sequence
                BufferedImage firstImage = ImageIO.read(new File(args[0]));
                
                System.out.println("1");
                // create a new BufferedOutputStream with the last argument
                ImageOutputStream output
                        = new FileImageOutputStream(new File(args[args.length - 1]));
                
                System.out.println("2");
                // create a gif sequence with the type of the first image, 1 second
                // between frames, which loops continuously
                GIFSequenceWriter writer
                        = new GIFSequenceWriter(output, firstImage.getType(), 1, false);
                
                System.out.println("3");
                // write out the first image to our sequence...
                writer.writeToSequence(firstImage);
                for (int i = 1; i < args.length - 1; i++) {
                    System.out.println("i: " + i);
                    BufferedImage nextImage = ImageIO.read(new File(args[i]));
                    writer.writeToSequence(nextImage);
                    System.out.println("i: " + i);
                }
                
                System.out.println("4");
                writer.close();
                output.close();
                System.out.println("5");
            } catch (IOException ex) {
                System.out.println("XXX: " + args[0]);
                Logger.getLogger(GIFMaker.class.getName()).log(Level.SEVERE, null, ex);
            }
        } else {
            System.out.println(
                    "Usage: java GifSequenceWriter [list of gif files] [output file]");
        }
    }
}
