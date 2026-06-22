#pragma once

#include <windows.h>
#include <cfgmgr32.h>
#include <devpropdef.h>

#ifndef __SWDEVICE_H__
#define __SWDEVICE_H__

typedef HANDLE HSWDEVICE;
typedef HSWDEVICE *PHSWDEVICE;

#ifndef DEVPROPSTORE
typedef enum _DEVPROPSTORE {
    DEVPROP_STORE_SYSTEM,
    DEVPROP_STORE_USER
} DEVPROPSTORE, *PDEVPROPSTORE;
#endif

#ifndef DEVPROPCOMPKEY_DEFINED
#define DEVPROPCOMPKEY_DEFINED
typedef struct _DEVPROPCOMPKEY {
    DEVPROPKEY Key;
    DEVPROPSTORE Store;
    PCWSTR LocaleName;
} DEVPROPCOMPKEY, *PDEVPROPCOMPKEY;
#endif

#ifndef DEVPROPERTY_DEFINED
#define DEVPROPERTY_DEFINED
typedef struct _DEVPROPERTY {
    DEVPROPCOMPKEY CompKey;
    DEVPROPTYPE Type;
    ULONG BufferSize;
    PVOID Buffer;
} DEVPROPERTY, *PDEVPROPERTY;
#endif

typedef int SW_DEVICE_CAPABILITIES;
#define SWDeviceCapabilitiesNone 0
#define SWDeviceCapabilitiesRemovable 1
#define SWDeviceCapabilitiesSilentInstall 2
#define SWDeviceCapabilitiesNoDisplayInUI 4
#define SWDeviceCapabilitiesDriverRequired 8

typedef int SW_DEVICE_LIFETIME;
#define SWDeviceLifetimeHandle 0
#define SWDeviceLifetimeParentPresent 1
#define SWDeviceLifetimeMax 2

typedef VOID (CALLBACK *SW_DEVICE_CREATE_CALLBACK)(
    _In_ HSWDEVICE hSwDevice,
    _In_ HRESULT hrCreateResult,
    _In_opt_ PVOID pContext,
    _In_opt_ PCWSTR pszDeviceInstanceId);

typedef struct SW_DEVICE_CREATE_INFO_ {
    DWORD cbSize;
    PCWSTR pszInstanceId;
    PCWSTR pszzHardwareIds;
    PCWSTR pszzCompatibleIds;
    const GUID *pContainerId;
    ULONG CapabilityFlags;
    PCWSTR pszDeviceDescription;
    PCWSTR pszDeviceLocation;
    const SECURITY_DESCRIPTOR *pSecurityDescriptor;
} SW_DEVICE_CREATE_INFO;

HRESULT WINAPI SwDeviceCreate(
    _In_ PCWSTR pszEnumeratorName,
    _In_ PCWSTR pszParentDeviceInstance,
    _In_ const SW_DEVICE_CREATE_INFO *pCreateInfo,
    _In_ DWORD cPropertyCount,
    _In_reads_opt_(cPropertyCount) const DEVPROPERTY *pProperties,
    _In_opt_ SW_DEVICE_CREATE_CALLBACK pCallback,
    _In_opt_ PVOID pContext,
    _Out_ HSWDEVICE *phSwDevice);

VOID WINAPI SwDeviceClose(_In_ HSWDEVICE hSwDevice);

HRESULT WINAPI SwDeviceSetLifetime(
    _In_ HSWDEVICE hSwDevice,
    _In_ SW_DEVICE_LIFETIME lifetime);

#endif
