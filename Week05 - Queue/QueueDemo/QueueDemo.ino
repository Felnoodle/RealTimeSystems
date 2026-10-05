#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

QueueHandle_t myQueue;
const int producerMs = 1000;
const int consumerMs = 1000;

TaskHandle_t producerTaskHandle = NULL;
TaskHandle_t receiverTaskHandle = NULL;

void producerTask(void *parameter)
{
  int value = 1;
  while (1){
  if (xQueueSend(myQueue, &value, 0) != pdPASS)
    Serial.println("Queue full: value not sent");
    value++;
    vTaskDelay(pdMS_TO_TICKS(producerMs));
  }
}

void receiverTask(void *parameter){
  int value;
  while(1){
    if (xQueueReceive(myQueue, &value, 0) == pdPASS){
      Serial.println(value);
    }
    vTaskDelay(pdMS_TO_TICKS(consumerMs));
  }
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("=== RTOS Queue Demo ===");
  Serial.println();

  Serial.println("Creating Queue...");
  myQueue = xQueueCreate(5, sizeof(int));

  if (myQueue == NULL)
  {
    Serial.println("Queue creation FAILED.");
  }
  else
  {
    Serial.println("Queue created.");
  }
  Serial.println();

  Serial.println("Creating Producer Task...");
  BaseType_t producerTaskResult = xTaskCreate(
    producerTask,
    "ProducerTask",
    8192,
    NULL,
    1,
    &producerTaskHandle
  );

  if (producerTaskResult == pdPASS)
  {
    Serial.println("Producer Task created.");
  }
  else
  {
    Serial.println("Producer Task creation FAILED.");
  }
  Serial.println();

  Serial.println("Creating Receiver Task...");
  BaseType_t receiverTaskResult = xTaskCreate(
    receiverTask,
    "ReceiverTask",
    4096,
    NULL,
    1,
    &receiverTaskHandle
  );

  if (receiverTaskResult == pdPASS)
  {
    Serial.println("Receiver Task created.");
  }
  else
  {
    Serial.println("Receiver Task creation FAILED.");
  }  
}

void loop() {
  // put your main code here, to run repeatedly:

}
