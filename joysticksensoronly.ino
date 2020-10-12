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
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);
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



  //Reset Bias with Input
  Serial.print("| Steering Raw: ");
  Serial.print(readsteer);
  Serial.print(" | Out: ");
  Serial.print(out_steer);
  Serial.print(" | JoyR X Raw: ");
  Serial.print(xachse);
  Serial.print(" | JoyR Y Raw: ");
  Serial.print(yachse);
  Serial.print(" | Out: ");
  Serial.print(out_joyry);
  Serial.print(" | ");
  Serial.print(switcha);
  Serial.print("\n");


  delay(100);
}
