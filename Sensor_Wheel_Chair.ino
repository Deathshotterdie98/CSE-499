#include <Wire.h>
#include <MPU6050.h>


int M_A1 = 3;
int M_A2 = 5;
int M_B1 = 10;
int M_B2 = 11;

#define TRIGGER_PIN  9
#define ECHO_PIN     6
#define MAX_DISTANCE 200
//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

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
  pinMode(M_A1, OUTPUT);
  pinMode(M_A2, OUTPUT);
  //Motor B
  pinMode(M_B1, OUTPUT);
  pinMode(M_B2, OUTPUT);
}

void loop()
{

  Vector normAccel = mpu.readNormalizeAccel();

  
  int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis)) * 180.0) / M_PI;
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis) * 180.0) / M_PI;

  Serial.print(sonar.ping_cm());

  if (sonar.ping_cm() > 30)
  {
    Serial.print(" Pitch = ");
    Serial.print(pitch);
    Serial.print(" Roll = ");
    Serial.print(roll);

    Serial.println();

    if (pitch > 50)
    {
      digitalWrite(13, LOW);
      //Motor A
      digitalWrite(M_A1, LOW);
      digitalWrite(M_A2, HIGH);
      //Motor B
      digitalWrite(M_B1, HIGH);
      digitalWrite(M_B2, LOW);
    }
    else if (pitch < -50)
    {
      digitalWrite(13, LOW);
      //Motor A
      digitalWrite(M_A1, HIGH);
      digitalWrite(M_A2, LOW);
      //Motor B
      digitalWrite(M_B1, LOW);
      digitalWrite(M_B2, HIGH);
    }
    else if (roll > 50)
    {
      digitalWrite(13, LOW);
      //Motor A
      digitalWrite(M_A1, LOW);
      digitalWrite(M_A2, HIGH);
      //Motor B
      digitalWrite(M_B1, LOW);
      digitalWrite(M_B2, HIGH);
    }
    else if (roll < -50)
    {
      digitalWrite(13, LOW);
      //Motor A
      digitalWrite(M_A1, HIGH);
      digitalWrite(M_A2, LOW);
      //Motor B
      digitalWrite(M_B1, HIGH);
      digitalWrite(M_B2, LOW);
    }
    else
    {
      digitalWrite(13, HIGH);
      //Motor A
      digitalWrite(M_A1, LOW);
      digitalWrite(M_A2, LOW);
      //Motor B
      digitalWrite(M_B1, LOW);
      digitalWrite(M_B2, LOW);
    }

  }
  else
  {
    digitalWrite(13, HIGH);
    //Motor A
    digitalWrite(M_A1, LOW);
    digitalWrite(M_A2, LOW);
    //Motor B
    digitalWrite(M_B1, LOW);
    digitalWrite(M_B2, LOW);
    Serial.print("Stoped");
  }
}
