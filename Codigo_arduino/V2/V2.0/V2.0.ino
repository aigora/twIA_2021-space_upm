
#define trigF 2
#define echoF 3
#define echoI 4
#define trigI 5
#define echoD 6
#define trigD 7
#define pinIN1 9
#define pinIN2 10
#define pinIN3 11
#define pinIN4 12

int MotorA[2]={pinIN1, pinIN2};
int MotorB[2]={pinIN3, pinIN4};
int T_bucle = 300;
int T_mov = 400;
int T_giro = 600;
long distanciaF;
long distanciaI;
long distanciaD;
int x_size = 49;
int y_size = 49;
int coord[2] = {0, 0};
int orientation = 0;
int coord_med[2] = {0, 0};
long medirDistancia();
unsigned long Tiempo;

void setup() {

  Tiempo = millis();
  
  Serial.begin(9600);
  pinMode(echoD,INPUT);
  pinMode(trigD,OUTPUT);
  pinMode(echoF,INPUT);
  pinMode(trigF,OUTPUT);
  pinMode(echoI,INPUT);
  pinMode(trigI,OUTPUT);
  pinMode(pinIN1,OUTPUT);
  pinMode(pinIN2,OUTPUT);
  pinMode(pinIN3,OUTPUT);
  pinMode(pinIN4,OUTPUT);
  
}

