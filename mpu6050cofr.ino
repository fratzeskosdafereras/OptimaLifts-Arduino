//Libraries installation required
#include "Wire.h"
#include "SPI.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int8_t threshold, count; 
float temp;
bool zero_detect; 
bool TurnOnZI = false;

bool XnegMD, XposMD, YnegMD, YposMD, ZnegMD, ZposMD;

const int ledPin = 13;

void setup() {
    
    Wire.begin();

    Serial.begin(38400);

    accelgyro.initialize();
	
    accelgyro.setAccelerometerPowerOnDelay(3);
	
    accelgyro.setIntZeroMotionEnabled(TurnOnZI);
	
    accelgyro.setDHPFMode(1);

    accelgyro.setMotionDetectionThreshold(2);

    accelgyro.setZeroMotionDetectionThreshold(2);

    accelgyro.setMotionDetectionDuration(40);

    accelgyro.setZeroMotionDetectionDuration(1);	
	

    // configure Arduino LED for
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW); // Turn off the LED
    
}
int sum = 0;


bool incrementFlag = false;

void loop() {
    
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    XnegMD = accelgyro.getXNegMotionDetected();
    XposMD = accelgyro.getXPosMotionDetected();
    YnegMD = accelgyro.getYNegMotionDetected();
    YposMD = accelgyro.getYPosMotionDetected();
    ZnegMD = accelgyro.getZNegMotionDetected();
    ZposMD = accelgyro.getZPosMotionDetected();
	
    zero_detect = accelgyro.getIntMotionStatus();
    threshold = accelgyro.getZeroMotionDetectionThreshold();
    
    temp=(accelgyro.getTemperature()/340.)+36.53;

  if (ay / 16384. < -0.50) {
    if (!incrementFlag) {
      sum = sum + 1;
      incrementFlag = true; 
      Serial.print(sum);
      Serial.print("\n");
      digitalWrite(ledPin, HIGH); 
      delay(500); 
      digitalWrite(ledPin, LOW); 
      delay(500); 
    }
  } else {
    incrementFlag = false; 
  }

    delay(80);
	
}