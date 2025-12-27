/*************  BLYNK CONFIG — MUST BE FIRST  *************/
#define BLYNK_TEMPLATE_ID "TMPL39ZO1jTn2"
#define BLYNK_TEMPLATE_NAME "Health Monitoring System"
#define BLYNK_AUTH_TOKEN "ulg02PQc5fclJopKH6yBmb_5AqTa2ZNJ"

#define BLYNK_PRINT Serial

/*************  LIBRARIES  *************/
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "MAX30105.h"
#include "spo2_algorithm.h"

#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"

/*************  SENSOR CONFIG  *************/
#define DHTPIN 18
#define DHTTYPE DHT11
#define DS18B20_PIN 5
#define REPORTING_PERIOD_MS 1000

DHT dht(DHTPIN, DHTTYPE);
OneWire oneWire(DS18B20_PIN);
DallasTemperature ds18b20(&oneWire);

MAX30105 sensor;

/*************  VARIABLES  *************/
float Temperature, Humidity, bodytemperature;
float BPM = 0, SpO2 = 0;

uint32_t irBuffer[100];
uint32_t redBuffer[100];
int32_t spo2;
int8_t validSPO2;
int32_t heartRate;
int8_t validHeartRate;

uint32_t tsLastReport = 0;

/*************  WIFI CREDENTIALS  *************/
char ssid[] = "Piyush's A35";
char pass[] = "Anonymous@08";

/*************  SETUP  *************/
void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(19, OUTPUT);

  dht.begin();
  ds18b20.begin();

  Serial.println("Connecting to WiFi...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.print("Initializing MAX30102 Sensor... ");
  if (!sensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("Sensor failed, continuing without it.");
  } else {
    Serial.println("SUCCESS");
    sensor.setup();  
    sensor.setPulseAmplitudeRed(0x0A);
    sensor.setPulseAmplitudeIR(0x0A);
  }
}

/*************  LOOP  *************/
void loop() {
  Blynk.run();

  /*************  READ DHT11  *************/
  Temperature = dht.readTemperature();
  Humidity = dht.readHumidity();

  /*************  READ DS18B20  *************/
  ds18b20.requestTemperatures();
  bodytemperature = ds18b20.getTempCByIndex(0);

  /*************  READ MAX30102 (100 samples)  *************/
  if (sensor.available()) {
    for (int i = 0; i < 100; i++) {
      while (!sensor.available()) sensor.check();

      redBuffer[i] = sensor.getRed();
      irBuffer[i] = sensor.getIR();

      sensor.nextSample();
    }

    maxim_heart_rate_and_oxygen_saturation(
      irBuffer, 100, redBuffer,
      &spo2, &validSPO2,
      &heartRate, &validHeartRate
    );

    BPM = heartRate;
    SpO2 = spo2;
  }

  /*************  PRINT + SEND TO BLYNK  *************/
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {

    Serial.print("Heart Rate: ");
    Serial.print(BPM);
    Serial.print(" bpm | SpO2: ");
    Serial.print(SpO2);
    Serial.println(" %");

    Serial.print("Room Temperature: ");
    Serial.print(Temperature);
    Serial.println(" °C");

    Serial.print("Room Humidity: ");
    Serial.print(Humidity);
    Serial.println(" %");

    Serial.print("Body Temperature: ");
    Serial.print(bodytemperature);
    Serial.println(" °C");

    Blynk.virtualWrite(V3, Temperature);
    Blynk.virtualWrite(V4, Humidity);
    Blynk.virtualWrite(V5, BPM);
    Blynk.virtualWrite(V6, SpO2);
    Blynk.virtualWrite(V7, bodytemperature);

    tsLastReport = millis();
  }
}
