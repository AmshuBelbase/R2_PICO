#include <Arduino.h>

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
      // Parse buffer and print as before

      // Parse float strings
      char *strtokIndex;
      strtokIndex = strtok(receivedChars, "|");
      float float1 = atof(strtokIndex);

      strtokIndex = strtok(NULL, "|");
      float float2 = atof(strtokIndex);

      strtokIndex = strtok(NULL, "|");
      float float3 = atof(strtokIndex);

      strtokIndex = strtok(NULL, "|");
      float float4 = atof(strtokIndex);

      // Print floats
      Serial.print("Received floats: ");
      Serial.print(float1);
      Serial.print(", ");
      Serial.print(float2);
      Serial.print(", ");
      Serial.print(float3);
      Serial.print(", ");
      Serial.println(float4);

      ndx = 0;
      isDataComplete = false;
    }
  }
}