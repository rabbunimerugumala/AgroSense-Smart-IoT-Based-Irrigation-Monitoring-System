#define BLYNK_TEMPLATE_ID ""   // Replace with your Blynk Template ID
#define BLYNK_TEMPLATE_NAME "" // Replace with your Blynk Template Name
#define BLYNK_AUTH_TOKEN ""    // Replace with your Blynk Auth Token

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// WiFi Credentials
char ssid[] = ""; // Your WiFi SSID
char pass[] = ""; // Your WiFi Password

// Variables for serial data handling
String inputString = "";
bool stringComplete = false;

// Sensor values to be parsed from Arduino
String soilStatus = "";
float temperature = 0;
float humidity = 0;
String rainStatus = "";
String motionStatus = "";
String pumpStatus = "";
int ldrValue = 0;

// Pump control state (from Blynk app)
bool pumpControl = false;

void setup()
{
    Serial.begin(9600); // ESP Serial to Arduino
    Serial.println("Starting ESP8266...");

    // Connect to WiFi
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);

    WiFi.begin(ssid, pass);
    int wifi_attempts = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        wifi_attempts++;
        if (wifi_attempts > 20)
        { // ~10 seconds timeout
            Serial.println("\nFailed to connect to WiFi. Restarting...");
            ESP.restart();
        }
    }

    Serial.println("\nWiFi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Connect to Blynk
    Serial.println("Connecting to Blynk...");
    Blynk.config(BLYNK_AUTH_TOKEN);
    int blynk_attempts = 0;
    while (!Blynk.connected())
    {
        Blynk.connect();
        delay(500);
        Serial.print(".");
        blynk_attempts++;
        if (blynk_attempts > 20)
        { // ~10 seconds timeout
            Serial.println("\nFailed to connect to Blynk. Restarting...");
            ESP.restart();
        }
    }
    Serial.println("\nBlynk connected!");
}

void loop()
{
    Blynk.run();
    readSerialData();
    delay(100);
}

// Read incoming serial data from Arduino
void readSerialData()
{
    while (Serial.available())
    {
        char inChar = (char)Serial.read();
        inputString += inChar;
        if (inChar == '\n')
        {
            stringComplete = true;
        }
    }

    if (stringComplete)
    {
        inputString.trim();
        Serial.print("Received from Arduino: ");
        Serial.println(inputString); // Debug print
        parseData(inputString);
        inputString = "";
        stringComplete = false;
    }
}

// Parse the incoming data and assign values to the respective variables
void parseData(String data)
{
    String values[7];
    int index = 0;

    while (data.length() > 0 && index < 7)
    {
        int commaIndex = data.indexOf(',');
        if (commaIndex == -1)
        {
            values[index++] = data;
            break;
        }
        else
        {
            values[index++] = data.substring(0, commaIndex);
            data = data.substring(commaIndex + 1);
        }
    }

    if (index < 7)
    {
        Serial.println("Error: Incomplete data received!");
        return;
    }

    soilStatus = values[0];
    temperature = values[1].toFloat();
    humidity = values[2].toFloat();
    rainStatus = values[3];
    motionStatus = values[4];
    pumpStatus = values[5];
    ldrValue = values[6].toInt();

    Serial.println("Parsed values:");
    Serial.println("Soil: " + soilStatus);
    Serial.println("Temp: " + String(temperature));
    Serial.println("Humidity: " + String(humidity));
    Serial.println("Rain: " + rainStatus);
    Serial.println("Motion: " + motionStatus);
    Serial.println("Pump: " + pumpStatus);
    Serial.println("LDR: " + String(ldrValue));

    Blynk.virtualWrite(V0, soilStatus);
    Blynk.virtualWrite(V1, temperature);
    Blynk.virtualWrite(V2, humidity);
    Blynk.virtualWrite(V3, rainStatus);
    Blynk.virtualWrite(V4, motionStatus);
    Blynk.virtualWrite(V5, pumpStatus);
    Blynk.virtualWrite(V6, ldrValue);
}

// Handle pump control from the Blynk app (Virtual Pin V7)
BLYNK_WRITE(V7)
{
    pumpControl = param.asInt();
    Serial.print("Sending pump control to Arduino: ");
    Serial.println(pumpControl);
    Serial.println(pumpControl); // Arduino will read this
}
