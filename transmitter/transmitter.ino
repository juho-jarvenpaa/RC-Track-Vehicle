#include <RH_ASK.h>   // Include the RH_ASK library
#include <SPI.h>      // Not actually used but needed to compile the RH_ASK library
 
int VRyLeft = 26;
int VRyRight = 27; 
// int SW = 2; // SW to digital pin 2
int yPositionLeft = 0; // Initialize yPosition variable with 0
int yPositionRight = 0; // Initialize yPosition variable with 0
// int SW_state = 0; // Initialize SW_state variable with 0

RH_ASK radio(2000, 11, 12);
 
void setup()
{
    Serial.begin(9600);
 
    pinMode(VRyLeft, INPUT);
    pinMode(VRyRight, INPUT);
    // pinMode(SW, INPUT_PULLUP); // Enable internal pullup resistor on switch pin

    // Speed of 2000 bits per second
    // Use pin 11 for reception
    // Use pin 12 for transmission
    
    if (!radio.init())
    {
         Serial.println("Radio module failed to initialize");
    }
}
 
void loop()
{
    uint8_t leftValue = map(analogRead(VRyLeft), 0, 1023, 1, 255);
    uint8_t rightValue = map(analogRead(VRyRight), 0, 1023, 1, 255);

    uint8_t data[2] = { leftValue, rightValue };

    radio.send(data, 2);

    Serial.println(data[0]);
    Serial.println(data[1]);

    radio.waitPacketSent();
 
    delay(100);
}