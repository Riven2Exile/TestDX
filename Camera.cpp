
#include "Camera.h"

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}


void CCamera::SetLookAt3Vecter(const D3DXVECTOR3& locate, 
                               const D3DXVECTOR3& lookAt, 
                               const D3DXVECTOR3& up)
{
    _locate = locate;
    _lookAt = lookAt;
    _up = up;
}

void CCamera::SetLocate(D3DXVECTOR3 locate)
{
    _locate = locate;
}

D3DXMATRIXA16 CCamera::GetLookAtMatrix()
{
    D3DXMATRIXA16 view;
    D3DXMatrixLookAtLH(&view, &_locate, &_lookAt, &_up);
    return view;
}


D3DXVECTOR3 CCamera::GetLocate()
{
    return _locate;
}

D3DXVECTOR3 CCamera::GetLookAt()
{
    return _lookAt;
}

D3DXVECTOR3 CCamera::GetUp()
{
    return _up;
}