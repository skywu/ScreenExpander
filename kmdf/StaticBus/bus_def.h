#ifndef BUS_DEF_H
#define BUS_DEF_H

// {4d36e968-e325-11ce-bfc1-08002be10318}
// This is a system-preserved device class GUID for display adapters
DEFINE_GUID(GUID_DEV_CLASS_DISPLAY_ADAPTER,
	0x4d36e968, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define INDIRECT_DISPLAY_HARDWARE_IDS L"{4d36e968-e325-11ce-bfc1-08002be10318}\\Indirect_Disp\0"
#define INDIRECT_DISPLAY_HARDWARE_IDS_LEN sizeof (INDIRECT_DISPLAY_HARDWARE_IDS)

#define INDIRECT_DISPLAY_COMPATIBLE_IDS L"{4d36e968-e325-11ce-bfc1-08002be10318}\\Indirect_Disp_Compatible\0"
#define INDIRECT_DISPLAY_COMPATIBLE_IDS_LEN sizeof (INDIRECT_DISPLAY_COMPATIBLE_IDS)

#define KDPFX "[Riley StatBus] "

DRIVER_INITIALIZE DriverEntry;

EVT_WDF_DRIVER_DEVICE_ADD Bus_EvtDeviceAdd;

NTSTATUS
Bus_StaticEnum(
	_In_ WDFDEVICE Device
);

#endif // !BUS_DEF_H

