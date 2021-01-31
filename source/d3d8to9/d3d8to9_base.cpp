/**
 * Copyright (C) 2015 Patrick Mours. All rights reserved.
 * License: https://github.com/crosire/d3d8to9#license
 */

#define NO_DEFINES
#define PCH_H

 //#include "..\pch.h"
#include "d3d8to9.hpp"
#include "..\Render\CustomShaders.h"

D3DPRESENT_PARAMETERS current_params;

D3DMULTISAMPLE_TYPE DeviceMultiSampleType = D3DMULTISAMPLE_NONE;
bool CopyRenderTarget = false;
bool SetSSAA = false;
DWORD MaxAnisotropy = 0;

static const D3DFORMAT AdapterFormats[] = {
    D3DFMT_A8R8G8B8,
    D3DFMT_X8R8G8B8,
    D3DFMT_R5G6B5,
    D3DFMT_X1R5G5B5,
    D3DFMT_A1R5G5B5
};

// IDirect3D8
Direct3D8::Direct3D8(IDirect3D9* ProxyInterface) :
    ProxyInterface(ProxyInterface)
{
    D3DDISPLAYMODE pMode;

    CurrentAdapterCount = ProxyInterface->GetAdapterCount();

    if (CurrentAdapterCount > MaxAdapters)
    {
        CurrentAdapterCount = MaxAdapters;
    }

    for (UINT Adapter = 0; Adapter < CurrentAdapterCount; Adapter++)
    {
        for (D3DFORMAT Format : AdapterFormats)
        {
            const UINT ModeCount = ProxyInterface->GetAdapterModeCount(Adapter, Format);

            for (UINT Mode = 0; Mode < ModeCount; Mode++)
            {
                ProxyInterface->EnumAdapterModes(Adapter, Format, Mode, &pMode);
                CurrentAdapterModes[Adapter].push_back(pMode);
                CurrentAdapterModeCount[Adapter]++;
            }
        }
    }
}
Direct3D8::~Direct3D8()
{
}

HRESULT STDMETHODCALLTYPE Direct3D8::QueryInterface(REFIID riid, void** ppvObj)
{
    if (ppvObj == nullptr)
    {
        return E_POINTER;
    }

    if (riid == __uuidof(this) ||
        riid == __uuidof(IUnknown))
    {
        AddRef();

        *ppvObj = this;

        return S_OK;
    }

    return ProxyInterface->QueryInterface(ConvertREFIID(riid), ppvObj);
}
ULONG STDMETHODCALLTYPE Direct3D8::AddRef()
{
    return ProxyInterface->AddRef();
}
ULONG STDMETHODCALLTYPE Direct3D8::Release()
{
    const ULONG LastRefCount = ProxyInterface->Release();

    if (LastRefCount == 0)
    {
        delete this;
    }

    return LastRefCount;
}

