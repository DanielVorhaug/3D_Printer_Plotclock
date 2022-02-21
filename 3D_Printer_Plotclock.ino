#define BEEPER_PIN          27

#define X_STEP_PIN          15
#define X_DIR_PIN           21
#define X_ENABLE_PIN        14

#define Y_STEP_PIN          22
#define Y_DIR_PIN           23
#define Y_ENABLE_PIN        14

#define Z_STEP_PIN          3
#define Z_DIR_PIN           2
#define Z_ENABLE_PIN        26

#define STEP_DELAY          500 // [Microseconds]


void setup() {
  pinMode(BEEPER_PIN, OUTPUT);
  
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);
  
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  
  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN,OUTPUT); 
  
  digitalWrite(X_ENABLE_PIN,LOW);
  digitalWrite(Y_ENABLE_PIN,LOW);
  digitalWrite(Z_ENABLE_PIN,LOW);
}


void loop() {
  int steps = 2000;
  move_motor(HIGH, steps, X_DIR_PIN, X_STEP_PIN);
  move_motor(HIGH, steps, Y_DIR_PIN, Y_STEP_PIN);
  move_motor(HIGH, steps, Z_DIR_PIN, Z_STEP_PIN);
  move_motor(LOW, steps, X_DIR_PIN, X_STEP_PIN);
  move_motor(LOW, steps, Y_DIR_PIN, Y_STEP_PIN);
  move_motor(LOW, steps, Z_DIR_PIN, Z_STEP_PIN);

  beep();

}

void move_motor(bool direction, int steps, int dir_pin, int step_pin) {
  digitalWrite(dir_pin, direction);
  for(int i = 0; i < steps; i++) {
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(STEP_DELAY);
  }
}

void beep() {
  digitalWrite(BEEPER_PIN, HIGH);
  delay(1);
  digitalWrite(BEEPER_PIN, LOW);
}
