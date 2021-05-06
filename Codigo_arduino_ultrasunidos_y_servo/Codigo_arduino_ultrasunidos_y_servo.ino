#include <Servo.h>
Servo upm;

#define servo 2
#define trig 7
#define echo 6
#define SensIR 3

int X = 0;
int T_bucle = 100;
int IR_signal;
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
pinMode(SensIR,INPUT);
while(!Serial) { ; }
}

void loop() {
  
  if(millis()-Tiempo>=T_bucle){
    IR_signal = digitalRead(SensIR);
    if(IR_signal==1){
      Serial.println("No IR");
    }
    else{
      Serial.println("IR detectados");
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
