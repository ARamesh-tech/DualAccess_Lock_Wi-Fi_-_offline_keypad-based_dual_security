#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "OpenWifi"; // Replace with your WiFi SSID
const char* password = "hackers12345"; // Replace with your WiFi Password

WebServer server(80);

void handleRoot() {
    String html = "<!DOCTYPE html>"
                  "<html><head><title>ESP32 Form</title></head><body>"
                  "<h2>Enter Your Password</h2>"
                  "<form action='/submit' method='POST'>"
                  "<input type='text' id='input' name='input' onkeypress='sendKey(event)'>"
                  "<input type='submit' value='Submit'>"
                  "</form>"
                  "<script>"
                  "function sendKey(event) {"
                  "    fetch('/keypress?key=' + event.key);"
                  "}"
                  "</script>"
                  "</body></html>";
    server.send(200, "text/html", html);
}

void handleFormSubmit() {
    if (server.hasArg("input")) {
        String userInput = server.arg("input");
        Serial.println("Received Input: " + userInput);
        if (userInput == "1234") {
            Serial.println("Correct password, Door Unlocked!");
            server.send(200, "text/html", "<h3>Correct password, Door Unlocked!</h3><br><a href='/'>Go Back</a>");
        } else {
            server.send(200, "text/html", "<h3>Incorrect Password, Try again!</h3><br><a href='/'>Go Back</a>");
        }
        // server.send(200, "text/html", "<h3>Received: " + userInput + "</h3><br><a href='/'>Go Back</a>");
    } else {
        server.send(400, "text/plain", "No input received");
    }
}

void handleKeyPress() {
    if (server.hasArg("key")) {
        String key = server.arg("key");
        Serial.println("Key Pressed: " + key);
        Serial2.print(key); // Send key to Arduino via Serial2
        server.send(200, "text/plain", "Key received");
    }
}

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, 16, 17); // Use GPIO 16 (RX2) and GPIO 17 (TX2) for communication

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, handleRoot);
    server.on("/submit", HTTP_POST, handleFormSubmit);
    server.on("/keypress", HTTP_GET, handleKeyPress);
    server.begin();
    Serial.println("Web server started!");
}

void loop() {
    server.handleClient();
}
