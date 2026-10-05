# Week 5 Lab Readme

## Purpose

The program reads sensor data from DHT22 in the Sensor Task and sends it via queue to display task, which then prints the values in the serial monitor.

## How it works

Using the DHT Sensor Library by Adafruit, the sensor task reads the DHT22 sensor's data with `dht22.readHumidity()` and `dht22.readTemperature()`.

The values are then read and sent to the queue with
```
if (isnan(humi)) {
    Serial.println("Error: failed to read humidity from DHT22");
  } else if (xQueueSend(humiQueue, &humi, 0) != pdPASS) {
    Serial.println("Queue full: humidity value not sent");
  }
```
This format reads the sensor data, rejects it if the sensor failed to read, then attempts to send it to queue and prints an error if the queue is full. The temperature values use a different queue, but the structure is identical.

The display task receives queued data with `if (xQueueReceive(humiQueue, &value, 0) == pdPASS)` and then the data is written to serial monitor. Similarly, the task receives temperature data from tempQueue.

The humidity and temperature queues can hold 5 float values each.

## Reflection

The queue lets the sensor task send readings to the display task without both tasks needing to run at exactly the same time. FreeRTOS copies each value into the queue, where it can wait until the display task receives it. This safely passes data between tasks and can buffer up to five humidity readings and five temperature readings. If a queue is full, the non-blocking send fails and the program prints an error.