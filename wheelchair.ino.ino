#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup()
{
  Serial.begin(9600);
  Serial.println("Initialize Sensor");
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  //Ideal Mode
  pinMode(13, OUTPUT);
  //Motor A
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  //Motor B
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
  // Read normalized values
  Vector normAccel = mpu.readNormalizeAccel();

  // Calculate Pitch & Roll
  int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis)) * 180.0) / M_PI;
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis) * 180.0) / M_PI;

  // Output
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);

  Serial.println();

  if (pitch > 50)
  {
    digitalWrite(13, LOW);
    //Motor A
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    //Motor B
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
  }
  else if (pitch < -50)
  {
    digitalWrite(13, LOW);
    //Motor A
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    //Motor B
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
  }
  else if (roll > 50)
  {
    digitalWrite(13, LOW);
    //Motor A
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    //Motor B
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
  }
  else if (roll < -50)
  {
    digitalWrite(13, LOW);
    //Motor A
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    //Motor B
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
  }
  else
  {
    digitalWrite(13, HIGH);
    //Motor A
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    //Motor B
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }

}
