#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SwitecX25.h>

static const uint32_t GPSBaud = 9600;
SwitecX25 motor1(219*3,5,6,7,8);
TinyGPSPlus gps;
SoftwareSerial ss(0, 1);

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
  motor1.currentStep = 50;
  motor1.setPosition(0);
  delay(5);
  while (motor1.currentStep > 0) {
    if (motor1.currentStep < 10){
      delay(50);
      motor1.update();
    }
    else{
      motor1.update();
    }
    }
  for (int i = 0; i<657; i++){
    motor1.setPosition(i);
    motor1.updateBlocking();
  };
  for (int i = 657; i>0; i--){
    motor1.setPosition(i);
    motor1.updateBlocking();
  };

  
}

void loop() {
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      if (gps.speed.kmph() > 3){
        motor1.setPosition(int(gps.speed.kmph())*4.7);
        motor1.updateBlocking();
      }
    }
  }
}

