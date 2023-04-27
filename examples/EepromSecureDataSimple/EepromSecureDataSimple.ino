//
// EepromSecureData Simple Example
//
#include <Arduino.h>
#include <EepromSecureData.h>

// My dummy class
// This class must be triavially copyable, i.e. it must have a trivial copy constructor
struct MyClass {
  int a;
  int b;
  int c;
  // Constructor with parameters
  MyClass (int a, int b, int c) : a (a), b (b), c (c) {}
  // Default constructor
  MyClass() : MyClass (0, 0, 0) {}
  // Copy constructor
  MyClass (const MyClass &) = default; // This is required
  // Comparison operator
  bool  operator == (const MyClass &rhs) const {
    return a == rhs.a && b == rhs.b && c == rhs.c;
  }
  // Inequality operator
  bool  operator != (const MyClass &rhs) const {
    return ! (*this == rhs);
  }
  // Print method
  void print (const char *prefix = "", Print & out = Serial) const {
    out.print (prefix);
    out.print (a);
    out.write (' ');
    out.print (b);
    out.write (' ');
    out.println (c);
  }
};

const MyClass dv1 (1, 2, 3);
EepromSecureData<MyClass> sd1;

void setup() {

  delay (2000);
  Serial.begin (115200);
  Serial.println ("\n[EepromSecureDataSimple] Example");

  #if defined(ESP32) || defined(ESP8266)
  EEPROM.begin (4096);
  #endif

  // Load from EEPROM
  if (sd1.load (dv1)) {
    Serial.println ("Loaded from EEPROM");
  }
  else {
    Serial.println ("Loaded default");
  }
  sd1.data().print ("sd1: ");

  MyClass d2 (sd1);
  MyClass d3 (4,5,6);
  // Compare
  if (d2 == sd1) {
    Serial.println ("d2 == sd1");
  }
  else {
    Serial.println ("d2 != sd1");
  }
  if (d3 == sd1) {
    Serial.println ("d3 == sd1");
  }
  else {
    Serial.println ("d3 != sd1");
  }

  sd1 = d3;
  // Save to EEPROM
  if (sd1.save()) {
    Serial.println ("Saved to EEPROM");
  }
  else {
    Serial.println ("Save failed");
  }

}

void loop() {
  // nothing to do here
}
