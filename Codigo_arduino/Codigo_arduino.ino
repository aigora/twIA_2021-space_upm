#include <Servo.h>
Servo upm;

#define servo 2
#define SensIRD 3
#define SensIRI 4
#define echo 5
#define trig 6
#define pinIN1 7
#define pinIN2 8
#define pinENA 9
#define pinIN3 10
#define pinENB 11
#define pinIN4 12

int MotorA[3]={pinENA, pinIN1, pinIN2};
int MotorB[3]={pinENB, pinIN3, pinIN4};
<<<<<<< Updated upstream:Codigo_arduino/Codigo_arduino.ino
int T_bucle = 100;
=======
<<<<<<< Updated upstream:Codigo_arduino_ultrasunidos_y_servo/Codigo_arduino_ultrasunidos_y_servo.ino
<<<<<<< Updated upstream:Codigo_arduino_ultrasunidos_y_servo/Codigo_arduino_ultrasunidos_y_servo.ino
int X = 0;
int T_bucle = 100;
=======
int T_bucle = 300;
>>>>>>> Stashed changes:Codigo_arduino/Codigo_arduino.ino
=======
int T_bucle = 300;
>>>>>>> Stashed changes:Codigo_arduino/Codigo_arduino.ino
>>>>>>> Stashed changes:Codigo_arduino_ultrasunidos_y_servo/Codigo_arduino_ultrasunidos_y_servo.ino
int IR_signalD;
int IR_signalI;
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
  char inp=0;
  if(millis()-Tiempo>=T_bucle){
    if( Serial.available()> 0) {
      inp=Serial.read();
      Serial.print(inp);
    }
    IR_signalD = digitalRead(SensIRD);
    IR_signalI = digitalRead(SensIRI);
    if(IR_signalD==HIGH){
      Serial.println("ZONA NEGRA DERECHA");
    }
    else{
<<<<<<< Updated upstream:Codigo_arduino/Codigo_arduino.ino
      Serial.println("ZONA BLANCA DERECHA");
=======
      Serial.println("ZONA BLANCA DER");
<<<<<<< Updated upstream:Codigo_arduino_ultrasunidos_y_servo/Codigo_arduino_ultrasunidos_y_servo.ino
>>>>>>> Stashed changes:Codigo_arduino/Codigo_arduino.ino
=======
>>>>>>> Stashed changes:Codigo_arduino/Codigo_arduino.ino
>>>>>>> Stashed changes:Codigo_arduino_ultrasunidos_y_servo/Codigo_arduino_ultrasunidos_y_servo.ino
      if (inp=='d'){
        inp='a';  
      }
    }
    if(IR_signalI==HIGH){
      Serial.println("ZONA NEGRA IZQUIERDA");
    }
    else{
<<<<<<< Updated upstream:Codigo_arduino/Codigo_arduino.ino
      Serial.println("ZONA BLANCA IZQUIERDAD");
=======
      Serial.println("ZONA BLANCA IZQ");
<<<<<<< Updated upstream:Codigo_arduino_ultrasunidos_y_servo/Codigo_arduino_ultrasunidos_y_servo.ino
>>>>>>> Stashed changes:Codigo_arduino/Codigo_arduino.ino
=======
>>>>>>> Stashed changes:Codigo_arduino/Codigo_arduino.ino
>>>>>>> Stashed changes:Codigo_arduino_ultrasunidos_y_servo/Codigo_arduino_ultrasunidos_y_servo.ino
      if (inp=='a'){
        inp='w';  
      }
    }
    distancia=medirDistancia();
    if (inp=='w'){
      if (distancia >= 25) {
        motorDelante(MotorA, 200);
        motorDelante(MotorB, 200);
      } 
      else if (10 <= distancia && distancia < 25) {
        motorDelante(MotorA, 125);
        motorDelante(MotorB, 125);
      } 
      else if (distancia <= 10) {
        motorParar(MotorA);
        motorParar(MotorB);
      }
    }
    else if (inp=='s'){
      motorAtras(MotorA, 200);
      motorAtras(MotorB, 200);
    }
    else if(inp=='a'||inp=='d'){
        girar(inp);
    }
<<<<<<< Updated upstream:Codigo_arduino/Codigo_arduino.ino
=======
<<<<<<< Updated upstream:Codigo_arduino_ultrasunidos_y_servo/Codigo_arduino_ultrasunidos_y_servo.ino
>>>>>>> Stashed changes:Codigo_arduino/Codigo_arduino.ino
=======
    else if(inp==' '){
      motorParar(MotorA);
      motorParar(MotorB);
    }
>>>>>>> Stashed changes:Codigo_arduino/Codigo_arduino.ino
>>>>>>> Stashed changes:Codigo_arduino_ultrasunidos_y_servo/Codigo_arduino_ultrasunidos_y_servo.ino
    Serial.println(distancia);
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
void girar(char dir){
    if (dir=='a'){
      upm.write(135);
    }
    else if(dir=='d'){
      upm.write(45);
    }
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
void motorParar(int Motor[3]){
  digitalWrite(Motor[1], LOW);
  digitalWrite(Motor[2], LOW);
  analogWrite(Motor[0], 0);
}
