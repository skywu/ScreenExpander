#pragma once

#include "pch.h"

EVT_WDF_DRIVER_DEVICE_ADD Evt_IddDeviceAdd;

EVT_WDF_DEVICE_D0_ENTRY Evt_IddDeviceD0Entry;

EVT_IDD_CX_ADAPTER_INIT_FINISHED Evt_IddAdapterInitFinished;
EVT_IDD_CX_ADAPTER_COMMIT_MODES Evt_IddAdapterCommitModes;

EVT_IDD_CX_PARSE_MONITOR_DESCRIPTION Evt_IddParseMonitorDescription;


#if IDDCX_VERSION_MINOR >= 4
EVT_IDD_CX_MONITOR_GET_PHYSICAL_SIZE Evt_IddMonitorGetPhysicalSize;
#endif

EVT_IDD_CX_MONITOR_GET_DEFAULT_DESCRIPTION_MODES Evt_IddMonitorGetDefaultModes;
EVT_IDD_CX_MONITOR_QUERY_TARGET_MODES Evt_IddMonitorQueryModes;

EVT_IDD_CX_MONITOR_ASSIGN_SWAPCHAIN Evt_IddMonitorAssignSwapChain;
EVT_IDD_CX_MONITOR_UNASSIGN_SWAPCHAIN Evt_IddMonitorUnassignSwapChain;

