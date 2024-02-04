// #include <Arduino.h>
#include <CytronMotorDriver.h>

CytronMD motor1(PWM_DIR, 21, 26); // front left - m1
CytronMD motor2(PWM_DIR, 12, 8);  // front right - m2
CytronMD motor3(PWM_DIR, 13, 11); // back right - m3
CytronMD motor4(PWM_DIR, 20, 22); // back left - m4

void setup()
{
  Serial.begin(115200);
}

void loop()
{

  const byte numChars = 100;
  char receivedChars[numChars];

  byte ndx = 0;
  char endMarker = '#';
  bool isDataComplete = false;

  while (true)
  {

    while (Serial.available() > 0 && !isDataComplete)
    {
      char rc = Serial.read();
      if (rc != endMarker)
      {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars)
        {
          ndx = numChars - 1;
        }
      }
      else
      {
        isDataComplete = true;
      }
    }

    if (isDataComplete)
    {
      receivedChars[ndx] = '\0'; // terminate string
      char *strtokIndex;

      strtokIndex = strtok(receivedChars, "|");
      int w2 = atoi(strtokIndex); // front_right

      strtokIndex = strtok(NULL, "|");
      int w1 = atoi(strtokIndex); // front_left

      strtokIndex = strtok(NULL, "|");
      int w4 = atoi(strtokIndex); // back_left

      strtokIndex = strtok(NULL, "|");
      int w3 = atoi(strtokIndex); // back_right

      // Print
      Serial.print("Received floats: FR: ");
      Serial.print(w2);
      Serial.print(" FL: ");
      Serial.print(w1);
      Serial.print(" BL: ");
      Serial.print(w4);
      Serial.print(" BR: ");
      Serial.println(w3);

      motor1.setSpeed(w1 * 2.5);
      motor2.setSpeed(w2 * 2.5);
      motor3.setSpeed(w3 * 2.5);
      motor4.setSpeed(w4 * 2.5);
      delay(200);
      motor1.setSpeed(w1 * 0);
      motor2.setSpeed(w2 * 0);
      motor3.setSpeed(w3 * 0);
      motor4.setSpeed(w4 * 0);
      ndx = 0;
      isDataComplete = false;
    }
  }
}