void loop() {
  
  if(millis()-Tiempo>=T_bucle){
    
    distanciaF=medirDistancia(echoF, trigF);
    switch (orientation) {
          case 0:
            coord_med[0] = coord[0]+1;
            coord_med[1] = coord[1];
          break;
          case 1:
            coord_med[0] = coord[0];
            coord_med[1] = coord[1]-1;
          break;
          case 2:
            coord_med[0] = coord[0]-1;
            coord_med[1] = coord[1];
          break;
          case 3:
            coord_med[0] = coord[0];
            coord_med[1] = coord[1]+1;
          break;
          default:
            Serial.println("Error en or.");
          break;
      }
      if (distanciaF > 30) {
        Serial.print('0');
        Serial.write((uint8_t*)coord_med, sizeof(coord_med));
      } 
      else if (distanciaF <= 30) {
        Serial.print('X');
        Serial.write((uint8_t*)coord_med, sizeof(coord_med));
      }
      delay(1500);
      distanciaI=medirDistancia(echoI, trigI);
      switch (orientation) {
          case 0:
            coord_med[0] = coord[0];
            coord_med[1] = coord[1]-1;
          break;
          case 1:
            coord_med[0] = coord[0]-1;
            coord_med[1] = coord[1];
          break;
          case 2:
            coord_med[0] = coord[0];
            coord_med[1] = coord[1]+1;
          break;
          case 3:
            coord_med[0] = coord[0]+1;
            coord_med[1] = coord[1];
          break;
          default:
            Serial.println("Error en or.");
          break;
      }
      if (distanciaI > 30) {
        Serial.print('0');
        Serial.write((uint8_t*)coord_med, sizeof(coord_med));
      } 
      else if (distanciaI <= 30) {
        Serial.print('X');
        Serial.write((uint8_t*)coord_med, sizeof(coord_med));
      }
      delay(1500);
      distanciaD=medirDistancia(echoD, trigD);
      switch (orientation) {
          case 0:
            coord_med[0] = coord[0];
            coord_med[1] = coord[1]+1;
          break;
          case 1:
            coord_med[0] = coord[0]+1;
            coord_med[1] = coord[1];
          break;
          case 2:
            coord_med[0] = coord[0];
            coord_med[1] = coord[1]-1;
          break;
          case 3:
            coord_med[0] = coord[0]-1;
            coord_med[1] = coord[1];
          break;
          default:
            Serial.println("Error en or.");
          break;
      }
      if (distanciaD > 30) {
        Serial.print('0');
        Serial.write((uint8_t*)coord_med, sizeof(coord_med));
      } 
      else if (distanciaD <= 30) {
        Serial.print('X');
        Serial.write((uint8_t*)coord_med, sizeof(coord_med));
      }
      delay(1500);
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

      if (distanciaI > 30) {
        girar_i();
        delay(500);
        av_cuadrado();
        delay(500);
        if((coord[0]>x_size)||(coord[1]>y_size)){
          re_cuadrado();
          delay(500);
          girar_d();
          delay(500);
          if(distanciaD > 30){
            girar_d();
          }
          else if(distanciaI > 30){
           girar_i();
          }
        }

        if((coord[0]<0)||(coord[1]<0)){
          re_cuadrado();
          delay(500);
          girar_d();
          delay(500);
          if(distanciaF > 30){
           av_cuadrado();
          }
          else if(distanciaD > 30){
            girar_d();
          }
        }
      }else if (distanciaF > 30) {
        av_cuadrado();
        if((coord[0]>x_size)||(coord[1]>y_size)){
          re_cuadrado();
          if(distanciaD > 30){
            girar_d();
          }
          else if(distanciaI > 30){
           girar_i();
          }
        }

        if((coord[0]<0)||(coord[1]<0)){
          re_cuadrado();
          if(distanciaD > 30){
           girar_d();
          }
          else if(distanciaI > 30){
            girar_i();
          }
        }
      }else if (distanciaD > 30) {
        girar_d();
        delay(500);
        av_cuadrado();
        delay(500);
        if((coord[0]>x_size)||(coord[1]>y_size)){
          re_cuadrado();
          delay(500);
          girar_d();
          delay(500);
          av_cuadrado();
        }

        if((coord[0]<0)||(coord[1]<0)){
          re_cuadrado();
          delay(500);
          girar_d();
          delay(500);
          av_cuadrado();
        }
      }else{
        //secuencia de marcha atrás 
          while((distanciaI<=30) && (distanciaD <= 30)){
            re_cuadrado();
            distanciaI=medirDistancia(echoI, trigI);
            distanciaD=medirDistancia(echoD, trigD);
            delay(500);
          }
          if(distanciaD > 30){
            girar_d();
            delay(500);
            av_cuadrado();
            delay(500);
          if((coord[0]>x_size)||(coord[1]>y_size)){
            re_cuadrado();
            delay(500);
            girar_d();
            delay(500);
            av_cuadrado();
          }

          if((coord[0]<0)||(coord[1]<0)){
            re_cuadrado();
            delay(500);
            girar_d();
            delay(500);
            av_cuadrado();
          }
         }
          else if(distanciaI > 30){
            girar_i();
            delay(500);
            av_cuadrado();
            delay(500);
            if((coord[0]>x_size)||(coord[1]>y_size)){
              re_cuadrado();
              delay(500);
              girar_d();
              delay(500);
              if(distanciaD > 30){
              girar_d();
              }
              else if(distanciaI > 30){
                girar_i();
            }
          }

            if((coord[0]<0)||(coord[1]<0)){
              re_cuadrado();
              delay(500);
              girar_d();
              delay(500);
              if(distanciaF > 30){
                av_cuadrado();
              }
              else if(distanciaD > 30){
                girar_d();
              }
            }
          }
      }

      Tiempo = millis();
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
void motorDelante(int Motor[2]){
  digitalWrite(Motor[0], HIGH);
  digitalWrite(Motor[1], LOW);
}
void motorAtras(int Motor[2]){
  digitalWrite(Motor[0], LOW);
  digitalWrite(Motor[1], HIGH);
}
void motorParar(int Motor[2]){
  digitalWrite(Motor[0], LOW);
  digitalWrite(Motor[1], LOW);
}

void av_cuadrado(){
  Tiempo = millis();
  motorDelante(MotorA);
  motorDelante(MotorB);
  delay(T_mov);
  motorParar(MotorA);
  motorParar(MotorB);
   switch (orientation) {
          case 0:
            coord[0] = coord[0]+1;
            coord[1] = coord[1];
          break;
          case 1:
            coord[0] = coord[0];
            coord[1] = coord[1]-1;
          break;
          case 2:
            coord[0] = coord[0]-1;
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
void re_cuadrado(){
  Tiempo = millis();
  motorAtras(MotorA);
  motorAtras(MotorB);
  delay(T_mov);
  motorParar(MotorA);
  motorParar(MotorB);
   switch (orientation) {
          case 0:
            coord[0] = coord[0]-1;
            coord[1] = coord[1];
          break;
          case 1:
            coord[0] = coord[0];
            coord[1] = coord[1]+1;
          break;
          case 2:
            coord[0] = coord[0]+1;
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

void girar_d(){
  motorDelante(MotorA);
  motorAtras(MotorB);
  delay(T_giro);
  motorParar(MotorA);
  motorParar(MotorB);
  
   switch (orientation) {
          case 0:
            orientation = 3;
          break;
          case 1:
            orientation = 0;
          break;
          case 2:
            orientation = 1;
          break;
          case 3:
            orientation = 2;
          break;
          default:
            Serial.println("Error en or.");
          break;
      }
}

void girar_i() {
  motorDelante(MotorB);
  motorAtras(MotorA);
  delay(T_giro);
  motorParar(MotorA);
  motorParar(MotorB);

   switch (orientation) {
          case 0:
            orientation = 1;
          break;
          case 1:
            orientation = 2;
          break;
          case 2:
            orientation = 3;
          break;
          case 3:
            orientation = 0;
          break;
          default:
            Serial.println("Error en or.");
          break;
      }
}