HRESULT STDMETHODCALLTYPE Direct3D8::RegisterSoftwareDevice(void* pInitializeFunction)
{
    return ProxyInterface->RegisterSoftwareDevice(pInitializeFunction);
}
UINT STDMETHODCALLTYPE Direct3D8::GetAdapterCount()
{
    return CurrentAdapterCount;
}
HRESULT STDMETHODCALLTYPE Direct3D8::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER8* pIdentifier)
{
    if (pIdentifier == nullptr)
    {
        return D3DERR_INVALIDCALL;
    }

    D3DADAPTER_IDENTIFIER9 AdapterIndentifier;

    if ((Flags & D3DENUM_NO_WHQL_LEVEL) == 0)
    {
        Flags |= D3DENUM_WHQL_LEVEL;
    }
    else
    {
        Flags ^= D3DENUM_NO_WHQL_LEVEL;
    }

    const HRESULT hr = ProxyInterface->GetAdapterIdentifier(Adapter, Flags, &AdapterIndentifier);

    if (FAILED(hr))
    {
        return hr;
    }

    ConvertAdapterIdentifier(AdapterIndentifier, *pIdentifier);

    return D3D_OK;
}
UINT STDMETHODCALLTYPE Direct3D8::GetAdapterModeCount(UINT Adapter)
{
    return CurrentAdapterModeCount[Adapter];
}
HRESULT STDMETHODCALLTYPE Direct3D8::EnumAdapterModes(UINT Adapter, UINT Mode, D3DDISPLAYMODE* pMode)
{
    if (pMode == nullptr || !(Adapter < CurrentAdapterCount && Mode < CurrentAdapterModeCount[Adapter]))
    {
        return D3DERR_INVALIDCALL;
    }

    pMode->Format = CurrentAdapterModes[Adapter].at(Mode).Format;
    pMode->Height = CurrentAdapterModes[Adapter].at(Mode).Height;
    pMode->RefreshRate = CurrentAdapterModes[Adapter].at(Mode).RefreshRate;
    pMode->Width = CurrentAdapterModes[Adapter].at(Mode).Width;

    return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3D8::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)
{
    return ProxyInterface->GetAdapterDisplayMode(Adapter, pMode);
}
HRESULT STDMETHODCALLTYPE Direct3D8::CheckDeviceType(UINT Adapter, D3DDEVTYPE CheckType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)
{
    return ProxyInterface->CheckDeviceType(Adapter, CheckType, DisplayFormat, BackBufferFormat, bWindowed);
}
HRESULT STDMETHODCALLTYPE Direct3D8::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
    if (CheckFormat == D3DFMT_UYVY || CheckFormat == D3DFMT_YUY2 || CheckFormat == MAKEFOURCC('Y', 'V', '1', '2') || CheckFormat == MAKEFOURCC('N', 'V', '1', '2'))
    {
        return D3DERR_NOTAVAILABLE;
    }
    return ProxyInterface->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}
HRESULT STDMETHODCALLTYPE Direct3D8::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType)
{
    return ProxyInterface->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, nullptr);
}
HRESULT STDMETHODCALLTYPE Direct3D8::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
    return ProxyInterface->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}
