void door_control(bool open) {
  if(open) {
    for(angle = 0; angle < 180; angle += 1) { // Open the door!
      door.write(angle);
      delay(5);
    }
  } else {
    for(angle = 180; angle >= 1; angle -= 1) { // Close the door.
      door.write(angle);
      delay(5);
    }
  }
  
  return true;
}

void figure_control(bool reveal) {
  // Reveal the figure! (servo control?)
}
