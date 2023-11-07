#include <dmx.h>
#include <Arduino.h>
#include <ESP32Servo.h>

int DMXch = 500;      //DMX Channel for servo control
int servoPin = 37;    //servo pin
Servo myservo;        //init servo object
int readcycle = 0;
int pos = 0;          //initial servo position
int switchState = 1;


void setup() {
  Serial.begin(115200);
  DMX::Initialize(input);
  myservo.attach(servoPin);
}

void switchOff()
{
  Serial.println("Switch OFF");
  for (pos = 70; pos >= 20; pos -= 5) // goes from 60 degrees to 20 degrees
  {
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    delay(15);          // waits 15ms for the servo to reach the position
  }
  {
    for (pos = 20; pos < 70; pos += 5) // goes from 20 degrees to 60 degrees
    {                                  // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}

void switchOn()
{
  Serial.println("Switch ON");
  for (pos = 70; pos < 110; pos += 5) // goes from 60 degrees to 1200 degrees
  {                                   // in steps of 1 degree
    myservo.write(pos);               // tell servo to go to position in variable 'pos'
    delay(15);                        // waits 15ms for the servo to reach the position
  }
  for (pos = 110; pos >= 70; pos -= 5) // goes from 100 degrees to 60 degrees
  {
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    delay(15);          // waits 15ms for the servo to reach the position
  }
}

void loop()
{
    if(millis() - readcycle > 1000)
  {
    readcycle = millis();

    Serial.print(readcycle);
      
    if(DMX::IsHealthy())
    {
      Serial.print(": ok - ");
    }
    else
    {
      Serial.print(": fail - ");
    }
    Serial.println(DMX::Read(500));
  }  

  while(switchState == 1 && DMX::Read(DMXch) < 120 && DMX::Read(DMXch) >= 1 )
  {
    switchOff();
    switchState = 0; //set state var to 0
    Serial.println(switchState);
  }
  while(switchState == 0 && DMX::Read(DMXch)>= 121)
  {
    switchOn();
    switchState = 1; //set state var to 1 
    Serial.println(switchState);
  }
}