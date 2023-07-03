#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// CUSTOM CODE

float timeLeft = 0;
float addedTime = 2;
float sensPos = 10;
float sensNeg = -10;

//

void setup(void) 
{

// CUSTOM CODE
  
  timeLeft = 0; // Starting time left
  sensPos = 15;  // Meters per second that activates it. The value is also turned negative when needed
  addedTime = 3; // Time added after each movement event

//


#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
  Serial.begin(9600);
  Serial.println("Accelerometer Test"); Serial.println("");

  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);
 
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  delay(500); // wait 500ms

// CUSTOM CODE

// Invert Limit to negative
sensNeg = 0 - sensPos;

// Set timeLeft to 0 if lower and 0

if (timeLeft < 0 && timeLeft != 0)
{
  timeLeft = 0;
  Serial.print("______________Not Chopping______________"); // If timeLeft is lower than or eual to 0, then we are not chopping
}

// Remove time if timeLeft is still bigger than 0
if (timeLeft > 0 && timeLeft != 0)
{
  timeLeft = timeLeft - 0.5f;  // Remove time, delay above makes this happen every 500ms
  Serial.print("______________CHOPPING Mode______________"); // If timeLeft bigger than 0, then we are chopping
}

Serial.println(timeLeft);


// Movement events

if (event.acceleration.x >= sensPos)
  {
    timeLeft = addedTime;
    Serial.print("______________CHOPPING X+______________");
  }

if (event.acceleration.x <= sensNeg)
  {
    timeLeft = addedTime;
    Serial.print("______________CHOPPING X-______________");
  }

if (event.acceleration.y >= sensPos)
  {
    timeLeft = addedTime;
    Serial.print("______________CHOPPING Y+______________");
  }

if (event.acceleration.y <= sensNeg)
  {
    timeLeft = addedTime;
    Serial.print("______________CHOPPING Y-______________");
  }

if (event.acceleration.z >= sensPos)
  {
    timeLeft = addedTime;
    Serial.print("______________CHOPPING Z+______________");
  }

if (event.acceleration.z <= sensNeg)
  {
    timeLeft = addedTime;
    Serial.print("______________CHOPPING Z-______________");
  }
}
