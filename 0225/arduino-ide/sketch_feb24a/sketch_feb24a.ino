#include "Arduino.h"
#include "my_func.h"

void setup() {
  show_hello_world();
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
}