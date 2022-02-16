#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "GY521.h"

GY521 sensor(0x68);
Adafruit_SSD1306 display(128, 64, &Wire, -1);
int kot;
int zero;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  delay(100);
  while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521");
    delay(1000);
  }
  sensor.setAccelSensitivity(2);
  sensor.setGyroSensitivity(1);

  sensor.setThrottle();

  sensor.axe = 0;
  sensor.aye = 0;
  sensor.aze = 0;
  sensor.gxe = 0;
  sensor.gye = 0;
  sensor.gze = 0;
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(500);
  display.clearDisplay();

  sensor.read();
  zero = sensor.getAngleX();

}

void loop()
{
  sensor.read();
  int absolutni_kot = (sensor.getAngleX() - zero);
  kot = map(absolutni_kot,0,84,0,80);
  kot = abs(kot);


  Serial.println(kot);
  
  display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(50, 20);
  display.print(kot);
  display.display();
}



