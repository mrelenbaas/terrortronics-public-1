/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mediaplayer;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UDPPoke {

  private int bufferSize; // in bytes
  private int timeout; // in milliseconds
  private InetAddress host; 
  private int port; 
   
  public UDPPoke(InetAddress host, int port, int bufferSize, int timeout) {
    this.bufferSize = bufferSize;
    this.host = host;
    if (port < 1 || port > 65535) {
      throw new IllegalArgumentException("Port out of range");
    }

    this.port = port;
    this.timeout = timeout;
  }
  
  public UDPPoke(InetAddress host, int port, int bufferSize) {
    this(host, port, bufferSize, 30000);
  }
  
  public UDPPoke(InetAddress host, int port) {
    this(host, port, 8192, 30000);
  }
  
  public byte[] poke() {
    try (DatagramSocket socket = new DatagramSocket(0)) {
      String someString = "java,right";
      //byte[] someByteArray = someString.getBytes();
      DatagramPacket outgoing = new DatagramPacket(someString.getBytes(), someString.length(), host, port);
      socket.connect(host, port);
      socket.setSoTimeout(timeout);
      
      socket.send(outgoing);
      DatagramPacket incoming 
          = new DatagramPacket(new byte[bufferSize], bufferSize);
      // next line blocks until the response is received
      socket.receive(incoming);
      int numBytes = incoming.getLength();
      byte[] response = new byte[numBytes];
      System.arraycopy(incoming.getData(), 0, response, 0, numBytes);
      System.out.println(response);
      return response;
    } catch (IOException ex) {
      return null;
    } 
  }
}
