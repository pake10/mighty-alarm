#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>
#include <Servo.h>

TMRpcm music;
const int knock_threshold = 100;
const float distance_threshold = 50.0f;

const int knock_pin = A0;
const int sd_pin = 10;
const int speaker_pin = 9;
const int trig_pin = 8;
const int echo_pin = 7; // For the ultrasonic sensor
const int door_pin = 6;
const int figure_pin = 5;
const int leds[6] = {2, 3, 4, 15, 16, 17}; // Analog pins are used for three LEDs.

Servo door;
Servo figure;

int volume = 3;

enum States{IDLE, OPEN, WAIT, CLOSE, DONT_CARE};
States state = IDLE;

bool check_distance() {
  long duration, cm;
	
  pinMode(trig_pin, OUTPUT);
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig_pin, LOW);

  pinMode(echo_pin, INPUT);
  duration = pulseIn(echo_pin, HIGH);

  cm = duration / 29 / 2;
  
  if (cm > distance_threshold) {
    return true;
  }
  
  return false;
}

void setup()
{
  Serial.begin(9600);
  music.speakerPin = speaker_pin;
  
  if (!SD.begin(sd_pin)) {  // see if the card is present and can be initialized:
    Serial.println("Couldn't initialize the SD card.");  
    return;
  }
  
  door.attach(door_pin);
  figure.attach(figure_pin);
  
  door.write(0);
  figure.write(0);

  for (int i = 0; i <= 5; i++) {
	  pinMode(leds[i], OUTPUT);
  }
	
  music.setVolume(volume);
  music.play("1.wav"); // Start playing the song.
  music.loop(1);
}

void loop() {
  switch(state) {
    case IDLE: {
      led_control(false); // Flash the LEDs.
      door.write(0);
      figure.write(0); // Ensuring the door remains closed and the figure inside when IDLE.
      
      if(analogRead(knock_pin) >= knock_threshold) { // Oooh, someone's at the door!
        state = OPEN;
      }
      
      break;
    }
    
    case OPEN: {
      music.stopPlayback(); // Stops the current track.
      led_control(true); // Reset the LEDs.
	    
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
      
      if (volume == 7) {
	state = DONT_CARE;
      } else {
      	volume += 2; // Increase the volume by 2 each iteration; when the maximum (7) has been reached, stop.
	music.setVolume(volume);
      	music.play("1.wav");
        music.loop(1);
      }
	
	break;
    }
	
    case DONT_CARE: {
    	break; // Do nothing!
    }
  }
}
