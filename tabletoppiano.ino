#include <Wire.h> //Needed for I2C to Qwiic MP3 Trigger
// This #include statement was automatically added by the Particle IDE.
#include "SparkFun_Qwiic_MP3_Trigger_Arduino_Library.h"

// This #include statement was automatically added by the Particle IDE.
#include <SparkFunMicroOLED.h>

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_VL53L0X.h>

MP3TRIGGER mp3;

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
MicroOLED oled;



// boolean isPlaying(void)
// {
//   if (digitalRead(playing) == HIGH) return (true); //Song is playing
//   return (false);

//   //if(getPlayStatus() == 0x01) return (true);
//   //return (false);
// }

void setup() {
    oled.begin();       // Initialize the OLED
    oled.clear(ALL);    // Clear the display's internal memory
    oled.display();     // Display what's in the buffer (splashscreen)
    delay(500);         // Delay 500 ms
    oled.clear(PAGE);   // Clear the buffer.
    
    
    
    Wire.begin();

      //Check to see if Qwiic MP3 is present on the bus
    mp3.begin();
    
    mp3.setVolume(20); //Volume can be 0 (off) to 31 (max)
    
    mp3.playTrack(1);
        mp3.playTrack(2);
            mp3.playTrack(3);
                mp3.playTrack(4);
                    mp3.playTrack(5);
    
    
    
    // mp3.playTrack(1); //Begin playing the first track on the SD card

    
    oled.println("Adafruit VL53L0X test");
    if (!lox.begin()) {
        //Serial.println(F("Failed to boot VL53L0X"));
        while(1);
        }
  // power 
  oled.println(F("VL53L0X API Simple Ranging example\n\n"));
}

int counter = 0;

void loop() {
    int measureTotal;
    int measureAverage;
    
    
    VL53L0X_RangingMeasurementData_t measure; // distance sensor measure
    //  VL53L0X_RangingMeasurementData_t measure2; // distance sensor measure
    //   VL53L0X_RangingMeasurementData_t measure3; // distance sensor measure
    //   VL53L0X_RangingMeasurementData_t measure4; // distance sensor measure
    //     VL53L0X_RangingMeasurementData_t measure5; // distance sensor measure
        
    // measureTotal = (measure.RangeMilliMeter + measure2.RangeMilliMeter + measure3.RangeMilliMeter + measure4.RangeMilliMeter + measure5.RangeMilliMeter);
    // measureAverage = (measureTotal / 5);
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
    oled.clear(PAGE);       // Clear the buffer.
    oled.setCursor(0, 0);   // Set cursor to top-left
    // oled.print("Reading a measurement... ");
    // oled.print(counter);
    
    
    
    if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    oled.print("Distance (mm): "); oled.println(measure.RangeMilliMeter);
   
    // if (measure.RangeStatus != 4 && measure2.RangeStatus != 4 && measure3.RangeStatus != 4 && measure4.RangeStatus != 4 && measure5.RangeStatus != 4) {  // phase failures have incorrect data
    // oled.print("Distance (mm): "); oled.println(measureAverage);
    
    } else {
    oled.println(" out of range ");
    }
    
    
    
    if (mp3.isPlaying() != true) {
        if (measure.RangeMilliMeter > 235 && measure.RangeMilliMeter < 315 ) {
            mp3.playFile(1);
         }
        if (measure.RangeMilliMeter > 316 && measure.RangeMilliMeter < 400 ) {
            mp3.playFile(2);
         } 
        if (measure.RangeMilliMeter > 401 && measure.RangeMilliMeter < 490 ) {
            mp3.playFile(3);
         }
        if (measure.RangeMilliMeter > 491 && measure.RangeMilliMeter < 570 ) {
            mp3.playFile(4);
         }
        if (measure.RangeMilliMeter > 571 && measure.RangeMilliMeter < 660 ) {
            mp3.playFile(5);
         }
        if (measure.RangeMilliMeter > 690 && measure.RangeMilliMeter < 750 ) {
            mp3.playFile(6);
         }
    
    }
        
        
   
    // if (measure.RangeMilliMeter > 125 && measure.RangeMilliMeter < 205 ) {
    //      mp3.playTrack(1);
    // } 
    // if (measure.RangeMilliMeter > 205 && measure.RangeMilliMeter < 280) {
    //     mp3.playTrack(3);
    // }
    if (mp3.isPlaying() == true) {
          oled.print("Now playing: ");
        }
        else {
          oled.print("Last played: ");
    }
    String songName = mp3.getSongName();
    oled.println(songName);
    
    oled.print(mp3.getSongCount());
    
    // counter += 1;
    oled.display();
    delay(50);
}
