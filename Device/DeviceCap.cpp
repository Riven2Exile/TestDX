#include "stdafx.h"
#include "DeviceCap.h"

CDeviceCap::CDeviceCap()
{

}

CDeviceCap::~CDeviceCap()
{

}

CDeviceCap& CDeviceCap::Instance(){
    static CDeviceCap inst;
    return inst;
}


extern IDirect3DDevice9 *g_pDevice;

void CDeviceCap::doSomething()
{
    // do something
    D3DCAPS9* pCaps = NULL;
    g_pDevice->GetDeviceCaps(pCaps);
}