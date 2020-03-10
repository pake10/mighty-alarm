enum States{IDLE, OPEN, WAIT, CLOSE}
States state = IDLE;

void loop() {
  knock = digitalRead(knockPin);
  // if current state is IDLE, check the reading of the vibration sensor
  // -> state OPEN (opening the door with the servo and bringing the figure forward)
  // -> state WAIT (check the reading of the proximity(?) sensor and switch to CLOSE if needed)
  // -> state CLOSE (bringing the figure back inside and closing the door)
  // -> state IDLE
  
  switch(state) {
    case IDLE: {
      if(knock == LOW) { // Someone's at the door!
        state = OPEN;
        break;
      }
    }
    
    case OPEN: {
      // calling the servo controller
      // setting the state to WAIT when ready
      break;
    }
      
    case WAIT: {
      // Checking the reading of the proximity(?) sensor: if the user has left, we'll switch to the CLOSE state.
      break;
    }
    
    case CLOSE: {
      // calling the servo controller
      // setting the state to IDLE when ready
    }
  }
      
  // Will we implement the actual alarm functionality?
  // playing the music only in state IDLE?
  // buzzer and tone-function
  // music speed/tone increasing with each iteration?
}
