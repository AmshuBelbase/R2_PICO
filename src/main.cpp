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
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
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
      int dela = 50;
      int thres = 30;

      if (fr > 5 && fr < thres)
      {
        fr = thres;
        fl = 0;
        br = 0;
        // dela = fr * 20;
      }
      if (bl > 5 && bl < thres)
      {
        bl = thres;
        fl = 0;
        br = 0;
        // dela = bl * 20;
      }
      if (fr < -5 && fr > -thres)
      {
        fr = -thres;
        fl = 0;
        br = 0;
        // dela = -fr * 20;
      }
      if (bl < -5 && bl > -thres)
      {
        bl = -thres;
        fl = 0;
        br = 0;
        // dela = -bl * 20;
      }

      if (fl > 5 && fl < thres)
      {
        fl = thres;
      }
      if (br > 5 && br < thres)
      {
        br = thres;
      }
      if (fl < -5 && fl > -thres)
      {
        fl = -thres;
      }
      if (br < -5 && br > -thres)
      {
        br = -thres;
      }

      if (fr > 250 || fr < -250 || fl > 250 || fl < -250 || br > 250 || br < -250 || bl > 250 || bl < -250)
      {
        fr = 0;
        fl = 0;
        br = 0;
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
      if ((fr < 255 && br < 255 && bl < 255 && fl < 255) && (fr > -255 && br > -255 && bl > -255 && fl > -255))
      {
        motor1.setSpeed(fright * 1);
        motor2.setSpeed(bright * 1);
        motor3.setSpeed(bleft * 1);
        motor4.setSpeed(fleft * 1);
        // delay(dela);
        // motor1.setSpeed(0);
        // motor2.setSpeed(0);
        // motor3.setSpeed(0);
        // motor4.setSpeed(0);
      }
      else
      {
        Serial.println("Closing MOTORS");
      }
      ndx = 0;
      isDataComplete = false;
    }
  }

  // if ((fr > 1 && fr < thres) || (fr < -1 && fr > -thres))
  // {
  //   fr = fr * 2;
  //   bl = 0;
  //   dela = 200;
  // }
  // if ((fl > 1 && fl < thres) || (fl < -1 && fl > -thres))
  // {
  //   fl = fl * 2;
  //   br = 0;
  //   dela = 200;
  // }
  // if ((bl > 1 && bl < thres) || (bl < -1 && bl > -thres))
  // {
  //   bl = bl * 2;
  //   fr = 0;
  //   dela = 200;
  // }
  // if ((br > 1 && br < thres) || (br < -1 && br > -thres))
  // {
  //   br = br * 2;
  //   fl = 0;
  //   dela = 200;
  // }

  // Serial.print("Semi Modified floats: FR: ");
  // Serial.print(fr);
  // Serial.print(" FL: ");
  // Serial.print(fl);
  // Serial.print(" BL: ");
  // Serial.print(bl);
  // Serial.print(" BR: ");
  // Serial.println(br);

  // if (fr > 1 && fr < thres)
  // {
  //   float ratio = thres / fr;
  //   fr = fr * ratio;
  //   fl = fl * ratio;
  //   bl = bl * ratio;
  //   br = br * ratio;
  // }
  // if (fr < -1 && fr > -thres)
  // {
  //   float ratio = -thres / fr;
  //   fr = fr * ratio;
  //   fl = fl * ratio;
  //   bl = bl * ratio;
  //   br = br * ratio;
  // }
  // if (fl > 1 && fl < thres)
  // {
  //   float ratio = thres / fl;
  //   fr = fr * ratio;
  //   fl = fl * ratio;
  //   bl = bl * ratio;
  //   br = br * ratio;
  // }
  // if (fl < -1 && fl > -thres)
  // {
  //   float ratio = -thres / fl;
  //   fr = fr * ratio;
  //   fl = fl * ratio;
  //   bl = bl * ratio;
  //   br = br * ratio;
  // }
  // if (bl > 1 && bl < thres)
  // {
  //   float ratio = thres / bl;
  //   fr = fr * ratio;
  //   fl = fl * ratio;
  //   bl = bl * ratio;
  //   br = br * ratio;
  // }
  // if (bl < -1 && bl > -thres)
  // {
  //   float ratio = -thres / bl;
  //   fr = fr * ratio;
  //   fl = fl * ratio;
  //   bl = bl * ratio;
  //   br = br * ratio;
  // }
  // if (br > 1 && br < thres)
  // {
  //   float ratio = thres / br;
  //   fr = fr * ratio;
  //   fl = fl * ratio;
  //   bl = bl * ratio;
  //   br = br * ratio;
  // }
  // if (br < -1 && br > -thres)
  // {
  //   float ratio = -thres / br;
  //   fr = fr * ratio;
  //   fl = fl * ratio;
  //   bl = bl * ratio;
  //   br = br * ratio;
  // }
}