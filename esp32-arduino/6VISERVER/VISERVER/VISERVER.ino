

#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "BRH_2.4GHZ";
const char* password = "BeWiFi@here";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Enter name of the devices
String Device_1 = "Fan";
String Device_2 = "Light";
String Device_3 = "Light2";

// Auxiliar variables to store the current output state
String output1State = "off";
String output2State = "off";
String output3State = "off";
String output4State = "off";
String output5State = "off";
String output6State = "off";

// Assign output variables to GPIO pins
const int output1 = 16;
const int output2 = 5;
const int output3 = 4;
const int output4 = 0;
const int output5 = 2;
const int output6 = 14;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output3, OUTPUT);
  
  // Set outputs to LOW
  digitalWrite(output1, LOW);
  digitalWrite(output2, LOW);
  digitalWrite(output3, LOW);
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /16/on") >= 0) {
              Serial.println(Device_1 + " on");
              output1State = "on";
              digitalWrite(output1, HIGH);
            } else if (header.indexOf("GET /16/off") >= 0) {
              Serial.println(Device_1 + " off");
              output1State = "off";
              digitalWrite(output1, LOW);
            } 
              else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println(Device_2 + " on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println(Device_2 + " off");
              output2State = "off";
              digitalWrite(output2, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println(Device_3 + " on");
              output3State = "on";
              digitalWrite(output3, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println(Device_3 + " off");
              output3State = "off";
              digitalWrite(output3, LOW);
            } 
          
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>KTEC SMART AUTOMATION </h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println("<p>" + Device_1 + ' ' + output1State + "</p>");
            // If the output5State is off, it displays the ON button       
            if (output1State=="off") {
              client.println("<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p>" + Device_2 + ' ' + output2State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output2State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<p>" + Device_3 + ' ' + output3State + "</p>");
            if (output3State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }               
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
