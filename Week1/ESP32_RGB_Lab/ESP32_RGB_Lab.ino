#define RGB_BUILTIN 38 
#define RGB_BRIGHTNESS 50
 
void setup() { 
  // No separate initialisation is required for this example. 
} 
 
void loop() { 
  
  // LED OFF 
  neopixelWrite(RGB_BUILTIN, 0, 0, 0); 
  delay(250);

  // Red
  neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS, 0, 0); 
  delay(250); 

  // Orange
  neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS,RGB_BRIGHTNESS/2, 0); 
  delay(250); 

  // Yellow
  neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS, RGB_BRIGHTNESS, 0); 
  delay(250); 

  // Light Green
  neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS/2, RGB_BRIGHTNESS, 0); 
  delay(250); 

  // Green
  neopixelWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0); 
  delay(250); 

  // Dark Green
  neopixelWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, RGB_BRIGHTNESS/2); 
  delay(250); 

  // Cyan
  neopixelWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, RGB_BRIGHTNESS); 
  delay(250); 

  // Light Blue
  neopixelWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS/2, RGB_BRIGHTNESS); 
  delay(250); 

  // Blue
  neopixelWrite(RGB_BUILTIN, 0, 0, RGB_BRIGHTNESS); 
  delay(250); 

  // Purple
  neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS/2, 0, RGB_BRIGHTNESS); 
  delay(250);

  ledBlink();
  ledBlink();
  ledBlink();
} 

void ledBlink(){
  // DARK 
  neopixelWrite(RGB_BUILTIN, 0, 0, 0); 
  delay(500);

  // WHITE
  neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS, RGB_BRIGHTNESS, RGB_BRIGHTNESS); 
  delay(500);
}