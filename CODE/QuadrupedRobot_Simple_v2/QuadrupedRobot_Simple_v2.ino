// Simple Gait Implementation - Based on your existing code
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Your existing variables
String inputString = "";
boolean stringComplete = false;
int currentPos[16];

// Simple gait control
bool continuousWalk = false;
int walkType = 0; // 0=stop, 1=crawl, 2=trot, 3=gallop
int stepCounter = 0;

// Your existing functions (unchanged)
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

void compact() {
  smoothSetPair(0, 80, 1, 570);
  smoothSetPair(14, 570, 15, 80);
  smoothSetPair(4, 470, 5, 220);
  smoothSetPair(6, 240, 7, 450);
  smoothSetPair(8, 470, 9, 230);
  smoothSetPair(10, 450, 11, 275);
}

void sit90() {
  smoothSetPair(0, 190, 1, 460);
  smoothSetPair(14, 500, 15, 150);
  smoothSetPair(4, 560, 5, 140);
  smoothSetPair(6, 200, 7, 500);
  smoothSetPair(8, 470, 9, 230);
  smoothSetPair(10, 450, 11, 275);
}

void standstraight() {
  smoothSetPair(0, 290, 1, 320);
  smoothSetPair(14, 360, 15, 290);
  smoothSetPair(4, 500, 5, 200);
  smoothSetPair(6, 250, 7, 450);
  smoothSetPair(8, 470, 9, 230);
  smoothSetPair(10, 470, 11, 275);
}

// Your original walk function
void walk() {
  int i = 0;
  while(i < 10) {
    smoothSetPair(0, 290, 1, 290);
    smoothSetPair(14, 360, 15, 290);
    smoothSetPair(4, 500, 5, 200);
    smoothSetPair(6, 250, 7, 430);
    smoothSetPair(8, 470, 9, 230);
    smoothSetPair(10, 470, 11, 275);
    delay(1000);
    
    smoothSetPair(0, 260, 1, 320);
    smoothSetPair(14, 390, 15, 260);
    smoothSetPair(4, 500, 5, 180);
    smoothSetPair(6, 250, 7, 450);
    smoothSetPair(8, 470, 9, 230);
    smoothSetPair(10, 470, 11, 275);
    delay(1000);
    i++;
  }
}

// NEW: Crawl gait - one leg at a time
void crawlStep() {
  int legSequence[4][12] = {
    // Front Left lift
    {270, 290, 360, 290, 500, 200, 250, 450, 470, 230, 470, 275},
    // Front Right lift  
    {290, 320, 340, 260, 500, 200, 250, 450, 470, 230, 470, 275},
    // Back Left lift
    {290, 320, 360, 290, 500, 200, 250, 450, 450, 200, 470, 275},
    // Back Right lift
    {290, 320, 360, 290, 500, 200, 250, 450, 470, 230, 450, 245}
  };
  
  int leg = stepCounter % 4;
  
  // Move all servos to the position for this leg
  smoothSetPair(0, legSequence[leg][0], 1, legSequence[leg][1]);
  smoothSetPair(14, legSequence[leg][2], 15, legSequence[leg][3]);
  smoothSetPair(4, legSequence[leg][4], 5, legSequence[leg][5]);
  smoothSetPair(6, legSequence[leg][6], 7, legSequence[leg][7]);
  smoothSetPair(8, legSequence[leg][8], 9, legSequence[leg][9]);
  smoothSetPair(10, legSequence[leg][10], 11, legSequence[leg][11]);
  
  delay(1500); // Hold position
  stepCounter++;
}

