#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>

TMRpcm music;
const int knock_threshold = 100;

const int knock_pin = A0;
const int sd_pin = 10;
const int speaker_pin = 9;
const int trig_pin = 8;
const int echo_pin = 7; // For the ultrasonic sensor
int volume = 3;

enum States{IDLE, OPEN, WAIT, CLOSE};
States state = IDLE;

void setup()
{
  Serial.begin(9600);
	music.speakerPin = speaker_pin;
  
  if (!SD.begin(sd_pin)) {  // see if the card is present and can be initialized:
    Serial.println("Couldn't initialize the SD card.");  
    return;
  }
  
  door.attach(2);
  figure.attach(4);
  pinMode(7, INPUT);
  pinMode(11, OUTPUT);
  pinMode(3, OUTPUT);
  
  music.setVolume(volume);
  music.play("1.wav"); // Start playing the first song.
  music.loop(1);
}

void loop() {
  knock = digitalRead(knockPin);
  // if current state is IDLE, check the reading of the vibration sensor
  // -> state OPEN (opening the door with the servo and bringing the figure forward)
  // -> state WAIT (check the reading of the proximity(?) sensor and switch to CLOSE if needed)
  // -> state CLOSE (bringing the figure back inside and closing the door)
  // -> state IDLE
  
  switch(state) {
    case IDLE: {
      door.write(0); // Ensuring the door remains closed when IDLE.
      
      if(analogRead(knockSensor) >= knock_threshold) { // Oooh, someone's at the door!
        state = OPEN;
      }
      
      break;
    }
    
    case OPEN: {
      music.stopPlayback(); // Stops the current track.
      servo_control(true);
      music.play("2.wav");
      music.loop(0);
      
      state = WAIT;
      break;
    }
      
    case WAIT: {
      if (check_distance()) {
        state = CLOSE;
        delay(1000);
      }
      
      break;
    }
    
    case CLOSE: {
      servo_control(false);
      state = IDLE;
      
      volume += 2;
      music.play("1.wav");
      music.loop(1);
      // Increasing volume with each iteration?
    }
  }
}
