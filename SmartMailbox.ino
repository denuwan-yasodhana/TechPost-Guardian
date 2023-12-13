#include <Servo.h>

int servoPin = 9;
int irPin1 = 8;
int irPin2 = 7;
int irPin3 = 6;
int pushButtonIn = 5; 
int buzzerPin = 4;
int ledPin1 = 10; 
int ledPin2 = 11; 
int ledPin3 = 12;

Servo srv1;

int irCheck;

int count = 0;

void setup() {

  Serial.begin(9600);
  pinMode(pushButtonIn, INPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(irPin1, INPUT);
  pinMode(irPin2, INPUT);
  pinMode(irPin3, INPUT);
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  
  srv1.attach(servoPin);

  srv1.write(0);

}

void loop() {
    int  buttonState = digitalRead(pushButtonIn);

    if(buttonState == HIGH)
    {  
      Serial.println("Door is opened");
      srv1.write(90);
    }
    if(digitalRead(irPin1)==LOW)
    { 
       Serial.println("Pass 1st checkpoint");  
       count = count + 1;
       //Serial.println(count); 
       irCheck = 1;
       digitalWrite(ledPin1, HIGH);
       delay(2000); 
       digitalWrite(ledPin1, LOW); 
  
        if(digitalRead(irPin2)==LOW)
        { 
           Serial.println("Pass 2nd checkpoint");  
           irCheck = 2;
           digitalWrite(ledPin2, HIGH);
           delay(2000); 
           digitalWrite(ledPin2, LOW);
           srv1.write(0);
           Serial.println("Door closed");

           if(digitalRead(irPin3)==LOW)
            { 
               Serial.println("Pass 3rd checkpoint");
               irCheck = 3;  
               digitalWrite(ledPin3, HIGH);
               delay(2000); 
               digitalWrite(ledPin3, LOW); 
            }
        }
    }
    
  switch(irCheck) 
  {
    case 1:
       if(count>1)
       {
          tone(buzzerPin, 2000);
          delay(2000);
          for(int i=1; i<=10; i++)
          {
            Serial.println("Parcel is insecure");
            digitalWrite(ledPin3, HIGH);
            delay(100);
            digitalWrite(ledPin3, LOW);
            delay(100);
            digitalWrite(ledPin2, HIGH);
            delay(100);
            digitalWrite(ledPin2, LOW);
            delay(100);
            digitalWrite(ledPin1, HIGH);
            delay(100);
            digitalWrite(ledPin1, LOW);
            delay(100);
            tone(buzzerPin, 2000);
            delay(3000);
          }
       }
       Serial.println("Parcel is not positioned correctly");
       break;
    case 2:
       if(count>1)
       {
          tone(buzzerPin, 2000);
          delay(2000);
          for(int i=1; i<=10; i++)
          {
            Serial.println("Parcel is insecure");
            digitalWrite(ledPin3, HIGH);
            delay(100);
            digitalWrite(ledPin3, LOW);
            delay(100);
            digitalWrite(ledPin2, HIGH);
            delay(100);
            digitalWrite(ledPin2, LOW);
            delay(100);
            digitalWrite(ledPin1, HIGH);
            delay(100);
            digitalWrite(ledPin1, LOW);
            delay(100);
            tone(buzzerPin, 2000);
            delay(3000);
          }
       }
       Serial.println("Parcel is not positioned correctly");
       break;
    case 3:
       if(digitalRead(irPin3)==HIGH)
       {
         Serial.println("Parcel has been removed");
         break; 
       }
       Serial.println("Parcel placed properly");
       break;
  }    
}
