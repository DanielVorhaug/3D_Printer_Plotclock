#define BEEPER_PIN 27

#define X_STEP_PIN 15
#define X_DIR_PIN 21
#define X_ENABLE_PIN 14

#define Y_STEP_PIN 22
#define Y_DIR_PIN 23
#define Y_ENABLE_PIN 14

#define Z_STEP_PIN 3
#define Z_DIR_PIN 2
#define Z_ENABLE_PIN 26

#define STEP_DELAY 500 // [Microseconds]

#define C3 130.81F
#define D3 146.83F
#define E3 164.81F
#define F3 174.61F
#define G3 196.00F
#define A3 220.00F
#define B3 246.94F

#define BEAT    60.0F
#define WHOLE   60.0F/BEAT
#define HALF    WHOLE/2.0F
#define FOURTH  WHOLE/4.0F

float lisa[22][2] = { 
  {C3, FOURTH}, {D3, FOURTH}, {E3, FOURTH}, {F3, FOURTH},
  {G3, HALF}, {G3, HALF},
  {A3, FOURTH}, {A3, FOURTH}, {A3, FOURTH}, {A3, FOURTH},
  {G3, WHOLE},

  {F3, FOURTH}, {F3, FOURTH}, {F3, FOURTH}, {F3, FOURTH},
  {E3, HALF}, {E3, HALF},
  {D3, FOURTH}, {D3, FOURTH}, {D3, FOURTH}, {D3, FOURTH},
  {C3, WHOLE}
  };

void setup()
{
  pinMode(BEEPER_PIN, OUTPUT);

  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);

  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);

  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);

  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);
}

void loop()
{
  int steps = 2000;
  // move_motor(HIGH, steps, X_DIR_PIN, X_STEP_PIN);
  // move_motor(HIGH, steps, Y_DIR_PIN, Y_STEP_PIN);
  // move_motor(HIGH, steps, Z_DIR_PIN, Z_STEP_PIN);
  // move_motor(LOW, steps, X_DIR_PIN, X_STEP_PIN);
  // move_motor(LOW, steps, Y_DIR_PIN, Y_STEP_PIN);
  // move_motor(LOW, steps, Z_DIR_PIN, Z_STEP_PIN);

  //move_motor(0, steps, STEP_DELAY, Z_DIR_PIN, Z_STEP_PIN);

  //play_tone(1.0f, 130.81f, Z_DIR_PIN, Z_STEP_PIN);

  for (int i = 0; i < sizeof(lisa)/sizeof(lisa[0]); i++) {
    play_tone(lisa[i][1], lisa[i][0], X_DIR_PIN, X_STEP_PIN);
    //delay(500);
  }
  delay(3000);

  // beep();
}

void play_tone(
    float duration, // [seconds]
    float frequency,
    int dir_pin,
    int step_pin)
{
  static int position = 0;
  int delay = round(frequency * 500 / 2461);
  int steps = round((1e6 * duration / delay) / 2);

  bool direction = 1;
  if (position)
  {
    direction = 1;
    position += steps;
  }
  else
  {
    direction = 0;
    position -= steps;
  }

  move_motor(direction, steps, delay, dir_pin, step_pin);
}

void move_motor(bool direction, int steps, int delay, int dir_pin, int step_pin)
{
  digitalWrite(dir_pin, direction);
  for (int i = 0; i < steps; i++)
  {
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(STEP_DELAY);
  }
}



void beep()
{
  digitalWrite(BEEPER_PIN, HIGH);
  delay(1);
  digitalWrite(BEEPER_PIN, LOW);
}
