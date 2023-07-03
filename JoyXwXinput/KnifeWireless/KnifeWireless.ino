#include <Wire.h> 

//Accelerometer adress
int ADXL1 = 0x53;

//Pin variables
const int PIN_BUTTON_B = 0;
const int PIN_BUTTON_RB = 0;

//X output from accelerometer
float X_out;

bool readyToChop = true;

const float PRESSURE_FOR_A_BUTTON = 5;

void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Wire.begin(); // Initiate the Wire library

  //Setup pins
  pinMode(A5, OUTPUT); //Pressure A button
  pinMode(PIN_BUTTON_B, INPUT_PULLUP);
  pinMode(PIN_BUTTON_RB, INPUT_PULLUP);
  SetupAccelerometer();
}
void SetupAccelerometer()
{
  //Setup accelerometers
  Wire.beginTransmission(ADXL1); // Start communicating with the device 
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
  Wire.endTransmission();
}

void loop() 
{
  ReadAccelerometer();
  CheckForChop();
  CheckForButtons();
}
void ReadAccelerometer()
{
     // === Read plate acceleromter data === //
  Wire.beginTransmission(ADXL1);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL1, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  X_out = ( Wire.read()| Wire.read() << 8); // X-axis value
  X_out = X_out/256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
}
void CheckForChop()
{
  if((X_out >= 0) && readyToChop == true)
  {
    readyToChop = false;
    Serial1.println("X has been pressed");
    delay(100);
    return;
  }
  if(X_out < 0 && readyToChop == false)
  {
    readyToChop = true;
  }
}
void CheckForButtons()
{
  //Button A
  if(analogRead(A1) > PRESSURE_FOR_A_BUTTON)
  {
      Serial1.println("A Button pressed");
  }
  /*
  //Button B
  if(digitalRead(PIN_BUTTON_B) == LOW)
  {
    Serial1.println("B Button Pressed");
  }
  //Button RB
  if(digitalRead(PIN_BUTTON_RB) == LOW)
  {
    Serial1.print("RB Button Pressed");
  }
  */
}