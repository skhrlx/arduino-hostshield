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
    if (Serial.available()) {
    int cmd = Serial.read();
    switch (cmd) {
      case CMD_JUMP: {
        Mouse.move(0, 0, +1);
      }
      break;
      case CMD_MDOWN: {
        Mouse.press(MOUSE_LEFT);
      }
      break;
      case CMD_MUP: {
        Mouse.release(MOUSE_LEFT);
      }
      break;
      case CMD_AIM: {
        char delta_x = static_cast<char>(Serial.read());
        char delta_y = static_cast<char>(Serial.read());
        char delta_z = static_cast<char>(Serial.read());
        Mouse.move(delta_x, delta_y, delta_z);
        }
      break;
      case CMD_CLEFT: {
        Mouse.click(MOUSE_LEFT);
      }
      break;
      case CMD_CRIGHT: {
        Mouse.click(MOUSE_RIGHT);
      }
      break;
      case CMD_W: {
        Keyboard.write('w');
      }
      break;
      case CMD_S: {
        Keyboard.write('s');
      }
      break;
    }
  }
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
