#include "XKeysDevice.h"

XKeysDevice::XKeysDevice(hid_device *device) {
	this->device = device;

	unsigned char buf[36];

	buf[0] = 0x0;
	buf[1] = 214;
	hid_write(this->device, buf, 36);

	int res = hid_read(this->device, buf, 33);

	numColumns = buf[7];
	printf("columns: %d\n",numColumns);
	printf("rows: %d\n", buf[8]);

	previousButtonStates = new unsigned char[numColumns];

	new std::thread(&XKeysDevice::HidRead, this);
}

void XKeysDevice::HidRead() {
	unsigned char buf[36];
	while (true) {
		int res = hid_read(this->device, buf, 33);

		switch (buf[1]) {
			case 214: //descriptor

				break;
			case 0: //general
			case 1:
				printf("unit id: %d\n", buf[0]);
				printf("data type: %d\n", buf[1]);

				for (int i=0; i<numColumns; i++) {
					unsigned char changes = previousButtonStates[i] ^ buf[i+2];

					unsigned char downs = changes & buf[i+2];

					printf("downs: %d\n", downs);

					unsigned char ups = changes & (~buf[i+2]);

					printf("ups: %d\n", ups);

					previousButtonStates[i] = buf[i+2];
				}
				break;
		}
	}
}

void XKeysDevice::SetBacklightIntensity(unsigned char intensityBank1, unsigned char intensityBank2)
{
	unsigned char buf[36];

	buf[0] = 0x0;
	buf[1] = 187;
	buf[2] = intensityBank1;
	buf[3] = intensityBank1;
	hid_write(this->device, buf, 36);
}

void XKeysDevice::ToggleBacklight()
{
	unsigned char buf[36];

	buf[0] = 0x0;
	buf[1] = 184;
	hid_write(this->device, buf, 36);
}

void XKeysDevice::SetFlashRate(unsigned char flashrate)
{
	unsigned char buf[36];

	buf[0] = 0x0;
	buf[1] = 180;
	buf[2] = flashrate;
	hid_write(this->device, buf, 36);
}

void XKeysDevice::TurnOffLed(unsigned char ledNumber)
{
	unsigned char buf[36];
	buf[0] = 0x0;
	buf[1] = 186;
	buf[2] = ledNumber;
	buf[3] = 0;
	hid_write(this->device, buf, 36);
}

void XKeysDevice::TurnOnLed(unsigned char ledNumber)
{
	unsigned char buf[36];
	buf[0] = 0x0;
	buf[1] = 186;
	buf[2] = ledNumber;
	buf[3] = 1;
	hid_write(this->device, buf, 36);
}

void XKeysDevice::FlashLed(unsigned char ledNumber)
{
	unsigned char buf[36];
	buf[0] = 0x0;
	buf[1] = 186;
	buf[2] = ledNumber;
	buf[3] = 2;
	hid_write(this->device, buf, 36);
}

void XKeysDevice::TurnOnBacklight(unsigned char keyNumber)
{
	unsigned char buf[36];
	buf[0] = 0x0;
	buf[1] = 181;
	buf[2] = keyNumber;
	buf[3] = 1;
	hid_write(this->device, buf, 36);
}

void XKeysDevice::TurnOffBacklight(unsigned char keyNumber)
{
	unsigned char buf[36];
	buf[0] = 0x0;
	buf[1] = 181;
	buf[2] = keyNumber;
	buf[3] = 0;
	hid_write(this->device, buf, 36);
}

void XKeysDevice::FlashBacklight(unsigned char keyNumber)
{
	unsigned char buf[36];
	buf[0] = 0x0;
	buf[1] = 181;
	buf[2] = keyNumber;
	buf[3] = 2;
	hid_write(this->device, buf, 36);
}