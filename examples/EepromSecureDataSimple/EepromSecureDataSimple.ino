//
// EepromSecureData Simple Example 
//
// This example ...
#include <Arduino.h>
#include <EepromSecureData.h>

struct Dummy {
  int a;
  int b;
  int c;
  Dummy (int a, int b, int c) : a (a), b (b), c (c) {}
  Dummy() : Dummy (0, 0, 0) {}
  Dummy (const Dummy &) = default;
  bool  operator == (const Dummy &rhs) const {
    return a == rhs.a && b == rhs.b && c == rhs.c;
  }
  bool  operator != (const Dummy &rhs) const {
    return ! (*this == rhs);
  }

};

const Dummy dv1 (1, 2, 3);
EepromSecureData<Dummy> sd1;

void setup() {

  delay (2000);
  Serial.begin (115200);

  sd1.load(dv1);
  
}

void loop() {

}
