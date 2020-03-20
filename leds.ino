void led_control(bool reset) {
  for(i = 0; i =< 5; i++) {
    if (reset) {
      digitalWrite(leds[i], LOW);
    } else {
      state = random(0, 2);
    
      switch(state) {
        case 0: {
          digitalWrite(leds[i], LOW);
        }
        
        case 1: {
          digitalWrite(leds[i], HIGH);
        }
      }
    }
  }
  
  delay(random(50, 300));
}
  
   
  
  
