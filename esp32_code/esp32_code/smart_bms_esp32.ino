#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_INA219.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

WiFiServer server(80);

Adafruit_INA219 ina219;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float voltage = 0;
float current = 0;
float power = 0;
float temperature = 0;

void setup()
{
    Serial.begin(115200);

    Wire.begin();

    ina219.begin();

    sensors.begin();

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi Connected");
    Serial.println(WiFi.localIP());

    server.begin();
}

void loop()
{
    sensors.requestTemperatures();

    temperature = sensors.getTempCByIndex(0);

    voltage = ina219.getBusVoltage_V();

    current = ina219.getCurrent_mA() / 1000.0;

    power = voltage * current;

    Serial.println("---------------");
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println(" V");

    Serial.print("Current: ");
    Serial.print(current);
    Serial.println(" A");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Power: ");
    Serial.print(power);
    Serial.println(" W");

    if(temperature > 60)
    {
        Serial.println("WARNING: HIGH TEMPERATURE");
    }

    if(voltage < 21.0)
    {
        Serial.println("WARNING: LOW BATTERY VOLTAGE");
    }

    WiFiClient client = server.available();

    if(client)
    {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();

        client.println("<html><body>");
        client.println("<h2>Smart Battery Management System</h2>");

        client.print("<p>Voltage: ");
        client.print(voltage);
        client.println(" V</p>");

        client.print("<p>Current: ");
        client.print(current);
        client.println(" A</p>");

        client.print("<p>Temperature: ");
        client.print(temperature);
        client.println(" C</p>");

        client.print("<p>Power: ");
        client.print(power);
        client.println(" W</p>");

        client.println("</body></html>");

        delay(1);
        client.stop();
    }

    delay(2000);
}
