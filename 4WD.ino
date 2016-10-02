//Beginner 4WD Kit_v1.ino (programma d'esempio evita ostacoli)

// Servo
// Red ---> 5V
// Brown ---> GND
// Yellow ---> D10

// SHARP Sensor
// Red ---> 3.3V
// Black ---> GND
// Yellow ---> A5

// test commit


#include <Motore.h> // Includiamo la nostra libreria per controllare i motori
#include <Servo.h> // Includiamo la libreria Servo per controllare quest'ultimo

Servo servo; // Dichiariamo la classe Servo come mioservo

Motore Robot; // Istanziamo la classe Motore

int SensorValue;
int SensorLeft;
int SensorRight;

int pos,i;

int centro = 90;
int destra = 180;
int sinistra = 0; 

int velocita = 230; // Qui modifichiamo la velocità del robot

int PinServo = 10; // Pin dove è collegato il servo (dovrà essere un pin che supporta la modalità PWM)

int distanza_massima = 400;
   
void setup()
{
    Serial.begin(9600); 
    
    servo.attach(PinServo); // Inizializziamo il servo al pin 10
    
    servo.write(centro); // il servo partirà da una posizione di 54° (Posizione centrale rispetto chassis)
    controllo();
}
 
void loop()
{
   do
   {
     Robot.up(velocita);
     velocita=velocita+10;  // LORENZO: INCREMENTO DI VELOCITÀ
     SensorValue= analogRead(5);
   } while (SensorValue<=distanza_massima);
   
   Robot.down(velocita);
   delay(100);   // LORENZO: OGNI QUANTO INCREMENTA
   Robot.shutdown();
   controllo();
   
     
}
    
 
void calibrazione()
{
    if (SensorValue=analogRead(5)>380)
    {
      return loop();
    }
    else
    {
      
    servo.write(destra);
    SensorRight = analogRead(5);
    // Serial.println(SensorLeft);
    delay(700);
    
    servo.write(sinistra);
    SensorLeft = analogRead(5);
    // Serial.println(SensorRight);
    delay(700);
    if (SensorLeft<SensorRight)
    {
      servo.write(centro);
      Robot.right(velocita);
      delay(600);
    }
      
    else
    {
      servo.write(centro);
      Robot.left(velocita);
      delay(600);
    }
  Robot.shutdown();
   }
}



void controllo()
{
  int valori[3]; 
  for (i=0; i<3; i++)
  {
    SensorValue = analogRead(5);
    delay(800);
    valori[i] = SensorValue;
    movimento_servo(i);
  }
  
  i=0;
  while (i<3)
  {
    if (valori[i]>=400)
    {
      pos=i;
    }
   i++;
  }
  
//  Se vuoi vedere su monitor seriale i valori del sensore
//  for (i=0; i<3; i++)
//  {
//    Serial.print("Valore: ");
//    Serial.println(valori[i]);
//    Serial.println("");
//  }
      
  
  switch (pos) {
    
    case 0:    
      servo.write(centro);
      return loop();
      break;
      
    case 1:
      servo.write(centro);
      Robot.right(velocita);
      delay(500);
      Robot.shutdown();
      return loop();
      break;
      
    case 2:
      servo.write(centro);
      Robot.left(velocita);
      delay(500);
      Robot.shutdown();
      return loop();
      break;
  }
}
    
    
void movimento_servo(int x)
{
  switch (x) {
    case 0:
      servo.write(centro);  // Rimani al centro
      break;
    case 1:
      servo.write(destra); // Gira a destra
      break;
    case 2:
      servo.write(sinistra);  // Gira a sinistra
      break;
  }
}

    
    



  
