#define EMIT_PIN       11    // Infra-red LEDs pin
#define LEFT_BUMP_PIN  4     // Pin to activate DN1 leftmost line sensor
#define RIGHT_BUMP_PIN 5     // Pin for the right bumper sensor (add this line)

void setup() {
  // Set initial pin modes and states
  pinMode(EMIT_PIN, INPUT); // Set EMIT as an input (off)
  pinMode(LEFT_BUMP_PIN, INPUT); // Set left line sensor pin to input
  pinMode(RIGHT_BUMP_PIN, INPUT); // Set right line sensor pin to input (add this line)

  // Start Serial, wait to connect, print a debug message.
  Serial.begin(9600);
  delay(1500);
  Serial.println("***RESET***");
}

void loop() {
  // Enable IR LEDs
  pinMode(EMIT_PIN, OUTPUT);
  digitalWrite(EMIT_PIN, LOW);

  // Prepare sensor reading for left bumper
  pinMode(LEFT_BUMP_PIN, OUTPUT);
  digitalWrite(LEFT_BUMP_PIN, HIGH);
  delayMicroseconds(10);
  pinMode(LEFT_BUMP_PIN, INPUT);
  unsigned long start_time_left = micros();
  while (digitalRead(LEFT_BUMP_PIN) == HIGH) {
    // Waiting for left bumper sensor
  }
  unsigned long end_time_left = micros();

  // Prepare sensor reading for right bumper
  pinMode(RIGHT_BUMP_PIN, OUTPUT);
  digitalWrite(RIGHT_BUMP_PIN, HIGH);
  delayMicroseconds(10);
  pinMode(RIGHT_BUMP_PIN, INPUT);
  unsigned long start_time_right = micros();
  while (digitalRead(RIGHT_BUMP_PIN) == HIGH) {
    // Waiting for right bumper sensor
  }
  unsigned long end_time_right = micros();

  // Turn off IR LEDs
  pinMode(EMIT_PIN, INPUT);

  unsigned long elapsed_time_left = end_time_left - start_time_left;
  unsigned long elapsed_time_right = end_time_right - start_time_right;

  Serial.print(elapsed_time_left);
  Serial.print(",");
  Serial.println(elapsed_time_right);
  delay(100);
}
