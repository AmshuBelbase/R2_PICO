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
      int fr = atoi(strtokIndex); // front_right

      strtokIndex = strtok(NULL, "|");
      int fl = atoi(strtokIndex); // front_left

      strtokIndex = strtok(NULL, "|");
      int bl = atoi(strtokIndex); // back_left

      strtokIndex = strtok(NULL, "|");
      int br = atoi(strtokIndex); // back_right

      // Print
      Serial.print("Received floats: FR: ");
      Serial.print(fr);
      Serial.print(" FL: ");
      Serial.print(fl);
      Serial.print(" BL: ");
      Serial.print(bl);
      Serial.print(" BR: ");
      Serial.println(br);

      motor1.setSpeed(fl * 1);
      motor2.setSpeed(fr * 1);
      motor3.setSpeed(br * 1);
      motor4.setSpeed(bl * 1);
      delay(950);
      motor1.setSpeed(fl * 0);
      motor2.setSpeed(fr * 0);
      motor3.setSpeed(br * 0);
      motor4.setSpeed(bl * 0);
      ndx = 0;
      isDataComplete = false;
    }
  }
}