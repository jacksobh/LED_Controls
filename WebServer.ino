#include <DHT.h>
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0E, 0xC6, 0xDA
};
IPAddress ip(192, 168, 0, 102);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

  // For analog reading
   #define LightSensor A0
   #define TempSensor A3
   #define DHTSensor A5
   int LightValue = 0;
   int TempValue = 0;
   int DHTValue = 0;
   
void setup() {

   
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
           client.println("<body bgcolor=#ff9966");
             client.println("<head>");
               client.println("This is Ben Jackson");
                client.println("<br />");
                client.println("<center>");
                client.println("<h1>");
                 client.println("Weather Currently");
                client.println("</h1>");
             client.println("<head>");
                client.println("<br />");
          
          LightValue = analogRead(LightSensor);
          TempValue = 1.3*analogRead(TempSensor);
          int RealTemp = (TempValue*(9/5) + 32);
               client.println("<h3>");
          client.print("Light Sensor:  ");
         if (LightValue <= 375)
          {
            client.print("Night");
            
          }
          else if (LightValue > 600)
          {
             client.println("Dawn or Dusk");
            
          }

          else
          {
             client.println("Day");
           
          
          }
           client.println("<br>");
                 client.println("<center>");    
                  client.print("It is currently:  ");
                  client.println(RealTemp);
                  client.println("&deg;");
                  client.println(" outside with a humidity of ___. ");
                  client.println("<br />");
                  client.println("DHT Sensor: ");
                  client.println(DHTSensor);
                  client.println("<br>");
                  client.println("Check the Extended weather in your area ");
                  client.println("<a href=http://www.weather.com target=_blank>here</a>");

               client.println("<h3/>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
    Ethernet.maintain();
  }
}
 
