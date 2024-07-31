**Explanation:**
WiFi Library: Manages Wi-Fi connectivity.
ssid and password: Replace with your network's SSID and password.
server(80): Starts a server on port 80.
setup():
Initializes serial communication and the LED pin.
Connects to Wi-Fi and prints the IP address.
Starts the server.
loop():
Listens for incoming client connections.
Reads client requests and checks for specific URLs (/LED_ON and /LED_OFF).
Controls the LED based on the request and serves a simple HTML page with buttons to control the LED.
4. Usage:
Upload the code to your ESP32.
Open the Serial Monitor to find the IP address of the ESP32.
In a web browser, navigate to the IP address (e.g., http://<ESP32_IP>/).
Use the buttons on the webpage to turn the LED on or off.
This setup provides a basic web interface for controlling an LED via Wi-Fi. You can extend this code to include additional controls and features as needed.
