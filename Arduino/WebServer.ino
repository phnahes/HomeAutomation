/*
  Web Server
 
PROGRAMA TESTE
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,0, 177);

int light_sensor = 7;

int term_meter = 1;

int dev1 = 8;
int dev2 = 9;

int dev3_up = 24;
int dev3_down = 25;
int dev3_reverse = 26; 
int dev3_count = 0;

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(9000);

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  
  pinMode(dev1, OUTPUT);
  pinMode(dev2, OUTPUT);

  pinMode(dev3_up, OUTPUT);
  pinMode(dev3_down, OUTPUT);
  pinMode(dev3_reverse, OUTPUT);

  pinMode(light_sensor, INPUT);

  digitalWrite(light, LOW);
  digitalWrite(ar_cond, LOW);
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    String pega_msg;
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        
         pega_msg.concat(c);
        
         char dev[7];
         
        int position = pega_msg.IndexOf("?");

         dev[1] = dev[2]; dev[2] = dev[3]; dev[3] = dev[4]; dev[4] = dev[5]; dev[5] = dev[6]; dev[6] = dev[7]; dev[7] = pega_msg.Substring(position); 


        if (c == '\n' && currentLineIsBlank) {
   
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connnection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

                    
          client.println("<meta http-equiv=\"refresh\" content=\"3\">");


    //PAGINA STATUS     
          if (dev[7] == "S"){

          /*
             0 - 1023 => 0 - 5v
             à cada 1 = 204,6
             leitura do sensor => 1°C = 10mV
             
             temperatura = (medicao porta/204,6)/100  
          */
          
          float temp = (analogRead(term_meter))/2.046;
          
          client.println("TS=");
          client.println(temp);
          client.println(";");

          client.println("Dispositivos:<br />");

          if(digitalWrite(dev1, HIGH) {client.println("DEV1=1;")}
          else{ client.println("DEV1=0;")};

          if(digitalWrite(dev2, HIGH) {client.println("DEV2=1;")}
          else{ client.println("DEV2=0;")};

          if(dev3_count >= 1) {client.println("DEV3=1;VEL="); client.println(dev3_count); client.println(";");}
          else{ client.println("DEV3=0;VEL=0;")};

          if(digitalRead(light_sensor)){client.println("LS=1;")}
          else{ client.println("LS=0;")};

          
        }//FIM PAGINA STATUS


          if(dev[2] == 1){ digitalWrite(dev1, HIGH) };
          if(dev[3] == 1){ digitalWrite(dev2, HIGH) };

          if(dev[2] == 0){ digitalWrite(dev1, LOW) };
          if(dev[3] == 0){ digitalWrite(dev2, LOW) };

          if((dev[4] == 1) && (dev_count <= 2)){
                dev3_count++;
                dev[4] = 0;
                digitalWrite(dev3_up, HIGH);
                delay(1000);
                digitalWrite(dev3_up, LOW);
                }; 

          if((dev[5] == 1) && (dev_count >= 1)){
                dev3_count--;
                dev[5] = 0;
                digitalWrite(dev3_down, HIGH);
                delay(1000);
                digitalWrite(dev3_down, LOW);
                }; 

          if(dev[6] == 1){
                dev3_count = 0;
                dev[6] = 0;
                digitalWrite(dev3_reverse, HIGH);
                delay(1000);
                digitalWrite(dev3_reverse, LOW);
                }; 
        

          client.println("</html>");
          break;


        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
 
 
 

    
    
  }
}

