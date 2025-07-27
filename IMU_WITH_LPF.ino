// === Motor B Pins ===
#define BIN1 5     // D5
#define BIN2 6     // D6
#define PWMB 10    // D10 (PWM)
#define STBY 11    // D11

// === Encoder Pins ===
#define C1B 3      // D3 (Interrupt 1)
#define C2B 12     // D12

volatile long encoderCount = 0;

void setup() {
  // Motor Pins
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  // Encoder Pins
  pinMode(C1B, INPUT);
  pinMode(C2B, INPUT);

  Serial.begin(9600);

  // Attach interrupt for C1B (Interrupt 1 = pin D3 on Uno)
  attachInterrupt(digitalPinToInterrupt(C1B), readEncoder, RISING);

  // Start Motor B forward
  digitalWrite(STBY, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 255); // Full speed
}

void loop() {
  // Print encoder value every 200ms
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint >= 200) {
    lastPrint = millis();
    Serial.print("Encoder Count: ");
    Serial.println(encoderCount);
  }
}

void readEncoder() {
  // Quadrature decoding (optional, you can skip C2B if not needed)
  if (digitalRead(C2B) == HIGH)
    encoderCount++;
  else
    encoderCount--;
}
