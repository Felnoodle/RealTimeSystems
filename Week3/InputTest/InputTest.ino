#define RGB_BUILTIN 38
#define RGB_BRIGHTNESS 50

volatile uint32_t blinkIntervalMs = 500;

TaskHandle_t ledTaskHandle = NULL;

void taskA(void *parameter) {
  char input[16];
  size_t inputLength = 0;

  Serial.println("Enter blink interval in milliseconds, suspend, or resume:");

  for (;;) {
    while (Serial.available() > 0) {
      char c = Serial.read();

      if (c == '\n' || c == '\r') {
        if (inputLength > 0) {
          input[inputLength] = '\0';

          if (strcmp(input, "suspend") == 0) {
            if (ledTaskHandle != NULL) {
              vTaskSuspend(ledTaskHandle);
              Serial.println("Blinking suspended.");
            }
          } 
          else if (strcmp(input, "resume") == 0) {
            if (ledTaskHandle != NULL) {
              vTaskResume(ledTaskHandle);
              Serial.println("Blinking resumed.");
            }
          } 
          else {
            char *endPointer;
            unsigned long requestedInterval = strtoul(input, &endPointer, 10);

            if (*endPointer == '\0' &&
                requestedInterval >= 10 &&
                requestedInterval <= 60000) {
              blinkIntervalMs = requestedInterval;

              Serial.print("Blink interval changed to ");
              Serial.print(blinkIntervalMs);
              Serial.println(" ms");
            } else {
              Serial.println(
                  "Enter 10-60000 ms, suspend, or resume.");
            }
          }

          inputLength = 0;
          Serial.println(
              "Enter another interval, suspend, or resume:");
        }
      } 
      else if (inputLength < sizeof(input) - 1) {
        input[inputLength++] = c;
      }
    }

    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void taskB(void *parameter) {
  for (;;) {
    neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS, 0, 0);

    uint32_t interval = blinkIntervalMs;
    vTaskDelay(pdMS_TO_TICKS(interval));

    neopixelWrite(RGB_BUILTIN, 0, 0, 0);

    interval = blinkIntervalMs;
    vTaskDelay(pdMS_TO_TICKS(interval));
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  xTaskCreatePinnedToCore(
      taskA,
      "Task A",
      4096,
      NULL,
      2,
      NULL,
      1);

  xTaskCreatePinnedToCore(
      taskB,
      "Task B",
      2048,
      NULL,
      1,
      &ledTaskHandle,
      1);
}

void loop() {
}