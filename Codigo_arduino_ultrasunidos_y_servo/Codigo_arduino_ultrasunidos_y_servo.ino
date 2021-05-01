#include <Servo.h>
Servo upm;
#define trig 7
#define echo 6
int X = 0;
long distancia;

long medirDistancia();



void setup() {
Serial.begin(9600);
upm.attach(2);
pinMode(echo,INPUT);
pinMode(trig,OUTPUT);
while(!Serial) { ; }
}

void loop() {
distancia=medirDistancia();
Serial.print ("distancia = ");
Serial.println(distancia);
int position_X = analogRead(X);
int angulo = map(position_X, 0, 1023, 0, 180);
Serial.print ("angulo = ");
Serial.println(angulo);
upm.write(angulo);
delay(100);



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



distanceCm = duration /(29.1*2); //convertimos la distancia en cm. No olvidemos dividirlo con 2 tambien.(1s/340m=0.00291s/m=)
return distanceCm;
}
