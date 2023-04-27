//
// Unit Test for the class EepromSecureData
//
#include <Arduino.h>
#include <unity.h>
#include <EepromSecureData.h>

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

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

const Dummy dv0;
const Dummy dv1 (1, 2, 3);
const Dummy dv2 (4, 5, 6);
const Dummy dv3 (7, 8, 9);

EepromSecureData<Dummy> sd1;
EepromSecureData<Dummy> sd2;
EepromSecureData<Dummy> sd3 (dv3);

void test_size (void) {

  TEST_ASSERT_EQUAL (sizeof (Dummy) + 1, sd2.size());
  TEST_ASSERT_EQUAL (sd1.size(), sd2.size());
  TEST_ASSERT_EQUAL (sd1.size() + sd2.size() + sd3.size(), EepromBase::counter);
}

void test_constructor (void) {

  TEST_ASSERT_EQUAL (0, dv0.a);
  TEST_ASSERT_EQUAL (0, dv0.b);
  TEST_ASSERT_EQUAL (0, dv0.c);
  TEST_ASSERT_EQUAL (0, sd1.data().a);
  TEST_ASSERT_EQUAL (0, sd1.data().b);
  TEST_ASSERT_EQUAL (0, sd1.data().c);
  TEST_ASSERT_EQUAL (0, sd2.data().a);
  TEST_ASSERT_EQUAL (0, sd2.data().b);
  TEST_ASSERT_EQUAL (0, sd2.data().c);
  TEST_ASSERT_EQUAL (dv3.a, sd3.data().a);
  TEST_ASSERT_EQUAL (dv3.b, sd3.data().b);
  TEST_ASSERT_EQUAL (dv3.c, sd3.data().c);
}

void test_equal_op (void) {

  TEST_ASSERT (dv0 == sd1.data());
  TEST_ASSERT (dv0 == sd1);
  TEST_ASSERT (sd1 == sd2);
}

void test_not_equal_op (void) {

  TEST_ASSERT (sd1 != sd3);
  TEST_ASSERT (sd1 != dv3);
}

void test_assignation_op (void) {

  sd1 = sd3;
  TEST_ASSERT (sd1 == sd3);
  sd1 = dv0;
  TEST_ASSERT (sd1 == sd2);
}

void test_save_load (void) {

  TEST_ASSERT_TRUE (sd1.save());
  TEST_ASSERT_TRUE (sd1.load (dv0));
}

void test_load_default (void) {

  EepromBase::counter = 0;
  EepromSecureData<int> sdi;
  TEST_ASSERT_FALSE (sdi.load (5));
  TEST_ASSERT_TRUE (sdi.load (0));
  TEST_ASSERT (5 == sdi.data());
}

void setup() {

  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay (2000);
#if defined(ESP32) || defined(ESP8266)
  EEPROM.begin(4096);
#endif
  UNITY_BEGIN();    // IMPORTANT LINE!
}

bool done = false;

void loop() {

  if (!done) {

    RUN_TEST (test_size);
    RUN_TEST (test_constructor);
    RUN_TEST (test_equal_op);
    RUN_TEST (test_not_equal_op);
    RUN_TEST (test_assignation_op);
    RUN_TEST (test_save_load);
    RUN_TEST (test_load_default);

    UNITY_END(); // stop unit testing
    done = true;
  }
}
