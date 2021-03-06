#pragma once

#include "pch.h"
#include "AsyncPipeServer.h"

namespace indirect_disp {
    class IndirectAdapter
    {
        friend struct IndirectMonitor;

    public:
        static constexpr DWORD MAX_MONITOR_CAPACITY = MAX_MONITOR_NUM;

        // Only for test purpose
        static constexpr DWORD MANUALLY_SPECIFIED_MONITOR_INFO_INDEX = 1;

        static constexpr DWORD MAX_DISPLAY_WIDTH = MAX_IMAGE_WIDTH;

        static constexpr DWORD MAX_DISPLAY_HEIGHT = MAX_IMAGE_HEIGHT;

        static constexpr DWORD MAX_DISPLAY_REFRESH_RATE_AT_MAX_RESOLUTION = 60;

        IndirectAdapter(WDFDEVICE Device);

        // Must be called explictly in the callback function specified
        // in WDF Object Attr since WDF is essentially a C environment!
        ~IndirectAdapter();

        // Called after the constructor. See the constructor.
        void IndirectAdapterFinishInit() {}

        _Must_inspect_result_
            bool NewMonitorArrives(_In_ const MONITOR_ARRIVE_ARG_IN& MonitorArriveArgIn,
                _Out_ MONITOR_ARRIVE_ARG_OUT* pMonitorArriveArgOut);

        _Must_inspect_result_
            bool MonitorDepart(_In_ const MONITOR_DEPART_ARG_IN& MonitorDepartArgIn);

        // In case of failed IddCxAdapterInitAsync
        bool IsAdapterNull() { return nullptr == m_AdapterContext.IddCxAdapterObject; }

    protected:
        struct AdapterContext {
            IDDCX_ADAPTER IddCxAdapterObject;
            IndirectAdapter* pAdaterClass;
        };

        AdapterContext m_AdapterContext;

        DWORD m_dwNumOfChildDisplay;

        // Why is a 'class' needed in front of a class type in MSVC????
        // FuckMSVC.jpg
        struct IndirectMonitor* m_pChildMonitors[MAX_MONITOR_CAPACITY];

        WDFDEVICE m_WdfDevice;

    public:
        AsyncPipeServer m_PipeServer;

        struct IndirectSampleMonitorInfo
        {
            static constexpr size_t szEdidBlock = 128;
            static constexpr size_t szModeList = 3;

            const BYTE pEdidBlock[szEdidBlock];
            const struct SampleMonitorMode {
                DWORD Width;
                DWORD Height;
                DWORD VSync;
            } pModeList[szModeList];
            const DWORD ulPreferredModeIdx;
        };

        static constexpr struct IndirectSampleMonitorInfo s_SampleMonitorInfo[] =
        {
            // Modified EDID from Dell S2719DGF
            {
                {
                    0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x10,0xAC,0xE6,0xD0,0x55,0x5A,0x4A,0x30,0x24,0x1D,0x01,
                    0x04,0xA5,0x3C,0x22,0x78,0xFB,0x6C,0xE5,0xA5,0x55,0x50,0xA0,0x23,0x0B,0x50,0x54,0x00,0x02,0x00,
                    0xD1,0xC0,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x58,0xE3,0x00,
                    0xA0,0xA0,0xA0,0x29,0x50,0x30,0x20,0x35,0x00,0x55,0x50,0x21,0x00,0x00,0x1A,0x00,0x00,0x00,0xFF,
                    0x00,0x37,0x4A,0x51,0x58,0x42,0x59,0x32,0x0A,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,
                    0x53,0x32,0x37,0x31,0x39,0x44,0x47,0x46,0x0A,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFD,0x00,0x28,
                    0x9B,0xFA,0xFA,0x40,0x01,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x2C
                },
                {
                    { 2560, 1440, 144 },
                    { 1920, 1080,  60 },
                    { 1024,  768,  60 },
                },
                0
            },
            // Modified EDID from Lenovo Y27fA
            {
                {
                    0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x30,0xAE,0xBF,0x65,0x01,0x01,0x01,0x01,0x20,0x1A,0x01,
                    0x04,0xA5,0x3C,0x22,0x78,0x3B,0xEE,0xD1,0xA5,0x55,0x48,0x9B,0x26,0x12,0x50,0x54,0x00,0x08,0x00,
                    0xA9,0xC0,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x68,0xD8,0x00,
                    0x18,0xF1,0x70,0x2D,0x80,0x58,0x2C,0x45,0x00,0x53,0x50,0x21,0x00,0x00,0x1E,0x00,0x00,0x00,0x10,
                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFD,0x00,
                    0x30,0x92,0xB4,0xB4,0x22,0x01,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,0x4C,
                    0x45,0x4E,0x20,0x59,0x32,0x37,0x66,0x41,0x0A,0x20,0x20,0x20,0x00,0x11
                },
                {
                    { 3840, 2160,  60 },
                    { 1600,  900,  60 },
                    { 1024,  768,  60 },
                },
                0
            }
        };
    };
}
