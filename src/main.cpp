// #include <Arduino.h>
#include <CytronMotorDriver.h>

CytronMD motor2(PWM_DIR, 22, 20); // front right - m2 - 1
CytronMD motor1(PWM_DIR, 11, 13); // front left - m1 - 2
CytronMD motor4(PWM_DIR, 8, 12);  // back left - m4 - 3
CytronMD motor3(PWM_DIR, 26, 21); // back right - m3 - 4

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
      int w2 = atoi(strtokIndex);

      strtokIndex = strtok(NULL, "|");
      int w1 = atoi(strtokIndex);

      strtokIndex = strtok(NULL, "|");
      int w4 = atoi(strtokIndex);

      strtokIndex = strtok(NULL, "|");
      int w3 = atoi(strtokIndex);

      // Print floats
      Serial.print("Received floats: ");
      Serial.print(w2);
      Serial.print(" ");
      Serial.print(w1);
      Serial.print(" ");
      Serial.print(w4);
      Serial.print(" ");
      Serial.println(w3);

      motor1.setSpeed(w1 * 5);
      motor2.setSpeed(w2 * 5);
      motor3.setSpeed(w3 * 5);
      motor4.setSpeed(w4 * 5);

      ndx = 0;
      isDataComplete = false;
    }
  }
}