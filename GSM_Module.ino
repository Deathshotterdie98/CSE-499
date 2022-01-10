#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPin = 13;
int buttonState = 0;

void setup()
{
  lcd.begin();
  lcd.backlight();
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  ss.begin(GPSBaud);

  lcd.print("HI........");
  delay(1000);
  lcd.clear();
}

void loop()
{
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH)
  {
    lcd.clear();
    SMSInfo();
  }
  else if (buttonState == LOW)
  {
    displayInfo();
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    lcd.print(F("No GPS detected"));
    while (true);
  }
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    lcd.setCursor(0, 0);
    lcd.print("Lat=");
    lcd.print(gps.location.lat(), 9);
    lcd.setCursor(0, 1);
    lcd.print("Lng=");
    lcd.print(gps.location.lng(), 9);
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("INVALID");
  }
}


void SMSInfo()
{
  if (gps.location.isValid())
  {
    lcd.print("Sending SMS");
    Serial.println("AT+CMGF=1");
    delay(100);
    delay(100);
    Serial.println(gps.location.lat(), 6);
    Serial.println(gps.location.lng(), 6);
    delay(1000);
    Serial.println((char)26);
    delay(100);
    lcd.clear();


  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("INVALID");
  }
}
