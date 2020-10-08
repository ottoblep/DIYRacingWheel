
#include <XInput.h>
// Setup
const boolean UseLeftJoystick   = true;  // set to true to enable left joystick
const boolean InvertLeftYAxis   = false;  // set to true to use inverted left joy Y

const boolean UseRightJoystick  = false;  // set to true to enable right joystick
const boolean InvertRightYAxis  = false;  // set to true to use inverted right joy Y

const boolean UseTriggerButtons = false;   // set to false if using analog triggers

static int bias = -80;
static int cutoff = 400;
static int deadzone = 7;
void setup() {
  XInput.begin();
  XInput.setJoystickRange(0, 2*sqrt(cutoff));  // Set joystick range to the ADC
  XInput.setAutoSend(false);  // Wait for all controls before sending

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {

  int readrechts = analogRead(A0);
  int readlinks = analogRead(A1);
  int diff = readlinks - readrechts + bias;
  int out;
  if (diff>=0) out = sqrt(diff);
  if (diff<0) out = -sqrt(abs(diff));
  if (diff >= cutoff) out = sqrt(cutoff);
  if (diff <= -cutoff ) out = -sqrt(cutoff);
  if (diff < deadzone && diff > -deadzone) out = 0;
  XInput.setJoystick(JOY_LEFT, out+sqrt(cutoff), 0);
  XInput.send();
}
