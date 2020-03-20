void servo_control(bool open) {
  if(open) {
    for(angle = 0; angle =< 90; angle += 1) { // Open the door!
      door.write(angle);
      delay(5);
    }
    
    for(angle = 0; angle =< 90; angle += 1) { // Reveal the figure!
      figure.write(angle);
      delay(5);
    }
    
  } else {
    for(angle = 90; angle >= 0; angle -= 1) { // Hide the figure.
      figure.write(angle);
      delay(5);
    }
    
    for(angle = 90; angle >= 0; angle -= 1) { // Close the door.
      door.write(angle);
      delay(5);
    }
  }
}
