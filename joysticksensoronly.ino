static int bias = -80;
static int cutoff = 400;
static int deadzone = 7;
void setup() {
  // put your setup code here, to run once:
   int range = 2 * cutoff;
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int readrechts = analogRead(A0);
  int readlinks = analogRead(A1);
  int diff = readlinks - readrechts + bias;
  int out;
  if (diff>=0) out = sqrt(diff);
  if (diff<0) out = -sqrt(abs(diff));
  if (diff >= cutoff) out = sqrt(cutoff);
  if (diff <= -cutoff ) out = -sqrt(cutoff);
  if (diff < deadzone && diff > -deadzone) out = 0;
  Serial.print(out);
  Serial.print(" | ");
  Serial.print(diff);
  Serial.print("\n");
  delay(100);
}
