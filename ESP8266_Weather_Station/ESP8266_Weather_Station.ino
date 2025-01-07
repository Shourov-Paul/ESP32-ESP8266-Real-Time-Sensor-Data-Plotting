#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
#else
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <WebSocketsServer.h>  
  #include <FS.h>
#endif
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_AHTX0.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_BMP280 bmp;
Adafruit_AHTX0 aht;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

//ESP8266
//VDD  --------->  3.3V
//GND  --------->  GND
//SDA  --------->  D2(GPIO-->04)
//SCL  --------->  D1(GPIO-->05)

// Replace with your network credentials
const char* ssid = "Arduino_Cloud";
const char* password = "01798320823";

//new added
// Configure IP addresses of the local access point
IPAddress local_IP(192,168,1,1);
IPAddress gateway(192,168,1,2);
IPAddress subnet(255,255,255,0);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

//new added
WebSocketsServer webSocket = WebSocketsServer(81);    // the websocket uses port 81 (standard port for websockets

String readbmp280Temperature() {
  // Read temperature as Celsius (the default)
  float t = bmp.readTemperature();
  // Convert temperature to Fahrenheit
  //t = 1.8 * t + 32;
  if (isnan(t)) {    
    Serial.println("Failed to read from bmp280 sensor!");
    return "";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String readbmp280Humidity() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  float h = humidity.relative_humidity;
  if (isnan(h)) {
    Serial.println("Failed to read from AHT20 sensor!");
    return "";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}

String readbmp280Pressure() {
  float p = bmp.readPressure() / 100.0F;
  if (isnan(p)) {
    Serial.println("Failed to read from bmp280 sensor!");
    return "";
  }
  else {
    Serial.println(p);
    return String(p);
  }
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin();
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

    if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }

/*      if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
   Serial.println(F("SSD1306 allocation failed"));
   for(;;);
 } */

  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

/*   Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  } */

/*   display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println(ssid);
  display.setCursor(0,30);
  display.println(password);
  display.setCursor(0, 50);
  display.println(WiFi.localIP());
  display.display();  */

  Serial.print("Setting up Access Point ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

  Serial.print("Starting Access Point ... ");
  Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");

  Serial.print("IP address = ");
  Serial.println(WiFi.softAPIP());

  // Print ESP32 Local IP Address
  //Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readbmp280Temperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readbmp280Humidity().c_str());
  });
  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readbmp280Pressure().c_str());
  });
  //new added
  server.serveStatic("/", SPIFFS, "/");
  
  webSocket.begin();                                  // start websocket
  //webSocket.onEvent(webSocketEvent);  

  // Start server
  server.begin();
}
 
void loop(){
  //DO NOTHING HERE
}
