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

String pega_msg;
int light_sensor = 7;
int term_meter = 1;

int light = 20;
int ar_cond = 21;

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
  
  pinMode(light, OUTPUT);
  pinMode(light_sensor, INPUT);
  pinMode(ar_cond, OUTPUT);
  
  analogRead(term_meter);
  
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
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        pega_msg.concat(c);
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connnection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
                    // add a meta refresh tag, so the browser pulls again every 5 seconds:
          client.println("<meta http-equiv=\"refresh\" content=\"5\">");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");       
          }
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
 
 
 
 /* ||||||||||||||||||||||||||||||||||||||||||||
              DES/ATIVAÇÃO DE PORTAS
    |||||||||||||||||||||||||||||||||||||||||||| */
 
    
    //acende Luz
    if ((pega_msg.endsWith("?luz=1")) || (!light_sensor)){
    
        digitalWrite(light, HIGH);
    
    }
    
    //apaga Luz
    if ((pega_msg.endsWith("?luz=0")) || (light_sensor)){
    
        digitalWrite(light, LOW);
    
    }
    
    
    
    //ativa AR CONDICIONADO
    if (pega_msg.endsWith("?ar=1")){
    
        digitalWrite(ar_cond, HIGH);
    
    }
    
    //desativa AR CONDICIONADO
    if (pega_msg.endsWith("?ar=0")){
    
        digitalWrite(ar_cond, LOW);
    
    }
    
    
  }
}

// Recurso para ler uma subpagina =)
//
//	else if (HTTP_req.indexOf("GET /page2.htm") > -1) {
//		client.println("HTTP/1.1 200 OK");
//		client.println("Content-Type: text/html");
//		client.println("Connnection: close");
//		client.println();
//		webFile = SD.open("page2.htm");        // open web page file
//	}

