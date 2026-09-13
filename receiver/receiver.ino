#include <RH_ASK.h>
#include <SPI.h>
 
RH_ASK radio;

void setup()
{
    Serial.begin(9600);
 
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT); // ENA

    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(5, OUTPUT); // ENB
    
    if (!radio.init())
    {
         Serial.println("Radio module failed to initialize");
    }
}
 
void loop()
{
  uint8_t data[2];

  delay(1);  // delay in between reads for stability

  data[0] = 0;
  data[1] = 0;

  radio.recv(data, 2);

  // Left track
  // Check if any data
  if(data[0] != 0)
  {

    if(data[0] > 135)
    {
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);  
      // Serial.println("Left: Forward");
      int power = map(data[0], 135, 255, 0, 255);
      analogWrite(6, power);
    }
    else if(data[0] < 120)
    {
        digitalWrite(8, HIGH);
        digitalWrite(7, LOW);  
        // Serial.println("Left: Reverse");
        int power = map(data[0], 0, 120, 255, 0);
        analogWrite(6, power);
    }
    else
    {
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);  
      // Serial.println("Left: Neutral");
    }
  }

  // Right track
  // Check if any data
  if(data[1] != 0)
  {

    if(data[1] < 120)
    {
      digitalWrite(10, LOW);
      digitalWrite(9, HIGH);  
      // Serial.println("Right: Forward");
      int power = map(data[1], 0, 120, 255, 0);
      analogWrite(5, power);
    }
    else if(data[1] > 135)
    {
        digitalWrite(10, HIGH);
        digitalWrite(9, LOW);  
        // Serial.println("Right: Reverse");
        int power = map(data[1], 135, 255, 0, 255);
        analogWrite(5, power);
    }
    else
    {
      digitalWrite(10, LOW);
      digitalWrite(9, LOW);  
      // Serial.println("Right: Neutral");
    }
  }
}