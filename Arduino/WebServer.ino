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

int light = 8;
int ar_cond = 9;

int ativa_luz = 0;
int ativa_ar = 0;

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
  
  pinMode(8, OUTPUT);
  pinMode(light_sensor, INPUT);
  pinMode(ar_cond, OUTPUT);
  
  digitalWrite(8, LOW);
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
         if (pega_msg.endsWith("?luz=1")){ ativa_luz = 1; }
         else if (pega_msg.endsWith("?luz=0")){ ativa_luz = 0; }
         else if (pega_msg.endsWith("?ar=1")){ ativa_ar = 1; }
         else if (pega_msg.endsWith("?ar=0")){ ativa_ar = 0; };
         
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
          
  
   /* ||||||||||||||||||||||||||||||||||||||||||||
              DES/ATIVAÇÃO DE PORTAS
    |||||||||||||||||||||||||||||||||||||||||||| */
 
    
    //acende Luz
    if (ativa_luz == 1){
    
        client.println("<br /> LUZ ACESA <br />");
        digitalWrite(8, HIGH);
    
    }
    
    //apaga Luz
    if (ativa_luz == 0){
    
        client.println("<br /> ALUZ APAGADA <br />");
        digitalWrite(8, LOW);
    
    }
    
    
    
    //ativa AR CONDICIONADO
    if (ativa_ar == 1){
    
        digitalWrite(ar_cond, HIGH);
    
    }
    
    //desativa AR CONDICIONADO
    if (ativa_ar == 0){
    
        digitalWrite(ar_cond, LOW);
    
    }
 
          
          
          /*
             0 - 1023 => 0 - 5v
             à cada 1 = 204,6
             leitura do sensor => 1°C = 10mV
             
             temperatura = (medicao porta/204,6)/100  
          */
          
          float temperatura = (analogRead(term_meter))/2.046;
          
          client.println("Temperatura: ");
          client.println(temperatura);
          client.println("<br />");
          client.println(pega_msg);
          client.println("<br />");
          client.println(ativa_luz);
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
// Recurso para ler uma subpagina =)
//
//	else if (HTTP_req.indexOf("GET /page2.htm") > -1) {
//		client.println("HTTP/1.1 200 OK");
//		client.println("Content-Type: text/html");
//		client.println("Connnection: close");
//		client.println();
//		webFile = SD.open("page2.htm");        // open web page file
//	}

