#include <obs-module.h>

#include "hidapi.h"
#include "XKeysDevice.h"

#include <obs-frontend-api.h>

XKeysDevice *xkeysDevice;

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("xkeys", "en-US")
MODULE_EXPORT const char *obs_module_description(void)
{
	return "XKeys device support";
}

void frontend_event_callback(enum obs_frontend_event event, void *private_data)
{
	switch (event) {
		case OBS_FRONTEND_EVENT_STREAMING_STARTED:
			xkeysDevice->TurnOnLed(14);
			break;
		case OBS_FRONTEND_EVENT_STREAMING_STOPPED:
			xkeysDevice->TurnOffLed(14);
			break;
		case OBS_FRONTEND_EVENT_RECORDING_STARTED:
			xkeysDevice->TurnOnLed(15);
			break;
		case OBS_FRONTEND_EVENT_RECORDING_STOPPED:
			xkeysDevice->TurnOffLed(15);
			break;
	}
}

bool obs_module_load(void)
{

	int res = hid_init();

	hid_device_info *device = hid_enumerate(0x05f3, 0);

	while(device != nullptr)
	{
		blog(LOG_INFO, "hiddevice %ls %04X", device->product_string, device->product_id);
		blog(LOG_INFO, "hiddevice %s", device->path);
		blog(LOG_INFO, "hiddevice %d", device->usage);

		if (device->usage == 1 && device->usage_page == 0xc) {
			hid_device *handle = hid_open_path(device->path);
			xkeysDevice = new XKeysDevice(handle);
			xkeysDevice->FlashBacklight(3);
			break;
		}

		device = device->next;
	}

	hid_free_enumeration(device);

	//hid_set_nonblocking(handle, 1);


	obs_frontend_add_event_callback(frontend_event_callback, nullptr);

	return true;
}


void obs_module_unload(void)
{
	hid_exit();
}