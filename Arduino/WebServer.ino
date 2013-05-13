#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,50,2);
String HTTP_req;  // stores the HTTP request

int readPorts[] = { 2,3,4,5,9,13};


// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
	; 
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
  if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                HTTP_req += c;  // save the HTTP request 1 char at a time
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    // remainder of header follows below, depending on if
                    // web page or XML page is requested
                    // Ajax request - send XML file
                    if (HTTP_req.indexOf("ajax_inputs") > -1) {
                        // send rest of HTTP header
                        client.println("Content-Type: text/xml");
                        client.println("Connection: keep-alive");
                        client.println();
                        // send XML file containing input states
                        XML_response(client);
                    }
                    else {  // web page request
                        // send rest of HTTP header
                        client.println("Content-Type: text/html");
                        client.println("Connection: keep-alive");
                        client.println();
                        // send web page
                        client.println("<!DOCTYPE html>");
                        client.println("<html>");
                        client.println("<head>");
                        client.println("<title>Arduino Web Page</title>");
                        client.println("</head>");
                        client.println("<body>");
                        client.println("<h1>Hello from Arduino!</h1>");
                        client.println("<p>A web page from the Arduino server</p>");
                        client.println("</body>");
                        client.println("</html>");
                    }
                    // display received HTTP request on serial port
                    Serial.print(HTTP_req);
                    HTTP_req = "";            // finished with request, empty string
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)
}

// send the XML file with switch statuses and analog value
void XML_response(EthernetClient cl)
{
    int analog_val;
    int i;
    cl.print("<?xml version = \"1.0\" ?>");
    cl.print("<automation>");
    for (i = 0; i < sizeof(readPorts) - 1; i++){
      cl.print("<disp>");
      cl.print("<id>");
      cl.print(readPorts[i]);
      cl.print("</id>");
      cl.print("<status>");
      if (digitalRead(7)) {
          cl.print("1");
      }
      else {
          cl.print("0");
      }
      cl.print("</status>");
      cl.print("</disp>");
    
//      Serial.print(i, DEC);
//      Serial.print(" = ");
//      Serial.write(myStr[i]);
//      Serial.println();
    }
    cl.print("</automation>");
//    // read analog pin A2
//    analog_val = analogRead(2);
//    cl.print("<analog1>");
//    cl.print(analog_val);
//    cl.print("</analog1>");
//    cl.print("</inputs>");
}
