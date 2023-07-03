#include <Wire.h>  // Wire library - used for I2C communication
#include <XInput.h>
#include <RunningMedian.h>

int ADXL2 = 0x53; // Plate ADXL345 sensor I2C address
int ADXL1 = 0x1D; // Spatula ADXL345 sensor I2C address

float X_out, Y_out, Z_out;  // Outputs
float X2_out, Y2_out, Z2_out;  // Outputs right

float filteredX; // Smoothed outputs
float filteredY;


RunningMedian samplesX = RunningMedian(50);
RunningMedian samplesY = RunningMedian(50);


const int PIN_BUTTON_B = 0;
const int PIN_BUTTON_X = 0;
const int PIN_BUTTON_Y = 0;
const int PIN_BUTTON_RB = 0;
const int PIN_BUTTON_LB = 0;
const int PIN_MOTOR = 10;

bool readyToChop = true;
int isInteracting = 0;

//Timer
unsigned long time = millis();
int toggle = 1;


//Til finjustering
const int DEADZONE = 500;
const float PLATE_THROW_TRIGGER = 0.95;
const float PRESSURE_FOR_BUTTON_A = 8;

//Feedback
const float PLATE_FEEDBACK_VALUE_MIN = .8;
const float PLATE_FEEDBACK_VALUE_MAX = .95;

void setup() 
{
  RunSetup();
}
void loop() 
{
  ReadGyroscope();
  MoveCharacter();
  CheckButtons();
  // delay(10);
}
void RunSetup()
{
  Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
  XInput.begin(); //Initiade XInput emulation
  Wire.begin(); // Initiate the Wire library

  //Setup accelerometers
  Wire.beginTransmission(ADXL1); // Start communicating with the device 
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
  Wire.endTransmission();

  Wire.beginTransmission(ADXL2); // Start communicating with the device 
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
  Wire.endTransmission();

  //Setup pins
  pinMode(A5, OUTPUT);
  pinMode(PIN_MOTOR, OUTPUT); 
  delay(10);
}

void ReadGyroscope()
{
    // === Read plate acceleromter data === //
  Wire.beginTransmission(ADXL1);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL1, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  X_out = ( Wire.read()| Wire.read() << 8); // X-axis value
  X_out = X_out/256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  samplesX.add(X_out);
  Y_out = ( Wire.read()| Wire.read() << 8); // Y-axis value
  Y_out = Y_out/256;
  samplesY.add(Y_out);
  Z_out = ( Wire.read()| Wire.read() << 8); // Z-axis value
  Z_out = Z_out/256;

     // === Read spatula acceleromter data === //
  Wire.beginTransmission(ADXL2);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL2, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  X2_out = ( Wire.read()| Wire.read() << 8); // X-axis value
  X2_out = X2_out/256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet

}

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void MoveCharacter()
{  
  filteredX = samplesX.getMedian();
  filteredY = samplesY.getMedian();
  
  float finalXOutput = floatMap(filteredX, -1, 1, -32768, 32767);

  float finalYOutput = floatMap(filteredY, -1, 1, -32768, 32767);
  

  if((!OutOfDeadZone(finalXOutput) && !OutOfDeadZone(finalYOutput)) || isInteracting)
  {
    finalXOutput = 0;
    finalYOutput = 0;
    RunFeedbackPlate(false, 0, 0);
    XInput.setJoystick(JOY_LEFT, finalXOutput, finalYOutput);
    return;
  }
  if (NormalizedAxis() > PLATE_THROW_TRIGGER)
  {
    XInput.press(BUTTON_A);
    XInput.release(BUTTON_A);
  }

  CheckForFeedback();
  XInput.setJoystick(JOY_LEFT, finalXOutput, finalYOutput);
}

bool OutOfDeadZone(float _input)
{
  if(_input < DEADZONE && _input > -DEADZONE)
  {
    return false;
  }
  else return true;
}

void CheckButtons()
{
  //Button A
  if(analogRead(A5) > PRESSURE_FOR_BUTTON_A)
  {
      Serial.println(analogRead(A5));
      /* if(analogRead(A5) - a5Value > 11) 
      {
        a5Value = analogRead(A5);
        return;
      }
      a5Value = analogRead(A5); 
      */
      XInput.press(BUTTON_A);
  }
  else
  {
    XInput.release(BUTTON_A);
  }
  /*
  //Button B
    if(digitalRead(PIN_BUTTON_B) == HIGH)
  {
    XInput.press(BUTTON_B);
  }
  else
  {
    XInput.release(BUTTON_B);
  }
  */
  //Button X
  if((X2_out >= 0) && readyToChop == true && !XInput.getButton(BUTTON_X))
  {
    isInteracting = 0;
    MoveCharacter();
    XInput.press(BUTTON_X);
    readyToChop = false;
    RunFeedbackPlate(false, 0, 0);
    delay(100);
    XInput.release(BUTTON_X);
  }
  else if(X2_out < 0 && readyToChop == false && !XInput.getButton(BUTTON_X))
  {
    isInteracting = 1;
    readyToChop = true;
  }
  /*
  //Button Y
    if(digitalRead(PIN_BUTTON_Y) == HIGH)
  {
    XInput.press(BUTTON_Y);
  }
  else
  {
    XInput.release(BUTTON_Y);
  }
  //Button RB
    if(digitalRead(PIN_BUTTON_RB) == HIGH)
  {
    XInput.press(BUTTON_RB);
  }
  else
  {
    XInput.release(BUTTON_RB);
  }
  //Button LB
    if(digitalRead(PIN_BUTTON_LB) == HIGH)
  {
    XInput.press(BUTTON_LB);
  }
  else
  {
    XInput.release(BUTTON_LB);
  }
  */
}

float NormalizedAxis() 
{
  return sqrt(filteredX * filteredX + filteredY * filteredY);
}


void CheckForFeedback()
{
  float normalizedAxis = NormalizedAxis();
  if(normalizedAxis < PLATE_FEEDBACK_VALUE_MIN) return;
  if(normalizedAxis >= PLATE_FEEDBACK_VALUE_MIN && normalizedAxis <= PLATE_FEEDBACK_VALUE_MAX)
  {
    RunFeedbackPlate(true, floatMap(normalizedAxis, PLATE_FEEDBACK_VALUE_MIN, PLATE_FEEDBACK_VALUE_MAX, 2000, 0), 50);

  }
  else if(normalizedAxis > PLATE_FEEDBACK_VALUE_MAX) 
  {
    RunFeedbackPlate(true, 0, 100);
  }
}


void RunFeedbackPlate(bool _run, int _motorOn, int _motorOff)
{
  if(!_run)
  {
    digitalWrite(PIN_MOTOR, 0);
    return;
  } 
  //Turn ON vibration
  if(toggle && (millis() - time > _motorOn))
  {
    digitalWrite(PIN_MOTOR, toggle);
    toggle = !toggle;
    time = millis();
  }
  //Turn OFF vibration
  if(!toggle && (millis() - time > _motorOff))
  {
    digitalWrite(PIN_MOTOR, toggle);
    toggle = !toggle;
    time = millis();
  }
}

