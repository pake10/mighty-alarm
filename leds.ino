void led_control(bool reset) {
  randomSeed(analogRead(A5)); // Seeding the random generator from an unused pin.
  int led_state = 0;
  
  for(i = 0; i =< 5; i++) {
    if (reset) {
      digitalWrite(leds[i], LOW);
    } else {
      led_state = random(0, 2);
    
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
  
  delay(random(50, 300));
}
  
   
  
  
