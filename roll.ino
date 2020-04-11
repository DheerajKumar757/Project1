/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo servo;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "n5QokSptDxqdi0Glme_JYnvZimSoztGo";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Brothers";
char pass[] = "Apple@321";

// Setup L298N Motor Controller Input Pins
int enA = D5;
int in1 = D0;  // Motor 1
int in2 = D1;  // Motor 1

int enB = D6;
int in3 = D2;  // Motor 2
int in4 = D3;  // Motor 2


int mapped = 0;
int x = 0;
int posVert = 512;
int y = 0;
int posHorz = 512;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Set all the motor control pins to outputs
 
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
   
  // Start with motors disabled and direction forward
  
  // Motor A
  
  digitalWrite(enA, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
  // Motor B
  
  digitalWrite(enB, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  servo.attach(15);//Servo Connected to D8 of node mcu

 

}

void loop()
{
  Blynk.run();
  BLYNK_WRITE(V0);

  posVert = y;
  //posHorz = x;


  if ((posVert < 460)&&(410<x<610))
  {
    // This is Backward
 
    // Set Motor A backward
 
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
 
    // Set Motor B backward
 
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
 
    //Determine Motor Speeds
 
    analogWrite(enA, 1023-y);
    analogWrite(enB, 1023-y);
 
  }
  else if ((posVert > 564)&&(410<x<610))
  {
    // This is Forward
 
    // Set Motor A forward
 
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
 
    // Set Motor B forward
 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
 
    //Determine Motor Speeds
 
    analogWrite(enA, posVert);
    analogWrite(enB, posVert);
 
  }
  else
  {
    // This is Stopped
    digitalWrite(enA, LOW);
    digitalWrite(enB, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    servo.write(90);
 
  }


  // Now do the steering
  // The Horizontal position will "weigh" the motor speed
  // Values for each motor
 
  if ((x < 410)&&(410<y<610))
  {
    // Move Left
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);

    posHorz = 1023-x;
    mapped = map(x,0,1023,55,135);
    servo.write(mapped);
    analogWrite(enA, posHorz-200);
    analogWrite(enB, posHorz+400);
 
  }
  else if ((x > 610)&&(410<y<610))
  {
    // Move Right
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);

    mapped = map(x,0,1023,55,135);
    servo.write(mapped);
    analogWrite(enA,x+400);
    analogWrite(enB,x-200);  
 
  }
  
}
BLYNK_WRITE(V0)
{
  x = param[0].asInt();
  Serial.print("Value of x is: ");
  Serial.print(x);
  Serial.print("\n");

  y = param[1].asInt();
  Serial.print("Value of y is: ");
  Serial.print(y);
  Serial.print("\n");

  Serial.print("\n\n");
}
BLYNK_WRITE(V1)
{
  servo.write(90);
  servo.write(param.asInt());
}
BLYNK_WRITE(V2)
{
  servo.write(50);
}
BLYNK_WRITE(V3)
{
  servo.write(130);
}
BLYNK_WRITE(V4)
{
  servo.write(90);
}