HRESULT STDMETHODCALLTYPE Direct3D8::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS8* pCaps)
{
    if (pCaps == nullptr)
    {
        return D3DERR_INVALIDCALL;
    }

    D3DCAPS9 DeviceCaps;

    const HRESULT hr = ProxyInterface->GetDeviceCaps(Adapter, DeviceType, &DeviceCaps);

    if (FAILED(hr))
    {
        return hr;
    }

    ConvertCaps(DeviceCaps, *pCaps);

    return D3D_OK;
}
HMONITOR STDMETHODCALLTYPE Direct3D8::GetAdapterMonitor(UINT Adapter)
{
    return ProxyInterface->GetAdapterMonitor(Adapter);
}
void UpdatePresentParameterForMultisample(D3DPRESENT_PARAMETERS* pPresentationParameters, D3DMULTISAMPLE_TYPE MultiSampleType)
{
    if (!pPresentationParameters)
    {
        return;
    }

    pPresentationParameters->MultiSampleType = MultiSampleType;

    pPresentationParameters->Flags &= ~D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
    pPresentationParameters->SwapEffect = D3DSWAPEFFECT_DISCARD;// D3DSWAPEFFECT_FLIP;// 

    if (!pPresentationParameters->EnableAutoDepthStencil)
    {
        pPresentationParameters->EnableAutoDepthStencil = true;
        pPresentationParameters->AutoDepthStencilFormat = D3DFMT_D24S8;
    }
}
extern void ToggleWindowed();
extern bool IsOptionOn(const char* option);
HRESULT STDMETHODCALLTYPE Direct3D8::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS8* pPresentationParameters, Direct3DDevice8** ppReturnedDeviceInterface)
{

    // MessageBox(0, 0, 0, 0);
#ifndef D3D8TO9NOLOG
    LOG << "Redirecting '" << "IDirect3D8::CreateDevice" << "(" << this << ", " << Adapter << ", " << DeviceType << ", " << hFocusWindow << ", " << BehaviorFlags << ", " << pPresentationParameters << ", " << ppReturnedDeviceInterface << ")' ..." << std::endl;
#endif

    if (pPresentationParameters == nullptr || ppReturnedDeviceInterface == nullptr)
    {
        return D3DERR_INVALIDCALL;
    }

    Gfx::hFocusWindow = hFocusWindow;
    if(!pPresentationParameters->Windowed && IsOptionOn("LM_GFX_bWindowed"))
        Gfx::command = Gfx::Command::ToggleWindowed;

    *ppReturnedDeviceInterface = nullptr;

    D3DPRESENT_PARAMETERS PresentParams;
    ConvertPresentParameters(*pPresentationParameters, PresentParams);

    IDirect3DDevice9* DeviceInterface = nullptr;

    if (Gfx::bVSync)
    {
        PresentParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
        PresentParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    }
    else
    {
        PresentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    }
    PresentParams.BackBufferCount = Gfx::numBackBuffers;// d3dpp.BackBufferCount;
    PresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;


    // Create new d3d9 device
    HRESULT hr = D3DERR_INVALIDCALL;

    // Setup presentation parameters
    D3DPRESENT_PARAMETERS d3dpp;
    CopyMemory(&d3dpp, &PresentParams, sizeof(D3DPRESENT_PARAMETERS));
    CopyMemory(&current_params, &d3dpp, sizeof(D3DPRESENT_PARAMETERS));

    // Check for AntiAliasing
    if (Gfx::AntiAliasing != 0)
    {
        extern DWORD QualityLevels;
        QualityLevels = 0;

        // Check AntiAliasing quality
        for (int x = Gfx::AntiAliasing == 1 ? 16 : min(16, Gfx::AntiAliasing); x > 0; x--)
        {
            if (SUCCEEDED(ProxyInterface->CheckDeviceMultiSampleType(Adapter,
                DeviceType, (d3dpp.BackBufferFormat) ? d3dpp.BackBufferFormat : D3DFMT_A8R8G8B8, d3dpp.Windowed,
                (D3DMULTISAMPLE_TYPE)x, &QualityLevels)) ||
                SUCCEEDED(ProxyInterface->CheckDeviceMultiSampleType(Adapter,
                    DeviceType, d3dpp.AutoDepthStencilFormat, d3dpp.Windowed,
                    (D3DMULTISAMPLE_TYPE)x, &QualityLevels)))
            {
                // Update Present Parameter for Multisample
                UpdatePresentParameterForMultisample(&d3dpp, (D3DMULTISAMPLE_TYPE)x, (QualityLevels > 0) ? QualityLevels - 1 : 0);

                // Create Device
                hr = ProxyInterface->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, &d3dpp, &DeviceInterface);

                // Check if device was created successfully
                if (SUCCEEDED(hr))
                {
                    CopyMemory(&current_params, &d3dpp, sizeof(D3DPRESENT_PARAMETERS));
                    DeviceMultiSampleType = (D3DMULTISAMPLE_TYPE)x;
                    DeviceInterface->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
                    //LOG_LIMIT(3, "Setting MultiSample " << d3dpp.MultiSampleType << " Quality " << d3dpp.MultiSampleQuality);
                    break;
                }
            }
        }
        if (DeviceMultiSampleType &&
            (ProxyInterface->CheckDeviceFormat(Adapter, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, 0, D3DRTYPE_SURFACE, (D3DFORMAT)MAKEFOURCC('S', 'S', 'A', 'A')) == S_OK))
        {
            SetSSAA = true;
        }

        if (FAILED(hr))
        {
            MessageBox(0, " Failed to enable AntiAliasing!", 0, 0);
            printf("Failed to enable AntiAliasing");
        }
    }

    // Create Device
    if (FAILED(hr))
    {
        // Update presentation parameters
        // Create Device
        hr = ProxyInterface->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, &PresentParams, &DeviceInterface);
    }


    //extern __restrict LPDIRECT3DDEVICE9 pDevice;
    Gfx::pDevice = DeviceInterface;

    //const HRESULT hr = ProxyInterface->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, &PresentParams, &DeviceInterface);

    if (FAILED(hr))
    {
        MessageBox(0, "failed", "", 0);
        return hr;
    }

    D3DCAPS9 caps;
    ProxyInterface->GetDeviceCaps(Adapter, DeviceType, &caps);
    MaxAnisotropy = caps.MaxAnisotropy;

    //MessageBox(0, 0, 0, 0);

    *ppReturnedDeviceInterface = new Direct3DDevice8(this, DeviceInterface, (PresentParams.Flags & D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL) != 0);

    // Set default vertex declaration
    DeviceInterface->SetFVF(D3DFVF_XYZ);
    //MessageBox(0, "I need this to test", "", 0);

    return D3D_OK;
}