// NEW: Trot gait - diagonal pairs
void trotStep() {
  if (stepCounter % 2 == 0) {
    // Front-left and back-right up
    smoothSetPair(0, 270, 1, 290);   // FL lift
    smoothSetPair(14, 360, 15, 290); // FR ground
    smoothSetPair(4, 500, 5, 200);
    smoothSetPair(6, 250, 7, 450);
    smoothSetPair(8, 470, 9, 230);   // BL ground
    smoothSetPair(10, 450, 11, 245); // BR lift
  } else {
    // Front-right and back-left up
    smoothSetPair(0, 290, 1, 320);   // FL ground
    smoothSetPair(14, 340, 15, 260); // FR lift
    smoothSetPair(4, 500, 5, 200);
    smoothSetPair(6, 250, 7, 450);
    smoothSetPair(8, 450, 9, 200);   // BL lift
    smoothSetPair(10, 470, 11, 275); // BR ground
  }
  
  delay(800);
  stepCounter++;
}

// NEW: Gallop gait - front legs together, back legs together
void gallopStep() {
  if (stepCounter % 4 == 0) {
    // Front legs up
    smoothSetPair(0, 270, 1, 290);
    smoothSetPair(14, 340, 15, 260);
    smoothSetPair(4, 500, 5, 200);
    smoothSetPair(6, 250, 7, 450);
    smoothSetPair(8, 470, 9, 230);
    smoothSetPair(10, 470, 11, 275);
  } else if (stepCounter % 4 == 1) {
    // Front legs down
    smoothSetPair(0, 290, 1, 320);
    smoothSetPair(14, 360, 15, 290);
    smoothSetPair(4, 500, 5, 200);
    smoothSetPair(6, 250, 7, 450);
    smoothSetPair(8, 470, 9, 230);
    smoothSetPair(10, 470, 11, 275);
  } else if (stepCounter % 4 == 2) {
    // Back legs up
    smoothSetPair(0, 290, 1, 320);
    smoothSetPair(14, 360, 15, 290);
    smoothSetPair(4, 500, 5, 200);
    smoothSetPair(6, 250, 7, 450);
    smoothSetPair(8, 450, 9, 200);
    smoothSetPair(10, 450, 11, 245);
  } else {
    // Back legs down
    standstraight();
  }
  
  delay(600);
  stepCounter++;
}

void setup() {
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(50);
  
  Serial.begin(115200);
  Serial.println("Enhanced Robot Ready!");
  Serial.println("Commands: compact, sit90, stand, walk, crawl, trot, gallop, stop");
}

void loop() {
  // Handle serial input (your existing code)
  while (Serial.available()) {
    char inChar = Serial.read();
    inputString += inChar;
    
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  
  if (stringComplete) {
    inputString.trim();

    if (inputString == "compact") {
      continuousWalk = false;
      compact();
      Serial.println("Compact position");
    }
    else if (inputString == "sit90") {
      continuousWalk = false;
      sit90();
      Serial.println("Sitting");
    }
    else if (inputString == "walk") {
      continuousWalk = false;
      walk();
      Serial.println("Basic walk completed");
    }
    else if (inputString == "stand") {
      continuousWalk = false;
      standstraight();
      Serial.println("Standing");
    }
    else if (inputString == "crawl") {
      continuousWalk = true;
      walkType = 1;
      stepCounter = 0;
      Serial.println("Crawl gait started");
    }
    else if (inputString == "trot") {
      continuousWalk = true;
      walkType = 2;
      stepCounter = 0;
      Serial.println("Trot gait started");
    }
    else if (inputString == "gallop") {
      continuousWalk = true;
      walkType = 3;
      stepCounter = 0;
      Serial.println("Gallop gait started");
    }
    else if (inputString == "stop") {
      continuousWalk = false;
      standstraight();
      Serial.println("Stopped");
    }
    else {
      Serial.println("Invalid option: " + inputString);
    }
    
    inputString = "";
    stringComplete = false;
  }
  
  // Execute continuous walking gaits
  if (continuousWalk) {
    switch (walkType) {
      case 1:
        crawlStep();
        break;
      case 2:
        trotStep();
        break;
      case 3:
        gallopStep();
        break;
    }
  }
  
  delay(50); // Small delay for responsiveness
}
