#include "hidmouserptparser.h"


HIDMouseReportParser::HIDMouseReportParser(void *) : previousButtonsState(0) {};

void HIDMouseReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) { 
	for (uint16_t buttonId = 1; buttonId <= 16; buttonId <<= 1) {
		if (buf[0] & buttonId) {
			if (!(previousButtonsState & buttonId)) {
				onButtonDown(buttonId);
			}
		} else {
			if (previousButtonsState & buttonId) {
				onButtonUp(buttonId);
			}
		}
	}
	previousButtonsState = buf[0];

	int8_t xMovement = buf[1];
	int8_t yMovement = buf[3];
	int8_t scrollValue = buf[5];
	int8_t tiltValue = buf[6];

	if (xMovement > 126) xMovement -= 255;
	if (yMovement > 126) yMovement -= 255;

	if (xMovement != 0 || yMovement != 0 || scrollValue != 0)
		onMouseMove(xMovement, yMovement, scrollValue);
	
	if (tiltValue != 0)
		onTiltPress(tiltValue);
}
