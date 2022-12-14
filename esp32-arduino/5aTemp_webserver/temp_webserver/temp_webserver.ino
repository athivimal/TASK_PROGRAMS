#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "BRH_2.4GHZ";
const char* password = "BeWiFi@here";
int Temperature = 38;
// Set web server port number to 80
WiFiServer server(80);
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
void setup() {
  Serial.begin(115200);
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
  WiFiClient client = server.available();
  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    client.println("<!DOCTYPE html> <html>\n");
    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n");
    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n");
    client.println("<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n");
    client.println("<title>KARTHI Weather Report</title>\n");
    client.println("<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #333333;}\n");
    client.println("body{margin-top: 50px;}");
    client.println("h1 {margin: 50px auto 30px;}\n");
    client.println(".side-by-side{display: inline-block;vertical-align: middle;position: relative;}\n");
    client.println(".temperature-icon{background-color: #f39c12;width: 30px;height: 30px;border-radius: 50%;line-height: 40px;}\n");
    client.println(".temperature-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n");
    client.println(".temperature{font-weight: 300;font-size: 60px;color: #f39c12;}\n");
    client.println(".superscript{font-size: 17px;font-weight: 600;position: absolute;right: -20px;top: 15px;}\n");
    client.println(".data{padding: 10px;}\n");
    client.println("</style>\n");
    client.println("</head>\n");
    client.println("<body>\n");
    client.println("<div id=\"webpage\">\n");
    client.println("<h1> KARTHI  Weather Report</h1>\n");
    client.println("<div class=\"data\">\n");
    client.println("<div class=\"side-by-side temperature-icon\">\n");
    client.println("<svg version=\"1.1\" id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n");
    client.println("<width=\"9.915px\" height=\"22px\" viewBox=\"0 0 9.915 22\" enable-background=\"new 0 0 9.915 22\" xml:space=\"preserve\">\n");
    client.println("<path fill=\"#FFFFFF\" d=\"M3.498,0.53c0.377-0.331,0.877-0.501,1.374-0.527C5.697-0.04,6.522,0.421,6.924,1.142\n");
    client.println("c0.237,0.399,0.315,0.871,0.311,1.33C7.229,5.856,7.245,9.24,7.227,12.625c1.019,0.539,1.855,1.424,2.301,2.491\n");
    client.println("c0.491,1.163,0.518,2.514,0.062,3.693c-0.414,1.102-1.24,2.038-2.276,2.594c-1.056,0.583-2.331,0.743-3.501,0.463\n");
    client.println("c-1.417-0.323-2.659-1.314-3.3-2.617C0.014,18.26-0.115,17.104,0.1,16.022c0.296-1.443,1.274-2.717,2.58-3.394\n");
    client.println("c0.013-3.44,0-6.881,0.007-10.322C2.674,1.634,2.974,0.955,3.498,0.53z\"/>\n");
    client.println("</svg>\n");
    client.println("</div>\n");
    client.println("<div class=\"side-by-side temperature-text\">Temperature</div>\n");
    client.println("<div class=\"side-by-side temperature\">");
    client.println(Temperature);
    client.println("<span class=\"superscript\">??C</span></div>\n");
    client.println("</div>\n");
    client.println("</body>\n");
    client.println("</html>\n");
  }
}


    
