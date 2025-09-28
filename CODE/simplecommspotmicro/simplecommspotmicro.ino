// === Quadruped Robot with Smooth Transitions and Serial Menu ===
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// State tracking
String inputString = "";
boolean stringComplete = false;
int currentPos[16];  

// Smooth single servo move
void smoothSetPWM(uint8_t channel, int target, int speed = 1, int delayMs = 3) {
  int current = currentPos[channel];
  if (current == 0) current = target;
  int step = (current < target) ? 1 : -1;

  for (int pos = current; pos != target; pos += step * speed) {
    pwm.setPWM(channel, 0, pos);
    delay(delayMs);
  }
  pwm.setPWM(channel, 0, target);
  currentPos[channel] = target;
}

// Smooth two servos in sync
void smoothSetPair(uint8_t chA, int tgtA, uint8_t chB, int tgtB, int speed = 1, int delayMs = 3) {
  int curA = currentPos[chA];
  int curB = currentPos[chB];
  if (curA == 0) curA = tgtA;
  if (curB == 0) curB = tgtB;

  int maxSteps = max(abs(tgtA - curA), abs(tgtB - curB)) / speed;
  for (int i = 1; i <= maxSteps; i++) {
    int posA = curA + ((tgtA - curA) * i) / maxSteps;
    int posB = curB + ((tgtB - curB) * i) / maxSteps;
    pwm.setPWM(chA, 0, posA);
    pwm.setPWM(chB, 0, posB);
    delay(delayMs);
  }
  pwm.setPWM(chA, 0, tgtA);
  pwm.setPWM(chB, 0, tgtB);
  currentPos[chA] = tgtA;
  currentPos[chB] = tgtB;
}

// === CUSTOM POSITIONS (yours) ===

// Sleep position
void sleepPos() {
  smoothSetPair(0, 190, 1, 460);
  smoothSetPair(14, 470, 15, 180);

  smoothSetPair(4, 560, 5, 140);
  smoothSetPair(6, 160, 7, 540);

  smoothSetPair(8, 450, 9, 230);
  smoothSetPair(10, 450, 11, 275);
  Serial.println("Now in SLEEP position");
}

// Sitting position 1
void sit1() {
  smoothSetPair(0, 190, 1, 460);
  smoothSetPair(14, 550, 15, 80);

  smoothSetPair(4, 560, 5, 140);
  smoothSetPair(6, 160, 7, 540);

  smoothSetPair(8, 450, 9, 230);
  smoothSetPair(10, 450, 11, 275);
  Serial.println("Now in SIT POSITION 1");
}

// Sitting position 2
void sit2() {
  smoothSetPair(0, 290, 1, 340);
  smoothSetPair(14, 550, 15, 80);

  smoothSetPair(4, 560, 5, 140);
  smoothSetPair(6, 300, 7, 400);

  smoothSetPair(8, 450, 9, 230);
  smoothSetPair(10, 450, 11, 275);
  Serial.println("Now in SIT POSITION 2");
}

// Stand straight
void standstraight() {
  smoothSetPair(0, 290, 1, 320);
  smoothSetPair(14, 360, 15, 290);

  smoothSetPair(4, 500, 5, 200);
  smoothSetPair(6, 250, 7, 450);

  smoothSetPair(8, 470, 9, 230);
  smoothSetPair(10, 470, 11, 275);
  Serial.println("Now in STAND position");
}

void setup() {
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(50);

  Serial.begin(115200);
  Serial.println("=== Quadruped Robot Ready ===");
  Serial.println("Commands available:");
  Serial.println("sleep   - Sleep position");
  Serial.println("sit1    - Sitting position 1");
  Serial.println("sit2    - Sitting position 2");
  Serial.println("stand   - Stand straight");
}

void loop() {
  // Handle serial input
  while (Serial.available()) {
    char inChar = Serial.read();
    inputString += inChar;
    if (inChar == '\n') stringComplete = true;
  }

  if (stringComplete) {
    inputString.trim();

    if (inputString == "sleep") sleepPos();
    else if (inputString == "sit1") sit1();
    else if (inputString == "sit2") sit2();
    else if (inputString == "stand") standstraight();
    else Serial.println("Invalid command: " + inputString);

    // Reset input
    inputString = "";
    stringComplete = false;

    // Print menu again
    Serial.println("\nCommands: sleep, sit1, sit2, stand");
  }
}
