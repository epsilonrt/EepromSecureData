//
// Unit Test for the class EepromBase
//
#include <Arduino.h>
#include <unity.h>
#include <EepromBase.h>

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
  Dummy() : a(0), b(0), c(0) {
    EepromBase::counter += sizeof (Dummy);
  }
  Dummy(const Dummy &) = default;
 };

void test_counter_default (void) {

  TEST_ASSERT_EQUAL (EepromBase::counter, 0);
}

void test_counter1 (void) {
  Dummy d1;

  TEST_ASSERT_EQUAL (EepromBase::counter, sizeof(Dummy));
}

void test_counter2 (void) {
  Dummy d2;

  TEST_ASSERT_EQUAL (EepromBase::counter, sizeof(Dummy) * 2);
}

void setup() {

  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  // delay (2000);

  UNITY_BEGIN();    // IMPORTANT LINE!
}

bool done = false;

void loop() {

  if (!done) {

    RUN_TEST (test_counter_default);
    RUN_TEST (test_counter1);
    RUN_TEST (test_counter2);

    UNITY_END(); // stop unit testing
    done = true;
  }
}
