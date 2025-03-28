#include <Arduino.h>
#include <WiFi.h>  // include the WiFi library in order to connect to Wifi network
#include <WebServer.h>  // include the WebServer library to be able to handle web requests
#include <ArduinoOTA.h>  // include the OTA library for updates
#include <Stepper.h>  // include the stepper library

// ULN2003 Motor Driver Pins
#define IN1 18
#define IN2 8
#define IN3 10
#define IN4 11
#define POT 4

// Replace with your network credentials
const char* ssid = "CenturyLink6441";       // Replace with your network SSID
const char* password = "af8b8fadadea8a"; // Replace with your network password

const int stepsPerRevolution = 2048;  //number of steps per revolution
uint16_t StepValue = 2*128;
// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

// Create an instance of the web server on port 80
WebServer server(80);

// Function to read ADC value from GPIO4
int readADC() {
    uint32_t adcValue = 0;
    for(int i = 0; i < 75; i++){
      adcValue = adcValue + analogRead(POT);
      //delay(5);
    }
    adcValue = adcValue / 75;
    return adcValue;
}

int readADCVolts()
{
  uint32_t adcVoltsIn = 0;
  for (int i = 0; i < 75; i++)
  {
    adcVoltsIn = adcVoltsIn + analogReadMilliVolts(POT);
    //delay(5);
  }
  adcVoltsIn= adcVoltsIn/75;
  return adcVoltsIn;
}
  

// Function to handle requests to the "/ADC" endpoint
void handle_ADC() {
  int adcValue = readADC(); // Get the ADC value
  int adcVolts= readADCVolts();
  String response = "ADC Value is: " + String(adcValue) + " ADC Volts is: " + String(adcVolts); // Create response string
    server.send(200, "text/plain", response); // Send response
}

// Function to initialize OTA

void initOTA() {
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch"; // firmware update
    } else { // U_SPIFFS
      type = "filesystem"; // filesystem update
    }
    Serial.println("Start updating " + type);
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }

  });
  ArduinoOTA.begin();
}


void StepperAllStop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void setup() {
  Serial.begin(115200); // Start the Serial communication
  delay(1000); // Give time for the Serial monitor to open

  // Connect to Wi-Fi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print the IP address
  Serial.println("");
  Serial.println("Connected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Define the route for the "/ADC" endpoint
  server.on("/ADC", HTTP_GET, handle_ADC); // Use the handle_ADC function

  initOTA(); // Initialize OTA
  // Start the server
  server.begin();
  Serial.println("HTTP server started");

    // set the speed at 5 rpm
    myStepper.setSpeed(8);

    pinMode(POT, INPUT);
    analogReadResolution(12);
    analogSetAttenuation(ADC_2_5db);
    StepperAllStop();
}

void loop() {
  server.handleClient(); // Handle incoming client requests
  ArduinoOTA.handle(); // Handle OTA requests

static uint32_t lastTime = 0;
if(millis() - lastTime > 10000)
{  uint32_t analogValue = readADC();
  while (analogValue < 2500)
  {
    myStepper.step(-StepValue);
    analogValue = readADC();
  }

while(analogValue > 1500)
{
  myStepper.step(StepValue);
  analogValue = readADC();
}
StepperAllStop();
lastTime = millis();
}
}