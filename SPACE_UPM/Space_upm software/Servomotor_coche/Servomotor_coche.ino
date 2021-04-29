#include <Servo.h>
Servo upm;

int X = 0;

void setup() {
  upm.attach(2);// Se asocia el servo al pin 2
  Serial.begin(9600);
  while(!Serial) { ; }
}

void loop () {
  int position_X = analogRead(X);
  int angulo = map(position_X, 0, 1023, 0, 180);
  Serial.print ("angulo = ");
  Serial.println(angulo);
  upm.write(angulo);
  delay(10);
}
