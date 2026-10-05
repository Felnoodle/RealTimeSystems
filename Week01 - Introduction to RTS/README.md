# RealTimeSystems Week 1

# Task A: Change the colour 
# Modify the sketch so the LED blinks green. Then change it to blue and white. 
Green:
# neopixelWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0); 

Blue:
# neopixelWrite(RGB_BUILTIN, 0, 0, RGB_BRIGHTNESS); 

White:
# neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS, RGB_BRIGHTNESS, RGB_BRIGHTNESS); 

# Task B: Change the blink rate 
# Change both delay values from 1000 ms to 250 ms. Compare the new behaviour with the original program. 
Faster blinking.


# Task C: Create an RGB cycle 
# Create a repeating sequence: Red > Green > Blue > Off. Use a 500 ms delay between each state. 
50, 0, 0 -> 0, 50, 0 -> 0, 0, 50

# Task D: Create your own pattern 
# Create a personal LED pattern using at least three different colours. You may also use different brightness values and delays. 
Cycle rainbow colors then flash white 3 times