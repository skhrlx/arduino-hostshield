#if !defined(__HIDMOUSERPTPARSER_H__)

#define __HIDMOUSERPTPARSER_H__

#include <usbhid.h>

#define MOUSE_LEFT 		1
#define MOUSE_RIGHT 	2
#define MOUSE_MIDDLE 	4
#define MOUSE_XB1 	  8
#define MOUSE_XB2 	  16

#define CMD_JUMP   1  // No arguments
#define CMD_AIM    2  // x, y -> how much to move mouse to in X and Y axis
#define CMD_MDOWN  3  // n - number of NOT dormant enemies (hp, weapon, position)
#define CMD_MUP    4
#define CMD_CLEFT  5
#define CMD_CRIGHT 6
#define CMD_W      7
#define CMD_S      8

void onButtonUp(uint16_t buttonId) __attribute__((weak));
void onButtonDown(uint16_t buttonId) __attribute__((weak));
void onTiltPress(int8_t tiltValue) __attribute__((weak));
void onMouseMove(int8_t xMovement, int8_t yMovement, int8_t scrollValue) __attribute__((weak));

class HIDMouseReportParser : public HIDReportParser {
	uint8_t previousButtonsState;
public:
	HIDMouseReportParser(void *);
	virtual void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

#endif//__HIDMOUSERPTPARSER_H__
