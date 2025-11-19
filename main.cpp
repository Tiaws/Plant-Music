#include <Arduino.h>
#include <BLEMidi.h>

int RGBLED_RedPin = 5;
int RGBLED_GreenPin = 18;
int RGBLED_BluePin = 19;

// const int MIN = 15;
// const int MAX = 30;

void setup() {
Serial.begin(115200);
delay(1000); // give me time to bring up serial monitor
Serial.println("ESP32 Touch Test");
pinMode(RGBLED_RedPin, OUTPUT);
pinMode(RGBLED_GreenPin, OUTPUT);
pinMode(RGBLED_BluePin, OUTPUT);

BLEMidiServer.begin("Basic MIDI device");
}

void setColor(int redValue, int greenValue, int blueValue) {
analogWrite(RGBLED_RedPin, redValue);
analogWrite(RGBLED_GreenPin, greenValue);
analogWrite(RGBLED_BluePin, blueValue);
}
void loop() {
int padValue = touchRead(4) * 3;
Serial.println(padValue); // get value of Touch 0 pin = GPIO 4

if (padValue<= 19){
digitalWrite(RGBLED_RedPin,1);
digitalWrite(RGBLED_GreenPin,0);
digitalWrite(RGBLED_BluePin,0);
}

//
else if (padValue >= 20 && padValue <= 28){
digitalWrite(RGBLED_RedPin,0);
digitalWrite(RGBLED_GreenPin,1);
digitalWrite(RGBLED_BluePin,0);
}
else{
digitalWrite(RGBLED_BluePin,1);
digitalWrite(RGBLED_RedPin,0);
digitalWrite(RGBLED_GreenPin,0);
}

if(BLEMidiServer.isConnected()) { // If we've got a connection, we send an A4 during one second, at full velocity (127)
BLEMidiServer.noteOn(0, padValue * 3, 127);
delay(100);
BLEMidiServer.noteOff(0, padValue * 3, 127); // Then we make a delay of one second before returning to the beginning of the loop
delay(100);
}
