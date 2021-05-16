#include <Servo.h>
Servo upm;

#define servo 2
#define trig 5
#define echo 4
#define SensIRD 3
#define SensIRI 12
#define pinENA 6
#define pinIN1 7
#define pinIN2 8
#define pinIN3 9
#define pinIN4 10
#define pinENB 11

int MotorA[3]={pinENA, pinIN1, pinIN2};
int MotorB[3]={pinENB, pinIN3, pinIN4};
int X = 0;
int T_bucle = 100;
int IR_signalD;
int IR_signalI;
int position_X;
int angulo;
long distancia;
long medirDistancia();
unsigned long Tiempo = millis();

void setup() {
  Serial.begin(9600);
  upm.attach(servo);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(SensIRD,INPUT);
  pinMode(SensIRI,INPUT);
  pinMode(pinENA,OUTPUT);
  pinMode(pinENB,OUTPUT);
  pinMode(pinIN1,OUTPUT);
  pinMode(pinIN2,OUTPUT);
  pinMode(pinIN3,OUTPUT);
  pinMode(pinIN4,OUTPUT);
  while(!Serial) { ; }
}

void loop() {
  
  if(millis()-Tiempo>=T_bucle){
    IR_signalD = digitalRead(SensIRD);
    IR_signalI = digitalRead(SensIRI);
    if(IR_signalD==1){
      Serial.println("Sin línea Der");
    }
    else{
      Serial.println("Línea a la der");
    }
    if(IR_signalI==1){
      Serial.println("Sin línea Izq");
    }
    else{
      Serial.println("Línea a la izq");
    }
    distancia=medirDistancia();
    position_X = analogRead(X);
    angulo = map(position_X, 0, 1023, 0, 180);
    Serial.println(distancia);
    Serial.println(angulo);
    upm.write(angulo);
  }
}
long medirDistancia() {
long duration, distanceCm; //duration es long porque pulseIN nos devuelve el tiempo en microsec.

digitalWrite(trig, LOW); //por cuestion de estabilizacion del sensor
delayMicroseconds(4);
digitalWrite(trig, HIGH); //generamos Trigger (disparo) de 10us
delayMicroseconds(10);//Tiene que estar 10us en ON
digitalWrite(trig, LOW);

duration = pulseIn(echo, HIGH); //medimos el tiempo hasta que el pulso vuelve a llegar, en microsegundos con la funcion Pulseln(), calculando el tiempo que esta ECHO en HIGH
//mientras recibe el ultrasonidos.

distanceCm = duration /(29.1*2); //convertimos la distancia en cm. No olvidemos dividirlo entre 2 también.(1s/340m=0.00291s/m)
return distanceCm;
}
void girarDer(){
  upm.write(45);  
}
void girarDer(){
  upm.write(135);  
}
void motorDelante(int Motor[3], int vel){
  digitalWrite(Motor[1], HIGH);
  digitalWrite(Motor[2], LOW);
  analogWrite(Motor[0], vel);
}
void motorAtras(int Motor[3], int vel){
  digitalWrite(Motor[1], LOW);
  digitalWrite(Motor[2], HIGH);
  analogWrite(Motor[0], vel);
}
void motorParar(int Motor[3], int vel){
  digitalWrite(Motor[1], LOW);
  digitalWrite(Motor[2], LOW);
  analogWrite(Motor[0], 0);
}
