#pragma once

#include <thread>

#include <hidapi.h>

class XKeysDevice{

public:
	XKeysDevice(hid_device* device);

	void SetBacklightIntensity(unsigned char intensityBank1, unsigned char intensityBank2);
	void ToggleBacklight();
	void SetFlashRate(unsigned char flashRate);
	void TurnOffLed(unsigned char ledNumber);
	void TurnOnLed(unsigned char ledNumber);
	void FlashLed(unsigned char ledNumber);
	void TurnOnBacklight(unsigned char keyNumber);
	void TurnOffBacklight(unsigned char keyNumber);
	void FlashBacklight(unsigned char keyNumber);

private:
	hid_device *device;
	int numColumns;
	unsigned char* previousButtonStates;

	void HidRead();
};
