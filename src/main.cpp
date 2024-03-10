// #include <Arduino.h>
#include <CytronMotorDriver.h>

CytronMD motor1(PWM_DIR, 7, 3);   // front right - m1
CytronMD motor2(PWM_DIR, 6, 2);   // back right - m2
CytronMD motor3(PWM_DIR, 21, 27); // back left - m3
CytronMD motor4(PWM_DIR, 20, 26); // front left - m4

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

      // // Print
      if (fr > 0 && fr < 25)
      {
        fr = fr + 25;
        if (fl > 0)
        {
          fl = fl + 25;
        }
        if (bl > 0)
        {
          bl = bl + 25;
        }
        if (br > 0)
        {
          br = br + 25;
        }

        if (fl < 0)
        {
          fl = fl - 25;
        }
        if (bl < 0)
        {
          bl = bl - 25;
        }
        if (br < 0)
        {
          br = br - 25;
        }
      }
      if (fr < 0 && fr > -25)
      {
        fr = fr - 25;
        if (fl > 0)
        {
          fl = fl + 25;
        }
        if (bl > 0)
        {
          bl = bl + 25;
        }
        if (br > 0)
        {
          br = br + 25;
        }

        if (fl < 0)
        {
          fl = fl - 25;
        }
        if (bl < 0)
        {
          bl = bl - 25;
        }
        if (br < 0)
        {
          br = br - 25;
        }
      }

      if (fl > 0 && fl < 25)
      {
        fl = fl + 25;
        if (fr > 0)
        {
          fr = fr + 25;
        }
        if (bl > 0)
        {
          bl = bl + 25;
        }
        if (br > 0)
        {
          br = br + 25;
        }

        if (fr < 0)
        {
          fr = fr - 25;
        }
        if (bl < 0)
        {
          bl = bl - 25;
        }
        if (br < 0)
        {
          br = br - 25;
        }
      }
      if (fl < 0 && fl > -25)
      {
        fl = fl - 25;
        if (fr > 0)
        {
          fr = fr + 25;
        }
        if (bl > 0)
        {
          bl = bl + 25;
        }
        if (br > 0)
        {
          br = br + 25;
        }

        if (fr < 0)
        {
          fr = fr - 25;
        }
        if (bl < 0)
        {
          bl = bl - 25;
        }
        if (br < 0)
        {
          br = br - 25;
        }
      }

      if (bl > 0 && bl < 25)
      {
        bl = bl + 25;
        if (fr > 0)
        {
          fr = fr + 25;
        }
        if (fl > 0)
        {
          fl = fl + 25;
        }
        if (br > 0)
        {
          br = br + 25;
        }

        if (fr < 0)
        {
          fr = fr - 25;
        }
        if (fl < 0)
        {
          fl = fl - 25;
        }
        if (br < 0)
        {
          br = br - 25;
        }
      }
      if (bl < 0 && bl > -25)
      {
        bl = bl - 25;
        if (fr > 0)
        {
          fr = fr + 25;
        }
        if (fl > 0)
        {
          fl = fl + 25;
        }
        if (br > 0)
        {
          br = br + 25;
        }

        if (fr < 0)
        {
          fr = fr - 25;
        }
        if (fl < 0)
        {
          fl = fl - 25;
        }
        if (br < 0)
        {
          br = br - 25;
        }
      }

      if (br > 0 && br < 25)
      {
        br = br + 25;
        if (fr > 0)
        {
          fr = fr + 25;
        }
        if (fl > 0)
        {
          fl = fl + 25;
        }
        if (bl > 0)
        {
          bl = bl + 25;
        }

        if (fr < 0)
        {
          fr = fr - 25;
        }
        if (fl < 0)
        {
          fl = fl - 25;
        }
        if (bl < 0)
        {
          bl = bl - 25;
        }
      }
      if (br < 0 && br > -25)
      {
        br = br - 25;
        if (fr > 0)
        {
          fr = fr + 25;
        }
        if (fl > 0)
        {
          fl = fl + 25;
        }
        if (bl > 0)
        {
          bl = bl + 25;
        }

        if (fr < 0)
        {
          fr = fr - 25;
        }
        if (fl < 0)
        {
          fl = fl - 25;
        }
        if (bl < 0)
        {
          bl = bl - 25;
        }
      }

      // if (fr > 0)
      // {
      //   fr = fr + 25;
      // }
      // if (fl > 0)
      // {
      //   fl = fl + 25;
      // }
      // if (br > 0)
      // {
      //   br = br + 25;
      // }
      // if (bl > 0)
      // {
      //   bl = bl + 25;
      // }
      // if (fr < 0)
      // {
      //   fr = fr - 25;
      // }
      // if (fl < 0)
      // {
      //   fl = fl - 25;
      // }
      // if (br < 0)
      // {
      //   br = br - 25;
      // }
      // if (bl < 0)
      // {
      //   bl = bl - 25;
      // }

      Serial.print("Received floats: FR: ");
      Serial.print(fr);
      Serial.print(" FL: ");
      Serial.print(fl);
      Serial.print(" BL: ");
      Serial.print(bl);
      Serial.print(" BR: ");
      Serial.println(br);
      if (fr < 255 && br < 255 && bl < 255 && fl < 255)
      {
        motor1.setSpeed(fr * 1);
        motor2.setSpeed(br * 1);
        motor3.setSpeed(bl * 1);
        motor4.setSpeed(fl * 1);
        delay(950);
        motor1.setSpeed(fr * 0);
        motor2.setSpeed(br * 0);
        motor3.setSpeed(bl * 0);
        motor4.setSpeed(fl * 0);
      }
      ndx = 0;
      isDataComplete = false;
    }
  }
}