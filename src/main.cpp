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
      int fright = atoi(strtokIndex); // front_right

      strtokIndex = strtok(NULL, "|");
      int fleft = atoi(strtokIndex); // front_left

      strtokIndex = strtok(NULL, "|");
      int bleft = atoi(strtokIndex); // back_left

      strtokIndex = strtok(NULL, "|");
      int bright = atoi(strtokIndex); // back_right

      float fr = (float)fright;
      float fl = (float)fleft;
      float bl = (float)bleft;
      float br = (float)bright;

      Serial.print("Received floats: FR: ");
      Serial.print(fr);
      Serial.print(" FL: ");
      Serial.print(fl);
      Serial.print(" BL: ");
      Serial.print(bl);
      Serial.print(" BR: ");
      Serial.println(br);
      // // Print
      if (fr > 0 && fr < 25)
      {
        float ratio = 26 / fr;
        fr = fr * ratio;
        fl = fl * ratio;
        bl = bl * ratio;
        br = br * ratio;
      }
      if (fr < 0 && fr > -25)
      {
        float ratio = -26 / fr;
        fr = fr * ratio;
        fl = fl * ratio;
        bl = bl * ratio;
        br = br * ratio;
      }
      if (fl > 0 && fl < 25)
      {
        float ratio = 26 / fl;
        fr = fr * ratio;
        fl = fl * ratio;
        bl = bl * ratio;
        br = br * ratio;
      }
      if (fl < 0 && fl > -25)
      {
        float ratio = -26 / fl;
        fr = fr * ratio;
        fl = fl * ratio;
        bl = bl * ratio;
        br = br * ratio;
      }
      if (bl > 0 && bl < 25)
      {
        float ratio = 26 / bl;
        fr = fr * ratio;
        fl = fl * ratio;
        bl = bl * ratio;
        br = br * ratio;
      }
      if (bl < 0 && bl > -25)
      {
        float ratio = -26 / bl;
        fr = fr * ratio;
        fl = fl * ratio;
        bl = bl * ratio;
        br = br * ratio;
      }
      if (br > 0 && br < 25)
      {
        float ratio = 26 / br;
        fr = fr * ratio;
        fl = fl * ratio;
        bl = bl * ratio;
        br = br * ratio;
      }
      if (br < 0 && br > -25)
      {
        float ratio = -26 / br;
        fr = fr * ratio;
        fl = fl * ratio;
        bl = bl * ratio;
        br = br * ratio;
      }

      if (fr > 250 || fr < -250)
      {
        fr = 0;
      }
      if (fl > 250 || fl < -250)
      {
        fl = 0;
      }
      if (br > 250 || br < -250)
      {
        br = 0;
      }
      if (bl > 250 || bl < -250)
      {
        bl = 0;
      }
      fright = (int)fr;
      fleft = (int)fl;
      bleft = (int)bl;
      bright = (int)br;

      Serial.print("Modified floats: FR: ");
      Serial.print(fright);
      Serial.print(" FL: ");
      Serial.print(fleft);
      Serial.print(" BL: ");
      Serial.print(bleft);
      Serial.print(" BR: ");
      Serial.println(bright);
      if (fr < 255 || br < 255 || bl < 255 || fl < 255)
      {
        motor1.setSpeed(fright * 1);
        motor2.setSpeed(bright * 1);
        motor3.setSpeed(bleft * 1);
        motor4.setSpeed(fleft * 1);
        delay(950);
        motor1.setSpeed(0);
        motor2.setSpeed(0);
        motor3.setSpeed(0);
        motor4.setSpeed(0);
      }
      ndx = 0;
      isDataComplete = false;
    }
  }
}