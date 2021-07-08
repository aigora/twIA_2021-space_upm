
#define trigF 1
#define echoF 2
#define echoI 3
#define trigI 4
#define echoD 5
#define trigD 6
#define pinIN1 7
#define pinIN2 8
#define pinENA 9
#define pinIN3 10
#define pinENB 11
#define pinIN4 12

int MotorA[3]={pinENA, pinIN1, pinIN2};
int MotorB[3]={pinENB, pinIN3, pinIN4};
int T_bucle = 300;
long distanciaF;
long distanciaI;
long distanciaD;
int x_size = 49;
int y_size = 49;
int coord[] = {0, 0};
int orientation = 0;
int coord_med[] = {0, 0};
long medirDistancia();
unsigned long Tiempo = millis();

void setup() {
  Serial.begin(9600);
  pinMode(echoD,INPUT);
  pinMode(trigD,OUTPUT);
  pinMode(echoF,INPUT);
  pinMode(trigF,OUTPUT);
  pinMode(echoI,INPUT);
  pinMode(trigI,OUTPUT);
  pinMode(pinENA,OUTPUT);
  pinMode(pinENB,OUTPUT);
  pinMode(pinIN1,OUTPUT);
  pinMode(pinIN2,OUTPUT);
  pinMode(pinIN3,OUTPUT);
  pinMode(pinIN4,OUTPUT);
  while(!Serial) { ; }
}

