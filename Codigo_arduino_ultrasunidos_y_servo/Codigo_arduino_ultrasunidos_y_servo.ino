#include <Servo.h>
Servo upm;

#define trig 7
#define echo 6

int X = 0;
int T_bucle = 100;
long distancia;
long medirDistancia();
unsigned long Tiempo = millis();

void setup() {
Serial.begin(9600);
upm.attach(2);
pinMode(echo,INPUT);
pinMode(trig,OUTPUT);
while(!Serial) { ; }
}

void loop() {
  
  if(millis()-Tiempo>=T_bucle){
    distancia=medirDistancia();
    int position_X = analogRead(X);
    int angulo = map(position_X, 0, 1023, 0, 180);
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
