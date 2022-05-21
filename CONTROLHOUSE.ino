//Import
#include <Servo.h> 
Servo servo1;//Servo motor

//Declaración de Variables
int leds[5];
int i=1;

//luces<-------------------------
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
int led6 = 7;


//Sensor ultrasonico<------------
int TRIG = 10;
int ECO = 9;
int DURACION;
int DISTANCIA;

//Servo Motor<-----------------
int PINSERVO=11;
int PULSOMIN=600;
int PULSOMAX=2450;

//Sensor de Sonido<-----------
int sensor =12;
int a=0; //Contador de aplausos
int b=0; //Salida del bucle
int lecturamicrofono=0;

//sistema de riego
int riego =13;

//Aire acondicionado
int aire = 8;

int estado = 0; //Recibe de App
int on = 1;

void setup()
{
  Serial.begin(9600);

  //Pines<---------------------
  //Luces
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
 
  //Sensor Ultrasónico
  pinMode(TRIG, OUTPUT);
  pinMode(ECO, INPUT);

  //Servo Motor
  servo1.attach(PINSERVO, PULSOMIN, PULSOMAX); //numero pin

  //Sensor de Sonido
  pinMode(sensor, INPUT);

  //Sistema de riego
  pinMode(riego, OUTPUT);

  //Aire Acondicionado
  pinMode(aire, OUTPUT);
  
}

void loop()
{
  if(on == 1){
      servo1.write(0);
      delay(1000);
      on--;
    }
  if( Serial.available()>0)
  {
    estado = Serial.read();
  }
  switch(estado)
  {

    //<------------------Habitacion 1------------------------------------------------------->
    case 'a':
    digitalWrite(led1, HIGH);
    break;
    case 'b':
    digitalWrite(led1, LOW);
    break;

    //<------------------Habitacion 2-------------------------------------------------------->
    case 'c':
    digitalWrite(led2, HIGH);
    break;
    case 'd':
    digitalWrite(led2, LOW);
    break;

    //<------------------Habitacion 3-------------------------------------------------------->
    case 'e':
    digitalWrite(led3, HIGH);
    break;
    case 'f':
    digitalWrite(led3, LOW);
    break;

    //<------------------Habitacion 4-------------------------------------------------------->
    case 'g':
    digitalWrite(led4, HIGH);
    break;
    case 'h':
    digitalWrite(led4, LOW);
    break;

    //<------------------Habitacion 5-------------------------------------------------------->
    case 'i':
    digitalWrite(led5, HIGH);
    break;
    case 'j':
    digitalWrite(led5, LOW);
    break;

    //<------------------Fachada--------------------------------------------------------------->
    case 'k':
    digitalWrite(led6, HIGH);
    break;
    case 'l':
    digitalWrite(led6, LOW);
    break;

    //<------------------Ventilacion-------------------------------------------------------->
    case 'm':
    digitalWrite(led2, HIGH);
    break;
    case 'n':
    digitalWrite(led2, LOW);
    break;

    //<------------------Encender o Apagar Todas las luces Disponibles--------------------->

    case 'o': //Prender
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
    break;

    case 'p': //Apagar
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
    break;

    //<------------------Sensor Ultrasonico Cochera-------------------------------------->
    case 'q': //Habilitar uso de sensor
    digitalWrite(TRIG, HIGH); //Emitimos un pulso
    delay(1);
    digitalWrite(TRIG, LOW);
    DURACION = pulseIn(ECO, HIGH); //Devolver un tiempo de rebote
    DISTANCIA = DURACION / 58.2; // Distancia del objeto mas cercano
    Serial.println(DISTANCIA);
    delay(200);
  
    if(DISTANCIA <=10 && DISTANCIA >= 0){ //10 centimetros
    digitalWrite(led1, HIGH);
    }
    break;
    
    case 'r': //Desabilitar uso de sensor
    digitalWrite(led1, LOW);
    digitalWrite(TRIG, LOW);
    break;

    //<------------------Puerta-------------------------------------->
    case 's': //Encender
      delay(1000);
      servo1.write(100);
      delay(1000);

    break;

    case 't':
      delay(1000);
      servo1.write(0);
      delay(1000);
    break;

    //<------------------Sensor de Sonido-------------------------------------->
    case 'u':
      lecturamicrofono= digitalRead(sensor);
      if(lecturamicrofono==HIGH){
        a=a+1;
        b=0;
        delay(200);
        }
      if(a==1 && b==0){
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, HIGH);
        digitalWrite(led5, HIGH);
        digitalWrite(led6, HIGH);
        }
      if(a==2){
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        digitalWrite(led5, LOW);
        digitalWrite(led6, LOW);
        a=0;
        }
    break;
    
    case 'v':
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        digitalWrite(led5, LOW);
        digitalWrite(led6, LOW);
        lecturamicrofono==LOW;
    break;

    //<------------------Sistema de Riego-------------------------------------->
    case 'w': //Encender
    digitalWrite(riego, HIGH);
    break;

    case 'x': //apagar
    digitalWrite(riego, LOW);
    break;

    //<------------------Aire Acondicionado-------------------------------------->
    case 'y': //Encender
    digitalWrite(aire, HIGH);
    break;

    case 'z': //apagar
    digitalWrite(aire, LOW);
    break;
  }
}
