
#include <XInput.h>
// Setup
const boolean UseLeftJoystick   = true;  // set to true to enable left joystick
const boolean InvertLeftYAxis   = false;  // set to true to use inverted left joy X
const boolean UseRightJoystick  = true;  // set to true to enable right joystick
const boolean InvertRightYAxis  = false;  // set to true to use inverted right joy Y
const boolean UseTriggerButtons = false;   // set to false if using analog triggers

int bias = 0;
int trimm_steer = -4;
int trimm_joyry = 0;
static int cutoff_steer = 60;
static int deadzone_steer = 4;
static int cutoff_joyrx = 100;
static int deadzone_joyrx = 3;
static int cutoff_joyry = 100;
static int deadzone_joyry = 3;

void setup() {
  
  XInput.setJoystickRange(0, 1000);  // Set joystick range to the ADC
  XInput.setAutoSend(false);  // Wait for all controls before sending
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(7, INPUT);
  XInput.begin();
}
int scale(double in, int maxvalue) { //Input needs to start from 0
  int out = (in / maxvalue) * 1000;
  return out;
}
void loop() {

  //Steuerung
  int readsteer = analogRead(A0); //782-1023 linear Mitte bei 903
  int out_steer = readsteer;
  if (readsteer > 903 - deadzone_steer && readsteer < 903 + deadzone_steer) out_steer = 903;
  if (readsteer > 903 + cutoff_steer) out_steer = 903 + cutoff_steer;
  if (readsteer < 903 - cutoff_steer) out_steer = 903 - cutoff_steer;
  out_steer = out_steer - 782 - cutoff_steer; //Adjust to 0-241 INVERTED!
  out_steer = scale(out_steer, 241-2*cutoff_steer)+trimm_steer; //Scale to 0-1000 INVERTED!
  out_steer = -(out_steer-1000);
  //Rechter Joystick Y-Achse
  double yachse = analogRead(A2); //140-970
  int out_joyry = yachse;
  if (yachse > 246 - deadzone_joyry && yachse < 246 + deadzone_joyry) out_joyry = 246;
  out_joyry = out_joyry - 140; //Adjust 
  if (out_joyry>246) out_joyry=246;
  out_joyry = scale(out_joyry, 246)+trimm_joyry; //Scale to 0-1000 I
  if (out_joyry>400 && out_joyry <600) out_joyry=500;
  out_joyry = -(out_joyry-1000);
  double xachse = analogRead(A3); //140-970
  boolean switcha = digitalRead(7);
  
  XInput.setJoystick(JOY_LEFT, out_steer, 500);
  XInput.setJoystick(JOY_RIGHT, 500,out_joyry );
  XInput.send();
}
