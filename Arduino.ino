#include <Mouse.h>
#include <Keyboard.h>
#include <hiduniversal.h>
#include "hidmouserptparser.h"

USB Usb;
HIDUniversal Hid(&Usb);
HIDMouseReportParser Mou(nullptr);

void setup() {
  Mouse.begin();
  Serial.begin(128000);
  Usb.Init();
  Hid.SetReportParser(0, &Mou);
}

void loop() {
  Usb.Task();
}

void onButtonDown(uint16_t buttonId) {
  Mouse.press(buttonId);
}

void onButtonUp(uint16_t buttonId) {
  Mouse.release(buttonId);
}

void onTiltPress(int8_t tiltValue) {
}

void onMouseMove(int8_t xMovement, int8_t yMovement, int8_t scrollValue) {
  Mouse.move(xMovement, yMovement, scrollValue);
}
