#define SR_SER 4
#define SR_RCLK 5
#define SR_SCLK 6

void writeByte();

byte val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SR_SER, OUTPUT);
  pinMode(SR_RCLK, OUTPUT);
  pinMode(SR_SCLK, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    val = Serial.read();
    writeByte();
  }
}

void writeByte() {
  shiftOut(SR_SER, SR_SCLK, MSBFIRST, val);
  digitalWrite(SR_RCLK, HIGH);
  digitalWrite(SR_RCLK, LOW);
}