#include <Arduino.h>
#include <DHT.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define DHT22_PIN 14 //ESP32 pin GPIO14 connected to DHT22

QueueHandle_t tempQueue;
QueueHandle_t humiQueue;
const int sensorMs = 1000;
const int displayMs = 1000;

TaskHandle_t sensorTaskHandle = NULL;
TaskHandle_t displayTaskHandle = NULL;


DHT dht22(DHT22_PIN, DHT22);

void sensorTask(void *parameter)
{
  int value = 1;
  while (1){
  // read humidity
  float humi  = dht22.readHumidity();
  // read temperature in Celsius
  float temp = dht22.readTemperature();

  if (isnan(humi)) {
    Serial.println("Error: failed to read humidity from DHT22");
  } else if (xQueueSend(humiQueue, &humi, 0) != pdPASS) {
    Serial.println("Queue full: humidity value not sent");
  }
  if (isnan(temp)) {
    Serial.println("Error: failed to read temperature from DHT22");
  } else if (xQueueSend(tempQueue, &temp, 0) != pdPASS) {
    Serial.println("Queue full: temperature value not sent");
  }
  vTaskDelay(pdMS_TO_TICKS(sensorMs));
  }
}

void displayTask(void *parameter){
  float value;
  while(1){
    if (xQueueReceive(humiQueue, &value, 0) == pdPASS){
      Serial.print("Humidity: ");
      Serial.print(value);
      Serial.println("%");
    }
    if (xQueueReceive(tempQueue, &value, 0) == pdPASS){
      Serial.print("Temperature: ");
      Serial.print(value);
      Serial.println("°C");
    }
    vTaskDelay(pdMS_TO_TICKS(displayMs));
  }
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("=== RTOS Sensor Demo ===");
  Serial.println();

  Serial.println("Starting up the DHT22 sensor...");
  dht22.begin();

  Serial.println("Creating Humidity Queue...");
  humiQueue = xQueueCreate(5, sizeof(float));

  if (humiQueue == NULL)
  {
    Serial.println("Humidity Queue creation FAILED.");
  }
  else
  {
    Serial.println("Humidity Queue created.");
  }
  Serial.println();

  Serial.println("Creating Temperature Queue...");
  tempQueue = xQueueCreate(5, sizeof(float));

  if (tempQueue == NULL)
  {
    Serial.println("Temperature Queue creation FAILED.");
  }
  else
  {
    Serial.println("Temperature Queue created.");
  }
  Serial.println();

  Serial.println("Creating Sensor Task...");
  BaseType_t sensorTaskResult = xTaskCreate(
    sensorTask,
    "SensorTask",
    8192,
    NULL,
    1,
    &sensorTaskHandle
  );

  if (sensorTaskResult == pdPASS)
  {
    Serial.println("Sensor Task created.");
  }
  else
  {
    Serial.println("Sensor Task creation FAILED.");
  }
  Serial.println();

  Serial.println("Creating Display Task...");
  BaseType_t displayTaskResult = xTaskCreate(
    displayTask,
    "DisplayTask",
    4096,
    NULL,
    1,
    &displayTaskHandle
  );

  if (displayTaskResult == pdPASS)
  {
    Serial.println("Display Task created.");
  }
  else
  {
    Serial.println("Display Task creation FAILED.");
  }  

}

void loop() {
  // put your main code here, to run repeatedly:

}
