#include <WiFi.h>

const char* ssid = "francis's Galaxy A14";         // Replace with your network SSID
const char* password = "franco254"; // Replace with your network password

WiFiServer server(80);

const int ledPin = 2; // GPIO pin where the LED is connected
String header;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // HTTP header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Web page content
            client.println("<!DOCTYPE html><html>");
            client.println("<head><title>ESP32 LED Control</title></head>");
            client.println("<body><h1>ESP32 LED Control</h1>");
            client.println("<p><a href=\"/LED_ON\"><button>Turn ON</button></a></p>");
            client.println("<p><a href=\"/LED_OFF\"><button>Turn OFF</button></a></p>");
            client.println("</body></html>");

            // Handle the requested URL
            if (header.indexOf("GET /LED_ON") >= 0) {
              Serial.println("LED ON");
              digitalWrite(ledPin, HIGH);
            } else if (header.indexOf("GET /LED_OFF") >= 0) {
              Serial.println("LED OFF");
              digitalWrite(ledPin, LOW);
            }

            // Break out of the loop
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
