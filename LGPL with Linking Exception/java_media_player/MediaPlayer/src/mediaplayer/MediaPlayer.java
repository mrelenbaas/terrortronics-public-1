/*
 * Title: MediaPlayer file.
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

package mediaplayer;

import java.io.UnsupportedEncodingException;
import java.net.InetAddress;
import java.net.UnknownHostException;
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;

public class MediaPlayer extends Application {
    
    @Override
    public void start(Stage stage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("FXMLDocument.fxml"));
        
        Scene scene = new Scene(root);
        stage.setTitle("Media Player");
        
        scene.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent doubleClicked) {
                if(doubleClicked.getClickCount() == 2) {
                    stage.setFullScreen(true);
                }
            }
        });
        
        stage.setScene(scene);
        stage.show();
    }
    
    /**
     * The main function.
     * 
     * @param args 
     */
    public static void main(String[] args) {
        launch(args);
        
        InetAddress host;
        int port = 0;
        try {
          //host = InetAddress.getByName(args[0]); 
          //port = Integer.parseInt(args[1]);
          host = InetAddress.getByName("192.168.1.70");
          port = Integer.parseInt("50007");
        } catch (RuntimeException | UnknownHostException ex) {
          System.out.println("Usage: java UDPPoke host port");
          return;
        }

        try {
          UDPPoke poker = new UDPPoke(host, port);
          byte[] response = poker.poke();
          if (response == null) {
            System.out.println("No response within allotted time");
            return;
          }
          String result = new String(response, "US-ASCII");
          System.out.println(result);
        } catch (UnsupportedEncodingException ex) {
          // Really shouldn't happen
          ex.printStackTrace();
        }
        }
}