void loop() {
  
  Tiempo = millis();
  
  if(millis()-Tiempo>=T_bucle){
    
    distanciaF=medirDistancia(echoF, trigF);
    switch (orientation) {
          case 0:
            coord_med[0] = coord[0]+1;
            coord_med[1] = coord[1];
          break;
          case 1:
            coord_med[0] = coord[0];
            coord_med[1] = coord[1]+1;
          break;
          case 2:
            coord_med[0] = coord[0]-1;
            coord_med[1] = coord[1];
          break;
          case 3:
            coord_med[0] = coord[0];
            coord_med[1] = coord[1]-1;
          break;
          default:
            Serial.println("Error en or.");
          break;
      }
      if (distanciaF > 10) {
        Serial.println('0');
        Serial.write(coord_med[0]);
        Serial.write(coord_med[1]);
      } 
      else if (distanciaF <= 10) {
        Serial.println('X');
        Serial.write(coord_med[0]);
        Serial.write(coord_med[1]);
      }
      
      distanciaI=medirDistancia(echoI, trigI);
      switch (orientation) {
          case 0:
            coord_med[0] = coord[0];
            coord_med[1] = coord[1]+1;
          break;
          case 1:
            coord_med[0] = coord[0]-1;
            coord_med[1] = coord[1];
          break;
          case 2:
            coord_med[0] = coord[0];
            coord_med[1] = coord[1]-1;
          break;
          case 3:
            coord_med[0] = coord[0]+1;
            coord_med[1] = coord[1];
          break;
          default:
            Serial.println("Error en or.");
          break;
      }
      if (distanciaI > 10) {
        Serial.println('0');
        Serial.write(coord_med[0]);
        Serial.write(coord_med[1]);
      } 
      else if (distanciaI <= 10) {
        Serial.println('X');
        Serial.write(coord_med[0]);
        Serial.write(coord_med[1]);
      }

      distanciaD=medirDistancia(echoD, trigD);
      switch (orientation) {
          case 0:
            coord_med[0] = coord[0];
            coord_med[1] = coord[1]-1;
          break;
          case 1:
            coord_med[0] = coord[0]+1;
            coord_med[1] = coord[1];
          break;
          case 2:
            coord_med[0] = coord[0];
            coord_med[1] = coord[1]+1;
          break;
          case 3:
            coord_med[0] = coord[0]-1;
            coord_med[1] = coord[1];
          break;
          default:
            Serial.println("Error en or.");
          break;
      }
      if (distanciaD > 10) {
        Serial.println('0');
        Serial.write(coord_med[0]);
        Serial.write(coord_med[1]);
      } 
      else if (distanciaD <= 10) {
        Serial.println('X');
        Serial.write(coord_med[0]);
        Serial.write(coord_med[1]);
      }
      /*if (distanciaF > 10) {
        av_cuadrado();
        if((coord[0]>x_size)||(coord[1]>y_size)){
          re_cuadrado();
          if(distanciaD > 10){
            //girar derecha (incluyendo cambio de orientación)
          }
          else if(distanciaI > 10){
           //girar izquierda (incluyendo cambio de orientación)
          }
        }

        if((coord[0]<0)||(coord[1]<0)){
          re_cuadrado();
          if(distanciaI > 10){
           //girar izquierda (incluyendo cambio de orientación)
          }
          else if(distanciaD > 10){
            //girar derecha (incluyendo cambio de orientación)
          }
        }
      } 
      else if (distanciaD <= 10) {
        if(distanciaI <= 10){
          //secuencia de marcha atrás 
          while((distanciaI<=10) && (distanciaD <= 10)){
            re_cuadrado();
          }
          if(distanciaD > 10){
            //girar derecha (incluyendo cambio de orientación)
          }
          else if(distanciaI > 10){
            //girar izquierda (incluyendo cambio de orientación)
          }  
        }
        else{
            //girar izquierda (incluyendo cambio de orientación)
        }
      }
      else if (distanciaI <= 10){
          //girar derecha (incluyendo cambio de orientación)
      }*/

      if (distanciaI > 10) {
        //girar izquierda (incluyendo cambio de orientación)
        av_cuadrado;
        if((coord[0]>x_size)||(coord[1]>y_size)){
          re_cuadrado();
          //girar derecha (incluyendo cambio de orientación)
          if(distanciaD > 10){
            //girar derecha (incluyendo cambio de orientación)
          }
          else if(distanciaI > 10){
           //girar izquierda (incluyendo cambio de orientación)
          }
        }

        if((coord[0]<0)||(coord[1]<0)){
          re_cuadrado();
          if(distanciaI > 10){
           //girar izquierda (incluyendo cambio de orientación)
          }
          else if(distanciaD > 10){
            //girar derecha (incluyendo cambio de orientación)
          }
        }
      }else if (distanciaF > 10) {
        av_cuadrado();
        if((coord[0]>x_size)||(coord[1]>y_size)){
          re_cuadrado();
          if(distanciaD > 10){
            //girar derecha (incluyendo cambio de orientación)
          }
          else if(distanciaI > 10){
           //girar izquierda (incluyendo cambio de orientación)
          }
        }

        if((coord[0]<0)||(coord[1]<0)){
          re_cuadrado();
          if(distanciaI > 10){
           //girar izquierda (incluyendo cambio de orientación)
          }
          else if(distanciaD > 10){
            //girar derecha (incluyendo cambio de orientación)
          }
        }
      }else if (distanciaD > 10) {
        //girar derecha (incluyendo cambio de orientación)
        av_cuadrado;
        if((coord[0]>x_size)||(coord[1]>y_size)){
          re_cuadrado();
          //girar derecha (incluyendo cambio de orientación)
          if(distanciaD > 10){
            //girar derecha (incluyendo cambio de orientación)
          }
          else if(distanciaI > 10){
           //girar izquierda (incluyendo cambio de orientación)
          }
        }

        if((coord[0]<0)||(coord[1]<0)){
          re_cuadrado();
          if(distanciaI > 10){
           //girar izquierda (incluyendo cambio de orientación)
          }
          else if(distanciaD > 10){
            //girar derecha (incluyendo cambio de orientación)
          }
        }
      }else{
        //secuencia de marcha atrás 
          while((distanciaI<=10) && (distanciaD <= 10)){
            re_cuadrado();
          }
          if(distanciaD > 10){
            //girar derecha (incluyendo cambio de orientación)
          }
          else if(distanciaI > 10){
            //girar izquierda (incluyendo cambio de orientación)
          }
      }
  }
}
long medirDistancia(int echo, int trig) {
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

void av_cuadrado(){
  Tiempo = millis();
  motorDelante(MotorA, 200);
  motorDelante(MotorB, 200);
   if(millis()-Tiempo>=T_bucle){
      motorParar(MotorA);
      motorParar(MotorB);
   }
   switch (orientation) {
          case 0:
            coord[0] = coord[0]+1;
            coord[1] = coord[1];
          break;
          case 1:
            coord[0] = coord[0];
            coord[1] = coord[1]+1;
          break;
          case 2:
            coord[0] = coord[0]-1;
            coord[1] = coord[1];
          break;
          case 3:
            coord[0] = coord[0];
            coord[1] = coord[1]-1;
          break;
          default:
            Serial.println("Error en or.");
          break;
      }
}
void re_cuadrado(){
  Tiempo = millis();
  motorAtras(MotorA, 200);
  motorAtras(MotorB, 200);
   if(millis()-Tiempo>=T_bucle){
      motorParar(MotorA);
      motorParar(MotorB);
   }
   switch (orientation) {
          case 0:
            coord[0] = coord[0]-1;
            coord[1] = coord[1];
          break;
          case 1:
            coord[0] = coord[0];
            coord[1] = coord[1]-1;
          break;
          case 2:
            coord[0] = coord[0]+1;
            coord[1] = coord[1];
          break;
          case 3:
            coord[0] = coord[0];
            coord[1] = coord[1]+1;
          break;
          default:
            Serial.println("Error en or.");
          break;
      }
}
