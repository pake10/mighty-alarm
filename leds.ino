void led_control(bool reset) {
  randomSeed(analogRead(A5)); // Seeding the random generator from an unused pin.
  int led_state = 0;
  
  for(int i = 0; i <= 5; i++) {
    if (reset) {
      digitalWrite(leds[i], LOW); // If a reset was requested, turn off all the LEDs.
    } else {
      led_state = random(0, 2); // Initialize a random binary value (0 or 1) for each LED.
    
      switch(led_state) {
        case 0: {
          digitalWrite(leds[i], LOW);
          break;
        }
        
        case 1: {
          digitalWrite(leds[i], HIGH);
          break;
        }
      }
    }
  }
  
  delay(random(50, 300)); // A random delay to boot; some added excitement!
}
  
   
  
  
