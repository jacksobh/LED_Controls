#include <SPI.h>
#include <Ethernet.h>

#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3

int RedVal = 0; 
int GreenVal = 0;
int BlueVal = 0;

//photoResistor set up
#define Value A5
int sensor = 0;
int Dim = 0;
int Dim1 = 0;
int brightness = 150;

byte mac[] = { 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45 };  //Replace MAC Address with Devices own MAC Address
IPAddress ip(192, 168, X, X);  // Choose your IP Adress that you would like to use


// (port 80 is default for HTTP):
EthernetServer server(80);
String readString; //For Buttons

void setup() {

  pinMode(REDPIN, OUTPUT);  //Pin modes
pinMode(GREENPIN, OUTPUT);
pinMode(BLUEPIN, OUTPUT);

Serial.begin(9600);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  } 


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP()); //Debug
} 

void loop() {
 
  // Create a client connection
  EthernetClient client = server.available();   
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          //Serial.print(c);
         }

         //if HTTP request has ended
         if (c == '\n') {          
           Serial.println(readString); //print to serial monitor for debuging
     
           client.println("HTTP/1.1 200 OK");          //Starting the setup for Webpage
           client.println("Content-Type: text/html");
           client.println("Connection: close");
           client.println("Refresh: 2");
           client.println();     
           client.println("<HTML><HEAD>");
           client.println("<body bgcolor= #bcc6cc>");
           client.println("<font face= Georgia color = #8c001a>");
           
           client.println("</HEAD><BODY>");
           client.println("<center><H1>LUMANARY LIGHTS</H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<H2>Select The type of light show</H2>");
           client.println("<br /><H2>");  
           client.println("<a href=\"/White_ON\"\">ON</a>");
           client.println("<a href=\"/Run_OFF\"\">OFF</a><br />");   
           client.println("  Brightness: ");
           client.println("<a href=\"/BRIGHTNESS_HIGH\"\">HIGH</a>");
           client.println("<a href=\"/BRIGHTNESS_MEDIUM\"\">MEDIUM</a>");  
           client.println("<a href=\"/BRIGHTNESS_LOW\"\">LOW</a>");
           client.println("<a href=\"/AUTOMATIC\"\">AUTOMATIC</a>");
           client.println("<br />");
           client.println("<br />");
           client.println("<a href=\"/buttonRED_ON\"\">Red ON</a>");
           client.println("<a href=\"/button1RED_OFF\"\">Red OFF</a><br />");   
           client.println("<br />"); 
           client.println("<a href=\"/buttonGREEN_ON\"\">Green ON</a>");
           client.println("<a href=\"/buttonGREEN_OFF\"\">Green OFF</a><br />"); 
           client.println("<br />"); 
           client.println("<a href=\"/buttonBLUE_ON\"\">Blue ON</a>");
           client.println("<a href=\"/buttonBLUE_OFF\"\">Blue OFF</a><br />"); 
           client.println("</H2><H3><br>Automatic</H3>");
           client.println("<br />");
           client.println("<a href=\"/Run_ON\"\">ON</a>");
           client.println("<a href=\"/Run_OFF\"\">OFF</a><br />"); 
           client.println("<br />");
           client.println("</center></BODY>");
           client.println("</HTML>");
     
           delay(1);
           //stopping client
           client.stop();
           //controls the Arduino if you press the buttons

         //Buttons to control the LED Strip

         if (readString.indexOf("White_ON") >0)   // >0 B/c if it can't find the string then it returns a -1
             {

               analogWrite(REDPIN,brightness);
               analogWrite(GREENPIN,brightness);
               analogWrite(BLUEPIN,brightness);
             }
             else if(readString.indexOf("AUTOMATIC")>0)
             {
                sensor = analogRead(Value);
                Dim1 = map(sensor,940,1000,1,254);
                Dim1 = abs(Dim1);
                Serial.println(Dim1);
                Serial.println(sensor); // Debug
               analogWrite(REDPIN,Dim1);
               analogWrite(GREENPIN,Dim1);
               analogWrite(BLUEPIN,Dim1);
             }

          else if (readString.indexOf("BRIGHTNESS_HIGH") >0)  // LEDs are HIGH
             {
             brightness = 250;
             }

         else if (readString.indexOf("BRIGHTNESS_MEDIUM") >0) // LEDs are Medium
             {
             brightness = 128;
             }

         else if (readString.indexOf("BRIGHTNESS_LOW") >0)  // LEDs are Low
             {
             brightness = 20;
             }
                                
          else if (readString.indexOf("buttonRED_ON") >0)
             {
               analogWrite(REDPIN,brightness);  // Red LED is ON
             }
          else if (readString.indexOf("button1RED_OFF") >0)
             {
              analogWrite(REDPIN,0);  //Red LED is OFF
             }
          else if (readString.indexOf("buttonGREEN_ON") >0)
             {
                analogWrite(GREENPIN,brightness); //Green LED is ON
             }
          else if (readString.indexOf("buttonGREEN_OFF") >0)
             {
             analogWrite(GREENPIN,0);       //Green LED is OFF
             } 
           else if (readString.indexOf("buttonBLUE_ON") >0)
             {
             analogWrite(BLUEPIN,brightness);   //Blue LED is ON
             }
          else if (readString.indexOf("buttonBLUE_OFF") >0)
             {
             analogWrite(BLUEPIN,0);     //Blue LED is OFF
             }

          if(readString.indexOf("Run_ON") > 0)  // Goes though colors
          {

            for(int i = 0; i <151; i++)
            {
              analogWrite(REDPIN, i);  // turns RED
              analogWrite(GREENPIN, 0);
              analogWrite(BLUEPIN, 0);
              delay(25);
            }
             for(int i = 0; i <151; i++)
            {
              analogWrite(REDPIN, 150-i);  
              analogWrite(GREENPIN, i);   //RED to Green
              analogWrite(BLUEPIN, 0);
              delay(25);
            }
             for(int i = 0; i <151; i++)
            {
              analogWrite(REDPIN, 0);
              analogWrite(GREENPIN, 150-i);
              analogWrite(BLUEPIN, i);    // Green to Blue
              delay(25);
            }
             for(int i = 0; i <151; i++)
            {
              analogWrite(REDPIN, 0);
              analogWrite(GREENPIN,0);
              analogWrite(BLUEPIN, 150-i);
              delay(25);
            }
              delay(100);
              for(int i = 0; i <10; i++)
            {
              analogWrite(REDPIN, 150); 
              analogWrite(GREENPIN, 0);
              analogWrite(BLUEPIN, 0);
              delay(100);
              analogWrite(REDPIN, 0);
              analogWrite(GREENPIN, 150);
              analogWrite(BLUEPIN, 0);
              delay(100);
              analogWrite(REDPIN, 0);
              analogWrite(GREENPIN, 0);
              analogWrite(BLUEPIN, 150);
              delay(100);
              
            }
           
      
          } // end while
          else if(readString.indexOf("Run_OFF")>0) // Turns off all LEDS
          {
            analogWrite(REDPIN,0);
            analogWrite(GREENPIN,0);
            analogWrite(BLUEPIN,0);
            }
            //clearing string for next read
            readString="";  
          
         }
       }
    }
}
}
