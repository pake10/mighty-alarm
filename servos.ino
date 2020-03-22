void servo_control(bool open) {
  if(open) {
    for(int angle = 0; angle <= 90; angle += 1) { // Open the door!
      door.write(angle);
      delay(50);
    }
    
    for(int angle = 0; angle <= 90; angle += 1) { // Reveal the figure!
      figure.write(angle);
      delay(50);
    }
    
  } else {
    for(int angle = 90; angle >= 0; angle -= 1) { // Hide the figure.
      figure.write(angle);
      delay(50);
    }
    
    for(int angle = 90; angle >= 0; angle -= 1) { // Close the door.
      door.write(angle);
      delay(50);
    }
  }
}
